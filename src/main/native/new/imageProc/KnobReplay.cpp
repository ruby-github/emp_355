/*
 * 2009, 深圳恩普电子技术有限公司
 *
 * @file: KnobLoadSnap
 * @brief: knob in freeze mode
 *
 * version: V1.0
 * date: 20010-1-19
 * @author: liudan
 */

#include <deque>
#include "imageProc/KnobReplay.h"
#include "display/KnobMenu.h"
#include "imageProc/FreezeMode.h"
#include "imageProc/Replay.h"
#include "Def.h"
#include "display/gui_global.h"
#include "patient/VideoMan.h"
#include "periDevice/PeripheralMan.h"
#include "sysMan/SysOptions.h"
#include "display/HintArea.h"
#include "utils/MessageDialog.h"
#include "ViewMain.h"
#include "imageProc/ModeStatus.h"
#include "sysMan/ViewSuperuser.h"

using std::deque;

KnobMenu::KnobItem KnobReplayMenu[] = {
    {N_("Replay"), "", MIN, ReplayChgSpeed, NULL},
    {N_("Replay Speed"), "", MIN, NULL, PressChgSpeed},
    {N_("Trim Left"),"", PRESS, ReplayChgTrimLeft460, NULL},
    {N_("Trim Right"),"", PRESS, ReplayChgTrimRight460, NULL},
    {N_("Reset Trim"),N_("Press"), PRESS, ReplayChgResetTrim460, NULL},
    {N_("Save Cine"), N_("Press"), PRESS, ReplayChgSaveCine460, NULL}
};

KnobMenu::KnobItem DemoKnobReplayMenu[] = {
    {N_("Replay/Speed"), "", MIN, ReplayChgSpeed, ReplayChgCtrl},
    {"", "", ERROR, NULL, NULL},
    {"", "", ERROR, NULL, NULL},
    {"", "", ERROR, NULL, NULL},
    {"", "", ERROR, NULL, NULL},
    {"", "", ERROR, NULL, NULL}
};

const char * Toggle_Replay[2] = {
    N_("OFF"),
    N_("ON")
};

void KnobReplayCreate() {
    if(ViewSuperuser::GetInstance()->GetDemoStatus()) {
        KnobMenu::GetInstance()->SetItem(DemoKnobReplayMenu, sizeof(DemoKnobReplayMenu)/sizeof(KnobMenu::KnobItem), KnobMenu::REPLAY);
    } else {
        KnobReplayMenu[REPLAY_CINE].status = PRESS;
        KnobMenu::GetInstance()->SetItem(KnobReplayMenu, sizeof(KnobReplayMenu)/sizeof(KnobMenu::KnobItem), KnobMenu::REPLAY);
    }
}

void KnobCineCreate() {
    KnobReplayCreate();
}

//sync
void SyncKnobReplay(EKnobReplay type, const char* s, EKnobReturn status, bool draw) {
    if(ViewSuperuser::GetInstance()->GetDemoStatus()) {
        if(type == REPLAY_CTRL) {
            DemoKnobReplayMenu[type].value = s;
            DemoKnobReplayMenu[type].status = status;
        }
    } else {
        KnobReplayMenu[type].value = s;
        KnobReplayMenu[type].status = status;
    }
    if (draw)
        KnobMenu::GetInstance()->Update();
}

///> callback function
EKnobReturn ReplayChgCtrl(void) {
    EKnobReturn ret;
    ret = FreezeMode::GetInstance()->ChangeAutoReplay();
    return ret;
}

EKnobReturn ReplayChgSpeed(EKnobOper oper) {
    EKnobReturn ret;
    ret = Replay::GetInstance()->ChangeSpeed(oper);
    return ret;
}

EKnobReturn PressChgSpeed(void) {
    EKnobReturn ret;
    ret = Replay::GetInstance()->ChangeSpeed(ROTATE);
    return ret;
}

EKnobReturn ReplayChgTrimLeft(void) {
    return PRESS;
}

EKnobReturn ReplayChgTrimRight(void) {
    return PRESS;
}

EKnobReturn ReplayChgResetTrim(void) {
    return PRESS;
}

EKnobReturn ReplayChgTrimLeft460(EKnobOper oper) {
    Replay::GetInstance()->SetTrimLeft(oper);
    return PRESS;
}

EKnobReturn ReplayChgTrimRight460(EKnobOper oper) {
    Replay::GetInstance()->SetTrimRight(oper);
    return PRESS;
}

EKnobReturn ReplayChgResetTrim460(EKnobOper oper) {
    Replay::GetInstance()->ResetTrim(oper);
    return PRESS;
}

static VideoMan::VideoItem item;
static gboolean DelayToSaveCine(gpointer data) {
    // save to image manage
    if(VideoMan::GetInstance()->GetVideoStorage() == VideoMan::UDISK) {
        PeripheralMan* ptrPeripheralMan = PeripheralMan::GetInstance();

        if(!ptrPeripheralMan->CheckUsbStorageState()) {
            HintArea::GetInstance()->UpdateHint(_("Error: No USB device Plug-in!"), 2);
            free(data);
            //	free(item.data);
            return ERROR;
        }
        if(!ptrPeripheralMan->MountUsbStorage()) {
            HintArea::GetInstance()->UpdateHint(_("Error: Failed to mount USB device!"), 2);
            free(data);
            //	free(item.data);
            return ERROR;
        }

        VideoMan::GetInstance()->SaveVideo(0, (char*)data, UDISK_PATH, &item);

        ptrPeripheralMan->UmountUsbStorage();
    } else
        VideoMan::GetInstance()->SaveVideo(0, (char*)data, STORE_PATH, &item);

    if(data !=NULL)
        free(data);

    return FALSE;
}

static int SaveCine(gpointer data) {
    PRINTF("SaveCine file name: %s\n", (char*)data);

    HintArea::GetInstance()->UpdateHint(_("Saving..."), 0);

    g_timeout_add(100, DelayToSaveCine, data);

    return OK;
}

EKnobReturn ReplayChgSaveCine(void) {
    if (!Replay::GetInstance()->GetCineImg(&(item.deq), item.begin, item.frames, item.width, item.height, item.frame_rate)) {
        HintArea::GetInstance()->UpdateHint(_("[Replay]: No image can be saved."), 1);
        return ERROR;
    }

    SysOptions so;
    if(!so.GetCineAutoName()) {
        if(!ModeStatus::IsFreezeMode())
            FreezeMode::GetInstance()->PressFreeze();
        MessageDialog::GetInstance()->Create(GTK_WINDOW(ViewMain::GetInstance()->GetMainWindow()),
                                          MessageDialog::DLG_FILENAME,
                                          _("Please input the file name(without suffix)"),
                                          &SaveCine);
    } else {
        time_t at;
        at = time(&at);

        struct tm* ct;
        ct = localtime(&at);

        char *fileName = (char*)malloc(256);
        //	char fileName[15];
        memset(fileName, 0, 255);
        sprintf(fileName, "%d%d%d%d%d%d%d%d%d%d%d", (ct->tm_year+1900), (ct->tm_mon+1)/10, (ct->tm_mon+1)%10, (ct->tm_mday)/10, (ct->tm_mday)%10, (ct->tm_hour)/10, (ct->tm_hour)%10, (ct->tm_min)/10, (ct->tm_min)%10, (ct->tm_sec)/10, (ct->tm_sec)%10);

        SaveCine(fileName);
    }

    return PRESS;
}

EKnobReturn ReplayChgSaveCine460(EKnobOper oper) {
    if (!Replay::GetInstance()->GetCineImg(&(item.deq), item.begin, item.frames, item.width, item.height, item.frame_rate)) {
        HintArea::GetInstance()->UpdateHint(_("[Replay]: No image can be saved."), 1);
        return ERROR;
    }

    SysOptions so;
    if(!so.GetCineAutoName()) {
        if(!ModeStatus::IsFreezeMode())
            FreezeMode::GetInstance()->PressFreeze();
        MessageDialog::GetInstance()->Create(GTK_WINDOW(ViewMain::GetInstance()->GetMainWindow()),
                                          MessageDialog::DLG_FILENAME,
                                          _("Please input the file name(without suffix)"),
                                          &SaveCine);
    } else {
        time_t at;
        at = time(&at);

        struct tm* ct;
        ct = localtime(&at);

        char *fileName = (char*)malloc(256);
        //	char fileName[15];
        memset(fileName, 0, 255);
        sprintf(fileName, "%d%d%d%d%d%d%d%d%d%d%d", (ct->tm_year+1900), (ct->tm_mon+1)/10, (ct->tm_mon+1)%10, (ct->tm_mday)/10, (ct->tm_mday)%10, (ct->tm_hour)/10, (ct->tm_hour)%10, (ct->tm_min)/10, (ct->tm_min)%10, (ct->tm_sec)/10, (ct->tm_sec)%10);

        SaveCine(fileName);
    }

    return PRESS;
}

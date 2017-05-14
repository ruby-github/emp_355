#include "sysMan/SysGeneralSetting.h"

#include "Def.h"

SysGeneralSetting::SysGeneralSetting() {
  m_inifile = new IniFile(string(CFG_RES_PATH) + string(SYS_SETTING_FILE));
}

SysGeneralSetting::~SysGeneralSetting() {
  if (m_inifile != NULL) {
    delete m_inifile;
  }

  m_inifile = NULL;
}

string SysGeneralSetting::GetHospital() {
  return m_inifile->ReadString("GeneralSetting", "Hospital");
}

int SysGeneralSetting::GetLanguage() {
  return m_inifile->ReadInt("GeneralSetting", "Language");
}

int SysGeneralSetting::GetDateFormat() {
  return m_inifile->ReadInt("GeneralSetting", "DateFormat");
}

int SysGeneralSetting::GetVideoMode() {
  return m_inifile->ReadInt("GeneralSetting", "VideoMode");
}

int SysGeneralSetting::GetConnectorType() {
  return m_inifile->ReadInt("GeneralSetting", "ConnectorType");
}

int SysGeneralSetting::GetVideoFormat() {
  return m_inifile->ReadInt("GeneralSetting", "VideoDisplayFormat");
}

int SysGeneralSetting::GetPrinterMethod() {
  return m_inifile->ReadInt("GeneralSetting", "PrinterMethod");
}

int SysGeneralSetting::GetPrinter() {
  return m_inifile->ReadInt("GeneralSetting", "Printer");
}

int SysGeneralSetting::GetScreenProtect() {
  int screenProtect =  m_inifile->ReadInt("GeneralSetting", "ScreenProtect");

  int ScreenSaver = 0;

  switch (screenProtect) {
  case 0:
    ScreenSaver = 0;
    break;
  case 1:
    ScreenSaver = 5;
    break;
  case 2:
    ScreenSaver = 10;
    break;
  case 3:
    ScreenSaver = 20;
    break;
  case 4:
    ScreenSaver = 30;
    break;
  case 5:
    ScreenSaver = 45;
    break;
  case 6:
    ScreenSaver = 60;
    break;
  default:
    ScreenSaver = 0;
  }

  return ScreenSaver;
}

int SysGeneralSetting::GetPrintViewMode() {
  return m_inifile->ReadInt("GeneralSetting", "PrintViewMode");
}

int SysGeneralSetting::GetAutoGeneratedID() {
  return m_inifile->ReadInt("GeneralSetting", "AutoGeneratedID");
}

int SysGeneralSetting::GetFID() {
  return m_inifile->ReadInt("GeneralSetting", "FID");
}

int SysGeneralSetting::GetDirection() {
  return m_inifile->ReadInt("PwMenuSetting", "TraceDirection");
}

int SysGeneralSetting::GetScaleUnit() {
  return m_inifile->ReadInt("PwMenuSetting", "ScaleUnit");
}

int SysGeneralSetting::GetTraceType() {
  return m_inifile->ReadInt("PwMenuSetting", "TraceType");
}

int SysGeneralSetting::GetSmooth() {
  return m_inifile->ReadInt("PwMenuSetting", "TraceSmooth");
}

int SysGeneralSetting::GetThreshold() {
  return m_inifile->ReadInt("PwMenuSetting", "TraceThreshold");
}

void SysGeneralSetting::SetHospital(string hospital) {
  m_inifile->WriteString("GeneralSetting", "Hospital", hospital);
}

// language: 0-english, 1-chinese
void SysGeneralSetting::SetLanguage(int language) {
  m_inifile->WriteInt("GeneralSetting", "Language", language);
}

// format: 0-Y/M/D, 1-M/D/Y, 2-D/M/Y
void SysGeneralSetting::SetDateFormat(int format) {
  m_inifile->WriteInt("GeneralSetting", "DateFormat", format);
}

// videoMode: 0-PAL, 1-NTSC
void SysGeneralSetting::SetVideoMode(int videoMode) {
  m_inifile->WriteInt("GeneralSetting", "VideoMode", videoMode);
}

// ConnectorType: 0-Mainboard, 1-Q7
void SysGeneralSetting::SetConnectorType(int connectorType) {
  m_inifile->WriteInt("GeneralSetting", "ConnectorType", connectorType);
}

void SysGeneralSetting::SetVideoFormat(int format) {
  m_inifile->WriteInt("GeneralSetting", "VideoDisplayFormat", format);
}

void SysGeneralSetting::SetPrinterMethod(int method) {
  m_inifile->WriteInt("GeneralSetting", "PrinterMethod", method);
}

// printer: 0-inkjet, 1-laser, 2-video
void SysGeneralSetting::SetPrinter(int printer) {
  m_inifile->WriteInt("GeneralSetting", "Printer", printer);
}

// screenProtect: 0-no, 5, 10, 20, 30, 45, 60
void SysGeneralSetting::SetScreenProtect(int screenProtect) {
  m_inifile->WriteInt("GeneralSetting", "ScreenProtect", screenProtect);
}

void SysGeneralSetting::SetPrintViewMode(int viewMode) {
  m_inifile->WriteInt("GeneralSetting", "PrintViewMode", viewMode);
}

void SysGeneralSetting::SetAutoGeneratedID(int autoGen) {
  m_inifile->WriteInt("GeneralSetting", "AutoGeneratedID", autoGen);
}

void SysGeneralSetting::SetDirection(int direction) {
  m_inifile->WriteInt("PwMenuSetting", "TraceDirection", direction);
}

void SysGeneralSetting::SetScaleUnit(int scaleunit) {
  m_inifile->WriteInt("PwMenuSetting", "ScaleUnit", scaleunit);
}

void SysGeneralSetting::SetTraceType(int tracetype) {
  m_inifile->WriteInt("PwMenuSetting", "TraceType", tracetype);
}

void SysGeneralSetting::SetSmooth(int smooth) {
  m_inifile->WriteInt("PwMenuSetting", "TraceSmooth", smooth);
}

void SysGeneralSetting::SetThreshold(int threshold) {
  m_inifile->WriteInt("PwMenuSetting", "TraceThreshold", threshold);
}

void SysGeneralSetting::DefaultFactory() {
  m_inifile->WriteInt("GeneralSetting", "TimeFormat", 0);
  m_inifile->WriteInt("GeneralSetting", "Language", 0);
  m_inifile->WriteInt("GeneralSetting", "DateFormat", 0);
  m_inifile->WriteInt("GeneralSetting", "PrinterMethod", 0);
  m_inifile->WriteInt("GeneralSetting", "Printer", 0);
  m_inifile->WriteInt("GeneralSetting", "ScreenProtect", 0);
}

void SysGeneralSetting::TVOutDefaultFactory() {
  m_inifile->WriteInt("GeneralSetting", "VideoMode", 0);
  // m_inifile->WriteInt("GeneralSetting", "ConnectorType", 0);
  m_inifile->WriteInt("GeneralSetting", "VideoDisplayFormat", 0);
}

void SysGeneralSetting::SyncFile() {
  m_inifile->SyncConfigFile();
}

#ifdef TRANSDUCER
  int SysGeneralSetting::GetPressAjust() {
    return m_inifile->ReadInt("GeneralSetting", "PressAjust");
  }

  void SysGeneralSetting::SetPressAdjust(double PressAjust) {
    m_inifile->WriteInt("GeneralSetting", "PressAjust", PressAjust);
  }
#endif
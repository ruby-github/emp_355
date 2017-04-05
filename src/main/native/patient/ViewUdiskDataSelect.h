#ifndef _VIEWUDISKDATA_SELECT_H_
#define _VIEWUDISKDATA_SELECT_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class FakeXEvent;
class ViewUdiskDataSelect: public FakeXEvent
{
public:
    ~ViewUdiskDataSelect();
	static ViewUdiskDataSelect* GetInstance();
	void CreateWindow(GtkWindow *parent);
	GtkWidget* GetWindow() {return m_window;}
	vector<string> GetSelectedVec() {return m_vecPath;}
	void ClearData() { m_vecPath.clear();}
	void DeleteSlideFile(void);
	void DestroyWindow(void);

private:
	enum{
		COL_CHECKED,
		COL_NAME,
		NUM_COLS
	};

	ViewUdiskDataSelect(void);
	static ViewUdiskDataSelect* m_ptrInstance;
    void KeyEvent(unsigned char KeyValue);

	GtkWidget *m_window;
	GtkWidget *m_treeRoot;
	GtkWidget *m_treeBranch;
	GtkWidget *m_chkbtnDel;
	GList *m_listBranch;

	vector<string> m_vecPath;

    GtkWidget* create_treeview(gint type);	
    GtkTreeModel* create_root_model(void);
	void UpdateRootModel(void);
	void UpdateBranchModel(gint rows);
	GtkTreeModel* LoadBranchModel(gchar *branch);
	void SetAllToggleValue(GtkTreeModel *model, gboolean value);
	gboolean GetAllSelectPath(void);
	gboolean CheckBranchStauts(void);

	//signal handle
    gboolean WindowDeleteEvent(GtkWidget *widget, GdkEvent *event);
//	void BtnSelectAllClicked(GtkButton *button);
//	void BtnDeselectClicked(GtkButton *button);
    void BtnOKClicked(GtkButton *button);
    void BtnCancelClicked(GtkButton *button);
	void ToggleData(GtkCellRendererToggle *cell, gchar *path_str);
	void RootSelectionChanged(GtkTreeSelection *selection);

	//signal connect 
    static gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, ViewUdiskDataSelect* data) { return data->WindowDeleteEvent(widget, event); }
    static void on_data_toggled(GtkCellRendererToggle *cell, gchar *path_str, ViewUdiskDataSelect* data) { data->ToggleData(cell, path_str); }
    static void on_root_selection_changed(GtkTreeSelection *selction, ViewUdiskDataSelect* data) { data->RootSelectionChanged(selction); }
    static void on_button_ok_clicked(GtkButton *button, ViewUdiskDataSelect* data) { data->BtnOKClicked(button); }
    static void on_button_cancel_clicked(GtkButton *button, ViewUdiskDataSelect* data) { data->BtnCancelClicked(button); }
//	static void on_button_select_all_clicked(GtkButton *button, ViewUdiskDataSelect* data) { data->BtnSelectAllClicked(button); }
//	static void on_button_deselect_clicked(GtkButton *button, ViewUdiskDataSelect* data) { data->BtnSelectAllClicked(button); }
};

#endif

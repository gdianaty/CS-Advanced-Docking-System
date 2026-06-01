#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QWidgetAction>

#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    CS_OBJECT(CMainWindow)

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

protected:
	virtual void closeEvent(QCloseEvent* event) override;

private:
	QAction* SavePerspectiveAction = nullptr;
	QWidgetAction* PerspectiveListAction = nullptr;
	QComboBox* PerspectiveComboBox = nullptr;

    Ui::CMainWindow *ui;

    ads::CDockManager* DockManager;
    ads::CDockAreaWidget* StatusDockArea;
    ads::CDockWidget* TimelineDockWidget;

    void createPerspectiveUi();

private :
	CS_SLOT_1(Private, void savePerspective())
	CS_SLOT_2(savePerspective) 
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QList>
#include <QSystemTrayIcon>
#include <QTimer>
#include "TaskButton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void operationButtonClicked();
    void taskStartedEditing();
    void taskCancelledEditing();
    void taskFinishedEditing();
    void taskDeleted();
    void taskMovedUp();
    void taskMovedDown();
    void saveSettings();
    void systemTrayActivated(QSystemTrayIcon::ActivationReason activationReason);
    void updateSystemTrayToolTip();

private:

    enum State {
        NORMAL,
        EDITING
    };

    struct TaskItem {
        TaskButton *taskButton;
        QAction *trayAction;
    };


    Ui::MainWindow *ui;
    QList<TaskItem*> taskItems;
    QTimer tickTimer;
    QTimer saveTimer;
    State state;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *systemTrayMenu;
    QAction *quitAction;
    QRect oldGeometry;

    TaskItem *addTaskItem(Task task);
    void changeState(State newState);
    void loadSettings();
    void setupTrayIcon();
    void removeTaskItem(TaskItem* taskItem);
    TaskItem* getTaskItemFromButton(TaskButton* taskButton);
    void moveTaskItem(int fromIndex, int toIndex);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);

};

#endif // MAINWINDOW_H
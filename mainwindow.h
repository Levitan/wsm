#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui.h"

class QAction;
class QMenu;
class SnapShot;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void aboutMsg();
    void enableBtns();
    void disableBtns();

private:
    QMenu *fileMenu, *aboutMenu;
    QToolBar *toolBar;
    QAction *quitAct, *about, *save, *open, *saveAct, *openAct, *exitAct;
    Ui *ui;
};

#endif // MAINWINDOW_H

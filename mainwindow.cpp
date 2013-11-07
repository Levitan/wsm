#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui;

    fileMenu = new QMenu;
    aboutMenu = new QMenu;

    fileMenu = menuBar()->addMenu(tr("&File"));
    aboutMenu = menuBar()->addMenu(tr("Support"));

    about = new QAction(QIcon(":/img/about-ico.png"), tr("About WebScreen Maker"), this);
    open = new QAction(QIcon(":/img/url-min.png"), tr("Load Url"), this);
    save = new QAction(QIcon(":/img/save-min.png"), tr("Make ScreenShot"), this);
    quitAct = new QAction(QIcon(":/img/exit.png"), tr("Quit"), this);

    open->setShortcut(QKeySequence("Ctrl+O"));
    save->setShortcut(QKeySequence("Ctrl+S"));
    quitAct->setShortcut(QKeySequence("Ctrl+Q"));

    save->setEnabled(false);

    fileMenu->addAction(open);
    fileMenu->addAction(save);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    aboutMenu->addAction(about);

    toolBar = new QToolBar;
    toolBar = addToolBar(tr("Main"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->setMovable(false);

    openAct = new QAction(QIcon(":/img/url.png"), tr("Load Url"), this);
    saveAct = new QAction(QIcon(":/img/save.png"), tr("Make ScreenShot"), this);
    exitAct = new QAction(QIcon(":/img/exitact.png"), tr("Quit"), this);
    saveAct->setEnabled(false);

    toolBar->addAction(openAct);
    toolBar->addAction(saveAct);
    toolBar->addAction(exitAct);

    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutMsg()));
    connect(openAct, SIGNAL(triggered()), ui, SLOT(addUrl()));
    connect(open, SIGNAL(triggered()), ui, SLOT(addUrl()));
    connect(save, SIGNAL(triggered()), ui, SLOT(saveFile()));
    connect(saveAct, SIGNAL(triggered()), ui, SLOT(saveFile()));
    connect(ui, SIGNAL(loadComplete()), this, SLOT(enableBtns()));
    connect(ui, SIGNAL(loadStart()), this, SLOT(disableBtns()));
    setCentralWidget(ui);
    resize(500, 300);
    setWindowTitle(tr("WebScreen Maker"));

}

void MainWindow::aboutMsg(){
    QMessageBox *abMsg = new QMessageBox;
    abMsg->setText(QString::fromUtf8("<center><h2>WebScreen Maker 0.1.1b</h2></center><br><b>") + tr("Developer") + QString::fromUtf8("</b>: <a href=\"mailto:vlevitan91@gmail.com\">Vitaly Levitan</a>"));
    abMsg->setWindowTitle(tr("About WebScreen Maker"));
    abMsg->setIconPixmap(QPixmap(":/img/about.png"));
    abMsg->exec();
}

void MainWindow::enableBtns(){
    save->setEnabled(true);
    saveAct->setEnabled(true);
}
void MainWindow::disableBtns(){
    save->setEnabled(false);
    saveAct->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete fileMenu;
    delete aboutMenu;
    delete toolBar;
    delete ui;
}

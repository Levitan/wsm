#include "ui.h"
#include <QtGui>
#include <QtWebKit>

Ui::Ui(QWidget *parent) :
    QWidget(parent){

// --------------- Widgets --------------- //

    web = new QWebView;
  // --- Left Block --- //
    leftBlock = new QGroupBox;

    //settingLab = new QLabel(tr("Properties"));
    wLab = new QLabel(tr("Width: "));
    hLab = new QLabel(tr("Height: "));

      /* -- Spin Boxes -- */
    wSpin = new QSpinBox;
    wSpin->setRange(800, 2560);
    wSpin->setValue(1280);

    hSpin = new QSpinBox;
    hSpin->setRange(600, 1600);

      /* -- Check Boxes -- */
    fullEn = new QCheckBox(tr("Full Size"));
    fullEn->setChecked(true);
    if(fullEn->isChecked()) { hSpin->setEnabled(false); }
    else { hSpin->setEnabled(true); }
    flashEn = new QCheckBox(tr("Flash"));
    jsEn = new QCheckBox(tr("JavaScript"));
    jsEn->setChecked(true);
    javaEn = new QCheckBox(tr("Java"));

  // --- Right Block --- //
    urlLab = new QLabel(tr("Url: "));
    urlLine = new QLineEdit;
    startBtn = new QPushButton(">");
    prevArea = new QScrollArea;
    prevArea->setFrameShape(QFrame::NoFrame);
    rightBlock = new QGroupBox;
    pBar = new QProgressBar();
    pBar->setOrientation(Qt::Horizontal);
    pBar->setMaximumWidth(200);
    pBar->setMaximumHeight(12);
    QFont font;
    font.setPixelSize(10);
    pBar->setFont(font);
    pBar->setValue(100);

// --------------- Layouts --------------- //

  // --- Left block layouts --- //
    QHBoxLayout *wLay = new QHBoxLayout;
    wLay->addWidget(wLab);
    wLay->addWidget(wSpin);

    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->addWidget(hLab);
    hLay->addWidget(hSpin);


    QVBoxLayout *leftMainLay = new QVBoxLayout;
    leftMainLay->addLayout(wLay);
    leftMainLay->addLayout(hLay);
    leftMainLay->addWidget(fullEn);
    leftMainLay->addWidget(jsEn);
    leftMainLay->addWidget(flashEn);
    leftMainLay->addWidget(javaEn);
    leftMainLay->addStretch();

  // --- Right block layouts --- //
    QHBoxLayout *progLay = new QHBoxLayout;
    progLay->addStretch();
    progLay->addWidget(pBar);

    QHBoxLayout *urlLay = new QHBoxLayout;
    urlLay->addWidget(urlLab);
    urlLay->addWidget(urlLine);
    urlLay->addWidget(startBtn);

    QVBoxLayout *rightMainLay = new QVBoxLayout;
    rightMainLay->addLayout(urlLay);
    rightMainLay->addWidget(prevArea);
    rightMainLay->addLayout(progLay);
    rightMainLay->setContentsMargins(3,3,3,0);

  // --- Main Layouts --- //
    QSplitter *split= new QSplitter(Qt::Horizontal);
    split->addWidget(leftBlock);
    split->addWidget(rightBlock);

    QHBoxLayout *mainLay = new QHBoxLayout;
    mainLay->addWidget(split);
    mainLay->setContentsMargins(3,3,3,0);

// --------------- Settings --------------- //

  // --- Left Block Settings --- //
    leftBlock->setTitle(tr("Properties"));
    leftBlock->setLayout(leftMainLay);
    leftBlock->setMinimumWidth(200);

  // --- Right Block Settings --- //
    rightBlock->setTitle(tr("Browser"));
    rightBlock->setLayout(rightMainLay);
    rightBlock->resize(1280, 0);

  // --- Main Settings --- //
    setLayout(mainLay);

// --------------- SIGNALS / SLOTS --------------- //
    connect(urlLine, SIGNAL(returnPressed()), startBtn, SLOT(click()));
    connect(startBtn, SIGNAL(clicked()), this, SLOT(setUrl()));
    connect(fullEn, SIGNAL(toggled(bool)), hSpin, SLOT(setDisabled(bool)));
    connect(flashEn, SIGNAL(clicked()), this, SLOT(setPlugins()));
    connect(jsEn, SIGNAL(clicked()), this, SLOT(setPlugins()));
    connect(javaEn, SIGNAL(clicked()), this, SLOT(setPlugins()));

}

// --- Get Url from menu and send signal to load --- //
void Ui::addUrl(){
    bool ok;
    QString urlText = QInputDialog::getText(this, tr("Input URL"),
                                            tr("URL"),QLineEdit::Normal, "http://", &ok);
    if(!urlText.isEmpty() && urlText != "http://" && urlText.contains('.') && ok == true){
        if(urlText.contains("http://")) { url = urlText; }
        else { url = "http://" + urlText; }
        urlLine->setText(url);
        loadUrl();
    }
}

// --- Get Url from urlLine and send signal to load --- //
void Ui::setUrl(){
    if(!urlLine->text().isEmpty() && urlLine->text() != "http://" && urlLine->text().contains('.')){
        if(urlLine->text().contains("http://")){ url = urlLine->text(); }
        else { url = "http://" + urlLine->text(); }
        urlLine->setText(url);
        loadUrl();
    }
}

// --- Set destination path to save screenshot and send signal to start rendering --- //
void Ui::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "~",
                                                    tr("PNG Image (*.png);;JPEG Image (*.jpg)"));
    if(!fileName.isEmpty()){
        saveFileName = fileName;
        printPage();
    }
}

void Ui::setPlugins(){
    web->settings()->setAttribute(QWebSettings::PluginsEnabled, flashEn->isChecked());
    web->settings()->setAttribute(QWebSettings::JavascriptEnabled, jsEn->isChecked());
    web->settings()->setAttribute(QWebSettings::JavaEnabled, javaEn->isChecked());
}

// --- Load WebPage --- //
void Ui::loadUrl(){
    prevArea->setWidget(web);
    web->settings()->clearMemoryCaches();
    web->resize(prevArea->width(), prevArea->height());
    connect(web, SIGNAL(loadProgress(int)), pBar, SLOT(setValue(int)));
    connect(web, SIGNAL(loadStarted()), this, SIGNAL(loadStart()));
    connect(web, SIGNAL(loadFinished(bool)), this, SIGNAL(loadComplete()));
    web->load(url);
}

// --- Rendering Screenshot --- //
void Ui::printPage(){
    if(fullEn->isChecked()) { hSize = web->page()->mainFrame()->contentsSize().height(); }
    else { hSize = hSpin->value(); }
    QImage *image = new QImage(QSize(wSpin->value(), hSize), QImage::Format_ARGB32);
    QPainter *paint = new QPainter(image);
    web->page()->setViewportSize(QSize(wSpin->value() + 16, hSize));
    web->page()->mainFrame()->render(paint);
    paint->end();
    image->save(saveFileName);
    web->settings()->clearMemoryCaches();
    delete image;
    delete paint;
    web->page()->setViewportSize(QSize(prevArea->width(), prevArea->height()));
}

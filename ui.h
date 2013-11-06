#ifndef UI_H
#define UI_H

#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QSpinBox;
class QGroupBox;
class QScrollArea;
class QFrame;
class QWebView;
class QProgressBar;

class Ui : public QWidget
{
    Q_OBJECT
public:
    explicit Ui(QWidget *parent = 0);

signals:
    void loadStart();
    void loadComplete();

public slots:
    void addUrl();
    void setUrl();
    void saveFile();
    void loadUrl();
    void printPage();

private slots:

private:
    QLabel *settingLab, *wLab, *hLab, *urlLab, *scaleLab;
    QPushButton *loadBtn, *startBtn;
    QCheckBox *fullEn, *flashEn, *jsEn, *javaEn;
    QSpinBox *wSpin, *hSpin;
    QGroupBox *leftBlock, *rightBlock;
    QLineEdit *urlLine;
    QScrollArea *prevArea;
    QWebView *web;
    QProgressBar *pBar;
    QString url, saveFileName;
    int wSize, hSize;
};

#endif // UI_H

#ifndef OPENCVFACEIDENTIFY_H
#define OPENCVFACEIDENTIFY_H

#include "GuiBaseWidget.h"

class TaskCamera;
class MainWindow : public GuiBaseWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget* CamearWidgetInit();
    void Init();
protected:
    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *e);

signals:
    void UpdateTime();

private:
    TaskCamera* taskCamera;
    int _preClock = -2;
    QString _faceName;
};

#endif // OPENCVFACEIDENTIFY_H

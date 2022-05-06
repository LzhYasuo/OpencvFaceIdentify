#ifndef _ADMIN_WIDGET_H_
#define _ADMIN_WIDGET_H_

#include "QDialog"

class AdminWidget : public QDialog
{
    Q_OBJECT
public:
    AdminWidget(QWidget* parent = nullptr);
    ~AdminWidget();

    QWidget* InitFaceClockWidget();
    QWidget* InitFaceInfoWidget();
private:
    QWidget* Init();
};

#endif //_ADMIN_WIDGET_H_

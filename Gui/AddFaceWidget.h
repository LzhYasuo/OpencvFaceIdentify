#ifndef _ADD_FACE_WIDGET_H_
#define _ADD_FACE_WIDGET_H_

#include "QDialog"

class AddFaceWidget : public QDialog
{
public:
    AddFaceWidget(QWidget* parent = nullptr);
    ~AddFaceWidget();

    void Init();

    QString GetStr() const;

signals:
    void SendStr(QString);
private:
    QString _Str;
};



#endif //_ADD_FACE_WIDGET_H_

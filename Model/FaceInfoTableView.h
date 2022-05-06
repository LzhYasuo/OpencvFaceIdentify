#ifndef FACE_INFO_TABLE_VIEW_H_
#define FACE_INFO_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class QTableView;
class FaceInfoTableView : public QTableView
{
    Q_OBJECT
public:
    FaceInfoTableView(QWidget* parent = nullptr);
    ~FaceInfoTableView();

    void Set_Model_Data(QList<QStringList> data);
    void mousePressEvent(QMouseEvent *event);

signals:
    void TableModityData(int,int,QVariant);
    void ChangePaint(QString,QString,QString);
};


#endif //FACE_INFO_TABLE_VIEW_H_

#ifndef FACE_CLOCK_TABLE_VIEW_H_
#define FACE_CLOCK_TABLE_VIEW_H_

#include <QWidget>
#include <QTableView>

class QTableView;
class FaceClockTableView : public QTableView
{
    Q_OBJECT
public:
    //SettingFourValTableView(QStringList HorList,int TableMaxNum,int NameWidth,int TableWidth,int DefaultHeight,int TableHeight,QWidget* parent = nullptr);
    FaceClockTableView(QWidget* parent = nullptr);
    ~FaceClockTableView();

    void Set_Model_Data(QList<QStringList> data);
//    void Pop_Model_Data();

//    QString Get_ModelData(const int row,const int Col) const;
//    bool Get_RowInfo(QStringList&);
//    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void TableModityData(int,int,QVariant);
    void ChangePaint(QString,QString,QString);
};


#endif //FACE_CLOCK_TABLE_VIEW_H_

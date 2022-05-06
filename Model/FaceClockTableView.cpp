#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QKeyEvent>

#include "FaceClockTableView.h"
#include "FaceClockModelDelegate.h"

FaceClockTableView::FaceClockTableView(QWidget* parent/* = nullptr*/)
    :QTableView(parent)
{
    this->setMouseTracking(true);
//    this->setFixedSize(900,300);
    const QStringList horHeadList = (QStringList() << "Name" << "Id" << "DateTime");
//    horHeadList << "ID";
    FaceClockTableModel* tableModel = new FaceClockTableModel(this);
    tableModel->setObjectName("Model");
    FaceClockModelDelegate* tableDelegate = new FaceClockModelDelegate(this);
    tableDelegate->setObjectName("Delegate");
    this->setModel(tableModel);
    this->setItemDelegate(tableDelegate);

    tableModel->setHorizontalHeaderList(horHeadList);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);


    //显示子网格
    this->setShowGrid(true);
    //取消进度条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置默认高度
    this->verticalHeader()->setDefaultSectionSize(30);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(25);

    this->setColumnWidth(0,200);
    this->setColumnWidth(1,150);
    this->setColumnWidth(2,450);

    //设置行列表头无法点击
    this->setCornerButtonEnabled(false);
    this->horizontalHeader()->setSectionsClickable(false);

    this->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                            "{"
                                            "color:rgb(230,230,230);"
                                            "background-color:rgb(30,30,30);"
                                            "border:1px solid rgb(230,230,230);}");

}


void FaceClockTableView::mousePressEvent(QMouseEvent *event)
{
    FaceClockModelDelegate* tableDelegate = this->findChild<FaceClockModelDelegate*>("Delegate");
    FaceClockTableModel* tableModel = this->findChild<FaceClockTableModel*>("Model");
    int row = indexAt(event->pos()).row();
    if(row >= 0)
    {
        tableDelegate->Set_ClickedRow(row);
    }
    else
    {
        tableDelegate->Set_ClickedRow(-1);
        emit ChangePaint("","","");
    }
    tableModel->RefrushModelData();


    return QTableView::mousePressEvent(event);
}

FaceClockTableView::~FaceClockTableView()
{

}

void FaceClockTableView::Set_Model_Data(QList<QStringList> data)
{
    FaceClockTableModel* tableModel = this->findChild<FaceClockTableModel*>("Model");
    tableModel->PushBackData(data);
}

//bool FaceClockTableView::Get_RowInfo(QStringList& value)
//{
//    FaceInfoModelDelegate* tableDelegate = this->findChild<FaceInfoModelDelegate*>("Delegate");
//    const int ClickedRow = tableDelegate->Get_ClickedRow();
//    if(ClickedRow == -1)
//    {
//        return false;
//    }
//#if 0
//    const QModelIndex nameIndex = tableModel->index(ClickedRow,7);
//    const QModelIndex codeIndex = tableModel->index(ClickedRow,9);
//    const QModelIndex TypeIndex = tableModel->index(ClickedRow,8);
//    //层位
//    const QModelIndex DiskIndex = tableModel->index(ClickedRow,2);
//    const QModelIndex WorkIndex = tableModel->index(ClickedRow,3);
//    const QModelIndex ResultIndex = tableModel->index(ClickedRow,10);
//    const QModelIndex ActionIndex = tableModel->index(ClickedRow,6);
//    const QModelIndex TimeIndex = tableModel->index(ClickedRow,14);

//    const QString nameValue = this->model()->data(nameIndex).toString();
//    const QString codeValue = this->model()->data(codeIndex).toString();
//    const QString typeValue = this->model()->data(TypeIndex).toString();
//    const QString diskValue = this->model()->data(DiskIndex).toString();
//    const QString workValue = this->model()->data(WorkIndex).toString();
//    const QString resultValue = this->model()->data(ResultIndex).toString();
//    const QString actionValue = this->model()->data(ActionIndex).toString();
//    const QString timeValue = this->model()->data(TimeIndex).toString();
//#endif

//    const QString nameValue = Get_ModelData(ClickedRow,7);
//    const QString codeValue = Get_ModelData(ClickedRow,9);
//    const QString typeValue = Get_ModelData(ClickedRow,8);
//    const QString frameValue = Get_ModelData(ClickedRow,1);
//    const QString diskValue = Get_ModelData(ClickedRow,2);
//    const QString workValue = Get_ModelData(ClickedRow,3);
//    const QString resultValue = Get_ModelData(ClickedRow,10);
//    const QString actionValue = Get_ModelData(ClickedRow,6);
//    const QString timeValue = Get_ModelData(ClickedRow,14);

//    if(codeValue.isEmpty() || codeValue == " ")
//        return false;

//    value << nameValue << codeValue << typeValue << frameValue << diskValue << workValue << resultValue << actionValue << timeValue;

//    return true;
//}

//void FaceClockTableView::Set_Model_Data(QList<QStringList> data)
//{
//    FaceInfoTableModel* tableModel = this->findChild<FaceInfoTableModel*>("Model");
//    tableModel->PushBackData(data);
//}

//void FaceClockTableView::Pop_Model_Data()
//{
//    FaceInfoTableModel* tableModel = this->findChild<FaceInfoTableModel*>("Model");
//    tableModel->PopBackData();
//}

//QString FaceClockTableView::Get_ModelData(const int row, const int Col) const
//{
//    FaceInfoTableModel* tableModel = this->findChild<FaceInfoTableModel*>("Model");
//    const QModelIndex index = tableModel->index(row,Col);
//    const QString value = this->model()->data(index).toString();

//    return value;
//}

#if 0
void ClickedRow(int Row);
void FaceClockTableView::ClickedRow(int Row)
{
    const QModelIndex index = this->model()->index(Row,0);
    this->clicked(index);
}

#endif

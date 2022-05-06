#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QKeyEvent>

#include "FaceInfoTableView.h"
#include "FaceInfoModelDelegate.h"

FaceInfoTableView::FaceInfoTableView(QWidget* parent/* = nullptr*/)
    :QTableView(parent)
{
    this->setMouseTracking(true);
//    this->setFixedSize(900,300);
    const QStringList horHeadList = (QStringList() << "ID" << "FrameNo" << "DiskNo" << "WorkNO" << "Line" << "Status" << "Action"
                                     << "Name" << "Type" << "Code" << "Result" << "Vaccum" << "Press" << "Notes" << "TimeStemp");
//    horHeadList << "ID";
    FaceInfoTableModel* tableModel = new FaceInfoTableModel(this);
    tableModel->setObjectName("Model");
    FaceInfoModelDelegate* tableDelegate = new FaceInfoModelDelegate(this);
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

    this->setColumnWidth(0,400);
    this->setColumnWidth(1,400);

    //设置行列表头无法点击
    this->setCornerButtonEnabled(false);
    this->horizontalHeader()->setSectionsClickable(false);

    this->horizontalHeader()->setStyleSheet("QHeaderView::section "
                                            "{"
                                            "color:rgb(230,230,230);"
                                            "background-color:rgb(30,30,30);"
                                            "border:1px solid rgb(230,230,230);}");

}

void FaceInfoTableView::Set_Model_Data(QList<QStringList> data)
{
    FaceInfoTableModel* tableModel = this->findChild<FaceInfoTableModel*>("Model");
    tableModel->PushBackData(data);
}

void FaceInfoTableView::mousePressEvent(QMouseEvent *event)
{
    FaceInfoModelDelegate* tableDelegate = this->findChild<FaceInfoModelDelegate*>("Delegate");
    FaceInfoTableModel* tableModel = this->findChild<FaceInfoTableModel*>("Model");
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

FaceInfoTableView::~FaceInfoTableView()
{

}


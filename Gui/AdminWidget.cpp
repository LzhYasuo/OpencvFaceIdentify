#include "AdminWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateTime>
#include <QStackedWidget>
#include "DateEdit.h"
#include "../Model/FaceInfoTableView.h"
#include "../Model/FaceClockTableView.h"
#include "../Sql/SqlDataBase.h"

AdminWidget::AdminWidget(QWidget *parent)
    :QDialog (parent)
{
    this->setObjectName("AdminWidget");
    this->setStyleSheet("background-color:rgb(30,30,30);");
    this->setFixedWidth(800);
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* mWidget = Init();

    mLayout->addWidget(mWidget);
    this->setLayout(mLayout);
}

AdminWidget::~AdminWidget()
{

}

QWidget *AdminWidget::InitFaceInfoWidget()
{
    const QString labelStyle = "font : 15pt ""楷体"";"
                               "color:rgb(230,230,230); ";
    const QString buttonStyle = "QPushButton"
                                "{"
                                "font : 15pt ""楷体"";"
                                "color:rgb(230,230,230);"
                                "border:1px solid rgb(230,230,230); "
                                "}"
                                "QPushButton:hover"
                                "{"
                                "color:rgb(0,155,155);"
                                "}";
    const QString LineEditStyle = "color:rgb(230,230,230);"
                                  "font : 15pt ""楷体""; ";
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* retrievalWidget = new QWidget();
    QHBoxLayout* retrievalLayout = new QHBoxLayout();
    retrievalLayout->setSpacing(0);
    retrievalLayout->setContentsMargins(0,0,0,0);

    QLabel* lblNameText = new QLabel();
    lblNameText->setText("名字");
    lblNameText->setStyleSheet(labelStyle);
    lblNameText->setFixedHeight(35);

    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setFixedHeight(35);
    nameEdit->setStyleSheet(LineEditStyle);

    QLabel* lblIdText = new QLabel();
    lblIdText->setText("ID");
    lblIdText->setStyleSheet(labelStyle);
    lblIdText->setFixedHeight(35);

    QLineEdit* idEdit = new QLineEdit();
    idEdit->setFixedHeight(35);
    idEdit->setStyleSheet(LineEditStyle);

    QPushButton* btnRetrieval = new QPushButton();
    btnRetrieval->setText("筛选");
    btnRetrieval->setFixedSize(100,35);
    btnRetrieval->setStyleSheet(buttonStyle);

    QPushButton* btnClear = new QPushButton();
    btnClear->setText("还原");
    btnClear->setFixedSize(100,35);
    btnClear->setStyleSheet(buttonStyle);

    retrievalLayout->addWidget(lblNameText);
    retrievalLayout->addWidget(nameEdit);
    retrievalLayout->addWidget(lblIdText);
    retrievalLayout->addWidget(idEdit);
    retrievalLayout->addWidget(btnRetrieval);
    retrievalLayout->addWidget(btnClear);
    retrievalWidget->setLayout(retrievalLayout);

    FaceInfoTableView* view = new FaceInfoTableView();
    QList<QStringList> list;
    SqlDataBase::Get()->GetFaceInfoAllData(list);
    view->Set_Model_Data(list);


    mLayout->addWidget(retrievalWidget);
    mLayout->addWidget(view);
    mWidget->setLayout(mLayout);

    this->connect(btnRetrieval,&QPushButton::clicked,this,[=]()
    {
        QString nameStr = nameEdit->text();
        QString idStr = idEdit->text();

        QList<QStringList> nameList;
        SqlDataBase::Get()->GetInfoData(nameList,nameStr,idStr);

        view->Set_Model_Data(nameList);
    });

    this->connect(btnClear,&QPushButton::clicked,this,[=]()
    {
        QList<QStringList> nameList;
        SqlDataBase::Get()->GetFaceInfoAllData(nameList);

        view->Set_Model_Data(nameList);
    });

    return mWidget;
}

QWidget* AdminWidget::InitFaceClockWidget()
{
    const QString labelStyle = "font : 15pt ""楷体"";"
                               "color:rgb(230,230,230); ";
    const QString buttonStyle = "QPushButton"
                                "{"
                                "font : 15pt ""楷体"";"
                                "color:rgb(230,230,230);"
                                "border:1px solid rgb(230,230,230); "
                                "}"
                                "QPushButton:hover"
                                "{"
                                "color:rgb(0,155,155);"
                                "}";
    const QString LineEditStyle = "color:rgb(230,230,230);"
                                  "font : 15pt ""楷体""; ";

    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QWidget* retrievalWidget = new QWidget();
    QHBoxLayout* retrievalLayout = new QHBoxLayout();
    retrievalLayout->setSpacing(0);
    retrievalLayout->setContentsMargins(0,0,0,0);

    QLabel* lblNameText = new QLabel();
    lblNameText->setText("名字");
    lblNameText->setFixedHeight(35);
    lblNameText->setStyleSheet(labelStyle);

    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setStyleSheet(LineEditStyle);
    nameEdit->setFixedHeight(35);

    QLabel* lblIdText = new QLabel();
    lblIdText->setText("ID");
    lblIdText->setStyleSheet(labelStyle);
    lblIdText->setFixedHeight(35);

    QLineEdit* idEdit = new QLineEdit();
    idEdit->setStyleSheet(LineEditStyle);
    idEdit->setFixedHeight(35);

    QLabel* lblTimeText = new QLabel();
    lblTimeText->setText("时间");
    lblTimeText->setStyleSheet(labelStyle);
    lblTimeText->setFixedHeight(35);

    DataEdit* Edit1 = new DataEdit;
    Edit1->setFixedHeight(35);

    DataEdit* Edit2 = new DataEdit;
    Edit2->setFixedHeight(35);

    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0,0,0,0);

    QPushButton* btnNIRetrieval = new QPushButton();
    btnNIRetrieval->setText("仅名字ID筛选");
    btnNIRetrieval->setFixedSize(150,35);
    btnNIRetrieval->setStyleSheet(buttonStyle);

    QPushButton* btnTimeRetrieval = new QPushButton();
    btnTimeRetrieval->setText("仅时间筛选");
    btnTimeRetrieval->setFixedSize(150,35);
    btnTimeRetrieval->setStyleSheet(buttonStyle);

    QPushButton* btnRetrieval = new QPushButton();
    btnRetrieval->setText("全部筛选");
    btnRetrieval->setFixedSize(150,35);
    btnRetrieval->setStyleSheet(buttonStyle);

    QPushButton* btnClear = new QPushButton();
    btnClear->setText("清空");
    btnClear->setFixedSize(150,35);
    btnClear->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(btnRetrieval);
    buttonLayout->addWidget(btnNIRetrieval);
    buttonLayout->addWidget(btnTimeRetrieval);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addStretch();
    buttonWidget->setLayout(buttonLayout);

    retrievalLayout->addWidget(lblNameText);
    retrievalLayout->addWidget(nameEdit);
    retrievalLayout->addWidget(lblIdText);
    retrievalLayout->addWidget(idEdit);
    retrievalLayout->addWidget(lblTimeText);
    retrievalLayout->addWidget(Edit1);
    retrievalLayout->addWidget(Edit2);
    retrievalWidget->setLayout(retrievalLayout);

    FaceClockTableView* view = new FaceClockTableView();
    QList<QStringList> list;
    SqlDataBase::Get()->GetFaceClockAllData(list);
    view->Set_Model_Data(list);

    mLayout->addWidget(retrievalWidget);
    mLayout->addWidget(buttonWidget);
    mLayout->addWidget(view);
    mWidget->setLayout(mLayout);

    this->connect(btnRetrieval,&QPushButton::clicked,this,[=]()
    {
        QString nameStr = nameEdit->text();
        QString idStr = idEdit->text();
        QString dateStr1 = Edit1->Get_Data().toString("yyyy-MM-dd HH:mm:ss");
        QString dateStr2 = Edit2->Get_Data().toString("yyyy-MM-dd HH:mm:ss");

        QList<QStringList> nameList;
        SqlDataBase::Get()->GetClockData(nameList,nameStr,idStr,dateStr1,dateStr2);

        view->Set_Model_Data(nameList);
    });
    this->connect(btnNIRetrieval,&QPushButton::clicked,this,[=]()
    {
        QString nameStr = nameEdit->text();
        QString idStr = idEdit->text();

        QList<QStringList> nameList;
        SqlDataBase::Get()->GetClockData(nameList,nameStr,idStr,"","");

        view->Set_Model_Data(nameList);
    });
    this->connect(btnTimeRetrieval,&QPushButton::clicked,this,[=]()
    {
        QString dateStr1 = Edit1->Get_Data().toString("yyyy-MM-dd HH:mm:ss");
        QString dateStr2 = Edit2->Get_Data().toString("yyyy-MM-dd HH:mm:ss");

        QList<QStringList> nameList;
        SqlDataBase::Get()->GetClockData(nameList,"","",dateStr1,dateStr2);

        view->Set_Model_Data(nameList);
    });
    this->connect(btnClear,&QPushButton::clicked,this,[=](){

        QList<QStringList> nameList;
        SqlDataBase::Get()->GetFaceClockAllData(nameList);

        view->Set_Model_Data(nameList);
    });

    return mWidget;
}

QWidget* AdminWidget::Init()
{
    const QString buttonStyle = "QPushButton"
                                "{"
                                "background-color:rgb(30,30,30);"
                                "color:rgb(230,230,230);"
                                "border:1px solid rgb(230,230,230);"
                                "}"
                                "QPushButton:hover"
                                "{"
                                "color:rgb(0,155,150);"
                                "}";
    QWidget* mWidget = new QWidget();
    QVBoxLayout* mLayout = new QVBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0,0,0,0);
    QPushButton* btnInfo = new QPushButton("人员信息");
    btnInfo->setStyleSheet(buttonStyle);
    btnInfo->setFixedSize(100,25);
    QPushButton* btnClock = new QPushButton("打卡记录");
    btnClock->setStyleSheet(buttonStyle);
    btnClock->setFixedSize(100,25);
    buttonLayout->addWidget(btnInfo);
    buttonLayout->addWidget(btnClock);
    buttonLayout->addStretch();

    QWidget* switchWidget = new QWidget();
    QHBoxLayout* switchLayout = new QHBoxLayout();
    switchLayout->setSpacing(0);
    switchLayout->setContentsMargins(0,0,0,0);

    QStackedWidget* mSWidget = new QStackedWidget();
    QWidget* FaceInfoWidget = InitFaceInfoWidget();
    QWidget* FaceClockWidget = InitFaceClockWidget();

    mSWidget->addWidget(FaceInfoWidget);
    mSWidget->addWidget(FaceClockWidget);

    switchLayout->addWidget(mSWidget);
    switchWidget->setLayout(switchLayout);

    mLayout->addLayout(buttonLayout);
    mLayout->addWidget(switchWidget);
    mWidget->setLayout(mLayout);

    this->connect(btnInfo,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(0);
    });
    this->connect(btnClock,&QPushButton::clicked,this,[=](){
        mSWidget->setCurrentIndex(1);
    });

    return mWidget;
}

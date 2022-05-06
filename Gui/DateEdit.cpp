#include "DateEdit.h"
#include <QTextCharFormat>
#include <QToolButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QCalendarWidget>
#include <QDebug>

DataEdit::DataEdit(QWidget *parent)
    :QWidget (parent)
{
    QHBoxLayout* mLayout = new QHBoxLayout();
    mLayout->setSpacing(0);
    mLayout->setContentsMargins(0,0,0,0);

    QString style_main_color = "rgb(230,230,230)";
    QDateTimeEdit* de = new QDateTimeEdit();
    de->setFixedHeight(35);
    de->setObjectName("DateEdit");
    de->setCalendarPopup(true); //设置日历弹出
    //border-radius: 6px;
    de->setStyleSheet(QString("QDateTimeEdit{color:rgb(230,230,230);"
                              "border: 1px solid %1;padding:3px 0px 3px 6px;selection-background-color:%1;}"
                             "QDateTimeEdit::drop-down{border:none;}"
                             "QDateTimeEdit::down-arrow{image: url(:/Icon/indicator_down.png);border: none;}").arg(style_main_color));

    QTextCharFormat format;//字体风格：黑色
    format.setForeground(QColor(Qt::black));
    QCalendarWidget * dateEditCalendarWidget = de->calendarWidget();
    dateEditCalendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
    dateEditCalendarWidget->setWeekdayTextFormat(Qt::Sunday, format);
    dateEditCalendarWidget->setFixedSize(300,250);
    dateEditCalendarWidget->findChildren<QWidget*>().value(0)->setCursor(Qt::PointingHandCursor);
    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setAlignment(Qt::AlignCenter);
    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setButtonSymbols(QSpinBox::NoButtons);
    QList<QToolButton * > toolbtn_list = de->calendarWidget()->findChildren<QToolButton*>();
    for (int var = 0; var < toolbtn_list.size(); ++var)
    {
        toolbtn_list.value(var)->setCursor(Qt::PointingHandCursor);
    }
//    QSize s = QSize(32,32);
    QToolButton * toolbtn  = de->calendarWidget()->findChild<QToolButton * >("qt_calendar_prevmonth");
    toolbtn->setIcon(QPixmap(":/Icon/indicator_left.png"));
//    toolbtn->setIconSize(s);
    toolbtn = de->calendarWidget()->findChild<QToolButton * >("qt_calendar_nextmonth");
    toolbtn->setIcon(QPixmap(":/Icon/indicator_right.png"));
//    toolbtn->setIconSize(s);

    de->calendarWidget()->setStyleSheet(QString("color:rgb(230,230,230);"
                                                "QCalendarWidget{background-color:#FFFFFF;border: 1px solid %1;}"
                                               "QCalendarWidget QAbstractItemView:enabled{color:#000000;"
                                               "background-color:#ffffff;"
                                               "selection-color: white;"
                                               "selection-background-color:%1;}"
                                               "QCalendarWidget QSpinBox#qt_calendar_yearedit{background:#ffffff;height:34px;width:125px;selection-background-color:%1;}"
                                               "QCalendarWidget QToolButton{background-color:#FFFFFF;height:34px;width:125px;color:rgb(230,230,230);}"
                                               "QCalendarWidget QToolButton:hover{border: 1px solid %1;}"
                                               "QCalendarWidget QToolButton::menu-indicator#qt_calendar_monthbutton{subcontrol-position: right center;subcontrol-origin: padding;}"
                                               "QCalendarWidget QToolButton QMenu{background-color:rgb(230,230,230);width:125px;border:1px solid %1;}"
                                               "QCalendarWidget QToolButton QMenu::item:selected{color:rgb(230,230,230);background:%1;}").arg(style_main_color));
    de->setDateTime(QDateTime::currentDateTime());
    de->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    mLayout->addWidget(de);
    this->setLayout(mLayout);
}

DataEdit::~DataEdit()
{

}

QDateTime DataEdit::Get_Data() const
{
    QDateTimeEdit* de = this->findChild<QDateTimeEdit*>("DateEdit");
    return de->dateTime();
}

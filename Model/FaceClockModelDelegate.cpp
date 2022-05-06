#include "FaceClockModelDelegate.h"
#include <QPainter>
#include <QDebug>

FaceClockModelItem::FaceClockModelItem()
{

}

FaceClockModelItem::~FaceClockModelItem()
{

}

FaceClockTableModel::FaceClockTableModel(QObject* parent)
    :QAbstractTableModel (parent)
{

}

FaceClockTableModel::~FaceClockTableModel()
{

}

#if 0
Qt::ItemFlags FaceClockTableModel::flags(const QModelIndex &index) const
{
    if(index.column() != 0)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index);
}
#endif

int FaceClockTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List.size();
}
int FaceClockTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 3;
}
QVariant FaceClockTableModel::data(const QModelIndex &index, int role) const
{
    if(Ary_row_List.size() < 1 || !index.isValid())
        return QVariant();
    if  (role == Qt::TextAlignmentRole)
         {
             return  int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(index.column() == 0)
        {
            return Ary_row_List.at(index.row()).GetId();
        }
        else if(index.column() == 1)
        {
            return Ary_row_List.at(index.row()).GetName();
        }
        else if(index.column() == 2)
        {
            return Ary_row_List.at(index.row()).GetDateTime();
        }
    }
    return QVariant();
}
QVariant FaceClockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(horizontal_header_list.size() > section)
                return horizontal_header_list[section];
            else
                return QVariant();
        }
        if(orientation == Qt::Vertical)
        {
            if(vertical_header_list.size() > section)
                return vertical_header_list[section];
            else
                return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void FaceClockTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void FaceClockTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void FaceClockTableModel::RefrushModel(FaceClockModelItem item)
{
    const int count = Ary_row_List.size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List.push_back(item);
    endInsertRows();
}

bool FaceClockTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value);
    if(Ary_row_List.size() < 1 || !index.isValid())
        return false;
    if  (role == Qt::TextAlignmentRole)
         {
             return int (Qt::AlignHCenter | Qt::AlignVCenter);
         }
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return true;
    }
    return false;
}

void FaceClockTableModel::PushBackData(QList<QStringList> data)
{
    Ary_row_List.clear();
    if(data.size() <= 0)
        return;
    if(data.at(0).size() < 3)
    {
        return;
    }
    for(int i = 0; i < data.size(); i++)
    {
        FaceClockModelItem Item;
        Item.SetId(data.at(i).at(0).isEmpty() ? "" : data.at(i).at(0));
        Item.SetName(data.at(i).at(1).isEmpty() ? "" : data.at(i).at(1));
        Item.SetDateTime(data.at(i).at(2).isEmpty() ? "" : data.at(i).at(2));
        Ary_row_List.push_back(Item);
    }

    RefrushModelData();
}

void FaceClockTableModel::PopBackData()
{
    for(int i = 0; i < Ary_row_List.size(); i++)
    {
        Ary_row_List.removeAt(0);
    }
     Ary_row_List.clear();
     RefrushModelData();
}

void FaceClockTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

FaceClockModelDelegate::FaceClockModelDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

FaceClockModelDelegate::~FaceClockModelDelegate()
{

}

void FaceClockModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
#if 0
    if(index.column() == 0 || index.column() == 1 || index.column() == 2)
    {
        painter->setPen(QPen(QColor(230,230,230)));
        if(index.row() == ClickedRow)
        {
            painter->setBrush(QColor(230,230,230));
            painter->setPen(QPen(QColor(30,30,30)));
            painter->drawRect(option.rect);
        }
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
#endif
        if(index.column() == 0 || index.column() == 1||  index.column() == 2 || index.column() == 3 || index.column() == 4
            || index.column() == 5 || index.column() == 6 || index.column() == 7 || index.column() == 8 || index.column() == 9 || index.column() == 10 || index.column() == 11 ||index.column() == 12)
        {
            painter->setPen(QPen(QColor(230,230,230)));
            QString mos = index.model()->data(index,Qt::DisplayRole).toString();
            QTextOption o;
            o.setAlignment(Qt::AlignCenter);
            painter->drawText(option.rect,mos,o);
        }
        else
        {
            QItemDelegate::paint(painter,option,index);
        }
}

#include "FaceInfoModelDelegate.h"
#include <QPainter>
#include <QDebug>

FaceInfoModelItem::FaceInfoModelItem()
{

}

FaceInfoModelItem::~FaceInfoModelItem()
{

}

FaceInfoTableModel::FaceInfoTableModel(QObject* parent)
    :QAbstractTableModel (parent)
{

}

FaceInfoTableModel::~FaceInfoTableModel()
{

}

#if 0
Qt::ItemFlags FaceInfoTableModel::flags(const QModelIndex &index) const
{
    if(index.column() != 0)
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index);
}
#endif

int FaceInfoTableModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return Ary_row_List.size();
}
int FaceInfoTableModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 2;
}
QVariant FaceInfoTableModel::data(const QModelIndex &index, int role) const
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
    }
    return QVariant();
}
QVariant FaceInfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void FaceInfoTableModel::setHorizontalHeaderList(QStringList hHeadList)
{
    horizontal_header_list = hHeadList;
}

void FaceInfoTableModel::setVerticalHeaderList(QStringList VHeadList)
{
    vertical_header_list = VHeadList;
}

void FaceInfoTableModel::RefrushModel(FaceInfoModelItem item)
{
    const int count = Ary_row_List.size();
    beginInsertRows(QModelIndex(), count, count);
    Ary_row_List.push_back(item);
    endInsertRows();
}

bool FaceInfoTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

void FaceInfoTableModel::PushBackData(QList<QStringList> data)
{
    Ary_row_List.clear();
    if(data.size() <= 0)
        return;
    if(data.at(0).size() < 2)
    {
        return;
    }
    for(int i = 0; i < data.size(); i++)
    {
        FaceInfoModelItem Item;
        Item.SetId(data.at(i).at(0).isEmpty() ? "" : data.at(i).at(0));
        Item.SetName(data.at(i).at(1).isEmpty() ? "" : data.at(i).at(1));
        Ary_row_List.push_back(Item);
    }

    RefrushModelData();
}

void FaceInfoTableModel::PopBackData()
{
    for(int i = 0; i < Ary_row_List.size(); i++)
    {
        Ary_row_List.removeAt(0);
    }
     Ary_row_List.clear();
     RefrushModelData();
}

void FaceInfoTableModel::RefrushModelData()
{
    this->beginResetModel();

    this->endResetModel();
}

FaceInfoModelDelegate::FaceInfoModelDelegate(QObject *parent)
    :QItemDelegate (parent)
{

}

FaceInfoModelDelegate::~FaceInfoModelDelegate()
{

}

void FaceInfoModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0 || index.column() == 1)
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
#if 0
    else if(index.column() == 1)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 2)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 3)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
    else if(index.column() == 4)
    {
        QString mos = index.model()->data(index,Qt::DisplayRole).toString();
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect,mos,o);
    }
#endif
    else
    {
        QItemDelegate::paint(painter,option,index);
    }
}

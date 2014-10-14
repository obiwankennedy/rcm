#include "leveldelegateitem.h"
#include <QPainter>


LevelDelegateItem::LevelDelegateItem()
{
    m_data << tr("Beginner")<< tr("Middle")<<tr("Veteran");
}

QWidget *	LevelDelegateItem::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QComboBox* box = new QComboBox(parent);
    return box;
}
void	LevelDelegateItem::setEditorData ( QWidget * editor, const QModelIndex & index ) const
{
    QComboBox* box = qobject_cast<QComboBox*>(editor);
    if(NULL!=box)
    {
        box->addItems(m_data);
        box->setCurrentIndex(index.data().toInt());
    }
}
void	LevelDelegateItem::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const
{
    QComboBox* box = qobject_cast<QComboBox*>(editor);
    if(NULL!=box)
    {

        model->setData(index,box->currentIndex());
    }
}
QSize	LevelDelegateItem::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
   return  QStyledItemDelegate::sizeHint(option,index);
}
void	LevelDelegateItem::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}
void LevelDelegateItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if( option.state & QStyle::State_Selected )
    {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    painter->drawText(option.rect,m_data.at(index.data().toInt()));
}

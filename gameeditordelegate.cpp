#include "gameeditordelegate.h"
#include <QComboBox>
#include <QModelIndex>
#include <QPainter>
#include <QApplication>

GameEditorDelegate::GameEditorDelegate(QMap<QString,Game*>& l)
    : m_list(l)
{
}

QWidget* GameEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index	) const
{
    QComboBox *cb = new QComboBox(parent);
     int row = index.row();


     foreach(Game* tmp,m_list.values())
     {
        cb->addItem(tmp->getTitle(),tmp->getUuid());
     }

     return cb;
}
void GameEditorDelegate::setEditorData(QWidget *editor	, const QModelIndex &index)
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor))
    {
         QString currentText = index.data(Qt::EditRole).toString();
         int cbIndex = cb->findData(currentText);

         if(cbIndex >= 0)
             cb->setCurrentIndex(cbIndex);
    }
    else
    {
         QStyledItemDelegate::setEditorData(editor, index);
    }
}
void GameEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}
void GameEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor))
           model->setData(index,cb->itemData(cb->currentIndex()), Qt::EditRole);
       else
           QStyledItemDelegate::setModelData(editor, model, index);
}


void GameEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        if(QStyle::State_Editing == option.state)
        {
            QStyledItemDelegate::paint(painter,option,index);
        }
        else
        {
            QString currentText = index.data(Qt::EditRole).toString();
            Game* tmp = m_list[currentText];
            QString value;
            if(NULL!=tmp)
            {
                value = tmp->getTitle();
            }


           QStyle *style=qApp->style();

           QRect checkBoxRect=style->subElementRect(QStyle::SE_ItemViewItemText, &option);



           //style->drawPrimitive(QStyle::PE_PanelItemViewItem, &modifiedOption, painter);
           style->drawItemText(painter,checkBoxRect,Qt::AlignCenter ,option.palette,true,value);





        }
    }
}

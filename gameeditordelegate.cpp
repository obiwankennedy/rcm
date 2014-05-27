/***************************************************************************
* Copyright (C) 2014 by Renaud Guezennec                                   *
* http://renaudguezennec.homelinux.org/accueil,3.html                      *
*                                                                          *
*  This file is part of rcm                                                *
*                                                                          *
* Rcm is free software; you can redistribute it and/or modify              *
* it under the terms of the GNU General Public License as published by     *
* the Free Software Foundation; either version 2 of the License, or        *
* (at your option) any later version.                                      *
*                                                                          *
* This program is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
* GNU General Public License for more details.                             *
*                                                                          *
* You should have received a copy of the GNU General Public License        *
* along with this program; if not, write to the                            *
* Free Software Foundation, Inc.,                                          *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
***************************************************************************/
#include "gameeditordelegate.h"
#include <QComboBox>
#include <QModelIndex>
#include <QPainter>
#include <QApplication>
#include <QDebug>

GameEditorDelegate::GameEditorDelegate(QMap<QString,Game*>& l)
    : m_list(l)
{
}

QWidget* GameEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index	) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *cb = new QComboBox(parent);


     foreach(Game* tmp,m_list.values())
     {
        cb->addItem(tmp->getTitle(),tmp->getUuid());
     }

     return cb;
}
void GameEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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
    {
           model->setData(index,cb->itemData(cb->currentIndex()), Qt::EditRole);
    }
    else
    {
           QStyledItemDelegate::setModelData(editor, model, index);
    }
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

           style->drawItemText(painter,checkBoxRect,Qt::AlignCenter ,option.palette,true,value);





        }
    }
}
QSize GameEditorDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QSize a = QStyledItemDelegate::sizeHint(option,index);

    QString currentText = index.data(Qt::EditRole).toString();

    Game* tmp = m_list[currentText];
    QString value;
    if(NULL!=tmp)
    {
        value = tmp->getTitle();
    }
    a.setWidth(option.fontMetrics.width(value));

    return a;
}

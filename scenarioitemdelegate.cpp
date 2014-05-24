/***************************************************************************
* Copyright (C) 2014 by Renaud Guezennec *
* http://renaudguezennec.homelinux.org/accueil,3.html *
* *
* This file is part of rcm *
* *
* Rcm is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 2 of the License, or *
* (at your option) any later version. *
* *
* This program is distributed in the hope that it will be useful, *
* but WITHOUT ANY WARRANTY; without even the implied warranty of *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
* GNU General Public License for more details. *
* *
* You should have received a copy of the GNU General Public License *
* along with this program; if not, write to the *
* Free Software Foundation, Inc., *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. *
***************************************************************************/
#include <QApplication>
#include <QPainter>

#include "scenarioitemdelegate.h"
#include <QDebug>

ScenarioItemDelegate::ScenarioItemDelegate(QMap<QString,Game*>& l,Scenario::STATE m )
    : m_list(l),m_state(m)
{
}
QSize ScenarioItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
 {
    QSize a = QStyledItemDelegate::sizeHint(option,index);

   return QSize(a.width(),a.height()*3);
 }
void ScenarioItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario tmp = var.value<Scenario>();





        QStyle *style=qApp->style();

        QRect checkBoxRect=style->subElementRect(QStyle::SE_ItemViewItemText, &option);

        if( option.state & QStyle::State_Selected )
        {
        //    QStyledItemDelegate::paint(painter, option, index);
            painter->fillRect(option.rect, option.palette.highlight());
        }

        //style->drawPrimitive(QStyle::PE_PanelItemViewItem, &modifiedOption, painter);
        style->drawPrimitive(QStyle::PE_PanelItemViewRow,&option,painter);
        style->drawItemText(painter,checkBoxRect,Qt::AlignHCenter | Qt::AlignTop ,option.palette,true,tmp.getTitle());
        style->drawItemText(painter,checkBoxRect,Qt::AlignRight | Qt::AlignTop ,option.palette,true,tr("Players: %1/%2").arg(tmp.getCurrentPlayers()).arg(tmp.getMaximumPlayers()));

        if(Scenario::AVAILABLE == m_state)
        {
            QString str=minutesToHours(tmp.getDuration(),tr("Duration"));
            style->drawItemText(painter,checkBoxRect,Qt::AlignRight | Qt::AlignBottom ,option.palette,true,str);
        }
        else if(Scenario::RUNNING == m_state)
        {
            QString str=minutesToHours(tmp.getRestingTime(),tr("End in"));
            style->drawItemText(painter,checkBoxRect,Qt::AlignRight | Qt::AlignBottom ,option.palette,true,str);

        }


        style->drawItemText(painter,checkBoxRect,Qt::AlignCenter,option.palette,true,m_list[tmp.getGameId()]->getTitle());

    }
}
QString ScenarioItemDelegate::minutesToHours(int minutes,QString word) const
{
    int hours = minutes/60;
    minutes -= 60*hours;


    return QString(tr("%3: %1:%2")).arg(hours,2,10,QChar('0')).arg(minutes,2,10,QChar('0')).arg(word);
}

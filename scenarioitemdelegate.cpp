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
#include "scenariomodel.h"
#include <QDebug>

#define FACTOR_SIZE 3

ScenarioItemDelegate::ScenarioItemDelegate(QMap<QString,Game*>& l,QMap<QString,GameMaster*>& masterlist,Scenario::STATE m, bool isPrivate )
    : m_list(l),m_masterlist(masterlist),m_state(m),m_private(isPrivate)
{
}
QSize ScenarioItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QSize a = QStyledItemDelegate::sizeHint(option,index);

    return QSize(a.width(),a.height()*FACTOR_SIZE);
}
void ScenarioItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        QVariant var = index.data(Qt::UserRole);
        Scenario tmp = var.value<Scenario>();





        QStyle *style=qApp->style();

        QRect itemRect=option.rect;//style->subElementRect(QStyle::SE_ItemViewItemText, &option);

        painter->save();
        painter->drawRect(itemRect);
        itemRect.adjust(1,1,-1,-1);
        painter->restore();

        style->drawPrimitive(QStyle::PE_PanelItemViewRow,&option,painter);



        if( option.state & QStyle::State_Selected )
        {

            painter->fillRect(itemRect, option.palette.highlight());
        }
        else if(Scenario::AVAILABLE == m_state)
        {
            QVariant var = index.data(ScenarioModel::ColorRole);
            QColor statusColor= var.value<QColor>();

            painter->fillRect(itemRect, statusColor);
        }









            if(Scenario::AVAILABLE == m_state)
            {



                QString str=minutesToHours(tmp.getDuration(),tr("Duration"));
                style->drawItemText(painter,itemRect,Qt::AlignRight | Qt::AlignBottom ,option.palette,true,str);



            }
            else if(Scenario::RUNNING == m_state)
            {
                QString str=minutesToHours(tmp.getRestingTime(),tr("End in"));
                style->drawItemText(painter,itemRect,Qt::AlignRight | Qt::AlignBottom ,option.palette,true,str);

                QStyleOptionProgressBarV2 progressBarStyleOption;
                QRect progressBarRect;

                progressBarRect.setY(2*option.rect.height()/3);
                progressBarRect.setX(option.rect.width()/4);
                progressBarRect.setHeight(option.rect.height()/3);
                progressBarRect.setWidth(option.rect.width()/2);


                progressBarStyleOption.rect = progressBarRect;


                const int progress = 100*tmp.getRestingTime()/tmp.getDuration();

                progressBarStyleOption.minimum = 0;
                progressBarStyleOption.state = option.state;
                progressBarStyleOption.maximum = 100;
                progressBarStyleOption.textAlignment = Qt::AlignHCenter | Qt::AlignBottom;
                progressBarStyleOption.progress = 100-progress ;
                progressBarStyleOption.text = QString( "%1%" ).arg( progressBarStyleOption.progress  );
                progressBarStyleOption.textVisible = true;

                style->drawControl( QStyle::CE_ProgressBar, &progressBarStyleOption, painter );




            }

        GameMaster* myGameMaster = m_masterlist[tmp.getGameMasterId()];
        if(!m_private)
        {
            QString gmStr = tr("GM:%1, phone:%2");
            style->drawItemText(painter,itemRect,Qt::AlignBottom | Qt::AlignLeft,option.palette,true,gmStr.arg(myGameMaster->getNickName()).arg(myGameMaster->getPhoneNumber()));
        }
        else
        {
            QString gmStr = tr("GM:%1");
            style->drawItemText(painter,itemRect,Qt::AlignBottom | Qt::AlignLeft,option.palette,true,gmStr.arg(myGameMaster->getNickName()));
        }


        //
        style->drawItemText(painter,itemRect,Qt::AlignHCenter | Qt::AlignTop ,option.palette,true,tmp.getTitle());
        style->drawItemText(painter,itemRect,Qt::AlignRight | Qt::AlignTop ,option.palette,true,tr("Players: %1/%2").arg(tmp.getCurrentPlayers()).arg(tmp.getMaximumPlayers()));


        style->drawItemText(painter,itemRect,Qt::AlignCenter,option.palette,true,m_list[tmp.getGameId()]->getTitle());


    }
}
QString ScenarioItemDelegate::minutesToHours(int minutes,QString word) const
{
    int hours = minutes/60;
    minutes -= 60*hours;


    return QString(tr("%3: %1:%2")).arg(hours,2,10,QChar('0')).arg(minutes,2,10,QChar('0')).arg(word);
}

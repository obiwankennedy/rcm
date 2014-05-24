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
#ifndef SCENARIOITEMDELEGATE_H
#define SCENARIOITEMDELEGATE_H

#include <QStyledItemDelegate>
#include "game.h"
#include "scenario.h"

class ScenarioItemDelegate : public QStyledItemDelegate
{
public:
    ScenarioItemDelegate(QMap<QString,Game*>& l,Scenario::STATE m);

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


    QString minutesToHours(int minutes,QString word) const;
private:
    QMap<QString,Game*>& m_list;
    Scenario::STATE m_state;

};

#endif // SCENARIOITEMDELEGATE_H

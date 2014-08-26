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
#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include <QQuickView>
#include "scenarioitemdelegate.h"
#include "scenariomodel.h"
#include "gameimageprovider.h"

class CustomerView : public QQuickView
{
    Q_OBJECT
    
public:
    explicit CustomerView(GameImageProvider* gameImgProvider,ScenarioModel* model, QWindow *parent = 0);
    ~CustomerView();

public slots:
    void setSelectionIndex(QModelIndex index);
    
private:
    ScenarioItemDelegate* m_scenarioDelegate;
    ScenarioModel* m_model;
};

#endif // CUSTOMERVIEW_H

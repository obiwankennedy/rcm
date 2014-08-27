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
#include "customerview.h"
#include <QQmlContext>
#include <QDebug>
#include <QQuickItem>
#include <QQuickView>

CustomerView::CustomerView(GameImageProvider* gameImgProvider,ScenarioModel* model,QWindow* parent) :
    QQuickView(parent),
    m_model(model)
{
    //ui->setupUi(this);
    //m_scenarioDelegate = new ScenarioItemDelegate(map,mastermap,Scenario::AVAILABLE,true);
    //ui->listView->setItemDelegate(m_scenarioDelegate);
    //ui->listView->setModel(m_model);
    rootContext()->setContextProperty("_myModel",m_model);
    QQmlEngine* myEngine =engine();
    myEngine->addImageProvider(QString("game"), gameImgProvider);
    setSource(QUrl("qrc:/listView.qml"));

    setResizeMode(QQuickView::SizeRootObjectToView);


}

CustomerView::~CustomerView()
{

}


void CustomerView::setSelectionIndex(const QModelIndex& index)
{

    QQuickItem* object = rootObject();
    QObject* listview = object->findChild<QObject*>("listView");
    if(NULL!=listview)
    {
        qDebug() << "S" << index.row();

        listview->setProperty("currentIndex ",index.row());
    }

/// @todo send selection to QML World
}

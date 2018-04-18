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
#include <QLabel>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QScrollArea>

#include "scenarioitemdelegate.h"
#include "scenariomodel.h"
#include "gameimageprovider.h"
#include "ui_mainwindow.h"

class CustomerView : public QObject
{
    Q_OBJECT
    
public:
    explicit CustomerView(GameImageProvider* gameImgProvider,ScenarioModel* model, QWindow *parent = 0);
    ~CustomerView();

    bool isVisible() const;
    void setVisible(bool visible);

    void setLabel(Ui::MainWindow* parent);
    Qt::WindowState windowState();
public slots:
    void setSelectionIndex(const QModelIndex& index);
    void showNormal();
    void showFullScreen();
    void refreshView();
    
protected:
    void resizeLabel();
    bool eventFilter(QObject *, QEvent *);

private:
    ScenarioItemDelegate* m_scenarioDelegate = nullptr;
    ScenarioModel* m_model;
    QLabel* m_label;
    QQmlApplicationEngine* m_engine;
    QQuickWindow* m_window;
    QTimer* m_timer;
    qreal m_ratioImage;
    qreal m_ratioImageBis;
    QScrollArea* m_widget;
    Ui::MainWindow* m_ui;
};

#endif // CUSTOMERVIEW_H

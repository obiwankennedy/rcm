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
#include <QDebug>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickView>
#include <QTimer>

CustomerView::CustomerView(GameImageProvider* gameImgProvider, QAbstractItemModel* model, QWindow* parent)
    : QObject(parent), m_model(model)
{
    m_engine= new QQmlApplicationEngine();

    m_timer= new QTimer();
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(refreshView()));

    m_engine->rootContext()->setContextProperty("_myModel", m_model);
    m_engine->addImageProvider(QString("game"), gameImgProvider);

    m_engine->load(QUrl("qrc:/qml/listView.qml"));

    // setResizeMode(QQuickView::SizeRootObjectToView);
    QObject* root= m_engine->rootObjects().first();
    if(nullptr != root)
    {
        m_window= qobject_cast<QQuickWindow*>(root);
        m_window->setVisible(false);
    }
}

CustomerView::~CustomerView() {}

void CustomerView::setLabel(Ui::MainWindow* parent)
{
    m_ui= parent;
    m_label= new QLabel();
    m_label->setLineWidth(0);
    m_label->setFrameStyle(QFrame::NoFrame);
    m_ui->m_scrollAreaVisual->setWidget(m_label);
    m_ui->m_scrollAreaVisual->setAlignment(Qt::AlignCenter);
    m_ui->m_scrollAreaVisual->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->m_scrollAreaVisual->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_label->setScaledContents(true);
    m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    connect(m_ui->m_startAnimation, &QPushButton::toggled, [=](bool b) { m_window->setProperty("autoAnimation", b); });

    connect(
        m_ui->m_showMsg, &QPushButton::clicked, [=](bool) { m_window->setProperty("msg", m_ui->m_msgEdit->text()); });

    m_widget= m_ui->m_scrollAreaVisual;

    m_label->installEventFilter(this);
}
void CustomerView::setSelectionIndex(const QModelIndex& index)
{
    QObject* root= m_engine->rootObjects().first();
    if(nullptr == root)
        return;

    QObject* listview= root->findChild<QObject*>("view");
    if(nullptr == listview)
        return;

    listview->setProperty("currentIndex", index.row());
}

bool CustomerView::isVisible() const
{
    return m_window->isVisible();
}

void CustomerView::setVisible(bool visible)
{
    m_window->setVisible(visible);
    if(visible)
    {
        QTimer::singleShot(2000, m_timer, SLOT(start()));
    }
    else
    {
        m_timer->stop();
    }
}
void CustomerView::showFullScreen()
{
    if(nullptr != m_window)
    {
        m_window->showFullScreen();
    }
}
void CustomerView::showNormal()
{
    if(nullptr != m_window)
    {
        m_window->showNormal();
    }
}
Qt::WindowState CustomerView::windowState()
{
    return m_window->windowState();
}
void CustomerView::refreshView()
{
    if(nullptr != m_window)
    {
        QImage img= m_window->grabWindow();
        m_ratioImage= static_cast<double>(img.size().width()) / static_cast<double>(img.size().height());
        m_ratioImageBis= static_cast<double>(img.size().height()) / static_cast<double>(img.size().width());
        m_label->setPixmap(QPixmap::fromImage(img));
        resizeLabel();
    }
}
void CustomerView::resizeLabel()
{
    int w= m_widget->viewport()->rect().width();
    int h= m_widget->viewport()->rect().height();
    if(w > h * m_ratioImage)
    {
        m_label->resize(static_cast<int>(h * m_ratioImage), h);
    }
    else
    {
        m_label->resize(w, static_cast<int>(w * m_ratioImageBis));
    }
}
#include <QMouseEvent>
bool CustomerView::eventFilter(QObject* label, QEvent* vt)
{
    if(label == m_ui->m_scrollAreaVisual)
    {
        /*if(vt->type() == QEvent::Resize)
        {
            resizeLabel();
        }*/
    }
    else if((label == m_label)
            && ((vt->type() == QEvent::MouseButtonPress) || (vt->type() == QEvent::MouseButtonRelease)
                   || (vt->type() == QEvent::MouseMove)))
    {
        QMouseEvent* evt= static_cast<QMouseEvent*>(vt);
        QPoint posOnLabel= evt->pos();

        int w= m_label->geometry().width();
        int h= m_label->geometry().height();

        qreal ratioW= static_cast<qreal>(m_window->width()) / static_cast<qreal>(w);
        qreal ratioH= static_cast<qreal>(m_window->height()) / static_cast<qreal>(h);

        qreal x= (posOnLabel.x()) * ratioW;
        qreal y= (posOnLabel.y()) * ratioH;

        QPointF posOnQML(x, y);
        QMouseEvent* event
            = new QMouseEvent(evt->type(), posOnQML.toPoint(), evt->button(), evt->buttons(), evt->modifiers());

        QObject* root= m_engine->rootObjects().first();
        // QCoreApplication::sendEvent(m_window,event);
        QCoreApplication::sendEvent(root, event);
        // m_window->sendEvent(m_window->contentItem(),event);
        return true;
    }
    return false;
}

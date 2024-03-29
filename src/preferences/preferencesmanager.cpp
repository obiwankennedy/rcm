/***************************************************************************
 *	Copyright (C) 2010 by Renaud Guezennec                             *
 *   http://renaudguezennec.homelinux.org/accueil,3.html                   *
 *                                                                         *
 *   rolisteam is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "preferencesmanager.h"
#include <QDebug>
#include <QDir>
#include <QSettings>

PreferencesManager::PreferencesManager() : m_optionDictionary(nullptr)
{
    m_optionDictionary= new QMap<QString, QVariant>;

    // Default value
    /*m_optionDictionary->insert("MusicDirectory",QDir::homePath());
    m_optionDictionary->insert("ImageDirectory",QDir::homePath());
    m_optionDictionary->insert("MapDirectory",QDir::homePath());
    m_optionDictionary->insert("ScriptDirectory",QDir::homePath());
    m_optionDictionary->insert("MinutesDirectory",QDir::homePath());
    m_optionDictionary->insert("TchatDirectory",QDir::homePath());
    m_optionDictionary->insert("DataDirectory",QDir::homePath());*/
}

PreferencesManager::~PreferencesManager()
{
    delete m_optionDictionary;
}

PreferencesManager* PreferencesManager::m_singleton= nullptr;

PreferencesManager* PreferencesManager::getInstance()
{
    if(m_singleton == nullptr)
        m_singleton= new PreferencesManager;

    return m_singleton;
}
bool PreferencesManager::registerValue(QString key, QVariant value, bool overwrite)
{
    if((overwrite) || (!m_optionDictionary->contains(key)))
    {
        m_optionDictionary->insert(key, value);
        return true;
    }
    else
        return false;
}
const QVariant PreferencesManager::value(QString key, QVariant defaultValue) const
{
    if(m_optionDictionary->contains(key))
        return m_optionDictionary->value(key);
    else
        return defaultValue;
}

void PreferencesManager::readSettings(QSettings& settings)
{
    qDebug() << "before reading preferences";
    settings.beginGroup("preferences");
    QVariant variant= settings.value("map", *m_optionDictionary);
    if(variant.canConvert<QMap<QString, QVariant>>())
    {
        *m_optionDictionary= variant.value<QMap<QString, QVariant>>();
    }
    settings.endGroup();
    qDebug() << "after reading prefrences";
}
void PreferencesManager::writeSettings(QSettings& settings)
{
    qDebug() << "before writing preferences";
    settings.beginGroup("preferences");
    settings.setValue("map", *m_optionDictionary);
    settings.endGroup();
    qDebug() << "after writing prefrences";
}

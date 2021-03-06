/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */


#include "xdgaction.h"
#include "xdgicon.h"
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>


/************************************************

 ************************************************/
XdgAction::XdgAction(QObject *parent):
    QAction(parent)
{
}


/************************************************

 ************************************************/
XdgAction::XdgAction(const XdgDesktopFile& desktopFile, QObject *parent):
    QAction(parent)
{
    load(desktopFile);
}


/************************************************

 ************************************************/
XdgAction::XdgAction(const XdgDesktopFile* desktopFile, QObject *parent):
    QAction(parent)
{
    load(*desktopFile);
}


/************************************************

 ************************************************/
XdgAction::XdgAction(const QString& desktopFileName, QObject *parent):
    QAction(parent)
{
    XdgDesktopFile df;
    df.load(desktopFileName);
    load(df);
}


/************************************************

 ************************************************/
XdgAction::XdgAction(const XdgAction& other, QObject *parent):
    QAction(parent)
{
    load(other.mDesktopFile);
}


/************************************************

 ************************************************/
XdgAction::~XdgAction()
{
}


/************************************************

 ************************************************/
XdgAction& XdgAction::operator=(const XdgAction& other)
{
    load(other.mDesktopFile);
     return *this;
}


/************************************************

 ************************************************/
bool XdgAction::isValid() const
{
    return mDesktopFile.isValid();
}


/************************************************

 ************************************************/
void XdgAction::load(const XdgDesktopFile& desktopFile)
{
    mDesktopFile = desktopFile;
    if (mDesktopFile.isValid())
    {
        setText(mDesktopFile.name());
        setToolTip(mDesktopFile.comment());

        connect(this, SIGNAL(triggered()), this, SLOT(runConmmand()));
        QMetaObject::invokeMethod(this, "updateIcon", Qt::QueuedConnection);
    }
    else
    {
        setText("");
        setToolTip("");
        setIcon(QIcon());
    }
}


/************************************************

 ************************************************/
void XdgAction::runConmmand() const
{
    if (mDesktopFile.isValid())
        mDesktopFile.startDetached();
}


/************************************************

 ************************************************/
void XdgAction::updateIcon()
{
    setIcon(mDesktopFile.icon());
    if (icon().isNull())
        setIcon(XdgIcon::fromTheme("application-x-executable"));
    QCoreApplication::processEvents();
}

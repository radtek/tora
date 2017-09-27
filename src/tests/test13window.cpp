
/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * TOra - An Oracle Toolkit for DBA's and developers
 *
 * Shared/mixed copyright is held throughout files in this product
 *
 * Portions Copyright (C) 2000-2001 Underscore AB
 * Portions Copyright (C) 2003-2005 Quest Software, Inc.
 * Portions Copyright (C) 2004-2013 Numerous Other Contributors
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program as the file COPYING.txt; if not, please see
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries.
 *
 * All trademarks belong to their respective owners.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "tests/test13window.h"
#include "editor/tosqltext.h"

#include <QStatusBar>
#include <QScrollArea>
#include <QSplitter>
#include <QToolBar>

Test13Window::Test13Window(const QString &sql)
    : Ui::Test13Window()
    , toContextMenuHandler()
{
    Ui::Test13Window::setupUi(this);

    sqlText->setText(sql);

    connect(actionOpen, SIGNAL(triggered()), this, SLOT(load()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QMainWindow::show();

    parseAct = new QAction(tr("Parse"), this);
    parseAct->setShortcut(Qt::CTRL + Qt::Key_K);
    connect(parseAct, SIGNAL(triggered()), this, SLOT(parse(void)));

}

void Test13Window::load()
{
    QString fn = Utils::toOpenFilename("*.sql", this);
    if (!fn.isEmpty())
    {
        QString data = Utils::toReadFile(fn);
        sqlText->setText(data);
    }
}

void Test13Window::parse()
{
}

void Test13Window::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void Test13Window::handle(QObject* obj, QMenu* menu)
{
    QString name = obj->objectName();

    if (toSqlText* t = dynamic_cast<toSqlText*>(obj))
    {
        Q_UNUSED(t);
        menu->addSeparator();
        menu->addAction(parseAct);
    }
}
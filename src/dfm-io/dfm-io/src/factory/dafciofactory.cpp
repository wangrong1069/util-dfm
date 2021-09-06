/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     dengkeyun<dengkeyun@uniontech.com>
 *
 * Maintainer: max-lv<lvwujun@uniontech.com>
 *             xushitong<xushitong@uniontech.com>
 *             zhangsheng<zhangsheng@uniontech.com>
 *             lanxuesong<lanxuesong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "factory/dafciofactory.h"
#include "factory/dafciofactory_p.h"
#include "local/dlocalhelper.h"

#include "local/dlocalenumerator.h"
#include "local/dlocalwatcher.h"
#include "local/dlocaloperator.h"
#include "local/dlocalfile.h"

#include <QDebug>

USING_IO_NAMESPACE

DAfcIOFactoryPrivate::DAfcIOFactoryPrivate(DAfcIOFactory *q)
    : q_ptr(q)
{
}

DAfcIOFactoryPrivate::~DAfcIOFactoryPrivate()
{
}

QSharedPointer<DFileInfo> DAfcIOFactoryPrivate::createFileInfo() const
{
    Q_Q(const DAfcIOFactory);
    const QUrl &uri = q->uri();
    const QString &url = uri.url();

    return DLocalHelper::getFileInfo(url);
}

QSharedPointer<DFile> DAfcIOFactoryPrivate::createFile() const
{
    Q_Q(const DAfcIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalFile>(new DLocalFile(uri));
}

QSharedPointer<DEnumerator> DAfcIOFactoryPrivate::createEnumerator() const
{
    Q_Q(const DAfcIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalEnumerator>(new DLocalEnumerator(uri));
}

QSharedPointer<DWatcher> DAfcIOFactoryPrivate::createWatcher() const
{
    Q_Q(const DAfcIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalWatcher>(new DLocalWatcher(uri));
}

QSharedPointer<DOperator> DAfcIOFactoryPrivate::createOperator() const
{
    Q_Q(const DAfcIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalOperator>(new DLocalOperator(uri));
}

DAfcIOFactory::DAfcIOFactory(const QUrl &uri)
    : DIOFactory(uri)
    , d_ptr(new DAfcIOFactoryPrivate(this))
{
    registerCreateFileInfo(std::bind(&DAfcIOFactory::createFileInfo, this));
    registerCreateFile(std::bind(&DAfcIOFactory::createFile, this));
    registerCreateWatcher(std::bind(&DAfcIOFactory::createWatcher, this));
    registerCreateOperator(std::bind(&DAfcIOFactory::createOperator, this));
    registerCreateEnumerator(std::bind(&DAfcIOFactory::createEnumerator, this));
}

DAfcIOFactory::~DAfcIOFactory()
{
}

QSharedPointer<DFileInfo> DAfcIOFactory::createFileInfo() const
{
    Q_D(const DAfcIOFactory);
    return d->createFileInfo();
}

QSharedPointer<DFile> DAfcIOFactory::createFile() const
{
    Q_D(const DAfcIOFactory);
    return d->createFile();
}

QSharedPointer<DEnumerator> DAfcIOFactory::createEnumerator() const
{
    Q_D(const DAfcIOFactory);
    return d->createEnumerator();
}

QSharedPointer<DWatcher> DAfcIOFactory::createWatcher() const
{
    Q_D(const DAfcIOFactory);
    return d->createWatcher();
}

QSharedPointer<DOperator> DAfcIOFactory::createOperator() const
{
    Q_D(const DAfcIOFactory);
    return d->createOperator();
}

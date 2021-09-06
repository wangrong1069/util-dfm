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

#include "factory/dnetworkiofactory.h"
#include "factory/dnetworkiofactory_p.h"
#include "local/dlocalhelper.h"

#include "local/dlocalenumerator.h"
#include "local/dlocalwatcher.h"
#include "local/dlocaloperator.h"
#include "local/dlocalfile.h"

#include <QDebug>

USING_IO_NAMESPACE

DNetworkIOFactoryPrivate::DNetworkIOFactoryPrivate(DNetworkIOFactory *q)
    : q_ptr(q)
{
}

DNetworkIOFactoryPrivate::~DNetworkIOFactoryPrivate()
{
}

QSharedPointer<DFileInfo> DNetworkIOFactoryPrivate::createFileInfo() const
{
    Q_Q(const DNetworkIOFactory);
    const QUrl &uri = q->uri();
    const QString &url = uri.url();

    return DLocalHelper::getFileInfo(url);
}

QSharedPointer<DFile> DNetworkIOFactoryPrivate::createFile() const
{
    Q_Q(const DNetworkIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalFile>(new DLocalFile(uri));
}

QSharedPointer<DEnumerator> DNetworkIOFactoryPrivate::createEnumerator() const
{
    Q_Q(const DNetworkIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalEnumerator>(new DLocalEnumerator(uri));
}

QSharedPointer<DWatcher> DNetworkIOFactoryPrivate::createWatcher() const
{
    Q_Q(const DNetworkIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalWatcher>(new DLocalWatcher(uri));
}

QSharedPointer<DOperator> DNetworkIOFactoryPrivate::createOperator() const
{
    Q_Q(const DNetworkIOFactory);
    const QUrl &uri = q->uri();

    return QSharedPointer<DLocalOperator>(new DLocalOperator(uri));
}

DNetworkIOFactory::DNetworkIOFactory(const QUrl &uri)
    : DIOFactory(uri)
    , d_ptr(new DNetworkIOFactoryPrivate(this))
{
    registerCreateFileInfo(std::bind(&DNetworkIOFactory::createFileInfo, this));
    registerCreateFile(std::bind(&DNetworkIOFactory::createFile, this));
    registerCreateWatcher(std::bind(&DNetworkIOFactory::createWatcher, this));
    registerCreateOperator(std::bind(&DNetworkIOFactory::createOperator, this));
    registerCreateEnumerator(std::bind(&DNetworkIOFactory::createEnumerator, this));
}

DNetworkIOFactory::~DNetworkIOFactory()
{
}

QSharedPointer<DFileInfo> DNetworkIOFactory::createFileInfo() const
{
    Q_D(const DNetworkIOFactory);
    return d->createFileInfo();
}

QSharedPointer<DFile> DNetworkIOFactory::createFile() const
{
    Q_D(const DNetworkIOFactory);
    return d->createFile();
}

QSharedPointer<DEnumerator> DNetworkIOFactory::createEnumerator() const
{
    Q_D(const DNetworkIOFactory);
    return d->createEnumerator();
}

QSharedPointer<DWatcher> DNetworkIOFactory::createWatcher() const
{
    Q_D(const DNetworkIOFactory);
    return d->createWatcher();
}

QSharedPointer<DOperator> DNetworkIOFactory::createOperator() const
{
    Q_D(const DNetworkIOFactory);
    return d->createOperator();
}

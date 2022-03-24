/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qwebengineloadinginfo.h>

#include <web_engine_error.h>

QT_BEGIN_NAMESPACE

using LoadStatus = QWebEngineLoadingInfo::LoadStatus;
using ErrorDomain = QWebEngineLoadingInfo::ErrorDomain;

Q_STATIC_ASSERT(static_cast<int>(WebEngineError::NoErrorDomain) == static_cast<int>(ErrorDomain::NoErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::InternalErrorDomain) == static_cast<int>(ErrorDomain::InternalErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::ConnectionErrorDomain) == static_cast<int>(ErrorDomain::ConnectionErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::CertificateErrorDomain) == static_cast<int>(ErrorDomain::CertificateErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::HttpErrorDomain) == static_cast<int>(ErrorDomain::HttpErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::FtpErrorDomain) == static_cast<int>(ErrorDomain::FtpErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::DnsErrorDomain) == static_cast<int>(ErrorDomain::DnsErrorDomain));
Q_STATIC_ASSERT(static_cast<int>(WebEngineError::HttpStatusCodeDomain) == static_cast<int>(ErrorDomain::HttpStatusCodeDomain));

class QWebEngineLoadingInfo::QWebEngineLoadingInfoPrivate : public QSharedData {
public:
    QWebEngineLoadingInfoPrivate(const QUrl& url, LoadStatus status, bool isErrorPage,
                                 const QString& errorString, int errorCode, ErrorDomain errorDomain)
        : url(url)
        , status(status)
        , isErrorPage(isErrorPage)
        , errorString(errorString)
        , errorCode(errorCode)
        , errorDomain(errorDomain)
    {
    }

    QUrl url;
    LoadStatus status;
    bool isErrorPage;
    QString errorString;
    int errorCode;
    ErrorDomain errorDomain;
};

/*!
    \class QWebEngineLoadingInfo
    \brief A utility type for the WebEngineView::loadingChanged signal.
    \inmodule QtWebEngineCore
    \since 6.2

    Contains information about a web page loading status change, such as the URL and
    current loading status (started, succeeded, stopped, failed).

    \sa QWebEnginePage::loadStarted, QWebEnginePage::loadFinished, WebEngineView::loadingChanged
*/
QWebEngineLoadingInfo::QWebEngineLoadingInfo(const QUrl& url, LoadStatus status, bool isErrorPage,
                                             const QString& errorString, int errorCode, ErrorDomain errorDomain)
    : d_ptr(new QWebEngineLoadingInfoPrivate(url, status, isErrorPage, errorString, errorCode, errorDomain))
{
}

QWebEngineLoadingInfo::QWebEngineLoadingInfo(const QWebEngineLoadingInfo &other) = default;
QWebEngineLoadingInfo& QWebEngineLoadingInfo::operator=(const QWebEngineLoadingInfo &other) = default;
QWebEngineLoadingInfo::QWebEngineLoadingInfo(QWebEngineLoadingInfo &&other) = default;
QWebEngineLoadingInfo& QWebEngineLoadingInfo::operator=(QWebEngineLoadingInfo &&other) = default;

QWebEngineLoadingInfo::~QWebEngineLoadingInfo()
{
}
/*!
    \property QWebEngineLoadingInfo::url
    \brief Holds the URL of the load request.
*/
/*!
    Returns the URL of the load request.
*/
QUrl QWebEngineLoadingInfo::url() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->url;
}
/*!
    \enum QWebEngineLoadingInfo::LoadStatus

    This enumeration represents the load status of a web page load request:

    \value  LoadStartedStatus Page is currently loading.
    \value  LoadStoppedStatus
            Loading the page was stopped by the stop() method or by the loader
            code or network stack in Chromium.
    \value  LoadSucceededStatus Page has been loaded with success.
    \value  LoadFailedStatus Page could not be loaded.
*/
/*!
    \property QWebEngineLoadingInfo::status
    \brief The load status of the page.
*/
LoadStatus QWebEngineLoadingInfo::status() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->status;
}
/*!
    \property QWebEngineLoadingInfo::isErrorPage
    \brief Indicates if the load resulted in an error page.
*/
bool QWebEngineLoadingInfo::isErrorPage() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->isErrorPage;
}
/*!
    \property QWebEngineLoadingInfo::errorString
    \brief Holds the error message.
*/
QString QWebEngineLoadingInfo::errorString() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->errorString;
}
/*!
    \enum QWebEngineLoadingInfo::ErrorDomain
    This enumeration holds the type of a load error:

    \value  NoErrorDomain
            Error type is not known.
    \value  InternalErrorDomain
            Content cannot be interpreted by \QWE.
    \value  ConnectionErrorDomain
            Error results from a faulty network connection.
    \value  CertificateErrorDomain
            Error is related to the SSL/TLS certificate.
    \value  HttpErrorDomain
            Error is related to the HTTP connection.
    \value  FtpErrorDomain
            Error is related to the FTP connection.
    \value  DnsErrorDomain
            Error is related to the DNS connection.
    \value  HttpStatusCodeDomain
            Error is the HTTP response status code, even in case of success e.g. the server replied with status 200.
*/
/*
    \property QWebEngineLoadingInfo::errorDomain
    \brief Holds the error domain.
*/
ErrorDomain QWebEngineLoadingInfo::errorDomain() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->errorDomain;
}

/*!
    \property QWebEngineLoadingInfo::errorCode
    \brief Holds the error code.
*/
int QWebEngineLoadingInfo::errorCode() const
{
    Q_D(const QWebEngineLoadingInfo);
    return d->errorCode;
}

QT_END_NAMESPACE

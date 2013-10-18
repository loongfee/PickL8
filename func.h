#pragma once
#ifndef FUNC_H
#define FUNC_H

#include <QThread> 
#include <QFileInfo>
#include <QDir>
#include <QPointer>
#include "qfileinfo.h"
#include "qstring.h"
#include "qstringlist.h"
#include "qiodevice.h"
#include "qfile.h"
#include "qdir.h"
#include "qtextstream.h"
#include "qbytearray.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <wtypes.h>
#include <atltypes.h>

bool FindFile(const QString& path, const QStringList& filter, QStringList &vFiles);
QString QBeforeLast(const QString& str, QChar ch);
QString QAfterFirst(const QString& str, QChar ch);
QString QAfterLast(const QString& str, QChar ch);
QString QBeforeFirst(const QString& str, QChar ch);

bool CopyFolder(QString pathFrom, QString pathTo, QStringList filters = QStringList("*.*"), bool bOverWrite = true);


static QString getLastErrorMsg() {
	LPWSTR bufPtr = NULL;
	DWORD err = GetLastError();
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
	const QString result = 
		(bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
		QString("Unknown Error %1").arg(err);
	LocalFree(bufPtr);
	return result;
}

class CopierWorker : public QThread { // only to be used by the Copier object
	BOOL m_stop;
	QString m_src, m_dst;
	QPointer<QObject> m_object;
	static DWORD CALLBACK copyProgress(
		LARGE_INTEGER totalSize, LARGE_INTEGER totalTransferred,
		LARGE_INTEGER streamSize, LARGE_INTEGER streamTransferred,
		DWORD streamNo, DWORD callbackReason, HANDLE src, HANDLE dst,
		LPVOID data)
	{
		Q_UNUSED(streamSize) Q_UNUSED(streamTransferred)
			Q_UNUSED(streamNo) Q_UNUSED(callbackReason)
			Q_UNUSED(src) Q_UNUSED(dst)
			QObject * object = static_cast<QObject*>(data);
		const QString text = QString("Transferred %1 of %2 bytes").
			arg(totalTransferred.QuadPart).arg(totalSize.QuadPart);
		QMetaObject::invokeMethod(object, "newStatus", Qt::QueuedConnection,
			Q_ARG(QString, text));
		return PROGRESS_CONTINUE;
	}
	void run() {
		m_stop = FALSE;
		BOOL rc = CopyFileExW((LPCWSTR)m_src.utf16(), (LPCWSTR)m_dst.utf16(),
			&copyProgress, m_object, &m_stop, 0);
		if (!rc) {
			QMetaObject::invokeMethod(m_object, "newStatus", Qt::QueuedConnection,
				Q_ARG(QString, getLastErrorMsg()));
		}
	}
	CopierWorker(const QString & src, const QString & dst, QObject * obj) :
		m_src(src), m_dst(dst), m_object(obj) {}
	void stop() { m_stop = TRUE; }
	friend class Copier;
};

class Copier : public QObject {
	Q_OBJECT
		QPointer<CopierWorker> m_worker;
public:
	Copier(const QString & src, const QString & dst) : m_worker(new CopierWorker(src, dst, this)) {
		connect(m_worker, SIGNAL(finished()), SIGNAL(finished()));
		connect(m_worker, SIGNAL(finished()), m_worker, SLOT(deleteLater()));
	}
	~Copier() {
		if (!m_worker) return;
		m_worker->stop();
		if (!m_worker->isRunning()) delete m_worker;
	}
	Q_SIGNAL void newStatus(const QString &);
	Q_SIGNAL void finished();
	Q_SLOT void stop() { m_worker->stop(); }
	void copy() { m_worker->start(); }
};

#endif
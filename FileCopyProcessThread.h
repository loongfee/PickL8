#ifndef FILE_COPY_PROCESS_THREAD_H
#define FILE_COPY_PROCESS_THREAD_H

#include <QThread> 
#include "qfileinfo.h"
#include "qstring.h"
#include "qstringlist.h"
#include "qiodevice.h"
#include "qfile.h"
#include "qdir.h"
#include "qtextstream.h"
#include "qbytearray.h"
#include "qmutex.h"
#include "func.h"
//#include "DlgMain.h"

class FileCopyProcessThread : public QThread   
{   
	Q_OBJECT  
signals:
	void taskProgress(double);
	void beginUI();
	void endUI();
	//void newProgressListener();
	//void releaseProgressListener();
	//void addListener(rspfImageFileWriter*);
	//void removeListener(rspfImageFileWriter*);
	public slots:

	//Q_SIGNAL void stopCopy();
	//Q_SLOT void startCopy() {
	//	Copier * copier = new Copier(m_src->text(), m_dst->text());
	//	connect(copier, SIGNAL(newStatus(QString)), m_status, SLOT(setText(QString)));
	//	connect(copier, SIGNAL(finished()), SIGNAL(copyFinished()));
	//	connect(this, SIGNAL(stopCopy()), copier, SLOT(stop()));
	//	copier->copy();
	//}
	//Q_SIGNAL void copyFinished();
public:   
	FileCopyProcessThread();
	~FileCopyProcessThread();

	//DlgMain *m_parent;

	QMutex fileCopyProcessMutex; 

	qint64 m_nCopySize;
	int m_nAllFolders;
	int m_nAllFiles;
	int m_nCurrentFolder;
	int m_nCurrentFile;

	void run(); //线程函数  
	void Process(QStringList inputFileList, QString outPath, bool bOverWrite = false); //线程接口
	void updateProgress(double file_percent);

private:	
	QStringList m_InputFileList;
	QString m_OutPath;
	bool m_bOverWrite;
	double m_percentage;

};   
#endif
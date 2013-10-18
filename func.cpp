#include "func.h"
#include <QDateTime>


bool FindFile(const QString& path, const QStringList& filter, QStringList &vFiles)
{
	QDir dir(path);
	if(!dir.exists())
		return false;
	dir.setFilter(QDir::Dirs | QDir::Files);
	dir.setSorting(QDir::DirsFirst);

	QFileInfoList list = dir.entryInfoList(filter, QDir::Files);
	int i = 0;
	for(i = 0;i < list.size();i++)
	{
		vFiles.push_back(list.at(i).absoluteFilePath());
	}

	i=0;
	list = dir.entryInfoList(QDir::Dirs);
	do{
		QFileInfo fileInfo=list.at(i);
		if(fileInfo.fileName()=="."||fileInfo.fileName()=="..")
		{
			i++;
			continue;
		}
		bool bisDir=fileInfo.isDir();
		if(bisDir)
		{
			FindFile(fileInfo.filePath(), filter, vFiles);
		}
		i++;
	}while(i<list.size());
	return true;
}

QString QBeforeLast(const QString& str, QChar ch)
{
	QStringList fields = str.split(ch);
	fields.removeLast();
	return fields.join(ch);
}

QString QAfterFirst(const QString& str, QChar ch)
{
	QStringList fields = str.split(ch);
	fields.removeFirst();
	return fields.join(ch);
}

QString QAfterLast(const QString& str, QChar ch)
{
	QStringList fields = str.split(ch);
	return fields.takeLast();
}

QString QBeforeFirst(const QString& str, QChar ch)
{
	QStringList fields = str.split(ch);
	return fields.takeFirst();
}

bool CopyFolder(QString pathFrom, QString pathTo, QStringList filters/* = QStringList("*.*")*/, bool bOverWrite/* = true*/)
{
	QStringList FileList;
	FindFile(pathFrom, filters, FileList);	//找出对应的全色文件	
	
	if (!QDir(pathTo).exists())
	{
		_mkdir(pathTo.toUtf8());
	}
	for(int i = 0;i < FileList.count();i++)
	{
		QFileInfo fileinfo(FileList.at(i));
		QString newpath = QDir::toNativeSeparators(pathTo + "\\" + fileinfo.fileName());
		if(QFile(newpath).exists() && bOverWrite)
		{
			QFile(newpath).remove();
		}
		QFile::copy(FileList.at(i), newpath);
	}
	return true;
}
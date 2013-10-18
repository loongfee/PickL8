#include "FileCopyProcessThread.h"
#include <QtGui>
#include <QApplication>
#include <QStateMachine>
#include <windows.h>

FileCopyProcessThread::FileCopyProcessThread()
{
	//m_parent = dlg;
}

void FileCopyProcessThread::Process(QStringList inputFileList, QString outPath, bool bOverWrite/* = false*/)
{
	m_InputFileList = inputFileList;
	m_OutPath = outPath;
	m_bOverWrite = bOverWrite;
	start(); //开始新线程
}

FileCopyProcessThread::~FileCopyProcessThread()
{
}

DWORD CALLBACK MyCopyProgressRoutine(
	LARGE_INTEGER TotalFileSize, // file size
	LARGE_INTEGER TotalBytesTransferred, // bytes transferred
	LARGE_INTEGER StreamSize, // bytes in stream
	LARGE_INTEGER StreamBytesTransferred, // bytes transferred for stream
	DWORD dwStreamNumber, // current stream
	DWORD dwCallbackReason, // callback reason
	HANDLE hSourceFile, // handle to source file
	HANDLE hDestinationFile, // handle to destination file
	LPVOID lpData // from CopyFileEx
	)
{
	FileCopyProcessThread* ptr = (FileCopyProcessThread*)lpData;
	// do something with pointer, e.g. ptr->m_Progressbar.Pos blahblah 

	//ptr->m_fileprog.Clear();
	//ptr->UpdateWindow();
	//DWORD percent = (TotalBytesTransferred.HighPart*2^31 + TotalBytesTransferred.LowPart) * 100/(TotalFileSize.HighPart*2^31 + TotalBytesTransferred.LowPart);
	double percent = (TotalBytesTransferred.HighPart*2^31 + TotalBytesTransferred.LowPart) /(double)(TotalFileSize.HighPart*2^31 + TotalBytesTransferred.LowPart);

	//wsprintf( currentprog, _T("%d %%"),percent );
	ptr->updateProgress(percent);

	return  PROGRESS_CONTINUE;
}

void FileCopyProcessThread::run() 
{   
	fileCopyProcessMutex.lock();
	emit beginUI();

	int num = m_InputFileList.size();
	int nSuccess = 0;
	int nFailed = 0;
	m_nAllFolders = num;
	for(int i = 0;i < num;i++)
	{
		m_nCurrentFolder = i;
		m_percentage = m_nCurrentFolder / (double)m_nAllFolders;
		emit taskProgress(m_percentage);
		QString pathFrom = QFileInfo(m_InputFileList[i]).path();
		QString folderName = QAfterLast(QDir::toNativeSeparators(pathFrom), QDir::separator());
		QString pathTo =  QDir::toNativeSeparators(m_OutPath + QDir::separator() + folderName);

		if (!QDir(pathTo).exists())
		{
			_mkdir(pathTo.toUtf8());
		}

		QStringList filters;
		filters<<"*.*";
		QStringList FileList;
		FindFile(pathFrom, filters, FileList);	//找出对应的全色文件

		m_nAllFiles = FileList.count();
		for(int i = 0;i < FileList.count();i++)
		{
			m_nCurrentFile = i;
			QFileInfo fileinfo(FileList.at(i));
			QString newpath = QDir::toNativeSeparators(pathTo + QDir::separator() + fileinfo.fileName());
			QFile newFile(newpath);
			m_nCopySize = fileinfo.size();
			//if(newFile.exists() && m_bOverWrite)
			//{
			//	newFile.remove();
			//}
			//QFile fromFile(FileList.at(i));
			//fromFile.readyRead();
			//connect(&newFile, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)));
			//connect(&newFile, SIGNAL(bytesWritten(qint64)),  SLOT(updateProgress(qint64)));
			//fromFile.copy(newpath);
			//QFile::copy(FileList.at(i), newpath);
			//qint64 nCopySize = newFile.size();
			wchar_t FileNameFrom[1024]={'\0'};
			wchar_t FileNameTo[1024]={'\0'};
			FileList.at(i).toWCharArray(FileNameFrom);
			newpath.toWCharArray(FileNameTo);
			if (m_bOverWrite)
			{
				bool ret = CopyFileEx( FileNameFrom, FileNameTo, &MyCopyProgressRoutine, this, FALSE, COPY_FILE_ALLOW_DECRYPTED_DESTINATION);
			}
			else
			{
				bool ret = CopyFileEx( FileNameFrom, FileNameTo, &MyCopyProgressRoutine, this, FALSE, COPY_FILE_FAIL_IF_EXISTS);
			}
			//delete []FileNameFrom;
			//delete []FileNameTo;
			//FileNameFrom = NULL;
			//FileNameTo = NULL;
		}
	}
	m_percentage = 1.0;
	emit taskProgress(m_percentage);

	emit endUI();
	fileCopyProcessMutex.unlock();
} 

void FileCopyProcessThread::updateProgress(double file_percent)
{
	//m_percentage = m_nCurrentFolder / (double)m_nAllFolders;
	m_percentage = (m_nCurrentFolder + (m_nCurrentFile + file_percent) / (double)m_nAllFiles) / (double)m_nAllFolders;
	emit taskProgress(m_percentage);
}
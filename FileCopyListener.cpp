#include "FileCopyListener.h"
#include "qmutex.h"
#include "func.h"
#include <QtGui>
#include <QApplication>
//QMutex DEMListenerMutex; 

FileCopyListener::FileCopyListener()
{
}

//void DemConvertListener::demListener(MultOrthProcessListener* progress)
//{
//	m_progressListener = progress;
//	start(); //开始新线程
//}

FileCopyListener::~FileCopyListener()
{
}

//void DemConvertListener::run()
//{   
//	DEMListenerMutex.lock();
//
//	int done = 0;
//	int lastDone = done;
//	while (done!=100)
//	{
//		msleep(1);
//		//if(NULL == m_parent->m_progressListener)
//		//{
//		//	continue;
//		//}
//		//done = m_parent->m_progressListener->getPercentComplete();
//		emit getCurrentPercent(&done);
//		emit updateProgressBar(done);
//	}
//
//	emit releaseProgressListener();
//	DEMListenerMutex.unlock();
//}

void FileCopyListener::processEvent(rspfEvent& event)
{
	switch(event.getId())
	{
	case RSPF_EVENT_PROCESS_PROGRESS_ID:
		{
			rspfProcessProgressEvent* eventCast = static_cast<rspfProcessProgressEvent*>(&event);
			processProgressEvent(*eventCast);
			break;
		}
	default:
		{
			rspfListener::processEvent(event);
			break;
		}
	}
}
void FileCopyListener::processProgressEvent(rspfProcessProgressEvent& event)
{
	emit updateProgress(event.getPercentComplete());
	//percentComplete = event.getPercentComplete();
}
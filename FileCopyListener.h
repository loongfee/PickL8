#ifndef FILE_COPY_LISTENER_H
#define FILE_COPY_LISTENER_H

#include <QThread> 


class FileCopyListener : public QThread
{   
	Q_OBJECT  

signals:
	void updateProgress(double);
	//void updateProgressBar(int);
	//void newProgressListener();
	//void releaseProgressListener();
	//void getCurrentPercent(int* done);

public:   
	FileCopyListener();   
	~FileCopyListener();
	rspfProcessProgressEvent  GaugeProgressEvent;
	virtual void processEvent(rspfEvent& event);
	virtual void processProgressEvent(rspfProcessProgressEvent& event);

	//void run(); //�̺߳���  
	//void demListener(MultOrthProcessListener* progress); //�߳̽ӿ�
	//DlgMain* m_parent;
	//MultOrthProcessListener* m_progressListener;
protected: 
}; 
#endif
#include <QtGui>
#include <xiosbase>
#include <iostream>
#include <QLabel>
#include <qdir.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>
#include <QHeaderView>
#include <QGroupBox>
#include <QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QCalendarWidget>

#include "DlgMain.h"
#include "FileCopyProcessThread.h"

QWaitCondition bufferNotFull;

DlgMain::DlgMain()
{
	m_Button_InputBrowse = new QPushButton(tr("输入目录"),this);
	//m_Button_InputBrowse->setMinimumSize(100,28);
	m_Edit_InputPath = new QLineEdit(this);
	m_Edit_InputPath->setReadOnly(true);
	QHBoxLayout *layoutInput = new QHBoxLayout;
	layoutInput->addWidget(m_Edit_InputPath);
	layoutInput->addWidget(m_Button_InputBrowse);

	m_Button_OutputBrowse = new QPushButton(tr("输出目录"),this);
	//m_Button_OutputBrowse->setMinimumSize(100,28);
	m_Edit_OutputPath = new QLineEdit(this);
	m_Edit_OutputPath->setReadOnly(true);
	ReadLastPath();
	QHBoxLayout *layoutOutput = new QHBoxLayout;
	layoutOutput->addWidget(m_Edit_OutputPath);
	layoutOutput->addWidget(m_Button_OutputBrowse);

	QLabel *text1 = new QLabel(tr("从"));
	m_DateEdit_StartDate = new QDateEdit(this);
	QLabel *text2 = new QLabel(tr("到"));
	m_DateEdit_EndDate = new QDateEdit(this);
	m_DateEdit_StartDate->setCalendarPopup(true);
	m_DateEdit_EndDate->setCalendarPopup(true);
	m_DateEdit_StartDate->setDate(QDate(2013, 6, 1));
	m_DateEdit_EndDate->setDate(QDate(2013, 9, 1));
	ReadLastDate();
	QHBoxLayout *layoutDate = new QHBoxLayout;
	layoutDate->addWidget(text1);
	layoutDate->addWidget(m_DateEdit_StartDate);
	layoutDate->addWidget(text2);
	layoutDate->addWidget(m_DateEdit_EndDate);

	m_CheckBox_OverWrite = new QCheckBox(tr("是否覆盖"));
	m_CheckBox_OverWrite->setCheckState(Qt::CheckState::Unchecked);
	QLabel *textMaxCloud = new QLabel(tr("最大云量："));
	m_ComboBox_MaxCloud = new QComboBox;
	QStringList cloudList;
	cloudList<<"100%";
	cloudList<<"90%";
	cloudList<<"80%";
	cloudList<<"70%";
	cloudList<<"60%";
	cloudList<<"50%";
	cloudList<<"40%";
	cloudList<<"30%";
	cloudList<<"20%";
	cloudList<<"10%";
	cloudList<<"0%";
	m_ComboBox_MaxCloud->insertItems(0, cloudList);
	QHBoxLayout *layoutOptions = new QHBoxLayout;
	layoutOptions->addWidget(m_CheckBox_OverWrite);
	layoutOptions->addSpacing(40);
	layoutOptions->addWidget(textMaxCloud);
	layoutOptions->addWidget(m_ComboBox_MaxCloud);

	m_Button_Search = new QPushButton(tr("开始挑选"),this);
	//m_Button_Search->setMinimumSize(100,28);

	m_ProgressBar = new QProgressBar();
	m_ProgressBar->setTextVisible(true);
	m_ProgressBar->setRange(0, 100);
	m_ProgressBar->setValue(0);
	m_ProgressBar->setVisible(false);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addLayout(layoutInput);
	mainLayout->addLayout(layoutOutput);
	mainLayout->addLayout(layoutDate);
	mainLayout->addLayout(layoutOptions);
	mainLayout->addWidget(m_Button_Search);
	mainLayout->addWidget(m_ProgressBar);


	connect(m_Button_InputBrowse,SIGNAL(clicked(bool)),this,SLOT(OnClickBrowseInputPath()));
	connect(m_Button_OutputBrowse,SIGNAL(clicked(bool)),this,SLOT(OnClickBrowseOutputPath()));
	connect(m_DateEdit_StartDate,SIGNAL(dateChanged(const QDate)),this,SLOT(OnStartDateChanged()));
	connect(m_DateEdit_EndDate,SIGNAL(dateChanged(const QDate)),this,SLOT(OnEndDateChanged()));

	connect(m_Button_Search,SIGNAL(clicked(bool)),this,SLOT(OnClickSearch()));

	mainLayout->setContentsMargins(20, 10, 20, 10);
	this->setLayout(mainLayout);
	//this->resize(880,650);
	this->setWindowFlags(Qt::WindowMinimizeButtonHint);
	this->setStyleSheet("FilesRename {background-color: lightblue};");
	this->setWindowTitle(qApp->applicationName());
	this->setWindowIcon(QIcon("PickL8.ico"));
}

DlgMain::~DlgMain()
{
}

void DlgMain::ReadLastPath()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString inpath = ConfigIni->value("/Last/InputPath","").toString();
	QString outpath = ConfigIni->value("/Last/OutputPath","").toString();

	m_Edit_InputPath->setText(inpath);
	m_Edit_OutputPath->setText(outpath);

	delete ConfigIni;
}

void DlgMain::ReadLastDate()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString StartDate = ConfigIni->value("/Last/StartDate","").toString();
	QString EndDate = ConfigIni->value("/Last/EndDate","").toString();

	if(!StartDate.isEmpty())
	{
		m_DateEdit_StartDate->setDate(QDate::fromString(StartDate));
	}
	if(!EndDate.isEmpty())
	{
		m_DateEdit_EndDate->setDate(QDate::fromString(EndDate));
	}
	delete ConfigIni;
}

void DlgMain::SaveLastDate()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString StartDate = ConfigIni->value("/Last/StartDate","").toString();
	QString EndDate = ConfigIni->value("/Last/EndDate","").toString();

	ConfigIni->setValue("/Last/StartDate", m_DateEdit_StartDate->date().toString());
	ConfigIni->setValue("/Last/EndDate", m_DateEdit_EndDate->date().toString());

	delete ConfigIni;
}

bool DlgMain::OnClickBrowseInputPath()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString path = ConfigIni->value("/Last/InputPath","").toString();

	QString inPath = QFileDialog::getExistingDirectory(this,
		tr("选择输入目录"), 
		path);
	if(inPath.length() == 0) { 
		delete ConfigIni;
		return false;
	}

	m_Edit_InputPath->setText(inPath);

	ConfigIni->setValue("/Last/InputPath", inPath);
	delete ConfigIni;
	return true;
}

bool DlgMain::OnClickBrowseOutputPath()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString path = ConfigIni->value("/Last/OutputPath","").toString();

	QString outPath = QFileDialog::getExistingDirectory(this,
		tr("选择输出目录"), 
		path);
	if(outPath.length() == 0) { 
		delete ConfigIni;
		return false;
	}

	m_Edit_OutputPath->setText(outPath);

	ConfigIni->setValue("/Last/OutputPath", outPath);
	delete ConfigIni;
	return true;
}

bool DlgMain::OnStartDateChanged()
{
	QSettings *ConfigIni = new QSettings(configFile, QSettings::IniFormat, 0);
	QString StartDate = ConfigIni->value("/Last/StartDate","").toString();

	ConfigIni->setValue("/Last/StartDate", m_DateEdit_StartDate->date().toString());

	delete ConfigIni;
	return true;
}


bool DlgMain::OnEndDateChanged()
{
	QSettings *ConfigIni = new QSettings(configFile,QSettings::IniFormat,0);
	QString EndDate = ConfigIni->value("/Last/EndDate","").toString();

	ConfigIni->setValue("/Last/EndDate", m_DateEdit_EndDate->date().toString());

	delete ConfigIni;
	return true;
}

bool DlgMain::comparePathRow(const MTLParser& d1, const MTLParser& d2)
{
	return d1.m_strPathRow < d2.m_strPathRow;
}

MTLParser DlgMain::Best(const vector<MTLParser>& allMTLParsers, const QDate& startDate, const QDate& endDate)
{
	int maxDateDistance = abs(startDate.daysTo(endDate));
	QDate midDate = startDate.addDays(maxDateDistance/2);
	float cloudThreshold = 0.05f;
	float cloudStep = 0.05f;
	int num = (int)allMTLParsers.size();
	while (cloudThreshold <= 1.0)
	{
		int bestIndex = -1;
		float bestDateDistance = maxDateDistance;

		for (int i = 0;i < num;++i)
		{
			if (allMTLParsers[i].CLOUD_COVER <= cloudThreshold)
			{
				double dateDistance =  abs(allMTLParsers[i].DATE_ACQUIRED.daysTo(midDate));
				if (dateDistance < bestDateDistance)
				{
					bestIndex = i;
					bestDateDistance = dateDistance;
				}
			}
		}
		if (bestIndex > -1)
		{
			return allMTLParsers[bestIndex];
		}
		cloudThreshold = cloudThreshold + cloudStep;
	}
	return allMTLParsers[0];
}

bool DlgMain::OnClickSearch()
{
	double maxCloud = QBeforeLast(m_ComboBox_MaxCloud->currentText(), '%').toDouble();
	vector<MTLParser> selectedMTLParsers;
	QStringList selectedMTLFiles;
	QString inputPath = m_Edit_InputPath->text();
	m_StartDate = m_DateEdit_StartDate->date();
	m_EndDate = m_DateEdit_EndDate->date();
	QStringList filter;
	QStringList MTLFiles;
	filter<<"*MTL.txt";
	FindFile(inputPath, filter, MTLFiles);
	int nFiles = (int)MTLFiles.size();
	if (nFiles < 1)
	{
#ifdef debug
		cout<<"no MTL files are found!"<<endl;
#endif
		return false;
	}

	vector<MTLParser> MTLParserList;
	for (int i = 0;i < nFiles;++i)
	{
		MTLParser psr;
		psr.parse(MTLFiles[i]);
		if (psr.DATE_ACQUIRED > m_StartDate && psr.DATE_ACQUIRED < m_EndDate)
		{
			MTLParserList.push_back(psr);
		}
	}
	nFiles = (int)MTLParserList.size();
	if (nFiles < 1)
	{
#ifdef debug
		cout<<"no MTL files are found!"<<endl;
#endif
		return false;
	}

	// 按Path Row排序
	std::sort(MTLParserList.begin(), MTLParserList.end(), comparePathRow);

	vector<MTLParser> MTLParserListTemp;
	MTLParserListTemp.push_back(MTLParserList[0]);
	QString currentPathRow = MTLParserList[0].m_strPathRow;
	for (int i = 1;i < nFiles;++i)
	{
		if (0 == MTLParserList[i].m_strPathRow.compare(currentPathRow))
		{
			MTLParserListTemp.push_back(MTLParserList[i]);
		}
		else
		{
			MTLParser bestMTL = Best(MTLParserListTemp, m_StartDate, m_EndDate);
			if (bestMTL.CLOUD_COVER <= maxCloud)
			{
				selectedMTLParsers.push_back(bestMTL);
				selectedMTLFiles.push_back(bestMTL.m_PathMTL);
			}

			MTLParserListTemp.clear();
			MTLParserListTemp.push_back(MTLParserList[i]);
		}
		currentPathRow = MTLParserListTemp.back().m_strPathRow;
	}
	MTLParser bestMTL = Best(MTLParserListTemp, m_StartDate, m_EndDate);
	if (bestMTL.CLOUD_COVER <= maxCloud)
	{
		selectedMTLParsers.push_back(bestMTL);
		selectedMTLFiles.push_back(bestMTL.m_PathMTL);
	}

	// 将挑选的数据写入日志文件
	QString outLogFile = QDir::toNativeSeparators(m_Edit_OutputPath->text() + QDir::separator() + logFile);
	FILE* pf;
	QString dateFormat("yyyy.MM.dd");
	fopen_s(&pf, outLogFile.toUtf8(), "w+");
	int nSelected = (int)selectedMTLParsers.size();
	fprintf(pf, "起始时间：%s\n", m_StartDate.toString(dateFormat).toUtf8().data());
	fprintf(pf, "截止时间：%s\n", m_EndDate.toString(dateFormat).toUtf8().data());
	fprintf(pf, "共挑选 %d 景\n", nSelected);
	for (int i = 0;i < nSelected;++i)
	{
		// 轨道号 日期 云量 路径
		fprintf(pf, "%s\t%s\t%lf\t%s\n", selectedMTLParsers[i].m_strPathRow.toUtf8().data(), selectedMTLParsers[i].DATE_ACQUIRED.toString(dateFormat).toUtf8().data(),
			selectedMTLParsers[i].CLOUD_COVER, selectedMTLParsers[i].m_PathMTL.toUtf8().data());
	}
	fclose(pf);
	//////////////////////////////////////////////////////////////////////////
	// 开始复制数据

	FileCopyProcessThread *fileCopyProcess = new FileCopyProcessThread;
	//m_progressListener = new DemConvertListener;

	//connect(m_progressListener,SIGNAL(updateProgress(double)),this,SLOT(OnUpdateProgress(double)));
	//connect(fileCopyProcess, SIGNAL(addLog(QString)),this,SLOT(OnAddLog(QString)));
	connect(fileCopyProcess, SIGNAL(taskProgress(double)),this,SLOT(OnTaskProgress(double)));
	//connect(fileCopyProcess, SIGNAL(newProgressListener()),this,SLOT(OnNewProgressListener()));
	//connect(fileCopyProcess, SIGNAL(releaseProgressListener()),this,SLOT(OnReleaseProgressListener()));
	connect(fileCopyProcess, SIGNAL(beginUI()),this,SLOT(lockUI()));
	connect(fileCopyProcess, SIGNAL(endUI()),this,SLOT(unlockUI()));


	//demListener->start();
	//demListener->demListener(demProcess->m_progressListener);//监视进度线程
	//demProcess->m_pDEMListenerThread = demListener;
	//double could = m_ComboBox_MaxCloud->currentText().toDouble();
	bool bOverWrite = false;
	if (Qt::CheckState::Checked == m_CheckBox_OverWrite->checkState())
	{
		bOverWrite = true;
	}
	fileCopyProcess->Process(selectedMTLFiles, m_Edit_OutputPath->text(), bOverWrite);	//数据处理线程


	return true;
}

void DlgMain::OnTaskProgress(double percentage)
{
	int progressValue = int(100*percentage+0.5);
	m_ProgressBar->setValue(progressValue);
}

void DlgMain:: setProgressBarVisible(bool bVisible/* = false*/)
{
	m_ProgressBar->setVisible(bVisible);
	mainLayout->update();
}
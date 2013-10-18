#ifndef DLG_MAIN_H
#define DLG_MAIN_H

#include <QDialog>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QStringList>
#include <QString>
#include <QMouseEvent>
#include <QPoint>
#include <QSettings>
#include <QMessageBox>
#include <QProgressBar>
#include <vector>
#include <QProgressDialog>
#include <QFileDialog>
#include <QThread> 
#include <QPoint> 
#include <QSettings>
#include <QDateEdit>
#include <QProgressBar>
#include <QCheckBox>
#include <QComboBox>
#include "qmutex.h"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "func.h"
#include "MTLParser.h"

class QProgressBar;
const QString configFile = "conf.ini";
const QString logFile = "file list.txt";

class DlgMain : public QDialog
{
	Q_OBJECT

signals:
	void notifyDEM(int);

	public slots:
		bool OnClickBrowseInputPath();
		bool OnClickBrowseOutputPath();

		bool OnStartDateChanged();
		bool OnEndDateChanged();

		bool OnClickSearch();

		void OnTaskProgress(double percentage);

		void lockUI() const
		{
			m_Button_InputBrowse->setDisabled(true);
			m_Button_OutputBrowse->setDisabled(true);
			m_Button_Search->setDisabled(true);
			m_DateEdit_StartDate->setDisabled(true);
			m_DateEdit_EndDate->setDisabled(true);
			m_ProgressBar->setVisible(true);
			mainLayout->update();
		}
		void unlockUI() const
		{
			m_Button_InputBrowse->setDisabled(false);
			m_Button_OutputBrowse->setDisabled(false);
			m_Button_Search->setDisabled(false);
			m_DateEdit_StartDate->setDisabled(false);
			m_DateEdit_EndDate->setDisabled(false);
			m_ProgressBar->setVisible(false);
			mainLayout->update();
		}

public:
	DlgMain();
	~DlgMain();
	void ReadLastDate();
	void SaveLastDate();
	void ReadLastPath();

	static bool comparePathRow(const MTLParser& d1, const MTLParser& d2);
	MTLParser Best(const vector<MTLParser>& allMTLParsers, const QDate& startDate, const QDate& endDate);

	void setProgressBarVisible(bool bVisible = false);

private:

	QLineEdit *m_Edit_InputPath;
	QLineEdit *m_Edit_OutputPath;
	QPushButton *m_Button_InputBrowse;
	QPushButton *m_Button_OutputBrowse;
	QPushButton *m_Button_Search;
	QDateEdit *m_DateEdit_StartDate;
	QDateEdit *m_DateEdit_EndDate;
	QCheckBox *m_CheckBox_OverWrite;
	QComboBox *m_ComboBox_MaxCloud;
	QProgressBar *m_ProgressBar;
	QVBoxLayout *mainLayout;
	

	QDate m_StartDate;
	QDate m_EndDate;

};

#endif // STARTBAR_H

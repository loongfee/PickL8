#ifndef MTL_PARSER_H
#define MTL_PARSER_H

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
class MTLParser
{
public:
	MTLParser(){};
	~MTLParser(){};

	bool parse(QString mtl_file);

	bool parseLine(QString strLine, QString strName, QString& strValue);
	QString m_PathMTL;
	QString m_strPathRow;

	QDate DATE_ACQUIRED;
	int WRS_PATH;
	int WRS_ROW;
	float CLOUD_COVER;
	int IMAGE_QUALITY_OLI;
	int IMAGE_QUALITY_TIRS;
	
	float CORNER_UL_LAT_PRODUCT;
	float CORNER_UL_LON_PRODUCT;
	float CORNER_UR_LAT_PRODUCT;
	float CORNER_UR_LON_PRODUCT;
	float CORNER_LL_LAT_PRODUCT;
	float CORNER_LL_LON_PRODUCT;
	float CORNER_LR_LAT_PRODUCT;
	float CORNER_LR_LON_PRODUCT;

};
#endif
#include "MTLParser.h"
#include <QTextStream>
#include "func.h"


bool MTLParser::parseLine(QString strLine, QString strName, QString& strValue)
{
	if (strLine.contains(strName))
	{
		strValue = QAfterLast(QAfterLast(strLine, '='), ' ');
		if (strValue.contains("\""))
		{
			strValue = QBeforeFirst(QAfterFirst(strValue, '"'), '"');
		}
		return true;
	}
	strValue = "";
	return false;
}

bool MTLParser::parse(QString mtl_file)
{
	QFile inputFile(mtl_file);
	if (inputFile.open(QIODevice::ReadOnly))
	{
		m_PathMTL = mtl_file;
		QTextStream in(&inputFile);
		while ( !in.atEnd() )
		{
			QString line = in.readLine();
			QString strValue;

			// DATE_ACQUIRED
			if (parseLine(line, "DATE_ACQUIRED", strValue))
			{
				int nYear = QBeforeFirst(strValue, '-').toInt();
				int nMonth = QBeforeLast(QAfterFirst(strValue, '-'), '-').toInt();
				int nDay = QAfterLast(strValue, '-').toInt();
				DATE_ACQUIRED.setDate(nYear, nMonth, nDay);
			}
			// WRS_PATH
			if (parseLine(line, "WRS_PATH", strValue))
			{
				WRS_PATH = strValue.toInt();
			}
			// WRS_ROW
			if (parseLine(line, "WRS_ROW", strValue))
			{
				WRS_ROW = strValue.toInt();
			}
			// CLOUD_COVER
			if (parseLine(line, "CLOUD_COVER", strValue))
			{
				CLOUD_COVER = strValue.toFloat();
			}
			// IMAGE_QUALITY_OLI
			if (parseLine(line, "IMAGE_QUALITY_OLI", strValue))
			{
				IMAGE_QUALITY_OLI = strValue.toInt();
			}
			// IMAGE_QUALITY_TIRS
			if (parseLine(line, "IMAGE_QUALITY_TIRS", strValue))
			{
				IMAGE_QUALITY_TIRS = strValue.toInt();
			}
			// CORNER_UL_LAT_PRODUCT
			if (parseLine(line, "CORNER_UL_LAT_PRODUCT", strValue))
			{
				CORNER_UL_LAT_PRODUCT = strValue.toFloat();
			}
			// CORNER_UL_LON_PRODUCT
			if (parseLine(line, "CORNER_UL_LON_PRODUCT", strValue))
			{
				CORNER_UL_LON_PRODUCT = strValue.toFloat();
			}
			// CORNER_UR_LAT_PRODUCT
			if (parseLine(line, "CORNER_UR_LAT_PRODUCT", strValue))
			{
				CORNER_UR_LAT_PRODUCT = strValue.toFloat();
			}
			// CORNER_UR_LON_PRODUCT
			if (parseLine(line, "CORNER_UR_LON_PRODUCT", strValue))
			{
				CORNER_UR_LON_PRODUCT = strValue.toFloat();
			}
			// CORNER_LL_LAT_PRODUCT
			if (parseLine(line, "CORNER_LL_LAT_PRODUCT", strValue))
			{
				CORNER_LL_LAT_PRODUCT = strValue.toFloat();
			}
			// CORNER_LL_LON_PRODUCT
			if (parseLine(line, "CORNER_LL_LON_PRODUCT", strValue))
			{
				CORNER_LL_LON_PRODUCT = strValue.toFloat();
			}
			// CORNER_LR_LAT_PRODUCT
			if (parseLine(line, "CORNER_LR_LAT_PRODUCT", strValue))
			{
				CORNER_LR_LAT_PRODUCT = strValue.toFloat();
			}
			// CORNER_LR_LON_PRODUCT
			if (parseLine(line, "CORNER_LR_LON_PRODUCT", strValue))
			{
				CORNER_LR_LON_PRODUCT = strValue.toFloat();
			}
		}
		inputFile.close();
		m_strPathRow = QString("%1%2").arg(WRS_PATH, 3, 10, QChar('0')).arg(WRS_ROW, 3, 10, QChar('0'));
		return true;
	}
#ifdef debug
	cout<<"failed to open file: "<<mtl_file<<endl;
#endif
	inputFile.close();
	return false;
}
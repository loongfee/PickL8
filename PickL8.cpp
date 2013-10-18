#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QSplashScreen>
#include <QTextCodec>
#include <QTimer>
#include <QFont>
#include <QTranslator>

#include <QtPlugin>
#include <QLibrary>

#include <iostream >

#include "DlgMain.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QString dir = QApplication::applicationDirPath();
	//设置可执行程序路径为当前工作路径
	QDir::setCurrent(dir);
	QApplication::addLibraryPath("./plugins");

	////1108
	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);

	QTextCodec::setCodecForTr(codec);
	////1108

	//QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));


	QTranslator oTranslator;
	oTranslator.load(":/qt_zh_CN"); // 注意此处字符串以“:/”开头，后接的字符串是刚才复制的qm文件的名字
	//QApplication oApp(argc, argv);
	app.installTranslator(&oTranslator);

	QFont font = QFont("Microsoft YaHei", 9);
	//QFont font = QFont("Times", 12);
	app.setFont(font);

	QPixmap pixmap("ceode.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	QTimer::singleShot(200, &splash, SLOT(close()));
	//splash.show();

	splash.showMessage("正在加载...",
		Qt::AlignRight | Qt::AlignTop, Qt::black);


	qApp->setApplicationName(QObject::tr("Landsat-8数据挑选"));
	qApp->setWindowIcon(QIcon("PickL8.ico"));
	//qApp->setApplicationName(appName);
	//qApp->setApplicationVersion(appVersion);


	DlgMain *dm = new DlgMain;
	dm->show();

	return app.exec();
}

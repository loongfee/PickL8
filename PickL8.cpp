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
	//���ÿ�ִ�г���·��Ϊ��ǰ����·��
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
	oTranslator.load(":/qt_zh_CN"); // ע��˴��ַ����ԡ�:/����ͷ����ӵ��ַ����ǸղŸ��Ƶ�qm�ļ�������
	//QApplication oApp(argc, argv);
	app.installTranslator(&oTranslator);

	QFont font = QFont("Microsoft YaHei", 9);
	//QFont font = QFont("Times", 12);
	app.setFont(font);

	QPixmap pixmap("ceode.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	QTimer::singleShot(200, &splash, SLOT(close()));
	//splash.show();

	splash.showMessage("���ڼ���...",
		Qt::AlignRight | Qt::AlignTop, Qt::black);


	qApp->setApplicationName(QObject::tr("Landsat-8������ѡ"));
	qApp->setWindowIcon(QIcon("PickL8.ico"));
	//qApp->setApplicationName(appName);
	//qApp->setApplicationVersion(appVersion);


	DlgMain *dm = new DlgMain;
	dm->show();

	return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>
#include "InstalationManager.hpp"
#include "ArchieveInstaller.hpp"
#include "IInstalationManager.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
	//responsible is more efficient but animations are too fast
	//QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	//auto updater = new upd::AppUpdater();
	//engine.rootContext()->setContextProperty("_AppUpdater", updater);
	engine.load("qrc:/AppUpdater.qml");
	//_sleep(10000);
	return app.exec();
}
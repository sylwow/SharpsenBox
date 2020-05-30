#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <unordered_map>
#include "IQmlObject.hpp"

// Backend class - registers all objects that will be exported to qml
namespace bc {
	class Backend {
	public:
		static Backend& getBakend();
		void init(QQmlApplicationEngine* eng);
		QObject* getObject(std::string name);

	private:
		Backend() {};
		~Backend();
		QQmlApplicationEngine* engine;
		void registerObjects();

		void registerObject(IQmlObject* object);

		std::unordered_map<std::string, QObject*> objects_;
	};
}
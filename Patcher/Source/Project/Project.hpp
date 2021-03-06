﻿#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <filesystem>
#include "IQmlObject.hpp"
#include "TreeModel.hpp"
#include "Packer.hpp"
#include<unordered_map>



namespace pr {

	class Project : public bc::IQmlObject {
		Q_OBJECT
	public:
		static Project& getObject() {
			static Project uc;
			return uc;
		}

		// implementation IQmlObject
		void update() override {};
		void init() override {};
		std::string getName() override { return TYPENAME(Project); };

		Q_PROPERTY(QString version WRITE setVer READ getVer);
		Q_PROPERTY(int numberOfPackets  READ  getPacketNmb NOTIFY nmbChanged);

		Q_INVOKABLE void setVer(QString str) {
			version_ = str;
		}

		Q_INVOKABLE int getPacketNmb() {
			return numberOFPacks;
		}

		Q_INVOKABLE QString getVer() {
			return version_;
		}

		Q_INVOKABLE void setGameDir(QString str) {
			AppDir_ = str.toStdString();
			auto& tree = dt::TreeModel::getObject();
			tree.setRoot(AppDir_);
			tree.init(false);
		}

		Q_INVOKABLE void setProjectDir(QString str) { projectDir = str.toStdString(); }
		Q_INVOKABLE void setGameName(QString str) { gameName = str.toStdString(); }
		Q_INVOKABLE void setProjectName(QString str) { projectName = str.toStdString(); }

		Q_INVOKABLE void setProjectPath(QString str) {
			projectPath = str;
			QFile file;
			//open LaunchBoxConfig file
			file.setFileName(projectPath);
			file.open(QIODevice::ReadOnly | QIODevice::Text);
			QString val = file.readAll();
			file.close();
			auto& ff = val.toStdString();
			d = QJsonDocument::fromJson(val.toUtf8());
			AppDir_ = d["AppDir"].toString().toStdString();
			auto& tree = dt::TreeModel::getObject();
			tree.getSetUpModel().setLoad(true);
			tree.setRoot(AppDir_);
			tree.init(false);
		}

		Q_INVOKABLE void setUpProject() { generate(); }
		Q_INVOKABLE void generatePatch() { save(); }
		void save();
		void generatePatchFile();
		void generate();
		void insertFileData(std::filesystem::path file);
		bool newProject() { return newProject_; }
		void insertData(dt::TreeItem* item, QJsonObject& object);
		void readPacket(dt::TreeItem* item, QJsonObject& object, dt::TreeItem* root, std::filesystem::path path);
		void verify(dt::TreeItem* item);
		Q_INVOKABLE void loadProject();
	signals:
		void verChanged();
		void nmbChanged();
	private:
		bool newProject_ = true;
		QFile file_;
		std::filesystem::path rootDir_;
		QJsonDocument doc_;
		QJsonObject* rootObject_;
		int packetId;

		QString version_;
		std::filesystem::path AppDir_;
		std::filesystem::path projectDir;
		QString projectPath;
		std::string gameName;
		std::string projectName;

		QJsonDocument d;
		bb::Packer packer_;
		int numberOFPacks = 0;
		QSet<QString> changed_;
		QSet<QString> deleted_;
		QSet<QString> added_;
	};
}

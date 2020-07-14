﻿#include <iostream>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <filesystem>

namespace gm {
	class GameUninstaller : public  QThread {
		Q_OBJECT
	public:
		void setId(int id);
		void run() override;
		virtual ~GameUninstaller() {};
		GameUninstaller() {};

	signals:
		void uninstalationComplete(int id);
	public slots:
	private:
		int id_;
		std::filesystem::path gameDir_;
		bool shortcut_;
		std::filesystem::path shortcutPath_;
	};
}
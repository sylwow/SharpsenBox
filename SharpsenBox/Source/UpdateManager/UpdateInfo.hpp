﻿#pragma once
#include <iostream>
#include <QObject>
#include <QThread>
#include <filesystem>
#include <atomic>
#include <unordered_map>
#include "IRunnable.hpp"
#include "Game.hpp"

namespace sb {
	struct AppPack;
}

namespace sb {
	class AbortException : public std::exception {};

	class UpdateInfo : public IRunnable {
	public:
		//class holind infomration about updating process
		using files = std::vector< AppPack >;
		enum UpdateMode : int { GAME = 0, SHARPSENBOX };

		UpdateInfo();
		~UpdateInfo() {}

		//getters setters
		UpdateMode getUpdateMode() { return updateMode_; }
		void setUpdateMode(UpdateMode mode) { updateMode_ = mode; }

		files& getFiles() { return files_; }
		void setFiles(const files& files) { files_ = files; }

		bool getFullInstall() { return fullInstall_; }
		void setFullInstall(const bool fullInstall) { fullInstall_ = fullInstall; }

		QString& getActualVersion() { return actualVersion_; }
		void setActualVersion(const QString& ver) { actualVersion_ = ver; }

		QString& getUpdateVersion() { return toUpdateVersion_; }
		void setUpdateVersion(const QString& ver) { toUpdateVersion_ = ver; }

		Game& getActualGame() { return actualGame_; }
		void setActualGame(Game& game) { actualGame_ = game; }
		void setActualGame(Game* game) { actualGame_ = *game; }

		QString& getDownloadDir() { return downloadDir_; }
		void setDownloadDir(const QString& dir) { downloadDir_ = dir; }

		QString& getInstallDir() { return installDir_; }
		void setInstallDir(const QString& dir) { installDir_ = dir; }

		bool isGameUppdating() { return getUpdateMode() == UpdateMode::GAME; }
		bool isLBUpdating() { return getUpdateMode() == UpdateMode::SHARPSENBOX; }

		void Reset() override;
		void Run() override {}

		//controlls 
		std::atomic_flag pause;
		std::atomic_flag resume;
		std::atomic_flag stop;
	private:
		UpdateMode updateMode_;
		bool cancel_;
		bool fullInstall_;

		files files_;
		QString actualVersion_;
		QString toUpdateVersion_;

		Game actualGame_;

		QString downloadDir_;
		QString installDir_;
	};
}

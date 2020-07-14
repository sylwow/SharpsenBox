﻿#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QNetworkAccessManager>
#include "IGameManager.hpp"

namespace gm {
	class GameUninstaller;
	class GameManager final : public IGameManager, bc::Get<IGameManager> {
		Q_OBJECT
	public:
		virtual ~GameManager() {};
		GameManager();

		// implementation IQmlComponent
		void update() final {};
		std::string getName() final;
		void init() final;

		// inferface
		void lock() final { lock_ = true; lockChanged(); }
		void unLock() final { lock_ = false; lockChanged(); }
		void uninstall(bool dialogValue) final;

		// Qml properties
		Q_PROPERTY(int lock READ getLock NOTIFY lockChanged);

		// QMl invokables
		Q_INVOKABLE void installGame(int id, QString path, bool shortcut);
		Q_INVOKABLE bool getLock() { return lock_; }
		Q_INVOKABLE void unistallRequest(int id);
		Q_INVOKABLE void checkAutoUpdate(int id);
		Q_INVOKABLE void update(int id);
		Q_INVOKABLE void runGame(int id);

	public slots:
		void uninstallation(int id);
	signals:
		void lockChanged();


	private:
		bool lock_ = false;
		int Gameid_;
		GameUninstaller* uninstaller_;
	};
}
﻿#pragma once
#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QNetworkAccessManager>
#include "IComponent.hpp"
#include <filesystem>
#include "ILoadingBar.hpp"
#include "IUpdateManager.hpp"

namespace lb {
	class LoadingBar final : public ILoadingBar {
		Q_OBJECT
	public:


		virtual ~LoadingBar();
		LoadingBar();

		// IQmlObject implementation
		void update() final;
		std::string getName() final;
		void init() final;

		void setTotal(double tot) final;
		void setActual(double act) final;
		void setProgress(double prog) final;
		void setSpeed(double sp) final;
		void setError(const QString& str) final;
		void setState(im::IUpdateManager::State st) final;
		void setVisibleState(im::IUpdateManager::VisibleState st) final;
		void setUninstallMode(bool un) final;
		void reset() final;
		//QML Propetries
		Q_PROPERTY(double speed READ getSpeed); //download speed B/s
		Q_PROPERTY(double actual READ getActual); //actual downloaded MB
		Q_PROPERTY(double total READ getTotal); // total MB to download
		Q_PROPERTY(double progress READ getProgress); // total MB to download

		Q_PROPERTY(int state READ getState NOTIFY stateChanged);
		Q_PROPERTY(int visibleState READ getVisibleState NOTIFY visibleStateChanged);

		Q_PROPERTY(int uninstall READ getUninstall);

		//QMl invoklabes
		Q_INVOKABLE double getSpeed() const;
		Q_INVOKABLE double getActual() const;
		Q_INVOKABLE double getTotal() const;
		Q_INVOKABLE double getProgress() const;

		Q_INVOKABLE int getState() const;
		Q_INVOKABLE int getVisibleState() const;

		Q_INVOKABLE bool getUninstall() const;

		Q_INVOKABLE void pause() const;
		Q_INVOKABLE void resume() const;
		Q_INVOKABLE void stop() const;


	signals:
		void stateChanged();
		void visibleStateChanged();

		void notifyEnded();
		void getProgress(qint64 actual);
	private:
		im::IUpdateManager::State state_ = im::IUpdateManager::State::NONE;
		im::IUpdateManager::VisibleState visibleState_ = im::IUpdateManager::VisibleState::HIDDEN;

		//synhronize mutex
		std::mutex mx_;
		//qml properties
		double progress_ = 0;
		double total_ = 0;
		double speed_ = 0;
		double actual_ = 0;

		bool uninstall_ = false;
	};
}
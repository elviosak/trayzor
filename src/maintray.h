#ifndef MAINTRAY_H
#define MAINTRAY_H

#include "traygroup.h"

#include <QApplication>
#include <QAction>
#include <QCheckBox>
#include <QDebug>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QIcon>
#include <QMainWindow>
#include <QMap>
#include <QPainter>
#include <QPushButton>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QX11Info>

#include <KWindowSystem>
#include <NETWM>

class MainTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    MainTray(QApplication * application);
    ~MainTray();
    QApplication * app;
    QWidget * win;
    QFormLayout * fCurrent = new QFormLayout();
    QFormLayout * fFilter = new QFormLayout();

    QSettings * pinned;
    QSettings * filter;
    QStringList filterGroup;
private:
    QMap<QString, TrayGroup*> groupList;
    QMap<WId, QString> windowList;
public slots:
    void initWindows();
    void initConnections();
    void iconClicked(QSystemTrayIcon::ActivationReason reason);
    void closedWidget();
    void showSettingsBox();
    void reloadSettings();
    void reloadWindows();
    void removeGroup(QString cl);
    void setMainIcon();
    void clickGlobal();
    void onWindowAdded(WId w);
    void onWindowRemoved(WId w);
    void onActiveWindowChanged(WId w);
    bool acceptWindow(WId window) const;
    void onWindowChanged(WId w, NET::Properties prop,NET::Properties2 prop2);

    void togglePin(bool checked, QString cl);
    void removeFilter(QString cl);
    void setFilter(QString cl);
};
#endif // MAINTRAY_H

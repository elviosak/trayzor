#ifndef TRAYGROUP_H
#define TRAYGROUP_H

#include <QBitmap>

#include <QAction>
#include <QEvent>
#include <QFile>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QMap>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QProcess>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QX11Info>

#include <KWindowSystem>
#include <NETWM>

#include <QDebug>

class TrayGroup : public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayGroup(QSettings *s, QString c, WId w);
    QSystemTrayIcon * self;
    int count;
    QSettings * settings;
    QString className;
    QIcon currentIcon;
    QIcon iconNormal;
    QIcon iconDisabled;
    QIcon iconActive;
    QMenu * menu;
    QMap<WId, QAction*> actionList;
    QList<WId> list;
    QString path;
    bool pinned = false;
private:

public slots:
    void drawBadge();
    void setCurrentIcon(QIcon ico);
    void addWindow(WId w);
    bool removeWindow(WId w);
    void changeActiveWindow(WId w);
    void updatePath(QString p);
    void updateWindow(WId w);
    void raiseWindow(WId w);
    void loadPinned();
    void pinAction();
    void unpinAction();
    void updateMenu();
    void drawActiveIcon();
    void assignIcon(WId w);
    void setPath(WId w);
    QIcon getWindowIcon(WId w);
    QString getWindowTitle(WId w);
    QAction* createAction(WId w, QMenu * menu = nullptr);
    void iconClicked(QSystemTrayIcon::ActivationReason reason);
    void clickedWindow(WId w);
    void activateWindow(WId w);
    void restoreWindow(WId w);
    void minimizeWindow(WId w);
    void closeWindow(WId w);
    bool event(QEvent* ev) override;

private slots:


};

#endif // TRAYGROUP_H

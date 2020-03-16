#include "maintray.h"

MainTray::~MainTray(){
}

MainTray::MainTray(QApplication * application)
    : QSystemTrayIcon(),
      app(application)
{
    setMainIcon();
    app->setWindowIcon(QIcon(":/trayzor.svg"));
    QMenu * menu = new QMenu();
    QAction * a;
    a = menu->addAction(icon(), "Show Config");
    connect(a, &QAction::triggered, this, &MainTray::showSettingsBox);
    a = menu->addAction(QIcon::fromTheme("reload"), "Reload All");
    connect(a, &QAction::triggered, this, &MainTray::reloadWindows);
    a = menu->addAction(QIcon::fromTheme("window-close"), "Close");
    connect(a, &QAction::triggered, this, [=](){
        app->exit();
    });
    setContextMenu(menu);
//     |= NET::DesktopMask;
//     |= NET::DockMask;
//     |= NET::SplashMask;
//     |= NET::ToolbarMask;
//     |= NET::MenuMask;
//     |= NET::PopupMenuMask;
//     |= NET::NotificationMask;
    win = new QWidget(nullptr, Qt::Widget | Qt::WindowStaysOnTopHint | Qt::Dialog);// | Qt::SplashScreen);
    win->setAttribute(Qt::WA_DeleteOnClose, false);
    win->setAttribute(Qt::WA_QuitOnClose, false);
    QHBoxLayout * hbox = new QHBoxLayout(win);
    win->setLayout(hbox);
    //hbox->setSpacing(20);
    QLabel * lbl = new QLabel("Window List");
    QFont font = lbl->font();
    font.setBold(true);
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter);
    fCurrent->addRow(lbl);
    hbox->addLayout(fCurrent, 5);
    hbox->addSpacing(20);
    lbl = new QLabel("Filter List");
    lbl->setFont(font);
    lbl->setAlignment(Qt::AlignHCenter);
    fFilter->addRow(lbl);
    hbox->addLayout(fFilter, 2);

    initWindows();
    initConnections();
}



void MainTray::setMainIcon(){
    QPixmap pix =  QIcon(":/trayzor-settings.svg").pixmap(128);
    QPixmap base(128,128);
    base.fill(QColor(Qt::GlobalColor::transparent));
    QPainter painter;
    painter.begin(&base);
    painter.setOpacity(0.5);
    painter.drawPixmap(0,0,pix);
    painter.end();
    //base.setMask(pix.createMaskFromColor( Qt::transparent ));
    //setIcon(QIcon(":/trayzor-settings.svg"));
    setIcon(base);
    show();
}
void MainTray::initWindows(){
    pinned = new QSettings("trayzor", "pinned");
    filter = new QSettings("trayzor", "filter");
    filterGroup = filter->childKeys();
    QStringList pinnedGroup = pinned->childGroups();
    foreach (const QString cl, pinnedGroup) {
        if(!groupList.contains(cl)){
            groupList[cl] = new TrayGroup(pinned, cl, 0);
            groupList[cl]->show();
        }
    }
}
void MainTray::initConnections(){
    connect(this, &QSystemTrayIcon::activated,this, &MainTray::iconClicked);
    connect(KWindowSystem::self(), &KWindowSystem::windowAdded,this, &MainTray::onWindowAdded);
    connect(KWindowSystem::self(), &KWindowSystem::windowRemoved,this, &MainTray::onWindowRemoved);
    connect(KWindowSystem::self(), static_cast<void (KWindowSystem::*)(WId, NET::Properties,                    NET::Properties2)>(&KWindowSystem::windowChanged), this, &MainTray::onWindowChanged);
}
void MainTray::clickGlobal(){
    qDebug()<< "clickGlobal";
    iconClicked(QSystemTrayIcon::Trigger);
}
void MainTray::iconClicked(QSystemTrayIcon::ActivationReason reason){
    qDebug() <<"clicked" << reason;
    if (reason == QSystemTrayIcon::MiddleClick){

    }
    if (reason == QSystemTrayIcon::Trigger){
        if(win->isVisible()){
            win->close();
        }else{
            showSettingsBox();
        }
    }
}
void MainTray::closedWidget(){
    qDebug() << "closedWidget";

}
void MainTray::showSettingsBox(){
    while (fCurrent->count()>1) {
        fCurrent->removeRow(1);
    }
    while (fFilter->count()>1) {
        fFilter->removeRow(1);
    }
    QStringList pinnedGroup = pinned->childGroups();

    filterGroup = filter->childKeys();
    for (auto i = groupList.cbegin();i != groupList.cend();++i){
        QString cl = i.key();
        if(!filterGroup.contains(cl)){
            TrayGroup * tray = i.value();
            auto hbox = new QHBoxLayout();
            auto txt = new QLineEdit(tray->path);
            if (!pinnedGroup.contains(cl))
                txt->setEnabled(false);
            auto btns = new QHBoxLayout();
            QCheckBox * check = new QCheckBox("Pin");
            if (pinnedGroup.contains(cl))
                check->setChecked(true);
            connect(check, &QCheckBox::clicked,this,[=](bool checked){
               togglePin(checked, cl);
               showSettingsBox();
            });
            btns->addWidget(check);
            QPushButton * btn;
            if (pinnedGroup.contains(cl)){
                btn = new QPushButton("Save Path");
                connect(btn, &QPushButton::clicked,this, [=](){
                    if(groupList.contains(cl)){
                        groupList[cl]->updatePath(txt->text().trimmed());
                    };
                    showSettingsBox();
                });
            }
            else{
                btn = new QPushButton("Filter");
                connect(btn, &QPushButton::clicked,this, [=](){
                    setFilter(cl);
                    showSettingsBox();
                });
            }
            btns->addWidget(btn);
            hbox->addWidget(txt);
            hbox->addLayout(btns);
            if(pinnedGroup.contains(cl)){
                fCurrent->insertRow(pinnedGroup.indexOf(cl) + 1,cl, hbox);
            }
            else {
                fCurrent->addRow(cl, hbox);
            }

        }

    }
    foreach (const QString cl, filterGroup) {
        auto btn = new QPushButton("Remove");
        connect(btn, &QPushButton::clicked, this, [=](){
            removeFilter(cl);
            showSettingsBox();
        });
        fFilter->addRow(cl, btn);
    }
    win->resize(800, 100);
    win->show();
}
void MainTray::togglePin(bool checked, QString cl){
    if(checked){
        if(groupList.contains(cl)){
            groupList[cl]->pinAction();
        }
    }else{
        if(groupList.contains(cl)){
            groupList[cl]->unpinAction();
        }
    }
}

void MainTray::removeFilter(QString cl){
    filter->remove(cl);
    filterGroup.removeAll(cl);
    if(groupList.contains(cl))
        groupList[cl]->show();
}

void MainTray::setFilter(QString cl){
    filter->setValue(cl, true);
    filterGroup.append(cl);
    if(groupList.contains(cl))
        groupList[cl]->hide();
}

void MainTray::reloadSettings(){

}
void MainTray::reloadWindows(){
    QList<WId> windows = KWindowSystem::windows();
    disconnect();
    auto i = groupList.begin();
    while (i != groupList.end()) {
        i.value()->~TrayGroup();
        groupList.erase(i);
        i = groupList.begin();
    }
    auto j = windowList.begin();
    while ( j != windowList.end()) {
        windowList.erase(j);
        j = windowList.begin();
    }
    hide();
    show();
    initWindows();
    initConnections();
    foreach (const WId w, windows) {
        onWindowAdded(w);
    }
}


void MainTray::onWindowChanged(WId w, NET::Properties prop, NET::Properties2 prop2)
{
    QString cl = QString::fromUtf8(KWindowInfo(w, nullptr, NET::WM2WindowClass).windowClassClass()).toLower();
    if(groupList.contains(cl)){
        //groupList[cl]->removeWindow(w);
        if (prop == NET::WMName || prop == NET::WMVisibleName || prop == NET::WMState){
            if(groupList.contains(cl)){
                groupList[cl]->updateWindow(w);
            }
        }
        else if(prop == NET::ActiveWindow)
        {
            qDebug()<<"active" << w << cl;
        }
        else{
            qDebug()<<"else" << w << "|" << prop2;
            //qDebug()<<static_cast<int>(prop);
            //qDebug()<<static_cast<int>(prop2);
        }
    }

}

void MainTray::onWindowAdded(WId w)
{
    const QString cl = QString::fromUtf8(KWindowInfo(w, nullptr, NET::WM2WindowClass).windowClassClass()).toLower();
    if(acceptWindow(w)){
        windowList[w] = cl;
        TrayGroup * tray;
        if(groupList.contains(cl)){
            tray = groupList[cl];
        }
        else {
            tray = new TrayGroup(pinned, cl, w);
            groupList[cl] = tray;
        }
        tray->addWindow(w);
        if(filterGroup.contains(cl)){
            tray->hide();
        }else {
            tray->show();
        }
    }else {
        qDebug() << "not accepted" << w << cl;
    }
}

void MainTray::onWindowRemoved(WId w)
{
    if(windowList.contains(w)){
        QString cl = windowList[w];
        qDebug()<<"onwindowremoved" << cl <<groupList.contains(cl)<< w;
        if(groupList.contains(cl)){
            if (groupList[cl]->removeWindow(w)){
                groupList[cl]->~TrayGroup();
                groupList.remove(cl);
            }
        }
        windowList.remove(w);
    }
}
void MainTray::onActiveWindowChanged(WId w){
    if(windowList.contains(w)){
        QString cl = windowList[w];
        qDebug()<<"onActiveWindowChanged" << cl <<groupList.contains(cl)<< w;
        if(groupList.contains(cl)){
            groupList[cl]->changeActiveWindow(w);
        }
    }
}
void MainTray::removeGroup(QString cl){
    if(groupList.contains(cl)){
        groupList.remove(cl);
    }
}
bool MainTray::acceptWindow(WId window) const
{
    if(windowList.contains(window)){
        return false;
    }
    QFlags<NET::WindowTypeMask> ignoreList;
    ignoreList |= NET::DesktopMask;
    ignoreList |= NET::DockMask;
    ignoreList |= NET::SplashMask;
    ignoreList |= NET::ToolbarMask;
    ignoreList |= NET::MenuMask;
    ignoreList |= NET::PopupMenuMask;
    ignoreList |= NET::NotificationMask;

    KWindowInfo info(window, NET::WMWindowType | NET::WMState, NET::WM2TransientFor);
    if (!info.valid())
        return false;

    if (NET::typeMatchesMask(info.windowType(NET::AllTypesMask), ignoreList))
        return false;

    if (info.state() & NET::SkipTaskbar)
        return false;

    // WM_TRANSIENT_FOR hint not set - normal window
    WId transFor = info.transientFor();
    if (transFor == 0 || transFor == window || transFor == static_cast<WId>(QX11Info::appRootWindow()))
        return true;

    info = KWindowInfo(transFor, NET::WMWindowType);

    QFlags<NET::WindowTypeMask> normalFlag;
    normalFlag |= NET::NormalMask;
    normalFlag |= NET::DialogMask;
    normalFlag |= NET::UtilityMask;
    return !NET::typeMatchesMask(info.windowType(NET::AllTypesMask), normalFlag);
}


#include "traygroup.h"

TrayGroup::TrayGroup(QSettings *s, QString c, WId w):
    QSystemTrayIcon()
{
    settings = s;
    count = 0;
    className = c;
    setObjectName(className);
    qDebug()<< "created class" << className;
    if (w!=0){
        addWindow(w);
    }else {
        loadPinned();
    }

    menu = new QMenu();
    updateMenu();
    connect(menu, &QMenu::aboutToShow, this, &TrayGroup::updateMenu);
    setContextMenu(menu);
    setToolTip(className);

    connect(this, &QSystemTrayIcon::activated,this, &TrayGroup::iconClicked);
    connect(KWindowSystem::self(), &KWindowSystem::activeWindowChanged,this, &TrayGroup::changeActiveWindow);
}


void TrayGroup::addWindow(WId w){
    if(list.isEmpty()){
        setPath(w);
        assignIcon(w);
    }else{
        qDebug()<< "not empty";
    }
    if(!list.contains(w))
        list.prepend(w);
    count = list.size();
    setCurrentIcon(iconNormal);
    //updateMenu();
    qDebug()<<"addwindow"<<className<<count;
}

bool TrayGroup::removeWindow(WId w){
    bool removed = false;
    if (w == 0)
        return removed;
    qDebug()<<"removeWindow"<<className<< w;
    if(list.contains(w)){
        list.removeAll(w);
        qDebug()<<"contains"<<className<< w;
        count = list.size();
        if(count ==0 ){
            if(pinned){
                setCurrentIcon(iconDisabled);
            }else{
                removed = true;
            }
        }
        drawBadge();
    }
    if(removed)
        deleteLater();
    return removed;
}

void TrayGroup::iconClicked(QSystemTrayIcon::ActivationReason reason){
    qDebug() <<"iconClicked, path:" <<path << reason;
    if (reason == QSystemTrayIcon::MiddleClick && path != ""){
        QProcess::startDetached(path);
    }
    if (reason == QSystemTrayIcon::Trigger){
        if (count ==0 && pinned == true && path != ""){
            QProcess::startDetached(path);
        }
        else if (count == 1 ) {
            clickedWindow(list.first());
        }else if (list.first()==KWindowSystem::activeWindow() && count > 1) {
            restoreWindow(list.at(1));
        }
        else {
            restoreWindow(list.first());
        }
    }
}
void TrayGroup::clickedWindow(WId w){
    activateWindow(w);
}
void TrayGroup::activateWindow(WId w){
    KWindowInfo info(w, NET::WMDesktop);
    if (!info.isOnCurrentDesktop()){
        KWindowSystem::setCurrentDesktop(info.desktop());
    }
    if(KWindowSystem::activeWindow()==w){
        qDebug()<<"active";
        if (KWindowInfo(w, NET::WMState).isMinimized()){
           restoreWindow(w);
        }else{
            minimizeWindow(w);
        }
    }
    else {
        restoreWindow(w);
    }
}
void TrayGroup::restoreWindow(WId w){
    KWindowInfo info(w, NET::WMDesktop);
    if (!info.isOnCurrentDesktop()){
        KWindowSystem::setCurrentDesktop(info.desktop());
    }
    KWindowSystem::forceActiveWindow(w);
    KWindowSystem::unminimizeWindow(w);
}
void TrayGroup::minimizeWindow(WId w){
    KWindowSystem::minimizeWindow(w);
}
void TrayGroup::closeWindow(WId w){
    NETRootInfo(QX11Info::connection(), NET::CloseWindow)
            .closeWindowRequest(static_cast<xcb_window_t>(w));
}
void TrayGroup::updatePath(QString p){
    path = p;
    if(pinned){
        settings->setValue(className+"/path", path);
    }
}
void TrayGroup::updateWindow(WId w){
    if(!list.contains(w)){
        list.append(w);
    }
}
void TrayGroup::raiseWindow(WId w){
    KWindowSystem::raiseWindow(w);
}
QAction* TrayGroup::createAction(WId w, QMenu * menu){
    QIcon i = KWindowInfo(w, NET::WMState).isMinimized() ? iconDisabled : iconNormal;
    QString name = KWindowInfo(w, NET::WMVisibleName).visibleName();
    if(name.length()>50 ){
        name.truncate(50);
        name.append("...");
    }
    return new QAction(i, name , menu);
}
void TrayGroup::pinAction(){
    settings->setValue(className + "/path", path);
    settings->setValue(className + "/icon", iconNormal);
    pinned = true;
}
void TrayGroup::unpinAction(){
    settings->remove(className);
    pinned = false;
    if(list.count()==0)
        deleteLater();
}
void TrayGroup::loadPinned(){
    iconNormal = qvariant_cast<QIcon>(settings->value(className + "/icon"));
    path = settings->value(className + "/path").toString();
    assignIcon(0);
    //setCurrentIcon(iconDisabled);
    pinned = true;
}
QIcon TrayGroup::getWindowIcon(WId w){
    return KWindowInfo(w, NET::WMState).isMinimized() ? iconDisabled : iconNormal;
}
QString TrayGroup::getWindowTitle(WId w){
    QString name = KWindowInfo(w, NET::WMVisibleName).visibleName();
    if(name.length()>50 ){
        name.truncate(50);
        name.append("...");
    }
    return  name;
}
void TrayGroup::updateMenu(){
    qDebug()<<"updateMenuBegin"<<className << "pinned" << pinned;
    menu->clear();
    QAction * a;
    if(path != ""){
        a = menu->addAction(QIcon::fromTheme("window-new", QIcon::fromTheme("add")),"New: " + path);
        connect(a, &QAction::triggered, this, [=]() { QProcess::startDetached(path); });
        if(pinned){
            a = menu->addAction(QIcon::fromTheme("bookmark-remove", QIcon::fromTheme("remove")),"Unpin");
            connect(a, &QAction::triggered, this,&TrayGroup::unpinAction);
        }
        else {
            a = menu->addAction(QIcon::fromTheme("bookmark-new"),"Pin");
            connect(a, &QAction::triggered, this,&TrayGroup::pinAction);
        }
        menu->addSeparator();
    }
    //for (int i = 0; i < list.size(); ++i){
    for (int i = list.size() - 1; i >= 0; --i){
        WId w = list.at(i);
        if(KWindowSystem::hasWId(w)){
            a = menu->addAction(getWindowIcon(w), getWindowTitle(w));
            connect(a, &QAction::triggered, this, [=]() { TrayGroup::restoreWindow(w); });
            connect(a, &QAction::hovered, this, [=]() { TrayGroup::raiseWindow(w); });
            if(i == 0){
                a = menu->addAction(QIcon::fromTheme("window-close"), "Close");
                connect(a, &QAction::triggered, this, [=]() { TrayGroup::closeWindow(w); });                
            }
            menu->addSeparator();
        }
    }
}
void TrayGroup::changeActiveWindow(WId w){
    if(list.contains(w)){
        if(!iconActive.isNull()){
            setCurrentIcon(iconActive);
            KWindowSystem::raiseWindow(w);
        }
        while(list.first() != w)
            list.append(list.takeAt(0));
    }else if(count) {
        setCurrentIcon(iconNormal);
    }
    drawBadge();

}
void TrayGroup::drawBadge(){
    QIcon ico = QIcon(currentIcon);
    if(count>1){
        QPixmap pix = ico.pixmap(128);
        int height = pix.height();
        QPainter painter;;
        painter.begin(&pix);
        painter.setRenderHint(QPainter::Antialiasing);
        QFont font = painter.font();
        int fontSize = height*2/5;
        font.setPixelSize(fontSize);
        font.setBold(true);
        painter.setFont(font);
        int rectHeight = height/2;
        const QRect r = QRect(0, 0, rectHeight , rectHeight);
        QPainterPath path;
        path.addRoundRect(r, 50, 50);
        painter.fillPath(path, QBrush(Qt::GlobalColor::darkMagenta));
        painter.setPen(QPen(Qt::GlobalColor::white));
        painter.drawText(r, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(count));
        painter.end();
        ico = QIcon(pix);
        this->setIcon(ico);
    }else if (count ==1 ) {
        this->setIcon(ico);
    } else {
        this->setIcon(iconDisabled);
    }
}
void TrayGroup::drawActiveIcon(){
    QIcon ico = QIcon(iconNormal);
    QPixmap pix = ico.pixmap(128);
    int height = pix.height();
    int width = pix.width();
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHint(QPainter::Antialiasing);
    int rectHeight = height/3;
    int rectWidth = width/3;
    int yoffset = width - rectWidth;
    const QRect r = QRect(yoffset, 0, rectWidth , rectHeight);
    QPainterPath path;
    path.addRoundRect(r, 100, 100);
    painter.fillPath(path, QBrush(Qt::GlobalColor::darkMagenta));
    painter.end();
    iconActive = QIcon(pix);
}

void TrayGroup::assignIcon(WId w){
    qDebug()<< "assignIcon" <<className;
    QIcon ico;
    if( w != 0){
        ico = KWindowSystem::icon(w);
            if(ico.isNull()){
                ico = QIcon::fromTheme(className);
                qDebug()<< "from theme";
            }
            else{
                if(ico.isNull()){
                    qDebug()<< "null icon";
                }else {
                    qDebug()<< "from kwin";
                }
            }
    }else {
        ico = iconNormal;
    }
    if(ico.isNull()){
        ico = QIcon::fromTheme("application-default-icon");
    }
    QPixmap pix = ico.pixmap(128,QIcon::Normal);
    pix = pix.scaled(128,128);
    iconNormal = QIcon(pix);

    //QPixmap pixDisabled = iconNormal.pixmap(128, QIcon::Disabled);
    QPixmap pixDisabled = QPixmap(pix.size());
    pixDisabled.fill(QColor(Qt::GlobalColor::transparent));
    QPainter painter;
    painter.setRenderHint( QPainter::Antialiasing);
    painter.begin(&pixDisabled);
    painter.setOpacity(0.6);
    painter.drawPixmap(0, 0, pix);
    painter.end();

   // iconDisabled = QIcon(iconNormal.pixmap(128,QIcon::Disabled));
    iconDisabled = QIcon(pixDisabled);
    drawActiveIcon();
    if(list.size()>0){
        setCurrentIcon(iconNormal);
    }else {
        setCurrentIcon(iconDisabled);
    }
}
void TrayGroup::setCurrentIcon(QIcon ico){
    currentIcon = QIcon(ico);
    drawBadge();
    //show();
}
void TrayGroup::setPath(WId w){
    qDebug()<<"set path";
    if(path==""){
        int pid = KWindowInfo(w, NET::WMPid).pid();
        qDebug()<< "pid" <<pid;
        QString sym = "/proc/";
        sym += QString::number(pid);
        sym += "/exe";
        path = QFile::symLinkTarget(sym);
        qDebug()<<"set" <<sym<<path;
    }
}

bool TrayGroup::event(QEvent * ev){
    if(ev->type()== QEvent::ToolTip && list.size()>0){
        qDebug() << "event" << ev->type();
        KWindowSystem::raiseWindow(list.first());
    }
    return true;
}

#include "menucontroller.h"
#include "views/global.h"
#include "dbuscontroller.h"

MenuController::MenuController(QObject *parent) : QObject(parent)
{
    m_menuManagerInterface = new MenumanagerInterface(MenuManager_service, MenuManager_path, QDBusConnection::sessionBus());
    initConnect();
}


void MenuController::initConnect(){
    connect(signalManager, SIGNAL(contextMenuShowed(QList<DesktopItemPointer>,DesktopItemPointer,QPoint)),
            this, SLOT(showMenuByDesktopItem(QList<DesktopItemPointer>,DesktopItemPointer,QPoint)));
    connect(signalManager, SIGNAL(contextMenuShowed(DesktopItemPointer,QPoint)), this, SLOT(showMenuByDesktopItem(DesktopItemPointer,QPoint)));
}

MenuController::~MenuController()
{
}

void MenuController::showMenuByDesktopItem(DesktopItemPointer pItem, QPoint pos){
    QStringList iconurl;
    if (!pItem.isNull()) {
        iconurl = QStringList(pItem->getUrl());
    }
    QString menucontent = createMenuContent(iconurl);
    QString menucontentfinal = JsonToQString(pos, menucontent);
    QString menucreatepath = registerMenu();
    if (menucreatepath.length() > 0){
        showMenu(menucreatepath, menucontentfinal);
    }else{
        qDebug() << "register menu fail!";
    }
}


void MenuController::showMenuByDesktopItem(const QList<DesktopItemPointer> &pCheckItems,
                                           const DesktopItemPointer &pItem, QPoint pos){
    qDebug() << pCheckItems << pItem << pos;
}

QString MenuController::createMenuContent(QStringList createmenupath) {
    QDBusPendingReply<QString> menu_content_reply = DBusController::instance()->getDesktopDaemonInterface()->GenMenuContent(createmenupath);
    menu_content_reply.waitForFinished();
    if (!menu_content_reply.isError()){
        QString menu_content = menu_content_reply.argumentAt(0).toString();
        return menu_content;
    } else {
        return "";
    }
}

QString MenuController::JsonToQString(QPoint pos, QString menucontent) {
    QJsonObject menuObj
    {
        {"x", pos.x()},
        {"y", pos.y()},
        {"isDockMenu", false},
        {"menuJsonContent", menucontent}
    };
    return QString(QJsonDocument(menuObj).toJson());
}

QString MenuController::registerMenu() {
    QDBusPendingReply<QDBusObjectPath> menu_register_reply = m_menuManagerInterface->RegisterMenu();
    menu_register_reply.waitForFinished();
    if (!menu_register_reply.isError()) {
        return menu_register_reply.value().path();
    } else {
        return "";
    }
}

void MenuController::showMenu(const QString showmenu_path, QString menucontent) {
    m_showmenuInterface = new ShowmenuInterface(MenuManager_service, showmenu_path, QDBusConnection::sessionBus());
    m_showmenuInterface->ShowMenu(menucontent);
    connect(m_showmenuInterface, SIGNAL(ItemInvoked(QString, bool)),this, SLOT(menuItemInvoked(QString,bool)));
    connect(m_showmenuInterface, SIGNAL(MenuUnregistered()), DBusController::instance()->getDesktopDaemonInterface(), SLOT(DestroyMenu()));
}

void MenuController::menuItemInvoked(QString itemId, bool flag){
    Q_UNUSED(flag)
    DBusController::instance()->getDesktopDaemonInterface()->HandleSelectedMenuItem(itemId);
}

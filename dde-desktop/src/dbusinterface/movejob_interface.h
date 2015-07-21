/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -N -p movejob_interface.h:movejob_interface.cpp -c MoveJobInterface movejob.xml
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef MOVEJOB_INTERFACE_H_1437460613
#define MOVEJOB_INTERFACE_H_1437460613

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.deepin.filemanager.Backend.Operations.MoveJob
 */
class MoveJobInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.deepin.filemanager.Backend.Operations.MoveJob"; }

public:
    MoveJobInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~MoveJobInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Abort()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Abort"), argumentList);
    }

    inline QDBusPendingReply<> Execute()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Execute"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void Aborted();
    void Done();
    void Moving(const QString &in0);
    void ProcessedAmount(qulonglong in0, ushort in1);
};

#endif

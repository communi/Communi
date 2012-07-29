/*
* Copyright (C) 2008-2012 J-P Nurmi <jpnurmi@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef MESSAGEVIEW_H
#define MESSAGEVIEW_H

#include "ui_messageview.h"
#include "messagereceiver.h"
#include "messageformatter.h"
#include "commandparser.h"
#include "settings.h"

class IrcMessage;
class UserModel;
class Session;

class MessageView : public QWidget, public MessageReceiver
{
    Q_OBJECT

public:
    MessageView(const QString& receiver, Session* session, QWidget* parent = 0);
    ~MessageView();

    bool isServerView() const;
    bool isChannelView() const;

public slots:
    void showHelp(const QString& text, bool error = false);
    void appendMessage(const QString& message);
    void applySettings(const Settings& settings);

signals:
    void highlight(MessageView* view, bool on);
    void alert(MessageView* view, bool on);
    void query(const QString& user);

protected:
    bool eventFilter(QObject* receiver, QEvent* event);

    void receiveMessage(IrcMessage* message);
    bool hasUser(const QString& user) const;
    void addUser(const QString& user);
    void addUsers(const QStringList& users);
    void removeUser(const QString& user);
    void clearUsers();
    void renameUser(const QString &from, const QString &to);
    void setUserMode(const QString& user, const QString& mode);

private slots:
    void onEscPressed();
    void onSend(const QString& text);
    void onCustomCommand(const QString& command, const QStringList& params);
    void onDoubleClicked(const QModelIndex& index);

private:
    struct MessageViewData : public Ui::MessageView
    {
        bool connecting;
        bool joining;
        Session* session;
        CommandParser parser;
        MessageFormatter formatter;
        UserModel* userModel;
        Settings settings;
    } d;
};

#endif // MESSAGEVIEW_H
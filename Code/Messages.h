#ifndef MESSAGES_H
#define MESSAGES_H

#include <QString>


enum MessageType
{
    MESSAGE_INFO, MESSAGE_WARNING, MESSAGE_ERROR
};

enum MessageValue
{
    MSG_DELETE_ROW, MSG_CANNOT_DELETE_ROW
};

void showMessage(MessageValue msg, const QString& extendedText = "");
void showMessage(MessageType type, const QString& text);

#endif

#include "Messages.h"

#include <utility>
#include <QMessageBox>

typedef std::pair <MessageType, QString> Information;

Information getInformation(MessageValue msg, const QString& extendedText)
{
    Information info;
    info.first = MESSAGE_INFO;

    switch (msg)
    {
        case MSG_DELETE_ROW:
        info.second = "Current row has been deleted.";
        break;
        case MSG_CANNOT_DELETE_ROW:
        info.first = MESSAGE_WARNING;
        info.second = "Current row could not be deleted.";
        break;
    }
    return info;
}

void showMessage(MessageValue msg, const QString& extendedText)
{
    Information info = getInformation(msg, extendedText);
    showMessage(info.first, info.second);
}

void showMessage(MessageType type, const QString& text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    switch (type)
    {
        case MESSAGE_INFO:
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Information");
        msgBox.exec();
        break;
        case MESSAGE_WARNING:
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
        msgBox.exec();
        break;
        case MESSAGE_ERROR:
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        break;
    }
}

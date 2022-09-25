#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <Class/Currencies.h>

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    QStringList m_list;
    Currencies::Rates m_rates;

private slots:
    void setting();
    void download();
    void filter(int index);
};

#endif

#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"

#include <QFileDialog>

DatabaseDialog::DatabaseDialog(QString path, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DatabaseDialog),
    m_path(path)
{
    ui->setupUi(this);
    ui->edtPath->setText(m_path);
    connect(ui->btnPath, &QPushButton::clicked, this, &DatabaseDialog::open);
}

DatabaseDialog::~DatabaseDialog()
{
    delete ui;
}    

void DatabaseDialog::accept()
{
   m_path = ui->edtPath->text();
   QDialog::accept();
}

void DatabaseDialog::reject()
{
    QDialog::reject();
}

void DatabaseDialog::open()
{
    m_path = QFileDialog::getOpenFileName(
                this,
                tr("Open Database"),
                "/home/",
                "Database (*.db)");
    ui->edtPath->setText(m_path);
}

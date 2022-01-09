#include "adding.h"
#include "ui_adding.h"
#include "QCompleter"
#include "QFileSystemModel"
#include "QFile"
#include "QFileDialog"
#include "QWidget"

Adding::Adding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adding)
{
    ui->setupUi(this);
    ui->lineEdit_5->setVisible(false);

}

Adding::~Adding()
{
    delete ui;
}
void Adding::on_pushButton_2_clicked()
{
    auto imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png *.jpg)");

      QFileInfo info(imageFile);
      filename = info.fileName();
      ui->lineEdit_5->setText(imageFile);

      QPixmap image (imageFile);
      ui->lineEdit_5->setText(imageFile);
      ui->label_6->setPixmap(image);
      ui->label_6->show();

}

void Adding::on_pushButton_clicked()
{

    QByteArray byte;
    QFile file(ui->lineEdit_5->text());

    if(file.open(QIODevice::ReadOnly))
    {
        byte = file.readAll();
        file.close();
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","Add");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

    QString manufacture = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString category = ui->lineEdit_3->text();
    QString price = ui->lineEdit_4->text();
\

    if(db.open()){

            QSqlQuery query(db);
            query.prepare("insert into products (product_manufacture,product_name,category,photo,price) values(:manufacture,:name,:category,:photo,:price)");
            query.bindValue(":manufacture",manufacture);
            query.bindValue(":name",name);
            query.bindValue(":category",category);
            query.bindValue(":photo",byte, QSql::In | QSql::Binary);
            query.bindValue(":price",price);

            if(manufacture == "" ){
                QMessageBox::warning(this,"","");
            }


     }else{
                QMessageBox::warning(this,"Connection","Unsucesfull");
     }
}





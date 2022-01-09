#include "modify.h"
#include "ui_modify.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QCompleter"
#include "QFileSystemModel"
#include "QFile"
#include "QFileDialog"
#include "QWidget"
modify::modify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","main");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

    QSqlQuery query;
    query.prepare("select product_name from products");
    query.exec();
    model->setQuery(query);
    ui->comboBox->setModel(model);


}

modify::~modify()
{
    delete ui;
}


void modify::on_comboBox_currentIndexChanged(const QString &arg1)
{

}


void modify::on_comboBox_currentTextChanged(const QString &arg1)
{
    const int w = ui->photo->width();
    const int h = ui->photo->height();
    QString val = ui->comboBox->currentText();
    QSqlQuery select;
    select.prepare("select * from products where product_name = '"+val+"'");
    if(select.exec()){
        while(select.next()){
        ui->lineEdit->setText(select.value(1).toString());
        ui->lineEdit_2->setText(select.value(2).toString());
        ui->lineEdit_3->setText(select.value(3).toString());
        ui->lineEdit_4->setText(select.value(5).toString());
        QPixmap pixmap;
        pixmap.loadFromData(select.value(4).toByteArray());
        ui->photo->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
        }
    }

}

void modify::on_pushButton_2_clicked()
{
    auto imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png *.jpg)");

    const int w = ui->photo->width();
    const int h = ui->photo->height();

      QFileInfo info(imageFile);
      filename = info.fileName();
      ui->lineEdit_5->setText(imageFile);

      QPixmap image (imageFile);
      ui->lineEdit_5->setText(imageFile);
      ui->photo->setPixmap(image);
      ui->photo->show();
      ui->photo->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
}


void modify::on_pushButton_clicked()
{

    QString manufacture = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString category = ui->lineEdit_3->text();
    QString price = ui->lineEdit_4->text();
    QString val = ui->comboBox->currentText();

    QByteArray byte;
    QFile file(ui->lineEdit_5->text());

    if(file.open(QIODevice::ReadOnly))
    {
        byte = file.readAll();
        file.close();
    }

    QSqlQuery alter;
    alter.prepare("update products set product_manufacture = :manufacture, product_name= :name, category=:category, price=:price, photo=:photo where product_name='"+val+"'");
    alter.bindValue(":manufacture",manufacture);
    alter.bindValue(":name",name);
    alter.bindValue(":category",category);
    alter.bindValue(":photo",byte, QSql::In | QSql::Binary);
    alter.bindValue(":price",price);
    if(alter.exec()){

        QMessageBox::information(this,"Insert","Succesful");

    }else{

        QMessageBox::warning(this,"Connection","not");


    }
}




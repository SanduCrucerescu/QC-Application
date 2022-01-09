#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "iostream"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/alex/Desktop/2013317805.png");
    ui->label_pic->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
        if(db.open()){

            QSqlQuery query(db);
            query.prepare("select * from users where username = :username and password = :password");
            query.bindValue(":username",username);
            query.bindValue(":password",password);

            if(!query.exec()){

                QMessageBox::warning(this,"login","fail");

            }else{
                while(query.next()){
                    QString usernameFromDB = query.value(1).toString();
                    QString passwordFromDB = query.value(2).toString();

                    if(usernameFromDB == username && passwordFromDB == password){
                        QMessageBox::information(this,"Login","Login Succesfull");
                        this->close();
                        MainWin main;
                        main.setModal(true);
                        main.exec();
                        db.close();

                    }else {
                         QMessageBox::warning(this,"Login","Login Failed");
                    }
                }

            }

        }else{
            QMessageBox::warning(this,"Connection","Unsucesfull");
        }
}


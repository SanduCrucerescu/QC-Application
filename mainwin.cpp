#include "mainwin.h"
#include "ui_mainwin.h"
#include "adding.h"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "modify.h"
#include "QInputDialog"
#include "cart.h"
MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

        if(db.open()){

            querymodel = new QSqlQueryModel();
            querymodel->setQuery("Select idproducts as ID,product_manufacture as Manufacture,product_name as Name,Category,Photo,Price from products");
            ui->tableView->setModel(querymodel);

        }else{
            QMessageBox::warning(this,"Connection","Unsucesfull");
        }
        QSqlQuery truncate;
        truncate.exec("TRUNCATE TABLE cart");
        QSortFilterProxyModel *m=new QSortFilterProxyModel(this);
        m->setDynamicSortFilter(true);
        m->setSourceModel(querymodel);
        ui->tableView->setModel(m);
        ui->tableView->setSortingEnabled(true);

}

MainWin::~MainWin()
{
    db.close();
    delete ui;
}

void MainWin::on_pushButton_clicked()
{
    Adding adding;
    adding.setModal(true);
    adding.exec();
}


void MainWin::on_pushButton_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {

                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));


               //out << ba1;
            }
        }
        out << "</tr>\n";
    }

    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
    /*QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("/Users/alex/Desktop/test.pdf");
    QPainter painter;
    QSqlQuery q;
    q.exec(QString("select photo from products"));
   // q.next();
    QImage pixmap;
    painter.begin(&printer);
    //pixmap.loadFromData(q.value(0).toByteArray());
    while(q.next()){
        pixmap.loadFromData(q.value(0).toByteArray());
        painter.drawImage(40,-40,pixmap);
    }
    //painter.drawText(40,40,"test");
    painter.end();*/
}


void MainWin::on_tableView_activated(const QModelIndex &index)
{
    int quantaty = QInputDialog::getInt(this, "Quantaty"," Set Quantaty:");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","main");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

    QString val = ui->tableView->model()->data(index).toString();
    QSqlQuery querry;
    querry.prepare("select product_manufacture,product_name,Category,Photo,Price from products where idproducts = '"+val+"' or product_name = '"+val+"' or photo = '"+val+"' or price = '"+val+"'");
    if(db.open()){
            if(querry.exec()){
                while(querry.next()){
                    QSqlQuery query(db);
                    query.prepare("insert into cart (product_manufacture,product_name,category,photo,price,quantaty) values(:manufacture,:name,:category,:photo,:price,:quantaty)");

                    int qt = querry.value(4).toInt() * quantaty;

                    query.bindValue(":manufacture",querry.value(0).toString());
                    query.bindValue(":name",querry.value(1).toString());
                    query.bindValue(":category",querry.value(2).toString());
                    query.bindValue(":photo",querry.value(3).toByteArray(), QSql::In | QSql::Binary);
                    query.bindValue(":price",qt);
                    query.bindValue(":quantaty",quantaty);

                    if(query.exec()){

                        QMessageBox::information(this,"Insert","Succesful");
                        db.close();

                    }else{

                        QMessageBox::warning(this,"Connection","Failure");


                    }
                }

             }else{
                        QMessageBox::warning(this,"Connection","Unsucel");
             }
    }else{
        QMessageBox::warning(this,"Connection","Unsucesfull");
    }

}





void MainWin::on_tableView_clicked(const QModelIndex &index)
{
    if(!index.isValid()){
        return;
    }

    const int id = querymodel->index(index.row(),0).data().toInt();
    const int w = ui->label_ph->width();
    const int h = ui->label_ph->height();
    QSqlQuery q;
    q.exec(QString("select photo from products where idproducts = %1").arg(id));
    q.next();
    QPixmap pixmap;
    if(!pixmap.loadFromData(q.value(0).toByteArray())) {
        ui->label_ph->setText("No picture");
    }
    ui->label_ph->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
}


void MainWin::on_pushButton_3_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    const int id = querymodel->index(index.row(),0).data().toInt();
    QSqlQuery q,select;
    q.exec(QString("delete from products where idproducts = %1").arg(id));
    q.next();
    if(q.exec()){

        QMessageBox::information(this,"Delete","Sucesfull");
        select.exec(QString("Select idproducts as ID,product_manufacture as Manufacture,product_name as Name,Category,Photo,Price from products"));
        select.next();
        querymodel->setQuery("Select idproducts as ID,product_manufacture as Manufacture,product_name as Name,Category,Photo,Price from products");
        ui->tableView->setModel(querymodel);
        db.close();

    }else{
        QMessageBox::warning(this,"Delete","Unsucesfull");
    }
}


void MainWin::on_pushButton_4_clicked()
{
    modify mod;
    mod.setModal(true);
    mod.exec();
}


void MainWin::on_pushButton_5_clicked()
{
    cart cart;
    cart.setModal(true);
    cart.exec();
}


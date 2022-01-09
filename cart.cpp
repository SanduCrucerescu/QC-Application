#include "cart.h"
#include "ui_cart.h"
#include "QTextDocument"
#include "QPrinter"
#include "QPrintDialog"
cart::cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cart)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","cart");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root1234");
    db.setDatabaseName("Practica");

        if(db.open()){

            query = new QSqlQueryModel();
            sum = new QSqlQueryModel();
            query->setQuery("Select product_manufacture as Manufacture,product_name as Name,Category,Quantaty,Price from cart");
            sum->setQuery("select sum(price) from cart");
            QString str = sum->record(0).value(0).toString();
            ui->tableView->setModel(query);
            ui->label_2->setText(str);
        }else{
            QMessageBox::warning(this,"Connection","Unsucesfull");
        }
}

cart::~cart()
{
    delete ui;
}

void cart::on_pushButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    const int id = query->index(index.row(),0).data().toInt();
    QSqlQuery q,select;
    q.exec(QString("delete from cart where idcart = %1").arg(id));
    q.next();
    if(q.exec()){

        QMessageBox::information(this,"Delete","Sucesfull");
        select.exec(QString("Select product_manufacture as Manufacture,product_name as Name,Category,Quantaty,Price from cart"));
        select.next();
        query->setQuery("Select product_manufacture as Manufacture,product_name as Name,Category,Quantaty,Price from cart");
        ui->tableView->setModel(query);
        db.close();

    }else{
        QMessageBox::warning(this,"Delete","Unsucesfull");
    }
}


void cart::on_pushButton_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QString str = sum->record(0).value(0).toString();
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


            }
        }
        out << "</tr>\n";
    }
    out << "<tr>";
    out << "<td colspan='1'></td>";
    out << "<td></td>";
    out << "<td></td>";
    out << "<td>Total:</td>";
    out << QString("<td>%1</td>").arg(str);



    out << "</tr>";

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
}


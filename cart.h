#ifndef CART_H
#define CART_H
#include "QSqlDatabase"
#include "QtSql"
#include "QMessageBox"
#include <QDialog>

namespace Ui {
class cart;
}

class cart : public QDialog
{
    Q_OBJECT

public:
    explicit cart(QWidget *parent = nullptr);
    ~cart();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::cart *ui;
    QSqlQueryModel *query, *sum;
    QSqlDatabase db;

};

#endif // CART_H

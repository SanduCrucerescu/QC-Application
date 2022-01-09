#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "QSqlDatabase"
#include "QtSql"
#include "QMessageBox"
#include "QPrinter"
#include "QPrintDialog"
#include "QPainter"
#include "QTextDocument"
#include "QTableWidgetItem"
#include "QTextBrowser"
#include "QAbstractPrintDialog"
#include <QPixmap>
namespace Ui {
class MainWin;
}

class MainWin : public QDialog
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);


    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWin *ui;
    QSqlDatabase db;
    QSqlQueryModel *querymodel;
    QSqlTableModel  *model;
};

#endif // MAINWIN_H

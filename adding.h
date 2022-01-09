#ifndef ADDING_H
#define ADDING_H

#include <QDialog>
#include "QSqlDatabase"
#include "QtSql"
#include "QMessageBox"
#include "QFileDialog"
namespace Ui {
class Adding;
}

class Adding : public QDialog
{
    Q_OBJECT

public:
    explicit Adding(QWidget *parent = nullptr);
    ~Adding();

        QString filename;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Adding *ui;


};

#endif // ADDING_H

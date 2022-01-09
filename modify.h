#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>
#include "QSqlDatabase"
#include "QtSql"
namespace Ui {
class modify;
}

class modify : public QDialog
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = nullptr);
    ~modify();
    QString filename;

private slots:

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::modify *ui;
};

#endif // MODIFY_H

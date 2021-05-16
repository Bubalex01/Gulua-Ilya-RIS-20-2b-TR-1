#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void changetext();
    //void on_lineEdit_textChanged(const QString &arg1);
    void on_box_period_activated(int index);

    void on_box_valyta_activated(int index);
    void on_line_srok_editingFinished();

    void on_line_sum_editingFinished();

    void on_line_fees_editingFinished();

    void on_line_stavka_editingFinished();
    void Calculation();
    void EveryMonth(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date);
    void EveryQuarter(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date);
    void EveryYear(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date);
    void RemoveRows();
    bool CheckErrors();
    void on_pushButton_2_clicked();

    void on_box_srok_currentIndexChanged();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

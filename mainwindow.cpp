#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
static bool f=0;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->hide();
    ui->label_1_text->hide();
    ui->label_2_text->hide();
    ui->label_error_days->hide();
    ui->label_error_fees->hide();
    ui->label_error_sum->hide();
    ui->label_3->hide();
    connect(ui->pushButton,&QPushButton::clicked, this,&MainWindow::Calculation);
    ui->line_fees->setValidator(new QDoubleValidator(this));
    ui->line_sum->setValidator(new QDoubleValidator(this));
    ui->line_srok->setValidator(new QIntValidator(this));
    ui->line_stavka->setValidator(new QDoubleValidator(this));
    MainWindow::setFixedSize(511,360);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_box_period_activated(int index)
{
    switch(index)
    {
    case 0:
        ui->label_fees->setText("Ежемесячная комиссия"); break;
    case 1:
        ui->label_fees->setText("Ежеквартальная комиссия"); break;
    case 2:
        ui->label_fees->setText("Ежегодная комиссия"); break;
    }
}

void MainWindow::on_box_valyta_activated(int index)
{
    switch(index)
    {
    case 0:
        ui->label_fees_val->setText("₽");
        break;
    case 1:
        ui->label_fees_val->setText("$");
        break;
    case 2:
        ui->label_fees_val->setText("€");
        break;
    }
   on_line_sum_editingFinished();
}

void MainWindow::on_line_srok_editingFinished()
{
    QString arg1=ui->line_srok->text();
    int box_index =ui->box_srok->currentIndex();

    if (box_index==0 && arg1.toInt()<30)
    {
        ui->label_error_days->setText("Не менее 30 дней");
        ui->label_error_days->show();
    }
    else
    if (arg1.toInt()==0)
    {
        ui->label_error_days->setText("Некорректное значение");
        ui->label_error_days->show();
    }
    else
        ui->label_error_days->hide();

    if (arg1<"0") {arg1.remove("-"); ui->line_srok->setText(arg1);}
    arg1=ui->line_srok->text();
    QString y=arg1.right(1);
    switch(box_index) //дни, месяца или года
    {
    case 0: //дни
        if (arg1>"14")
        switch(y.toInt())
        {
        case 1: ui->box_srok->setItemText(0,"день"); break;
        case 2: case 3: case 4: ui->box_srok->setItemText(0,"дня"); break;
        default: ui->box_srok->setItemText(0,"дней"); break;
        }
        else
            switch(arg1.toInt())
            {
            case 1: ui->box_srok->setItemText(0,"день"); break;
            case 2:case 3:case 4: ui->box_srok->setItemText(0,"дня"); break;
            default: ui->box_srok->setItemText(0,"дней"); break;
            }
    case 1: //месяца
        if (arg1>"14")
            switch(y.toInt())
            {
            case 1: ui->box_srok->setItemText(1,"месяц"); break;
            case 2: case 3: case 4: ui->box_srok->setItemText(1,"месяца"); break;
            default: ui->box_srok->setItemText(1,"месяцев"); break;
            }
        else
            switch(arg1.toInt())
            {
            case 1: ui->box_srok->setItemText(1,"месяц"); break;
            case 2:case 3:case 4: ui->box_srok->setItemText(1,"месяца"); break;
            default: ui->box_srok->setItemText(1,"месяцев"); break;
            }
    case 2: //года
        if (arg1>"14")
            switch(y.toInt())
            {
            case 1: ui->box_srok->setItemText(2,"год"); break;
            case 2: case 3: case 4: ui->box_srok->setItemText(2,"года"); break;
            default: ui->box_srok->setItemText(2,"лет"); break;
            }
        else
            switch(arg1.toInt())
            {
            case 1: ui->box_srok->setItemText(2,"год"); break;
            case 2:case 3:case 4: ui->box_srok->setItemText(2,"года"); break;
            default: ui->box_srok->setItemText(2,"лет"); break;
            }
    }
}


void MainWindow::on_line_sum_editingFinished()
{
    QString sum=ui->line_sum->text();
    sum.remove(",00");
    bool flag=0;
    if (sum.contains(',')||sum.contains('.'))
    {
        sum.replace(",","."); flag=1;
    }
    if (sum<"0") sum.remove("-");
    int box_index =ui->box_valyta->currentIndex();
    switch(box_index)
    {
    case 0:
        if (sum.toDouble()<1000)
        {
            ui->label_error_sum->setText("Не менее 1000 ₽");
            ui->label_error_sum->setVisible(1);
        } else ui->label_error_sum->hide();break;
    case 1:
        if (sum.toDouble()<20)
        {
            ui->label_error_sum->setText("Не менее 20 $");
            ui->label_error_sum->setVisible(1);
        } else ui->label_error_sum->hide();break;
    case 2:
        if (sum.toDouble()<20)
            {
                ui->label_error_sum->setText("Не менее 20 €");
                ui->label_error_sum->setVisible(1);
            } else ui->label_error_sum->hide(); break;
    }
    if (flag)
    {
        sum.replace(".",",");
        ui->line_sum->setText(sum);
    }
    else ui->line_sum->setText(sum+",00");
}

void MainWindow::on_line_fees_editingFinished()
{
    QString fees=ui->line_fees->text();
    QString sum=ui->line_sum->text();
    fees.remove(",00");
    sum.replace(",",".");
    bool flag=0;
    if (fees.contains(',')||fees.contains('.'))
    {
        fees.replace(",","."); flag=1;
    }
    if (fees<"0") fees.remove("-");
    if (sum.toDouble()/fees.toDouble()<=1)
    {
        ui->label_error_fees->setVisible(1);
    } else  ui->label_error_fees->hide();

    if (flag)
    {
        fees.replace(".",",");
        ui->line_fees->setText(fees);
    }
    else ui->line_fees->setText(fees+",00");
}

void MainWindow::on_line_stavka_editingFinished()
{
    QString stavka=ui->line_stavka->text();
    stavka.remove(",00");
    bool flag=0;
    if (stavka.contains(',')||stavka.contains('.'))
    {
        stavka.replace(",","."); flag=1;
    }
    if (stavka<"0") stavka.remove("-");
    if (stavka.toDouble()>99) stavka="99";
    if (flag)
    {
        stavka.replace(".",",");
        ui->line_stavka->setText(stavka);
    }
    else ui->line_stavka->setText(stavka+",00");
    if (stavka=="0") ui->line_stavka->setText("0,1");
}

void MainWindow::EveryMonth(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date)
{
    double P=(stavka/100)/12;
    double month;
    switch(sroktype)
    {
    case 0:
        month=srok/29; break;
    case 1:
        month=srok; break;
    case 2:
        month=srok*12; break;
    }
    double x = sum * (P + (P / (pow(1 + P, month) - 1)))+fees;
    float aaa=x*month;
    switch(val)
    {
    case 0:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" ₽");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" ₽"); break;
    case 1:
        ui->label_1_sum->setText("$"+QString::number(aaa,'f',2));
        ui->label_2_sum->setText("$"+QString::number(aaa-sum,'f',2)); break;
    case 2:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" €");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" €"); break;
    }
    QTableWidgetItem *data=new QTableWidgetItem(date.toString());
    ui->tableWidget->setItem(0,0,data);
    QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
    ui->tableWidget->setItem(0,5,sum1);
    for(int i=1;i<=month;i++)
    {
        ui->tableWidget->insertRow(i);
        double percent=sum*P;
        double dolg=x-percent-fees;
        date=date.addMonths(1);
        sum=sum-dolg;
        if (i==month) sum=0;
        QTableWidgetItem *data=new QTableWidgetItem(date.toString());
        ui->tableWidget->setItem(i,0,data);
        QTableWidgetItem *platej=new QTableWidgetItem(QString::number(x,'f',2));
        ui->tableWidget->setItem(i,1,platej);
        QTableWidgetItem *proc=new QTableWidgetItem(QString::number(percent));
        ui->tableWidget->setItem(i,2,proc);
        QTableWidgetItem *fee=new QTableWidgetItem(QString::number(fees,'f',2));
        ui->tableWidget->setItem(i,3,fee);
        QTableWidgetItem *dolgg=new QTableWidgetItem(QString::number(dolg,'f',2));
        ui->tableWidget->setItem(i,4,dolgg);
        QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
        ui->tableWidget->setItem(i,5,sum1);
    }

}

void MainWindow::EveryQuarter(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date)
{
    double P=(stavka/100)/4;
    double month;
    switch(sroktype)
    {
    case 0:
        month=srok/29; break;
    case 1:
        month=srok; break;
    case 2:
        month=srok*12; break;
    }
    if(fmod(month,3)) {EveryMonth(sum,stavka,fees,1,val,srok,date); return;}
    double x = sum * (P + (P / (pow(1 + P, month/3) - 1)))+fees;
    double aaa=x*month/3;
    switch(val)
    {
    case 0:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" ₽");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" ₽"); break;
    case 1:
        ui->label_1_sum->setText("$"+QString::number(aaa,'f',2));
        ui->label_2_sum->setText("$"+QString::number(aaa-sum,'f',2)); break;
    case 2:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" €");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" €"); break;
    }
    QTableWidgetItem *data=new QTableWidgetItem(date.toString());
    ui->tableWidget->setItem(0,0,data);
    QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
    ui->tableWidget->setItem(0,5,sum1);
    for(int i=1;i<=month/3;i++)
    {
        ui->tableWidget->insertRow(i);
        double percent=sum*P;
        double dolg=x-percent-fees;
        date=date.addMonths(3);
        sum=sum-dolg;
        if (i==month/3) sum=0;
        QTableWidgetItem *data=new QTableWidgetItem(date.toString());
        ui->tableWidget->setItem(i,0,data);
        QTableWidgetItem *platej=new QTableWidgetItem(QString::number(x,'f',2));
        ui->tableWidget->setItem(i,1,platej);
        QTableWidgetItem *proc=new QTableWidgetItem(QString::number(percent));
        ui->tableWidget->setItem(i,2,proc);
        QTableWidgetItem *fee=new QTableWidgetItem(QString::number(fees,'f',2));
        ui->tableWidget->setItem(i,3,fee);
        QTableWidgetItem *dolgg=new QTableWidgetItem(QString::number(dolg,'f',2));
        ui->tableWidget->setItem(i,4,dolgg);
        QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
        ui->tableWidget->setItem(i,5,sum1);
    }

}

void MainWindow::EveryYear(double sum,double stavka,double fees,int sroktype,int val,int srok,QDate &date)
{
    double P=(stavka/100);
    double month;
    switch(sroktype)
    {
    case 0:
        month=srok/29; break;
    case 1:
        month=srok; break;
    case 2:
        month=srok*12; break;
    }
    if(month<12) {EveryMonth(sum,stavka,fees,1,val,srok,date); return;}
    double x = sum * (P + (P / (pow(1 + P, month/12) - 1)))+fees;
    double aaa=x*month/12;
    switch(val)
    {
    case 0:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" ₽");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" ₽"); break;
    case 1:
        ui->label_1_sum->setText("$"+QString::number(aaa,'f',2));
        ui->label_2_sum->setText("$"+QString::number(aaa-sum,'f',2)); break;
    case 2:
        ui->label_1_sum->setText(QString::number(aaa,'f',2)+" €");
        ui->label_2_sum->setText(QString::number(aaa-sum,'f',2)+" €"); break;
    }
    QTableWidgetItem *data=new QTableWidgetItem(date.toString());
    ui->tableWidget->setItem(0,0,data);
    QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
    ui->tableWidget->setItem(0,5,sum1);
    for(int i=1;i<=month/12;i++)
    {
        ui->tableWidget->insertRow(i);
        double percent=sum*P;
        double dolg=x-percent-fees;
        date=date.addMonths(12);
        sum=sum-dolg;
        if (i==month/12) sum=0;
        QTableWidgetItem *data=new QTableWidgetItem(date.toString());
        ui->tableWidget->setItem(i,0,data);
        QTableWidgetItem *platej=new QTableWidgetItem(QString::number(x,'f',2));
        ui->tableWidget->setItem(i,1,platej);
        QTableWidgetItem *proc=new QTableWidgetItem(QString::number(percent));
        ui->tableWidget->setItem(i,2,proc);
        QTableWidgetItem *fee=new QTableWidgetItem(QString::number(fees,'f',2));
        ui->tableWidget->setItem(i,3,fee);
        QTableWidgetItem *dolgg=new QTableWidgetItem(QString::number(dolg,'f',2));
        ui->tableWidget->setItem(i,4,dolgg);
        QTableWidgetItem *sum1= new QTableWidgetItem(QString::number(sum,'f',2));
        ui->tableWidget->setItem(i,5,sum1);
    }

}

void MainWindow::RemoveRows()
{
    int a=ui->tableWidget->rowCount();
    for(int i=a;i>=1;i--)
    {
        ui->tableWidget->removeRow(i);
    }
}

bool MainWindow::CheckErrors()
{
    bool flag=(ui->label_error_days->isVisible()
               ||ui->label_error_fees->isVisible()
               ||ui->label_error_sum->isVisible());
    return flag;
}

void MainWindow::Calculation()
{
    if (CheckErrors()) return;
    ui->tableWidget->show();
    ui->label_1_text->show();
    ui->label_2_text->show();
    ui->label_1_sum->show();
    ui->label_2_sum->show();
    ui->label_3->show();
    MainWindow::setFixedSize(1200,485);
    RemoveRows();
    QString sumstr=ui->line_sum->text(); sumstr.replace(",",".");
    QString stavkastr=ui->line_stavka->text(); stavkastr.replace(",",".");
    QDate date=ui->box_date->date();
    QString feesstr=ui->line_fees->text(); feesstr.replace(",",".");
    QString srokstr=ui->line_srok->text();
    double sum=sumstr.toDouble();
    double stavka=stavkastr.toDouble();
    double fees=feesstr.toDouble();
    int srok=srokstr.toInt();
    int sroktype=ui->box_srok->currentIndex();
    int val=ui->box_valyta->currentIndex();
    int period=ui->box_period->currentIndex();
    switch(period)
    {
    case 0:
        EveryMonth(sum, stavka, fees, sroktype, val,srok, date); break;
    case 1:
        EveryQuarter(sum, stavka, fees, sroktype, val,srok, date); break;
    case 2:
        EveryYear(sum, stavka, fees, sroktype, val,srok, date); break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::setFixedSize(511,360);
    ui->tableWidget->hide();
    ui->label_1_sum->hide();
    ui->label_1_text->hide();
    ui->label_2_sum->hide();
    ui->label_2_text->hide();
    ui->label_3->hide();
}

void MainWindow::on_box_srok_currentIndexChanged()
{
    on_line_srok_editingFinished();
}

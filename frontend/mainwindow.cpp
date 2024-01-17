
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    step = 0.1;
    start = ui->x_end_2->value();
    end = ui->x_start->value();
    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
    temp_x = start;
    dot_count = (end - start) / step + 2;
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);

    connect(ui->number_0, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_1, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_2, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_3, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_4, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_5, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_6, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_7, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_8, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->number_9, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->dot, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->x_value, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->pi_value, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->plus, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->minus, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->power, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->multiply, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->division, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->mod, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->open_bracket, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->close_bracket, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->sine, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->cosine, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->tangent, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->arc_sine, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->arc_cosine, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->arc_tangent, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->log_10, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->log, SIGNAL(clicked()), this, SLOT(insert_number()));
    connect(ui->square_root, SIGNAL(clicked()), this, SLOT(insert_number()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insert_number()
{
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->insert(button->text());
}


void MainWindow::on_calculate_clicked()
{
    int code = 0;
    QByteArray ba = ui->lineEdit->text().toLatin1();
    double result = get_result(ba.data(), user_x, &code);
    if (code == OK) {
        ui->lineEdit->setText(QString::number(result, 'f', 10));
    } else {
        ui->lineEdit->setText("Произошла ошибка");
    }

}


void MainWindow::on_draw_graph_clicked()
{
    int code = 0;
    if (ui->widget->graphCount() > 0) {
        ui->widget->clearPlottables();
        ui->widget->clearGraphs();
    }
    ui->widget->replot();
    QByteArray ba = ui->lineEdit->text().toLatin1();

    for (temp_x = ui->x_start->value(); temp_x <= ui->x_end_2->value() && code == OK; temp_x += step) {
        x.push_back(temp_x);
        double temp_y = get_result(ba.data(), temp_x, &code);
        if ((temp_y <= 100000 && temp_y >= -100000) && code == OK) {
            y.push_back(temp_y);
        }

    }
    if (code == OK) {
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x, y);
        ui->widget->replot();
    } else {
        ui->lineEdit->setText("Произошла ошибка");
    }

    x.clear();
    y.clear();
}



void MainWindow::on_erase_clicked()
{
    ui->widget->clearPlottables();
    ui->widget->clearGraphs();
    ui->widget->replot();
}

void MainWindow::on_x_user_value_valueChanged(double arg1)
{
    user_x = arg1;
}


void MainWindow::on_smart_calc_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_credit_calc_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_calculateCredit_clicked()
{
    ui->listWidget->clear();
    double creditSumValue = ui->creditSum->value();
    int paymentsCountValue = ui->paymentsCount->value();
    double annualRateValue = ui->rate->value();
    double payment = 0.0;
    double allPayments = 0.0;
    if (ui->annCredit->isChecked()) {
        for (int i = 0; i < paymentsCountValue; i++) {
            payment = get_monthly_payment_ann(creditSumValue, annualRateValue, paymentsCountValue);
            ui->listWidget->addItem(QString::number(payment, 'f', 2));
            allPayments = allPayments + payment;
        }
    } else if (ui->diffCredit->isChecked()) {
        double debtLeft = creditSumValue;
        for (int i = 0; i < paymentsCountValue; i++) {
            payment = get_monthly_payment_diff(creditSumValue, annualRateValue, paymentsCountValue, debtLeft);
            ui->listWidget->addItem(QString::number(payment, 'f', 2));
            debtLeft = debtLeft - payment;
            allPayments = allPayments + payment;
        }
    }
    ui->overPayLabel->setText(QString::number(allPayments - creditSumValue, 'f', 2));
    ui->paymentsSumLabel->setText(QString::number(allPayments, 'f', 2));
}


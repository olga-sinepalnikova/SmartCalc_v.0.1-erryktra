#include "../s21_smartcalc.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void insert_number();

    void on_calculate_clicked();

    void on_draw_graph_clicked();

    void on_erase_clicked();

    void on_x_user_value_valueChanged(double arg1);

    void on_smart_calc_clicked();

    void on_credit_calc_clicked();

    void on_calculateCredit_clicked();

private:
    Ui::MainWindow *ui;
    double start, end, step, temp_x;
    int dot_count;
    QVector<double> x, y;
    double user_x;
};
#endif // MAINWINDOW_H


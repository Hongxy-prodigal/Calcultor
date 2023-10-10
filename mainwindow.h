#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStack>

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
    QString operand;
    QString code;
    QString operands;
    QString codes;

    QString calculation();

private:
    Ui::MainWindow *ui;

private slots:
    void btnNumClicked();
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClearAll_clicked();
    void on_btnSign_clicked();
    void on_btnClear_clicked();
    void btnOperatorClicked();
    void on_btnEqual_clicked();
};
#endif // MAINWINDOW_H

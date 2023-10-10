#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnNum0, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum1, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum2, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum3, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum4, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum5, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum6, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum7, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum8, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum9, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation()
{
    double result;
    if (codes == "+") {
        if (operand == "")
            result = operands.toDouble() * 2;
        else
            result = operands.toDouble() + operand.toDouble();
    } else if (codes == "-") {
        if (operand == "")
            result = 0;
        else
            result = operands.toDouble() - operand.toDouble();
    } else if (codes == "×") {
        if (operand == "")
            result = operands.toDouble() * operands.toDouble();
        else
            result = operands.toDouble() * operand.toDouble();
    } else {
        if (operand == "")
            result = 1;
        else if (operand == "0") {
            return "除数不能为零";
        }
        result = operands.toDouble() / operand.toDouble();
    }
    return QString::number(result);
}

//数字键
void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if (digit == "0" && operand == "0") {
        digit = "";
    }
    if (digit != "0" && operand == "0") {
        operand = "";
    }
    operand += digit;
    ui->display->setText(operand);
}

//小数点
void MainWindow::on_btnPeriod_clicked()
{
    if (!operand.contains('.')) {
        operand += '.';
        ui->display->setText(operand);
    }
}

//正负号
void MainWindow::on_btnSign_clicked()
{
    if (!operand.contains('-'))
        operand = '-' + operand;
    else
        operand = operand.right(operand.size() - 1);
    ui->display->setText(operand);
}

//删除键
void MainWindow::on_btnDel_clicked()
{
    if (operand != NULL) {
        operand = operand.left(operand.size() - 1);
        ui->display->setText(operand);
    }
}

//这是清楚所有
void MainWindow::on_btnClearAll_clicked()
{
    operand = "";
    operands = "";
    code = "";
    codes = "";
    ui->display->setText(operand);
}

//这是清楚要加或要减的数
void MainWindow::on_btnClear_clicked()
{
    operand = "";
    ui->display->setText(operand);
}

//操作符
void MainWindow::btnOperatorClicked()
{
    code = qobject_cast<QPushButton *>(sender())->text();
    if (operand == "") {        //避免多次使用操作数
        codes = code;
        return;
    }
    if (codes != "") {
        //计算
        operands = calculation();
        operand = "";
        codes = code;
        ui->display->setText(operands);
    } else {
        //不计算
        if (operand != "") {
            operands = operand;
            operand = "";
        } else {
            operands = "0";
        }
        ui->display->setText(operands);
        codes = code;
    }


}

void MainWindow::on_btnEqual_clicked()
{

    if (codes != "") {      //有操作符时
        //计算
        if (operand == "") {                    //操作数为空让它自己乘自己
            operands = calculation();
            codes = "";
            ui->display->setText(operands);
        } else {                                //就算前面的数和操作数相乘
            operands = calculation();
            operand = "";
            codes = "";
            ui->display->setText(operands);
        }
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    keyBtns = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
    };
    operatorBtns = {
        {Qt::Key_Backspace, ui->btnDel},
        {Qt::Key_Slash, ui->btnDivide},
        {Qt::Key_Asterisk, ui->btnMul},
        {Qt::Key_Minus, ui->btnSub},
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Equal, ui->btnEqual},
        {Qt::Key_Return, ui->btnEqual},
    };
    QList<QPushButton *> values = keyBtns.values();
    foreach (auto btn, values) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

    connect(ui->btnPlus, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));
    connect(ui->btnDivide, SIGNAL(clicked()), this, SLOT(btnOperatorClicked()));

    connect(ui->btnPercentage, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnInverse, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
    connect(ui->btnSquare, SIGNAL(clicked()), this, SLOT(btnUniOperatorClicked()));
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
            operand = "";
            code = "";
            codes = "";
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
    if (operand != "") {
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

//实现单操作和计算器一样
void MainWindow::btnUniOperatorClicked()
{
    QString op = qobject_cast<QPushButton *>(sender())->text();
//    QString digit = ui->display->text();
    double result = ui->display->text().toDouble();
    if (op == "%")
        result /= 100.0;
    else if (op == "1/x") {
        if (result == 0) {
            operands = "除数不能为零";
            operand = "";
            code = "";
            codes = "";
            ui->display->setText(operands);
            return;
        }
        result = 1 / result;
    } else if (op == "x^2")
        result = result * result;
    else if (op == "√")
        result = sqrt(result);
//    if (digit == operands) {
//        operands = QString::number(result);
//        ui->display->setText(operands);
//    } else {
//        operand = QString::number(result);
//        ui->display->setText(operand);
//    }
    //判断当前数字是结果还是操作数
    if (operand == "") {
        operands = QString::number(result);
        ui->display->setText(operands);
    } else {
        operand = QString::number(result);
        ui->display->setText(operand);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QList<int> values = keyBtns.keys();
    foreach (auto key, values) {
        if (event->key() == key)
            emit keyBtns[key]->clicked();
    }
    QList<int> values1 = operatorBtns.keys();
    foreach (auto op, values1) {
        if (event->key() == op)
            emit operatorBtns[op]->clicked();
    }
}



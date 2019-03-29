#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPixmap>

#include <QDebug>
#include <QVector>
#include <QString>
#include <numeric>
#include <algorithm>
#include <QFileDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>

#include <QThread>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort serial;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getPotencia();

private slots:
    void on_btn_Enviar_clicked();
    void dadosRecebidos();

private:
    Ui::MainWindow *ui;
    QString dados_serial="";

};

#endif // MAINWINDOW_H

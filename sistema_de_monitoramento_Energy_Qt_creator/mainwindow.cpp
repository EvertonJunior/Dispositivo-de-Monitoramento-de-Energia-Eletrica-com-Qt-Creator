#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&serial, SIGNAL(readyRead()),this,SLOT(dadosRecebidos()));

    serial.setPortName("COM4");
    serial.setBaudRate(QSerialPort::Baud115200);

    if(serial.open(QIODevice::ReadWrite)){
       qDebug()<< "Conectado a COM4";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Enviar_clicked()
{
    int Potencia = 0;

    QString Eletrodomestico = ui->comboBox_Eletro->currentText() ;

    if(Eletrodomestico == "Ferro Eletrico") Potencia = 1230;
    if(Eletrodomestico == "Forno Microondas") Potencia = 1200;
    if(Eletrodomestico == "Secador de Cabelo") Potencia = 1600;
    if(Eletrodomestico == "Prancha de Cabelo") Potencia = 1570;
    if(Eletrodomestico == "Maquina de Lavar Roupa") Potencia = 1000;
    if(Eletrodomestico == "Maquina de Lavar Louça") Potencia = 1500;
    if(Eletrodomestico == "Condicionador de Ar") Potencia = 1400;
    if(Eletrodomestico == "Cortador de Grama") Potencia = 1300;
    if(Eletrodomestico == "Fogão Elétrico 2 Bocas") Potencia = 3000;
    if(Eletrodomestico == "Fogão Elétrico 4 Bocas") Potencia = 6000;

    if(Eletrodomestico == "Maquina de Costura") Potencia = 127;
    if(Eletrodomestico == "Geladeira Duplex") Potencia = 500;
    if(Eletrodomestico == "Espremedor de Frutas") Potencia = 200;
    if(Eletrodomestico == "Aspirador de Po") Potencia = 600;
    if(Eletrodomestico == "Ventilador") Potencia = 100;
    if(Eletrodomestico == "Geladeira Simples") Potencia = 250;
    if(Eletrodomestico == "Luminaria") Potencia = 9;
    if(Eletrodomestico == "Ferro de Solda") Potencia = 18;

    else{};


    if(Potencia != 0)
    {
        QString Pot = QString::number(Potencia);
        serial.write("{POTENCIA:" + Pot.toUtf8() + "}");
    }
}
void MainWindow::dadosRecebidos(){

    QString Dados_IDE = serial.readAll();
    //qDebug()<<dados;

    dados_serial = dados_serial + Dados_IDE;

    if(dados_serial.startsWith("{") && dados_serial.endsWith("}"))
    {
        //qDebug()<<dados_serial;
        dados_serial ="";
    }

}

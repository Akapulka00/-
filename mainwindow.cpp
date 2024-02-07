#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <chrono>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

   ui->setupUi(this);
   const int dataSize=1000000;

}
template  <typename T> QVector <T>  MainWindow:: sempleMovingAvrage (const QVector <T>& data, int period){
   QVector <T> result;
   for(int i=period-1;i<data.size() ;++i){
      T sum=0;
      for (int j =i-period+1;j<=i;++j) {
         sum+=data[j];
      }

      result.append(sum/period);
   }
   return result;
}
template  <typename T> T MainWindow:: sempleMovingAvrageOnce (const QVector <T>& data, int period){
   T sum = 0;
   int count=0;
   for(int i=data.size()-1-(counter*period);i>=0 && count<period;--i){
      sum+=data[i];
      ++count;
   }
   return sum/count;
}
void MainWindow::measurePerfomanceOnce( int fl){
   if(floatData.size()==0) {
      return;
      ui->textEdit->setText(("Последовательнось не задана!"));
   }
   QVector <int> windowSizes={4,8,16,32,64,128};
   QString ret;
   if(fl==0){
      for(int windowSize : windowSizes){
         ui->textEdit->append(QString());
         counter=0;
         while(counter<((floatData.size()/windowSizes[5]))/100) {
            auto start=std::chrono::steady_clock::now();
            float smaFloat=sempleMovingAvrageOnce(floatData,windowSize);
            auto end=std::chrono::steady_clock::now();
            qint64 elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
            ret.append(QString(" %1  %2 \n").arg(windowSize).arg(elapsedTime));
            counter++;
         }}
      ui->textEdit->append(ret);
   }
   if(fl==1){
      for(int windowSize : windowSizes){
         counter=0;
         while(counter<((floatData.size()/windowSizes[5]))/100) {
            auto start=std::chrono::steady_clock::now();
            float smaFloat=sempleMovingAvrageOnce(doubleData,windowSize);
            auto end=std::chrono::steady_clock::now();
            qint64 elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
            ret.append(QString(" %1  %2 \n").arg(windowSize).arg(elapsedTime));
            counter++;
         }}
      ui->textEdit->append(ret);
   }
   ret.clear();
}
void MainWindow::measurePerfomance(){
   QString ret;
   ret.clear();
   QVector <int> windowSizes={4,8,16,23,64,128};
   for(int windowSize : windowSizes){
      auto start=std::chrono::steady_clock::now();
      QVector <float> smaFloat=sempleMovingAvrage(floatData,windowSize);
      auto end=std::chrono::steady_clock::now();
      qint64 elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
      ret.append(QString("Время  выполнения последовательности за fload %1  %2 мс \n").arg(windowSize).arg(elapsedTime));
   }
   for(int windowSize : windowSizes){
      auto start=std::chrono::steady_clock::now();
      QVector <double> smaDouble=sempleMovingAvrage(doubleData,windowSize);
      auto end=std::chrono::steady_clock::now();
      qint64 elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
      ret.append(QString("Время  выполнения последовательности за double %1  %2 мс \n").arg(windowSize).arg(elapsedTime));
   }
   ui->textEdit->append(ret);

}
MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
   const int dataSize=1000000;
   floatData.clear();
   doubleData.clear();
   for(int i=0;i<dataSize;i++){
      double Value=qrand()%100;
      floatData.append(Value);
      doubleData.append(Value);
   }
   qDebug()<<"Размер foatData="<<floatData.size();
}

void MainWindow::on_pushButton_3_clicked()
{
   if(floatData.size()==0) {
      ui->textEdit->setText("Последовательнось не задана!");
      return;
   }
   ui->textEdit->clear();
   measurePerfomanceOnce(0);
}

void MainWindow::on_pushButton_clicked()
{
   if(floatData.size()==0) {
      ui->textEdit->setText("Последовательнось не задана!");
      return;
   }
   ui->textEdit->clear();
   measurePerfomance();
}

void MainWindow::on_pushButton_4_clicked()
{
   if(floatData.size()==0) {
      ui->textEdit->setText("Последовательнось не задана!");
      return;
   }
   ui->textEdit->clear();
   measurePerfomanceOnce(1);

}

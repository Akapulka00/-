#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

   public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

   private:
   Ui::MainWindow *ui;
   int counter;
   template  <typename T>
   QVector <T> sempleMovingAvrage (const QVector <T>& data, int period);
   template  <typename T>
   T sempleMovingAvrageOnce (const QVector <T>& data, int period);
   private slots:
   void measurePerfomanceOnce( int fl);
   void measurePerfomance();
   void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_clicked();

   void on_pushButton_4_clicked();

   private:
   QVector<float> floatData;
   QVector<double> doubleData;

};
#endif // MAINWINDOW_H

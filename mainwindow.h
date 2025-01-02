#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QTextDocument>
#include <QFontMetrics>

#include <QStandardPaths>
#include <QFileDialog>


#include <QDebug>
#include <iostream>



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

    int writeTextToPDF(const QString &data_string);

private:
    Ui::MainWindow *ui;
    QString filepath;

    QString FontName = QString("Helvetica");
    unsigned int FontSize = 14;
    unsigned int padding = 50;
    unsigned int spacing = 20;
    double coeff = 3.51;

    void printString(QPdfWriter &writer,QPainter &painter, QString &text_line, QFontMetrics &fontMetrics, int &TextWidth, int &heightPixels, unsigned int &x_pos, unsigned int &y_pos);

};
#endif // MAINWINDOW_H

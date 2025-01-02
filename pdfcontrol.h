#ifndef PDFCONTROL_H
#define PDFCONTROL_H

#include <QString>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QTextDocument>
#include <QStandardPaths>
#include <QFileDialog>

class PDFControl
{
public:
    PDFControl(QPdfWriter *writer_gui);
    ~PDFControl();

    int WriteToPDF(QString data);
    int SavePDF();

private:
    QString filepath;
    QPdfWriter *writer;
    QPainter *painter;
    QFont font;
};

#endif // PDFCONTROL_H

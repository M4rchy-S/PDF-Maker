#include "pdfcontrol.h"

PDFControl::PDFControl(QPdfWriter *writer_gui, QPainter *painter_gui)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //QString filepath = QFileDialog::getSaveFileName(this, "Save PDF", path, "PDF Files") + QString(".pdf") ;
    this->filepath = QFileDialog::getSaveFileName(nullptr, "Save PDF", path, "PDF Files")  ;

    if (filepath.isEmpty())
    {
        return ;
    }

    // Создание PDF-документа

    this->writer = writer_gui;

    writer->setPageSize(QPageSize(QPageSize::A4));
    writer->setCreator("Creator test");

    this->painter = painter_gui;
    this->painter()
    if (!painter.isActive()) {
        qWarning("Failed to open the PDF file for writing.");
        return ;
    }


    // Настройка шрифта с поддержкой кириллицы

    QFont helvetica("Helvetica", 14);
    painter.setFont(helvetica);
    painter.drawText(100, 100, "Привет, это PDF-документ!");
    painter.drawText(100, 500, "this is test pdf-document");
}

PDFControl::~PDFControl()
{
    this->painter.end();
}

int PDFControl::WriteToPDF(QString data)
{
    return 0;
}

int PDFControl::SavePDF()
{
    return 0;
}

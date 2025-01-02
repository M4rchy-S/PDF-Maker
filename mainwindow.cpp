#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // QObject::connect(ui->pushButton, &QPushButton::clicked, this, [=](){
    //     qDebug() << ui->textEdit->toPlainText();
    //     this->writeTextToPDF(ui->textEdit->toPlainText());
    // });

    QObject::connect(ui->editorButton, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(0);
    });
    QObject::connect(ui->settingButton, &QPushButton::clicked, this, [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
    });

    QObject::connect(ui->saveButton, &QPushButton::clicked, this, [=]()
    {
        this->writeTextToPDF(ui->textEdit->toPlainText());
    });

    QObject::connect(ui->loadButton, &QPushButton::clicked, this, [=]()
    {
        QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QString txt_path = QFileDialog::getSaveFileName(this, "Load txt file", path);

        QFile file(txt_path);
        //if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        if(!file.open(QIODevice::ReadOnly))
            return;

        ui->textEdit->setText( QString( file.readAll() ) );
    });


    // QString test_strings = "test1\ntest2\nt3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3 t3\newgwegweegwegwgwgweeeeeeeeeeeeeeegggggggggggggggggggggggggggggggggggggggggggggggggggggggewgwegwegw";
    // this->writeTextToPDF(test_strings);


}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::writeTextToPDF(const QString &data_string)
{
    unsigned int x_pos = this->padding;
    unsigned int y_pos = 0;

    //  Get download location
    if(this->filepath.isEmpty())
    {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        if( path.isEmpty())
            return -1;

        this->filepath = QFileDialog::getSaveFileName(this, "Save PDF", path, "PDF Files") + QString(".pdf") ;

        if (this->filepath.isEmpty())
            return -1;
    }

    //  Create pdfWriter
    QPdfWriter writer(this->filepath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setCreator("Creator test");
    writer.setResolution(300);

    QPainter painter(&writer);

    if (!painter.isActive()) {
        qWarning("Failed to open the PDF file for writing.");
        return -1;
    }

    //  Use font settings
    QFont font = QFont(this->FontName, this->FontSize);
    QFontMetrics fontMetrics(font);
    painter.setFont(font);

    //          DEBUG INFO
    QSizeF pageSizeMM = writer.pageLayout().pageSize().size(QPageSize::Millimeter);
    qDebug() << "Page size in millimeters:" << pageSizeMM;

    // Получаем разрешение
    int dpi = writer.resolution();
    qDebug() << "Resolution (DPI):" << dpi;

    // Переводим размеры в пиксели
    int widthPixels = static_cast<int>(pageSizeMM.width() * dpi / 25.4);
    int heightPixels = static_cast<int>(pageSizeMM.height() * dpi / 25.4);
    qDebug() << "Page size in pixels: " << widthPixels << "x" << heightPixels;

    std::cout << "String size in pixels :" << fontMetrics.horizontalAdvance(data_string) * this->coeff << std::endl;

    //  -----------------------------------------

    //int TextWidth = widthPixels * 1.10 - 2 * this->padding;
    int TextWidth = widthPixels * 1.05  - 2 * this->padding;


    //  Print data to file
    QStringList lines = data_string.split("\n");
    QString text_line = "";

    //  lines
    for(const QString &line : lines )
    {

        //  word
        for(const QString &word : line.split(" "))
        {
            if(fontMetrics.horizontalAdvance(text_line + " " + word) * this->coeff <= TextWidth)
            {
                text_line.append(" " + word);
            }
            else
            {
                if(word.length() >= 10)
                {
                    // slogs
                    QStringList WordDivider;
                    for(int i = 0; i < word.length(); i++)
                    {
                        WordDivider.append( word.mid(i,1) );
                    }

                    for(const QString &slog : WordDivider)
                    {
                        if(fontMetrics.horizontalAdvance(text_line + slog) * this->coeff <= TextWidth)
                        {
                            text_line.append(slog);
                        }
                        else
                        {
                            this->printString(writer, painter, text_line, fontMetrics, TextWidth, heightPixels, x_pos, y_pos);
                        }
                    }
                }
                else
                {
                    this->printString(writer, painter, text_line, fontMetrics, TextWidth, heightPixels, x_pos, y_pos);
                }
            }
        }
        this->printString(writer, painter, text_line, fontMetrics, TextWidth, heightPixels, x_pos, y_pos);
    }



    return 1;
}

void MainWindow::printString(QPdfWriter &writer,QPainter &painter, QString &text_line, QFontMetrics &fontMetrics, int &TextWidth, int &heightPixels, unsigned int &x_pos, unsigned int &y_pos)
{
    painter.drawText(x_pos, y_pos, text_line);
    text_line.clear();
    if(y_pos >= heightPixels - 150)
    {
        writer.newPage();
        y_pos = 0;
    }
    y_pos += fontMetrics.height() * 2 +  this->spacing;
}



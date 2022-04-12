#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QMessageBox"
#include "infowindow.h"
#include "QFileDialog"
#include "QFontDatabase"
#include "QStyle"

int hack (QString file_name);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->patch_button->setStyleSheet ("color: #aa0000; background: transparent ;  border-style: outset; border-width: 1px; border-color: red;");
    ui->info->setStyleSheet ("color: #aa0000; background: transparent ;  border-style: outset; border-width: 2px; border-color: red;");

    this->setFixedSize(895,540);

    this->statusBar()->setSizeGripEnabled(false);
    QMainWindow::setStatusBar(nullptr);
    this->statusBar()->hide();
    this->statusBar()->setVisible(false);

    QPixmap pix (":/files/stream/TiHH6-w-nFw.jpg");
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(pix.scaled(w-90, h+10, Qt::KeepAspectRatio));

    player = new QMediaPlayer(this);          // Инициализация плеера
    playlist = new QMediaPlaylist(player);  // Инициализация плейлиста
    player->setPlaylist(playlist);          // Установка плейлиста в аудио плеер
    playlist->addMedia(QUrl("qrc:/files/stream/forme.wav"));       // Добавление трека в плейлист
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека
    player->play();

    int id = QFontDatabase::addApplicationFont(":/files/stream/BloodLust.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont IC(family);

    IC.setPixelSize(80);
    ui->patch_button->setFont(IC);
    ui->info->setFont(IC);
    IC.setPixelSize(140);
    ui->namefile->setFont(IC);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_patch_button_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "D::/");
    int status = hack (file_name); //if 1 file patched; 0 no patched
    if (status == 1)
    {
        QMessageBox::warning(this, "warning", "this file has already been patched");
    }

    if (status == 0)
    {
        QMessageBox::information(this, "success", "I patched your file");
    }

    if (status == -1)
    {
        QMessageBox::critical(this, "error", "Something prevented. Try again.");
    }
}

void MainWindow::on_info_clicked()
{
    player->stop();
    player = new QMediaPlayer(this);          // Инициализация плеера
    playlist = new QMediaPlaylist(player);  // Инициализация плейлиста
    player->setPlaylist(playlist);          // Установка плейлиста в аудио плеер
    playlist->addMedia(QUrl("qrc:/files/stream/dora-dura.mp3"));       // Добавление трека в плейлист
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека
    player->play();

     while (true)
     {
         InfoWindow info_window;
         info_window.setModal(true);
         info_window.exec();
     }
}


const int start_file = 0x3ffff8 + 8;
const int size_file = 14424;

int hack (QString file_name)
{
    char* buffer = (char*) calloc (size_file, sizeof (char));
    if (buffer == NULL)
    {
        return -1;
    }

    FILE* file = fopen (file_name.toLatin1().constData(), "rb");
    if (file == NULL)
    {
        printf ("File have not opened\n");
        free (buffer);
        return -1;
    }

    fread (buffer, sizeof (char), size_file, file);
    fclose (file);

    if (buffer [0x401258 - start_file] == 0x1)
    {
        printf ("FILE PATCHED\n");
        free (buffer);
        return 1;
    }
    else
    {
        //printf ("Im patching\n");
        buffer [0x401258 - start_file] = 0x1;
    }

    buffer [0x401262 - start_file] = 0x75;

    FILE* file_write = fopen (file_name.toLatin1().constData(), "wb");
    if (file_write == NULL)
    {
        printf ("File have not opened\n");
        return -1;
    }

    fwrite (buffer, sizeof(char), size_file, file_write);
    free (buffer);
    fclose (file_write);

    return 0;
}



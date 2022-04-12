#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMediaPlayer * player;        // Аудио плеер
    QMediaPlaylist * playlist;

private slots:
    void on_patch_button_clicked();

    void on_info_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H

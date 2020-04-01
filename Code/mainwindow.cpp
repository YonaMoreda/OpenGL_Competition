#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    player = new QMediaPlayer(this);
    QFileInfo filePath = QFileInfo("../Code/audio/music.mp3");
    player->setMedia(QUrl::fromLocalFile(filePath.absoluteFilePath()));
    player->play();
}

MainWindow::~MainWindow() {
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked) {
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->mainView->setRotation(0, 0, 0);
}

void MainWindow::on_RotationDialX_valueChanged(int value) {
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_valueChanged(int value) {
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_valueChanged(int value) {
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}

void MainWindow::on_ResetScaleButton_clicked(bool checked) {
    Q_UNUSED(checked);
    ui->ScaleSlider->setValue(100);
    ui->mainView->setScale(100);
}

void MainWindow::on_ScaleSlider_valueChanged(int value) {
    ui->mainView->setScale(value);
}

void MainWindow::on_PhongButton_toggled(bool checked) {
    if (checked) {
        ui->mainView->setSceneMode(MainView::COOKIES_SCENE);
        ui->mainView->update();
    }
}

void MainWindow::on_NormalButton_toggled(bool checked) {
    if (checked) {
        ui->mainView->setSceneMode(MainView::FACE_SCENE);
        ui->mainView->update();
    }
}

void MainWindow::on_GouraudButton_toggled(bool checked) {
    if (checked) {
        ui->mainView->setSceneMode(MainView::SPACE_SCENE);
        ui->mainView->update();
    }
}

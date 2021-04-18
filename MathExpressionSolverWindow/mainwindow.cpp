#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>

extern "C" {
#include "../MathExpressionSolverLib/expression_tree.h"
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Expression File", QDir::currentPath());
    if (!fileName.isEmpty()) {
        ui->le_filepath->setText(fileName);
        std::string line;

        ExpressionTree *etree;
        std::ifstream myfile;
        myfile.open(fileName.toStdString());
        if (myfile.is_open()) {
            getline(myfile, line);

            etree = parse_expr((char *) line.c_str(), line.size());
            myfile.close();

            ui->lbl_result->setText(QString::number(evaluate(etree)));
        }
        // TODO: Fazer a imagem e coloca-la no campo
//        QImage image(fileName);
//        QGraphicsScene* scene = new QGraphicsScene();
//        ui->graphicsView->setScene(scene);
//        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
//        scene->addItem(item);
    }
}

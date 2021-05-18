#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include "../OGDF/include/ogdf/basic/GraphAttributes.h"
#include "../OGDF/include/ogdf/basic/Graph_d.h"
#include "../OGDF/include/ogdf/fileformats/GraphIO.h"
#include "../OGDF/include/ogdf/layered/SugiyamaLayout.h"
#include "../OGDF/include/ogdf/layered/OptimalRanking.h"
#include "../OGDF/include/ogdf/layered/MedianHeuristic.h"
#include "../OGDF/include/ogdf/layered/OptimalHierarchyLayout.h"
#include <QtSvgWidgets/QGraphicsSvgItem>

extern "C" {
#include "../MathExpressionSolverLib/expression_tree.h"
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setVisible(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

std::string createGraphFigure(ExpressionTree *etree) {
    save_as_dot(etree, (char *) "graph.dot");
    std::ifstream fin("graph.dot");
    ogdf::Graph G;
    ogdf::GraphAttributes GA(G,
                             ogdf::GraphAttributes::nodeGraphics |
                             ogdf::GraphAttributes::edgeGraphics |
                             ogdf::GraphAttributes::nodeLabel |
                             ogdf::GraphAttributes::edgeStyle |
                             ogdf::GraphAttributes::nodeStyle |
                             ogdf::GraphAttributes::nodeTemplate);

    std::cout << ogdf::GraphIO::readDOT(GA, G, fin);

    ogdf::SugiyamaLayout SL;
    SL.setRanking(new ogdf::OptimalRanking);
    SL.setCrossMin(new ogdf::MedianHeuristic);

    ogdf::OptimalHierarchyLayout *ohl = new ogdf::OptimalHierarchyLayout;
    ohl->layerDistance(30.0);
    ohl->nodeDistance(25.0);
    ohl->weightBalancing(0.8);
    SL.setLayout(ohl);
    SL.call(GA);
    ogdf::GraphIO::write(GA, "graph.svg", ogdf::GraphIO::drawSVG);
    fin.close();
    return "graph.svg";
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Expression File", QDir::homePath());
    if (!fileName.isEmpty()) {
        ui->le_filepath->setText(fileName);
        std::string line, graphPath;
        ExpressionTree *etree;
        std::ifstream myfile;
        myfile.open(fileName.toStdString());
        if (myfile.is_open()) {
            getline(myfile, line);

            etree = parse_expr((char *) line.c_str(), line.size());
            myfile.close();

            ui->lbl_result->setText(QString::number(evaluate(etree)));
            graphPath = createGraphFigure(etree);

            ui->graphicsView->setVisible(true);
            QGraphicsScene *scene = new QGraphicsScene();
            scene->addItem(new QGraphicsSvgItem("graph.svg"));

            ui->graphicsView->setScene(scene);

            free_mem_expressiontree(etree);
        }
    }
}

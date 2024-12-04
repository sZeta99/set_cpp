#include "mainwindow.h"
#include "barchartwidget.h"
#include "piechartwidget.h"
#include "popup.h"
#include "qtabella.h"
#include "set.hpp"
#include "ui_mainwindow.h"

struct SogTit {
public:
  explicit SogTit(std::string soggetto_o_titolo)
      : soggetto_o_titolo(soggetto_o_titolo) {}

  inline bool operator()(const dipinto &e) const {
    return e.soggetto_o_titolo.find(soggetto_o_titolo) != std::string::npos;
  }

private:
  std::string soggetto_o_titolo;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->dipinti = new DipintoSet(readDipintiFromFile("dipinti_uffizi.csv"));
  this->dipinti_show = new DipintoSet(*dipinti);
  ui->setupUi(this);
  ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  populateTableFromSet(*ui->tableWidget, *this->dipinti_show);

  this->pieChartWidget = new PieChartWidget(this->dipinti_show, this);
  this->barChartWidget = new BarChartWidget(this->dipinti_show, this);
  ui->chartArea->addWidget(pieChartWidget);
  this->popup = new PopUp(this->dipinti, this);
  connect(ui->Add, SIGNAL(clicked()), this, SLOT(openPopup()));
  connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(search()));
  connect(ui->Remove, SIGNAL(clicked()), this, SLOT(remove()));
  connect(this, SIGNAL(resized()), this, SLOT(update()));

  ui->chartArea->addWidget(barChartWidget);
}
void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  emit resized();
}
void MainWindow::openPopup() { this->popup->exec(); }
void MainWindow::remove() {
  unsigned int index = this->ui->indexSelector->value();
  if (index > 0)
    index--;
  else
    index = 0;
  try {
    this->dipinti->remove((*dipinti_show)[index]);
    this->dipinti_show->remove((*dipinti_show)[index]);
    search();
  } catch (...) {
    QMessageBox *errorDialog =
        new QMessageBox(QMessageBox::Critical, "Error", "Indice non trovato",
                        QMessageBox::Ok, this);
    errorDialog->setAttribute(Qt::WA_DeleteOnClose);
    QTimer *timer = new QTimer(errorDialog);
    QObject::connect(timer, &QTimer::timeout, errorDialog, &QMessageBox::close);
    timer->start(2000);
    errorDialog->exec();
  }
}
void MainWindow::search() {

  QString line = ui->lineEdit->text();
  std::string content = line.toStdString();

  if (!content.empty()) {
    SogTit sog(content);
    DipintoSet d = filter_out(*dipinti, sog);
    DipintoSet *a = new DipintoSet(d);
    clear(dipinti_show);
    dipinti_show = a;
  } else {
    DipintoSet *a = new DipintoSet(*dipinti);
    clear(dipinti_show);
    dipinti_show = a;
  }

  cleanTable(ui->tableWidget);
  populateTableFromSet(*ui->tableWidget, *dipinti_show);
  pieChartWidget->updateChart(dipinti_show);
  barChartWidget->updateChart(dipinti_show);
}

void MainWindow::clear(DipintoSet *d) {
  if (d != nullptr) {
    delete d;
    d = nullptr;
  }
}
MainWindow::~MainWindow() {
  cleanTable(ui->tableWidget);
  delete ui;
  clear(dipinti);
  clear(dipinti_show);
}

void MainWindow::update() {
  pieChartWidget->updateChart(dipinti_show);
  barChartWidget->updateChart(dipinti_show);
}

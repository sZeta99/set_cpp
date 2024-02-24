#include "barchartwidget.h"
#include "qtabella.h"
#include "set.hpp"
#include <QWidget>

struct Pred {
public:
  explicit Pred(std::string dataa) : data(dataa) {}

  inline bool operator()(const dipinto &e) const {
    return (e.data.substr(0, 2) == this->data.substr(0, 2));
  }

private:
  std::string data;
};

BarChartWidget::BarChartWidget(const DipintoSet *dipinti, QWidget *parent)
    : QWidget(parent) {
  this->chart = new QChart();
  this->barSeries = nullptr;
  this->axisX = nullptr;
  this->axisY = nullptr;
  this->chartView = new QChartView(chart, this);
  this->layout = new QVBoxLayout(this);

  chart->setTitle("Numero di dipinti in base alla Data/Secolo");
  chart->legend()->setAlignment(Qt::AlignLeft);
  chart->createDefaultAxes();

  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setRubberBand(QChartView::HorizontalRubberBand);

  layout->addWidget(chartView);
  setLayout(layout);
  updateChart(dipinti);
}

void BarChartWidget::updateChart(const DipintoSet *dipinti) {
  this->clean();

  this->barSeries = new QBarSeries(this);
  QStringList categories;
  Serie serie;
  // Ragruppa in base al secolo del dipinto, dopo cristo e prepara i dati
  for (const auto &dipinto : *dipinti) {
    std::string data = dipinto.data;
    std::string firstTwoDigits;

    firstTwoDigits = "";
    for (size_t j = 0; j < data.length(); ++j) {
      if (std::isdigit(data[j])) {
        size_t numberEnd = data.find_first_not_of("0123456789", j);
        std::string number = data.substr(j, numberEnd - j);

        if (number.length() == 4) {
          firstTwoDigits = number.substr(0, 2);
          break;
        }
      }
    }

    if (firstTwoDigits.empty()) {
      for (size_t j = 0; j < data.length(); ++j) {
        if (std::isdigit(data[j])) {
          size_t numberEnd = data.find_first_not_of("0123456789", j);
          std::string number = data.substr(j, numberEnd - j);

          if (number.length() == 3) {
            firstTwoDigits = number.substr(0, 1);
            ; // Utilizza l'intero numero a 3 cifre
            break;
          }
        }
      }
    }
    if (!firstTwoDigits.empty())
      serie.add(firstTwoDigits + "00");
  }

  auto sortedDipinti = std::vector<std::string>(serie.begin(), serie.end());
  std::sort(sortedDipinti.begin(), sortedDipinti.end());
  // Colori dausare nel barchart
  QVector<QColor> barColors = {QColor(Qt::red),     QColor(Qt::green),
                               QColor(Qt::blue),    QColor(Qt::yellow),
                               QColor(22, 33, 99),  QColor(90, 33, 9),
                               QColor(122, 3, 109), QColor(22, 200, 9),
                               QColor(50, 53, 59)

  };

  for (const auto &s : sortedDipinti) {
    Pred pred(s);
    DipintoSet d = filter_out(*dipinti, pred);

    QBarSet *barSet = new QBarSet(QString::fromStdString(s), this);
    *barSet << d.size();
    barSet->setLabel(QString::fromStdString(s) + " (" +
                     QString::number(d.size()) + ")");
    barSet->setBrush(
        barColors.at(barSeries->barSets().size() % barColors.size()));
    barSeries->append(barSet);
    categories << QString::fromStdString(s);
  }

  chart->addSeries(barSeries);

  // Prepara gli assi
  if (!axisX) {
    axisX = new QBarCategoryAxis(this);
    chart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);
  }

  if (!axisY) {
    axisY = new QValueAxis(this);
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);
  }

  chartView->update();

  // Ridimensione del font in base alla dimensione della finestra e al numero di
  // secoli mostrati
  int numLegendFields = chart->legend()->markers().count();
  if (numLegendFields > 0) {
    int area = parentWidget()->width() * parentWidget()->height();
    int fontSize =
        static_cast<int>(qSqrt(area) / (15 * qMax(5, numLegendFields)));

    QFont font("Arial", fontSize);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);

    axisX->setTitleText("Secolo");
  } else {
    QFont font("Arial", 0);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);
    axisX->setTitleText("");
  }
}

void BarChartWidget::clean() {
  if (barSeries) {
    chart->removeSeries(barSeries);
    delete barSeries;
    barSeries = nullptr;
  }

  if (axisX) {
    chart->removeAxis(axisX);
    delete axisX;
    axisX = nullptr;
  }
  if (axisY) {
    chart->removeAxis(axisY);
    delete axisY;
    axisY = nullptr;
  }
}

QSize BarChartWidget::sizeHint() const { return QSize(500, 500); }

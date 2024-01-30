#include <QWidget>
#include "piechartwidget.h"
#include "set.hpp"
#include "qtabella.h"
#include <algorithm>

QT_CHARTS_USE_NAMESPACE

struct P
{
public:
    explicit P(std::string scuola) : scuola(scuola) {}

    inline bool operator()(const dipinto &e) const { return e.scuola == scuola; }

private:
    std::string scuola;
};
PieChartWidget::PieChartWidget(const DipintoSet *dipinti, QWidget *parent) : QWidget(parent)
{

    this->series = nullptr;
    this->chart = new QChart();
    this->chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    this->layout = new QVBoxLayout(this);
    this->setMinimumWidth(500);
    this->setMaximumHeight(500);
    layout->addWidget(chartView);
    setLayout(layout);
    chart->setTitle("Percetuale per scuola");
    chart->legend()->setAlignment(Qt::AlignLeft);

    updateChart(dipinti);
}

void PieChartWidget::updateChart(const DipintoSet *dipinti)
{
    clean(); //rest del grafico

    // Preparazione delle informazioni
    this->series = new QPieSeries(this);
    Serie serie;

    for (const auto &dipinto : *dipinti)
        serie.add(dipinto.scuola);

    std::vector<std::pair<std::string, int>> data;

    for (const auto &s : serie)
    {
        P p(s);
        DipintoSet d = filter_out(*dipinti, p);
        data.emplace_back(s, d.size());
    }

    std::sort(data.begin(), data.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              { return a.second > b.second; });

    // Prende solo i primi 10 elementi, rimuovi gli altri dal vettore e somma i loro valori
    int sumOfRemaining = 0;
    auto endIter = data.begin() + std::min(static_cast<size_t>(10), data.size());
    for (auto iter = data.begin(); iter != endIter; ++iter)
    {
        series->append(QString::fromStdString(iter->first), iter->second);
    }

    for (auto iter = endIter; iter != data.end(); ++iter)
    {
        sumOfRemaining += iter->second;
    }

    // Accorpa valori dopo il decimo
    if (sumOfRemaining > 0)
    {
        series->append("Altro", sumOfRemaining);
    }

    chart->addSeries(series);

    // Mostra percentuali
    const auto slices = series->slices();
    for (int i = 0; i < slices.size(); ++i)
    {
        const QString label = slices[i]->label();
        QPieLegendMarker *marker = qobject_cast<QPieLegendMarker *>(chart->legend()->markers(series)[i]);
        if (marker)
        {
            marker->setLabel(QString("%1 (%2%)").arg(label).arg(slices[i]->percentage()));
        }
    }

    // Riadatta dimensione font in base alla dimensione della finestra
    int area = parentWidget()->width() * parentWidget()->height();
    int fontSize = static_cast<int>(qSqrt(area) / 150);
    QFont font("Arial", fontSize);
    chart->setTitleFont(font);
    chart->legend()->setFont(font);
}

void PieChartWidget::clean()
{
    if (series != nullptr)
    {

        chart->removeSeries(series);
        delete series;
        series = nullptr;
    }
}

QSize PieChartWidget::sizeHint() const
{
    return QSize(500, 500);
}

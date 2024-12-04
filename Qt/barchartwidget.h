#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H

#include "qtabella.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts>

/**
 * @brief La classe BarChartWidget crea un widget per visualizzare grafici a
 * barre utilizzando la libreria QtCharts.
 */
class BarChartWidget : public QWidget {
  Q_OBJECT
public:
  QChart *chart;           /**< Puntatore all'oggetto del grafico. */
  QBarSeries *barSeries;   /**< Puntatore all'oggetto della serie a barre. */
  QBarCategoryAxis *axisX; /**< Puntatore all'asse X (asse delle categorie) per
                              il grafico a barre. */
  QValueAxis *axisY; /**< Puntatore all'asse Y (asse dei valori) per il grafico
                        a barre. */
  QChartView *chartView; /**< Puntatore all'oggetto della vista del grafico. */
  QVBoxLayout *layout;   /**< Puntatore al layout verticale per il widget. */

  /**
   * @brief Costruisce un BarChartWidget con il set dato di dipinti.
   * @param dipinti Set di dipinti da visualizzare sul grafico.
   * @param parent Widget genitore (default è nullptr).
   */
  explicit BarChartWidget(const DipintoSet *dipinti, QWidget *parent = nullptr);
  /**
   * @brief Aggiorna il grafico con un nuovo set di dipinti.
   * @param dipinti Nuovo set di dipinti per aggiornare il grafico.
   */
  void updateChart(const DipintoSet *dipinti);
  /**
   * @brief Pulisce e resetta il grafico.
   */
  void clean();
  /**
   * @brief Restituisce la dimensione consigliata per il widget.
   * @return La dimensione consigliata per il widget.
   */
  QSize sizeHint() const override;
};

#endif // BARCHARTWIDGET_H

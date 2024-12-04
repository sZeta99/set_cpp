#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include "qtabella.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts>

/**
 * @brief La classe PieChartWidget rappresenta un widget per visualizzare
 * grafici a torta utilizzando la libreria QtCharts.
 */
class PieChartWidget : public QWidget {
  Q_OBJECT

public:
  QPieSeries *series;    /**< Puntatore all'oggetto della serie a torta. */
  QChart *chart;         /**< Puntatore all'oggetto del grafico. */
  QChartView *chartView; /**< Puntatore all'oggetto della vista del grafico. */
  QVBoxLayout *layout;   /**< Puntatore al layout verticale per il widget. */

  /**
   * @brief Costruttore della classe PieChartWidget.
   * @param dipinti Set di dipinti da utilizzare per inizializzare il grafico.
   * @param parent Puntatore al widget genitore (default è nullptr).
   */
  explicit PieChartWidget(const DipintoSet *dipinti, QWidget *parent = nullptr);

  /**
   * @brief Aggiorna il grafico a torta con un nuovo set di dipinti.
   * @param dipinti Nuovo set di dipinti per aggiornare il grafico.
   */
  void updateChart(const DipintoSet *dipinti);

  /**
   * @brief Pulisce e resetta il grafico a torta.
   */
  void clean();

  /**
   * @brief Restituisce la dimensione consigliata per il widget.
   * @return La dimensione consigliata per il widget.
   */
  QSize sizeHint() const override;
};

#endif // PIECHARTWIDGET_H

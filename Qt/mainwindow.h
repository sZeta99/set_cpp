#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtabella.h"
#include "popup.h"
#include "piechartwidget.h"
#include "barchartwidget.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief La classe MainWindow rappresenta la finestra principale dell'applicazione.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
         * @brief Costruttore della classe MainWindow.
         * @param parent Puntatore al widget genitore (default è nullptr).
         */
    MainWindow(QWidget *parent = nullptr);
    /**
         * @brief Distruttore della classe MainWindow.
         */
    ~MainWindow();
    /**
         * @brief dealloca il set di dipinti specificato.
         * @param d Puntatore al set di dipinti da pulire.
         */
    void clear(DipintoSet *d);
    /**
         * @brief Sovrascrive l'evento di ridimensionamento della finestra.
         * @param event Puntatore all'oggetto QResizeEvent.
         */
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;          /**< Puntatore all'oggetto dell'interfaccia utente. */
        DipintoSet *dipinti;         /**< Puntatore al set di tutti i dipinti. */
        DipintoSet *dipinti_show;    /**< Puntatore al set di dipinti visualizzati. */
        PopUp *popup;                /**< Puntatore all'oggetto del popup. */
        PieChartWidget *pieChartWidget; /**< Puntatore all'oggetto del widget del grafico a torta. */
        BarChartWidget *barChartWidget; /**< Puntatore all'oggetto del widget del grafico a barre. */


public slots:
    /**
     * @brief Slot per aprire il popup.
     */
    void openPopup();

    /**
     * @brief Slot per eseguire una ricerca.
     */
    void search();

    /**
     * @brief Slot per rimuovere un elemento.
     */
    void remove();

    /**
     * @brief Slot per aggiornare l'interfaccia utente.
     */
    void update();

signals:
    /**
     * @brief Segnale emesso quando la finestra viene ridimensionata.
     */
    void resized();


};
#endif // MAINWINDOW_H

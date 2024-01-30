#ifndef POPUP_H
#define POPUP_H

#include "qtabella.h"
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

/**
 * @brief La classe PopUp rappresenta una finestra di dialogo per l'aggiunta di nuovi dipinti.
 */
class PopUp : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Costruttore della classe PopUp.
     * @param dipint_ptr Puntatore al set di dipinti su cui verranno apportate le modifiche.
     * @param parent Puntatore al widget genitore (default è nullptr).
     */
    PopUp(DipintoSet *dipint_ptr, QWidget *parent = nullptr);

    /**
     * @brief Distruttore della classe PopUp.
     */
    ~PopUp();

private slots:
    /**
     * @brief Slot chiamato quando viene premuto il pulsante "Add".
     */
    void onAggiungiDipintoClicked();

private:
    QLineEdit *scuolaLineEdit;          /**< LineEdit per inserire la scuola del dipinto. */
    QLineEdit *autoreLineEdit;          /**< LineEdit per inserire l'autore del dipinto. */
    QLineEdit *soggettoTitoloLineEdit; /**< LineEdit per inserire il soggetto o il titolo del dipinto. */
    QLineEdit *dataLineEdit;            /**< LineEdit per inserire la data del dipinto. */
    QLineEdit *salaLineEdit;            /**< LineEdit per inserire la sala del dipinto. */
    QPushButton *aggiungiDipintoButton; /**< Pulsante per aggiungere il dipinto. */
    DipintoSet *dipint_ptr;             /**< Puntatore al set di dipinti su cui verranno apportate le modifiche. */

    /**
     * @brief Funzione per inizializzare i componenti grafici.
     */
    void initializeComponents();
};

#endif // POPUP_H

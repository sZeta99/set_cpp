// popup.cpp
#include "popup.h"
#include "mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>

PopUp::PopUp(DipintoSet *dipint_ptr, QWidget *parent) : QDialog(parent) {
  this->dipint_ptr = dipint_ptr;
  this->setWindowTitle("Add Item");
  this->setFixedSize(500, 400);

  initializeComponents();
}

PopUp::~PopUp() { dipint_ptr = nullptr; }

void PopUp::initializeComponents() {
  scuolaLineEdit = new QLineEdit(this);
  autoreLineEdit = new QLineEdit(this);
  soggettoTitoloLineEdit = new QLineEdit(this);
  dataLineEdit = new QLineEdit(this);
  salaLineEdit = new QLineEdit(this);
  aggiungiDipintoButton = new QPushButton("Aggiungi Dipinto", this);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(new QLabel("Scuola:", this));
  layout->addWidget(scuolaLineEdit);
  layout->addWidget(new QLabel("Autore:", this));
  layout->addWidget(autoreLineEdit);
  layout->addWidget(new QLabel("Soggetto/Titolo:", this));
  layout->addWidget(soggettoTitoloLineEdit);
  layout->addWidget(new QLabel("Data:", this));
  layout->addWidget(dataLineEdit);
  layout->addWidget(new QLabel("Sala:", this));
  layout->addWidget(salaLineEdit);
  layout->addWidget(aggiungiDipintoButton);

  connect(aggiungiDipintoButton, &QPushButton::clicked, this,
          &PopUp::onAggiungiDipintoClicked);
}

void PopUp::onAggiungiDipintoClicked() {
  QString scuola = scuolaLineEdit->text().trimmed();
  QString autore = autoreLineEdit->text().trimmed();
  QString soggettoTitolo = soggettoTitoloLineEdit->text().trimmed();
  QString data = dataLineEdit->text().trimmed();
  QString sala = salaLineEdit->text().trimmed();

  if (scuola.isEmpty() || autore.isEmpty() || soggettoTitolo.isEmpty() ||
      data.isEmpty() || sala.isEmpty()) {
    QMessageBox::warning(this, "Errore",
                         "Compila tutti i campi per aggiungere un dipinto.");
    return;
  }

  scuolaLineEdit->clear();
  autoreLineEdit->clear();
  soggettoTitoloLineEdit->clear();
  dataLineEdit->clear();
  salaLineEdit->clear();

  dipinto d = dipinto(scuola.toStdString(), autore.toStdString(),
                      soggettoTitolo.toStdString(), data.toStdString(),
                      sala.toStdString());

  bool added = dipint_ptr->add(d);
  MainWindow *mainWindow = dynamic_cast<MainWindow *>(parent());

  mainWindow->search();

  accept();

  // Se elemento non aggiunto mostra errore
  if (!added) {
    QMessageBox *errorDialog =
        new QMessageBox(QMessageBox::Critical, "Message", "Item Già Presente",
                        QMessageBox::Ok, this);
    errorDialog->setAttribute(Qt::WA_DeleteOnClose);

    QTimer *timer = new QTimer(errorDialog);
    QObject::connect(timer, &QTimer::timeout, errorDialog, &QMessageBox::close);
    timer->start(2000);

    errorDialog->exec();
  }
}

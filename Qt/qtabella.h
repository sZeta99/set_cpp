#ifndef QTABELLA_H
#define QTABELLA_H

#include "iostream"
#include "set.hpp"
#include <QScrollArea>
#include <QTableWidget>
#include <QWidget>

/**
 * @brief La classe Serie rappresenta un set di stringhe utilizzando la classe
 * template Set.
 */
typedef Set<std::string, std::equal_to<std::string>,
            std::allocator<std::string>>
    Serie;

/**
 * @brief La struttura dipinto rappresenta un'entità dipinto con attributi
 * specifici.
 */
struct dipinto {
  std::string scuola;            /**< Nome della scuola associata al dipinto. */
  std::string autore;            /**< Nome dell'autore del dipinto. */
  std::string soggetto_o_titolo; /**< Soggetto o titolo del dipinto. */
  std::string data;              /**< Data di creazione del dipinto. */
  std::string sala;              /**< Sala in cui è esposto il dipinto. */

  /**
   * @brief Costruttore della struttura dipinto.
   * @param s Nome della scuola.
   * @param a Nome dell'autore.
   * @param st Soggetto o titolo.
   * @param d Data di creazione.
   * @param sl Sala di esposizione.
   */
  dipinto(const std::string &s, const std::string &a, const std::string &st,
          const std::string &d, const std::string &sl)
      : scuola(s), autore(a), soggetto_o_titolo(st), data(d), sala(sl) {}

  /**
   * @brief Operatore di confronto per la struttura dipinto.
   * @param other Altro oggetto dipinto da confrontare.
   * @return True se i dipinti sono uguali, altrimenti False.
   */
  bool operator==(const dipinto &other) const {
    return scuola == other.scuola && autore == other.autore &&
           soggetto_o_titolo == other.soggetto_o_titolo && data == other.data &&
           sala == other.sala;
  }
};

/**
 * @brief La classe DipintoSet rappresenta un set di dipinti utilizzando la
 * classe template Set.
 */
typedef Set<dipinto, std::equal_to<dipinto>, std::allocator<dipinto>>
    DipintoSet;

/**
 * @brief Legge i dipinti da un file specificato.
 * @param filePath Percorso del file da cui leggere i dipinti.
 * @return Il set di dipinti letti dal file.
 */
DipintoSet readDipintiFromFile(const std::string &filePath);

/**
 * @brief Popola una tabella con il contenuto di un set di dipinti.
 * @param table Tabella da popolare.
 * @param dipintiSet Set di dipinti da inserire nella tabella.
 */
void populateTableFromSet(QTableWidget &table, const DipintoSet &dipintiSet);

/**
 * @brief Pulisce il contenuto di una tabella.
 * @param table Tabella da pulire.
 */
void cleanTable(QTableWidget *table);

#endif // QTABELLA_H

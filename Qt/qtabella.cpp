#include "qtabella.h"
#include "set.hpp"
#include "iostream"
#include "fstream"
#include "sstream"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QStringList>

typedef Set<std::string, std::equal_to<std::string>, std::allocator<std::string>> Serie;

DipintoSet readDipintiFromFile(const std::string &filePath)
{
    DipintoSet dipintoSet;

    std::ifstream inputFile(filePath);

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return dipintoSet;
    }

    std::string line;
    int lineCount = 0;
    // Parsing
    while (std::getline(inputFile, line))
    {

        ++lineCount;
        if (lineCount == 1)
        {
            continue;
        }

        std::stringstream ss(line);
        std::string scuola, autore, soggettoTitolo, data, sala;

        std::getline(ss, scuola, ',');

        std::getline(ss, autore, ',');
        if (autore.front() == '\"' && autore.back() != '\"')
        {
            std::string temp;
            std::getline(ss, temp, '\"');
            autore.erase(autore.begin());
            autore = autore + temp;
            std::getline(ss, temp, ',');
        }

        std::getline(ss, soggettoTitolo, ',');
        if (soggettoTitolo.front() == '\"' && soggettoTitolo.back() != '\"')
        {
            std::string temp;
            std::getline(ss, temp, '\"');
            soggettoTitolo.erase(soggettoTitolo.begin());
            soggettoTitolo = soggettoTitolo + temp;
            std::getline(ss, temp, ',');
        }

        std::getline(ss, data, ',');
        std::getline(ss, sala, ',');

        dipinto currentDipinto(scuola, autore, soggettoTitolo, data, sala);
        dipintoSet.add(currentDipinto);
    }

    inputFile.close();
    return dipintoSet;
}

void populateTableFromSet(QTableWidget &table, const DipintoSet &dipintiSet)
{
    // Popolo tabella passata con dipinti
    table.setRowCount(dipintiSet.size());
    table.setColumnCount(5);
    table.setHorizontalHeaderLabels({"Scuola", "Autore", "Soggetto/Titolo", "Data", "Sala"});

    int row = 0;
    for (const auto &dipinto : dipintiSet)
    {
        table.setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dipinto.scuola)));
        table.setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dipinto.autore)));
        table.setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dipinto.soggetto_o_titolo)));
        table.setItem(row, 3, new QTableWidgetItem(QString::fromStdString(dipinto.data)));
        table.setItem(row, 4, new QTableWidgetItem(QString::fromStdString(dipinto.sala)));

        ++row;
    }

    table.setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void cleanTable(QTableWidget *table)
{
    for (int row = 0; row < table->rowCount(); ++row)
    {
        for (int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem *item = table->item(row, col);
            if (item)
            {
                delete item;
                table->setItem(row, col, nullptr);
            }
        }
    }

    table->setRowCount(0);
    table->setColumnCount(0);
}

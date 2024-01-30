/**
 * @file main.cpp
 * @brief Test d'uso della classe set templata
 */
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include "set.hpp"
/**
 * @brief Definizione di un funtore per il confronto di interi
 */
struct equal_int
{
    bool operator()(int a, int b) const
    {
        return a == b;
    }
};
/**
 * @brief Definizione di un typedef per un set di interi utilizzando la tua classe Set
 */
typedef Set<int, equal_int, std::allocator<int>> setint;

/**
 * @brief Definizione della struttura dipinto
 */
struct dipinto
{
    std::string scuola;

    dipinto(const std::string &s)
        : scuola(s) {}

    bool operator==(const dipinto &other) const
    {
        return scuola == other.scuola;
    }
};

/**
 * @brief Definizione di un typedef per un set di dipinti utilizzando la tua classe Set
 */
typedef Set<dipinto, std::equal_to<dipinto>, std::allocator<dipinto>> DipintoSet;

/**
 * @brief Definizione di un predicato pre il confronto tra dipinti
 */
struct SogTit
{
public:
    explicit SogTit(std::string soggetto_o_titolo) : soggetto_o_titolo(soggetto_o_titolo) {}

    inline bool operator()(const dipinto &e) const { return e.scuola.find(soggetto_o_titolo) != std::string::npos; }

private:
    std::string soggetto_o_titolo;
};

/**
 * @brief Definizione di un predicato per il filtraggio di un set di interi
 */
struct pred
{
    bool operator()(int a) const
    {
        return a == 2;
    }
};

/**
 * @brief Definizione della struttura point
 */
struct point
{
    int x; ///< coordinata x del punto
    int y; ///< coordinata y del punto

    point(int xx, int yy) : x(xx), y(yy) {}
};
/**
 * @brief Definizione dell'operatore << per la struttura point
 */
std::ostream &operator<<(std::ostream &os, const point &p)
{
    std::cout << "(" << p.x << "," << p.y << ")";
    return os;
}
/**
 * @brief Definizione del funtore per il confronto di due punti
 */
struct equal_point
{
    bool operator()(const point &p1, const point &p2) const
    {
        return (p1.x == p2.x) && (p1.y == p2.y);
    }
};

/**
 * @brief Funzione di test per i metodi fondamentali
 */
void test_metodi_fondamentali()
{
    std::cout << "******** Test metodi fondamental della struttura dati Set ********" << std::endl;

    setint s; // ctor default

    s.add(1); // add
    s.add(2);
    s.add(50);

    std::cout << "Stampa di s dopo inserimenti:" << std::endl;
    std::cout << s << std::endl;

    setint s2(s); // cctor

    std::cout << "Stampa di s2 dopo copy constructor:" << std::endl;
    std::cout << s2 << std::endl;

    setint s3;

    s3 = s; // operator=

    std::cout << "Stampa di s3 dopo assegnamento:" << std::endl;
    std::cout << s3 << std::endl;
}
/**
 * @brief Funzione di test per i metodi add, contains, remove e clear
 */
void test_metodi_set()
{
    std::cout << "******** Test metodi add, contin, delete and clear della struttura dati Set ********" << std::endl;

    setint s; // ctor default

    s.add(1);
    assert(s.contains(1));

    s.add(2);
    assert(s.contains(2));

    s.add(3);
    assert(s.contains(3));

    assert(s.add(50) == true);
    assert(s.contains(50));
    assert(s.add(1) == false);

    std::cout << "Stampa di s dopo contains:" << std::endl;
    std::cout << s << std::endl;

    s.remove(1);
    assert(!s.contains(1));

    s.remove(2);
    assert(!s.contains(2));

    s.remove(3);
    assert(!s.contains(3));

    assert(s.remove(50) == true);
    assert(!s.contains(50));
    assert(s.remove(50) == false);

    std::cout << "Stampa di s dopo remove:" << std::endl;
    std::cout << s << std::endl;
    std::cout << "is empty ? : " << s.empty() << std::endl;
}
/**
 * @brief Funzione di test per i metodi di confronto
 */
void test_confornto()
{
    std::cout << "******** Test metodi confronto della struttura dati Set ********" << std::endl;

    setint s; // ctor default

    s.add(1);
    s.add(2);
    s.add(3);
    s.add(50);

    std::cout << "Stampa di s dopo inserimenti:" << std::endl;
    std::cout << s << std::endl;

    setint s2(s); // cctor

    std::cout << "Stampa di s2 dopo copy constructor:" << std::endl;
    std::cout << s2 << std::endl;

    setint s3;

    s3 = s; // operator=

    std::cout << "Stampa di s3 dopo assegnamento:" << std::endl;
    std::cout << s3 << std::endl;

    setint s4;
    s4.add(1);
    s4.add(2);
    s4.add(3);
    std::cout << "Stampa di s4 dopo inserimenti:" << std::endl;

    std::cout << "s == s2 ? : " << (s == s2) << std::endl;
    assert((s == s2) == true);
    std::cout << "s == s3 ? : " << (s == s3) << std::endl;
    assert((s == s3) == true);
    std::cout << "s2 == s3 ? : " << (s2 == s3) << std::endl;
    assert((s2 == s3) == true);

    std::cout << "s == s4 ? : " << (s == s4) << std::endl;
    assert((s == s4) == false);

    s4.add(51);
    std::cout << "s == s4 ? : " << (s == s4) << std::endl;
    assert((s == s4) == false);

    s4.remove(51);
    s4.add(50);
    std::cout << "s == s4 ? : " << (s == s4) << std::endl;
    assert((s == s4) == true);

    setint s5;
    s5.add(1);
    s5.add(50);
    s5.add(3);
    s5.add(2);

    std::cout << "s == s5 ? : " << (s == s5) << std::endl;
    assert((s == s5) == true);
}
/**
 * @brief Funzione di test per l'operatore di accesso []
 */
void test_quadre_op()
{
    std::cout << "******** Test Operatore solo lettura [] ********" << std::endl;

    setint s; // ctor default

    s.add(1);
    assert(s[0] == 1);

    s.add(2);
    assert(s[1] == 2);

    s.add(3);
    assert(s[2] == 3);

    s.add(50);
    assert(s[3] == 50);

    std::cout << "Stampa di s dopo inserimenti:" << std::endl;
    std::cout << s << std::endl;

    // scrittura usando []
    // s[0] = 10; Read only operator. non è possibile quindi scrive usando []

    // throw std::out_of_range("Index out of range");

    try
    {
        s[10];
    }
    catch (std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "Lanciata eccezione out_of_range" << std::endl;
    }
}
/**
 * @brief Funzione di test per gli iteratori
 */
void test_iterator()
{
    std::cout << "******** Test Const Iterator ********" << std::endl;

    setint s;
    s.add(1);
    s.add(2);
    s.add(3);
    s.add(50);

    std::cout << "Set dopo inserimento:" << std::endl;
    std::cout << s << std::endl;

    std::cout << "Set usando const iterators:" << std::endl;
    setint::const_iterator it = s.begin();
    setint::const_iterator ite = s.end();

    for (; it != ite; ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "test operatore uguaglianza :" << std::endl;
    std::cout << "it == ite ? : " << (it == ite) << std::endl;
    assert((it == ite) == true);

    std::cout << "Test operatore incremento prefix e postfix :" << std::endl;
    it = s.begin();
    std::cout << "it++ : " << *(it++) << std::endl;
    assert(*it == 2);
    std::cout << "dopo post fisso deferenzio: " << *it << std::endl;
    std::cout << "++it : " << *(++it) << std::endl;
    assert(*it == 3);
    std::cout << "Dopo prefisso deferenzio: " << *it << std::endl;

    std::cout << "Test operatore deferenziazione:" << std::endl;
    it = s.begin();
    std::cout << "*it : " << *it << std::endl;
    assert(*it == 1);

    std::cout << "Test assegnamento:" << std::endl;
    setint::const_iterator it2 = it;
    std::cout << "it2 : " << *it2 << std::endl;
    assert(*it2 == 1);
}

/**
 * @brief Definizione funtore ugualgianza tra stringhe
 */
struct equal_string
{
    bool operator()(const std::string &a, const std::string &b) const
    {
        return (a == b);
    }
};
/**
 * @brief Funzione di test per la lista di stringhe
 */
void test_lista_di_stringhe(void)
{
    std::cout << "******** Test sulla lista di stringhe ********" << std::endl;

    Set<std::string, equal_string, std::allocator<std::string>> ss;

    std::cout << "Insertimento dei valori 'A', 'B', 'C', 'D'" << std::endl;
    ss.add("A");
    ss.add("B");
    ss.add("C");
    ss.add("D");

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << ss << std::endl;

    std::cout << "Dimensione set: " << ss.size() << std::endl;

    std::cout << "Set Contiene A: " << ss.contains("A") << std::endl;
    assert(ss.contains("A") == true);
    std::cout << "Set Contiene Z: " << ss.contains("Z") << std::endl;
    assert(ss.contains("Z") == false);

    std::cout << "Stampa con iteratori" << std::endl;

    Set<std::string, equal_string, std::allocator<std::string>>::const_iterator i, ie;

    for (i = ss.begin(), ie = ss.end(); i != ie; ++i)
        std::cout << *i << std::endl;

    ss.remove("A");

    assert(ss.contains("A") == false);

    ss.clear();
    std::cout << "Chiamo clear()" << std::endl;
    std::cout << "Dimensione set: " << ss.size() << std::endl;
    assert(ss.empty() == true);
}
/**
 * @brief Funzione di test contruttore a partire da iteratore
 */
void test_iter()
{
    std::cout << "******** Test costruttore da iteratore ********" << std::endl;

    int a[] = {1, 2, 3, 4, 5};
    Set<int, equal_int, std::allocator<int>> s(a, a + 5);

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << s << std::endl;
    assert(s.size() == 5);

    Set<int, equal_int, std::allocator<int>> s2(s.begin(), s.end());

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << s2 << std::endl;
    assert(s2.size() == 5);

    std::vector<double> v;
    v.push_back(1.1);
    v.push_back(2.2);
    v.push_back(3.3);
    v.push_back(4.4);
    v.push_back(5.5);

    Set<double, equal_int, std::allocator<double>> s3(v.begin(), v.end());

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << s3 << std::endl;
    assert(s3.size() == 5);
}
/**
 * @brief Funzione di test su oggetti custom (point)
 */
void test_lista_di_point(void)
{
    Set<point, equal_point, std::allocator<point>> sp;

    std::cout << "******** Test sull set di point ********" << std::endl;

    std::cout << "Insertimento dei valori (1,1), (1,2), (2,7), (0,0), (5,4)" << std::endl;
    sp.add(point(1, 1));
    sp.add(point(1, 2));
    sp.add(point(2, 7));
    sp.add(point(0, 0));
    sp.add(point(5, 4));

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << sp << std::endl;

    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 5);

    Set<point, equal_point, std::allocator<point>>::const_iterator i, ie;
    std::cout << "Stampa con iteratori" << std::endl;

    for (i = sp.begin(), ie = sp.end(); i != ie; ++i)
        std::cout << *i << std::endl;

    std::cout << "Set Contiene (1,1): " << sp.contains(point(1, 1)) << std::endl;
    assert(sp.contains(point(1, 1)) == true);

    std::cout << "Set Contiene (1,3): " << sp.contains(point(1, 3)) << std::endl;
    assert(sp.contains(point(1, 3)) == false);

    std::cout << "Set Contiene (0,0): " << sp.contains(point(0, 0)) << std::endl;
    assert(sp.contains(point(0, 0)) == true);

    std::cout << "Set Contiene (5,4): " << sp.contains(point(5, 4)) << std::endl;
    assert(sp.contains(point(5, 4)) == true);

    std::cout << "Set Contiene (5,5): " << sp.contains(point(5, 5)) << std::endl;

    std::cout << "Rimozione di (1,1)" << std::endl;
    sp.remove(point(1, 1));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 4);

    std::cout << "Rimozione di (1,3)" << std::endl;
    sp.remove(point(1, 3));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 4);

    std::cout << "Rimozione di (0,0)" << std::endl;
    sp.remove(point(0, 0));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 3);

    std::cout << "Rimozione di (5,4)" << std::endl;
    sp.remove(point(5, 4));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 2);

    std::cout << "Rimozione di (2,7)" << std::endl;
    sp.remove(point(2, 7));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 1);

    std::cout << "Rimozione di (1,2)" << std::endl;
    sp.remove(point(1, 2));
    std::cout << "Dimensione della lista: " << sp.size() << std::endl;
    assert(sp.size() == 0);

    std::cout << "Is empty? :  " << sp.empty() << std::endl;
    std::cout << sp.empty() << std::endl;
    assert(sp.empty() == true);
}
/**
 * @brief Funzione di test per le funzioni globali
 */
void test_global_method(void)
{
    std::cout << "******** Test della funzione globale filter_out ********" << std::endl;

    setint s; // ctor default

    s.add(1);
    s.add(2);
    s.add(3);

    std::cout << "Stampa di s dopo inserimenti:" << std::endl;
    std::cout << s << std::endl;

    setint s2 = filter_out(s, pred());
    std::cout << "Stampa di s dopo filter_out:" << std::endl;
    std::cout << s << std::endl;
    std::cout << "Stampa di s2 dopo filter_out:" << std::endl;
    std::cout << s2 << std::endl;
    assert(s2.size() == 1);

    std::cout << "******** Test della funzione globale operator+ ********" << std::endl;

    setint s3 = s + s2;
    std::cout << "Stampa di s3 = s + s2 dopo operator+:" << std::endl;
    std::cout << s3 << std::endl;

    setint s4;
    s4.add(10);
    s4.add(20);
    s4.add(30);
    std::cout << "Stampa di s4 dopo filter_out:" << std::endl;
    std::cout << s4 << std::endl;

    s4 = s3 + s4;

    std::cout << "Stampa di s4 = s3 + s4 dopo operator+:" << std::endl;
    std::cout << s4 << std::endl;

    std::cout << "******** Test della funzione globale operator- ********" << std::endl;

    setint s5 = s4 - s3;
    std::cout << "Stampa di s5 = s4 - s3 dopo operator-:" << std::endl;
    std::cout << s5 << std::endl;

    setint s6;
    s6.add(10);
    s6.add(20);
    s6.add(30);

    setint s7 = s6 - s4;
    std::cout << "Stampa di s7 = s6 - s4 dopo operator-:" << std::endl;
    std::cout << s7 << std::endl;

    std::cout << "******** Test della funzione globale save ********" << std::endl;

    // save(s7, "test.txt"); Compiele error acceta solo Set<stringhe>

    Set<std::string, equal_string, std::allocator<std::string>> ss;

    std::cout << "Insertimento dei valori 'A', 'B', 'C', 'D'" << std::endl;
    ss.add("A");
    ss.add("B");
    ss.add("C");
    ss.add("D");

    std::cout << "Stampa con operator<<" << std::endl;
    std::cout << ss << std::endl;

    save(ss, "t.txt");

    // check file
    std::ifstream file("t.txt");
    std::string str;
    std::getline(file, str);
    std::cout << "Stampa del file test.txt:" << std::endl;
    std::cout << str << std::endl;
    assert(str == "4 (A) (B) (C) (D)");
}

/**
 * @brief Funzione di test su oggetto dipinto set usando new
 */
void test_con_new()
{
    DipintoSet *prova = new DipintoSet();

    prova->add(dipinto("C"));
    prova->add(dipinto("B"));
    SogTit sog("A");
    std::cout << "Chiamo filter out";
    assert(prova->size() == 2);
    DipintoSet d = filter_out(*prova, sog);
    assert(d.size() == 0);
    std::cout << "Inizializzo copio e distruggo oggetto";
    DipintoSet *a = new DipintoSet(d);
    delete a;
    delete prova;
}
/**
 * @brief Funzione main
 */
int main()
{
    test_metodi_fondamentali();
    test_metodi_set();
    test_quadre_op();
    test_confornto();
    test_iterator();
    test_lista_di_stringhe();
    test_lista_di_point();
    test_global_method();
    test_iter();
    test_con_new();
}

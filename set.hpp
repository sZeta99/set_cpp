/**
  @file set.hpp

  @brief File header della classe set templata

  File di dichiarazioni/definizioni della classe set templata
*/
#ifndef SET_H
#define SET_H

#include <algorithm> // std::swap
#include <cstddef>   // std::ptrdiff_t
#include <fstream>   // std::ofstream
#include <iterator>  // std::forward_iterator_tag
#include <ostream>   // std::ostream

/**
 * @brief classe set
 *
 * @tparam T tipo di dato
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator tipo di allocazione
 */
template <typename T, typename Equal, typename Allocator> class Set {
public:
  typedef unsigned int size_type; ///< Tipo di dato per la dimensione dell'array
  typedef T value_type;

private:
  value_type *_elements; ///< Array of elements
  size_type _size;       ///< Number of elements
  Equal _eq;             ///< funtore
  Allocator _allocator;  ///< allocazione

public:
  // Costruttore di default
  Set() : _elements(nullptr), _size(0) {}
  // Distruttore
  ~Set() { clear(); }
  // Costruttore Copia
  Set(const Set &other) : _elements(nullptr), _size(0) {
    if (other._size > 0) {
      _elements = _allocator.allocate(other._size);
      _size = other._size;

      for (size_type i = 0; i < _size; i++) {
        _allocator.construct(_elements + i, other._elements[i]);
      }
    }
  }

  /**
   * @brief Costruttore che crea un set riempito con dati presi
   * da una sequenza identificata da un iteratore di inizio e
   * uno di fine.
   *
   *
   * @tparam Iter tipo di iteratore
   * @param begin iteratore di inizio sequenza
   * @param end iteratore di fine sequenza
   * @throw std::bad_alloc possibile eccezione di allocazione
   */

  template <typename Iter>
  Set(Iter begin, Iter end) : _elements(nullptr), _size(0) {
    Iter curr = begin;
    try {
      for (; curr != end; ++curr) {
        add(static_cast<T>(*curr));
      }
    } catch (...) {
      clear();
      throw;
    }
  }
  /**
   * @brief Aggiungere un elemento alla lista
   *
   *
   * @param value valore da inserire nella lista
   * @return true se l'elemento è stato inserito, false altrimenti
   * @throw std::bad_alloc possibile eccezione di allocazione
   *
   */
  bool add(const value_type &value) {
    if (contains(value)) {
      return false;
    }

    value_type *tmp = _allocator.allocate(_size + 1);

    for (size_type i = 0; i < _size; i++) {
      _allocator.construct(tmp + i, _elements[i]);
    }

    _allocator.construct(tmp + _size, value);

    for (size_type i = 0; i < _size; i++) {
      _allocator.destroy(_elements + i);
    }
    _allocator.deallocate(_elements, _size);

    _elements = tmp;
    _size++;

    return true;
  }

  /**
   * @brief  Rimuovere un elemento dal set
   *
   * @param value valore da rimuovere dal set
   * @return true se l'elemento è stato rimosso, false altrimenti
   * @throw std::bad_alloc possibile eccezione di allocazione
   */

  bool remove(const value_type &value) {
    if (!contains(value)) {
      return false;
    }

    if (_size == 1) {
      clear();
      return true;
    }
    value_type *tmp = _allocator.allocate(_size - 1);

    size_type j = 0;
    for (size_type i = 0; i < _size; i++) {
      if (!_eq(_elements[i], value)) {
        _allocator.construct(tmp + j, _elements[i]);
        j++;
      }
    }

    for (size_type i = 0; i < _size; i++) {
      _allocator.destroy(_elements + i);
    }

    _allocator.deallocate(_elements, _size);

    _elements = tmp;
    _size--;

    return true;
  }

  /**
   * @brief Controlla se un elemento è presente nel set
   *
   * @param value valore da cercare nel set
   * @return true se l'elemento è presente nel set, false altrimenti
   */
  bool contains(const value_type &value) const {
    for (size_type i = 0; i < _size; i++) {
      if (_eq(_elements[i], value)) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Scambia il contenuto di due set
   *
   * @param other set con cui scambiare il contenuto
   */
  void swap(Set &other) {
    std::swap(_elements, other._elements);
    std::swap(_size, other._size);
    std::swap(_eq, other._eq);
  }

  /**
   * @brief operatore di assegnamento
   *
   * @param other set da copiare
   * @return reference a this
   */
  Set &operator=(const Set &other) {
    if (&other != this) {
      Set tmp(other);
      this->swap(tmp);
    }

    return *this;
  }

  /**
      @brief operatore di uguaglianza
      @param other set da confrontare
      @return true se i due set sono uguali, tutti gli elementi coincidono,
     false altrimenti
  */
  bool operator==(const Set &other) const {
    if (_size != other._size) {
      return false;
    }

    for (size_type i = 0; i < _size; i++) {
      if (!contains(other._elements[i]))
        return false;
    }

    return true;
  }
  /**
    @brief Accesso in sola lettura ad un elemento tramite operatore []
    @param i indice dell'elemento da leggere
    @return reference all'elemento di indice i
    @throw std::out_of_range se i >= _size
  */
  const value_type &operator[](size_type i) const {

    if (i < _size) {
      return _elements[i];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  /**
   * @brief Dimensione del set
   *
   *
   * @return Il numero di elementi nel set
   *
   */
  size_type size(void) const { return _size; }

  /**
   * @brief Controlla se il set è vuoto
   *
   * @return true se il set è vuoto, false altrimenti
   */
  bool empty(void) const { return (_size == 0); }

  /**
   * @brief Svuota il set
   *
   */
  void clear(void) {
    if (_size > 0) {
      for (size_type i = 0; i < _size; i++) {
        _allocator.destroy(_elements + i);
      }

      _allocator.deallocate(_elements, _size);
    }

    _elements = nullptr;
    _size = 0;
  }
  /**
   * @brief Iteratore costante
   *
   */
  class const_iterator {
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;

    // Costruttore di default
    const_iterator() : ptr(nullptr) {}

    // Costruttore Copia
    const_iterator(const const_iterator &other) : ptr(other.ptr) {}

    // Distruttore
    ~const_iterator() {}

    // Operatore di assegnamento
    const_iterator &operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    // Operatore di iterazione post-incremento
    const_iterator &operator++() {
      ++ptr;
      return *this;
    }

    // Operatore di iterazione pre-incremento
    const_iterator operator++(int) {
      const_iterator temp(*this);
      ++ptr;
      return temp;
    }

    // Operatore di dereferenziazione
    reference operator*() const { return *ptr; }

    // Operatore di accesso a membro
    pointer operator->() const { return ptr; }

    // Operatore di uguaglianza
    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }

    // Operatore di disuguaglianza
    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }

  private:
    const T *ptr;

    friend class Set;

    // Costruttore privato di inizializzazione usato dalla classe container
    const_iterator(const T *p) : ptr(p) {}
  };

  /**
   * @brief Iteratore costante di inizio sequenza
   *
   * @return const_iterator di inizio sequenza
   */
  const_iterator begin() const { return const_iterator(_elements); }

  /**
   * @brief Iteratore costante di fine sequenza
   *
   * @return const_iterator di fine sequenza
   */
  const_iterator end() const { return const_iterator(_elements + _size); }
};

/**
 * @brief Operatore di stream
 *
 * @tparam T tipo di dato
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator tipo di allocazione
 * @param os stream di output
 * @param s set da stampare
 * @return reference allo stream di output
 */
template <typename T, typename Equal, typename Allocator>
std::ostream &operator<<(std::ostream &os, const Set<T, Equal, Allocator> &s) {

  os << s.size();
  for (typename Set<T, Equal, Allocator>::const_iterator i = s.begin();
       i != s.end(); ++i) {
    os << " (" << *i << ")";
  }

  return os;
}

/**
 * @brief Operatore di stream
 *
 * @tparam T tipo di dato
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator tipo di allocazione
 * @tparam P tipo di predicato
 * @param s set da filtrare
 * @param predicate predicato
 *
 * @return nuovo set filtrato
 */
template <typename T, typename Equal, typename Allocator, typename P>
Set<T, Equal, Allocator> filter_out(const Set<T, Equal, Allocator> &s,
                                    P predicate) {
  typename Set<T, Equal, Allocator>::const_iterator i, ie;
  Set<T, Equal, Allocator> result;

  for (i = s.begin(), ie = s.end(); i != ie; ++i) {
    if (predicate(*i)) {
      result.add(*i);
    }
  }

  return result;
}

/**
 * @brief Operatore +
 *
 * @tparam T tipo di dato
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator tipo di allocazione
 * @param s1 set da sommare
 * @param s2 set da sommare
 * @return nuovo set unione
 */
template <typename T, typename Equal, typename Allocator>
Set<T, Equal, Allocator> operator+(const Set<T, Equal, Allocator> &s1,
                                   const Set<T, Equal, Allocator> &s2) {

  typename Set<T, Equal, Allocator>::const_iterator i, ie;
  Set<T, Equal, Allocator> result;

  for (i = s1.begin(), ie = s1.end(); i != ie; ++i) {
    result.add(*i);
  }

  for (i = s2.begin(), ie = s2.end(); i != ie; ++i) {
    result.add(*i);
  }

  return result;
}

/**
 * @brief Operatore -
 *
 * @tparam T tipo di dato
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator tipo di allocazione
 * @param s1 set da intersecare
 * @param s2 set da intersecare
 * @return nuovo set intersezione
 */
template <typename T, typename Equal, typename Allocator>
Set<T, Equal, Allocator> operator-(const Set<T, Equal, Allocator> &s1,
                                   const Set<T, Equal, Allocator> &s2) {

  typename Set<T, Equal, Allocator>::const_iterator i, ie;
  Set<T, Equal, Allocator> result;

  for (i = s1.begin(), ie = s1.end(); i != ie; ++i) {
    if (s2.contains(*i)) {
      result.add(*i);
    }
  }

  return result;
}

/**
 * @brief  salva il contenuto di un set su file
 * @details Salva escusivamente il contenuto di Set<std::string> su file
 * @tparam Equal funtore di uguaglianza
 * @tparam Allocator
 * @param s set da salvare
 * @param filename nome del file su cui salvare il set
 */
template <typename Equal, typename Allocator>
void save(const Set<std::string, Equal, Allocator> &s,
          const std::string &filename) {
  std::ostream *os = nullptr;
  std::ofstream ofs;

  ofs.open(filename.c_str());
  if (ofs.fail()) {
    throw std::runtime_error("Cannot open file");
  }

  os = &ofs;

  *os << s;

  ofs.close();

  if (ofs.fail()) {
    throw std::runtime_error("Cannot close file");
  }

  os = nullptr;

  return;
}
#endif // SET_H

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <limits>
#include <algorithm>
#include <functional>
#include <thread>

template <typename KeyType, typename ValueType>
class Map;



template <typename KeyType, typename ValueType>
struct Node {
    KeyType key;
    ValueType value;

    // Node(KeyType key, ValueType value):key(key), value(value) {}
    // Node(KeyType &key, ValueType &value):key(key), value(value) {}
};



template <typename KeyType, typename ValueType, bool is_const>
class MapIterator{
public:
    /*!
    * @brief Type that shows the distance between two iterators
    *        equals to std::distance(it1, it2)
    */
    typedef ptrdiff_t difference_type;
    /*!
    * @brief The type addressed by the iterator
    */
    typedef Node<KeyType, ValueType> value_type;
    /*!
    * @brief The type of a pointer on a stored value
    *        for const_iterator - const value_type*, for an ordinary - value_type*
    */
    typedef std::conditional_t<is_const, const value_type, value_type> *pointer;
    /*!
    * @brief The type of a pointer on a stored value,
    *        for const_iterator - const value_type&, for an ordinary - value_type&
    */
    typedef std::conditional_t<is_const, const value_type, value_type> &reference;
    /*!
    * @brief Iterator category
    */
    typedef std::bidirectional_iterator_tag iterator_category;

    /*!
    * @brief Empty constructor, dereferencing of the created iterator will result in Undefined Behaviour
    * @note Realizes default_initializable from regular
    */
    MapIterator() noexcept;

    /*!
    * @brief Copy Constructor
    * @tparam other_const Shows the const quality of copy iterator
    * @note Allows copying an iterator of different const type
    * @note Realizes std::move_constructible and std::copy_constructible
    */
    template<bool other_const>
    explicit MapIterator(const MapIterator<KeyType, ValueType, other_const>& o) noexcept
    requires (is_const >= other_const);

    /*!
    * @brief Copying movement
    * @returns Reference to the passed iterator
    * @tparam other_const The constancy of the iterator being copied
    * @note Allows copying an iterator of a different constancy
    * @note Realizes std::assignable_from<value_type&, value_type>, std::copyable and std::swappable
    */
    template<bool other_const>
    MapIterator& operator = (const MapIterator<KeyType, ValueType, other_const>& o) noexcept
    requires (is_const >= other_const);

    /*!
    * @brief Dereference
    * @returns A reference to the addressable element of the array
    * @note Realizes `{ *i } -> / *can-reference* /` from input_or_output_iterator and indirectly_readable
    */
    reference operator*() const noexcept;
    /*!
    * @brief Accessing element fields
    * @returns A pointer to the addressable element of the array
    */
    pointer operator -> () const noexcept;

    /*!
    * @brief Iterators Comparison
    * @tparam other_const The constancy of the iterator being copied
    * @returns true if iterators refer to the same element,
    *          otherwise false
    * @note Realizes equality_comparable из regular
    * @note Operator != we get it automatically
    */
    template<bool other_const>
    bool operator == (const MapIterator<KeyType, ValueType, other_const>& o) const noexcept;

    /*!
    * @brief Moves the iterator to the next element of the array
    * @returns Reference to the passed iterator
    * @note Realizes `{ ++i } -> std::same_as<I&>` from weakly_incrementable
    */
    MapIterator& operator ++ () noexcept;
    /*!
    * @brief Moves the iterator to the next element of the array
    * @returns The state of the iterator before modification
    * @note Realizes `{ i++ } -> std::same_as<I>` from incrementable
    */
    MapIterator operator++(int) noexcept;
    /*!
    * @brief Moves the iterator to the previous element of the array
    * @returns Reference to the passed iterator
    * @note Realizes `{ --i } -> std::same_as<I&>` from bidirectional_iterator
    */
    MapIterator& operator -- () noexcept;
    /*!
    * @brief Moves the iterator to the previous element of the array
    * @returns The state of the iterator before modification
    * @note Realizes `{ i-- } -> std::same_as<I>` from bidirectional_iterator
    */
    MapIterator operator--(int) noexcept;

private:
    // Type of pointer on a node
    typedef std::conditional_t<is_const, const value_type, value_type>* node_t;

    node_t first; // First element of an array
    int map_size; // Size of an array
    int pos; // Position of an element that iterator points on

    // Constructor in a private field, for usage in Map
    MapIterator(node_t first, int map_size, int pos);

    // MapIterator(node_t first, int map_size, int pos);

    // Map can apply to private field
    friend Map<KeyType, ValueType>;

    // An iterator of opposite constancy can address to private fields
    friend MapIterator<KeyType, ValueType, !is_const>;
};



template <typename KeyType, typename ValueType>
class Map {
public:
    /*!
    * @brief Type of stored values
    */
    typedef Node<KeyType, ValueType> node_t;
    /*!
    * @brief Reference to the type of stored values
    */
    typedef node_t &reference;
    /*!
    * @brief Constant reference to the type of stored values
    */
    typedef const node_t &const_reference;
    /*!
    * @brief Type of an iterator
    */
    typedef MapIterator<KeyType, ValueType, false> iterator;
    /*!
    * @brief Type of constant iterator
    */
    typedef MapIterator<KeyType, ValueType, true> const_iterator;
    /*!
    * @brief Type, indicating the distance between two iterators,
    *        equals to std::distance(it1, it2)
    */
    typedef ptrdiff_t difference_type;
    /*!
    * @brief The type used to represent the size of the container
    */
    typedef int size_type;

    /*!
    * @brief Empty constructor, creates empty map
    */
    Map();
    /*!
    * @brief Copy constructor
    * @param map Copied map
    */
    Map(const Map& map);
    /*!
    * @brief Move constructor
    * @param map A movable map
    */
    Map(Map&& map) noexcept;
    /*!
    * @brief Destructor
    */
    ~Map();

    /*!
    * @brief The copying assignment operator
    * @param o The map being copied
    */
    Map& operator = (const Map& o) // Работает только если есть T() и T(a)
    requires std::copy_constructible<node_t>;

    /*!
    * @brief Comparing two arrays
    * @returns true if equal, otherwise false
    * @note It also generates !=
    */
    bool operator== (const Map& o) const;

    /*!
    * @brief Returns the size of the container
    * @returns Container size
    */
    [[nodiscard]] int size() const noexcept;
    /*!
    * @brief Returns the maximum possible container size
    * @returns The maximum possible container size
    */
    [[nodiscard]] int max_size() const noexcept;
    /*!
    * @brief Checking the array for emptiness
    * @returns true if the list is empty, otherwise false
    */
    [[nodiscard]] bool empty() const noexcept;

    /*!
    * @brief Exchanges the states of two arrays with each other
    * @param o An array for exchanging
    */
    void swap(Map& o) noexcept;

    /*!
    * @brief Getting an iterator to the top of the array
    * @returns The iterator addressing the beginning of the array
    */
    iterator begin() noexcept;
    /*!
    * @brief Getting an iterator to the end of the array
    * @returns The iterator addressing the end of the array
    */
    iterator end() noexcept;
    /*!
    * @brief Getting a constant iterator to the top of the array
    * @returns The iterator addressing the beginning of the array
    */
    const_iterator begin() const noexcept;
    /*!
    * @brief Getting a constant iterator to the end of the array
    * @returns The iterator addressing the end of the array
    */
    const_iterator end() const noexcept;
    /*!
    * @brief Getting a constant iterator to the top of the array
    * @returns The iterator addressing the beginning of the array
    */
    const_iterator cbegin() const noexcept;
    /*!
    * @brief Getting a constant iterator to the end of the list
    * @returns The iterator addressing the end of the list
    */
    const_iterator cend() const noexcept;

    /*!
    * @brief Searching for an item by key
    * @param key The key by which the search will be performed
    * @returns Iterator on the found element
    */
    iterator find(KeyType key) noexcept;

    /*!
    * @brief Searching for an item by key
    * @param key The key by which the search will be performed
    * @returns Iterator on the found element
    */
    const_iterator find(KeyType key) const noexcept;

    /*!
    * @brief Inserting an item in the map
    * @param new_node The node that will be inserted
    */
    void insert(node_t* new_node);
    /*!
    * @brief Inserting an item in the map
    * @param new_node The node that will be inserted
    */
    void insert(node_t& new_node);
    /*!
    * @brief Removing an item from the array
    * @param key The key that points on the deleting node
    */
    void erase_node(KeyType key) noexcept;
    /*!
     * @brief Multi Thread function that finds first element that satisfies the callback function
     * @param callback function
     * @param n the number of threads
     */
    void find(std::function<bool(KeyType, ValueType )> &callback, unsigned int th_n = std::thread::hardware_concurrency());

private:
    node_t* arr;
    int map_size = 0;

    void resize(int new_size);
    int binary_search(KeyType key) noexcept;
};



static_assert(std::bidirectional_iterator<MapIterator<int, int, false>>);
static_assert(std::bidirectional_iterator<MapIterator<int, int, true>>);



// =MapIterator=Private=================================================================================================
template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>::MapIterator(node_t first, int map_size, int pos):
        first(first), map_size(map_size), pos(pos) {}



// =MapIterator=Public==================================================================================================
template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>::MapIterator() noexcept: first(nullptr), map_size(0), pos(0){}



template<typename KeyType, typename ValueType, bool is_const>
template<bool other_const>
MapIterator<KeyType, ValueType, is_const>::MapIterator(
        const MapIterator<KeyType, ValueType, other_const>& o) noexcept
requires (is_const >= other_const) : first(o.first), map_size(o.map_size), pos(o.pos) {}



template<typename KeyType, typename ValueType, bool is_const>
template<bool other_const>
MapIterator<KeyType, ValueType, is_const>& MapIterator<KeyType, ValueType, is_const>::
operator = (const MapIterator<KeyType, ValueType, other_const>& o) noexcept
requires (is_const >= other_const) {
    first = o.first;
    map_size = o.map_size;
    pos = o.pos;
    return *this;
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType> &Map<KeyType, ValueType>::operator=(const Map &o) requires std::copy_constructible<node_t> {
    if (*this == o) return *this;

    delete[] arr;
    arr = nullptr;

    for (int i = 0; i < o.map_size; i++){
        insert(o.arr[i]);
    }

    return *this;
}



template<typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::operator==(const Map &o) const {
    if (map_size != o.map_size) return false;

    for (int i = 0; i < map_size; i++){
        if ((arr[i].key != o.arr[i].key) || (arr[i].value != o.arr[i].value))
            return false;
    }

    return true;
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>& MapIterator<KeyType, ValueType, is_const>::
operator ++ () noexcept {
    if (pos == map_size - 1)
        return MapIterator();
    pos++;
    return *this;
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const> MapIterator<KeyType, ValueType, is_const>::
operator ++ (int) noexcept {
    MapIterator res(first, map_size, pos);

    if (pos > map_size - 1){
        *this = MapIterator();
        return res;
    }

    pos++;
    return res;
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>& MapIterator<KeyType, ValueType, is_const>::
operator -- () noexcept {
    if (pos == 0)
        return MapIterator<KeyType, ValueType, is_const>(nullptr, 0, 0);
    pos--;
    return *this;
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const> MapIterator<KeyType, ValueType, is_const>::
operator -- (int) noexcept {
    MapIterator res(first, map_size, pos);
    pos--;
    return res;
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>::reference MapIterator<KeyType, ValueType, is_const>::
operator * () const noexcept {
    return *(first + pos);
}



template<typename KeyType, typename ValueType, bool is_const>
MapIterator<KeyType, ValueType, is_const>::pointer MapIterator<KeyType, ValueType, is_const>::
operator -> () const noexcept {
    return (first + pos);
}



template<typename KeyType, typename ValueType, bool is_const>
template<bool other_const>
bool MapIterator<KeyType, ValueType, is_const>::
operator == (const MapIterator<KeyType, ValueType, other_const> &o) const noexcept {
    return ((first == o.first) && (map_size == o.map_size) && (pos == o.pos));
}



// =Map=Private=========================================================================================================
template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>:: resize(int new_size) {
    int old_size = map_size;
    try {
        map_size = new_size;
        node_t* tmp = arr;
        arr = new node_t[new_size];
        std::copy(tmp, tmp + std::min(new_size, old_size), arr);
        delete[] tmp;
    }
    catch(...) {
        map_size = old_size;
        throw;
    }
}



template<typename KeyType, typename ValueType>
int Map<KeyType, ValueType>::binary_search(KeyType key) noexcept{
    int l = 0, r = map_size - 1, m;

    if (map_size == 0) return -1;

    while(l <= r){
        m = (l + r) / 2;
        if (key < arr[m].key){
            if(m == 0){
                return -1;
            }
            else{
                if (arr[m - 1].key <= key){
                    return m - 1;
                }
            }
            r = m - 1;
        }
        if (key > arr[m].key){
            if(m == map_size - 1){
                return map_size - 1;
            }
            else{
                if (arr[m + 1].key > key){
                    return m;
                }
            }
            l = m + 1;
        }
        if (key == arr[m].key){
            return m;
        }
    }

    return -1;
}



// =Map=Public==========================================================================================================
template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map():map_size(0), arr(nullptr) {}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(const Map& map) {
    map_size = map.map_size;
    arr = new node_t[map_size];

    for (int i = 0; i < map_size; i++){
        arr[i] = node_t{map.arr[i].key, map.arr[i].value};
    }
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(Map&& map) noexcept : map_size(map.map_size), arr(map.arr) {
    map.map_size = 0;
    map.arr = nullptr;
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map() {
    delete[] arr;
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::size_type Map<KeyType, ValueType>::size() const noexcept {
    return map_size;
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::size_type Map<KeyType, ValueType>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
}



template<typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::empty() const noexcept {
    return map_size == 0;
}



template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::swap(Map &o) noexcept {
    std::swap(arr, o.arr);
    std::swap(map_size, o.map_size);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::iterator Map<KeyType, ValueType>::begin() noexcept {
    return iterator(arr, map_size, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::iterator Map<KeyType, ValueType>::end() noexcept {
    return iterator(nullptr, 0, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::const_iterator Map<KeyType, ValueType>::begin() const noexcept {
    return const_iterator(arr, map_size, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::const_iterator Map<KeyType, ValueType>::end() const noexcept {
    return const_iterator(nullptr, 0, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::const_iterator Map<KeyType, ValueType>::cbegin() const noexcept {
    return const_iterator(arr, map_size, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::const_iterator Map<KeyType, ValueType>::cend() const noexcept {
    return const_iterator(nullptr, 0, 0);
}




template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::iterator Map<KeyType, ValueType>::find(KeyType key) noexcept {
    int l = 0, r = map_size - 1, m;

    while(l <= r){
        m = (l + r) / 2;
        if (key < arr[m].key){
            r = m - 1;
        }
        if (key > arr[m].key){
            l = m + 1;
        }
        if (key == arr[m].key){
            return iterator(arr, map_size, m);
        }
    }

    return iterator(nullptr, 0, 0);
}



template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::const_iterator Map<KeyType, ValueType>::find(KeyType key) const noexcept {
    int l = 0, r = map_size - 1, m;

    while(l <= r){
        m = (l + r) / 2;
        if (key < arr[m].key){
            r = m - 1;
        }
        if (key > arr[m].key){
            l = m + 1;
        }
        if (key == arr[m].key){
            return const_iterator(arr, map_size, m);
        }
    }

    return const_iterator(nullptr, 0, 0);
}



template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(Map::node_t *new_node){
    try {
        int pos = binary_search(new_node->key);
        resize(map_size + 1);
        for (int i = map_size - 1; i != pos + 1; i--)
            arr[i] = arr[i - 1];
        arr[pos + 1] = (*new_node);
    }
    catch (...) {
        throw;
    }
}



template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(Map::node_t &new_node){
    try {
        int pos = binary_search(new_node.key);
        resize(map_size + 1);
        for (int i = map_size - 1; i > pos + 1; i--)
            arr[i] = arr[i - 1];

        arr[pos + 1] = new_node;


    }
    catch (...) {
        throw;
    }
}



template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::erase_node(KeyType key) noexcept {
    if (find(key) == iterator(nullptr, 0, 0)) {
        return;
    }

    int pos = binary_search(key);

    for (int i = pos; i < map_size - 1; i++){
        arr[i] = arr[i + 1];
    }

    resize(map_size - 1);
}



template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::find(std::function<bool(KeyType, ValueType)> &callback, unsigned int th_n) {
    std::vector<std::thread> threads(th_n);

    std::mutex m1;
    for (size_t i = 0; i < th_n; ++i){
        size_t pos_start = i * map_size / th_n;
        size_t pos_end = (i + 1) * map_size / th_n;

        threads[i] = std::thread([pos_start, pos_end, &m1, this](){});

        }
}


#endif

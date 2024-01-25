#ifndef MAP_H
#define MAP_H

#include <iostream>

template <typename KeyType, typename ValueType>
class Map;

template <typename KeyType, typename ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node* left;
    Node* right;
};


template <typename KeyType, typename ValueType, bool is_const>
class MapIterator{
public:
    typedef ptrdiff_t difference_type;
    typedef Node<KeyType, ValueType> value_type;
    typedef std::conditional_t<is_const, const value_type, value_type> *pointer;
    typedef std::conditional_t<is_const, const value_type, value_type> &reference;
    typedef std::forward_iterator_tag iterator_category;

    template<bool other_const>
    // Можно переместить оператор иной константности
    MapIterator(MapIterator<KeyType, ValueType, other_const>& o) noexcept
    // Но нельзя из неконстантного в константный
    requires (is_const >= other_const);

    template<bool other_const>
    MapIterator& operator = (const MapIterator<KeyType, ValueType, other_const>& o) noexcept
    requires (is_const >= other_const);

    reference operator*() const noexcept;

    template<bool other_const>
    bool operator == (const MapIterator<KeyType, ValueType, other_const>& o) const noexcept;

    MapIterator& operator ++ () noexcept;

    MapIterator operator++(int) noexcept;

    MapIterator& operator -- () noexcept;

    MapIterator operator--(int) noexcept;
private:
    // Тип указателя на пару ключ: значение
    typedef std::conditional_t<is_const, const value_type, value_type> *pair_ptr_t;

    // Пара, на которую указывает итератор
    pair_ptr_t pair;

    // Конструктор в private области, для использования в Map
    MapIterator(pair_ptr_t pair);

    // Map может обращаться к private полям
    friend Map<KeyType, ValueType>;

    // Итератор противоположной константности может обращаться к private полям
    friend MapIterator<KeyType, ValueType, !is_const>;
};



template <typename KeyType, typename ValueType>
class Map {
    Node<KeyType, ValueType>* head;

    typedef Node<KeyType, ValueType> pair_type;
    typedef pair_type &reference;
    typedef const pair_type &const_reference;
    typedef MapIterator<KeyType, ValueType, false> iterator;
    typedef MapIterator<KeyType, ValueType, true> const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;
    void swap(Map& o) noexcept;
public:
    Map() : head(nullptr) {}

    ~Map() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(const KeyType& key, const ValueType& value) {
        Node* newNode = new Node(key, value);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }//
            curr->next = newNode;
        }
    }

    bool find(const KeyType& key, ValueType& value) const {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->key == key) {
                value = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void remove(const KeyType& key) {
        if (head == nullptr) {
            return;
        }

        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            if (curr->next->key == key) {
                Node* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                return;
            }
            curr = curr->next;
        }
    }
};

int main() {
    Map<std::string, int> myMap;

    myMap.insert("apple", 5);
    myMap.insert("banana", 10);
    myMap.insert("orange", 7);

    int value;
    if (myMap.find("banana", value)) {
        std::cout << "Value of banana: " << value << std::endl;
    } else {
        std::cout << "banana not found" << std::endl;
    }

    myMap.remove("banana");

    if (myMap.find("banana", value)) {
        std::cout << "Value of banana: " << value << std::endl;
    } else {
        std::cout << "banana not found" << std::endl;
    }

    return 0;
}


#endif
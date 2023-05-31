#include <iostream>
#include <numeric>
#include <vector>
#include "LList.h"

using std::cout;

template<typename T>
LList<T>::LList() {
    _size = 0;
    auto new_el_1 = new Node<T>();
    head = new_el_1;

    auto new_el_2 = new Node<T>();
    z = new_el_2;
    z->_next = z;
    head->_next = z;
}

template<typename T>
LList<T>::LList(std::initializer_list<T> values) : LList() {
    for (auto const &val: values) {
        push_back(val);
    }
}

template<typename T>
size_t LList<T>::size() {
    return _size;
}

template<typename T>
bool LList<T>::empty() {
    return _size == 0;
}

template<typename T>
void LList<T>::push_back(T _val) {
    auto *new_element = new Node(_val);

    Node<T> *current = head;
    while (current->_next != z) {
        current = current->_next;
    }
    current->_next = new_element;
    new_element->_next = z;
    _size++;
}

template<typename T>
void LList<T>::push_front(T _val) {
    auto *new_element = new Node(_val);

    new_element->_next = head->_next;
    head->_next = new_element;

    _size++;
}

template<typename T>
void LList<T>::insert(size_t index, T _val) {
    Node<T> *curr;
    int count;
    if (_size < index)
        throw std::out_of_range("oooooy, this is outside");
    if (index == 0) {
        push_front(_val);
        return;
    }
    if (index == _size) {
        push_back(_val);
        return;
    }

    Node<T> *previous_element = head;
    curr = head->_next;
    count = 0;
    while (count != index) {
        count++;
        previous_element = curr;
        curr = curr->_next;
    }

    Node<T> *new_element = new Node(_val);
    new_element->_next = curr;
    previous_element->_next = new_element;

    _size++;
}

template<typename T>
void LList<T>::remove_at(size_t index) {
    if (index < 0 || index >= _size)
        throw std::out_of_range("oooooy, this is outside");
    else {
        if (index == _size - 1) {
            pop_back();
            return;
        } else if (index == 0) {
            pop_front();
            return;
        }

        Node<T> *curr = head->_next, *previous = head;
        int curr_i = 0;
        while (index != curr_i) {
            previous = curr;
            curr = curr->_next;
            curr_i++;
        }
        previous->_next = curr->_next;
        delete curr;
        _size--;
    }
}

template<typename T>
void LList<T>::pop_back() {
    if (_size == 0)
        return;

    Node<T> *current = head->_next, *previous;
    while (current->_next != z) {
        previous = current;
        current = current->_next;
    }
    previous->_next = current->_next;
    delete current;
    _size--;
}

template<typename T>
void LList<T>::pop_front() {
    if (_size == 0)
        return;

    Node<T> *temp = head->_next;
    head->_next = temp->_next;
    delete temp;
    _size--;
}

//DEBUG CLEAR
template<typename T>
void LList<T>::clear() {
    auto curr = head->_next, previous = head;
    while (curr != z) {
        previous = curr;
        curr = curr->_next;
        delete previous;
    }
    head->_next = z;
    _size = 0;
}

template<typename T>
LList<T>::~LList() {
    clear();
    delete head;
    delete z;
}

template<typename T>
T LList<T>::front() {
    if (_size != 0)
        return head->_next;
    throw std::out_of_range("oooooy, this is outside");
}

template<typename T>
T LList<T>::back() {
    if (_size != 0) {
        Node<T> *current = head->_next;
        while (current->_next != z) {
            current = current->_next;
        }
        return current;
    }
    throw std::out_of_range("oooooy, this is outside");
}

template<typename T>
T &LList<T>::operator[](const size_t index) {
    if (_size <= index || index < 0)
        throw std::out_of_range("oooooy, this is outside");
    Node<T> *curr;
    size_t curr_i = 0;
    curr = head->_next;

    while (curr != z) {
        if (curr_i == index)
            return curr->_val;
        curr = curr->_next;
        curr_i++;
    }
    return head->_val;
}

template<typename T>
ListIterator<T> LList<T>::begin() {
    return ListIterator<T>(head->_next);
}

template<typename T>
ListIterator<T> LList<T>::end() {
    return ListIterator<T>(z);
}

template<typename T>
void LList<T>::print() {
    if (!empty()) {
        Node<T> *current = head->_next;
        while (current->_next != z) {
            cout << current->_val << " -> ";
            current = current->_next;
        }
        cout << current->_val << '\n';
    }
}

int main() {
    LList<char> lst;
    std::cout << std::boolalpha << lst.empty() << std::endl;
    for (int i = 0; i < 5; i++)
        lst.push_back(char('a' + i));

    lst.print();

    for (int i = 0; i < 5; i++)
        lst.insert(0, char('z' - i));

    lst.print();

    for (size_t i = 0; i != lst.size(); i++)
        lst[i] = char('a' + i);

    lst.print();

    lst.pop_back();
    lst.pop_front();

    lst.print();

    lst.remove_at(5);
    lst.insert(3, 'o');

    lst.print();

    lst.clear();
    lst.push_back('q');
    lst.push_back('w');
    std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;

    LList<int> l = {3, 5, 2, 7};
    for (auto &i: l) i += 2;
    auto lambda = [& l](int a, int b) { return a + b * 10; };
    std::cout << std::accumulate(l.begin(), l.end(), 0, lambda) << "\n";// 250

    return 0;
}

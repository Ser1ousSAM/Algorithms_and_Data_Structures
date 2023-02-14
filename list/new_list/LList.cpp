#include <iostream>
#include "LList.h"

using std::cout;

template<typename T>
LList<T>::LList() {
    _size = 0;
    z->_val = NULL;
    z->_next = z;
    head->_val = NULL;
    head->_next = z;
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
    Node<T> *new_element = new Node<T>(_val);
    new_element->_next = z;

    Node<T> *current = head;
    while (current->_next != z) {
        current = current->_next;
    }
    current->_next = new_element;

    _size++;
}

template<typename T>
void LList<T>::push_front(T _val) {
    Node<T> *new_element = new Node<T>(_val);

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

    Node<T> *previous_element = nullptr;
    curr = head;
    count = 0;
    while (count != index) {
        count++;
        previous_element = curr;
        curr = curr->_next;
    }

    Node<T> *new_element = new Node<T>(_val);
    new_element->_next = curr;
    previous_element->_next = new_element;

    _size++;
}

template<typename T>
void LList<T>::remove_at(size_t index) {
    if (index < 0 || index >= _size)
        throw std::out_of_range("oooooy, this is outside");
    else {
        if (index == _size - 1)
            pop_back();
        else if (index == 0)
            pop_front();

        Node<T> *curr = head->_next, *previous = nullptr;
        int curr_i = 0;
        while (index != curr_i) {
            previous = curr;
            curr = curr->_next;
            curr_i++;
        }
        previous->_next = curr->_next;
        delete curr;
    }
}

template<typename T>
void LList<T>::pop_back() {
    if (_size == 0)
        return;

    Node<T> *current = head->_next, *previous = head;
    while (current->_next != z) {
        previous = current;
        current = current->_next;
    }
    previous = current->_next;
    delete current;
}

template<typename T>
void LList<T>::pop_front() {
    if (_size == 0)
        return;

    Node<T> *temp = head->_next;
    head->_next = temp->_next;
    delete temp;
}

template<typename T>
void LList<T>::clear() {
    Node<T> *curr = head->_next, *previous;
    while (curr != z) {
        previous = curr;
        curr = curr->_next;
        delete previous;
    }
    delete previous;
    head->_next = z;
    _size = 0;
}

template<typename T>
T LList<T>::front() {
    if (_size != 0)
        return head->_next;
    throw std::out_of_range("oooooy, this is outside");
}

template<typename T>
T LList<T>::back() {
    if (_size != 0){
        Node<T> *current = head->_next;
        while (current->_next != z){
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
}

//void print_lst(const LList<char> &l) {
//    for (auto i = 0; i < l.size(); i++) {
//        cout << l[i] << " ";
//    }
//    cout << '\n';
//}

// template<typename T>
// void LList<T>::print() {
//     if (!empty()) {
//         Node<T> *current = head.next;
//         while (current != z) {
//             cout << current->_val << " ";
//             current = current->_next;
//         }
//         cout << '\n';
//     }
// }

int main() {
    LList<char> lst; // ваш список
    std::cout << std::boolalpha << lst.empty() << std::endl;
    for (int i = 0; i < 5; i++)
        lst.push_back(char('a' + i));

//    print_lst(lst);

    for (int i = 0; i < 5; i++)
        lst.insert(0, char('z' - i));

//    print_lst(lst);

    for (size_t i = 0; i != lst.size(); i++)
        lst[i] = char('a' + i);

//    print_lst(lst);

    lst.pop_back();
    lst.pop_front();
//    print_lst(lst);

    lst.remove_at(5);
    lst.insert(3, 'o');

//    print_lst(lst);

    lst.clear();
    lst.push_back('q');
    lst.push_back('w');
//а почему запись по индексу и чтение это отдельные методы?
    std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;
    return 0;
} // деструктор освободит оставшиеся узлы
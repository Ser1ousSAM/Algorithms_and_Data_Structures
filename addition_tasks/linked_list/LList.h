//difference between class and typename - first for all, second for internal types(int, char...)
template<typename T>
class ListIterator;

template<typename T>
struct Node {
    T _val;
    Node *_next;
    Node() : _val(T()), _next(nullptr) {}
    Node(T val) : _val(val), _next(nullptr) {}

};

template<typename T>
class LList {
public:
    LList();

    LList(std::initializer_list<T> values);

    ~LList();

    void push_back(T);

    void push_front(T);

    void insert(size_t, T);

    void pop_back();

    void pop_front();

    void remove_at(size_t);

    T &operator[](size_t index);

    ListIterator<T> begin();

    ListIterator<T> end();

    size_t size();

    bool empty();

    void clear();

    void print();

    T front();

    T back();


private:
    Node<T> *head;
    Node<T> *z;

    int _size;
};


template<typename T>
class ListIterator {
public:
    ListIterator(Node<T> *node = nullptr) : _ptr(node) {};

    ListIterator operator++() {
        _ptr = _ptr->_next;
        return *this;
    }

    T &operator*() {
        return _ptr->_val;
    }

    bool operator!=(ListIterator const &rhs) const {
        return _ptr != rhs._ptr;
    }

private:
    Node<T> *_ptr;
};
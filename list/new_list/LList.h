//difference between class and typename - first for all, second for internal types(int, char...)
template<typename T>
class Node;

template<typename T>
class LList {
public:
    LList();

    ~LList() = default;

    void push_back(T);

    void push_front(T);

    void insert(size_t, T);

    void pop_back();

    void pop_front();

    void remove_at(size_t);

    T &operator[](size_t index);

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
class Node {
    T _val;
    Node *_next;

    Node(T val = T()) : _val(val), _next(nullptr) {};

    friend class LList<T>;
};
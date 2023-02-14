//difference between class and typename - first for all, second for internal types(int, char...)
template<typename T>
class Node;

template<typename T>
class List {
public:
    List();

    ~List() = default;

    int getSize();

    bool isEmpty();

    void pushBack(T);

    void pushFront(T);

    void insert(T, int);

    int indexOf(T);

    T &valueAt(int);

    void print();

    bool remove(T);

    bool removeAt(int);

    bool removeFront();

    bool removeLast();

    void clear();

    void sort();

    int binarySearch(T);

    T &operator[](const int index);

private:
    Node<T> *first;
    Node<T> *last;
    int _size;
};

template<typename T>
class Node {
    T _val;
    Node *_next;
    Node *_prev;

    Node(T _val = T()) : _val(_val), _next(nullptr), _prev(nullptr) {};

    friend class List<T>;
};
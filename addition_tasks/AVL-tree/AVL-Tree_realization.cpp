#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::max;

template<typename T>
class Node;

template<typename T>
class AVL_Tree {
public:
    Node<T> *root = nullptr;
    int treeSize;

    AVL_Tree();

    ~AVL_Tree() = default;

    void add(T x) {
        root = add_p(root, x);
        treeSize++;
    }

    void remove(T x) {
        root = remove_p(root, x);
        treeSize--;
    }

    bool find(T x) {
        Node<T> *temp = find_p(root, x);
        if (temp != nullptr) {
            if (temp->val_p == x)
                return true;
        }
        return false;
    }

    void clear() {
        clear_p(root);
        treeSize = 0;
    }

    void prefix() {
        prefix_p(root);
        cout << '\n';
    }

    void infix() {
        infix_p(root);
        cout << '\n';
    }

    void postfix() {
        postfix_p(root);
        cout << '\n';
    }

private:
    int height(Node<T> *);

    Node<T> *rightRotation_p(Node<T> *);

    Node<T> *leftRotation_p(Node<T> *);

    Node<T> *balance_p(Node<T> *vertex, T x);

    Node<T> *add_p(Node<T> *, T);

    Node<T> *remove_p(Node<T> *, T);

    void clear_p(Node<T> *&);

    Node<T> *find_p(Node<T> *, T);

    void prefix_p(Node<T> *);

    void infix_p(Node<T> *);

    void postfix_p(Node<T> *);
};

template<typename T>
class Node {
    T val_p;
    Node *left_p;
    Node *right_p;
    int height_p;

    explicit Node(T _val = T()) : val_p(_val), left_p(nullptr), right_p(nullptr), height_p(1) {};

    friend class AVL_Tree<T>;
};

template<typename T>
AVL_Tree<T>::AVL_Tree() {
    root = new Node<T>();
    treeSize = 0;
}

template<typename T>
int AVL_Tree<T>::height(Node<T> *vertex) {
    if (vertex == nullptr) return 0;
    return vertex->height_p;
}

template<typename T>
Node<T> *AVL_Tree<T>::rightRotation_p(Node<T> *vertex) {
    Node<T> *newVertex = vertex->left_p;
    vertex->left_p = newVertex->right_p;
    newVertex->right_p = vertex;
    vertex->height_p = 1 + max(height(vertex->left_p), height(vertex->right_p));
    newVertex->height_p = 1 + max(height(newVertex->left_p), height(newVertex->right_p));
    return newVertex;
}

template<typename T>
Node<T> *AVL_Tree<T>::leftRotation_p(Node<T> *vertex) {
    Node<T> *newVertex = vertex->right_p;
    vertex->right_p = newVertex->left_p;
    newVertex->left_p = vertex;
    vertex->height_p = 1 + max(height(vertex->left_p), height(vertex->right_p));
    newVertex->height_p = 1 + max(height(newVertex->left_p), height(newVertex->right_p));
    return newVertex;
}

template<typename T>
Node<T> *AVL_Tree<T>::balance_p(Node<T> *vertex, T x) {
    int bal = height(vertex->left_p) - height(vertex->right_p);
    if (bal > 1) {
        if (x < vertex->left_p->val_p) {
            return rightRotation_p(vertex);
        } else {
            vertex->left_p = leftRotation_p(vertex->left_p);
            return rightRotation_p(vertex);
        }
    } else if (bal < -1) {
        if (x > vertex->right_p->val_p) {
            return leftRotation_p(vertex);
        } else {
            vertex->right_p = rightRotation_p(vertex->right_p);
            return leftRotation_p(vertex);
        }
    } else{
        return vertex;
    }
}

template<typename T>
Node<T> *AVL_Tree<T>::add_p(Node<T> *vertex, T x) {
    if (vertex == nullptr || root->val_p == 0) {
        auto *temp = new Node<T>(x);
        return temp;
    }
    if (x < vertex->val_p) vertex->left_p = add_p(vertex->left_p, x);
    else if (x > vertex->val_p) vertex->right_p = add_p(vertex->right_p, x);
    vertex->height_p = 1 + max(height(vertex->left_p), height(vertex->right_p));
    return balance_p(vertex, x);
}

template<typename T>
Node<T> *AVL_Tree<T>::remove_p(Node<T> *vertex, T x) {
    if (vertex == nullptr) return nullptr;
    if (x < vertex->val_p) {
        vertex->left_p = remove_p(vertex->left_p, x);
    } else if (x > vertex->val_p) {
        vertex->right_p = remove_p(vertex->right_p, x);
    } else {
        Node<T> *r = vertex->right_p;
        if (vertex->right_p == nullptr) {
            Node<T> *l = vertex->left_p;
            delete (vertex);
            vertex = l;
        } else if (vertex->left_p == nullptr) {
            delete (vertex);
            vertex = r;
        } else {
            while (r->left_p != nullptr) r = r->left_p;
            vertex->val_p = r->val_p;
            vertex->right_p = remove_p(vertex->right_p, r->val_p);
        }
    }
    if (vertex == nullptr) return vertex;
    vertex->height_p = 1 + max(height(vertex->left_p), height(vertex->right_p));
    return balance_p(vertex, x);
}

template<typename T>
Node<T> *AVL_Tree<T>::find_p(Node<T> *vertex, T x) {
    if (vertex == nullptr) return nullptr;
    T k = vertex->val_p;
    if (k == x) return vertex;
    if (k > x) return find_p(vertex->left_p, x);
    if (k < x) return find_p(vertex->right_p, x);
    return nullptr;
}

template<typename T>
void AVL_Tree<T>::clear_p(Node<T> *&vertex) {
    if (vertex != nullptr) {
        clear_p(vertex->left_p);
        clear_p(vertex->right_p);
        delete vertex;
    }
    vertex = nullptr;
}

template<typename T>
void AVL_Tree<T>::prefix_p(Node<T> *vertex) {
    if (vertex == nullptr)
        return;

    /* first print data of node */
    cout << vertex->val_p << " ";

    /* then recur on left subtree */
    prefix_p(vertex->left_p);

    /* now recur on right subtree */
    prefix_p(vertex->right_p);
}

template<typename T>
void AVL_Tree<T>::infix_p(Node<T> *vertex) {
    if (vertex == nullptr)
        return;

    /* first recur on left child */
    infix_p(vertex->left_p);

    /* then print the data of node */
    cout << vertex->val_p << " ";

    /* now recur on right child */
    infix_p(vertex->right_p);
}

template<typename T>
void AVL_Tree<T>::postfix_p(Node<T> *vertex) {
    if (vertex == nullptr)
        return;
    // first recur on left subtree
    postfix_p(vertex->left_p);
    // then recur on right subtree
    postfix_p(vertex->right_p);
    // now deal with the node
    cout << vertex->val_p << " ";
}

int main() {
    AVL_Tree<int> t;
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(4);
    t.add(5);
    t.add(6);
    t.add(7);
    std::cout << t.find(7) << '\n';

    t.prefix();
    t.infix();
    t.postfix();

    t.remove(5);
    t.remove(6);
    t.remove(7);
    t.infix();
    t.clear();
    t.infix();

    return 0;
}
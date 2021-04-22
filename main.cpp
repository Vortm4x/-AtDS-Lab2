#include <iostream>

// ---------------------------
//  struct Node<T>
//  Consists data and ptr on
//  the left and right nodes
// ---------------------------
template<typename T>
struct Node
{
	Node<T>* left;
	Node<T>* right;
	T data;

	Node(const T& data = T(), Node<T> *const left = nullptr, Node<T> *const right = nullptr);
};

// --------------------------
//  class BBST<T>
//  <DESCRIPTION NOT READY>
// --------------------------
template<typename T>
class BBST
{
private:
    Node<T>* root;
    void destroy(Node<T>* node);
    void print_ascending(Node<T>* node);
    void print_descending(Node<T>* node);
    void add(const T& data, Node<T>* node);
    Node<T>* remove(const T& data, Node<T>* node);
    bool search(const T& data, Node<T>* node);
    Node<T>* findMin(Node<T>* node);
    Node<T>* findMax(Node<T>* node);

public:
    BBST();
    ~BBST();
    void clear();
    void remove(const T& data)
    {
        root = remove(data, root);

        //balance
    }

    void add(const T& data)
    {
        if(isEmpty())
        {
            root = new Node<T>(data);
        }
        else
        {
            add(data, root);
        }

        //balance
    }

    bool isEmpty()
    {
        return root == nullptr;
    }

    bool search(const T& data)
    {
        return search(data, root);
    }

    void print_sorted()
    {
        print_ascending(root);
        std::cout << std::endl;

        print_descending(root);
        std::cout << std::endl;
    }
};

// -------------------------------------------------------------------------
//  Node<T>::Node(const T& data, Node<T> *const left, Node<T> *const right)
//  Node constructor  with default params
// -------------------------------------------------------------------------
template<typename T>
Node<T>::Node(const T& data, Node<T> *const left, Node<T> *const right)
{
    this->data = data;
    this->left = left;
    this->right = right;
}

// ------------------
//  BBST<T>::BBST()
//  BBST constructor
// ------------------
template<typename T>
BBST<T>::BBST()
{
    root = nullptr;
}

// ------------------
//  BBST<T>::~BBST()
//  BBST constructor
// ------------------
template<typename T>
BBST<T>::~BBST()
{
    destroy(root);
}

// ----------------------------------------
//  void BBST<T>::destroy(Node<T>* node)
//  Deletes a subtree including given node
// ----------------------------------------
template<typename T>
void BBST<T>::destroy(Node<T>* node)
{
    if(node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template<typename T>
void BBST<T>::clear()
{
    destroy(root);
    root = nullptr;
}

template<typename T>
void BBST<T>::add(const T& data, Node<T>* node)
{
    if(data < node->data)
    {
        if(node->left == nullptr)
        {
            node->left = new Node<T>(data);
        }
        else
        {
            add(data, node->left);
        }
    }
    else if(data > node->data)
    {
        if(node->right == nullptr)
        {
            node->right = new Node<T>(data);
        }
        else
        {
            add(data, node->right);
        }
    }
}

template<typename T>
Node<T>* BBST<T>::remove(const T& data, Node<T>* node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else if(data < node->data)
    {
        node->left = remove(data, node->left);
    }
    else if(data > node->data)
    {
        node->right = remove(data, node->right);
    }
    else
    {
        if( (node->left == nullptr) && (node->right == nullptr) )
        {
            delete node;
            node = nullptr;
        }
        else if(node->left == nullptr)
        {
            Node<T>* temp = node;
            node = node->right;
            delete temp;
        }
        else if(node->right == nullptr)
        {
            Node<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            node = remove(temp->data, node->right);
        }
    }

    return node;
}

template<typename T>
Node<T>* BBST<T>::findMin(Node<T>* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

template<typename T>
Node<T>* BBST<T>::findMax(Node<T>* node)
{
    Node<T> current = node;

    while(node->right != nullptr)
    {
        node = node->right;
    }

    return node;
}

template<typename T>
void BBST<T>::print_ascending(Node<T>* node)
{
    if(node != nullptr)
    {
        print_ascending(node->left);
        std::cout << node->data << ", ";
        print_ascending(node->right);
    }
}

template<typename T>
void BBST<T>::print_descending(Node<T>* node)
{
    if(node != nullptr)
    {
        print_descending(node->right);
        std::cout << node->data << ", ";
        print_descending(node->left);
    }
}

template<typename T>
bool BBST<T>::search(const T& data, Node<T>* node)
{
    if(node == nullptr)
    {
        return false;
    }
    else if(node->data == data)
    {
        return true;
    }
    else
    {
        return search(data, (node->data > data) ? node->left : node->right);
    }
}

int main()
{
    BBST<int> tree;

    tree.add(10);

    for(int i = 1; i < 4; ++i)
    {
        tree.add(10 + i);
        tree.add(10 - i);
    }

    tree.add(10);

    tree.print_sorted();

    std::cout << tree.search(16) << ' ' << tree.search(8) << std::endl;

    tree.remove(12);
    tree.remove(8);
    tree.remove(5);

    tree.print_sorted();

    std::cout << "Good" << std::endl;

    return 0;
}

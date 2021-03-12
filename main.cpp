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
    void print_preorder(Node<T>* node);

public:
    BBST();
    ~BBST();
    void clear();
    void add(const T& data);
    void print_preorder()
    {
        print_preorder(root);
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
void BBST<T>::print_preorder(Node<T>* node)
{
    if(node != nullptr)
    {
        std::cout << node->data << ", ";
        print_preorder(node->left);
        print_preorder(node->right);
    }
}

template<typename T>
void BBST<T>::add(const T& data)
{
    Node<T>* current = nullptr;
    Node<T>* following = root;

    while(following != nullptr)
    {
        current = following;
        following = (following->data > data) ? following->left : following->right;
    }

    if(current == nullptr)
    {
        root = new Node<T>(data);
    }
    else
    {
        if(current->left == following)
        {
            current->left = new Node<T>(data);
        }
        else
        {
            current->right = new Node<T>(data);
        }
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

    tree.print_preorder();

    std::cout << "Good" << std::endl;

    return 0;
}

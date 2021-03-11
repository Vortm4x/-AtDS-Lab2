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

public:
    BBST();
    ~BBST();
    void clear();
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

int main()
{
    BBST<int> tree;
    tree.clear();
    std::cout << "Good" << std::endl;

    return 0;
}

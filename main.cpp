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
	int height;

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
    Node<T>* add(const T& data, Node<T>* node);
    Node<T>* remove(const T& data, Node<T>* node);
    bool search(const T& data, Node<T>* node);
    Node<T>* initChain(Node<T>* node);
    bool compare(Node<T>* a, Node<T>* b);
    int countNode(Node<T>* node);
    T sumKeys(Node<T>* node);
    Node<T>* findMin(Node<T>* node);
    Node<T>* findMax(Node<T>* node);
    void insert(Node<T>* node);

    inline int balance(Node<T>* node)
    {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    inline void heightUpdate(Node<T>* node)
    {
        node->height = 1 + (( height(node->left) > height(node->right) ) ? height(node->left) : height(node->right) );
    }

    inline int height(Node<T>* node)
    {
        return (node == nullptr) ? 0 : node->height;
    }

    inline T abs(const T& data)
    {
        return (data < 0) ? -data : data;
    }
    Node<T>* findSecondLargest(Node<T>* node);


public:
    BBST();
    BBST(const BBST& tree);
    ~BBST();
    void clear();
    T findMiddle();
    BBST<T> operator =(const BBST<T>& other)
    {
        this->root = initChain(other.root);
    }

    bool operator ==(const BBST<T>& other)
    {
        return compare(root, other.root);
    }

    bool operator !=(const BBST<T>& other)
    {
        return !(*this == other);
    }

    inline int height()
    {
        return height(root);
    }

    void insert(const BBST<T>& other)
    {
        insert(other.root);
    }

    void remove(const T& data)
    {
        root = remove(data, root);

        //balance
    }

    void add(const T& data)
    {
        root = add(data, root);
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

    int countNode()
    {
        return countNode(root);
    }

    T sumKeys()
    {
        return sumKeys(root);
    }

    T findSecondLargest();
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
    this->height = 1;
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
//  BBST<T>::BBST()
//  BBST constructor
// ------------------
template<typename T>
BBST<T>::BBST(const BBST& tree)
{
    this->root = initChain(tree.root);
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

// -------------------------------------------
//  Node<T>* BBST<T>::initChain(Node<T>* node)
//  Return a copy of a subtree
// -------------------------------------------
template<typename T>
Node<T>* BBST<T>::initChain(Node<T>* node)
{
    if(node != nullptr)
    {
        return new Node<T>(node->data, initChain(node->left), initChain(node->right));
    }
    else
    {
        return nullptr;
    }

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
    if(node == nullptr)
    {
        return new Node<T>(data);
    }
    else if(data < node->data)
    {
        node->left = add(data, node->left);
    }
    else if(data > node->data)
    {
        node->right = add(data, node->right);
    }
    else
    {
        return node;
    }

    heightUpdate(node);

    if ((balance(node) > 1) && (data < node->left->data))
    {
        return rightRotation(node);
    }

    if ((balance(node) < -1) && (data > node->right->data))
    {
        return leftRotation(node);
    }

    if ((balance(node) > 1) && (data > node->left->data))
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if ((balance(node) < -1) && (data < node->right->data))
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
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
            node->right = remove(temp->data, node->right);
        }
    }

    if(node == nullptr)
    {
        return nullptr;
    }


    if((balance(node) > 1) && (balance(node->left) >= 0))
    {
        return rightRotation(node);
    }

    if((balance(node) > 1) && (balance(node->left) < 0))
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if((balance(node) < -1) && (balance(node->right) <= 0))
    {
        return leftRotation(node);
    }

    if((balance(node) < -1) && (balance(node->right) > 0))
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
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
    Node<T>* current = node;

    while(node->right != nullptr)
    {
        node = node->right;
    }

    return node;
}

template<typename T>
T BBST<T>::findSecondLargest()
{
    if(root != nullptr)
    {
        if(root->right != nullptr)
        {
            Node<T>* node = findSecondLargest(root);
            return node->data;
        }
        else
        {
            if(root->left != nullptr)
            {
                return root->left->data;
            }
            else
            {
                return T();
            }
        }
    }
    else
    {
        return T();
    }
}

template<typename T>
int BBST<T>::countNode(Node<T>* node)
{
    if(node != nullptr)
    {
        if(node->left != nullptr)
        {
            return 1 + countNode(node->left) + countNode(node->right);
        }
        else
        {
            return countNode(node->right);
        }
    }
    else
    {
        return 0;
    }
}

template<typename T>
T BBST<T>::sumKeys(Node<T>* node)
{
    if(node != nullptr)
    {
        if(node->right != nullptr)
        {
            return node->right->data + sumKeys(node->left) + sumKeys(node->right);
        }
        else
        {
            return sumKeys(node->left);
        }
    }
    else
    {
        return T();
    }
}

template<typename T>
Node<T>* BBST<T>::findSecondLargest(Node<T>* node)
{
    Node<T>* current = node;

    while(current->right->right != nullptr)
    {
        current = current->right;
    }

    return current;
}

template<typename T>
T BBST<T>::findMiddle()
{
    if(root != nullptr)
    {
        T minDist = (findMax(root))->data;
        T currDist = (findMin(root))->data;
        T middle = (minDist + currDist) / 2;

        Node<T>* current = root;

        while(current != nullptr)
        {
            int currDist = current->data - middle;
            minDist = (abs(currDist) < abs(minDist)) ? currDist : minDist;

            if(minDist == 0)
            {
                break;
            }

            current = (middle < current->data) ? current->left : current->right;
        }

        return middle + minDist;

    }
    else
    {
        return T();
    }
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

template<typename T>
void BBST<T>::insert(Node<T>* node)
{
    if(node != nullptr)
    {
        this->add(node->data);
        insert(node->left);
        insert(node->right);
    }
}

template<typename T>
bool BBST<T>::compare(Node<T>* a, Node<T>* b)
{
    if((a != nullptr) && (b != nullptr))
    {
        if(a->data == b->data)
        {
            return compare(a->left, b->left) && compare(a->right, b->right);
        }
        else
        {
            return false;
        }
    }
    else if((a == nullptr) && (b == nullptr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void testCopy(BBST<int> tree)
{
    tree.print_sorted();
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

    tree.print_sorted();

    tree.remove(10);

    tree.print_sorted();

    std::cout << "Good" << std::endl;

    return 0;
}

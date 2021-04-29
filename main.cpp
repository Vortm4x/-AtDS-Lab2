#include <iostream>
#include <vector>

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

// -----------------------------------
//  class BBST<T>
//  Balanced Binary Search Tree class
// -----------------------------------
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
    void inverse(Node<T>* node);
    bool compare(Node<T>* a, Node<T>* b);
    int countNode(Node<T>* node);
    T sumKeys(Node<T>* node);
    Node<T>* findMin(Node<T>* node);
    Node<T>* findMax(Node<T>* node);
    Node<T>* leftRotation(Node<T>* x);
    Node<T>* rightRotation(Node<T>* y);
    void insert(Node<T>* node);
    Node<T>* deleteEven(Node<T>* node);
    void pathTo(std::vector<Node<T>*>& path, T data);
    bool contains(Node<T>* node);


// -----------------------------------------
//  inline int balance(Node<T>* node)
//  Returns a balance factor of the subtree
// -----------------------------------------
    inline int balance(Node<T>* node)
    {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

// -----------------------------------------
//  inline void heightUpdate(Node<T>* node)
//  Resets height of the subtree
// -----------------------------------------
    inline void heightUpdate(Node<T>* node)
    {
        node->height = 1 + (( height(node->left) > height(node->right) ) ? height(node->left) : height(node->right) );
    }

// -----------------------------------------
//  inline int height(Node<T>* node)
//  Returns a height of the subtree
// -----------------------------------------
    inline int height(Node<T>* node)
    {
        return (node == nullptr) ? 0 : node->height;
    }

// ----------------------------------------------
//  inline T abs(const T& data)
//  Returns an absolute value (for numeric types)
// ----------------------------------------------
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

// ----------------------------------------------
//  BBST<T> operator =(const BBST<T>& other)
//  = operator overload
// ----------------------------------------------
    BBST<T> operator =(const BBST<T>& other)
    {
        this->root = initChain(other.root);
    }

// ----------------------------------------------
//  bool operator ==(const BBST<T>& other)
//  == operator overload
// ----------------------------------------------
    bool operator ==(const BBST<T>& other)
    {
        return compare(root, other.root);
    }

// ----------------------------------------------
//  bool operator !=(const BBST<T>& other)
//  != operator overload
// ----------------------------------------------
    bool operator !=(const BBST<T>& other)
    {
        return !(*this == other);
    }

// ------------------------------------------------------------
//  bool contains(const BBST<T>& other)
//  Checks does this tree contains all nodes of another one
// ------------------------------------------------------------
    bool contains(const BBST<T>& other)
    {
        return contains(other.root);
    }

// -----------------------------------
//  void deleteEven()
//  Removes all even values of a tree
// -----------------------------------
    void deleteEven()
    {
        root = deleteEven(root);
    }

// -------------------
//  void inverse()
//  Inverse the tree
// ------------------
    void inverse()
    {
        inverse(root);
    }

// --------------------------------
//  inline int height()
//  Return a height of the subtree
// --------------------------------
    inline int height()
    {
        return height(root);
    }


// ----------------------------------------
//  inline T fatherNode()
//  Return a value of the father(root) node
// ----------------------------------------
    inline T fatherNode()
    {
        return (root != nullptr) ? root->data : T();
    }

// -------------------------------------------------
//  void insert(const BBST<T>& other)
//  Inserts all nodes of the other tree to this one
// -------------------------------------------------
    void insert(const BBST<T>& other)
    {
        insert(other.root);
    }


// -------------------------------------------------
//  void remove(const T& data)
//  Removes the node with the given value
// -------------------------------------------------
    void remove(const T& data)
    {
        root = remove(data, root);
    }

// -------------------------------------------------
//  void add(const T& data)
//  Adds the node with the given value
// -------------------------------------------------
    void add(const T& data)
    {
        root = add(data, root);
    }

// -------------------------------------------------
//  inline bool isEmpty()
//  Checks is the tree is empty
// -------------------------------------------------
    inline bool isEmpty()
    {
        return root == nullptr;
    }

// -------------------------------------------------
//  bool search(const T& data)
//  Checks if there is a root
//	with the given value in the tree
// -------------------------------------------------
    bool search(const T& data)
    {
        return search(data, root);
    }

// -------------------------------------------------
//  void print_sorted()
//  Prints nodes in ascending and descending order
// -------------------------------------------------
    void print_sorted()
    {
        if(root != nullptr)
        {
            print_ascending(root);
            std::cout << '\n';

            print_descending(root);
            std::cout << '\n';
        }
        else
        {
            std::cout << "<Empty>\n<Empty>\n";
        }

    }

// -------------------------------------------------
//  int countNode()
// 	Counts left son nodes in tree
// -------------------------------------------------
    int countNode()
    {
        return countNode(root);
    }

// -------------------------------------------------
//  T sumKeys()
// 	Returns sum of values in right son nodes in tree
// -------------------------------------------------
    T sumKeys()
    {
        return sumKeys(root);
    }

    T findSecondLargest();
    T commonAncestor(const T& a, const T& b);
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
//  BBST destructor
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

// ---------------------------------------
//  void BBST<T>::inverse(Node<T>* node)
//  Inverse the tree
// ---------------------------------------
template<typename T>
void BBST<T>::inverse(Node<T>* node)
{
    if(node != nullptr)
    {
        inverse(node->left);
        inverse(node->right);

        Node<T>* temp = node->left;
        node->left = node->right;
        node->right = temp;
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

// ----------------------------
//  void BBST<T>::clear()
//  Removes all nodes from tree
// ----------------------------
template<typename T>
void BBST<T>::clear()
{
    destroy(root);
    root = nullptr;
}

// ----------------------------------------------------
//  Node<T>* BBST<T>::add(const T& data, Node<T>* node)
//  Adds the node with the given value
// ----------------------------------------------------
template<typename T>
Node<T>* BBST<T>::add(const T& data, Node<T>* node)
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

// -------------------------------------------------
//  Node<T>* BBST<T>::remove(const T& data, Node<T>* node)
//  Removes the node with the given value
// -------------------------------------------------
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


// -------------------------------------------------
//  Node<T>* BBST<T>::leftRotation(Node<T>* x)
//  Left AVL rotation
// -------------------------------------------------
template<typename T>
Node<T>* BBST<T>::leftRotation(Node<T>* x)
{
    Node<T>* y = x->right;
    Node<T>* z = y->left;

    y->left = x;
    x->right = z;

    heightUpdate(x);
    heightUpdate(y);

    return y;
}

// -------------------------------------------------
//  Node<T>* BBST<T>::rightRotation(Node<T>* x)
//  Right AVL rotation
// -------------------------------------------------
template<typename T>
Node<T>* BBST<T>::rightRotation(Node<T>* y)
{
    Node<T>* x = y->left;
    Node<T>* z = x->right;

    x->right = y;
    y->left = z;

    heightUpdate(y);
    heightUpdate(x);

    return x;
}

// -------------------------------------------------
//  Node<T>* BBST<T>::findMin(Node<T>* node)
//  Returns the node with the minimum value
// -------------------------------------------------
template<typename T>
Node<T>* BBST<T>::findMin(Node<T>* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

// -------------------------------------------------
//  Node<T>* BBST<T>::findMax(Node<T>* node)
//  Returns the node with the maximum value
// -------------------------------------------------
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

// -------------------------------------------------
//  T BBST<T>::findSecondLargest()
//  Returns second largest node
// -------------------------------------------------
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

// -------------------------------------------------
//  int BBST<T>::countNode(Node<T>* node)
// 	Counts left son nodes in tree
// -------------------------------------------------
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


// -------------------------------------------------
//  T BBST<T>::sumKeys(Node<T>* node)
// 	Returns sum of values in right son nodes in tree
// -------------------------------------------------
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

// -------------------------------------------------
//  T BBST<T>::findSecondLargest()
//  Returns second largest node
// -------------------------------------------------
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


// -------------------------------------------------
//  T BBST<T>::findMiddle()
//  Returns middle tree value
// -------------------------------------------------
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

// -----------------------------------
//  void deleteEven()
//  Removes all even values of a tree
// -----------------------------------
template<typename T>
Node<T>* BBST<T>::deleteEven(Node<T>* node)
{
    if(node != nullptr)
    {
        node->left = deleteEven(node->left);
        node->right = deleteEven(node->right);

        while((node != nullptr) && (node->data % 2 == 0))
        {
            node = remove(node->data, node);
        }
    }

    return node;
}

// ---------------------------------------------------------
//  T BBST<T>::commonAncestor(const T& a, const T& b)
//  Finds a common ancestor for nodes with the givven values
// ----------------------------------------------------------
template<typename T>
T BBST<T>::commonAncestor(const T& a, const T& b)
{
    std::vector<Node<T>*> pathA ;
    pathTo(pathA, a);
    std::vector<Node<T>*> pathB;
    pathTo(pathB, b);

    if(pathA.empty() || pathB.empty())
    {
        return T();
    }
    else
    {
        size_t i = 0;

        for(; i < pathA.size() && i < pathB.size(); ++i)
        {
            if(pathA[i] != pathB[i])
            {
                break;
            }
        }

        return (pathA[i - 1])->data;
    }
}

// -----------------------------------------------------------
//  void BBST<T>::pathTo(std::vector<Node<T>*>& path, T data)
//  Finds a path to the node with the given value
// -----------------------------------------------------------
template<typename T>
void BBST<T>::pathTo(std::vector<Node<T>*>& path, T data)
{
    Node<T>* node = root;

    while(node != nullptr)
    {
        path.push_back(node);

        if(data < node->data)
        {
            node = node->left;
        }
        else if(data > node->data)
        {
            node = node->right;
        }
        else
        {
            path.pop_back();
            break;
        }
    }

    if(node == nullptr)
    {
        path.clear();
    }
}


// -----------------------------------------------------------
//  void BBST<T>::print_ascending(Node<T>* node)
//  Prints nos in ascending order
// -----------------------------------------------------------
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

// -----------------------------------------------------------
//  void BBST<T>::print_descending(Node<T>* node)
//  Prints nos in descending order
// -----------------------------------------------------------
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

// ----------------------------------------------------
//  bool BBST<T>::search(const T& data, Node<T>* node)
//  Checks if there is a root
//	with the given value in the tree
// ----------------------------------------------------
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

// -------------------------------------------------
//  void BBST<T>::insert(Node<T>* node)
//  Inserts all nodes of the other tree to this one
// -------------------------------------------------
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

// -----------------------------------------------
//  bool BBST<T>::compare(Node<T>* a, Node<T>* b)
//  Compares two given trees
// -----------------------------------------------
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
// ------------------------------------------------------------
//  bool contains(const BBST<T>& other)
//  Checks does this tree contains all nodes of another one
// ------------------------------------------------------------
template<typename T>
bool BBST<T>::contains(Node<T>* node)
{
    if(node != nullptr)
    {
        return search(node->data) && contains(node->left) && contains(node->right);
    }
    else
    {
        return true;
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

    for(int i = 1; i < 10; ++i)
    {
        tree.add(10 + i);
        tree.add(10 - i);
    }

    BBST<int> copied = tree;

    std::cout << tree.contains(copied) << '\n';
    tree.remove(10);
    std::cout << tree.contains(copied) << '\n';

    return 0;
}

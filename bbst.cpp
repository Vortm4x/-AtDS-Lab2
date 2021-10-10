#include <iostream>
#include <vector>

template<typename T>
AVL::Node<T>::Node(const T& data, AVL::Node<T> *const left, AVL::Node<T> *const right)
{
    this->data = data;
    this->left = left;
    this->right = right;
    this->height = 1;
}

template<typename T>
BBST<T>::BBST()
{
    root = nullptr;
}

template<typename T>
BBST<T>::BBST(const BBST& tree)
{
    this->root = copy(tree.root);
}

template<typename T>
BBST<T>::~BBST()
{
    destroy(root);
}

template<typename T>
AVL::Node<T>* BBST<T>::copy(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        return new AVL::Node<T>(node->data, copy(node->left), copy(node->right));
    }
    else
    {
        return nullptr;
    }
}

template<typename T>
void BBST<T>::inverse(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        inverse(node->left);
        inverse(node->right);

        AVL::Node<T>* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

template<typename T>
void BBST<T>::destroy(AVL::Node<T>* node)
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
AVL::Node<T>* BBST<T>::add(const T& data, AVL::Node<T>* node)
{

    if(node == nullptr)
    {
        return new AVL::Node<T>(data);
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
AVL::Node<T>* BBST<T>::remove(const T& data, AVL::Node<T>* node)
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
            AVL::Node<T>* temp = node;
            node = node->right;
            delete temp;
        }
        else if(node->right == nullptr)
        {
            AVL::Node<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            AVL::Node<T>* temp = findMin(node->right);
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
AVL::Node<T>* BBST<T>::leftRotation(AVL::Node<T>* x)
{
    AVL::Node<T>* y = x->right;
    AVL::Node<T>* z = y->left;

    y->left = x;
    x->right = z;

    heightUpdate(x);
    heightUpdate(y);

    return y;
}

template<typename T>
AVL::Node<T>* BBST<T>::rightRotation(AVL::Node<T>* y)
{
    AVL::Node<T>* x = y->left;
    AVL::Node<T>* z = x->right;

    x->right = y;
    y->left = z;

    heightUpdate(y);
    heightUpdate(x);

    return x;
}

template<typename T>
AVL::Node<T>* BBST<T>::findMin(AVL::Node<T>* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

template<typename T>
AVL::Node<T>* BBST<T>::findMax(AVL::Node<T>* node)
{
    AVL::Node<T>* current = node;

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
            AVL::Node<T>* node = findSecondLargest(root);
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
int BBST<T>::countNode(AVL::Node<T>* node)
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
T BBST<T>::sum(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        return node->data + sum(node->left) + sum(node->right);
    }
    else
    {
        return T();
    }
}

template<typename T>
AVL::Node<T>* BBST<T>::findSecondLargest(AVL::Node<T>* node)
{
    AVL::Node<T>* current = node;

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

        AVL::Node<T>* current = root;

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
AVL::Node<T>* BBST<T>::deleteEven(AVL::Node<T>* node)
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

template<typename T>
T BBST<T>::commonAncestor(const T& a, const T& b)
{
    std::vector<AVL::Node<T>*> pathA ;
    pathTo(pathA, a);
    std::vector<AVL::Node<T>*> pathB;
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

template<typename T>
void BBST<T>::pathTo(std::vector<AVL::Node<T>*>& path, T data)
{
    AVL::Node<T>* node = root;

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

template<typename T>
void BBST<T>::print_ascending(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        print_ascending(node->left);
        std::cout << node->data << ", ";
        print_ascending(node->right);
    }
}

template<typename T>
void BBST<T>::print_descending(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        print_descending(node->right);
        std::cout << node->data << ", ";
        print_descending(node->left);
    }
}

template<typename T>
bool BBST<T>::search(const T& data, AVL::Node<T>* node)
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
void BBST<T>::insert(AVL::Node<T>* node)
{
    if(node != nullptr)
    {
        this->add(node->data);
        insert(node->left);
        insert(node->right);
    }
}

template<typename T>
bool BBST<T>::compare(AVL::Node<T>* a, AVL::Node<T>* b)
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

template<typename T>
bool BBST<T>::contains(AVL::Node<T>* node)
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

template<typename T>
inline int BBST<T>::balance(AVL::Node<T>* node)
{
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

template<typename T>
inline void BBST<T>::heightUpdate(AVL::Node<T>* node)
{
    node->height = 1 + (( height(node->left) > height(node->right) ) ? height(node->left) : height(node->right) );
}

template<typename T>
inline int BBST<T>::height(AVL::Node<T>* node)
{
    return (node == nullptr) ? 0 : node->height;
}

template<typename T>
inline T BBST<T>::abs(const T& data)
{
    return (data < 0) ? -data : data;
}

template<typename T>
BBST<T> BBST<T>::operator =(const BBST<T>& other)
{
    this->root = copy(other.root);
}

template<typename T>
bool BBST<T>::operator ==(const BBST<T>& other)
{
    return compare(root, other.root);
}

template<typename T>
bool BBST<T>::operator !=(const BBST<T>& other)
{
    return !(*this == other);
}

template<typename T>
bool BBST<T>::contains(const BBST<T>& other)
{
    return contains(other.root);
}

template<typename T>
void BBST<T>::deleteEven()
{
    root = deleteEven(root);
}

template<typename T>
void BBST<T>::inverse()
{
    inverse(root);
}

template<typename T>
inline int BBST<T>::height()
{
    return height(root);
}

template<typename T>
inline T BBST<T>::fatherNode()
{
    return (root != nullptr) ? root->data : T();
}

template<typename T>
void BBST<T>::insert(const BBST<T>& other)
{
    insert(other.root);
}

template<typename T>
void BBST<T>::remove(const T& data)
{
    root = remove(data, root);
}

template<typename T>
void BBST<T>::add(const T& data)
{
    root = add(data, root);
}

template<typename T>
inline bool BBST<T>::isEmpty()
{
    return root == nullptr;
}

template<typename T>
bool BBST<T>::search(const T& data)
{
    return search(data, root);
}

template<typename T>
void BBST<T>::print_ascending()
{
    if(root != nullptr)
    {
        print_ascending(root);
    }
    else
    {
        std::cout << "<Empty>";
    }

    std::cout << '\n';
}

template<typename T>
void BBST<T>::print_descending()
{
    if(root != nullptr)
    {
        print_descending(root);
    }
    else
    {
        std::cout << "<Empty>";
    }

    std::cout << '\n';
}

template<typename T>
int BBST<T>::countNode()
{
    return countNode(root);
}

template<typename T>
T BBST<T>::sum()
{
    return sum(root);
}

template<typename T>
AVL::Node<T>* BBST<T>::copy()
{
    return copy(root);
}

template<typename T>
int BBST<T>::size()
{
    return size(root);
}

template<typename T>
int BBST<T>::size(AVL::Node<T>* node)
{
    return (node == nullptr) ? 0 : size(node->left) + size(node->right) + 1;  
}

template<typename T>
bool BBST<T>::same(const BBST<T>& other)
{
    return contains(other.root) && ( size() == size(other.root) );
}
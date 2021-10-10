#pragma once
#include <vector>

namespace AVL
{
    template<typename T>
    struct Node
    {
	    Node<T>* left;
	    Node<T>* right;
	    T data;
	    int height;

	    Node(const T& data = T(), Node<T> *const left = nullptr, Node<T> *const right = nullptr);
    };
}
    
template<typename T>
class BBST
{
private:
    AVL::Node<T>* root;
    void destroy(AVL::Node<T>* node);
    void print_ascending(AVL::Node<T>* node);
    void print_descending(AVL::Node<T>* node);
    AVL::Node<T>* add(const T& data, AVL::Node<T>* node);
    AVL::Node<T>* remove(const T& data, AVL::Node<T>* node);
    bool search(const T& data, AVL::Node<T>* node);
    AVL::Node<T>* copy(AVL::Node<T>* node);
    void inverse(AVL::Node<T>* node);
    bool compare(AVL::Node<T>* other, AVL::Node<T>* b);
    int countNode(AVL::Node<T>* node);
    T sum(AVL::Node<T>* node);
    AVL::Node<T>* findMin(AVL::Node<T>* node);
    AVL::Node<T>* findMax(AVL::Node<T>* node);
    AVL::Node<T>* leftRotation(AVL::Node<T>* x);
    AVL::Node<T>* rightRotation(AVL::Node<T>* y);
    void insert(AVL::Node<T>* node);
    AVL::Node<T>* deleteEven(AVL::Node<T>* node);
    void pathTo(std::vector<AVL::Node<T>*>& path, T data);
    bool contains(AVL::Node<T>* node);
    inline int balance(AVL::Node<T>* node);
    inline void heightUpdate(AVL::Node<T>* node);
    inline int height(AVL::Node<T>* node);
    inline T abs(const T& data);
    AVL::Node<T>* findSecondLargest(AVL::Node<T>* node);
    int size(AVL::Node<T>* node);

public:
    BBST();
    BBST(const BBST& tree);
    ~BBST();
    void clear();
    T findMiddle();
    BBST<T> operator =(const BBST<T>& other);
    bool operator ==(const BBST<T>& other);
    bool operator !=(const BBST<T>& other);
    bool contains(const BBST<T>& other);
    void deleteEven();
    inline int height();
    void inverse();
    inline T fatherNode();
    void insert(const BBST<T>& other);
    void remove(const T& data);
    void add(const T& data);
    inline bool isEmpty();
    bool search(const T& data);
    void print_ascending();
    void print_descending();
    int countNode();
    T sum();
    T findSecondLargest();
    T commonAncestor(const T& a, const T& b);
    AVL::Node<T>* copy();
    int size();
    bool same(const BBST<T>& other);
};

#include "bbst.cpp"
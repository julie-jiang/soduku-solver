/*
 * Easy to add element 
 * Easy to remove element
 * Easy to find element
 */

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef AVLTree_H
#define AVLTree_H

template<typename ElemType>


class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void add(ElemType);
    bool contains(ElemType);
    void remove(ElemType);
    bool empty();
    void print();
    void printTree();

private:
    struct Node {
        int height;
        ElemType value;
        Node *left;
        Node *right;
    }
    *root;

    Node *add(Node *, ElemType);
    Node *makeNewNode(ElemType);
    bool contains(Node *, ElemType);
    Node *remove(Node *, ElemType);
    void print(Node *);
    void printTree(Node *);
    
    int getBalance(Node *);
    int height(Node *);
    int max(int, int);
    Node *getMinNode(Node *);
    Node *rotateRight(Node *);
    Node *rotateLeft(Node *);
    Node *removeNode(Node *);
    Node *replaceParentWithChild(Node *, Node *);
    
    
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/

template<typename ElemType>
AVLTree<ElemType>::AVLTree()
{
    root = nullptr;
}

template<typename ElemType>
AVLTree<ElemType>::~AVLTree()
{

}
template<typename ElemType>
bool AVLTree<ElemType>::contains(ElemType val)
{
    if (not empty())
        return contains(root, val);
    return false;

}
template<typename ElemType>
bool AVLTree<ElemType>::contains(Node *node, ElemType val)
{
    // If node == s, return true
    if (node->value == val) {
        return true;
    } 

    // Search left subtree if node > s
    if (node->value > val and node->left != nullptr) {
        return contains(node->left, val);
    }

    // Search right subtree if node < s
    else if (node->right != nullptr) {
        return contains(node->right, val);
    } 

    // s does not exist in BST. Return false
    else {
        return false;
    }
}

template<typename ElemType>
bool AVLTree<ElemType>::empty()
{
    return (root == nullptr);
}
template<typename ElemType>
void AVLTree<ElemType>::add(ElemType val)
{
    root = add(root, val);
        
}
template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::add(Node *node, ElemType val)
{
    // Make new node 
    if (node == nullptr) {
        node = makeNewNode(val);

    // Insert left if node is greater than s
    } else if (node->value > val) {
        node->left = add(node->left, val);

    // Insert right if node is smaller than s
    } else {
        node->right = add(node->right, val);
    }
    
    // Update height
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
    
    if (balance > 1) {
        // Right right unbalance 
        if (val > node->right->value) {    
            return rotateLeft(node);
        // Right left unbalance
        } else { // val < node->right->value              
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        // Left left unbalance
        if (val < node->left->value) {
            return rotateRight(node);
        // Left right unbalance
        } else { // val > node->left->value
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    return node;
}

template<typename ElemType>
void AVLTree<ElemType>::remove(ElemType val)
{
    root = remove(root, val);
}


template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::remove(Node* node, ElemType val)
{
    if (node != nullptr) {
        // If node == val, remove node
        if (val == node->value) {
            node = removeNode(node);
        }
        // Search left subtree if node > s
        else if (val < node->value) {
            node->left = remove(node->left, val);

        // Search right subtree if node < s
        } else {
            node->right = remove(node->right, val);
        }
        if (node == nullptr) 
            return node;
        // Update height
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);
        
        if (balance > 1) {
            // Right right unbalance 
            if (getBalance(root->right) >= 0) {     
                return rotateLeft(node);
            // Right left unbalance
            } else { // getBalance(root->right) < 0              
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        } else if (balance < -1) {
            // Left left unbalance
            if (getBalance(root->left) <= 0) {
                return rotateRight(node);
            // Right left unbalance
            } else { // getBalance(rood->left) > 0
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
    }
    return node;

}
template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::removeNode(Node *node)
{
        // If node has two children, find its in-order successor and replace node 
    // with it. Then delete an instance of its in-order successor through 
    // recursion
    if (node->left != nullptr and node->right != nullptr) {
        Node *successor = getMinNode(node->right);
        node->value  = successor->value;
        node->height = successor->height;
        node->right  = removeNode(successor);
    
    // If node has only left child, replace node with its left child
    } else if (node->left != nullptr) {
        node = replaceParentWithChild(node, node->left);

    // If node has only right child, replace node with its right child
    } else if (node->right != nullptr) {
        node = replaceParentWithChild(node, node->right);
    
    // If node has no children, delete it
    } else {
        Node *temp = node;
        delete temp;
        node = nullptr;
    }
    return node;
}
template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::getMinNode(Node *node)
{
    // Keep traversing left until end of AVL tree is reached
    if (node->left != nullptr) {
        return getMinNode(node->left);
    }
    return node;
}

template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::replaceParentWithChild
                                  (Node *parent,  Node *child)
{
    parent->height = child->height;
    parent->value  = child->value;
    parent->left   = child->left;
    parent->right  = child->right;
    delete child;
    return parent;
}


template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::rotateLeft(Node *node)
{
    Node *rightChild     = node->right;
    Node *rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right      = rightLeftChild;

    node->height       = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    
    return rightChild;
}
template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::rotateRight(Node *node)
{
    Node *leftChild     = node->left;
    Node *leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left       = leftRightChild;

    node->height      = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;

}

template<typename ElemType>
int AVLTree<ElemType>::getBalance(Node *node)
{
    return (height(node->right) - height(node->left));
}

template<typename ElemType>
int AVLTree<ElemType>::height(Node *node)
{
    if (node != nullptr)
        return node->height;
    return 0;
}

template<typename ElemType>
int AVLTree<ElemType>::max(int a, int b)
{
    return (a > b) ? a : b;
}

template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::makeNewNode(ElemType val)
{
    Node *newNode    = new Node;
    newNode->height  = 1;
    newNode->value   = val;
    newNode->left    = nullptr;
    newNode->right   = nullptr;
    return newNode;
}
template<typename ElemType>
void AVLTree<ElemType>::print()
{
    std::cout << "[";
    if (not empty()) {
        print(root);
    }
    std::cout << "]";
}
template<typename ElemType>
void AVLTree<ElemType>::print()
{
    if (node->left != nullptr) 
        print(node->left);
    
    std::cout << node->value << " ";

    if (node->right != nullptr) 
        print(node->right);

}

template<typename ElemType>
void AVLTree<ElemType>::printTree()
{
    std::cout << "[";
    if (not empty()) {
        printTree(root);
    }
    std::cout << "]" << std::endl;
}
template<typename ElemType>
void AVLTree<ElemType>::printTree(Node *node)
{
    // Traverse left subtree 
    std::cout << "[";
    if (node->left != nullptr) {    
        printTree(node->left);  
    } 
    // Print current node
    std::cout << "] " << node->value << " [";
    
    // Traverse right subtree
    if (node->right != nullptr) {
        printTree(node->right);
    }
    std::cout << "]";
    
}
#endif
#ifndef BST_H
#define BST_H

/** @brief Bst class is a basic Binary Search Tree.
 *
 * @author Hazoorpreet Singh
 * @date   16 July 2026
 */
template <typename T>
class Bst
{
private:
    struct Node
    {
        Node * left{nullptr};
        Node * right{nullptr};
        T key{};
    };
public:

    /** @brief Create a Binary Search Tree
     *
     */
    Bst();

    /** @brief Copy a Binary Search Tree into a new one
     *
     * @param[in] other - Other Binary Search Tree to copy
     */
    Bst(const Bst<T> & other);

    /** @brief Copy a Binary Search Tree into an existing one
     *
     * @param[in] other - Other Binary Search Tree to copy
     */
    Bst & operator=(const Bst<T> & other);

    /** @brief Destroy Binary Search Tree
     *
     */
    virtual ~Bst();

    /** @brief Insert a new key into the Binary Search Tree
     *
     * @param[in] key - New key to be inserted
     *
     * @retval 1 - Key successfully inserted
     * @retval 0 - Key could not be inserted due to already existing
     * @retval -1 - Key could not be inserted due to inability to reserve memory
     */
    int Insert(T key);

    /** @brief Insert a new key into the Binary Search Tree
     *
     * @param[in] key - Key to search for
     *
     * @retval True - Key found in tree
     * @retval False - Key not found in tree
     */
    bool Search(const T & key) const;

    /** @brief Traverse tree in Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void InOrder(void(*func)(T)) const;
    void InOrder(void(*func)(const T&)) const;

    /** @brief Traverse tree in Order, performing a mutating function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void InOrder(void(*func)(T&));

    /** @brief Traverse tree in Pre Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void PreOrder(void(*func)(T)) const;
    void PreOrder(void(*func)(const T&)) const;

    /** @brief Traverse tree in Pre Order, performing a mutating function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void PreOrder(void(*func)(T&));

    /** @brief Traverse tree in Post Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void PostOrder(void(*func)(T)) const;
    void PostOrder(void(*func)(const T&)) const;

    /** @brief Traverse tree in Post Order, performing a mutating function on each item
     *
     * @param[in] func - Function done on each value.
     */
    void PostOrder(void(*func)(T&));

    /** @brief Clear tree of all items.
     *
     */
    void Clear();

private:
    Node * m_root;

    /** @brief Delete a tree (or subtree)
     *
     * @post Will not set to nullptr to save compute at recursion but memory will be freed.
     * @param[in] node - Root of tree or subtree
     */
    static void DeleteTree(Node * & node);

    /** @brief Recursively insert a new node recursively then proceeds to call rebalance
     *
     * @param[in] new_node - Node to be added
     *
     * @retval True - Node successfully added and rebalanced tree
     * @retval False - Node was discarded as it already exists in the tree
     */
    static bool Insert (Node * new_node, Node * parent);

    /** @brief Recursively searches for a key down the length of a tree
     *
     * @param[in] key - Key to search for
     * @param[in] node - Node/subtree to search for key
     */
    static bool Search(const T & key, const Node * node);

    /** @brief Traverse tree in Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     * @param[in] node - Node/subtree to apply function to
     */
    static void InOrder(void(*func)(T), Node * node);
    static void InOrder(void(*func)(T&), Node * node);
    static void InOrder(void(*func)(const T&), Node * node);

    /** @brief Traverse tree in Pre Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     * @param[in] node - Node/subtree to apply function to
     */
    static void PreOrder(void(*func)(T), Node * node);
    static void PreOrder(void(*func)(T&), Node * node);
    static void PreOrder(void(*func)(const T&), Node * node);

    /** @brief Traverse tree in Post Order, performing a function on each item
     *
     * @param[in] func - Function done on each value.
     * @param[in] node - Node/subtree to apply function to
     */
    static void PostOrder(void(*func)(T), Node * node);
    static void PostOrder(void(*func)(T&), Node * node);
    static void PostOrder(void(*func)(const T&), Node * node);

    /** @brief Deeply copy a tree recursively
     *
     * @param[in] node - Node's subtree to copy
     */
    static void DeepCopy(Node * node);

    /** @brief Gets height of a node
     *
     * @param[in] node - Node to retrieve height of
     * @return Height of node
     */
    static int Height(Node * node);

    /** @brief Gets balance of a node
     *
     * @param[in] node - Node to retrieve balance of
     * @return Balance of node (positive is right heavy, negative is left heavy)
     */
    static int NodeBalance(Node * node);

    /** @brief Rebalances a node
     *
     * @param[in] node - Node to rebalance
     * @param[in] inserted_node - Node being inserted
     */
    static Node * Rebalance(Node * node, const Node * inserted_node);

    /** @brief Left rotate a branch
     *
     * @param[in] branch_root - Branch to be rotated
     * @return New branch root after left rotation
     */
    static Node * LeftRotate(Node * branch_root);

    /** @brief Right rotate a branch
     *
     * @param[in] branch_root - Branch to be rotated
     * @return New branch root after right rotation
     */
    static Node * RightRotate(Node * branch_root);

    /** @brief Max of two values
     *
     * @param[in] a - Value to compare A
     * @param[in] b - Value to compare B
     */
    static int max(int a, int b);
};

template <typename T>
int Bst<T>::max(int a, int b) {
    return (a > b) ? a : b;
}

template <typename T> typename
Bst<T>::Node * Bst<T>::Rebalance(Node * node, const Node * inserted_node)
{
    int node_balance = NodeBalance(node);
    if (node_balance > 1)
    {
        // right heavy
        if (node->right->key < inserted_node->key)
        {
            return LeftRotate(node);
        }
        else
        {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }
    }
    else if (node_balance < -1)
    {
        // left heavy
        if (node->left->key > inserted_node->key)
        {
            return RightRotate(node);
        }
        else
        {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
    }
    return node;
}

template <typename T> typename
Bst<T>::Node * Bst<T>::LeftRotate(Node * branch_root)
{
    // fetch required nodes
    Node * branch_right = branch_root->right;
    Node * mid_node = branch_right->left;

    // rotate nodes
    branch_right->left = branch_root;
    branch_root->right = mid_node;

    return branch_right;
}

template <typename T> typename
Bst<T>::Node * Bst<T>::RightRotate(Node * branch_root)
{
    // fetch required nodes
    Node * branch_left = branch_root->left;
    Node * mid_node = branch_left->right;

    // rotate nodes
    branch_left->right = branch_root;
    branch_root->left = mid_node;

    return branch_left;
}

template <typename T>
int Bst<T>::Height(Node * node)
{
    if (node == nullptr)
    {
        return -1;
    }

    return max(Height(node->right), Height(node->left)) + 1;
}

template <typename T>
int Bst<T>::NodeBalance(Node * node)
{
    return Height(node->right) - Height(node->left);
}

template <typename T>
Bst<T>::Bst(): m_root{nullptr} {}

template <typename T>
Bst<T>::Bst(const Bst<T> & other): m_root{nullptr}
{
    if (other.m_root != nullptr)
    {
        m_root = new Node{*(other.m_root)};
        DeepCopy(m_root);
    }
}

template <typename T>
Bst<T> & Bst<T>::operator=(const Bst<T> & other)
{
    if (this == &other) {
        return *this;
    }
    Clear();
    if (other.m_root != nullptr)
    {
        m_root = new Node{*(other.m_root)};
        DeepCopy(m_root);
    }
    return *this;
}

template <typename T>
Bst<T>::~Bst()
{
    DeleteTree(m_root);
    m_root = nullptr;
}

template <typename T>
int Bst<T>::Insert(T key)
{
    Node * new_node = new Node{};
    if (new_node == nullptr)
    {
        return -1;
    }
    new_node->key = key;
    if (m_root == nullptr)
    {
        m_root = new_node;
        return 1;
    }
    else
    {
        if (Insert(new_node, m_root))
        {
            m_root = Rebalance(m_root, new_node);
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

template <typename T>
bool Bst<T>::Search(const T & key) const
{
    if (m_root == nullptr)
    {
        return false;
    }
    return Search(key, m_root);
}

template <typename T>
void Bst<T>::InOrder(void(*func)(T)) const
{
    InOrder(func, m_root);
}

template <typename T>
void Bst<T>::InOrder(void(*func)(T&))
{
    InOrder(func, m_root);
}

template <typename T>
void Bst<T>::InOrder(void(*func)(const T&)) const
{
    InOrder(func, m_root);
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(T)) const
{
    PreOrder(func, m_root);
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(T&))
{
    PreOrder(func, m_root);
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(const T&)) const
{
    PreOrder(func, m_root);
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(T)) const
{
    PostOrder(func, m_root);
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(T&))
{
    PostOrder(func, m_root);
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(const T&)) const
{
    PostOrder(func, m_root);
}

template <typename T>
void Bst<T>::Clear()
{
    if (m_root != nullptr)
    {
        DeleteTree(m_root);
        m_root = nullptr;
    }
}

template <typename T>
void Bst<T>::DeleteTree(Node * & node)
{
    if (node != nullptr)
    {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

template <typename T>
bool Bst<T>::Insert (Node * new_node, Node * parent)
{
    if (new_node->key < parent->key)
    {
        if (parent->left == nullptr)
        {
            parent->left = new_node;
            return true;
        }
        else
        {
            if (Insert(new_node, parent->left))
            {
                parent->left = Rebalance(parent->left, new_node);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else if (new_node->key == parent->key)
    {
        delete new_node;
        return false;
    }
    else
    {
        if (parent->right == nullptr)
        {
            parent->right = new_node;
            return true;
        }
        else
        {
            if (Insert(new_node, parent->right))
            {
                parent->right = Rebalance(parent->right, new_node);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

template <typename T>
bool Bst<T>::Search(const T & key, const Node * node)
{
    if (node->key == key)
    {
        return true;
    }
    else if (key < node->key)
    {
        if (node->left == nullptr)
        {
            return false;
        }
        else
        {
            return Search(key, node->left);
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            return false;
        }
        else
        {
            return Search(key, node->right);
        }
    }
}

template <typename T>
void Bst<T>::InOrder(void(*func)(T), Node * node)
{
    if (node != nullptr)
    {
        InOrder(func, node->left);
        func(node->key);
        InOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(T), Node * node)
{
    if (node != nullptr)
    {
        func(node->key);
        PreOrder(func, node->left);
        PreOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(T), Node * node)
{
    if (node != nullptr)
    {
        PreOrder(func, node->left);
        PreOrder(func, node->right);
        func(node->key);
    }
}

template <typename T>
void Bst<T>::InOrder(void(*func)(T&), Node * node)
{
    if (node != nullptr)
    {
        InOrder(func, node->left);
        func(node->key);
        InOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(T&), Node * node)
{
    if (node != nullptr)
    {
        func(node->key);
        PreOrder(func, node->left);
        PreOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(T&), Node * node)
{
    if (node != nullptr)
    {
        PreOrder(func, node->left);
        PreOrder(func, node->right);
        func(node->key);
    }
}

template <typename T>
void Bst<T>::InOrder(void(*func)(const T&), Node * node)
{
    if (node != nullptr)
    {
        InOrder(func, node->left);
        func(node->key);
        InOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PreOrder(void(*func)(const T&), Node * node)
{
    if (node != nullptr)
    {
        func(node->key);
        PreOrder(func, node->left);
        PreOrder(func, node->right);
    }
}

template <typename T>
void Bst<T>::PostOrder(void(*func)(const T&), Node * node)
{
    if (node != nullptr)
    {
        PreOrder(func, node->left);
        PreOrder(func, node->right);
        func(node->key);
    }
}

template <typename T>
void Bst<T>::DeepCopy(Node * node)
{
    if (node->left != nullptr)
    {
        node->left = new Node{*(node->left)};
        DeepCopy(node->left);
    }

    if (node->right != nullptr)
    {
        node->right = new Node{*(node->right)};
        DeepCopy(node->right);
    }
}
#endif

/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
   Node *TRight = t->right;
   t->right = TRight->left;
   TRight -> left = t;
   t=TRight;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node *TLeft = t->left;
    Node *TLeftLeft = TLeft->left;
    t->left = TLeft->right;
    TLeft->right = t;
    t = TLeft;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{

    if (subtree == NULL)
        return;

        
    int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);



    if (balance == -2)
   {
       int rightBalance = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
       if (rightBalance == -1)
           rotateLeft(subtree);
       else
           rotateRightLeft(subtree);
   }
   else if(balance == 2){
       int leftBalance = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
       if (leftBalance == 1)
           rotateRight(subtree);
       else
           rotateLeftRight(subtree);
   }

  

   if (subtree->right != NULL)
       subtree->right->height = 1 + std::max(heightOrNeg1(subtree->right->left), heightOrNeg1(subtree->right->right));

   if (subtree->left != NULL)
       subtree->left->height = 1 + std::max(heightOrNeg1(subtree->left->left), heightOrNeg1(subtree->left->right));

   subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL)
        subtree = new Node(key, value);
    else if (key < subtree->key)
        insert(subtree->left, key, value);
    else if (key > subtree->key)
        insert(subtree->right, key, value);

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node *temp = subtree->left;
            while (temp->right != NULL)
            {
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            Node *temp = subtree;
            if (subtree->left != NULL)
                subtree = subtree->left;
            else
                subtree = subtree->right;
            delete temp;
        }
      
    }
    rebalance(subtree);
}

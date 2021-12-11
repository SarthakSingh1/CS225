/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree &other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader &bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs)
{
    if (this != &rhs)
    {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode *current)
{
    if (current == NULL)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree &rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode *HuffmanTree::copy(const TreeNode *current)
{
    if (current == NULL)
        return NULL;
    TreeNode *node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode *
HuffmanTree::removeSmallest(queue<TreeNode *> &singleQueue,
                            queue<TreeNode *> &mergeQueue)
{
    TreeNode *single = NULL;
    TreeNode *merge = NULL;

    if (!singleQueue.empty())
        single = singleQueue.front();
    if (!mergeQueue.empty())
        merge = mergeQueue.front();

    if (!single && !merge)
        return NULL;

    else if (single && !merge)
    {
        singleQueue.pop();
        return single;
    }
    else if (!single && merge){
        mergeQueue.pop();
        return merge;
    }
    else if ((single->freq).getFrequency() <= (merge->freq).getFrequency()){
        singleQueue.pop();
        return single;
    }
    else{
        mergeQueue.pop();
        return merge;
    }
}

/**
     * @todo Your code here!
     *
     * First, place all of the leaf nodes into the singleQueue in
     * increasing order of frequency. Note: frequencies is already sorted
     * for you.
     *
     * Next, until there is only one node on the two queues (that is, one
     * of the queues is empty and one has a single node), remove the two
     * smallest entries from the two queues. Then, create a new internal
     * node with these nodes as children, whose frequency is the sum of
     * these two children's frequencies. Place the new internal node onto
     * the back of the mergeQueue.
     *
     * Finally, when there is a single node left, it is the root. Assign it
     * to the root and you're done!
     */
void HuffmanTree::buildTree(const vector<Frequency> &frequencies)
{
    queue<TreeNode *> singleQueue; // Queue containing the leaf nodes
    queue<TreeNode *> mergeQueue;  // Queue containing the inner nodes

    for(Frequency f:frequencies) 
    {
        TreeNode * b = new TreeNode(f);
        singleQueue.push(b);
    }

    while (singleQueue.size() + mergeQueue.size() > 1)
    {
        TreeNode *temp = removeSmallest(singleQueue, mergeQueue);
        TreeNode *temp2 = removeSmallest(singleQueue, mergeQueue);
        int x = temp->freq.getFrequency();
        int y = temp2->freq.getFrequency();
        TreeNode *temp3 = new TreeNode(x + y);
        temp3->right = temp2;
        temp3->left = temp;
        mergeQueue.push(temp3);
    }
    root_ = mergeQueue.front();
}
string HuffmanTree::decodeFile(BinaryFileReader &bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream &ss, BinaryFileReader &bfile)
{
    TreeNode *current = root_;
    while (bfile.hasBits())
    {
        if (bfile.getNextBit())
            current = current->right;
        else
            current = current->left;

        if (!current->left && !current->right){
            ss << (current->freq).getCharacter();
            current = root_;
        }
    }
}

void HuffmanTree::writeTree(BinaryFileWriter &bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode *current, BinaryFileWriter &bfile)
{
    if (!current->left && !current->right) {
        char character = (current->freq).getCharacter();
        bfile.writeBit(1);
        bfile.writeByte(character);
    }
    else{
        bfile.writeBit(0);
        writeTree(current->left, bfile);
        writeTree(current->right, bfile);
    }
}

HuffmanTree::TreeNode *HuffmanTree::readTree(BinaryFileReader &bfile)
{
    while (bfile.hasBits())
    {
        if (bfile.getNextBit())
        {
            char c = bfile.getNextByte();
            Frequency f(c, 0);
            TreeNode *curr = new TreeNode(f);
            return curr;
        }
        else
        {
            TreeNode *curr = new TreeNode(0);
            curr->left = readTree(bfile);
            curr->right = readTree(bfile);
            return curr;
        }
    }

    return NULL;
}

void HuffmanTree::buildMap(TreeNode *current, vector<bool> &path)
{
    // Base case: leaf node.
    if (current->left == NULL && current->right == NULL)
    {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode *current) const
{
    if (current == NULL)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
         << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string &data, BinaryFileWriter &bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter &bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode> >
{
public:
    HuffmanTreeNodeDescriptor(const TreeNode *root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else
        {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == NULL;
    }
    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }
    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

private:
    const TreeNode *subRoot_;
};

int HuffmanTree::height(const TreeNode *subRoot) const
{
    if (subRoot == NULL)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream &out) const
{
    int h = height(root_);
    if (h > _max_print_height)
    {
        out << "Tree is too big to print. Try with a small file (e.g. "
               "data/small.txt)"
            << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}

Frequency
HuffmanTree::testRemoveSmallest(vector<Frequency> single,
                                vector<Frequency> merge)
{
    queue<TreeNode *> singleQueue;
    queue<TreeNode *> mergeQueue;
    for (auto it = single.begin(); it != single.end(); ++it)
    {
        singleQueue.push(new TreeNode(*it));
    }
    for (auto it = merge.begin(); it != merge.end(); ++it)
    {
        mergeQueue.push(new TreeNode(*it));
    }

    TreeNode *testNode = removeSmallest(singleQueue, mergeQueue);
    Frequency testFreq = testNode->freq;

    delete testNode;
    while (!singleQueue.empty())
    {
        delete singleQueue.front();
        singleQueue.pop();
    }
    while (!mergeQueue.empty())
    {
        delete mergeQueue.front();
        mergeQueue.pop();
    }

    return testFreq;
}

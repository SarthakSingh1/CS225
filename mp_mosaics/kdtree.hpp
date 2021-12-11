/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
   if(curDim > Dim)
    return false;
  else{
    if(first[curDim] < second[curDim])
      return true;
    else if (first[curDim] > second[curDim])
      return false;
    else
      return first<second;
  }

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
      
  double potentialDifference = 0, currentDistance = 0, temp = 0;
  for (int i = 0; i < Dim; i++)
  {
    currentDistance += std::pow((currentBest[i] - target[i]),2);
    potentialDifference += std::pow((potential[i] - target[i]), 2);
  }
   
  if(potentialDifference < currentDistance)
    return true;
  else if(currentDistance < potentialDifference)
    return false;
  else
    return potential < currentBest;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  size = 0;
  if (newPoints.empty()){
    root = NULL;
    return;
  }
  
  vector<Point<Dim>> tempVector;
  tempVector.assign(newPoints.begin(),newPoints.end());
  buildTree(tempVector, 0, 0, newPoints.size()-1, root);
  /**
   * @todo Implement this function!
   */
}
template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim> > &currVector,int dim, int start, int end, KDTreeNode *&curRoot)
{
  
  Point<Dim> temp;
  if(currVector.empty())
    return;

  if(start>end || start<0 || end<0)
    return;
  

    int middle = (start+end)/2;
    temp = select(currVector,start,end,middle, dim);
    curRoot = new KDTreeNode(temp);
    size++;
    buildTree(currVector, (dim + 1) % Dim, start, middle - 1, curRoot->left);
    buildTree(currVector, (dim + 1) % Dim, middle+1, end, curRoot->right);

}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim> > &currVector, int start, int end, int pivotIndex, int currDim)
{
   int storeIndex = start;
   Point<Dim> pivotValue = currVector[pivotIndex];
   Point<Dim> temp = currVector[end];
   currVector[end] = currVector[pivotIndex];
   currVector[pivotIndex] = temp;

   for (int i = start; i < end; i++)
   {
     if (smallerDimVal(currVector[i], pivotValue, currDim))
     {
      auto temp = currVector[storeIndex] ;
      currVector[storeIndex] =  currVector[i];
      currVector[i]=temp;
      storeIndex++;
     }
  }
  temp = currVector[storeIndex] ;
  currVector[storeIndex] = currVector[end] ;
  currVector[end] = temp ;
  
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim> > &currVector, int start, int end, int k, int currDim)
{
  int pivotIndex = (start + end) / 2;

  if (start == end)
    return currVector[end];

  pivotIndex = partition(currVector, start, end, pivotIndex, currDim);
  if (k == pivotIndex)
    return currVector[k];
  else if (k > pivotIndex)
    return select(currVector, pivotIndex + 1, end, k, currDim);
  else
    return select(currVector, start, pivotIndex-1, k, currDim);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim> &other)
{
  /**
   * @todo Implement this function!
   */
  if(other.root == NULL || other == this){
    root = NULL;
    size = 0;
  }

  root = new KDTreeNode(other.root());

  copyNode(other.root, root);
  size = other.size;
}


template <int Dim>
void KDTree<Dim>::copyNode(KDTree<Dim>::KDTreeNode *otherRoot, KDTree<Dim>::KDTreeNode *currRoot)
{   
  if(otherRoot == NULL)
    return;

  currRoot->left = new KDTreeNode(otherRoot->left);
  currRoot->right = new KDTreeNode(otherRoot->right);

  copyNode(otherRoot->left, currRoot->left);
  copyNode(otherRoot->right, currRoot->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  this = new KDTree(rhs);
  return *this;
}


template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroyTree(root);
  root = NULL;
}
template <int Dim>
void KDTree<Dim>::destroyTree(KDTreeNode *node)
{
  if (node)
  {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if(root != NULL)
      return findNearestNeighborHelper(query, 0, root);
    
    else{
      return Point<Dim>();
      std::cout << "Tree is Null" << std::endl;
    }
    

}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim> &query , int currDim , KDTree<Dim>::KDTreeNode *curRoot) const
{
  Point<Dim> nearest;
  Point<Dim> tempNearest;
  int radius=0, splitDistance;
  bool isRecusedLeft ;

  if(curRoot->left == NULL && curRoot->right == NULL)
    return (curRoot->point) ;


  if (smallerDimVal(query, curRoot->point, currDim))
  {
    if (curRoot->left != NULL)
    {
      nearest = findNearestNeighborHelper(query, (currDim + 1) % Dim, curRoot->left);
      isRecusedLeft = true;
    }
    }
    else {
      if(curRoot->right !=NULL){
        nearest = findNearestNeighborHelper(query, (currDim + 1) % Dim, curRoot->right);
        isRecusedLeft = false;
      }
    }
    if (shouldReplace(query, nearest,curRoot->point ))
      nearest = (curRoot->point);

    for (int i = 0; i < Dim; i++){
      radius += std::pow((query[i] - nearest[i]), 2);
    }
    
    splitDistance = std::pow((curRoot->point[currDim] - query[currDim]), 2);

    if(radius >= splitDistance)
    {
      if (isRecusedLeft){
        if(curRoot->right !=NULL)
          tempNearest = findNearestNeighborHelper(query, (currDim + 1) % Dim, curRoot->right);
      }
      else{
        if (curRoot->left !=NULL)
          tempNearest = findNearestNeighborHelper(query, (currDim + 1) % Dim, curRoot->left);
      }
      if (shouldReplace(query, nearest, tempNearest))
        nearest = tempNearest; 
    }
  return nearest;
}
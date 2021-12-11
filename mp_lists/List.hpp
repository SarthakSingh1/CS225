/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()
{
  // @TODO: graded in MP3.1

  ListNode *head_ = NULL;
  ListNode *tail_ = NULL;
  length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  if (length_ > 0)
  {
    ListNode *curr = head_;
    ListNode *temp;
    while (curr != NULL)
    {
      temp = curr;
      curr = curr->next;
      delete temp;
    }
    head_ = NULL;
    tail_ = NULL;
    temp = NULL;
    length_ = 0;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  if (length_ == 0)
  {
    newNode->next = NULL;
    newNode->prev = NULL;
    head_ = newNode;
    tail_ = newNode;
  }
  else
  {
    newNode->next = head_;
    newNode->prev = NULL;
    head_->prev = newNode;
    head_ = head_->prev;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  if (length_ == 0)
  {
    head_ = tail_ = newNode;
  }
  else
  {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{
  /// @todo Graded in MP3.1

  ListNode *curr = start;
  ListNode *temp;

  for (int i = 0; i < splitPoint && curr != NULL; i++)
  {
    curr = curr->next;
  }
  if (curr->prev != NULL)
  {
    temp = curr->prev;
    curr->prev = NULL;
    temp->next = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate()
{
  // @todo Graded in MP3.1
  ListNode *current = head_, *initial, *middle, *temp;

  for (int i = 1; i <= length_ && current != NULL; i++)
  {
    if (i % 3 == 0)
    {
      temp = current->next;
      middle = current->prev;
      initial = middle->prev;

      middle->prev = initial->prev;
      if (initial->prev != NULL)
        initial->prev->next = middle;
      else
      {
        head_ = middle;
      }

      initial->prev = current;

      if (current->next != NULL)
      {
        initial->next = current->next;
        current->next->prev = initial;
      }
      else
      {
        initial->next = NULL;
        tail_ = initial;
      }
      current->next = initial;

      current = temp;
    }
    else
      current = current->next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
  /// @todo Graded in MP3.2
  bool isEdge = (startPoint == head_ && endPoint == tail_);
  bool includesTail = (startPoint != head_ && endPoint == tail_);
  bool includesHead = (startPoint == head_ && endPoint != tail_);

  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL)
    return;

  ListNode *current = endPoint, *temp, *temp2;
  ListNode *endNext = endPoint->next;
  ListNode *startPrev = startPoint->prev;
  ListNode *start = startPoint;
  while (current != NULL && current != startPrev)
  {
    temp2 = current;
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;

    if (isEdge)
    {
      if (temp2->prev == NULL)
        head_ = temp2;
      tail_ = start;
    }
    current = current->next;
  }
  if (!isEdge && !includesTail && !includesHead)
  {
    if (temp2->next == NULL)
      tail_ = temp2;

    if (endPoint->prev == NULL)
      head_ = endPoint;

    endPoint->prev = startPrev;
    startPoint->next = endNext;

    if (head_ != endPoint)
      endPoint->prev->next = endPoint;
    if (tail_ != startPoint)
      startPoint->next->prev = startPoint;
  }
  else if (includesHead)
  {

    startPoint->next = endNext;
    head_ = endPoint;
    endPoint->prev = NULL;
  }
  else if (includesTail)
  {
    startPoint->next = endNext;
    startPrev->next = endPoint;
    tail_ = start;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{

  std::cout << " Reached reverseNth " << std::endl;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL)
  {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2

  if (first == NULL)
    return second;
  if (second == NULL)
    return first;

  ListNode *begin, *savedNode;

  if (second->data < first->data)
  {
    savedNode = second;
    begin = second;
    second = second->next;
  }
  else
  {
    savedNode = first;
    begin = first;
    first = first->next;
  }

  while (first != NULL && second != NULL)
  {
    if (first->data < second->data)
    {
      begin->next = first;
      first->prev = begin;
      first = first->next;
      begin = begin->next;
    }
    else
    {
      begin->next = second;
      first->prev = begin;
      second = second->next;
      begin = begin->next;
    }
  }
  if (first != NULL && second == NULL)
  {
    begin->next = first;
    first->prev = begin;
  }
  else if (second != NULL && first == NULL)
  {
    begin->next = second;
    second->prev = begin;
  }
  return savedNode;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  if (chainLength == 1)
    return start;

  if (start->next == NULL)
    return start;

  ListNode *splitList = split(start, chainLength / 2);
  auto a = mergesort(start, chainLength / 2);
  auto b = mergesort(splitList, (chainLength % 2) + (chainLength / 2));
  return merge(a, b);
}

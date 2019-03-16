/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
  while(current != NULL) {
    ListNode * temp;
    temp = current;
    current = current->next;
    delete temp;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * new_head = new ListNode(ndata);

  if(head_){
    head_->prev = new_head;
  }

  new_head->next = head_;
  new_head->prev = nullptr;

  if(!head_){
    tail_ = new_head;
  }

  head_ = new_head;
  length_ += 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * new_tail = new ListNode(ndata);

  if(tail_){
    tail_->next = new_tail;
  }

  new_tail->prev = tail_;
  new_tail->next = nullptr;

  if(!tail_){
    head_ = new_tail;
  }

  tail_ = new_tail;
  length_ += 1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
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
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if(!startPoint || !endPoint || endPoint == startPoint){ return; }

  ListNode * temp = startPoint;

  startPoint = endPoint;
  endPoint = temp;

  while(temp){
    ListNode * prev_node = temp->prev;
    ListNode * next_node = temp->next;

    temp->next = prev_node;
    temp->prev = next_node;

    if(temp == startPoint){ break; }
    temp = next_node;
  }
}

/*
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode * cur_node = head_;
  ListNode * start_node = head_;

  int cur_count = 1;
  while(cur_node){
    if(cur_count == n){
      ListNode * prev_node = start_node->prev;
      ListNode * next_node = cur_node->next;
      
      if(start_node == head_){head_ = cur_node;}
      if(cur_node == tail_){tail_ = start_node;}

      ListNode * old_start_node_prev = start_node->prev;
      ListNode * old_last_node_next = cur_node->next;

      reverse(start_node, cur_node);

      start_node->prev = old_start_node_prev;
      if(old_start_node_prev)
        old_start_node_prev->next = start_node;
      
      cur_node->next = old_last_node_next;
      if(old_last_node_next)
        old_last_node_next->prev = cur_node;
      
      start_node = next_node;
      cur_node = next_node;
      cur_count = 1;
    }
    else{
      cur_node = cur_node->next;
      cur_count += 1;
    }
  }
  if(cur_count != 1){
    cur_node = tail_;

    ListNode * old_start_node_prev = start_node->prev;
    ListNode * old_last_node_next = cur_node->next;

    reverse(start_node, cur_node);
    
    start_node->prev = old_start_node_prev;
    if(old_start_node_prev)
      old_start_node_prev->next = start_node;
      
    cur_node->next = old_last_node_next;
    if(old_last_node_next)
      old_last_node_next->prev = cur_node;
      
    tail_ = start_node;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * cur_node = head_;
  while(cur_node && cur_node->next != tail_){
    ListNode * next_next_node = nullptr;

    if(cur_node->next->next){next_next_node = cur_node->next->next;}

    ListNode * next_node = cur_node->next;

    cur_node->next = next_next_node;

    if(next_next_node)
      next_next_node->prev = cur_node;

    tail_->next = next_node;
    next_node->prev = tail_;
    
    next_node->next = nullptr;
    
    tail_ = next_node;

    cur_node = next_next_node;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode * splitNode = start;
  int i = 0;
  while(i < splitPoint) {
    if (splitNode == NULL) {
      break;
      return NULL;
    } else {
      splitNode = splitNode -> next;
    }
    i++;
  }

  (splitNode->prev)->next = NULL;
  splitNode->prev = NULL;

  return splitNode;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
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
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * result = NULL;
  ListNode * temp1 = first;
  ListNode * temp2 = second;
  ListNode * powerOfChristCompelsYou;

  if(temp1->data < temp2->data) {
    result = temp1;
    powerOfChristCompelsYou = result;
    temp1 = temp1->next;
  } else {
    result = temp2;
    powerOfChristCompelsYou = result;
    temp2 = temp2->next;
  } 

  while(temp1 != NULL || temp2 != NULL){

    if(temp1 == NULL) {
      result->next = temp2;
      result->next->prev = result;
      break;
    } else if(temp2 == NULL){
      result->next = temp1;
      result->next->prev = result;      
      break;
    }

    if(temp1->data < temp2->data) {
      result->next = temp1;
      result->next->prev = result;
      temp1 = temp1->next;
      result = result->next;
    } else {
      result->next = temp2;
      result->next->prev = result;
      temp2 = temp2->next;
      result = result->next;
    }
  }

  return powerOfChristCompelsYou;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1) {
    return start;
  }
  int mid = chainLength/2;
  ListNode * first = start;
  ListNode * second = split(start, mid);
  first = mergesort(first,mid);
  second = mergesort(second,chainLength - mid);
  ListNode * fin = merge(first,second);
  return fin;
}

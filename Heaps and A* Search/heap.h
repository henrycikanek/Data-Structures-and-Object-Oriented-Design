#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  void heapify(int idx);
  void trickleUp(int loc);
  bool hasChild(int idx);
  std::vector<T> myheap;
  int m_;
  PComparator c_;

};

//Are there children
template <typename T, typename PComparator>
bool Heap<T, PComparator>::hasChild(int idx)
{
  int child_pos = (idx*m_) + 1;
  if(child_pos > (int) myheap.size() - 1)
  {
    return false;
  }
  else
  {
    return true;
  }
}

//constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c):
m_(m), c_(c)
{
}

//destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{}

//checks if heap is empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return myheap.empty();
}

//heapify
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int idx)
{
  //if leaf node
  if(!hasChild(idx)){
    return;
  }
  int smallChild = (m_*idx) + 1;
  //check m children
  for(int i = smallChild; i <= (m_*idx) + m_; i++)
  {
    if(i < (int) myheap.size() && c_(myheap[i], myheap[smallChild]))
    {
      smallChild = i;
    }
  }
  //swap curr with smallest child
  if(c_(myheap[smallChild], myheap[idx]))
  {
    std::swap(myheap[idx], myheap[smallChild]);
    heapify(smallChild);
  }
}

//trickle up
template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(int loc)
{
  int parent = (loc-1)/m_;
  while(parent >= 0 && c_(myheap[loc], myheap[parent]))
  {
    std::swap(myheap[parent], myheap[loc]);
    loc = parent;
    parent = (loc-1)/m_;
  }
  
}

//top
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // handles exceptions caused by trying to return 
  // top from an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return myheap[0];
}


// pop
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  //swap last element for first
  myheap[0] = myheap.back();
  myheap.pop_back();
  //perform heapify
  heapify(0);
}

//push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  //pushing
  myheap.push_back(item);
  trickleUp(myheap.size() - 1);
}

#endif

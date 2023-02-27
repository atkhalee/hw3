#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
	PComparator c_;
  unsigned int m_;
	std::vector<T> data;
	//trickleUp
  void trickleUp(unsigned int loc);
  void Heapify(unsigned int idx);


};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
	m_=m;
	c_=c;
}
//do we ned to include a destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
 
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  //push heap requires trickleUp
  //will check the condition using PComparator to determine if min or max heap
	if(empty()){
		data.push_back(item);
	}else{

		data.push_back(item);
  	trickleUp(data.size()-1);
	}

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(unsigned int loc)
{
  //starting at 0  of the indexes
 unsigned int parent = (loc-1)/m_;
 while (parent>=0 && c_(data[loc], data[parent]))
 {
	  std::swap(data[parent], data[loc]);
	  loc = parent;
  	parent = (loc)/m_;
 }
//  if(c(data[loc],data[parent])) //if comparater c returns true -->then min heap
//  {
// 	 	std::swap(data[parent], data[loc]);
// 	 	loc = parent;
//   	parent = (loc-1)/m;
//    //c(data[loc], data[parent]) --> when I remove this it is causing seg faults
// 	 //(data[loc]< data[parent])
//   //  while(parent >= 0 && c(data[loc], data[parent])){
//   //    loc = parent;
//   //    parent = (loc-1)/m;
// 	// 	 std::swap(data[parent], data[loc]);
//   //  } 
 
//  } 
 //else //when I commented out this section, I was getting seg faults
//  { //for max heap
//    while(parent >= 0 && (data[loc] > data[parent])){
//      std::swap(data[parent], data[loc]);
//      loc = parent;
//      parent = (loc-1)/m;
//    } 
//  }
 
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
	//if(empty())
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("Heap is empty");
    //throw(std::out_of_range());
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
	//pushed back a dummy variable so when size is 1, the vector is considered empty
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    //throw(std::out_of_range());
    throw std::out_of_range("Heap is empty");
    //throw std::underflow_error("Heap is empty.");
  }
	if(data.size()==1){
		data.pop_back();
	}else{
  	std::swap(data.front(), data.back());
  	data.pop_back();
		if(!(data.size()==1)){	
  		Heapify(0);
		}
	}

}
template <typename T, typename PComparator>
void Heap<T, PComparator>::Heapify(unsigned int idx)
{
	//we do now know how may children exist --> can be 2,3, or more -->depends on m
  //parent = m*idx
	unsigned int parent = idx;
	//(m * idx) +1
	unsigned int smallerChild = (m_*idx)+1;
	//for(unsigned int i =1 ; i<= m_; i++){}

	if(smallerChild+1 > data.size())
	{
		return;
	}else{
			for(unsigned int i = 1; i<= m_; i++){
				if(smallerChild+i < data.size()){
					unsigned int currChild = smallerChild +i;
					if(c_(data[currChild],data[smallerChild]))
					{
						smallerChild = currChild;
					}
					//currChild++;
				}
			}
			if(c_(data[smallerChild], data[idx]))
				{
					swap(data[idx], data[smallerChild]);
					smallerChild = parent;
					Heapify(smallerChild);
				}
		
	}
	// while(smallerChild+1 <data.size())
	// {
	// 	unsigned int currChild = smallerChild +1;
	// 		if(c_(data[currChild],data[smallerChild]))
	// 				{
	// 					smallerChild = currChild;
	// 				}
	// }
	// 	if(c_(data[smallerChild], data[idx]))
	// 		{
	// 			swap(data[idx], data[smallerChild]);
	// 			smallerChild = parent;
	// 			Heapify(smallerChild);
	// 		}
}


template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  if(data.empty()){
    return true;
  }
  
  return false;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return data.size();
}

#endif


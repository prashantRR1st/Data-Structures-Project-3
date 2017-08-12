#include <iostream>
#include "a3_priority_queue.hpp"
using namespace std;

// Queue Constructor
PriorityQueue::PriorityQueue(unsigned int capacity){
	heap_ = new DataType[capacity+1];
	capacity_=capacity;
	size_=0;
}

//Queue Destructor
PriorityQueue::~PriorityQueue(){
	delete heap_;
	heap_=NULL;
	capacity_=0;
	size_=0;
}

// Returns the number of elements in the priority queue.
unsigned int PriorityQueue::size() const{
	return size_;
}
// Returns true if the priority queue is empty, and false otherwise.
bool PriorityQueue::empty() const{
	return (size_==0);
}
// Returns true if the priority queue is full, and false otherwise.
bool PriorityQueue::full() const{
	return (size_==capacity_);
}
// Prints the contents of the priority queue.
void PriorityQueue::print() const{
	for (int i=1; i<=capacity_; i++){
		cout<< heap_[i]<<endl;
	}
}
// Returns the max element of the priority queue, but does not remove it.
PriorityQueue::DataType PriorityQueue::max() const{
	return heap_[1];
}

// Inserts value into the priority queue. Returns true if successful, and 
// false otherwise.
bool PriorityQueue::enqueue(PriorityQueue::DataType val){
	if (PriorityQueue::empty()){ //empty heap insert
		heap_[1]=val;
		size_++;
	} else if (PriorityQueue::full()){ //full heap check
		return false;
	} else {
		size_++;
		heap_[size_]=val;
		int location=size_;
		while((location/2)>=1){ //order correction loop from last element
			if (heap_[location]>heap_[location/2]){
				PriorityQueue::DataType temp;
				temp=heap_[location/2];
				heap_[location/2]=heap_[location];
				heap_[location]=temp;
			}
			location/=2; //loop counter moved to parent
		}	
	}
	return true;
}

// Removes the top element with the maximum value (priority) and rearranges 
// the resulting heap. Returns true if successful, and false otherwise.
bool PriorityQueue::dequeue(){
	if (PriorityQueue::empty()){
		return false;
	}
	PriorityQueue::DataType temp;
	heap_[1]=heap_[size_];
	size_--;
	if (PriorityQueue::empty() || size_==1) //check for empty or single item queue
		return true;
	int location=1;
	while(location<=size_){ //if left child exists but right child doesn't exist
		int LChildIndex=2*location; int RChildIndex = (2*location)+1;
		if (LChildIndex > size_)
			return true;
		else if (RChildIndex > size_)
		{
			if (heap_[LChildIndex] > heap_[location]) //correction of priority queue order
				{
					PriorityQueue::DataType temp;
					temp=heap_[LChildIndex];
					heap_[LChildIndex]=heap_[location];
					heap_[location]=temp;
					return true;
				}
		}	
		bool LGreaterThanR = (heap_[LChildIndex]>=heap_[RChildIndex]);	
		if (LGreaterThanR&&(heap_[location]<heap_[LChildIndex])){ //Swap Left
			PriorityQueue::DataType temp;
			temp=heap_[LChildIndex];
			heap_[LChildIndex]=heap_[location];
			heap_[location]=temp;
			location=LChildIndex;
		} else if (!LGreaterThanR&&(heap_[location]<heap_[RChildIndex])){ //Swap Right
			PriorityQueue::DataType temp;
			temp=heap_[RChildIndex];
			heap_[RChildIndex]=heap_[location];
			heap_[location]=temp;
			location=RChildIndex;
		} else {
			return true;
		}
	}
	return true;
		
}

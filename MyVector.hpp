
/*
 * Name    : Duy Le
 * CWID    : 88499942
 * Email   : 23dle@csu.fullerton.edu
 */


/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>

namespace CPSC131::MyVector
{

	//
	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
				if (capacity < MINIMUM_CAPACITY) {
       			 capacity = MINIMUM_CAPACITY;
   			 }
				capacity_ = capacity; 
				size_ = 0;
				elements_ = new T[capacity_];
				called_destructor_already = false;
				// TODO: Your code here
			}
			
			/// Copy constructor
			MyVector(const MyVector& other)
			{
				size_ = other.size_;
				capacity_ = other.capacity_;			
				elements_ = new T[capacity_];
				called_destructor_already = other.called_destructor_already;
				for (size_t i = 0; i < size_; ++i)
				{
					elements_[i] = other.elements_[i];
				}
				// TODO: Your code here
			}
			
			/**
			 * Destructor
			 * Cleanup here.
			 */
			~MyVector()
			{	
				if(!called_destructor_already) 
				{
				delete[] elements_;
				elements_ = nullptr;
				
				called_destructor_already = true;
				}
			}
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs) {
				if (this != &rhs) {	    					//cited from cpp reference on Assignment operator
				delete[] elements_;   					// need it  to delete old array elements 
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				called_destructor_already = rhs.called_destructor_already;
				elements_ = new T[capacity_];						//cited from cpp reference on Assignment operator
				for (size_t i = 0; i < size_; ++i) {					//cited from cpp reference on Assignment operator
					elements_[i] = rhs.elements_[i];
				}	

			}
				return *this;
			}

			/// Operator overload to at()
			T& operator[](size_t index) const
			{
				// TODO: Your code here
				if (index >= size_){
				throw std::range_error(" out of range"); //copy of at()
				}
				//	erase me
				return elements_[index];
			}
			
			/************
			 * Accessors
			 ************/
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				// TODO: Your code here
				
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				// TODO: Your code here
				
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				if (size_ == 0 ) {
				return true;
				} 
				return false;
				
			}
			
			/// Return a reference to the element at an index
			T& at(size_t index) const
			{
				// TODO: Your code here
				if (index >= size_) {
					throw std::range_error("out of range");
				}
				
				//	erase me
				return elements_[index];	
			}
			
			/***********
			 * Mutators
			 ***********/
			
			/**
			 * Reserve capacity in advance, if our capacity isn't currently large enough.
			 * Useful if we know we're about to add a large number of elements,
			 *   and we'd like to avoid the overhead of many internal changes to capacity.
			 */
			void reserve(size_t capacity)
			{
				if (capacity > capacity_) {
					changeCapacity(capacity);
				}
				
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
				if (index >= size_) {

					throw std::range_error("outside the size boundary");
				}
				elements_[index].~T(); // set should call on Destructor
				elements_[index] = element; // Set an element at an index
				
				
				//
				return elements_[index];
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				if (size_ == capacity_){

					changeCapacity(capacity_ * 2); //doubles the capactiy
				}
					elements_[size_] = element;   // Set an element at an index.
					size_++;    				// increase the size of the vector
					return elements_[size_ - 1]; //returns the newly inserted element, 
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
				if (size_ == 0) {
					throw std::range_error("vector empty");
				}

				// Make a copy of the element to be popped
				T Pop_Element_value = elements_[size_ - 1];

				// Call the destructor explicitly to clean up resources (if needed)
				elements_[size_ - 1].~T();
				
				// Decrease the size
					size_--;

					if ( size_ < capacity_ / 3) {
			// Set the new capacity to the larger of size or MINIMUM_CAPACITY
					changeCapacity(capacity_ / 2);
					if (capacity_ < size_ || size_ < MINIMUM_CAPACITY) {
					changeCapacity(MINIMUM_CAPACITY);
				}	
				}

				return Pop_Element_value; // Return the popped element
				}

			
			/**
			 * Insert an element at some index in our vector
			 * 
			 * Example:
			 * 	 Insert a 9 at index 2
			 *   Contents before: [6, 2, 7, 4, 3]
			 *   Contents after:  [6, 2, 9, 7, 4, 3]
			 * 
			 * Returns a reference to the newly added element (not the original).
			 */
			T &insert(size_t index, const T &element) {

				if (index > size_) {
  					throw std::out_of_range("out of range");
					
				} else if (size_ == capacity_) {		
					reserve(capacity_ * 2);
				}

				for (size_t i = size_; i > index; i--) {  	// reference from Professor Bein
					elements_[i] = elements_[i - 1];
				}
				elements_[index] = element;
 				elements_[index].~T();

				size_++;

				return elements_[index];
				}
			
			/**
			 * Erase one element in our vector at the specified index
			 * 
			 * Throws std::range_error if the index is out of bounds.
			 * 
			 * Example:
			 *   Erase index 2
			 *   Contents before: [8, 4, 3, 9, 1]
			 *   Contents after:  [8, 4, 9, 1]
			 * 
			 * Returns a copy of the erased element.
			 * Hint: call DTOR on original after making the copy.
			 */
			T erase(size_t index)
			{
				if (index >= size_)
				{
					throw std::range_error("index is out of bounds");
				}
				
				if (size_ <= capacity_ / 3)
				{
					changeCapacity(capacity_ / 2);		// same as pop_back

				} 								
				
				T erased_element = elements_[index]; // copy the value of the element

				 elements_[index].~T(); //calls on destructor to remove an element 
				
   				 for (size_t i = index; i < size_ - 1; i++) {  // shifts to fill a gap after erase an element  reference from Professor Bein
        		elements_[i] = elements_[i + 1];
   				 }
				 size_--; //decrease the size of the array
				//	erase me

				return erased_element; // returns the erased element 
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called)
			 * 
			 * Should also reset capacity, if needed
			*/
			void clear()
			{
				
				for (size_t i = 0; i < size_; i++) {   //reference from Professor Bein using for loop instead of while 
					elements_[i].~T();
				}
				size_ = 0;									
				changeCapacity(DEFAULT_CAPACITY);			// resets capacity 
				
				// TODO: Your code here
			}
		
				/**
				 * Begin private members and methods.
				 * You may add your own private helpers here, if you wish.
				*/
				private:
			
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
			
			 bool called_destructor_already;
			/**
			 * Helper function that is called whenever we need to change the capacity of our vector.
			 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
			 */
			void changeCapacity(size_t c)

			{
				if (c < size_)
				{
					throw std::range_error(" capacity cannot hold our existing elements.");
				} 

				T* elements = new T[c];

				for(size_t i = 0; i < size_; i++) {
					elements[i] = elements_[i];
				}
				delete[] elements_;				// need it for memory leak issues 
				elements_ = elements;
				capacity_ = c;

				
			}
			
	};

}

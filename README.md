Overview

This project is an implementation of a custom vector class in C++ that mimics some of the functionality of the standard std::vector container. The custom vector class is designed to manage dynamic arrays, offering functionalities such as memory management, element access, and modification.

Features

The implemented vector class includes the following functions:

1. reserve(size_t new_capacity)
Ensures the vector has enough memory to store at least new_capacity elements.
If new_capacity is greater than the current capacity, the function allocates additional memory.
Does not reduce the capacity of the vector.
2. set(size_t index, const T& value)
Sets the element at the specified index to value.
Requires that the index is within the bounds of the vector.
3. pushBack(const T& value)
Appends a new element to the end of the vector.
Automatically resizes the vector if the current capacity is insufficient.
4. popBack()
Removes the last element from the vector.
Does nothing if the vector is empty.
5. changeCapacity(size_t new_capacity)
Adjusts the capacity of the vector to new_capacity.
Shrinks or grows the vector’s capacity as needed.
Preserves existing elements up to the new capacity.
6. erase(size_t index)
Removes the element at the specified index.
Shifts all subsequent elements one position to the left.
Requires that the index is within bounds.
7. clear()
Removes all elements from the vector.
Sets the size of the vector to 0 but does not change its capacity.

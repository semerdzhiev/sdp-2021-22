[**Priority queue**](https://en.wikipedia.org/wiki/Priority_queue) is an **abstract data type** (**an interface** definition or **an adaptor**) that defines three operations: `is_empty`, `insert_with_priority`, and `pull_highest_priority_element`. The definition says what those functions are expected to do, but it doesn't say how it is to be implemented.

[**Binary heap**](https://en.wikipedia.org/wiki/Binary_heap) is a **data structure** and is **one way** to implement a priority queue. Its advantages are ease of implementation and that it is reasonably efficient. It's **not** necessarily the most efficient way to implement a priority queue. Whereas a heap is definitely a priority queue, by no means is it true that a priority queue is a heap.

*Can we maintain insertion order in the heap?*
>A solution is to add time of insertion attribute to the inserted element. That may be just a simple counter incremented each time a new element is inserted into the heap. Then when two elements are equal by priority, compare the time of insertion.

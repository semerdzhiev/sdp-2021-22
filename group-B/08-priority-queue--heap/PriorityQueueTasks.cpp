#include <iostream>
#include "PriorityQueue.hpp"

class MedianStruct;

int main()
{
    std::vector<int>    arr = { 10, 13, -4, 11, 16, 0, 5, 3 };

    /// Task 1
    //int kth = 5;
    //
    //PriorityQueue<int>  pq( arr.begin(), arr.end() );
    // or just std::make_heap( arr.begin(), arr.end() );
    //
    //if ( kth > pq.size() )
    //{
    //    std::cout << "No such elem";
    //}
    //else
    //{
    //    for ( size_t i = 0; i < kth - 1; i++ )
    //        pq.pop();
    //
    //    std::cout << pq.top();
    //}

    /// Task 2
    // 2 3 1 4 5    =>  med() = 3 
    // 2 3 1 4 5 6  =>  med() = (3+4)/2

    MedianStruct    medSt;

    for ( int elem : arr )
        medSt.push( elem );

    std::cout << medSt.median();

    /// Task 3 is trivial

    return 0;
}


class MedianStruct
{
public:
    float median() const
    {
        if ( maxHeap.size() == minHeap.size() )
            return (maxHeap.top() + minHeap.top()) / 2;

        return maxHeap.top();
    }

    void push( float elem )
    {
        if ( maxHeap.empty() || elem < maxHeap.top() )
            maxHeap.push( elem );

        // 1) Keep all elements <= median in the max heap
        // 2) Keep maxHeap.size() <= minHeap.size() + 1
        // 3) Keep minHeap.size() <= maxHeap.size()
        if ( maxHeap.size() > minHeap.size() + 1 )
        {
            minHeap.push( maxHeap.top() );
            maxHeap.pop();
        }
        else if ( minHeap.size() > maxHeap.size() )
        {
            maxHeap.push( minHeap.top() );
            minHeap.pop();
        }
    }

private:
    PriorityQueue<float, std::vector<float>, std::less<float>>      maxHeap;
    PriorityQueue<float, std::vector<float>, std::greater<float>>   minHeap;
};

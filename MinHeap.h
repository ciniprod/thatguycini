#include <iostream> 
#include <cstdlib>
#include <climits>
#include <cmath>

using namespace std;

class MinHeap{
    private:
        int* heap;
        int capacity;
        int size;

    public:
        MinHeap(int);
        ~MinHeap();
        void push(int);
        int pop();
        void build_heap();
        bool empty() const{
            return size == 0;
        }

    private:
        void heapify(int);
};
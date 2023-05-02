#include "MinHeap.h"

MinHeap::MinHeap(int heap_capacity){
    capacity = heap_capacity;
    size = 0;
    heap = new int[capacity];
}



void MinHeap::push(int distance){
    if(size >= capacity){
        return;
    }
    heap[size++] = distance;
}

int MinHeap::pop(){
    if(size <= 0){
        return INFINITY;
    }

    if(size == 1){
        size--;
        return heap[0];
    }

    int minimum_val = heap[0];
    heap[0] = heap[size -1];
    size--;
    heapify(0);
    return minimum_val;
}

void MinHeap::heapify(int curr){
    int smallest = curr;
    int left = 2*curr+1;
    int right = 2*curr+2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != curr) {
        int temp = heap[curr];
        heap[curr] = heap[smallest];
        heap[smallest] = temp;
        heapify(smallest);
    }
}

void MinHeap::build_heap(){
    for(int i = size/2 - 1; i >=0; i--){
        heapify(i);
    }
}

MinHeap::~MinHeap(){
    delete[] heap;
}
import time
import random
import math
import numpy
from os import listdir
def mid(a, b, c, data):
    '''Return the Index of Mid Value of data[a], data[b], data[c]'''
    if data[a] > data[b]:
        if data[b] > data[c]:
            return b
        if data[a] < data[c]:
            return a
        else:               
            return c
    else:
        if data[b] < data[c]: 
            return b
        if data[a] < data[c]: 
            return c
        else:               
            return a


def Swap(a, b, data):
    '''Exchange the value of data[a] and data[b]'''
    temp = data[a]
    data[a] = data[b]
    data[b] = temp
    return


def Qsort_knn(data, left, right, k):
    '''KNN with Quick Sort'''
    if not (left <= k and right >= k): return #Key sentences 
    print left," ",right;
    temp=data[(left + right)/2]
    #temp=data[mid(left, right, (left + right)/2, data)]
    l = left;r = right;
    while l <= r:
        while data[l] < temp: l += 1
        while data[r] > temp: r -= 1
        if l <= r:
            Swap(l, r, data)
            l += 1
            r -= 1
    if r > left: Qsort_knn(data, left, r, k)
    if l < right: Qsort_knn(data, l, right, k)
    return


def Heap_down(i, current, Heap, k=0):
    '''Maintain Heap from head'''
    next = 2 * i + 1
    while next <= current:
        if next + 1 <= current and Heap[next + k] < Heap[next + 1 + k]: next += 1 #turn to the right child.
        if not Heap[next + k] < Heap[i + k]:
            Swap(next + k, i + k, Heap)
        else: #Down can no longer continue.
            break 
        i = next
        next = next*2 + 1 #left child.
    return


def Heapsort_knn(n, k, data, Delta=0):
    '''  
    KNN with Heap Sort
    n: the number of object.
    k: you want the first k object.
    Delta: the begin of data.
    '''
    if k >=n: return
    j=0
    while j < k/2 + 2:#Intialize Heap
        Heap_down(k/2 + 1-j, k, data, Delta)
        j = j + 1
    j = 0
    while j < n-k:
        if data[j + k + Delta] < data[0 + Delta]:   #Compare with the maximum
            Swap(0 + Delta, j + k + Delta, data)    #Smaller than maximum,  Exchange
            Heap_down(0, k-1, data, Delta)          #Maintain
        j += 1


def introspectiveSort_knn(data, left, right, k, count):
    '''
    KNN with both Heapsort and QuickSort.
        n: the number of object.
    k: you want the first k object.
    '''    
    if not (left < k and right > k): return
    if count < 0 :
        Heapsort_knn(right - left + 1, k - left, data, left)
        return
    #temp=data[mid(left, right, (left + right)/2, data)]
    temp = data[(left + right)/2]
    #temp=data[left]
    l = left;r = right
    while l <=r:
        while data[l] < temp: l += 1
        while data[r] > temp: r -= 1
        if l <= r:
            Swap(l, r, data)
            l += 1
            r -= 1
    if r > left:  introspectiveSort_knn(data, left, r, k, count-1)
    if l < right: introspectiveSort_knn(data, l, right, k, count-1)
    return

class Node: 
    def __init__(self,i,d):
        self.index=i;
        self.dis=d;
        return;

    def __cmp__(self,other):
        if self.dis<other.dis:
            return -1;
        elif self.dis>other.dis:
            return 1;
        return 0;

    def __repr__(self):
        return "("+'%3d' %self.index+","+'%f' %self.dis+")"; 


def ArgSort_k(Data,n,k):
    '''Return the index of the K nearest point.'''
    node=[Node(i,Data[i]) for i in range(n)];
    introspectiveSort_knn(node, 0, n-1, k, int(math.log(n,2)))
    return [node[i].index for i in range(n)];


if __name__=='__main__':
    n=100
    k=10
    size=n
    Data=[int(math.floor(random.random()*size*2)) for i in range(size)];
    #Data.sort();Data.reverse()
    checkData=[Data[i] for i in range(n)];
    checkData.sort();
    print checkData
    print(Data.__len__());

    testData=[Data[i] for i in range(size)]
    start = time.clock()
    Heapsort_knn(n, k, testData)
    end = time.clock()
    print testData
    print(end-start);

    testData=[Data[i] for i in range(size)]
    #Data.sort();Data.reverse()
    start = time.clock()
    Qsort_knn(testData,0,n-1,k);
    end = time.clock()
    print(end-start);
    print testData


    testData=[Data[i] for i in range(size)]
    #Data.sort();Data.reverse()
    start = time.clock()
    introspectiveSort_knn(testData,0,n-1,k,int(math.log(n,2)));
    end = time.clock()
    print(end-start);
    print testData

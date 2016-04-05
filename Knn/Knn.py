import time
import random
import math
import numpy
from os import listdir

def Swap(a, b, data):
    '''Exchange the value of data[a] and data[b]'''
    temp = data[a]
    data[a] = data[b]
    data[b] = temp
    return


def Qsort_knn(data, left, right, k):
    '''KNN with Quick Sort'''
    if not (left < k and right >= k): return #Key sentences 
    #print left," ",right;
    while True:
        temp=data[random.randint(left,right-1)]
        l = left;r = right;
        while l <= r:
            while data[l] < temp: l += 1
            while data[r] > temp: r -= 1
            if l <= r:
                Swap(l, r, data)
                l += 1
                r -= 1
        if left<k<=r:   right=r
        elif l<k<=right:  left=l
        else: return


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


def introspectiveSort_knn(data, left, right, k, count=0):
    '''
    KNN with both Heapsort and QuickSort.
        n: the number of object.
    k: you want the first k object.
    '''    
    count=int(math.log(n,2));
    if not k<(right-left+1)/100:
        for i in range(count):
            temp=data[random.randint(left,right-1)]
            l = left;r = right;
            while l <= r:
                while data[l] < temp: l += 1
                while data[r] > temp: r -= 1
                if l <= r:
                    Swap(l, r, data)
                    l += 1
                    r -= 1
            if left<k<=r:   right=r
            elif l<k<=right:  left=l
            else: return;
    Heapsort_knn(right - left + 1, k - left, data, left)
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
    introspectiveSort_knn(node, 0, n-1, k)
    return [node[i].index for i in range(n)];


if __name__=='__main__':
    n=size=50000
    i=0;
    Time=[0.0 for i in range(10)];
    print(size);
    k=50
    for j in range(100):
        print j;
        #k=50*(j+1)
        Data=[random.randint(0,size*2) for i in range(size)];
        #Data.sort();Data.reverse()
        #checkData=[Data[i] for i in range(n)];
        #checkData.sort();
    
        testData=[Data[i] for i in range(size)]
        start = time.clock()
        Heapsort_knn(n, k, testData)
        Time[0]+=(time.clock()-start);
    
        testData=[Data[i] for i in range(size)]
        start = time.clock()
        Qsort_knn(testData,0,n-1,k);
        Time[1]+=(time.clock()-start);
    
    
        testData=[Data[i] for i in range(size)]
        start = time.clock()
        introspectiveSort_knn(testData,0,n-1,k);
        Time[2]+=(time.clock()-start);

        #testData2=[testData[i] for i in range(k)];testData2.sort();
        #for what in range(k):
        #    if not testData2[what]==checkData[what]:
        #        break

    for j in range(3):
        print Time[j]/100.0;
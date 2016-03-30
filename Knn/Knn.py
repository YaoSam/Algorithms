import time
import random
import math
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


def Qsort(data, left, right):
    '''Just Quick Sort between data[left] and data[right]'''
    temp = data[(left + right)/2]
    l = left
    r = right
    while l <= r:
        while data[l] < temp: l=l + 1
        while data[r] > temp: r=r-1
        if l <= r:
            Swap(l, r, data)
            l += 1
            r -= 1
    if r > left: Qsort(data, left, r)
    if l < right: Qsort(data, l, right)
    return


def Qsort_knn(data, left, right, k):
    '''KNN with Quick Sort'''
    #temp=data[mid(left, right, (left + right)/2, data)]
    if not left <= k and right >= k: return
    temp=data[(left + right)/2]
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
        if next + 1 <= current and Heap[next + k] < Heap[next + 1 + k]: next += 1
        if not Heap[next + k] < Heap[i + k]:
            Swap(next + k, i + k, Heap)
        else:
            break
        i = next
        next = next*2 + 1
    return


def Heapsort_knn(n, k, data, Delta=0):
    '''  
    KNN with Heap Sort
    n: the number of object.
    k: you want the first k object.
    Delta: the begin of data.
    '''
    if k>=n: return
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


def inspecteSort_knn(data, left, right, k, count):    
    if not left <= k and right >= k: return
    if count < 0:
        Heapsort_knn(right - left + 1, k - left, data, left)
        return
    temp = data[(left + right)/2]
    l = left;r = right
    while l <=r:
        while data[l] < temp: l += 1
        while data[r] > temp: r -= 1
        if l <= r:
            Swap(l, r, data)
            l += 1
            r -= 1
    if r > left:  inspecteSort_knn(data, left, r, k, count-1)
    if l < right: inspecteSort_knn(data, l, right, k, count-1)
    return

def myKNN(n, k, data):
    '''
    KNN with both Heapsort and QuickSort.
        n: the number of object.
    k: you want the first k object.
    '''
    inspecteSort_knn(data, 0, n-1, k, int(math.log(n,2)))


if __name__=='__main__':
    #n=1000000
    #k=n/1000
    #size=n
    #Data=[int(math.floor(random.random()*size*2)) for i in range(0,size,1)];
    #print Data.__len__()
    #start = time.clock()
    #Heapsort_knn(n, k, Data)
    #end = time.clock()
    #print end-start;
    #Data=[int(math.floor(random.random()*size*2)) for i in range(0,size,1)];
    #start = time.clock()
    #Qsort_knn(Data,0,n-1,k);
    #end = time.clock()
    #print end-start;

    #Data=[int(math.floor(random.random()*size*2)) for i in range(0,size,1)];
    #start = time.clock()
    #myKNN(n,k,Data);
    #end = time.clock()
    #print end-start;

    a=[0,3]
    b=[a for i in range(3)]
    print b
    a[1]=1;
    print b

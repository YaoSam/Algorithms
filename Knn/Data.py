# -*- coding: UTF-8 -*-
import numpy
import operator
from numpy import *
from os import listdir
from Knn import myKNN

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
        return "index: "+'%3d' %self.index+" ,distance: "+'%f' %self.dis; 

def dis(vec1,vec2):
    return sum((vec1-vec2)*(vec1-vec2));

if __name__=='__main__':
    size=100;
    j=0;
    k=10
    Data=[Node(j,((random.random()*size))) for j in range(size)];
    Origin=[Data[j].dis for j in range(size)]
    #    print Data[i].dis,Data[i].index;
    print("After KNN\n");
    myKNN(size,k,Data);
    for i in range(k):
        print Data[i];
    Origin=sort(Origin)
    print;
    for i in range(k):
        print(Origin[i])
# -*- coding: UTF-8 -*-
import numpy
import operator
from numpy import *
from os import listdir


class Node: #Äã¾õµÃÄØ£¿
    index=0
    dis=0.0
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

def dis(vec1,vec2):
    return sum((vec1-vec2)*(vec1-vec2)).cumsum(axis=0);

if __name__=='__main__':
    vec1=array([1,2,3])
    vec2=array([2,3,4])
    print dis(vec1,vec2)
    

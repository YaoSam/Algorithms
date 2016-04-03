# coding: UTF-8
from numpy import *
import operator
import math
import random
from os import listdir
import Knn
#from Knn import ArgSort_k
# 跟KNN差不多。只是这里的距离是已经提前算好的。还是本质还是通过KNN来模式识别。
def topk(distances,labels,k):
    sortedDistIndicies = Knn.ArgSort_k(distances,len(distances),k);
    #print 'sortedDistIndicies',sortedDistIndicies
    classCount={}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel,0) + 1
    #print 'classCount',classCount
    sortedClassCount = sorted(classCount.items(), key=operator.itemgetter(1), reverse=True)
    #print 'sortedClassCount',sortedClassCount
    return sortedClassCount[0][0]

# 加载数据。
def loadDataSet(fileName):
    numFeat = len(open(fileName).readline().split('\t')) - 1 # 通过\t作为间隔来统计向量的维数
    dataMat = []; labelMat = []
    fr = open(fileName)
    for line in fr.readlines():
        lineArr =[]
        curLine = line.strip().split('\t')
        for i in range(numFeat):
            lineArr.append(float(curLine[i]))
        dataMat.append(lineArr)
        labelMat.append(float(curLine[-1]))
    return dataMat,labelMat

# 谁能告诉我这个玩意在这里干什么？！差了个float？！卖萌的么……
def loadDataSet1(fileName):      #general function to parse tab -delimited floats
    numFeat = len(open(fileName).readline().split('\t')) - 1 #get number of fields
    dataMat = []; labelMat = []
    fr = open(fileName)
    for line in fr.readlines():
        lineArr =[]
        curLine = line.strip().split('\t')
        for i in range(numFeat):
            lineArr.append((curLine[i]))
        dataMat.append(lineArr)
        labelMat.append((curLine[-1]))
    return dataMat,labelMat

# 将各种数据标准化。转化成0-1的范围。防止某些数据权重过大。方法就是找出最大最小。然后直接算比例。
def autoNorm(dataSet):
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)
    ranges = maxVals - minVals
    normDataSet = zeros(shape(dataSet))
    m = dataSet.shape[0]
    normDataSet = dataSet - tile(minVals, (m,1))
    normDataSet = normDataSet/tile(ranges, (m,1))   #element wise divide
    return normDataSet, ranges, minVals

# 小测试函数。没有测试数据所以没有运行结果。
def try1() :
    dataMat1,labelMat=loadDataSet('testSet1.txt')
    dataMat=array(dataMat1)
    m,n=shape(dataMat)
    print('dataMat[1,:]',dataMat[1,:])
    list=array([2,2,4,1,5,3,2,7])
    sortd=sorted(list,reverse=True)
    sortedlist = list.argsort()
    print('sortd',sortd)
    minVals=dataMat.min(0)
    print('minVals',minVals)
    DminVals=tile(minVals,(m,1))
    #print('DminVals',DminVals)
    dataMat,labelMat=loadDataSet1('lenses.txt')
    m,n=shape(dataMat)
    print(dataMat[1][2])

if  '__name__ == __main__' :
    # try1()
    #distances=array([23,45,12,78,45,90,32,45,20])
    #labels=array([2,3,2,1,2,3,1,1,2])
    size=100;
    distances=array([random.random()*size for i in range(size)]);
    #print distances
    labels=array([int(random.random()*10) for i in range(size)])
    #print labels 
    print topk(distances,labels,10)


from numpy import *

def loadDataSet():#读取数据用的函数。
    dataMat = []; labelMat = []
    fr = open('testSet.txt')
    for line in fr.readlines():
        lineArr = line.strip().split()
        dataMat.append([1.0, float(lineArr[0]),float(lineArr[1])])
        labelMat.append(int(lineArr[2]))
    return dataMat,labelMat

def sigmoid(inX):#导数
    return 1.0/(1+exp(-inX))

def gradAscent(dataMatIn, classLabels):#最直接的方法。
    dataMatrix = mat(dataMatIn)#数据             
    labelMat = mat(classLabels).transpose() #标签的转置
    m,n = shape(dataMatrix) #size
    alpha = 0.001           #步长
    maxCycles = 500         #迭代次数
    weights = ones((n,1))   #系数。初始化为1.
    for k in range(maxCycles):              
        h = sigmoid(dataMatrix*weights) #计算梯度。
        error = (labelMat - h)          #误差，误差越大，走得越多。
        weights = weights + alpha * dataMatrix.transpose()*error #走到下一步
    return weights

def plotBestFit(weights):#画出系数为weight的图
    import matplotlib.pyplot as plt
    dataMat,labelMat=loadDataSet()#载入数据
    dataArr = array(dataMat)
    n = shape(dataArr)[0] 
    xcord1 = []; ycord1 = []#两种点
    xcord2 = []; ycord2 = []
    for i in range(n):#分别放在两个数组里面
        if int(labelMat[i])== 1:
            xcord1.append(dataArr[i,1]); 
            ycord1.append(dataArr[i,2])
        else: 
            xcord2.append(dataArr[i,1]); 
            ycord2.append(dataArr[i,2])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(xcord1, ycord1, s=30, c='red', marker='s')#分辨用两种颜色画出来。
    ax.scatter(xcord2, ycord2, s=30, c='green')
    x = arange(-3.0, 3.0, 0.1)
    y = (-weights[0]-weights[1]*x)/weights[2]
    ax.plot(x, y)
    plt.xlabel('X1'); plt.ylabel('X2');
    plt.show()

def stocGradAscent0(dataMatrix, classLabels):#改进一，每次只计算一个点。扫一遍数据结束
    m,n = shape(dataMatrix)
    alpha = 0.01
    weights = ones(n)  
    for i in range(m):
        h = sigmoid(sum(dataMatrix[i]*weights))
        error = classLabels[i] - h
        weights = weights + alpha * error * dataMatrix[i]
    return weights

def stocGradAscent1(dataMatrix, classLabels, numIter=150):#改进二。循环150次。
    m,n = shape(dataMatrix)
    weights = ones(n)   
    for j in range(numIter):
        dataIndex = range(m)
        for i in range(m):
            alpha = 4/(1.0+j+i)+0.0001 #逐渐减少步长。
            randIndex = int(random.uniform(0,len(dataIndex)))#随机选择点。防止周期性波动。
            h = sigmoid(sum(dataMatrix[randIndex]*weights))
            error = classLabels[randIndex] - h
            weights = weights + alpha * error * dataMatrix[randIndex]    
    del(dataIndex[randIndex])
    return weights

def classifyVector(inX, weights):#判断函数。没必要计算啊……直接判断>0,<0不就完了吗……
    prob = sigmoid(sum(inX*weights))
    if prob > 0.5: return 1.0
    else: return 0.0

def colicTest():#对某个数据进行测试
    frTrain = open('horseColicTraining.txt'); 
    frTest = open('horseColicTest.txt')
    trainingSet = []; trainingLabels = []
    for line in frTrain.readlines():#读取数据。以空格为分割。
        currLine = line.strip().split('\t')
        lineArr =[]
        for i in range(21):
            lineArr.append(float(currLine[i]))
        trainingSet.append(lineArr)
        trainingLabels.append(float(currLine[21]))
    trainWeights = stocGradAscent1(array(trainingSet), trainingLabels, 1000)#用改进方法2.循环1000次
    errorCount = 0; numTestVec = 0.0
    for line in frTest.readlines():#检验
        numTestVec += 1.0
        currLine = line.strip().split('\t')
        lineArr =[]
        for i in range(21):
            lineArr.append(float(currLine[i]))
        if int(classifyVector(array(lineArr),trainWeights))!= int(currLine[21]):
            errorCount += 1
    errorRate = (float(errorCount)/numTestVec)#计算错误率
    print "the error rate of this test is: %f" % errorRate
    return errorRate

def multiTest():
    numTests = 10; errorSum=0.0
    for k in range(numTests):
        errorSum += colicTest()#运算10次取平均值。
    print "after %d iterations the average error rate is: %f" % (numTests, errorSum/float(numTests))

def search2(list,x,left,right) :
    if left > right :
        print('NO')
        return -1
    middle=int((left+right)/2)
    if list[middle]==x :
        print(middle)
        return middle
    if list[middle]>x : search2(list,x,left,right-1)
    else : search2(list,x,left+1,right)


if __name__ == '__main__' :
    dataArr, lebelMat=loadDataSet();
    weights=stocGradAscent1(array(dataArr),lebelMat);
    plotBestFit(weights);
    #multiTest()

    #data=[23,45,12,56,78,90,34,43]
    #print(data[0])
    #m=shape(data)[0]
    #print(m)
    #print(data[7])
    #n=search2(data,12,1,7)
    #print(n)
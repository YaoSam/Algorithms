<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css" rel="stylesheet"></link>
#分支界限法解决01背包
##总体思路##
构建一个储存背包状态的类(**BagState**)。  
用堆(**MaxHeap**)作为优先队列的结构。  
以当前状态的价值上界作为优先队列的判别标准将状态存入队列。  
每次从队列中拿出价值上界最大的物体，遍历下一个物体，即向队列中存入两个新状态（存/不存这个物体的状态），当拿出的状态是已经遍历完所有物体的状态时，显然这就是最优解。  
因为由于优先队列的判别条件，其他物体的价值上界都比他小，而他的价值上界又恰好就是这个状态本身的价值。

##object##
包含三个变量
- value：物体的价值
- weight：物体占用的空间
- num：融合的物体的数目（对外无用）

##BagState##
接口如下：
- value()：返回背包的总价值。
- operator<<：输出背包中放入的物体。

##使用方法##
1. 输入物体（可直接构造，或是用operator>>）
2.  > `BagState solution=Solve(thing[],objectNum);`

即可得到最优解**solution**
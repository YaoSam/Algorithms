# HuffManTree

通过堆还有二叉树实现哈夫曼树（**HuffmanTree**）  
首先整体结构继承自普通二叉树（**NormalTree**）  
通过定义节点的比较函数（即直接比较节点的数据）来定义堆。  
用这个堆来实现快速查找最小的两个节点。然后结合生成新的节点放入堆。<br>
循环n-1次。即可以得到哈夫曼树。
使用方法：
---

> `HuffmanTree<int> tree(Data, DataNumber);`>

这样就可以用`Data`生成的哈夫曼树。  
**注意：请务必实现数据类型的operator>。**
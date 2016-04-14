#线段树以及线段树离散化
**基本用递归实现……懒得写了……**
##线段##
变量：  
- left，right：线段的范围。
-  cover：线段被覆盖的层数。

重载了operator >,==,<<,>>

##线段树**SegmentTree**##
继承自普通二叉树，用递归构造。结构不可更改。
构造方法  
>`SegmentTree Tree(l,r)`;

就可以构造范围从l,r的线段树。
接口：  
- insert()：插入线段。
- del()：删除线段。
- count()：线段树被计算覆盖的长度。

##线段树的离散化##
前提：
- 插入的线段已知。
- 无需再插入或删除未知的线段。  

构造方法：  
> `DiscreteSegTree Tree(Segment[],SegmentNumber);`

用的是**AVLtree**进行检索。
接口：  
- insert()：插入线段。
- del()：删除线段。
- count()：线段树被计算覆盖的长度。
**注意：不能插入删除初始化时没有的节点！**

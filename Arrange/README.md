#用栈实现的几个跟排列组合相关的函数

##AllSolution(int m,int n)##
输出完全n插树的每一个分支。  
也就是有m个位置，每一位置有n个选择。  
如输入 `Allsolution(2,5)`
输出：
>0 0  
0 1  
0 2  
0 3  
0 4  
1 0  
1 1  
1 2  
1 3  
1 4  
2 0  
2 1  
2 2  
2 3  
2 4  
3 0  
3 1  
3 2  
3 3  
3 4  
4 0  
4 1  
4 2  
4 3  
4 4  

##Combination(int m,int n)##
输出n个数取m个的取法。  
如输入 `Combination(4, 5)`
输出：
>0 1 2 3  
0 1 2 4  
0 1 3 4  
0 2 3 4  
1 2 3 4  

##Permutation(int m,int n)##
输出n个元素的取出m个的排列情况。
如输入 `Permutation(4, 5);`
输出：
>0 1 2 3  
0 1 2 4  
0 1 3 2  
0 1 3 4  
0 1 4 2  
0 1 4 3  
0 2 1 3  
0 2 1 4  
0 2 3 1  
0 2 3 4  
0 2 4 1  
0 2 4 3  
0 3 1 2   
0 3 1 4  
0 3 2 1  
0 3 2 4  
0 3 4 1  
0 3 4 2  
0 4 1 2  
0 4 1 3  
0 4 2 1  
0 4 2 3  
0 4 3 1  
0 4 3 2   
1 0 2 3  
1 0 2 4  
1 0 3 2  
1 0 3 4  
1 0 4 2  
1 0 4 3  
1 2 0 3  
1 2 0 4  
1 2 3 0  
1 2 3 4   
1 2 4 0  
1 2 4 3  
1 3 0 2  
1 3 0 4  
1 3 2 0  
1 3 2 4  
1 3 4 0  
1 3 4 2  
1 4 0 2  
1 4 0 3  
1 4 2 0  
1 4 2 3  
1 4 3 0  
1 4 3 2  
2 0 1 3  
2 0 1 4  
2 0 3 1  
2 0 3 4  
2 0 4 1  
2 0 4 3  
2 1 0 3  
2 1 0 4  
2 1 3 0  
2 1 3 4  
2 1 4 0  
2 1 4 3  
2 3 0 1  
2 3 0 4  
2 3 1 0  
2 3 1 4  
2 3 4 0  
2 3 4 1  
2 4 0 1  
2 4 0 3  
2 4 1 0  
2 4 1 3  
2 4 3 0  
2 4 3 1  
3 0 1 2  
3 0 1 4  
3 0 2 1  
3 0 2 4  
3 0 4 1  
3 0 4 2  
3 1 0 2  
3 1 0 4  
3 1 2 0  
3 1 2 4  
3 1 4 0  
3 1 4 2  
3 2 0 1  
3 2 0 4  
3 2 1 0  
3 2 1 4  
3 2 4 0  
3 2 4 1  
3 4 0 1  
3 4 0 2  
3 4 1 0  
3 4 1 2  
3 4 2 0  
3 4 2 1  
4 0 1 2  
4 0 1 3  
4 0 2 1  
4 0 2 3  
4 0 3 1  
4 0 3 2  
4 1 0 2  
4 1 0 3  
4 1 2 0  
4 1 2 3  
4 1 3 0  
4 1 3 2  
4 2 0 1  
4 2 0 3  
4 2 1 0  
4 2 1 3  
4 2 3 0  
4 2 3 1  
4 3 0 1  
4 3 0 2  
4 3 1 0  
4 3 1 2  
4 3 2 0  
4 3 2 1   
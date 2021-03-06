#解数独

##基本思路##
用了遍历+递归的做法。  
建立了一个数独的类(**sudoku**)，用来方便传输数据和统一接口。  
接口有**write()**, **find()**, **findEmpty()**, **solve()**。
- write()： 写入某一个点，并且标记**visit[]**.
- find(): **关键**，遍历查找能输入的点。通过**visit[][]**来推算。  
主要有两种方法来排除：  
 - 该位置的**visit[][]**只有一个空位了。  
  - 某个值，该位置所在的行/列/方阵只有这个位置能填。  
- findEmpty(): 找一个没有填上的空位。  
- solve(): 通过**find()**和**write()**不断填。只要无法继续为止。


##递归##
先调用**solve**。若还有空位。则通过**findEmpty()**找到空位。遍历能填的值。直到解出为止。

---------
##Example##
###Sample Input###
>8 0 0 0 0 0 0 0 0  
0 0 3 6 0 0 0 0 0  
0 7 0 0 9 0 2 0 0   
0 5 0 0 0 7 0 0 0  
0 0 0 0 4 5 7 0 0  
0 0 0 1 0 0 0 3 0  
0 0 1 0 0 0 0 6 8  
0 0 8 5 0 0 0 1 0  
0 9 0 0 0 0 4 0 0  

###In *main.cpp*###

>sudoku one;  
cin >> one;  
sudoku ans = Solve(one);  
cout << ans;
      
###Sample Output###
>空格数为：0  
8 1 2 7 5 3 6 4 9  
9 4 3 6 8 2 1 7 5  
6 7 5 4 9 1 2 8 3  
1 5 4 2 3 7 8 9 6  
3 6 9 8 4 5 7 2 1  
2 8 7 1 6 9 5 3 4  
5 2 1 9 7 4 3 6 8  
4 3 8 5 2 6 9 1 7  
7 9 6 3 1 8 4 5 2  
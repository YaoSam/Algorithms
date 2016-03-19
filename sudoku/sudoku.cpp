#pragma once
#include "sudoku.h"
int TIME = 0;
sudoku::sudoku(){
	clean();
}

void sudoku::Write(int x, int y, int value){
	if (map[y][x]>0||visit[y][x].test(value)){
		empty = -1;
		return;
	}
	empty--;
	map[y][x] = value;
	int tempX = (x - 1) / 3 * 3 + 1, tempY = (y - 1) / 3 * 3 + 1;//得到当前方块的左上角。
	int X, Y;
	Re(i, 9){
		if (i!= y){
			if (map[i][x] == map[y][x]){
				empty = -1;
				return;
			}
			visit[i][x].set(map[y][x]);
		}
		if (i!= x){
			if (map[y][i] == map[y][x]){
				empty = -1;
				return;
			}
			visit[y][i].set(map[y][x]);
		}
		X = tempX + (i-1) / 3, Y = tempY + (i-1) % 3;
		if (!(Y== y&&X== x)){
			if (map[Y][X] == map[y][x]){
				empty = -1;
				return;
			}
			visit[Y][X].set(map[y][x]);
		}		
	}

}

point sudoku::FindEmpty()const{
	Re(i, 9)
		Re(j, 9){
		if (map[j][i] == 0)
			return point(i, j);
	}
	return point(0, 0);
}

point sudoku::Find()const{
	Re(x, 9)//最简单的情况
		Re(y, 9){
		if (map[y][x] == 0 && visit[y][x].count() == 8){
			Re(i, 9)
				if (visit[y][x].test(i) == 0)
					return point(x, y, i);
		}
	}
	//二层搜索。感觉还可以搞三层四层。不过好像会很复杂……
	Re(x, 9)
		Re(y, 9){
		if (map[y][x] == 0)//寻找空格。
			Re(value, 9)
			if (visit[y][x].test(value) == 0){
				int k = 0;
				//对该行该列该方块的visit进行遍历。看是否能能填上这个数。假如都不能。那就只有这个可以填了。
				for (k = 1; k <= 9;k++)
					if (map[y][k] == 0 && x != k&&visit[y][k].test(value) == 0)//可以填
						break;
				if (k == 10)return point(x, y, value);//代表只有这个可以填
				for (k = 1; k <= 9; k++)
					if (map[k][x] == 0 && y != k&&visit[k][x].test(value)== 0)
						break;
				if (k == 10)return point(x, y, value);
				int tempX = (x - 1) / 3 * 3 + 1, tempY = (y - 1) / 3 * 3 + 1,X,Y;
				for (k = 0; k < 9;k++){
					X = tempX + k / 3, Y = tempY + k % 3;
					if (map[Y][X] == 0 && (x != X || y != Y) && visit[Y][X].test(value) == 0)
						break;
				}
				if (k == 9)return point(x, y, value);
			}
	}
	return point();
}

void sudoku::solve(){
	const point NoPoint(0, 0);
	point target;
	target = Find();
	while (!(target == NoPoint)){
		Write(target.x, target.y,target.value);
		if (empty == -1)return;
		target = Find();
	}
	return;
}

void sudoku::clean(){
	empty = 9 * 9;
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
}

std::istream& operator>>(std::istream &in, sudoku &other){
	other.clean();
	int temp;
	Re(i, 9)
		Re(j, 9){
		in >> temp;
		if (temp != 0)
			other.Write(j, i, temp);
	}
	return in;
}
std::ostream& operator<<(std::ostream &out, sudoku const &other){
	out << "空格数为：" << other.empty << std::endl;
	Re(i, 9){
		Re(j, 9)
			out << other.map[i][j] << " ";
		out << std::endl;
	}
	return out;
}
sudoku Solve(sudoku one){
	TIME++;
	one.solve();
	if (one.empty == 0)
		return one;
	else{
		//常规方法不能解决，则暴力。
		point temp = one.FindEmpty();//找到空格
		int list[10] = { 0 }, count = 0;
		Re(i, 9)//记录能填的数字
			if (one.visit[temp.y][temp.x].test(i) == 0)
				list[count++] = i;
		if (count == 0){ 
			one.empty = -1; 
			return one;
		}
		sudoku tempAns;
		re(i, count){
			tempAns = one;//临时状态
			tempAns.Write(temp.x, temp.y, list[i]);//填上能填的数字
			sudoku two=Solve(tempAns);//进入递归
			if (two.empty == 0)
				return two;
		}
		return one;
	}
}
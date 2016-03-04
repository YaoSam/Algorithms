#pragma once
#include "sudoku.h"
std::ostream& operator<<(std::ostream &out, point const &other){
	return out << "(" << other.x << "," << other.y << ")";
}

sudoku::sudoku(){
	clean();
}

void sudoku::Write(int x, int y, int value){
	if (map[y][x]>0||visit[y][x][value]>0){
		empty = -1;
		return;
	}
	empty--;
	map[y][x] = value;
	re(i,4)
		re(k, 9){
		int X = x + (k + 1)*vector[i].x, Y = y + (k + 1)*vector[i].y;
		if (!Out(X, Y)){
			if (map[Y][X] == map[y][x]){
				empty = -1;
				return;
			}
			visit[Y][X][map[y][x]]++;
			if (visit[Y][X][map[y][x]] == 1)
				visit[Y][X][0]++;
		}
		else
			break;
	}
	int X = (x - 1) / 3 * 3 + 1, Y = (y - 1) / 3 * 3 + 1;
	re(i,3)
		re(j, 3)
		if (!(Y + i == y&&X + j == x)){
			if (map[Y + i][X + j] == map[y][x]){
				empty = -1;
				return;
			}
			visit[Y + i][X + j][map[y][x]]++;
			if (visit[Y + i][X + j][map[y][x]] == 1)
				visit[Y + i][X + j][0]++;
		}
}

point sudoku::FindEmpty()const{
	re(i, 9)
		re(j, 9){
		if (map[j + 1][i + 1] == 0)
			return point(i + 1, j + 1);
	}
}

point sudoku::Find()const{
	re(ax, 9)//最简单的情况
		re(ay, 9){
		int x = ax + 1, y = ay + 1;
		if (map[y][x] == 0 && visit[y][x][0] == 8){
			re(i, 9)
				if (visit[y][x][i + 1] == 0)
					return point(x, y, i + 1);
		}
	}
	re(ax, 9)
		re(ay, 9){
		int x = ax + 1, y = ay + 1;
		if (map[y][x] == 0)
			re(v, 9)
			if (visit[y][x][v + 1] == 0){
				int value = v + 1;
				int k = 0;
				for (k = 1; k <= 9; k++){
					if (map[y][k] == 0 && x != k&&visit[y][k][value] == 0)//可以填
						break;
				}
				if (k == 10)return point(x, y, value);//只有这个可以填
				for (k = 1; k <= 9; k++)
					if (map[k][x] == 0 && y != k&&visit[k][x][value] == 0)
						break;
				if (k == 10)return point(x, y, value);
				int X = (x - 1) / 3 * 3 + 1, Y = (y - 1) / 3 * 3 + 1;
				re(i,3)
					re(j,3){
					X += i; Y += j;
				//for (k = 1; k <= 9; k++){
					//X += k / 3; Y += k % 3;
					if (map[Y][X] == 0 && (x != X || y != Y) && visit[Y][X][value] == 0)
						break;
				}
				if (k == 10)return point(x, y, value);
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
	re(i, 9)
		re(j, 9){
		in >> temp;
		if (temp != 0)
			other.Write(j + 1, i + 1, temp);
	}
	return in;
}
std::ostream& operator<<(std::ostream &out, sudoku const &other){
	out << "空格数为：" << other.empty << std::endl;
	re(i, 9){
		re(j, 9)
			out << other.map[i + 1][j + 1] << " ";
		out << std::endl;
	}
	return out;
}
sudoku Solve(sudoku one){
	TIME++;
	//if (one.empty == -1)std::cout << "错误" << std::endl;
	one.solve();
	//std::cout << one << std::endl;
	if (one.empty == 0)
		return one;
	else{
		point temp = one.FindEmpty();
		int list[10] = { 0 }, count = 0;
		re(i, 9)
			if (one.visit[temp.y][temp.x][i + 1] == 0)
				list[count++] = i + 1;
		if (count == 0){ 
			one.empty = -1; 
			return one;
		}
		sudoku tempAns;
		re(i, count){
			tempAns = one;
			tempAns.Write(temp.x, temp.y, list[i]);
			sudoku two=Solve(tempAns);
			if (two.empty == 0)
				return two;
			//std::cout << "一个错了\n";
			//std::cout << tempAns << std::endl;
		}
		return one;
	}
}
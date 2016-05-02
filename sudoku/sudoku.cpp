#pragma once
#include "sudoku.h"
int TIME = 0;
sudoku::sudoku(){
	clean();
}

void sudoku::Write(int x, int y, int value){
	if (map[y][x]>0||visit[y][x].test(value)){//对该空格进行检查。
		empty = -1;
		return;
	}
	empty--;
	map[y][x] = value;
	int tempX = (x - 1) / 3 * 3 + 1, tempY = (y - 1) / 3 * 3 + 1;//得到当前方块的左上角。
	int X, Y;
	Re(i, 9){//维护其他空格的visit。
		if (i!= y){//行
			visit[i][x].set(value);
			if (map[i][x] == map[y][x] || visit[i][x].count() == 9)//visit.count=9意味着所有数都不能填了。
				empty = -1;
		}
		if (i!= x){//列
			visit[y][i].set(value);
			if (map[y][i] == map[y][x] || visit[y][i].count() == 9)
				empty = -1;
		}
		X = tempX + (i-1) / 3, Y = tempY + (i-1) % 3;
		if (!(Y== y&&X== x)){//方块
			visit[Y][X].set(value);
			if (map[Y][X] == map[y][x] || visit[Y][X].count() == 9)
				empty = -1;
		}
		if (empty == -1)return;
	}

}

point sudoku::FindEmpty()const{//查找不能确定的空位。
	int max_count = 0;
	point ans;
	Re(j, 9)
		Re(i, 9){
		if (map[i][j] == 0&&visit[i][j].count()>max_count){//筛选出不能填的数字最多的位置
				max_count = visit[i][j].count();
				if (max_count == 2)//不可能更少了。
					return point(j, i);
				//return point(j,i);//直接返回有空格的点。不进行筛选。
				ans = point(j, i);
			}
	}
	return ans;
}

point sudoku::Find()const{//查找能确定的空位
	//唯一性判断
	Re(x, 9)
		Re(y, 9){
		if (map[y][x] == 0 && visit[y][x].count() == 8)
			Re(i, 9)
				if (visit[y][x].test(i) == 0)
					return point(x, y, i);
	}
	//存在性判断
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

void sudoku::logic_solve(){
	static const point NoPoint(0, 0);
	point target;
	target = Find();
	while (!(target == NoPoint)){
		Write(target.x, target.y,target.value);
		if (empty == -1)return;
		target = Find();
	}
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
void sudoku::Solve() {
	TIME++;
	logic_solve();//剪枝
	if (empty == 0 || empty == -1)//得到答案或者错误答案
		return ;
	//常规方法不能解决，则暴力。
	point temp = FindEmpty();//找到空格
	sudoku tempAns;
	Re(i, 9)
		if (visit[temp.y][temp.x].test(i) == 0)//填上能填的数字
		{
			tempAns = *this;//临时状态
			tempAns.Write(temp.x, temp.y, i);
			//这里肯定是无法判断是否正确的。所以不用判断empty==-1
			tempAns.Solve();//进入递归
			if (tempAns.empty == 0)
			{
				*this = tempAns;
				return;
			}
		}
}
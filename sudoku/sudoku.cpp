#pragma once
#include "sudoku.h"
int TIME = 0;
sudoku::sudoku(){
	clean();
}

void sudoku::Write(int x, int y, int value){
	if (map[y][x]>0||visit[y][x].test(value)){//�Ըÿո���м�顣
		empty = -1;
		return;
	}
	empty--;
	map[y][x] = value;
	int tempX = (x - 1) / 3 * 3 + 1, tempY = (y - 1) / 3 * 3 + 1;//�õ���ǰ��������Ͻǡ�
	int X, Y;
	Re(i, 9){//ά�������ո��visit��
		if (i!= y){//��
			visit[i][x].set(value);
			if (map[i][x] == map[y][x] || visit[i][x].count() == 9)//visit.count=9��ζ�����������������ˡ�
				empty = -1;
		}
		if (i!= x){//��
			visit[y][i].set(value);
			if (map[y][i] == map[y][x] || visit[y][i].count() == 9)
				empty = -1;
		}
		X = tempX + (i-1) / 3, Y = tempY + (i-1) % 3;
		if (!(Y== y&&X== x)){//����
			visit[Y][X].set(value);
			if (map[Y][X] == map[y][x] || visit[Y][X].count() == 9)
				empty = -1;
		}
		if (empty == -1)return;
	}

}

point sudoku::FindEmpty()const{//���Ҳ���ȷ���Ŀ�λ��
	int max_count = 0;
	point ans;
	Re(j, 9)
		Re(i, 9){
		if (map[i][j] == 0&&visit[i][j].count()>max_count){//ɸѡ�����������������λ��
				max_count = visit[i][j].count();
				if (max_count == 2)//�����ܸ����ˡ�
					return point(j, i);
				//return point(j,i);//ֱ�ӷ����пո�ĵ㡣������ɸѡ��
				ans = point(j, i);
			}
	}
	return ans;
}

point sudoku::Find()const{//������ȷ���Ŀ�λ
	//Ψһ���ж�
	Re(x, 9)
		Re(y, 9){
		if (map[y][x] == 0 && visit[y][x].count() == 8)
			Re(i, 9)
				if (visit[y][x].test(i) == 0)
					return point(x, y, i);
	}
	//�������ж�
	Re(x, 9)
		Re(y, 9){
		if (map[y][x] == 0)//Ѱ�ҿո�
			Re(value, 9)
			if (visit[y][x].test(value) == 0){
				int k = 0;
				//�Ը��и��и÷����visit���б��������Ƿ�������������������綼���ܡ��Ǿ�ֻ������������ˡ�
				for (k = 1; k <= 9;k++)
					if (map[y][k] == 0 && x != k&&visit[y][k].test(value) == 0)//������
						break;
				if (k == 10)return point(x, y, value);//����ֻ�����������
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
	out << "�ո���Ϊ��" << other.empty << std::endl;
	Re(i, 9){
		Re(j, 9)
			out << other.map[i][j] << " ";
		out << std::endl;
	}
	return out;
}
void sudoku::Solve() {
	TIME++;
	logic_solve();//��֦
	if (empty == 0 || empty == -1)//�õ��𰸻��ߴ����
		return ;
	//���淽�����ܽ����������
	point temp = FindEmpty();//�ҵ��ո�
	sudoku tempAns;
	Re(i, 9)
		if (visit[temp.y][temp.x].test(i) == 0)//�������������
		{
			tempAns = *this;//��ʱ״̬
			tempAns.Write(temp.x, temp.y, i);
			//����϶����޷��ж��Ƿ���ȷ�ġ����Բ����ж�empty==-1
			tempAns.Solve();//����ݹ�
			if (tempAns.empty == 0)
			{
				*this = tempAns;
				return;
			}
		}
}
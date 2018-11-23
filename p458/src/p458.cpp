#include <iostream>
#include <cstdlib>
using namespace std;

class GameObject{
protected:
	int distance;
	int x,y;
public:
	GameObject(int startX, int startY, int distance){
		this->x = startX;
		this->y = startY;
		this->distance = distance;
	}
	virtual ~GameObject() {};

	virtual void move() = 0;
	virtual char getShape() = 0;

	int getX() { return x; }
	int getY() { return y; }
	bool collide(GameObject *p){
		if(this->x == p->getX() && this->y == p->getY()){
			return true;
		}
		else{
			return false;
		}
	}
};

class Human : public GameObject{
public:
	Human(int d, int _x, int _y):GameObject(d,_x,_y){};
	void move() {
		char in;
		cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
		cin >> in;

		if(in=='a'){
			this->y=this->y-1;
		}
		else if(in=='s'){
			this->x=this->x+1;
		}
		else if(in=='d'){
			this->x=this->x-1;
		}
		else if(in=='f'){
			this->y=this->y+1;
		}

	};
	char getShape() {
		return 'H';
	}
	virtual ~Human() {};
};

class Monster : public GameObject{
public:
	Monster(int d, int _x, int _y):GameObject(d,_x,_y){};
	void move() {
		int num;
		while(1){
			num=rand()%4+1;
			if(num==1){
				this->y=this->y-2;
				if(this->y < 0){
					this->y=this->y+2;
				}
			}
			else if(num==2){
				this->x=this->x+2;
				if(this->x > 9){
					this->x=this->x-2;
				}
			}
			else if(num==3){
				this->x=this->x-2;
				if(this->x < 0){
					this->x=this->x+2;
				}
			}
			else if(num==4){
				this->y=this->y+2;
				if(this->y > 19){
					this->y=this->y-2;
				}
			}

			if(this->x >= 0 && this->x <= 9 && this->y >= 0 && this->y <= 19){
				break;
			}
		}

	}
	char getShape() {
		return 'M';
	}
	virtual ~Monster() {};
};

class Food : public GameObject{
public:
	Food(int d, int _x, int _y):GameObject(d,_x,_y){};
	void move() {
		int num;
		while(1){
			num=rand()%4+1;
			if(num==1){
				this->y=this->y-1;
				if(this->y < 0){
					this->y=this->y+1;
				}
			}
			else if(num==2){
				this->x=this->x+1;
				if(this->x > 9){
					this->x=this->x-1;
				}
			}
			else if(num==3){
				this->x=this->x-1;
				if(this->x < 0){
					this->x=this->x+1;
				}
			}
			else if(num==4){
				this->y=this->y+1;
				if(this->y > 19){
					this->y=this->y-1;
				}
			}

			if(this->x >= 0 && this->x <= 9 && this->y >= 0 && this->y <= 19){
				break;
			}
		}
	};
	char getShape() {
		return '@';
	}
	virtual ~Food() {};
};

int main() {

	char str[10][20];
	int q=0;
	srand((unsigned int)time(NULL));
	GameObject *h = new Human(0,0,1);
	GameObject *m = new Monster(5,5,2);
	GameObject *f = new Food(9,9,1);
	for(int i=0; i<10; i++){
		for(int o=0; o<20; o++){
			str[i][o] = '-' ;
		}
	}
	str[h->getX()][h->getY()]=h->getShape();
	str[m->getX()][m->getY()]=m->getShape();
	str[f->getX()][f->getY()]=f->getShape();
	while(1){
		cout << "** Human의 Food 먹기 게임을 시작합니다. **" << endl;
		cout << endl;

		for(int i=0; i<10; i++){
			for(int o=0; o<20; o++){
				cout << str[i][o] << " ";
			}
			cout << endl;
		}
		str[h->getX()][h->getY()]='-';
		h->move();
		str[h->getX()][h->getY()]=h->getShape();

		str[m->getX()][m->getY()]='-';
		m->move();
		str[m->getX()][m->getY()]=m->getShape();

		q++;
		if(q>=6){
			q=1;
		}
		else if(q>3){
			str[f->getX()][f->getY()]='-';
			f->move();
			str[f->getX()][f->getY()]=f->getShape();
		}


		if(h->collide(f)){
			cout << "게임에서 이겼습니다." << endl;
			break;
		}
		else if(m->collide(h)){
			cout << "몬스터에게 잡혔습니다." << endl;
			break;
		}
		else if(m->collide(f)){
			cout << "몬스터가 음식을 먹었습니다." << endl;
			break;
		}

		cout << endl;

	}

	return 0;
}

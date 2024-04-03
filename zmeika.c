#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// * * * *          
// _ _ _ _ _ _ _ _ _
//         ^
// сделайте так, чтобы
// - удаление элемента из массива
// - добавление элемента в массив
// массивы надо сделать глобальными, чтобы они были видны во всех функциях
// были отдельными функциями
// + добавьте функцию проверки самопересечения



int *p_pos_X;
int *p_pos_Y;
int number;

void field(void) {
	for(int i = 0; i < number; i++) {
	    mvaddstr(p_pos_Y[i],p_pos_X[i], "0");
	}
}

void add_value(int x,int y) {
	p_pos_X[number] = x;
	p_pos_Y[number] = y;
}

void remove_value(void) {
	for (int i = 0; i < number;i++) {
		p_pos_X[i] = p_pos_X[i + 1];
		p_pos_Y[i] = p_pos_Y[i + 1];
	}
}

int dead_snake(int x,int y,int flag) {
	for (int i = 0; i < number; i++) {
		if ((x == p_pos_X[i]) && (y == p_pos_Y[i])) {
			flag += 1;
			return flag;
		}
	}
	return flag;
}

int main() {
    initscr();
    int x = 10;
    int y = 10;
    int sizex;
    int sizey;
    char* apple = "*";
    getmaxyx(stdscr,sizey,sizex);
	int applex = rand()%sizex;
	int appley = rand()%sizey;
    p_pos_X = malloc(sizex * sizey);
    p_pos_Y = malloc(sizey * sizex);
    number = 0;
    char button;
	int flag = 0;

	while(flag < 1) {

		srand(time(NULL));
		if (x == applex && y == appley){
			applex = rand()%sizex;
			appley = rand()%sizey;
		} else {
			remove_value();
			number -= 1;
		}
		mvaddstr(appley,applex,apple);
		button = getch();
		
		erase();
		if (button == 'w'){
	    	mvaddstr(y -= 1, x, "0");
		}
		if (button == 's'){
	    	mvaddstr(y += 1, x, "0");
		}
		if (button == 'd'){
	    	mvaddstr(y, x += 1, "0");
		}
		if (button == 'a'){
	    	mvaddstr(y, x -= 1, "0");
		}
		flag = dead_snake(x,y,flag);
		add_value(x,y);
		number += 1;

		field();
    }
    endwin();
    return 0;
}
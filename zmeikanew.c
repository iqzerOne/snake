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
int first;
int sizex;
int sizey;
int razmer;


// + + +     +++++++++
 //_ _ _ _ _ _ _ _ _ _
//     ^     ^             
//     n     f 

void field(void) {
	if (first <= number) {
	    for(int i = first; i < number; i++) {
			//((x == p_pos_X[i]) && (y == p_pos_Y[i]))
			mvaddstr(p_pos_Y[i],p_pos_X[i], "0");
		}
    }else{
		for(int i = 0;i < number; i++) {
			//((x == p_pos_X[i]) && (y == p_pos_Y[i]))
	    	mvaddstr(p_pos_Y[i],p_pos_X[i], "0");
		}
		for(int j = first; j < razmer; j++) {
			//((x == p_pos_X[j]) && (y == p_pos_Y[j]))
	    	mvaddstr(p_pos_Y[j], p_pos_X[j], "0");
		}
    }
}

void add_value(int x,int y) {
	p_pos_X[number] = x;
	p_pos_Y[number] = y;
	number += 1;
    if (number >= razmer){
		number = 0;
    }
}


// + + +     +++++++++
 //_ _ _ _ _ _ _ _ _ _
//     ^     ^             
//     n     f 

void remove_value(void) {
    first += 1;
    if (first >= razmer) {
		first = 0;
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
    srand(time(NULL));
    int x = 10;
    int y = 10;
    //int sizex;
    //int sizey;
    char* apple = "*";
    getmaxyx(stdscr,sizey,sizex);
	int applex = rand()%sizex;
	int appley = rand()%sizey;
	razmer = sizex * sizey;
    //razmer = 10;
    p_pos_X = malloc(razmer * 4);
    p_pos_Y = malloc(razmer * 4);
    first = 0;
    number = 0;
    add_value(x,y);
    char button;
    int flag = 0;

	while(flag < 1) {
		mvaddstr(appley,applex,apple);
		//mvaddstr(y,x,"0");
		button = getch();
		
		erase();
		if (button == 'w'){
	    	y -= 1;
		}else if (button == 's'){
	    	y += 1;
		}else if (button == 'd'){
	    	x += 1;
		}else if (button == 'a'){
	    	x -= 1;
		}
		if (x == applex && y == appley){
			applex = rand()%sizex;
			appley = rand()%sizey;
		} else {
			remove_value();
		}
		//flag = dead_snake(x,y,flag);
		add_value(x,y);

		field();
    }
    endwin();
    return 0;
}
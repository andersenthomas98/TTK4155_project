/*
 * menu.h
 *
 * Created: 25.09.2019 09:35:39
 *  Author: thoander
 */ 


#ifndef MENU_H_
#define MENU_H_


typedef struct menuItem {
	void(*fun_ptr)(void);
	int num_children;
	struct menuItem* children[8];
	struct menuItem* parent;
	int selectedChild;
	char *name;
}menu_t, *menu_ptr;

void MENU_init(void);

void MENU_print_children(menu_ptr item);

void MENU_navigate(menu_ptr item);

void MENU_veryFunInvertingFunction();

void MENU_animation();

void MENU_pong();

void MENU_start(void);

void MENU_playGame();



#endif /* MENU_H_ */
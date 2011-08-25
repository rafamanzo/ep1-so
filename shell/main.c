#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "files.h"
#include "commands.h"

void printMenu(WINDOW *menu, int tam, int atual){
	int y, i, max;
	if( atual > tam-1 )
	{
		i = 1+(atual-tam);
		max = atual;	
	}
	else
	{
		i = 0;
		max = tam-1;
	}
	wrefresh(menu);
	mvwprintw(menu,0, 0, "Diretório Corrente: %s",get_current_dir_name());/* NÃO FUNCIONA */
	for(y = 1; i <= max; i++, y++)
	{
		if( atual == i) 
			mvwprintw(menu, y, 0, "->  %d. %s %s %s\t", i,files[i].name, files[i].date,files[i].perm);
		else
			mvwprintw(menu, y, 0, "    %d. %s %s %s\t", i,files[i].name, files[i].date,files[i].perm);
	}
	mvwprintw(menu,y, 0, "V=Visualizar, E=Editar, R=Executar, C=Mudar Dir, U=Subir, D=Descer, X=Sair");
	wrefresh(menu);
}

void parser(WINDOW *menu, int tam, int quantidade){
	int atual = 0;
	int c, qtd = quantidade;
  	char command[NAME_MAX + 5];

	while(1)
	{	
		c = wgetch(menu);
		switch(c)
		{
			case 'v': /* V - Visualizar */
				if(files[atual].perm[0] == '-'){
				  strcpy(command, "less ");
				  strcat(command, files[atual].name);
							  run(command);
				}
				break;
			case 'e': /* E - Editar */
				if(files[atual].perm[0] == '-'){
				  strcpy(command, "vi ");
				  strcat(command, files[atual].name);
				  run(command);
				}
				break;
			case 'r': /* R - Executar */
				if(files[atual].perm[0] == '-' && files[atual].perm[1] == 'r'){
							  run(files[atual].name);
				}
				break;
			case 'c': /* C - Mudar Diretório */
				if(files[atual].perm[0] == 'd'){
					if( chdir(files[atual].name) != -1){
						mvwprintw(menu, 10, 0, "erro %s\t",files[atual].name);
						qtd = startDir(files[atual].name);
						atual = 0;
						printMenu(menu, tam, atual);
					}
				}
				break;
			case 'u':  /* U - Subir */
				if( atual == 0)
					atual = 1;
				else
					atual--;
				printMenu(menu, tam, atual);
				break;
			case 'd': /* D - Descer */
				if( atual == qtd-1)
					atual = qtd-1;
				else
					atual++;
				printMenu(menu, tam, atual);
				break;
			case 'x': /* X - Sair */
				return;
		}
	}
}	

int main(int argc,char *argv[]){
 	WINDOW *menu;
	int i, tam;

	if( argc != 2 || atoi(argv[1]) < 1)
	{
		printf("Entrada inválida!\n");
		return 1;
	}

	i = startDir(".");

	initscr();
	clear();
	noecho();
	cbreak();
		
	menu = newwin(24,80,0,0);
	keypad(menu, TRUE);
	refresh();

	if( (tam = atoi(argv[1])) > i )
		tam = i;
	printMenu(menu, tam, 0);
	parser(menu, tam, i);

	clrtoeol();
	refresh();
	endwin();
	return 0;
}



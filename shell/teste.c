#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <dirent.h>

char *files[50];

void printMenu(WINDOW *menu, int tam, int atual)
{
	int y, i, max;
	if( atual > tam )
	{
		i = 1+(atual-tam);
		max = atual;	
	}
	else
	{
		i = 1;
		max = tam;
	}
	wrefresh(menu);
	mvwprintw(menu,0, 0, "Diretório Corrente: /bla/bla");
	for(y = 1; i <= max; i++, y++)
	{
		if( atual == i) 
			mvwprintw(menu, y, 0, "->  %d. %s\t", i-1,files[i-1]);
		else
			mvwprintw(menu, y, 0, "    %d. %s\t", i-1,files[i-1]);
	}
	mvwprintw(menu,y, 0, "V=Visualizar, E=Editar, R=Executar, C=Mudar Dir, U=Subir, D=Descer, X=Sair");
	wrefresh(menu);
}

void parser(WINDOW *menu, int tam, int qtd)
{
	int atual = 1;
	int c;

	while(1)
	{	
		c = wgetch(menu);
		switch(c)
		{
			case 86: /* V - Visualizar */
				
				break;
			case 69: /* E - Editar */

				break;
			case 82: /* R - Executar */
				
				break;
			case 67: /* C - Mudar Diretório */
				
				break;
			case 85:  /* U - Subir */
				if( atual == 1)
					atual = 1;
				else
					atual--;
				printMenu(menu, tam, atual);
				break;
			case 68: /* D - Descer */
				if( atual == qtd)
					atual = qtd;
				else
					atual++;
				printMenu(menu, tam, atual);
				break;
			case 88: /* X - Sair */
				return;
				break;
		}
	}
}	

int main(int argc,char *argv[])
{
 	WINDOW *menu;
	DIR *dp;
	struct dirent *entry;
	int i, tam;

	if( argc != 2 || atoi(argv[1]) < 1)
	{
		printf("Entrada inválida!\n");
		return 1;
	}

	dp = opendir(".");
	for(i = 0; (entry = readdir(dp)); i++)
		files[i] = entry->d_name;

	initscr();
	clear();
	noecho();
	cbreak();
		
	menu = newwin(24,80,0,0);
	keypad(menu, TRUE);
	refresh();

	if( (tam = atoi(argv[1])) > i )
		tam = i;
	printMenu(menu, tam, 1);
	parser(menu, tam, i);

	closedir(dp);
	clrtoeol();
	refresh();
	endwin();
	return 0;
}



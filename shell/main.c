#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "files.h"
#include "commands.h"

char erro[256];

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
  wclear(menu);
	wrefresh(menu);
  mvwprintw(menu,0, 0, "%s",erro);
  strcpy(erro, "");
	mvwprintw(menu,1, 0, "Diretório Corrente: %s",getcwd(0,0));
	for(y = 2; i <= max; i++, y++)
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
				}else{
          strcpy(erro, "Não é arquivo regular");
          strcat(erro, files[atual].name);
        }
				break;
			case 'e': /* E - Editar */
				if(files[atual].perm[0] == '-'){
				  strcpy(command, "vi ");
				  strcat(command, files[atual].name);
				  run(command);
				}else{
          strcpy(erro, "Não é arquivo regular");
          strcat(erro, files[atual].name);
        }
				break;
			case 'r': /* R - Executar */
				if(files[atual].perm[0] == '-' && files[atual].perm[3] == 'r'){
							  run(files[atual].name);
				}else{
          strcpy(erro, "Não é arquivo regular ou não é executável");
          strcat(erro, files[atual].name);
        }
				break;
			case 'c': /* C - Mudar Diretório */
				if(files[atual].perm[0] == 'd'){
					if( chdir(files[atual].name) != -1){
						qtd = startDir(".");
						atual = 0;
						printMenu(menu, tam, atual);
					}else{
            strcpy(erro, "Falha ao abrir diretório");
            printMenu(menu, tam, atual);
          }
				}else{
          strcpy(erro, "Não é diretorio");
          strcat(erro, files[atual].name);
          printMenu(menu, tam, atual);
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

  strcpy(erro, "");

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



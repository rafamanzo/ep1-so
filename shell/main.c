/*
 * main.c
 *
 *  Created on: Aug 16, 2011
 *      Author: rafael
 */

#include <ncurses.h>
#include <dirent.h>

int main()
{
	DIR *dp;
	struct dirent *entry;

	initscr();			/* Start curses mode 		  */

	dp = opendir(".");
	while ((entry = readdir(dp))){
		printw("\n %s", entry->d_name);
	}

	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}

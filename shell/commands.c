#include<unistd.h>
#include<ncurses.h>

int run(char *program){
  int child_pid;

  /*ncurses libera o terminal*/
  def_prog_mode();
	endwin();

  if(child_pid = fork()){
    waitpid(child_pid, 0, 0);
    
    /*ncurses retoma a tela*/
    reset_prog_mode();
	  refresh();
    return 0;
  }else{
    execl("/bin/sh","sh","-c",program,(char *) 0);
  }
}

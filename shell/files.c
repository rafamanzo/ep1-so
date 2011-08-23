#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include <string.h>

void stringCopy( char dest[], char *in)
{
 int i;

	for( i = 0; i <= strlen(in)+1; i++)
		dest[i] = in[i];
}

void permission(char perm[], mode_t mode)
{
	perm[1]=perm[2]=perm[3]=perm[4]=perm[5]=perm[6]=perm[7]=perm[8]=perm[9]= '-';
	perm[10] ='\n';

	/* Arquivo regular */
	if( S_ISREG(mode) )
		perm[0] = '-';
	/* Diretório */
	else if( S_ISDIR(mode) )
		perm[0] = 'd';
	/* Dispositivo de caracter */
	else if( S_ISCHR(mode) )
		perm[0] = 'c';
	/* Dispositivo de bloco */
	else if( S_ISBLK(mode) )
		perm[0] = 'b';
	/* Pipe */
	else if( S_ISFIFO(mode) )
		perm[0] = 'p';
	/* Link simbólico */
	else if( S_ISLNK(mode) )
		perm[0] = 'l';
	/* Socket */
	else if( S_ISSOCK(mode) )
		perm[0] = 's';

	/* Usuário */
	if( mode & S_IRUSR )
		perm[1] = 'r';
	if ( mode & S_IWUSR ) 
		perm[2] = 'w';
	if ( mode & S_IXUSR )
		perm[3] = 'x';
	/* Grupo */
	if ( mode & S_IRGRP ) 
		perm[4] = 'r';
	if ( mode & S_IWGRP )
		perm[5] = 'w';
	if ( mode & S_IXGRP )
		perm[6] = 'x';
	/* Outro */
	if ( mode & S_IROTH ) 
		perm[7] = 'r';
	if ( mode & S_IWOTH )
		perm[8] = 'w';
	if ( mode & S_IXOTH )
		perm[9] = 'x';
}

void newFile(int i , char *filename)
{
 struct stat buf;	
 struct tm *tm;
 file new;
 char data[10];

	 /* Nome */
	stringCopy(new.name,filename);

	stat (filename, &buf);
	/* Data */
	tm = localtime(&buf.st_mtime);
	strftime(data, sizeof(data), "%d %b %y", tm);
	stringCopy(new.date,data);

	/* Permissão */
	permission(new.perm, buf.st_mode);

	files[i] = new;

 /* para o tamanho buf.st_size */
}





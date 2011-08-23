#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

struct arquivo
{
 char name[NAME_MAX];
 char date[10];
 char *size;
 char perm[11];
};
typedef struct arquivo file;

file files[50];

void newFile(int , char *);

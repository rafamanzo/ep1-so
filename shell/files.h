#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#define MAX_DIR 1024

struct arquivo
{
 char name[NAME_MAX];
 char date[10];
 char size[6];
 char perm[11];
};
typedef struct arquivo file;

file files[MAX_DIR];

int startDir(char *);

#include "directoryFinder.h"

void directoryFinderMain::findDir() {
    char *retptr = _getcwd(NULL, 1024);
    if (retptr == NULL)
    {
    printf("Get current working directory failed.\n");
    if (errno == ERANGE)
      printf("Path exceeds max buffer length.\n");
    else if (errno == ENOMEM)
      printf("Memory cannot be allocated for path.\n");
    }
  
    printf("Current working directory: \n\n%s\n", retptr);
    free(retptr);
}
//Compile with kernel32
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

DWORD RenameFiles(char *szDir, char *fargptr, int recurs);

int streq_(char *a, char *b)
{
  unsigned long la, lb;
  la = strlen(a);
  lb = strlen(b);
  if (la != lb) return 0;
  if (memcmp(a,b,la)==0) return 1; else return 0;
}

long FindChar(char *astr, long maxlen, char fchar)
{
  long i;
  for (i=0;i<maxlen && astr[i]!=0;i++)
  {
    if (astr[i] == fchar) return i;
  }
  return -1;
}

int main(int argc, char *argv[])
{
  HANDLE hFind = INVALID_HANDLE_VALUE;
  char szDir[MAX_PATH];
  char *fargptr;
  int recurs = 0;
  DWORD dwError=0;
  
  if((argc < 2 || argc > 3) || ((argc > 2) && (streq_(argv[1],"/r"))==0) || (streq_(argv[1],"/?")))
  {
      printf("\r\nDHSC RenameFilesForWeb 1.20.00 \r\nTwitter @DHeadshot\r\nRenames files for use in MS SharePoint and other systems\r\n");
      printf("Usage: %s [/r] <directory name>\r\n", argv[0]);
          printf("\t/r\tGoes through the directories recursively within the path.  \r\n");
          printf("\t\tWithout this option, it renames only files in the specified \r\n\t\tdirectory and not in subdirectories.");
          //printf("'%s' '%s' '%d'",argv[0],argv[1],argc);
      return (1);
  }
  if (streq_(argv[1],"/r"))
  {
    fargptr = argv[2];
        recurs = 1;
  }
  else fargptr = argv[1];
  if (strlen(fargptr) > MAX_PATH - 3)
  {
    printf("\nDirectory path is too long.\n");
    return (2);
  }
  strcpy(szDir, fargptr);
  strcat(szDir, "\\*");
  dwError = RenameFiles(szDir, fargptr, recurs);
  return dwError;
}

DWORD RenameFiles(char *szDir, char *fargptr, int recurs)
{
  HANDLE hFind = INVALID_HANDLE_VALUE;
  DWORD dwError=0;
  WIN32_FIND_DATA ffd;
  hFind = FindFirstFile(szDir, &ffd);
  char chDir[MAX_PATH *2], nchDir[MAX_PATH *2];
  
  if (INVALID_HANDLE_VALUE == hFind) 
  {
    //DisplayErrorBox(TEXT("FindFirstFile"));
        printf("\nError Finding File.\n");
    dwError = GetLastError();
    return dwError;
  } 
  long ic = 0;
  int changed = 0;
  char afn[MAX_PATH] = "\0";
  do
  {
    changed = 0;
        ic = 0;
    strcpy(afn,ffd.cFileName);
    while (ic >= 0)
    {
      ic = FindChar(afn, strlen(afn),'&');
      if (ic >= 0)
          {
            afn[ic] = '_';
            changed = 1;
          }
          ic = FindChar(afn, strlen(afn),'#');
      if (ic >= 0)
          {
            afn[ic] = '_';
            changed = 1;
          }
          ic = FindChar(afn, strlen(afn),'@');
      if (ic >= 0)
          {
            afn[ic] = '_';
            changed = 1;
          }
          ic = FindChar(afn, strlen(afn),'+');
      if (ic >= 0)
          {
            afn[ic] = '_';
            changed = 1;
          }
          ic = FindChar(afn, strlen(afn),'\'');
      if (ic >= 0)
          {
            afn[ic] = '_';
            changed = 1;
          }
    }
    if (changed)
    {
      strcpy(chDir,fargptr);
          strcat(chDir,"\\");
          strcat(chDir, ffd.cFileName);
          strcpy(nchDir,fargptr);
          strcat(nchDir,"\\");
          strcat(nchDir, afn);
          switch (rename(chDir, nchDir))
          {
            case EACCES:
                  printf("Could not rename %s = maybe the file %s already exists?\n",chDir,nchDir);
                break;
                case 0:
              printf("%s -> %s\r\n",chDir,nchDir);
            break;
                default:
                  printf("Error renaming %s!\r\n",chDir);
                break;
          }
    }
        if (recurs && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (ffd.cFileName[0] != '.'))
        {
          strcpy(chDir,fargptr);
          strcat(chDir,"\\");
          strcat(chDir, ffd.cFileName);
          strcpy(nchDir,chDir);
          strcat(nchDir,"\\*");
          dwError = RenameFiles(nchDir,chDir,recurs);
          if (dwError != ERROR_NO_MORE_FILES) 
          {
            printf("Error recursing in %s!\r\n",chDir);
          }
        }
  } while (FindNextFile(hFind, &ffd) != 0);
  dwError = GetLastError();
  if (dwError != ERROR_NO_MORE_FILES) 
  {
     printf("Error finding files!\r\n");
  }
  
  FindClose(hFind);
  return dwError;
}

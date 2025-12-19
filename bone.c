#include "logo.h"
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

/*#define BOLD "\x1B[1m"*/
/*#define RED "\x1B[31m"*/
/*#define YEL "\x1B[33m"*/
/*#define GRN "\x1B[32m"*/
/*#define CYN "\x1B[36m"*/
/*#define BLU "\x1B[34m"*/
/*#define MAG "\x1B[35m"*/
#define WHT "\x1B[37m"
/*#define BLK "\x1B[30m"*/
/*#define RESET "\x1B[0m"*/
/*#define BOLDWHITE "\x1B[1m\x1B[37m"*/

#define TOP 48
#define USR 50
#define HST 50
#define OS 51
#define KRN 50
#define ARC 50
#define SHL 50
#define PKG 51
#define SEP 53
#define COL 31
#define BOT 59
#define WHTL 5
#define RSTL 4
#define DOTL 78

int getMacV(char *version);
char **count_subdirectories(const char *path);

int main(int argc, const char *argv[]) {
  char buf[sizeof(char) * 1024] = "";

  char *pTop = "\n        ╭───────────╮";
  char *pUser =
      "\n        \x1B[37m│\x1B[31m  \x1B[37m user   │\x1B[31m  ";
  char *pHost =
      "\n        \x1B[37m│\x1B[33m  \x1B[37m host   │\x1B[33m  ";
  char *pOs =
      "\n        \x1B[37m│\x1B[32m  󰌢\x1B[37m os     │\x1B[32m  ";
  char *pKern =
      "\n        \x1B[37m│\x1B[36m  \x1B[37m kernal │\x1B[36m  ";
  char *pArch =
      "\n        \x1B[37m│\x1B[36m  \x1B[37m arch   │\x1B[36m  ";
  char *pShell =
      "\n        \x1B[37m│\x1B[34m  \x1B[37m shell  │\x1B[34m  ";
  char *pPkg =
      "\n        \x1B[37m│\x1B[35m  󰏖\x1B[37m pkgs   │\x1B[35m  ";
  char *pSep = "\n        \x1B[37m├───────────┤";
  char *pCols = "\n        │  󰏘 colors │  ";
  char *pBott = "\n        \x1B[37m╰───────────╯\x1B[0m\n\n\0";

  char *pDot = "\x1B[37m●  \x1B[31m●  \x1B[33m●  \x1B[32m●  \x1B[36m●  "
               "\x1B[34m●  \x1B[35m●  \x1B[30m●";

  char *user = getlogin();
  size_t userL = strlen(user);

  char os[100];
  getMacV(os);
  size_t osL = strlen(os);

  char host[64];
  gethostname(host, sizeof(host));
  char *domain = strstr(host, ".");
  if (domain) {
    *domain = '\0';
  }
  size_t hostL = strlen(host);

  char *shell = strrchr(getenv("SHELL"), '/') + 1;
  size_t shellL = strlen(shell);

  char *kernal = "xnu";
  size_t kernL = strlen(kernal);

  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  int count = 0;
  const char *path = "/opt/homebrew/Cellar/";
  if ((dir = opendir(path)) != NULL) {
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_DIR) {
        if (entry->d_name[0] != '.') {
          char full_path[1024];
          snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
          count++;
        }
      }
    }
    closedir(dir);
  }
  char dirC[16];
  snprintf(dirC, sizeof(int), "%d", count);

  memcpy(buf, WHT, WHTL);
  memcpy(buf + WHTL, LOGO, 221);
  size_t bufInd = 226;

  memcpy(buf + bufInd, pTop, TOP);
  bufInd += TOP;

  memcpy(buf + bufInd, pUser, USR);
  bufInd += USR;
  memcpy(buf + bufInd, user, userL);
  bufInd += userL;

  memcpy(buf + bufInd, pHost, HST);
  bufInd += HST;
  memcpy(buf + bufInd, host, hostL);
  bufInd += hostL;

  memcpy(buf + bufInd, pOs, OS);
  bufInd += OS;
  memcpy(buf + bufInd, os, osL);
  bufInd += osL;

  memcpy(buf + bufInd, pKern, KRN);
  bufInd += KRN;
  memcpy(buf + bufInd, kernal, 3);
  bufInd += 3;

  // memcpy(buf + bufInd, pArch, ARC);
  // bufInd += ARC;

  memcpy(buf + bufInd, pShell, SHL);
  bufInd += SHL;
  memcpy(buf + bufInd, shell, shellL);
  bufInd += shellL;

  memcpy(buf + bufInd, pPkg, PKG);
  bufInd += PKG;
  memcpy(buf + bufInd, dirC, 3);
  bufInd += 3;

  memcpy(buf + bufInd, pSep, SEP);
  bufInd += SEP;

  memcpy(buf + bufInd, pCols, COL);
  bufInd += COL;

  memcpy(buf + bufInd, pDot, DOTL);
  bufInd += DOTL;

  memcpy(buf + bufInd, pBott, BOT);
  bufInd += BOT;

  printf("%s", buf);
  return 0;
}

#if defined(__APPLE__)
int getMacV(char *os) {
  FILE *fp;
  char line[256];
  char *name = NULL;
  char *version = NULL;
  size_t len;

  fp = fopen("/System/Library/CoreServices/SystemVersion.plist", "r");
  if (fp == NULL) {
    perror("cant get system version");
    return 1;
  }

  while (fgets(line, sizeof(line), fp)) {
    if (strstr(line, "<key>ProductVersion</key>")) {
      fgets(line, sizeof(line), fp);
      version = line;
      version += 9;
      char *end = strstr(version, "<");
      if (end) {
        *end = '\0';
      }
      memcpy(os + len + 1, version, strlen(version));
      break;
    } else if (strstr(line, "<key>ProductName</key>")) {
      fgets(line, sizeof(line), fp);
      name = line;
      name += 9;
      char *end = strstr(name, "<");
      if (end) {
        *end = '\0';
      }
      len = strlen(name);
      memcpy(os, name, len);
      memcpy(os + len, " ", 1);
    }
  }
  // printf("%s\n", name);
  // printf("%s\n", version);
  fclose(fp);

  return 0;
}
#endif /* ifdef defined(__APPLE__) */

/*char **count_subdirectories(const char *path) {*/
/*  DIR *dir;*/
/*  struct dirent *entry;*/
/*  struct stat statbuf;*/
/*  int count = 0;*/
/**/
/*  if ((dir = opendir(path)) != NULL) {*/
/*    while ((entry = readdir(dir)) != NULL) {*/
/*      if (entry->d_type == DT_DIR) {*/
/*        // Exclude "." and ".."*/
/*        if (entry->d_name[0] != '.') {*/
/*          // Get information about the directory entry*/
/*          char full_path[1024]; // Adjust the size accordingly*/
/*          snprintf(full_path, sizeof(full_path), "%s/%s", path,
 * entry->d_name);*/
/*          count++;*/
/*        }*/
/*      }*/
/*    }*/
/*  }*/
/*  closedir(dir);*/
/*  char dirC[16];*/
/*  snprintf(dirC, sizeof(int), "%d", count);*/
/*  return &dirC;*/
/*}*/

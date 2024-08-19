#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_ssize_t.h>
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
/*#define WHT "\x1B[37m"*/
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
  char *art = "                                 ____  _____\n"
              "           ____ ___  ____  _____/ __ \\/ ___/\n"
              "          / __ `__ \\/ __ `/ ___/ / / /\\__ \\\n"
              "         / / / / / / /_/ / /__/ /_/ /___/ /\n"
              "        /_/ /_/ /_/\\__,_/\\___/\\____//____/\n";

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

  /*size_t pDotL = strlen(pDot); // 78*/
  /*size_t modifeiers = strlen(BOLDWHITE); // 9*/
  /*size_t artL = strlen(art);             // 221*/
  /*size_t pTopL = strlen(pTop);           // 45*/
  /*size_t pUserL = strlen(pUser);         // 49*/
  /*size_t pHostL = strlen(pHost);         // 49*/
  /*size_t pOsL = strlen(pOs);             // 51*/
  /*size_t pKernL = strlen(pKern);         // 50*/
  /*size_t pArchL = strlen(pArch);         // 49*/
  /*size_t pShellL = strlen(pShell);       // 49*/
  /*size_t pPkgL = strlen(pPkg);           // 50*/
  /*size_t pSepL = strlen(pSep);           // 53*/
  /*size_t pColsL = strlen(pCols);         // 31*/
  /*size_t pBottL = strlen(pBott);         // 59*/
  /*size_t whtL = strlen(RESET);             // 5*/

  /*printf("dot %zu\n", pDotL);*/
  // printf("modifier %zu\n", modifeiers);
  // printf("%zu\n", artL);
  // printf("top %zu\n", pTopL);
  // printf("user %zu\n", pUserL);
  // printf("host %zu\n", pHostL);
  // printf("os %zu\n", pOsL);
  // printf("kernal %zu\n", pKernL);
  // printf("arch %zu\n", pArchL);
  // printf("shell %zu\n", pShellL);
  // printf("pkg %zu\n", pPkgL);
  /*printf("sep %zu\n", pSepL);*/
  /*printf("colors %zu\n", pColsL);*/
  /*printf("white %zu\n", whtL);*/
  /*printf("bottom %zu\n", pBottL);*/

  char *user = getlogin();
  size_t userL = strlen(user);

  char os[100];
  getMacV(os);
  size_t osL = strlen(os);

  /*int pipefd[2];*/
  /*pid_t pid;*/
  /*char buffer[256];*/
  /*ssize_t vLength;*/
  /*pipe(pipefd);*/
  /*pid = fork();*/
  /**/
  /*if (pid == 0) { // Child process (sw_vers)*/
  /*  // Close the read end of the pipe*/
  /*  close(pipefd[0]);*/
  /*  // Redirect stdout to the write end of the pipe*/
  /*  dup2(pipefd[1], STDOUT_FILENO);*/
  /*  // Close the original write end of the pipe*/
  /*  close(pipefd[1]);*/
  /*  // Execute the command*/
  /*  execlp("sw_vers", "sw_vers", NULL);*/
  /*  // If execlp fails*/
  /*  perror("execlp");*/
  /*  return 1;*/
  /*} else { // Parent process*/
  /*  // Close the write end of the pipe*/
  /*  close(pipefd[1]);*/
  /*  // Read from the pipe*/
  /*  ssize_t nbytes = read(pipefd[0], buffer, 256 - 1);*/
  /*  // Close the read end of the pipe*/
  /*  close(pipefd[0]);*/
  /*  if (nbytes == -1) {*/
  /*    perror("read");*/
  /*    return 1;*/
  /*  }*/
  /*  // Null-terminate the buffer*/
  /*  buffer[nbytes] = '\0';*/
  /*  // Tokenize the buffer*/
  /*  char *token;*/
  /*  char *delimiters = " \t\n";*/
  /*  char *tokens[100]; // Assuming at most 100 tokens*/
  /*  int token_count = 0;*/
  /**/
  /*  token = strtok(buffer, delimiters);*/
  /*  while (token != NULL && token_count < 100) {*/
  /*    tokens[token_count++] = token;*/
  /*    token = strtok(NULL, delimiters);*/
  /*  }*/
  /**/
  /*  // Print the tokens*/
  /*  printf("Tokens:\n");*/
  /*  for (int i = 0; i < token_count; ++i) {*/
  /*    printf("%d: %s\n", i, tokens[i]);*/
  /*  }*/
  /*  vLength = strlen(tokens[3]);*/
  /*  memcpy(buffer, tokens[0], 5);*/
  /*  memcpy(buffer + 5, " ", 1);*/
  /*  memcpy(buffer + 6, tokens[3], vLength);*/
  /*  memcpy(buffer + 6 + vLength, "\0", 1);*/
  /**/
  /*  wait(NULL);*/
  /*}*/
  /*int osLength = strlen(buffer);*/

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
  memcpy(buf + WHTL, art, 221);
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int keep_running = 1;

void int_handler(int signal) {
  keep_running = 0;
}

int main() {
  char buffer[1024];
  FILE *fp;

  signal(SIGINT, int_handler);

  while (keep_running) {
    fp = popen("dmesg -Hw", "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      exit(1);
    }

    while (fgets(buffer, 1024, fp) != NULL) {
      if (strstr(buffer, "offline")) {
        printf("System went offline: %s\n", buffer);
      }
     
     else if (strstr(buffer, "Booting")) {
        printf("System went online: %s\n", buffer);
      }
      }

    pclose(fp);
    sleep(1);
  }

  return 0;
}

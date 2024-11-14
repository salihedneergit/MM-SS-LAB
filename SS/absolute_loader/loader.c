/*
considering no dollar deliminator
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  int i, addr1, l, j, staddr1;
  char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];

  printf("Enter program name: ");
  scanf("%s", name);

  fp = fopen("input.txt", "r");
  if (fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  fscanf(fp, "%s", line);
  for (i = 2, j = 0; i < 8 && j < 6; i++, j++) {
    name1[j] = line[i];
  }
  name1[j] = '\0';
  printf("Name from object file: %s\n", name1);

  if (strcmp(name, name1) == 0) {
    do {
      fscanf(fp, "%s", line);
      if (line[0] == 'T') {
        for (i = 2, j = 0; i < 8 && j < 6; i++, j++) {
          staddr[j] = line[i];
        }
        staddr[j] = '\0';
        
        // Convert hexadecimal start address to integer
        staddr1 = strtol(staddr, NULL, 16);
        // jump to 12th index T^001009^0C^001003^071009 from this we only need
        // 001003^071009
        i = 12;
        while (line[i] != '\0') {
          if (line[i] != '^') {
            printf("00%X \t %c%c\n", staddr1, line[i], line[i + 1]);
            staddr1++;
            i += 2;
          } else {
            i++;
          }
        }
      } else if (line[0] == 'E') {
        break;
      }
    } while (!feof(fp));
  } else {
    printf("Program name does not match.\n");
  }

  fclose(fp);
  return 0;
}

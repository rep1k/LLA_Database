#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
  printf("Usage: %s -n -f <database file>\n", argv[0]);
  printf("\t -n - creates new database file\n");
  printf("\t -f - (required) path to the database file\n");
  return;
}

int main(int argc, char *argv[]) { 
	bool new_file = false;
  int c = 0;
  char *file_path = NULL;
  int dbfd = -1;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch (c) {
      case 'n':
        new_file = true;
        break;
      case 'f':
        file_path = optarg;
        break;
      case '?':
        printf("Unknown flag -%c\n", c);
        break;
      default:
        return -1;
    }
  }
  if (file_path == NULL) {
    printf("File_path is a required argument\n");
    print_usage(argv);
    return EXIT_SUCCESS;
  }

  if (new_file) {
    dbfd = create_db_file(file_path);
    if (dbfd == STATUS_ERROR){ 
      printf("Unable to create_db_file\n");
      return EXIT_FAILURE;
    }
  } else {
    dbfd = open_db_file(file_path);
    if (dbfd == STATUS_ERROR) {
      printf("Unable to open db file\n");
      return EXIT_FAILURE;
    }
  }


  printf("new_file: %d\n", new_file);
  printf("file_path: %s\n", file_path);

  return EXIT_SUCCESS;
}

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
  int filedescriptor;

  filedescriptor = open("testfile.txt", O_WRONLY | O_CREAT, S_IRWXU);

  if (filedescriptor < 0) {
    printf("The open operation failed...");
    return -1;
  } else {
    printf("The open operation succeeded!\n");
  }

  int writertn;

  // Including the '.' to match the 30 character length calculated in the README
  writertn = write(filedescriptor, "Writing test data to the file.", 30);

  if (writertn != 30) {
    printf("The write operation failed...");
    return -1;
  } else {
    printf("The write operation succeeded!");
  }

  return 0;
}

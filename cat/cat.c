#include <unistd.h>

#define BUFFER_SIZE 8192

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t count;
    while ((count = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, count) != count) {
            return 1;
        }
    }

    return count < 0;
}
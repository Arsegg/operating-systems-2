#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <sstream>
#include <iostream>
#include <vector>

#define SIZE 1337

size_t safe_read(int fd, void *buf, size_t count) {
    ssize_t n;
    do {
        n = read(fd, buf, count);
    } while (n < 0 && errno == EINTR);

    return n;
}

ssize_t safe_write(int fd, const void *buf, size_t count) {
    ssize_t n;
    do {
        n = write(fd, buf, count);
    } while (n < 0 && errno == EINTR);

    return n;
}

ssize_t full_write(int fd, const void *buf, size_t len) {
    ssize_t writen;
    ssize_t n = 0;
    while (len) {
        writen = safe_write(fd, buf, len);
        if (writen < 0) {
            return n ? n : writen;
        }
        n += writen;
        buf = ((const char *) buf) + writen;
        len -= writen;
    }

    return n;
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> ans;
    std::istringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter)) {
        ans.push_back(token);
    }
    if (!str.empty() && str[str.size() - 1] == delimiter) {
        ans.push_back("");
    }

    return ans;
}

void exec(const std::string &s) {
    pid_t pid = fork();
    if (!pid) {
        std::vector<std::string> vargs = split(s, ' ');
        char *args[vargs.size() + 1];
        args[vargs.size()] = NULL;
        for (int i = 0; i < vargs.size(); i++) {
            args[i] = (char *) vargs[i].c_str();
        }
        execvp(args[0], args);
    }
}

void run(const std::string &s) {
    std::vector<std::string> pipes = split(s, '|');
    exec(pipes[0]);
}

int main() {
    char s[SIZE];
    ssize_t n;
    std::string last;
    while ((n = safe_read(STDIN_FILENO, s, SIZE)) > 0) {
        std::string current(s, n);
        current = last + current;
        std::vector<std::string> commands = split(current, '\n');
        if (!commands.empty()) {
            for (int i = 0; i < commands.size() - 1; i++) {
                run(commands[i]);
            }
            last = commands[commands.size() - 1];
        }
    }

    return 0;
}
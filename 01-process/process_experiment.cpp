#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    int value = 10;

    pid_t pid = fork();

    if(pid<0){
        std::cerr << "fork() failed to start a process" << std::endl;
        return 1;
    }

    if(pid == 0){
        std::cout << "Hello! from child process" << std::endl;
        std::cout << "Child PID: " << getpid() << std::endl;
        std::cout << "Child PPID: " << getppid() << std::endl;
        value = 20;
        std::cout << "Value in child process: " << value << std::endl;

        execl("/bin/echo", "echo", "Hello, World!", nullptr);

        std::cerr << "execl() failed to execute echo command" << std::endl;
        return 1;
    }
    std::cout << "Hello! from parent process" << std::endl;
    std::cout << "Parent PID: " << getpid() << std::endl;
    std::cout << "Child PID: " << pid << std::endl;
    value = 30;
    std::cout << "Value in parent process: " << value << std::endl;

    int status = 0;

    std::cout << "Waiting for child process to finish..." << std::endl;

    waitpid(pid, &status, 0);

    std::cout << "Child process finished with status: " << status << std::endl;

    std::cout << "Value in parent process after child finished: " << value << std::endl;

    return 0;
}
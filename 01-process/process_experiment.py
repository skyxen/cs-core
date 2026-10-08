import os
import sys

def main():
    value = 10
    pid = os.fork()

    if (pid<0):
        print("fork() failed to start a process")
        sys.exit(1)
    if(pid==0):
        print("Hello! from child process")
        print("Child PID: ", os.getpid())
        print("Child PPID: ", os.getppid())
        value = 20
        print("Value in child process: ", value)

        os.execl("/bin/echo", "echo", "Hello, World!", str(None))

        print("execl() failed to execute echo command")
        sys.exit(1)
        
    print("Hello! from parent process")
    print("Parent PID: ", os.getpid())
    print("Child PID: ", pid)
    value = 30
    print("Value in parent process: ", value)
    print("Waiting for child process to finish...")
    child_pid, status = os.wait()
    print("Child process has finished.")
    print("Child PID: ", child_pid)
    print("Exit status: ", status)
    print("Value in parent process after child finishes: ", value)

if __name__ == "__main__":
    sys.exit(main())
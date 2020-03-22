/*copyright 2020 plattcr
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Platt
 *
 * Created on February 24, 2020, 1:07 PM
 */

#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <vector>
// #include <stdexecpt>
#include <iostream>
#include <iomanip>




using StrVec = std::vector<std::string>;

using namespace std;

/*
 * 
 */

/*
void serial(){
StrVecargs= {"sleep","5"};
intpid1 = forkNexec(args);
waitpid(pid1, nullptr, 0);
intpid2 = forkNexec(args);
waitpid(pid2, nullptr, 0);
}

void parallel(){
   StrVecargs= {"sleep","5"};
   intpid1 = forkNexec(args);
   intpid2 = forkNexec(args);
   waitpid(pid1, nullptr, 0);
   waitpid(pid2, nullptr, 0); 
}
*/
void input() {    
}

void myExec(StrVec argList) {   
     std::vector<char*> args;    // list of pointers to args    
     for (auto& s : argList) {        
         args.push_back(&s[0]);  // address of 1st character    
     }
     // nullptr is very important    
     args.push_back(nullptr);
     // Make execvp system call to run desired process    
     execvp(args[0], &args[0]);    
     // In case execvp ever fails, we throw a runtime execption    
     throw std::runtime_error("Call to execvp failed!");
}

int forkNexec(const StrVec& strVec) {
    // Fork and save the pid of the child process    
    int childPid = fork();
    // Call the myExec helper method in the child    
    if (childPid == 0) {
          // We are in the child process        
        myExec(strVec);
    }    
    // Control drops here only in the parent process!    
    return childPid;
}


StrVec splitCSV(std::string line) {
    // Replace comma with spaces to ease reading
// Convenience stream to read from a string
std::istringstream is(line);
StrVec retVal;  // The vector to be returned
std::string word;
// Use the usual pattern to read
while(is >> quoted(word)) {
    retVal.push_back(word);
}
return retVal;
}

int wait(int childPid) {    
    int exitCode = 0;  // Child process's exit code    
    waitpid(childPid, &exitCode, 0);  // wait for child to finish    
    return exitCode;
}

int main(int argc, char** argv) {
    // create process object - will there be only one? a new one for each input?
    // should I create this after/depending on input?
    
    std::string line;
    std::string command;
    std::string fileName;
    std::string programToExecute;
    std::string dummy;
    
    while (std::cout << "> ", std::getline(std::cin, line)) {
        std::istringstream fd(line);
        while (fd.good()) {
        fd >> command >> quoted(fileName);
        getline(fd, dummy);
        }
       // cout << command << fileName;
    // Process the input line here.
    // input is happening
        // if command is exit then break while loop
        if (command.compare("#") == 0 || line.empty()) {
            dummy = "";
            fileName = "";
            // how do I make it do this without doing else
            // 
        }        else if (command == "exit") {
            return 0;
        } else if (command == "SERIAL") {
            // serial();
        } else if (command == "PARALLEL") {
            // runProcessesParallel();
        }        else {    
           // create a strvec including all inputs separated 
           // by spaces then pass this strvec into myexec
            StrVec program = splitCSV(line);
            
            int pid = forkNexec(program);
            std::cout << "Running: " << command << " " << fileName <<
                    dummy << endl;
            std::cout << "Exit code: " << wait(pid) << endl;
        }
    }
}


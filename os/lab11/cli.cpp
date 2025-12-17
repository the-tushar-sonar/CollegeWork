#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<char *> parseCommand(string input)
{
    vector<char *> args;
    char *token = strtok(&input[0], " ");
    while (token != nullptr)
    {
        args.push_back(token);
        token = strtok(nullptr, " ");
    }
    args.push_back(nullptr);
    return args;
}

int main()
{
    string input;

    while (true)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        cout << "mini-linux:" << cwd << "$ ";

        getline(cin, input);

        if (input.empty())
            continue;

        if (input == "exit")
            break;

        if (input == "clear")
        {
            system("clear");
            continue;
        }

        vector<char *> args = parseCommand(input);

        pid_t pid = fork();

        if (pid == 0)
        {
            if (execvp(args[0], args.data()) < 0)
            {
                perror("Command not found");
            }
            exit(0);
        }
        else
        {
            wait(nullptr);
        }
    }
    return 0;
}
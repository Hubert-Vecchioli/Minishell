
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void) {
    char* nom;
    while(1)
    {
        nom = readline("minishell42-EB&HV$ ");
        if (!nom)
            break;
        printf("Bonjour, %s!\n", nom);
        add_history(nom);
    }
    return (0);
}
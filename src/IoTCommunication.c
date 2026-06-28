// Includes all used libraries
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "list.h" // From Programming and Algorithms course, manages a simple linked list

#ifdef _WIN32
    #define CLEAR_SCREEN "cls" // Windows: clear screen command
#else
    #define CLEAR_SCREEN "clear" // Linux: clear screen command
#endif

typedef struct Event_ *Event; // Pointer to Event_ struct

struct Event_ // Event struct definition
{
    char *name;  // Event name
    time_t time; // Event timestamp
};

void free_event(void *event) // Frees event memory
{
    free(event);
}

int main(int argc, char **argv)
{
    char *array_commands[] = {"Identidade Válida  ", "Identidade Inválida"}; // Event name labels
    List list = list_create();                                               // Creates a simple linked list
    // Communication setup code
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_fd; // File descriptor for Arduino communication
    system(CLEAR_SCREEN); // Clears the terminal
    printf("   _____            _             _        _____ ____ _______\n");
    printf("  / ____|          | |           | |      |_   _/ __ \\__   __|\n");
    printf(" | |     ___  _ __ | |_ _ __ ___ | | ___    | || |  | | | |   \n");
    printf(" | |    / _ \\| '_ \\| __| '__/ _ \\| |/ _ \\   | || |  | | | |   \n");
    printf(" | |___| (_) | | | | |_| | | (_) | |  __/  _| || |__| | | |   \n");
    printf("  \\_____\\___/|_| |_|\\__|_|  \\___/|_|\\___| |_____|\\____/ |_|   \n");
    printf("\n");
    printf("Comandos de Controle:\n");
    printf("i - Ligar Led Vermelho\n");
    printf("o - Desligar Led Vermelho\n");
    printf("k - Ligar Led Verde\n");
    printf("l - Desligar Led Verde\n");
    printf("b - Ligar Buzzer\n");
    printf("n - Desligar Buzzer\n");
    printf("z - Mostrar Tabela de Eventos\n");
    printf("c - Mostrar Controles\n");
    printf("q - Sair\n");
    printf("\n");

    unsigned char c = 'D'; // Character read from terminal
    tcgetattr(STDOUT_FILENO, &old_stdio);

    memset(&stdio, 0, sizeof(stdio));
    stdio.c_iflag = 0;
    stdio.c_oflag = 0;
    stdio.c_cflag = 0;
    stdio.c_lflag = 0;
    stdio.c_cc[VMIN] = 1;
    stdio.c_cc[VTIME] = 0;
    tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); // Makes input non-blocking

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL;
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;

    tty_fd = open(argv[1], O_RDWR | O_NONBLOCK); // Opens communication with Arduino
    cfsetospeed(&tio, B9600);                    // 9600 baud
    cfsetispeed(&tio, B9600);                    // 9600 baud

    tcsetattr(tty_fd, TCSANOW, &tio);
    // End of communication setup
    while (c != 'q') // Loop until user presses 'q'
    {
        if (read(tty_fd, &c, 1) > 0 && c != '0' && c != '1' && c != '2' && c != '3') // If Arduino sends a character, write to terminal (skip ID chars)
        {
            write(STDOUT_FILENO, &c, 1); // Writes character to terminal
        }

        if (read(STDIN_FILENO, &c, 1) > 0) // If user types something, send to Arduino
        {
            write(tty_fd, &c, 1); // Writes character to Arduino
        }

        if (c == '0') // If Arduino sends '0', add "Valid Identity" event with timestamp
        {
            Event event = malloc(sizeof(struct Event_)); // Allocates event memory
            event->name = array_commands[0];             // Sets event name
            event->time = time(NULL);                    // Sets event timestamp
            list_insert_last(list, event);               // Adds event to list
        }
        if (c == '1') // If Arduino sends '1', add "Invalid Identity" event with timestamp
        {
            Event event = malloc(sizeof(struct Event_)); // Allocates event memory
            event->name = array_commands[1];             // Sets event name
            event->time = time(NULL);                    // Sets event timestamp
            list_insert_last(list, event);               // Adds event to list
        }
        if (c == '2') // If Arduino sends '2', show event table
        {
            if (list_is_empty(list)) // If list is empty, show empty message
            {
                write(STDOUT_FILENO, "Nenhum evento registrado\n\r", 27); // Writes empty message
            }
            else // If list has events, show them
            {
                list_iterator_start(list);                         // Starts list iterator
                write(STDOUT_FILENO, "\n\r", 2);                   // Skips a line
                write(STDOUT_FILENO, "Lista de Eventos:\n\r", 19); // Writes event list header
                for (int i = 0; i < list_size(list); i++)          // For each event, show name and timestamp
                {
                    Event event = list_iterator_get_next(list);                             // Gets next list element
                    write(STDOUT_FILENO, event->name, strlen(event->name));                 // Writes event name
                    write(STDOUT_FILENO, " - ", 3);                                         // Writes separator
                    write(STDOUT_FILENO, ctime(&event->time), strlen(ctime(&event->time))); // Writes event timestamp
                    write(STDOUT_FILENO, "\r ", 1);                                         // Moves cursor to line start
                }
            }
        }
        if(c == '3') //If '3' is pressed, show control commands
        {
            // Writes control commands to terminal
            write(STDIN_FILENO, "\n\r", 1);
            write(STDIN_FILENO, "Comandos de Controle:\n\r", 23);
            write(STDIN_FILENO, "i - Ligar Led Vermelho\n\r", 25);
            write(STDIN_FILENO, "o - Desligar Led Vermelho\n\r", 28);
            write(STDIN_FILENO, "k - Ligar Led Verde\n\r", 22);
            write(STDIN_FILENO, "l - Desligar Led Verde\n\r", 25);
            write(STDIN_FILENO, "b - Ligar Alarme\n\r", 22);
            write(STDIN_FILENO, "n - Desligar Alarme\n\r", 25);
            write(STDIN_FILENO, "z - Mostrar Tabela de Eventos\n\r", 32);
            write(STDIN_FILENO, "c - Mostrar Controles\n\r", 24);
            write(STDIN_FILENO, "q - Sair\n\r", 11);
        }
    }

    list_destroy(list, free_event); // Frees list memory
    // End of setup code

    close(tty_fd);                                 // Closes Arduino communication
    tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio); // Restores terminal settings

    // End of communication setup

    return EXIT_SUCCESS; // Returns 0
}

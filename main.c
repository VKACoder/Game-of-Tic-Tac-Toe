#include <stdio.h>

typedef struct 
{
    char name[30];
    char choice;
    int winner;
    int score;
} 
player;

int check_row(int );
int check_column(int );
int check_diagonal(int );
void set_grid(void );
void display_grid(void );
void update_grid(int, int);
void get_details(void );
int check_position(int );

player players[2];
char grid[3][3];
int positions[9];

int main(void)
{
    int turn = 0;
    int position;
    int win;
    char next = 'Y';

    players[0].score = players[1].score = 0;

    printf("Welcome to the game of Tic-Tac-Toe\n");
    get_details();
    printf("The XO grid has the following pattern:\n| 1 | 2 | 3 |\n| 4 | 5 | 6 |\n| 7 | 8 | 9 |\nYou have to enter the respective block number!\n");
    
    while (1)
    {
        win = -1;
        set_grid();
        display_grid();

        for (int i = 0; i < 9; i++)
        {
            positions[i] = 0;
        }

        while (turn <= 8)
        {
            int chance = turn % 2;

            block:
                printf("%s\'s turn : ", players[chance].name);
                scanf("%d", &position);
                    
                if (check_position(position))
                {
                    update_grid(chance, position);
                    display_grid();
                    positions[turn] = position;
                }
                else
                {
                    printf("Block already occupied! Try again\n");
                    goto block;
                }

            players[chance].winner = check_row(chance);
            if (players[chance].winner == 1)
            {
                win = chance;
                break;
            }
            turn++;
        }

        if (win != -1)
        {
            printf("Game over! Result : %s won the game in %d moves!\n", players[win].name, (turn + 1));
            players[win].score++;
        }
        else
        {
            printf("Game over! Result : Draw\n");
        }

        fflush(stdin);
        printf("Up for another round (Y/N) : ");
        scanf("%c", &next);

        if (next == 'n' || next == 'N')
        {
            printf("Overall result: ");
            if (players[0].score > players[1].score)
                printf("%s won!\n", players[0].name);
            else if (players[0].score < players[1].score)
                printf("%s won!\n", players[1].name);
            else    
                printf("DRAW\n");
            break;
        }
    }
    return 0;
}

void set_grid(void)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = '-';
        }
    }
}

void get_details(void)
{
    for (int i = 0; i < 2; i++)
    {
        players[i].winner = 0;
        printf("Enter player %d\'s name : ", (i + 1));
        scanf("%s", players[i].name);
        fflush(stdin);

        if (i == 0)
        {
            wrong:
                printf("Enter your choice (X/O) : ");
                scanf("%c", &players[i].choice);
                fflush(stdin);

            if (!(players[i].choice == 'x' || players[i].choice == 'o' || players[i].choice == 'X' || players[i].choice == 'O'))
            {
                printf("Invalid Input!\n");
                goto wrong;
            }
        }
        else
        {
            players[i].choice = (players[0].choice == 'X' || players[0].choice == 'x') ? 'O' : 'X';
            printf("%s has been alloted to %c\n\n", players[i].name, players[i].choice);
        }
    }
}

void update_grid(int number, int pos)
{
    if (pos <= 3)
    {
        grid[0][(pos - 1)] = players[number].choice;
    }
    else if (pos <= 6)
    {
        grid[1][(pos % 4)] = players[number].choice;
    }
    else
    {
        grid[2][(pos % 7)] = players[number].choice;
    }
}

void display_grid(void)
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n|");
        for (int j = 0; j < 3; j++)
        {
            printf(" %c |", grid[i][j]);
        }
    }
    printf("\n\n");
}

int check_row(int number)
{
    int count;
    for (int i = 0; i < 3; i++)
    {
        count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == players[number].choice)
            {
                count++;
                if (count == 3)
                    return 1;
            }
            else
                break;
        }
    }
    return (check_column(number));
}

int check_column(int number)
{
    int count;
    for (int i = 0; i < 3; i++)
    {
        count = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grid[j][i] == players[number].choice)
            {
                count++;
                if (count == 3)
                    return 1;
            }
            else    
                break;
        }
    }
    return (check_diagonal(number));
}

int check_diagonal(int number)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][i] == players[number].choice)
        {
            count++;
            if (count == 3)
                return 1;
        }
        else   
            break;
    }
    
    count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][(2 - i)] == players[number].choice)
        {
            count++;
            if (count == 3)
                return 1;
        }
        else
            break;
    }
    return 0;
}

int check_position(int pos)
{
    for (int i = 0; i < 9; i++)
    {
        if (positions[i] == pos)
            return 0;
    }
    return 1;
}
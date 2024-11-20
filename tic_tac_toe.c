#include <stdio.h>

int main()
{
    char choose = 'y';

    while (choose != 'n')
    {
        printf("\nEnter '100' terminate the game before the next time a player is asked to enter the block location\n");
        char name1[20], name2[20];
        printf("Player 1 name : ");
        scanf("%s", name1);

        printf("\nPlayer 1 name : ");
        scanf("%s", name2);

        printf("%s is assinged 1 for inputing\n%s is assigned 0 for inputing", name1,name2);

        int win = 0;
        char matrix[3][3];
        int terminate;
        int whoseTurn = 2;
        while (terminate != 100)
        {
            int x, y;
            if (whoseTurn == 2)
            {
                printf("It's %s's turn to make a move!", name1);
                whoseTurn = 1;
                printf("Enter the coordinates of the block in which you wanna input (space seperated integers) : ");
                scanf("%d %d", &x, &y); // add error handling when x and y are beyond constraints and if the block is preoccupied
                matrix[x][y] = '1';
            }

            else
            {
                printf("It's %s's turn ot make the move", name2);
                whoseTurn = 2;
            }

            if ((matrix[0][0] == matrix[1][1] == matrix[2][2]) || (matrix[0][2] == matrix[1][1] == matrix[2][0]) || (matrix[0][0] == matrix[1][0] == matrix[2][0]) || (matrix[0][1] == matrix[1][1] == matrix[2][1]) || (matrix[0][2] == matrix[1][2] == matrix[2][2]) || (matrix[0][0] == matrix[0][1] == matrix[0][2]) || (matrix[1][0] == matrix[1][1] == matrix[1][2]) || (matrix[2][0] == matrix[2][1] == matrix[2][2]))
            {
                if (whoseTurn == 1)
                {
                    printf("Hurray! %s wins", name1);
                }
                else if (whoseTurn == 2)
                {
                    printf("Hurray! %s wins", name2);
                }

                break;
            }
            else if (1) /*if all place occupied*/
            {
                printf("Ohh! The Game ended in Draw! \nNobody wins");

                break;
            }
        }

        printf("Wanna Replay the game? (y/n) : ");
        scanf("%c", &choose);
        if (choose = 'n')
        {
            printf("Okay! See you again on some another beautiful day!\n\nHave a nice Day!\n\n");
        }
    }
    return 0;
}
#include <stdio.h>
// Made by Mr.Quantum (Darshan Patel)

// struct players{
//     char name[20];

// }; // can upgrade to display score of the player by history file in one by one game
int check(char matrix[3][3]);
void printCanvas(char matrix[3][3]);
void updateHistory(char name1[20], char name2[20], int whoseTurn);
int findLastGameNumber();

int main()
{
    char choose = 'y';

    while (choose == 'y' || choose == 'Y')
    {
        printf("Instructions:-\n\t1) Enter '-1 -1' to terminate the game before the next time a player is asked to enter the block location\n\t2) Enter the coordinates of the block in which you wanna input (space seperated integers) when asked Coordinates\n\t3) The coordinates index starts from 1,1 to 3,3 \n4) Press H to see game History\n");

        char name1[20], name2[20];
        printf("Player 1 name : ");
        fgets(name1, sizeof(name1), stdin); // to store the full names along with space in between

        printf("Player 2 name : ");
        fgets(name2, sizeof(name2), stdin);

        printf("\n%s is assinged 'X'\n%s is assigned 'O'\n", name1, name2);

        int win = 0;
        char matrix[3][3] = {
            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}}; // So that initially the every block is different valued because here I check equal character in the blocks to decide winner.
        int terminate;
        int whoseTurn = 2;

        int count = 0; // for counting to check whether all the blocks are occupied or not. And then check if its draw.

        while (1)
        {
            int x, y;
            if (whoseTurn == 2)
            {
                printf("It's %s's turn to make a move!\n", name1);
                whoseTurn = 1;
                int error = 0;
                while (error != 1) // error handling
                {
                    printf("\nCoordinates : ");
                    scanf("%d %d", &x, &y);

                    if (x == -1)
                    {
                        return -1; // terminate the game
                    }

                    if (((x > 3) || (x < 1)) || ((y > 3) || (y < 1)))
                    {
                        printf("Please Enter valid coordinates!");
                    }
                    else if (matrix[x - 1][y - 1] == 'X' || matrix[x - 1][y - 1] == 'O')
                    {
                        printf("The block is already occupied. Please enter valid coordinates!");
                    }
                    else
                    {
                        error = 1;
                    }
                }

                matrix[x - 1][y - 1] = 'X';
                count++;
                printCanvas(matrix);
            }

            else
            {
                printf("It's %s's turn to make the move", name2);
                whoseTurn = 2;
                int error = 0;
                while (error != 1) // error handling
                {
                    printf("\nCoordinates : ");
                    scanf("%d %d", &x, &y);
                    if (x == -1)
                    {
                        return -1;
                    }

                    if (((x > 3) || (x < 1)) || ((y > 3) || (y < 1)))
                    {
                        printf("Please Enter valid coordinates!");
                    }
                    else if (matrix[x - 1][y - 1] == 'X' || matrix[x - 1][y - 1] == 'O')
                    {
                        printf("The block is already occupied. Please enter valid coordinates!");
                    }
                    else
                    {
                        error = 1;
                    }
                }

                matrix[x - 1][y - 1] = 'O';
                count++;
                printCanvas(matrix);
            }

            int checkWin = check(matrix);
            if (checkWin == 1)
            {
                if (whoseTurn == 1)
                {
                    printf("\nHurray! %s wins!", name1);
                }
                else if (whoseTurn == 2)
                {
                    printf("\nHurray! %s wins!", name2);
                }
                break;
            }
            else if (count == 9) /*if all place occupied*/
            {
                printf("Ohh! The Game ended in Draw! \nNobody wins");
                break;
            }
        }

        updateHistory(name1, name2, whoseTurn);

        printf("\n\nWanna Replay the game? (y/n)[case insensitive] : ");

        getchar(); // somehow some buffer newline character is being taken by scanf below, hence used this to clear any buffer

        scanf("%c", &choose);
        if (choose == 'n')
        {
            printf("\nOkay! See you again on some another beautiful day!\n\nHave a nice Day ahead!\n\n");
        }
    }
    return 0;
}

int check(char matrix[3][3])
{
    int result = 0;

    for (int i = 0; i < 3; i++)
    {
        if (((matrix[i][0] == matrix[i][1]) && (matrix[i][1] == matrix[i][2])) || ((matrix[0][i] == matrix[1][i]) && (matrix[1][i] == matrix[2][i])))
        {
            result = 1;
            return result;
        }
    }

    if ((matrix[0][0] == matrix[1][1]) && (matrix[1][1] == matrix[2][2]) || ((matrix[0][2] == matrix[1][1]) && matrix[1][1] == matrix[2][0]))
    {
        result = 1;
        return result;
    }

    return 0;
}

void printCanvas(char matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        printf("\t\t\t");

        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] != 'X' && matrix[i][j] != 'O')
            {
                printf(".   ");
            }

            else
            {
                printf("%c   ", matrix[i][j]);
            }
        }
        printf("\n\n");
    }
    printf("\n");
}

void updateHistory(char name1[20], char name2[20], int whoseTurn)
{
    char *winner; // pointer to store adress of winner so That I can print it in history file below
    if (whoseTurn == 1)
    {
        winner = name1;
    }
    else
    {
        winner = name2;
    }

    FILE *fptr1;

    fptr1 = fopen("history.txt", "a"); // opens in both read and write mode
    if (fptr1 == NULL)
    {
        printf("Error opening game history file...\nHistory is not saved.\nProcess Terminated");
        return;
    }

    int gameNumber = findLastGameNumber();

    fprintf(fptr1, "\n{\n"
                   "\tGame number : %d\n"
                   "\tPlayer 1 : %s"
                   "\tPlayer 2 : %s"
                   "\tWho Won : %s"
                   "}\n",
            (gameNumber+1), name1, name2, winner);
    fclose(fptr1);
}

int findLastGameNumber()
{
    FILE *fptr2;
    fptr2 = fopen("history.txt", "r");
    fseek(fptr2, 0, SEEK_END);

    int position = 0;
    char ch;
    int count=0;
    while (1) // Note that atleast one previous Entry in whole file must be there for this to work. Because This is the simplest logic I come up with. Hence I have written 0th entry by default
    {
        // printf("counting\n");
        fseek(fptr2, -1, SEEK_CUR);
        ch = fgetc(fptr2);

        if (ch == '\n')
        {
            count++;
        }

        if (count == 5)
        {
            break;
        }

        fseek(fptr2, -1, SEEK_CUR); // I had to do this again because reading the cahracter by fgetc moves the pointer forward again by one position
    }

    int gameNumber = 0;
    char TempCharNum;
    for (int i = 0; i < 3; i++) //Setting maximum file history to 3 digit number as it already is beyond what anyone would actually play XD
    {

        fseek(fptr2, -1, SEEK_CUR);

        if (fgetc(fptr2) == ' ')
        {
            break;
        }

        TempCharNum = fgetc(fptr2);
        if (i == 0)
        {
            gameNumber += (TempCharNum - '0');
        }
        else
        {
            gameNumber += (10 * (i) * (TempCharNum - '0')); // Here I am converting character to integer
            fseek(fptr2, -1, SEEK_CUR);
        }
    }

    return gameNumber;
}
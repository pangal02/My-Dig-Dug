/*  Panagiotis Galiotos
    AM: 2022202000033
    dit20033@go.uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **obs_table(char **table, int N, int M, double percentage_obs);
char **soil(char **arr, int N, int M);
char **getMemory(char **array, int N, int M);
int Dig_Doug(char **table, int M);
char **diam(char **table, int N, int M, int diamonds);
int path(char **table, int N, int M, int x, int y, char com, int steps, int diamonds, int *cntD, int *sumD, int *vald, int *cntm);
void print_table(char **table, int N, int M);
int Random(int num);
int found_x(char **array, int N, int M);
int found_y(char **array, int N, int M);
int down(char **table, int N, int M, int x, int y, int *vald);

int falling = 0;

int main(int argc, char *argv[])
{
    int i, j, N, M, diamonds, cntD = 0, sumD = 0, x = 0, y, steps = 0, cntm = 0, val_diam = 0, maxD = 300, lvl = 0, p;
    char **table = NULL, **array = NULL, dif, trash, com;
    double percentage_obs;
    int valid = 0;

    srand(time(NULL));

    printf("WELCOME!!\n");
    printf("\nEasy  (E/e)\nMedium  (M/m)\nHard  (H/h)\nExit  (X/x)\nChoose Difficulty: ");
    while (!valid)
    {
        printf("Give difficulty (E/e, M/m, H/h, X/x): ");
        scanf(" %c", &dif);

        switch (dif)
        {
        case 'E':
        case 'e':
            valid = 1;
            break;
        case 'M':
        case 'm':
            valid = 1;
            break;
        case 'H':
        case 'h':
            valid = 1;
            break;
        case 'X':
        case 'x':
            printf("\nBYE!\n");
            
            valid = 1;
            return 0;
            break;
        default:
            printf("Enter a valid input\n");
            while (getchar() != '\n'); // Καθαρισμός του input buffer
        }
    }
    while (getchar() != '\n');
    printf("\"Enter dimensions of (5x5) and larger\"\n");
    printf("Enter dimensions \"only integers\" (N and M): ");
    scanf("%d %d", &N, &M);

    while (((N < 5) || (M < 5)) || (N * M > maxD))
    {
        // scanf("%c", &trash);
        while (getchar() != '\n');
        printf("Enter dimensions (N >= 5 and M >= 5)  AND (N x M) <= MAX (300): ");
        scanf("%d %d", &N, &M);
    }
    while (getchar() != '\n');

    if ((dif == 'E') || (dif == 'e'))
    {
        percentage_obs = 0.1;
        diamonds = 3;
    }
    else if ((dif == 'M') || (dif == 'm'))
    {
        percentage_obs = 0.15;
        diamonds = 6;
    }
    else if ((dif == 'H') || (dif == 'h'))
    {
        percentage_obs = 0.20;
        diamonds = 9;
    }

    // tamplo

    do
    {
        printf("\n*******LEVEL %d*******", ++lvl);
        table = getMemory(table, N, M);
        table = soil(table, N, M);
        table = obs_table(table, N, M, percentage_obs);
        y = Dig_Doug(table, M);
        table = diam(table, N, M, diamonds);
        print_table(table, N, M);

        while (cntD < diamonds)
        {
            x = found_x(table, N, M);
            y = found_y(table, N, M);
            fflush(stdin);
            printf("\nLevel diamond value: %d", sumD);
            printf("\nGame diamond value: %d", val_diam);
            printf("\nMake your move(s): ");
            scanf("%c", &com);
            if ((com == 'X') || (com == 'x'))
            {
                printf("\nGAME OVER!\nBYE!\n");
                exit(0);
            }
            scanf("%d", &steps);
            fflush(stdin);
            while (((com != 'U') && (com != 'u')) && ((com != 'D') && (com != 'd')) && ((com != 'L') && (com != 'l')) && ((com != 'R') && (com != 'r')) && ((com != 'X') && (com != 'x')) == 1)
            {
                scanf("%c", &com);
                printf("\nERROR: Enter a valid command (U/u/D/d/L/l/R/r/X/x)");
                printf("\nMake your move(s): ");
                scanf("%c", &com);
                if ((com == 'X') || (com == 'x'))
                {
                    printf("\nGAME OVER!\nBYE!\n");
                    exit(0);
                }
                scanf("%d", &steps);
                fflush(stdin);
                
            }
            scanf("%c", &trash);

            while (steps <= 0)
            {
                printf("\nERROR: Move(s) only > 0\n");
                printf("\nMake your move(s): ");
                scanf("%c", &com);
                scanf("%d", &steps);
                scanf("%c", &trash);
            }
            path(table, N, M, x, y, com, steps, diamonds, &cntD, &sumD, &val_diam, &cntm);
            print_table(table, N, M);
            printf("\n%s%d %s\n", "Dig Doug moved for: ", cntm, "blocks!");

            cntm = 0;
        }

        sumD = 0;
        cntD = 0;
        // adeiasma mnhmhs tou level
        for (i = 0; i < N; i++)
        {
            free(table[i]);
        }
        free(table);

        // next level
        if ((dif == 'E') || (dif == 'e'))
        {
            N = N + 3;
            M = M + 3;
        }
        else if ((dif == 'M') || (dif == 'm'))
        {
            N = N + 2;
            M = M + 2;
        }
        else if ((dif == 'H') || (dif == 'h'))
        {
            N = N + 1;
            M = M + 1;
        }

    } while ((N * M) <= maxD);

    printf("\nCONGRATULATIONS!!!\n");
    printf("\nYOU WIN!!!");
    printf("\nDiamonds collected: %d\n\n", val_diam);

    return 0;
}

int path(char **table, int N, int M, int x, int y, char com, int steps, int diamonds, int *cntD, int *sumD, int *vald, int *cntm)
{
    char temp, j;
    int i, falls = 0, dn = 0, a = x, b = y; // a,b=dig doug

    if (steps > 0)
    {

        if ((x < 0) || (x >= N) || (y < 0) || (y >= M))
        {
            printf("\nMAP LIMITS REACHED! Dig Doug moved only %d blocks!\n", *cntm);
            return 0;
        }

        if (table[x][y] == ' ')
            return 1;

        if (table[x][y] == '.')
            return 1;

        if (table[x][y] == '#')
        {
            printf("\nOBSTACLE IN THE WAY! Dig Doug moved only %d blocks!\n", *cntm);
            return 0;
        }

        for (i = 0; i < 10; i++)
        {
            j = i + '0';
            if (table[x][y] == j)
            {
                printf("\nYou pick up a diamond with value = %c\n", j);
                *sumD += i;
                *vald += i;
                *cntD += 1;
                return 1;
            }
        }

        if ((com == 'U') || (com == 'u'))
        {
            if ((path(table, N, M, x - 1, y, com, steps, diamonds, cntD, sumD, vald, cntm) == 1))
            {
                *cntm += 1;
                temp = table[x][y];
                table[x][y] = table[x - 1][y];
                table[x - 1][y] = temp;
                table[x][y] = ' ';
                // thesi Dig Doug
                a = x - 1;
                b = y;
                return path(table, N, M, x - 1, y, com, steps - 1, diamonds, cntD, sumD, vald, cntm);
            }
        }

        else if ((com == 'D') || (com == 'd'))
        {
            if ((path(table, N, M, x + 1, y, com, steps, diamonds, cntD, sumD, vald, cntm) == 1))
            {
                *cntm += 1;
                temp = table[x][y];
                table[x][y] = table[x + 1][y];
                table[x + 1][y] = temp;
                table[x][y] = ' ';
                // thesi Dig Doug
                a = x + 1;
                b = y;

                return path(table, N, M, x + 1, y, com, steps - 1, diamonds, cntD, sumD, vald, cntm);
            }
        }

        else if ((com == 'R') || (com == 'r'))
        {
            if ((path(table, N, M, x, y + 1, com, steps, diamonds, cntD, sumD, vald, cntm) == 1))
            {
                *cntm += 1;
                temp = table[x][y];
                table[x][y] = table[x][y + 1];
                table[x][y + 1] = temp; // Dig Doug
                table[x][y] = ' ';
                // thesi Dig Doug
                a = x;
                b = y + 1;

                if ((a + 1 < N) && (b < M))
                {
                    dn = down(table, N, M, a, b, vald);
                    if ((table[a + 1][b] == ' ') && (path(table, N, M, a, b, 'd', dn, diamonds, cntD, sumD, vald, cntm) == 1))
                    {
                        if (dn >= 3)
                        {
                            print_table(table, N, M);
                            printf("\nDig Doug fell and broke his leg!");
                            printf("\nGAME OVER!");
                            printf("\nDiamonds collected: %d\n\n", *vald);
                            exit(0);
                        }

                        return path(table, N, M, a + 1, b, 'D', dn, diamonds, cntD, sumD, vald, cntm);
                    }

                    if (dn >= 3)
                    {
                        print_table(table, N, M);
                        printf("\nDig Doug fell and broke his leg");
                        printf("\nGAME OVER!");
                        printf("\nDiamonds collected: %d\n\n", *vald);
                        exit(0);
                    }
                }

                return path(table, N, M, x, y + 1, com, steps - 1, diamonds, cntD, sumD, vald, cntm);
            }
        }
        else if ((com == 'L') || (com == 'l'))
        {
            if ((path(table, N, M, x, y - 1, com, steps, diamonds, cntD, sumD, vald, cntm) == 1))
            {
                *cntm += 1;
                temp = table[x][y];
                table[x][y] = table[x][y - 1];
                table[x][y - 1] = temp; // Dig doug
                table[x][y] = ' ';
                // thesi Dig Doug
                a = x;
                b = y - 1;

                if ((a < N - 1) && (b < M))
                {
                    dn = down(table, N, M, a, b, vald);
                    if ((table[x + 1][b] == ' ') && (path(table, N, M, a, b, 'd', dn, diamonds, cntD, sumD, vald, cntm) == 1))
                    {
                        if (dn >= 3)
                        {
                            print_table(table, N, M);
                            printf("\nDig Doug fell and broke his leg");
                            printf("\nGAME OVER!");
                            printf("\nDiamonds collected: %d\n\n", *vald);
                            exit(0);
                        }
                        return path(table, N, M, a + 1, b, 'D', dn, diamonds, cntD, sumD, vald, cntm);
                    }

                    if (dn >= 3)
                    {
                        print_table(table, N, M);
                        printf("\nDig Doug fell and broke his leg");
                        printf("\nGAME OVER!");
                        printf("\nDiamonds collected: %d\n\n", *vald);
                        exit(0);
                    }
                }

                return path(table, N, M, x, y - 1, com, steps - 1, diamonds, cntD, sumD, vald, cntm);
            }
        }
    }
}

void print_table(char **table, int N, int M)
{
    int i, j, k;

    printf("\n    "); // 4spc
    for (j = 0; j < M; j++)
    {
        if (j <= 8)
            printf("%d ", j + 1);
        else
            printf("%d", j + 1);
    }
    printf("\n");
    for (k = 0; k < M * 2 + 3; k++)
    {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < N; i++)
    {
        if (i <= 8)
            printf("%d | ", i + 1);
        else
            printf("%d| ", i + 1);

        for (j = 0; j < M; j++)
        {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }

    return;
}

char **soil(char **arr, int N, int M)
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            arr[i][j] = '.';
        }

    return arr;
}

char **obs_table(char **table, int N, int M, double percentage_obs)
{
    char **arr;
    int x, y, i, j, o, flag = 0;

    arr = getMemory(arr, N, M);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            arr[i][j] = '#';
        }
    }
    o = N * M * percentage_obs;

    for (i = 0; i < o; i++)
    {
        flag = 0;
        while (flag == 0)
        {
            x = Random(N);
            y = Random(M);
            if (table[x][y] == '.')
            {
                table[x][y] = arr[x][y];
                flag = 1;
            }
        }
    }

    for (i = 0; i < N; i++)
    {
        free(arr[i]);
    }

    free(arr);
    return table;
}

int Dig_Doug(char **table, int M)
{
    int j, flag = 0;

    j = Random(M);
    while (flag == 0)
    {
        if (table[0][j] == '.')
        {
            table[0][j] = '$';
            flag = 1;
        }
    }
    return j;
}

char **diam(char **table, int N, int M, int diamonds)
{
    char **arr;
    int x, y, i, j, flag = 0;
    char g;

    arr = getMemory(arr, N, M);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            g = 48 + rand() % 10;
            arr[i][j] = g;
        }
    }

    for (i = 0; i < diamonds; i++)
    {
        flag = 0;
        while (flag == 0)
        {
            x = Random(N);
            y = Random(M);
            if (table[x][y] == '.')
            {
                table[x][y] = arr[x][y];
                flag = 1;
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        free(arr[i]);
    }

    free(arr);
    return table;
}

int Random(int num)
{
    double d;
    int k;
    d = (double)rand() / ((double)RAND_MAX + 1);
    d = (d * num);
    k = (int)d;

    return k;
}

char **getMemory(char **array, int N, int M)
{
    int i;

    array = (char **)malloc(N * sizeof(char *));

    if (array == NULL)
    {
        printf("ERROR: Not Available Memory\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < N; i++)
    {
        array[i] = (char *)malloc(M * sizeof(char));
        if (array[i] == NULL)
        {
            printf("ERROR: Not Available Memory\n");
            exit(EXIT_FAILURE);
        }
    }
    return array;
}

int found_x(char **array, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (array[i][j] == '$')
                return i;
        }
    }
}

int found_y(char **array, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (array[i][j] == '$')
                return j;
        }
    }
}

int down(char **table, int N, int M, int x, int y, int *vald)
{
    int i, j, cnt = 0;

    x = found_x(table, N, M);
    y = found_y(table, N, M);
    while (x < N - 1)
    {
        if (table[x + 1][y] == ' ')
        {
            cnt += 1;
        }
        x += 1;
    }

    if ((cnt == 1) || (cnt == 2))
        printf("\nDig Doug fell but it's ok!\n");

    return cnt;
}

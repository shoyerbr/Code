#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int main (int argc, char* argv[])
{
    FILE *F;
    if (argc == 3)
    {
        F = fopen(argv[1], "r");
        if (F != NULL)
        {
            char **words = calloc(20, sizeof(char *));
            if (words == NULL)
                exit(0);
            int two_d = 0;
            char temp[16];
            printf("Allocated initial array of 16 character pointers.\n");
            char *pre= argv[2];
            int number = 16;
            //read in file
            while ( fscanf(F, "%s", temp) != EOF)
            {
                words[two_d] = (char *)malloc((strlen(temp)+1) * sizeof(char *));
                if (words[two_d] == NULL)
                    exit(0);
                strcpy(words[two_d], temp);
                two_d++;
                //make sure we dont run out of space
                if (two_d == number + 1)
                {
                    number = number*2;
                    words = (char **) realloc(words, number*sizeof(char *));
                    printf("Re-allocated array of %d character pointers.\n", number);
                }
            }
            int i;
            //step thorugh all the words
            printf("All done (successfully read %d words).\n", two_d);
            printf("Words containing substring \"%s\" are:\n", pre);
            for (i = 0; i < two_d; i++)
            {
                // the prefix has to be smaller for same size as word
                 if (strlen(pre) <= strlen(words[i]))
                {
                    int j;
                    int l;
                    //printf("%d\n", tempp);
                    int count = 0;
                    //step through the prefix and the first part of the word to see if they are the same
                    for (l = 0; l <= strlen(words[i]); l++)
                    {
                        count = 0;
                        if (words[i][l] == pre[0])
                        {
                            //printf("%s\n",words[i]);
                            for (j = 0; j < strlen(pre); j++)
                            {
                                if (words[i][j+l] == pre[j])
                                {
                                    count++;
                                }
                            }
                        }
                        if (count == strlen(pre))
                            printf("%s\n",words[i]);
                    }
                }
            }
            free(words);
        }
    }
    else
        fputs("Error wrong number of arguments\n",stderr);
    return 0;
}
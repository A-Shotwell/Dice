/* This header file handles the roll functions and influencing variables (items) attained throughout the narrative. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void PRESS_KEY(char a); // Press specified key to continue or roll
int AMULET_SAVE(int save_amulet, int player, int persevere, int enemy, char rollType); // Prompt another roll of the last roll condition while AMULET item is active. Amulet becomes inactive after use.
int ROLL(char conflict, int save, bool a, bool b, bool c); // Prompt user to roll (Press ENTER), and roll either a save (int SAVE) or against an enemy counter-roll.

bool SHIELD = false; // Possession of family shield item
bool SWORD = false; // Possession of legendary sword item
bool AMULET = false; // Possession of revival amulet item, single use

void PRESS_KEY(char a) // PRESS ENTER TO CONTINUE (ERROR: "PARAMETER "SHIELD" IS INITIALIZED" SINCE I ADDED THIS TO ROLL.H)
{
    Sleep(1000); // Wait 2 seconds before prompt
    char input; // store player's input

    do // Prompt for character entry while character entered does not match corresponding call
    {
        printf("\n\t\t\tTYPE \"%c\" TO ", a);

        if (a == 'C') // If char a is 'C', signifying "continue", set to print "PRESS 'C' TO CONTINUE"
        {
            printf("CONTINUE: ");
        }
        else if (a == 'R') // If char a is 'R', signifying "roll", set to print "PRESS 'R' TO ROLL"
        {
            printf("ROLL: ");
        }

        scanf(" %c", &input);

        if(islower(input))
            input = toupper(input);
    }while(input != a);

    return;
}

int AMULET_SAVE(int SAVE, int player, int persevere, int enemy, char rollType)
{
    printf("You failed! But, as the merchant promised, the amulet restores you to life! \nThe amulet turns to dust. \
Roll to save! (D20)\n\n");
    AMULET = false;
    PRESS_KEY('R');
    srand(time(0));

    switch (rollType)
    {
        case 'A' :  player = rand() % 20;

                    if (player == 0)
                    player++;

                    if(SHIELD)
                    {
                        printf("You raise your family shield! (+5 to roll)\n\n");
                        player += 5;
                    }

                    if(SWORD)
                    {
                        printf("The light of destiny gleams from the hero's blade! (+5 to roll)\n\n");
                        player += 5;
                    }

                    printf("You rolled: %d\n", player);
                    printf("Enemy rolled: %d\n\n", enemy);

                    if (player == enemy)
                    {
                        do
                        {
                            printf("An even clash! Roll to save! (D20)\n\n");

                            PRESS_KEY('R');
                            player = rand() % 20;
                            enemy = 15 + (rand() % 5);

                            if (player == 0)
                                player++;

                            printf("You rolled: %d\nEnemy rolled: %d\n\n", player, enemy);
                        } while (player == enemy);
                    }

                    if (player > enemy)
                    {
                        printf("Success!\n");
                        PRESS_KEY('C');
                        return 1;
                    }
                    else if (enemy - player <= 6)
                    {
                        printf("You are in mortal peril! Roll to save! (D6)\n");

                        persevere = rand() % 6;

                        if (persevere == 0)
                            persevere++;

                        if (player + persevere == enemy)
                            persevere++;

                        PRESS_KEY('R');
                        printf("\nYou rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                        if(player + persevere > enemy)
                        {
                            printf("Success!\n");
                            PRESS_KEY('C');
                            return 1;
                        }
                    }

                    printf("You failed!\n");
                    PRESS_KEY('C');
                    return 0;

        case 'B' :  persevere = rand() % 6;

                    if (persevere == 0)
                        persevere++;

                    printf("You summon your strength! You rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                    if ((player + persevere) == enemy)
                    {
                        do
                        {
                            printf("An even clash! Roll to save! (D6)\n");
                            PRESS_KEY('R');
                            persevere = rand() % 6;

                            if (persevere == 0)
                                persevere++;

                            printf("You summon your strength! You rolled: %d +%d = %d\n\n", player, persevere, player + persevere);
                        } while (((player + persevere) == enemy));
                    }

                    if ((player + persevere) >= enemy)
                    {
                        printf("Success!\n");
                        PRESS_KEY('C');
                        return 1;
                    }

                    printf("You failed!\n");
                    PRESS_KEY('C');
                    return 0;

        case 'C' :  player = rand() % 20;

                    if(player == 0)
                    {
                        player++;
                    }

                    printf("You rolled: %d\n\n", player);
                    if (player >= SAVE)
                    {
                        printf("Success!\n");
                        PRESS_KEY('C');
                        return 1;
                    }
                    if (player < SAVE)
                    {
                        if (player >= (SAVE - 6))
                        {
                            printf("You are in mortal peril! Roll to save!\n\n");
                            PRESS_KEY('R');
                            persevere = rand() % 6;

                            if (persevere == 0)
                                persevere++;

                            printf("\nYou rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                            if (player + persevere >= SAVE)
                            {
                                printf("Success!\n");
                                PRESS_KEY('C');
                                return 1;
                            }
                        }

                        printf("You failed!\n");
                        PRESS_KEY('C');
                        return 0;
                    }
    }
}

int ROLL(char conflict, int SAVE, bool a, bool b, bool c)
{
    srand(time(0));
    int player, persevere, enemy;
    int save_amulet = SAVE;

    printf("\n\n***************************************************************************************\n");

    switch (conflict)
    {
        // Non-adversarial rolls
        case 'A' :  printf("Roll %d or higher to save.\n\n", SAVE);
                    PRESS_KEY('R');
                    player = rand() % 20;

                    if(player == 0)
                    {
                        player++;
                    }

                    printf("You rolled: %d\n\n", player);
                    if (player >= SAVE)
                    {
                        printf("Success!\n");
                        PRESS_KEY('C');
                        printf("\n");
                        return 1;
                    }
                    if (player < SAVE)
                    {
                        if (player >= (SAVE - 6))
                        {
                            printf("You are in mortal peril! Roll to save! (D6)\n\n");
                            PRESS_KEY('R');
                            persevere = rand() % 6;

                            if (persevere == 0)
                                persevere++;

                            printf("\nYou rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                            if (player + persevere >= SAVE)
                            {
                                printf("Success!\n");
                                PRESS_KEY('C');
                                printf("\n");
                                return 1;
                            }

                            if(AMULET)
                            {
                                if(AMULET_SAVE(save_amulet, player, persevere, enemy, 'C'))
                                {
                                    printf("\n");
                                    return 1;
                                }

                                printf("\n");
                                return 0;
                            }

                            printf("You failed!\n");
                            PRESS_KEY('C');
                            printf("\n");
                            return 0;
                        }

                        if(AMULET)
                        {
                            if(AMULET_SAVE(save_amulet, player, persevere, enemy, 'C'))
                            {
                                printf("\n");
                                return 1;
                            }

                            printf("\n");
                            return 0;
                        }

                        printf("You failed!\n");
                        PRESS_KEY('C');
                        printf("\n");
                        return 0;
                    }

        case 'B' :  printf("The enemy is attacking!\n");
                    PRESS_KEY('R'); // Press ENTER to roll, reject all other input
                    player = rand() % 20;

                    if(player == 0)
                    {
                        player++;
                    }

                    if(SHIELD)
                    {
                        printf("\nYou raise your family shield! (+5 to roll)\n");
                        player += 5;
                    }

                    if(SWORD)
                    {
                        printf("\nThe light of destiny gleams from the hero's blade! (+5 to roll)\n");
                        player += 5;
                    }

                    printf("\nYou rolled: %d\n", player);
                    enemy = 15 + (rand() % 5);

                    printf("Enemy rolled: %d\n\n", enemy);

                    if (player > enemy)
                    {
                        printf("Success!\n");
                        PRESS_KEY('C');
                        printf("\n");
                        return 1;
                    }
                    else if (player == enemy)
                    {
                        do
                        {
                            printf("An even clash! Roll to save! (D20)\n\n");
                            PRESS_KEY('R');
                            player = rand() % 20;
                            enemy = 15 + (rand() % 5);

                            if (player == 0)
                                player++;

                            printf("You rolled: %d\nEnemy rolled: %d\n\n", player, enemy);
                        } while (player == enemy);

                        if (player > enemy)
                        {
                            printf("Success!\n");
                            PRESS_KEY('C');
                            printf("\n");
                            return 1;
                        }
                        else if (enemy - player <=5)
                        {
                            printf("You are in mortal peril! Roll to save! (D6)\n");

                        persevere = rand() % 6;

                        if (persevere == 0)
                            persevere++;

                        if (player + persevere == enemy)
                            persevere++;

                        PRESS_KEY('R');
                        printf("\nYou rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                        if(player + persevere > enemy)
                        {
                            printf("Success!\n");
                            PRESS_KEY('C');
                            printf("\n");
                            return 1;
                        }
                        }

                        if(AMULET)
                        {
                            if(AMULET_SAVE(save_amulet, player, persevere, enemy, 'A'))
                            {
                                printf("\n");
                                return 1;
                            }

                            printf("\n");
                            return 0;
                        }

                        printf("You failed!\n");
                        PRESS_KEY('C');
                        printf("\n");
                        return 0;
                    }
                    else if (enemy - player <= 6) // REWRITE PER PROBLEMS MEMO
                    {
                        printf("You are in mortal peril! Roll to save! (D6)\n");

                        persevere = rand() % 6;

                        if (persevere == 0)
                            persevere++;

                        if (player + persevere == enemy)
                            persevere++;

                        PRESS_KEY('R');
                        printf("\nYou rolled: %d +%d = %d\n\n", player, persevere, player + persevere);

                        if(player + persevere > enemy)
                        {
                            printf("Success!\n");
                            PRESS_KEY('C');
                            printf("\n");
                            return 1;
                        }

                        if(AMULET)
                        {
                            if(AMULET_SAVE(save_amulet, player, persevere, enemy, 'B'))
                            {
                                printf("\n");
                                return 1;
                            }

                            printf("\n");
                            return 0;
                        }

                        printf("You failed!\n");
                        PRESS_KEY('C');
                        printf("\n");
                        return 0;
                    }

                    if(AMULET)
                    {
                        if(AMULET_SAVE(save_amulet, player, persevere, enemy, 'A'))
                        {
                            printf("\n");
                            return 1;
                        }

                        printf("\n");
                        return 0;
                    }

                    printf("You failed!\n");
                    PRESS_KEY('C');
                    printf("\n");
                    return 0;
    }
}

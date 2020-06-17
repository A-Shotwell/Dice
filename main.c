#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "scenario.h"; // Scenario text and presentation functions
#include "roll.h"; // Dice roll functions

char REPLAY(void); // Replay prompt

int SAVE = 0; // Current save roll minimum. If roll type is 'B', this variable should be set to 0.

int VALOR = 0; // Track player's brave/selfless action. Valor of 3+ required to claim hero's sword.

int main()
{
    do
    {
        INTRO();

        char Aud_Cham = SCENARIO('A', audience); // Opening scenario, Audience Chamber

        if (Aud_Cham == 'F') // If player chooses FIGHT n the Audience Chamber
        {
            printf("%s", audience_FIGHT); // Print FIGHT selection text
            PRESS_KEY('C'); // Press C to continue

            char GH = SCENARIO('A', great_hall); // Print Grand Hall scenario

            if (GH == 'F') // If player chooses to fight in the Grand Hall...
            {
                switch (ROLL('B', 0, SHIELD, SWORD, AMULET)) // FIGHT FIREBRAND
                {
                    case 1   :   printf("%s", great_hall_FIGHT_S); // If player wins roll, print success text

                                    PLAY = REPLAY(); // Prompt replay

                                    if (PLAY == 'Y')
                                    {
                                        continue;
                                    }
                                    else if (PLAY == 'N')
                                    {
                                        return 0;
                                    }

                    case 0  :   printf("%s", great_hall_FIGHT_F); // If player loses roll, print fail text

                                    PLAY = REPLAY(); // Prompt to replay

                                    if (PLAY == 'Y')
                                    {
                                        continue;
                                    }
                                    else if (PLAY == 'N')
                                    {
                                        return 0;
                                    }
                }
            }
            else if (GH == 'R') // If player chooses to run from the Great Hall...
            {
                char GH_R = SCENARIO('B', great_hall_RUN); // Print run from Grand Hall scenario

                if (GH_R == 'R') // If player chooses to abandon the woman in the Great Hall and run
                {
                    switch(ROLL('A', 7, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                    {
                        case 1   :   printf("%s", great_hall_run_S); // Print Great Hall abandon success text
                                        PRESS_KEY('C'); // Type 'C' to continue
                                        break;

                        case 0  :   printf("%s", great_hall_run_F); // Print Great Hall abandon fail text

                                    PLAY = REPLAY(); // Prompt to replay

                                    if (PLAY == 'Y')
                                    {
                                        continue;
                                    }
                                    else if (PLAY == 'N')
                                    {
                                        return 0;
                                    }
                    }
                }
                else if (GH_R == 'S') // If player chooses to save the woman
                {
                    switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                    {
                        case 1   :   printf("%s", great_hall_save_S); // If success, print save success text
                                        PRESS_KEY('C'); // Press 'C' to continue
                                        VALOR++; // Increase valor for brave action
                                        break;

                        case 0  :   printf("%s", great_hall_save_F); // If fail, print save fail text

                                        PLAY = REPLAY(); // Prompt to replay

                                        if (PLAY == 'Y')
                                        {
                                            continue;
                                        }
                                        else if (PLAY == 'N')
                                        {
                                            return 0;
                                        }
                    }
                }

                char corr = SCENARIO('B', corridor); // print Grand Corridor scenario

                if (corr == 'R') // If player chooses to run and abandon merchant in Grand Corridor...
                {
                    switch(ROLL('A', 7, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                    {
                        case 1  :  printf("%s", corridor_run_S); // print run success text
                                   PRESS_KEY('C'); // Press 'C' to continue
                                   break;

                        case 0  :  printf("%s", corridor_run_F); // print run fail text, GAME OVER

                                   PLAY = REPLAY(); // Prompt to replay

                                   if (PLAY == 'Y')
                                   {
                                       continue;
                                   }
                                   else if (PLAY == 'N')
                                   {
                                       return 0;
                                   }
                    }
                }
                else if (corr == 'S') // If player chooses to save merchant in Grand Corridor...
                {
                    switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                    {
                        case 1  :  printf("%s", corridor_save_S); // print save success text
                                   AMULET = true; // Get Holy Amulet
                                   VALOR++; // Valor up for rescue
                                   PRESS_KEY('C'); // Press 'C' to continue

                                   printf("%s", armory); // print Royal Armory scenario
                                   PRESS_KEY('C'); // Press 'C' to continue

                                   switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                                   {
                                        case 1  :  printf("%s", armory_success); // Print success text
                                                   SHIELD = true; // Get Family Shield
                                                   PRESS_KEY('C'); // Press 'C' to continue
                                                   break;

                                        case 0  :  printf("%s", armory_fail); // Print fail text, GAME OVER

                                                   PLAY = REPLAY(); // Prompt to replay

                                                   if (PLAY == 'Y')
                                                   {
                                                       continue;
                                                   }
                                                   else if (PLAY == 'N')
                                                   {
                                                       return 0;
                                                   }
                                   }

                                   break;

                        case 0  :  printf("%s", corridor_save_F); // print save fail text, GAME OVER

                                   PLAY = REPLAY(); // Prompt to replay

                                   if (PLAY == 'Y')
                                   {
                                       continue;
                                   }
                                   else if (PLAY == 'N')
                                   {
                                       return 0;
                                   }
                    }
                }
            }

            char court = SCENARIO('A', bailey); // Print bailey scenario text. Choice: FIGHT or RUN?

            if (court == 'F')
            {
                switch (ROLL('B', 0, SHIELD, SWORD, AMULET))
                {
                    case 1  :  printf("%s", bailey_fight_S); // print bailey fight success text, YOU WIN!

                               PLAY = REPLAY(); // Prompt for replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }

                    case 0  :  printf("%s", bailey_fight_F); // print bailey fight fail text, GAME OVER

                               PLAY = REPLAY(); // Prompt for replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }
                }
            }
            else if (court == 'R')
            {
                char court_run = SCENARIO('B', bailey_run); // Print bailey run text. Choice: RUN or SAVE the crowd?

                if (court_run == 'R')
                {
                    switch(ROLL('A', 7, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                    {
                        case 1  :  printf("%s", bailey_run_S); // Print bailey run success text
                                   PRESS_KEY('C'); // Press "C" to continue
                                   break;

                        case 0  :  printf("%s", bailey_run_F); // Print bailey run fail text, GAME OVER

                                   PLAY = REPLAY(); // Prompt for replay

                                   if (PLAY == 'Y')
                                   {
                                       continue;
                                   }
                                   else if (PLAY == 'N')
                                   {
                                       return 0;
                                   }
                    }
                }
                else if (court_run == 'S')
                {
                    switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                    {
                        case 1  :  printf("%s", bailey_save_S); // Print bailey save success text
                                   VALOR++; // Valor up for save
                                   PRESS_KEY('C'); // Press 'C' to continue
                                   break;

                        case 0  :  printf("%s", bailey_save_F); // Print bailey save fail text, GAME OVER

                                   PLAY = REPLAY(); // Prompt for replay

                                   if (PLAY == 'Y')
                                   {
                                       continue;
                                   }
                                   else if (PLAY == 'N')
                                   {
                                       return 0;
                                   }
                    }
                }
            }

            char mark = SCENARIO('B', market); // Print Market scenario text, choice RUN or SAVE

            if (mark == 'R') // If player chooses to run from the market and abandon the man held at knife point...
            {
                switch(ROLL('A', 7, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                {
                    case 1  :  printf("%s", market_run_S); // Print market run success text
                               PRESS_KEY('C'); // Press 'C' to continue
                               break;

                    case 0  :  printf("%s", market_run_F); // Print market run fail text, GAME OVER

                               PLAY = REPLAY(); // Prompt for replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }
                }
            }
            else if (mark == 'S') // If player chooses to save the man held at knife point...
            {
                switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                {
                    case 1  :  printf("%s", market_save_S); // Print market save success text
                               VALOR++; // Valor up for save
                               PRESS_KEY('C'); // Press 'C' to continue
                               break;

                    case 0  :  printf("%s", market_save_F); // Print market save fail text

                               PLAY = REPLAY(); // Prompt for replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }
                }
            }

            char twn = SCENARIO('B', town); // Print Town scenario text

            if (twn == 'R')
            {
                printf("%s", town_run); // Print town run text
                PRESS_KEY('C'); // Press 'C' to continue
            }
            else if (twn == 'S')
            {
                switch (ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                {
                    case 1  :  printf("%s", town_save_S); // Print town save success text
                               VALOR++; // Valor up for save
                               PRESS_KEY('C'); // Press 'C' to continue
                               break;

                    case 0  :  printf("%s", town_save_F); // Print town save fail text, GAME OVER

                               PLAY = REPLAY();

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }
                }
            }

            if (VALOR >= 3)
            {
                printf("%s", cathedral_worthy); // Print cathedral text, player is worthy
                SWORD = true; // Get Hero's Sword
                PRESS_KEY('C'); // Press 'C' to continue
            }
            else if (VALOR < 3)
            {
                printf("%s", cathedral_unworthy); // Print cathedral text, player is not worthy
                PRESS_KEY('C'); // Press 'C' to continue
            }
        }
        else if (Aud_Cham == 'R') // If player chooses RUN from the Audience Chamber
        {
            printf("%s", audience_RUN); // Print RUN selection text
            PRESS_KEY('C'); // Press 'C' to continue

            printf("%s", hidden_passage); // print Hidden Passage scenario
            PRESS_KEY('C'); // Press 'C' to continue
            switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 7+
            {
                case 1  :  break; // If successful, continue to the cathedral

                case 0  :  printf("%s", hidden_passage_FAIL); // If fail, print fail text, GAME OVER

                           PLAY = REPLAY(); // Prompt to replay

                           if (PLAY == 'Y')
                           {
                                continue;
                           }
                                else if (PLAY == 'N')
                           {
                                return 0;
                           }
            }

            printf("%s", cathedral_hidden_passage); // Print cathedral (from Hidden Passage) text, unworthy of sword
            PRESS_KEY('C'); // Press 'C' to continue
        }

            printf("%s", showdown_intro); // Print final showdown intro text

            if (AMULET) // If the player acquired the Holy Amulet and still has it, mention the amulet
                printf("%s", showdown_AMULET);

            if (SHIELD) // If the player acquired the Family Shield, mention the shield
                printf("%s", showdown_SHIELD);

            if (SWORD) // If the player has acquired the Hero's Sword, mention the sword
                printf("%s", showdown_SWORD);

            PRESS_KEY('C'); // Press 'C' t continue

            char showdown = SCENARIO('A', showdown_choice); // Final showdown. Fight in residential district, or run for the field?

            if (showdown == 'F') // If player chooses to fight Firebrand in the residential district at the final showdown...
            {
                switch(ROLL('B', 0, SHIELD, SWORD, AMULET)) // FIGHT Firebrand
                {
                    case 1  :   printf("%s", showdown_fight_S); // If success, print fight success text. YOU WIN!

                                PLAY = REPLAY(); // Prompt to replay

                                if (PLAY == 'Y')
                                {
                                    continue;
                                }
                                else if (PLAY == 'N')
                                {
                                    return 0;
                                }

                    case 0  :   printf("%s", showdown_fight_F); // If fail, print save fail text. GAME OVER.

                                PLAY = REPLAY(); // Prompt to replay

                                if (PLAY == 'Y')
                                {
                                    continue;
                                }
                                else if (PLAY == 'N')
                                {
                                    return 0;
                                }
                    }
            }
            else if (showdown == 'R') // If player chooses to run to the field at the final showdown...
            {
                switch(ROLL('A', 7, SHIELD, SWORD, AMULET)) // Roll to save, 7+
                {
                    case 1  :  printf("%s", showdown_run_S); // Print run success text
                               PRESS_KEY('C'); // Press 'C' to continue
                               break;

                    case 0  :  printf("%s", showdown_run_F); // Print run fail text, GAME OVER

                                PLAY = REPLAY();

                                if (PLAY == 'Y')
                                {
                                    continue;
                                }
                                else if (PLAY == 'N')
                                {
                                    return 0;
                                }
                }
            }

            char field_shdwn = SCENARIO('A', field); // present FIGHT or RUN at field, final showdown

            if (field_shdwn == 'F') // If the player chooses to fight FIREBRAND in the field...
            {
                switch(ROLL('B', 0, SHIELD, SWORD, AMULET)) // FIGHT Firebrand
                {
                    case 1  :  printf("%s", field_fight_S); // Print fight success text, YOU WIN!

                               PLAY = REPLAY(); // Prompt to replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }

                    case 0  :  printf("%s", field_fight_F); // Print fight fail text, GAME OVER

                               PLAY = REPLAY(); // Prompt to replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   while (getchar() != '/n');
                                   return 0;
                               }
                }
            }
            else if (field_shdwn == 'R') // If the player chooses to run in the field...
            {
                switch(ROLL('A', 10, SHIELD, SWORD, AMULET)) // Roll to save, 10+
                {
                    case 1  :  printf("%s", field_run_S); // Print run success text, GAME OVER

                               PLAY = REPLAY(); // Prompt to replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }

                    case 0  :  printf("%s", field_run_F); // Print run fail text, GAME OVER

                               PLAY = REPLAY(); // Prompt to replay

                               if (PLAY == 'Y')
                               {
                                   continue;
                               }
                               else if (PLAY == 'N')
                               {
                                   return 0;
                               }
                }
        } // HIDDEN PASSAGE RUN ENDS HERE
    }while (PLAY == 'Y'); // Prompt for replay choice

    return 0;
}

char REPLAY(void) // Prompt for replay choice
{
    printf("\n\nPLAY AGAIN? (Y/N): ");

    char play_Again;

    do
    {
        scanf(" %c", &play_Again);

        if(islower(play_Again))
            play_Again = toupper(play_Again);
    }while(play_Again != 'Y' && play_Again != 'N');

    if(play_Again == 'N')
    {
        printf("\n***************************************************************************************\n\n\
THANK YOU FOR PLAYING!");
        Sleep(1000); // Wait 2 seconds before prompt

        char ext;

        do
        {
            printf("\n\nTYPE 'X' TO EXIT: ");
            scanf(" %c", &ext);
            ext = toupper(ext);
        }while (ext != 'X');

        return 'N';
    }

    if(play_Again == 'Y');
        SHIELD = false;
        SWORD = false;
        AMULET = false;
        return 'Y';
}

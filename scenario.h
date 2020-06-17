/* This is the repository for dialogue and narrative strings. I understand that this is not how style strings for
collaborator readability, but I'm currently struggling with understanding escape sequences. Once I have a proper
understanding, I will correct this unreadable mess. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void INTRO(void); // Tile banner and introduction
char SCENARIO(char type, char* scen); // Audience Chamber scenario

char YES_NO; // YES or NO decision
char PLAY; // Replay trigger

// Start of the game, king's audience chamber. Choose to face the dragon, or flee via the hidden passage.
char *audience = ("\n***************************************************************************************\n\nYou can hear \
the sounds of chaos beyond the walls of your audience chamber. The\ncaptain of the royal guard enters, panicked and out of \
breath.\n\n\"Your Majesty, Firebrand has returned! He is attacking the castle! Prince Viktor is\nnowhere to be found... I fear \
he is lost. But your life may yet be spared, my liege!\"\n\nThe captain pulls a candelabra on the wall behind your throne. A \
section of the wall\nslides away to reveal a hidden doorway.\n\n\"This passage leads directly to the cathedral in the town \
residential district. From\nthere, the bishop will usher you to safety. Make haste, my liege! Fear not for your\nsubjects or \
your kingdom. We, your loyal soldiers, shall defend them with our lives!\"\n\nYou've known of this passage for some time. The \
cathedral stands above the Chosen's\nTemple, which enshrines the hero's legendary sword. It would grant you an advantage in\nthis \
fight. But your subjects just outside these walls are in need of help, your son\namong them.\n\n\Will you stand and FIGHT for \
your people? Or will you RUN for the cathedral?\n\n---------------------------------------------------------\n");

// Audience chamber conversation, choose to fight. VALOR++
char *audience_FIGHT = ("\n***************************************************************************************\n\nYou thank \
the captain for his loyalty, but you remind him that Firebrand is the sworn \nenemy of your bloodline. You remind him that your \
family has ruled these lands so that \nthey might defend them from the terrible dragon's return. This fight is your destiny, \n\
and defending this kingdom is your charge.\n\n\"My lord, I... I understand. Then I will see to the evacuation. My men will do \
their \nbest to slow the beast's advance. You should make for the cathedral all the same. The \nsword of destiny awaits you there. \
I bid you good fortune. May your blade find the \nmonster's heart!\"\n");

// Audience chamber conversation, choose to flee via the hidden passage. (TO hidden_passage)
char *audience_RUN = ("\n***************************************************************************************\n\nYou thank \
the captain for his loyalty and bravery. You wish him good fortune in battle\nas he ushers you into the hidden passage, but \
you insist that you make the trip alone.\nYou urge him to fight with the spirit of the hero in his heart. It is your destiny \
to\nfell the beast, but you must live until you are properly armed for the fight.\n\nThe captain salutes you one last time as \
he pulls the candelabra, sealing the entrance.\nHis voice calls faintly from beyond the stone wall...\n");

// Hidden passage. The dragon is raging outside, and the passage begins to collapse. (TO cathedral_1)
char* hidden_passage = "\n***************************************************************************************\n\n\"Godspeed, \
my king!\"\n\nThe stone wall slams closed behind you.\n\nYou can hear the captain's voice growing fainter as he rushes the Great \
Hall and\nrallies his men to the fight. You are left alone with miles of dark, narrow tunnel\nbetween you and sanctuary.\n\n\
Above you rage the same sounds of destruction and mayhem. Ferocious bangs and\nfrustrated roars among a sea of screams and \
cries for help. It would appear that\nthe beast knows your location, because they're growing closer by the second.\n\nSuddenly, \
the passage quakes violently! Dust and rocks rain down from the low\nceiling! The walls begin cracking and crunching! The \
passage is collapsing around\nyou, but you can see an increasingly brighter light in the near-distance!\n\n\Run for your \
life!\n";

// Hidden passage. Failure to make it out of the collapsing passage alive. GAME OVER. Play again prompt.
char* hidden_passage_FAIL = "\n***************************************************************************************\n\nAs you \
sprint for the exit, you trip on a fallen piece of debris. Before you can get\nto your feet, a large slab breaks free of the \
ceiling and crushes your legs. You can\nsee the silhouette of the priest beckoning you, but his calls are drown out by the\n\
raucus clatter of colliding stones.\n\nWith an outstretched hand and a cry of horror, you watch as the ruins of the passage\n\
swallow the light and seal your fate. This tunnel has become your tomb. Above, Firebrand\nis stamping out your kingdom and your \
legacy. The hero's legend, and his bloodline,\nwill die with you beneath the rubble.\n\n\
---------------------------------------------------------\nGAME OVER";

// Great Hall. Nobles and merchants are in a panic. Dragon arrives.
char* great_hall = "\n***************************************************************************************\n\nA rattling \
explosion shakes the foundations of the castle. You take up your sword and\nexit the audience chamber. It's no legendary steel, \
but it will do.\n\nThe great hall is in flames, and the nobles and merchants gathered there are fleeing for\ntheir lives. As \
you emerge, the dreaded Firebrand swoops in from a hole he blasted in\nthe cieling moments ago; a terrible beast barely \
contained in the room's towering\nheights. He sniffs the air and scowls at you.\n\n\"The blood of that wretched man flows \
through your veins, petty king. Today, I will\nexact my vengeance!\"\n\nDespite the great hall's tremendous size, the dragon's \
movements may be hindered here.\nThere's a chance that you may catch him off-guard, but it would be much easier to make an\n\
escape.\n\n---------------------------------------------------------\n";

// Fight in the Great Hall. Slay the dragon. THANKS FOR PLAYING.
char* great_hall_FIGHT_S = "\n***************************************************************************************\n\nWith a \
valiant battle cry, you leap through the air, sword shining red in the \nsurrounding flames. A glint from its blade blinds \
Firebrand, and in the moment of his \nrecoil, you chance a strike. With the strength of a hero, you thrust your blade into \n\
the softer flesh at the underside of his neck. It pierces deeply.\n\nFirebrand wails in pain. Gravely wounded, he makes a quick \
escape through the damaged \nroof and heads for the cave whence he came. Peace returns to the castle for a time. \nSome days \
later, your army happens upon the dragon's corpse not far outside the \ncity, fallen from its wound.\n\nYou have done the \
impossible. With a common blade, you felled your family's ancient \nfoe. You reign over the Whitespire kingdom into old age, and \
you are laid to rest in \nthe temple beside the hero of old. Together, two swords lay enshrined at the Chosen's \nTemple. \
The blade that drove back Firebrand, and the blade that ended his life.\n\n\
---------------------------------------------------------\nCONGRATULATIONS! YOU WIN!!";

// Fight in the Great Hall. Fail. GAME OVER.
char* great_hall_FIGHT_F = "\n***************************************************************************************\n\nThough \
a warrior both strong and nimble, you could not match the might and speed of the \ndreaded Firebrand. Your blade shatters \
against his armored hide, and in a single \ncrushing swoop, he pins you beneath one colossal talon. As you struggle to breathe, \
he \nstares into your eyes with a sneer of daggers.\n\n\"Is this the best the blood of Whitespire can do? Regret and despair, \
foolish little \nking. Your insufferable lineage ends with you.\"\n\nYou struggle with all your strength, but to no avail. You \
watch, helpless, as Firebrand \nbathes the great hall in flames. You and your people are burned to ash. Your kingdom is \n\
reduced to rubble.\n\n---------------------------------------------------------\nGAME OVER";

// Run from Great Hall. VALOR CHANCE: Save fallen noble woman.
char* great_hall_RUN = "\n***************************************************************************************\n\nYou dart \
and dodge between Firebrand's legs, narrowly evading his frustratedly stomping \ntalons as he struggles to turn his massive \
body in your direction. The crowd has \ndispersed into the Grand Corridor, and you see a clear path to follow.\n\nHowever, as \
you make for the open doorway, you notice someone left behind. A young \nwoman, fallen and struggling to get to her feet. You \
are confident that you can escape \non your own. However, though it would be a close call, there may be time to help her \n\
escape with you.\n\n---------------------------------------------------------\n";

// Run from Great Hall. Abandon woman. Run success. (To grand_corridor)
char* great_hall_run_S = "\n***************************************************************************************\n\nWith \
eyes fixed on the doorway in front of you, you hear a scream of agony as the woman \nyou abandoned is crushed. You can hear the \
dragon's frustrated roar and feel the heat of \nhis flames at your back, but you manage to escape just in time. Ahead of you \
lies the \nGrand Corridor.\n";

// Run from Great Hall. Abandon woman. Run fail. GAME OVER. PLAY AGAIN prompt.
char* great_hall_run_F = "\n***************************************************************************************\n\nWith \
eyes fixed on the doorway in front of you, you hear a scream of agony as the woman \nyou abandoned is crushed. You sprint for \
your life, but not quickly enough. In his \nrampage, Firebrand crushes you underheel, leaving you a broken pile of bones and \
mangled \nflesh. Your kingdom will suffer for the loss of their king and champion.\n\n\
---------------------------------------------------------\nGAME OVER";

// Run from Great Hall. Save woman, success. (To grand_corridor)
char* great_hall_save_S = "\n***************************************************************************************\n\n\
Firebrand notices you moving to save the woman. He lashes his tail at you like a barbed \nwhip the width of a great oak tree, \
but you deftly slide beneath it and to the woman's \nside.\n\nYou lift her in your arms and run with all your might for the \
open doorway. You can hear \nthe dragon's frustrated roar and feel the heat of his flames at your back, but you \nmanage to \
escape just in time, and with the young woman unharmed.\n\n\"Bless you, my lord! I had feared the worst! The legends were true, \
and the dreaded \nFirebrand is upon us. But you are truly the hero's successor! I have faith that you \nwill save us all!\"\n\n\
She bows and takes her leave. Ahead of you lies the Grand Corridor.\n";

// Run from Great Hall. Save woman, fail. GAME OVER. PLAY AGAIN prompt.
char* great_hall_save_F = "\n***************************************************************************************\n\n\
Firebrand notices you moving to save the woman. He lashes his tail at you like a barbed\nwhip the width of a great oak tree. \
You attempt to slide beneath it, but you aren't \nquick enough. You are impailed on its bony spikes and flung to the far wall, \
shattered\nand bloodied.\n\nAs your last breath escapes your lungs, you see the dragon's enormous talon stomp on the \nwoman's \
head, crushing it. The rest of your kingdom will share her fate, and the legend \ndies with you.\n\n\
---------------------------------------------------------\nGAME OVER";

char* corridor = "\n***************************************************************************************\n\nOn any other \
day, the marble length and stained-glass heights of the Grand Corridor\nwould be the envy of the world. But on this day of \
Firebrand's wrath, it is a terrifying\nrun through the falling shards and rubble of its former beauty. You see that most of\n\
those still living have made it to the far end's exit to the bailey, but for one\nremaining straggler.\n\nYou happen upon \
a rotund man of amber skin and black beard clothed in foreign silks.\nMidway through the corridor, he is hobbling in his \
step. He cannot catch his breath,\nand he is slowing by the second. All the while, Firebrand's wild rampage in the Great\nHall \
is bringing the structure around you down in larger chunks.\n\nThe foreign stranger can run no longer. He falls to his knees, \
clasps a golden amulet\nhanging from a silver chain about his neck, and begins to pray. Your strength, however,\nhas not left \
you; you could easily make it to the bailey on your own. But the Grand\nCorridor will not stand much longer. Without your \
help, this poor man will perish.\n\n---------------------------------------------------------\n";

char* corridor_run_S = "\n***************************************************************************************\n\nYou run \
as fast as you can, bolting past the foreign man and leaving him to his fate.\nAs the ruins of the Grand Corridor crash down \
around you, you can hear the terror in his\nwhimpering prayers growing louder and louder until they're silenced with a fatal \
crunch.\nJust before the falling debris can claim your life, you slide through a narrow opening\nin the collapsing entryway, \
and out to the bailey.\n";

char* corridor_run_F = "\n***************************************************************************************\n\nYou run \
as fast as you can, bolting past the foreign man and leaving him to his fate.\nAs the ruins of the Grand Corridor crash down \
around you, you can hear the terror in his\nwhimpering prayers growing louder and louder until they're silenced with a fatal \
crunch.\n\nJust before you make it to the bailey, the arching entryway collapses and crushes\nyou to death. Firebrand's \
rampage will only grow more violent before he realizes that\nyou're no longer among the living. He will stamp out every last \
standing structure in\nyour kingdom.\n\nYour legend ends here. Your people are doomed.\n\n------------------------------------\
---------------------\nGAME OVER";

char* corridor_save_S = "\n***************************************************************************************\n\nYou rush \
to the foreign man's side and pull him to his feet, urging him to keep running.\nThe ceiling is about to collapse in an \
onslaught of falling glass and stone; you must\nseek an alternate escape route. As you hobble along with the foreign man in \
tow, every\nentryway you find has caved in, trapping who knows how many inside.\n\nAgainst all odds, you find the entrance to \
the royal armory standing and clear. You pull\nthe foreign man by the arm into the armory just as the ceiling comes crashing \
down. He\nfalls to his hands and knees with nerve-shaken laughter.\n\n\"Many thanks to you, lord of Whitespire! I am but a simple \
merchant seeking trade in\nyour fine land. I never imagined I would face such peril! Please, take this amulet.\nIt was meant \
as a gift of good will. But I fear you will now need its divine protection.\nIt is a priceless treasure from my native land, \
for it is said that it will deliver its\nwearer from the hands of death.\"\n\nYOU GET: HOLY AMULET (re-roll chance, single \
use)\n";

char* corridor_save_F = "\n***************************************************************************************\n\nYou rush \
to the foreign man's side and pull him to his feet, urging him to keep running.\nThe ceiling is about to collapse in an \
onslaught of falling glass and stone; you must\nseek an alternate escape route. As you hobble along with the foreign man in \
tow, every\nentryway you find has caved in, trapping who knows how many inside.\n\nAlas, though you search tirelessly, you \
are unable to find a means of escape before\nthe ceiling gives way. You and the merchant are shredded and crushed in a hail \
of ruin.\nAs will be the rest of your kingdom. With your death, Whitespire's fate is sealed.\n\n----------------------------\
-----------------------------\nGAME OVER";

char* armory = "\n***************************************************************************************\n\nYou enter the \
royal armory to find it in shambles. The outer wall has fallen, leaving\nthe room exposed to the elements. Its shelves and \
racks have been stripped bare of their\nsteel, either by the royal guard defending your people or by your people attempting \
to\ndefend themselves. All that remains is a single shield mounted above the entryway; a\nsymbol of the royal guard's fealty \
emblazoned with your family's coat of arms.\n\nYou hear rustling in a far corner of the room, past a number of empty racks. \
Upon\ninvestigation, you find your son, Prince Viktor, struggling to open a hatch in the\nfloor. But before you can express \
your relief, your attention is drawn to the sky. \nFirebrand has once again taken flight, raining fire and death on the \
castle.\n\nA massive fireball is headed straight for this room. Roll to save!\n";

char* armory_success = "\n***************************************************************************************\n\nWhile the \
foreign merchant struggles to help the prince open the hatch, you rush to\nthe shield mounted above the entryway and \
attempt to pry it free. Its pristine state\nbelies its history. It has been said that the hero used this blessed shield to \
ward\nFirebrand's flames. The time has come to test the legend.\n\nYou pull with all your might, and at the last moment, free \
the shield from the wall.\nFacing the shattered wall, you raise the shield and brace yourself. The shield absorbs\nthe impact, \
reducing the explosion to a harmless scattering of embers.\n\nYOU GET: FAMILY SHIELD (+5 to FIGHT roll)\n\nHaving averted the \
immediate threat, you apply a third set of hands to the hatch and\nfinally force it open. You descend the spiral staircase \
with your son and the foreign\nstranger to a subterranean junction. It was once used to quickly deploy units of the royal\n\
guard to various points around the castle grounds. Currently, it's being used to evacuate\nsurvivors of the royal court.\n\n\
You entrust the lives of the merchant and your son to a supervising member of the guard\nand head in the opposite direction, \
toward the outlet at the bailey.\n";

char* armory_fail = "\n***************************************************************************************\n\nWhile the \
foreign merchant struggles with the prince to open the hatch, you rush to\nthe shield mounted above the entryway and attempt \
to pry it free. Its pristine state\nbelies its history. It has been said that the hero used this blessed shield to ward\n\
Firebrand's flames. The time has come to test the legend.\n\nYou pull with all your might, but the shield will not budge. The \
wayward fireball\ncrashes into the open armory with a violent explosion, incinerating you, the merchant,\nand your son upon \
impact.\n\n---------------------------------------------------------\nGAME OVER";

char* bailey = "\n***************************************************************************************\n\nYou arrive at the \
bailey in a throng of chaos. Survivors are attempting to flee for\ntheir lives, but the drawbridge has been destroyed, \
leaving them without an immediately\nviable means of escape. Firebrand is quickly descending, but he doesn't appear to see\n\
you among the crowd.\n\nYou could fight here, but it wouldn't be in your favor. The crowd would make maneuvering\ndifficult, \
and casualties would be high. It may be better to look for a more advantageous\nposition.\n\n------------------------------------\
---------------------\n";

char* bailey_fight_S = "\n***************************************************************************************\n\n\
As Firebrand is distracted with the chaos of the fleeing crowd, you act upon a chance\nto strike. \
Scaling a nearby statue, you leap onto his back with a vicious, downward\nthrust of your blade between his shoulder blades. \
The beast shrieks in agony, flailing\nabout in a violent panic and trampling one innocent bystander after another, as you\n\
drive the blade further into his spine. He curses the name of Whitespire as he exhales\nhis last fiery breath.\n\nYou have \
slain the dreaded Firebreand before the crowd's very eyes, but there have been\nmany casualties. While they admire you for \
your strength, they now fear you for both your\nbrutality and your evident disregard for the lives of your subjects. The \
tension sows a\npolitical rift in your kingdom and births a faction of rebels threatening your crown.\n\nBegrudging them their \
disloyalty, you choose to rule with an iron fist. Fear you as\nthey may, your army respects you as a warrior and would follow \
you into the pits of hell.\nYou use them as a hammer to stamp out the resistance and enforce your will.\n\nThe death of \
Firebrand marks the beginning of your vast and terrible empire. The vile\nbeast's severed head adorns your throne as a \
testament to your might, and your legend\nwill deify your descendants for many generations to come.\n\n------------------\
---------------------------------------\nCONGRATULATIONS! YOU WIN!";

char* bailey_fight_F = "\n***************************************************************************************\n\nYou wait \
for Firebrand to land, staying hidden among the crowd. As you attempt to scale\na nearby statue to jump on his back, Firebrand \
notices you and lashes his tail in your\ndirection. The mighty blow shatters the statue, hurling you and its fragments into \
the\ncrowd. Several are crushed by the rubble. You are broken and unable to move. Your\nlegacy ends here.\n\n--------------\
-------------------------------------------\nGAME OVER";

char* bailey_run = "\n***************************************************************************************\n\nThinking \
quickly, you grab a discarded length of rope and scale a tower to the battlements.\nFirebrand is headed for the mass of \
people gathered at the fallen drawbridge, and he\nstill hasn't spotted you. You could safely rappel to the winding road below \
and pass to\nthe market unnoticed. But the people trapped here will suffer his wrath. You could also\nuse a nearby \
ballista to gain his attention and draw him away.\n\n---------------------------------------------------------\n";

char* bailey_run_S = "\n***************************************************************************************\n\nYou tie the \
rope around your waist and around the nearest merlon. Rope in hand, you\nstep over the crenel and slowly lower yourself to \
the road below. Above you, you can hear\nthe screams of your people among frustrated roars and flashes of fire. After a short \
run,\nyou arrive at the market without incident.\n";

char* bailey_run_F = "\n***************************************************************************************\n\nYou tie the \
rope around your waist and around the nearest merlon. Rope in hand, you\nstep over the crenel and slowly lower yourself to \
the road below. Above you, you can hear\nthe screams of your people among frustrated roars and flashes of fire.\n\nSuddenly, \
the rope snaps and sends you plummeting to your doom. Nearly every bone in your\nbody breaks on impact, but unfortunately for \
you, your life does not end with the fall.\nYou will live to suffer Firebrand's killing blow.\n\n-----------------------------\
----------------------------\nGAME OVER";

char* bailey_save_S = "\n***************************************************************************************\n\nYou fire \
the ballista. The bolt splinters against his armored hide. Little more than an\nannoyance, but it gets his attention. He ignores \
the crowd and adjusts his flight path\ntoward you. There will be no time to rappel to the road below. Fortunately, you spot an\n\
abandoned cart of hay near the wall.\n\nYou jump for the cart, and it breaks your fall. You push the abandoned cart down a\n\
steep hill and jump in the back, riding it toward the market below. Giving chase,\nFirebrand hurls a barrage of fireballs at \
the cart, but is unable to land a hit.\n\nYou jump from the cart just before it crashes into a storefront.\n";

char* bailey_save_F = "\n***************************************************************************************\n\nYou fire \
the ballista. The bolt splinters against his armored hide. Little more than\nannoyance, but it gets his attention. He ignores \
the crowd and adjusts his flight path\ntoward you. There will be no time to rappel to the road below. Fortunately, you spot an\n\
abandoned cart of hay near the wall.\n\nYou jump for the cart, and it breaks your fall. You push the abandoned cart down a\n\
steep hill and jump in the back, riding it toward the market below. Giving chase,\nFirebrand hurls a barrage of fireballs at \
the cart. A fireball hits its target,\nblasting the cart to splinters, and you along with it.\n\n-----------------------------\
----------------------------\nGAME OVER";

char* market = "\n***************************************************************************************\n\nThe market is in \
shambles and flames. Looters abound, some fighting and killing each\nother over their ill-gotten gain. \
You notice a peasant man carrying away an over-packed\nbasket of what appear to be vegetables and salted meats. Suddenly, \
another man blocks his\npath and holds him at knife point, demanding his likely stolen fare.\n\nThough these people would \
sooner tear your kingdom apart for survival than band together\nto save it, they are still your people. Firebrand has taken \
to the skies, and he is on\nthe approach. You should make haste for the cathedral, but you swore an oath to protect\nthem. Even \
from themselves.\n\n---------------------------------------------------------\n";

char* market_run_S = "\n***************************************************************************************\n\nAgainst \
your better judgment, you leave the victim to die. You have little time to spare,\nand you must reach the cathedral before \
Firebrand catches up with you. With a sizeable\nmeasure of effort and dexterity, you manage to navigate the rioting crowds \
and burning\ndebris, arriving at the residential district.\n";

char* market_run_F = "\n***************************************************************************************\n\nAgainst \
your better judgment, you leave the victim to die. You have little time to spare,\nand you must reach the cathedral before \
Firebrand catches up with you. You attempt to\nnavigate the rioting crowds and burning debris, but the crowd overtakes you. \
You are\ntrampled, and your leg is broken.\n\nThe pain is excuciating. You cannot move, and you are helpless to defend \
yourself, let\nalone them. Your people will be destroyed when Firebrand arrives, and you will die with\nthem.\n\n--------------\
-------------------------------------------\nGAME OVER";

char* market_save_S = "\n***************************************************************************************\n\nThe man's \
assailant moves to stab, but before he can, you punch him in the face and\nsend him toppling over. When he sees who struck \
him, he looks to you in awe, then averts\nhis gaze in shame. The crowd notics you and, one by one, they gather around you and\n\
kneel.\n\nYour words for them are brief, but dire.\n\n\"What wretches I behold on this fateful hour! The dragon is upon us, and \
this is what\nbecomes of my people?! By Divine Right, it is my charge to slay the beast, and mine\nalone. But the strength of \
a king is the faith of his kingdom. And the strength of a man\nis in the compassion of his neighbor.\n\nI ask not that you fight \
here with me today. But I urge you to remember that we, all of\nus, are a people of legend. We are the sons and daughters of \
a small hamlet that\nsurvived a great evil and thrived. Will we now abandon that legacy for fear and\nweakness? For selfish \
gain? Do right by your fellow man. Lend me your strength, and we\nwill prevail!\"\n\nTheir silence turns to thunderous \
cheering! You leave them in faith that they may show\nfaith in you. Firebrand is close on your heels, and there is no time \
to dawdle here.\nAhead of you lies the residential district.\n";

char* market_save_F = "\n***************************************************************************************\n\nAs the \
man's assailant moves to stab, you rush forward to intervene. He sees you coming in\nhis peripheral vision \
and, in a panic, he thrusts for you instead. You attempt to dodge,\nbut your martial dexterity fails you. The blade sinks \
between your ribs and into your\nlung. You stare into the assailant's eyes as you draw your last breath.\n\nHorrified, the \
assailant realizes what he's done. The kingdom's fate is sealed.\n\n---------------------------------------------------\
------\nGAME OVER";

char* town = "\n***************************************************************************************\n\nSo far, the \
residential district appears largely untouched. Firebrand clearly headed\nstraight for the throne. Most of the damage here \
and behind you at the market is\nundoubtedly due to panic from the people. Your kingdom may yet survive.\n\nThe back alleys \
will provide you sufficient cover until you reach the cathedral. While\nturning a corner near the town square, you spot a burning \
building. You hear the harrowing\ncries of a small child coming from the second floor. The cathedral isn't far, but this\nchild \
will surely die without your help.\n\n---------------------------------------------------------\n";

char* town_run = "\n***************************************************************************************\n\nYou run by the \
burning building and head for the cathedral, deciding that there is no more\ntime to spare. The sacrifice of one, even of one \
so young, is a pittance compared to\nputting the masses at risk. You must claim the hero's blade.\n";

char* town_save_S = "\n***************************************************************************************\n\nThrowing \
caution to the wind, you enter the burning building. You call out for the child\nas you keep low and step over fallen planks \
and beams. The house begins to creak and\nrumble beneath its own weight just as you spot a little boy trapped beneath a \
fallen\nshelf.\n\nSummoning all of your strength, you lift the shelf and allow the young boy to crawl\nout. However, the stair \
well you just climbed is now engulfed in flames. You take the\nboy in your arms and leap from the second floor window. You \
roll upon landing, breaking\nyour fall and saving the boy's life.\n\n\"Thank you, sir...\" the boy meekly whispers. His \
parents approach, but you have no\ntime to spare. You leave them in peace and head for the cathedral.\n";

char* town_save_F = "\n***************************************************************************************\n\nThrowing \
caution to the wind, you enter the burning building. You call out for the child\nas you keep low and step over fallen planks \
and beams. The house begins to creak and\nrumble beneath its own weight just as you spot a little boy trapped beneath a \
fallen\nshelf.\n\nYou attempt to lift the shelf, but suddenly, the building's central pillar falls on\nyou, knocking you \
unconscious. The building collapses in on itself. You and the\nchild are burned alive in the flaming rubble.\n\n----------\
-----------------------------------------------\nGAME OVER";

char* cathedral_hidden_passage = "\n***************************************************************************************\n\nThe \
passage collapses violently behind you with the sound of each falling stone right\nat your heels. As you near the light, you \
can see the bishop beckoning you. Running with\nall of the speed you can muster, you dive for the narrow exit. You roll to a \
stop on the\ncathedral floor just as the remains of the passage crash into clutter of shattered rubble.\n\nThe bishop helps you \
to your feet, and you check yourself for injuries. You're covered\nin dust, but no worse for the wear.\n\n\"My lord, you're \
safe! Praise be to God! The fated hour is upon us! Please, come this\nway. Your birthright awaits!\"\n\nThe bishop leads you \
to a hidden vault beneath the altar; a small but highly decorated\nroom encircling a large pedestal. On that pedestal, standing \
at the heart of a blazing\nfire pit, is a pristine and glistening sword. The bishop speaks with reverence...\n\n\"This \
sinister, red flame is of the beast himself. It has burned for centuries, since\nbefore the first bricks of this kingdom were \
laid. Passed down patiently, from coal to\ncoal, from year to year, to house the hero's sword. For it has been told that \
dragonfire\ncould do him no harm. And, be he worthy, a son of the hero may know the same immunity.\"\n\nYou hesitate for a \
moment, then slowly reach for the sword's grip. But the flames roar\nand flash forth, burning you with their heat. You recoil, \
and for a moment, you swear\nthat you can see the dragon's wicked grin in their haze. You hear a stern and ominous\nvoice \
in your head.\n\n\"Ye son of Whitespire. Apostate king and selfish coward. You are not worthy.\"\n\nA pang of shame wrenches in \
your heart. You have put your own safety first. You have\nabandoned your people. You have failed to honor the defender's \
oath, and so you will\nface the dragon without the hero's blessing.\n\nSuddenly, a thunderous bang rattles the cathedral from \
above. You rush for the\nentrance.\n";

char* cathedral_worthy = "\n***************************************************************************************\n\nYou enter \
the cathedral to find it unharmed. Perhaps the will of the hero guards it even\nnow. The bishop emerges from behind the altar. \
Though he hid in fear, he upheld his\nsacred duty just as you have upheld yours. He is an honorable man.\n\n\"My lord, you're \
safe! Praise be to God! The fated hour is upon us! Please, come this\nway. Your birthright awaits!\"\n\nThe bishop leads you to \
a hidden vault beneath the altar; a small but highly decorated\nroom encircling a large pedestal. On that pedestal, standing \
at the heart of a blazing\nfire pit, is a pristine and glistening sword. The bishop speaks with reverence...\n\n\\
"This sinister, red flame is of the beast himself. It has burned for centuries, since\nbefore the first bricks of this kingdom \
were laid. Passed down patiently, from coal to\ncoal, from year to year, to house the hero's sword. For it has been told that \
dragonfire\ncould do him no harm. And, be he worthy, a son of the hero may know the same immunity.\"\n\nYou hesitate for a \
moment, then slowly reach for the sword's grip. As your hand nears\nthe sacred steel, the flames recede as if in fear, \
vanishing in a pitiful whisp of\nsmoke. As you lift the shining blade from the coals, you hear a strong and triumphant\nvoice \
in your head.\n\n\"Ye son of Whitespire. Courageous and valiant. True ruler and defender of these lands.\nYou are worthy.\"\n\n\
You feel a divine strength well within you. The spirit of the hero courses through\nyour veins.\n\nSuddenly, a thunderous \
bang rattles the cathedral from above. You rush for the\nentrance.\n\nYOU GET: HERO'S SWORD (+5 to FIGHT roll)\n";

char* cathedral_unworthy = "\n***************************************************************************************\n\nYou enter \
the cathedral to find it unharmed. Perhaps the will of the hero guards it even\nnow. The bishop emerges from behind the altar. \
Though he hid in fear, he upheld his\nsacred duty just as you have upheld yours. He is an honorable man.\n\n\"My lord, you're \
safe! Praise be to God! The fated hour is upon us! Please, come this\nway. Your birthright awaits!\"\n\nThe bishop leads you \
to a hidden vault beneath the altar; a small but highly decorated\nroom encircling a large pedestal. On that pedestal, \
standing at the heart of a blazing\nfire pit, is a pristine and glistening sword. The bishop speaks with reverence...\n\n\"This \
sinister, red flame is of the beast himself. It has burned for centuries, since\nbefore the first bricks of this kingdom were \
laid. Passed down patiently, from coal to\ncoal, from year to year, to house the hero's sword. For it has been told that \
dragonfire\ncould do him no harm. And, be he worthy, a son of the hero may know the same immunity.\"\n\nYou hesitate for a \
moment, then slowly reach for the sword's grip. But the flames roar\nand flash forth, burning you with their heat. You recoil, \
and for a moment, you swear\nthat you can see the dragon's wicked grin in their haze. You hear a stern and ominous\nvoice in \
your head.\n\n\"Ye son of Whitespire. Apostate king and selfish coward. You are not worthy.\"\n\nA pang of shame wrenches in \
your heart. You have put your own safety first. You have\nabandoned your people. You have failed to honor the defender's oath, \
and so you will\nface the dragon without the hero's blessing.\n\nSuddenly, a thunderous bang rattles the cathedral from above. \
You rush for the\nentrance.\n";

char* showdown_intro = "\n***************************************************************************************\n\nYou exit \
the cathedral. The air is eerily still, and the roar of the flames left in the\ndragon's wake carries for miles. As you step \
out into the town square, you hear a fearsome\nvoice boom above you. Firebrand is perched on the cathedral roof, sneering like \
a deranged\ngargoyle spouting fire from its nostrils.\n\n\"There you are, little king. This game of cat and mouse ends here. \
It would chill that\naccursed man's heart to know his descendant is the coward standing before me. For shame,\nson of \
Whitespire.\"\n\nFirebrand leaps from the rooftop. The earth quakes, and the tiles of the town square\ncrunch beneath his \
weight. But you stand firm and unflinching.\n";

char* showdown_AMULET = "\nThe Holy Amulet hangs about your neck to guard your soul.\n";

char* showdown_SHIELD = "\nYour family shield awaits to ward his noxious fire.\n";

char* showdown_SWORD = "\nThe legendary sword gleams in your hand. The might of the hero is with you.\n";

char* showdown_choice = "\n***************************************************************************************\n\nYou could \
end it here. You could slay the beast in this very square, but victory will\nnot come without a perilous battle. The people \
still attempting to flee will be at risk,\nas will what's left of their homes and livelihood. Fortunately, you spot a horse \
waiting\nnearby. Against all odds, it did not flee. Perhaps it shares in your destiny, serves some\ndivine purpose.\n\nIt is \
certainly not without risk, but you may be able to ride to a more advantageous\nposition.\n\n---\
------------------------------------------------------\n";

char* showdown_fight_S = "\n***************************************************************************************\n\nIn your \
violent clash, Firebrand shows no mercy for the people or structures around\nhim. He purposefully lays waste to your legacy \
in his effort to destroy you, unleashing\ncarnage and terror in his wake before your blade finally finds his heart.\n\nYou \
have slain Firebrand at long last, but it did not come without sacrifice. He has\nleft your kingdom in ruins, and many \
lives were lost in the residential district. There\naren't enough left to rebuild and re-establish order.\n\nYour feats \
here today will be told in song. But it will be one of tragedy rather\nthan triumph. And it will fade into the mists of \
time along with the legends of your\nancestor and your people. Though you live on, your legacy is left in whispers\namong \
the mass grave once known as Whitespire.\n\n---------------------------------------------------------\nCONGRATULATIONS! YOU WIN!";

char* showdown_fight_F = "\n***************************************************************************************\n\nIn your \
violent clash, Firebrand shows no mercy for the people or structures around\nhim. He purposefully lays waste to your legacy in \
his effort to destroy you, unleashing\ncarnage and terror in his wake.\n\nThough you fight with honor and bravery, Firebrand \
wins out in the end. And he does not\nleave a corpse to honorably inter. Nor a tomb or graveyard in which to leave you. You \
and\nyour people will perish here, your kingdom and legacy reduced to burning rubble. And the\nlegends they told will be left \
as whispers on a mass grave.\n\nWhitespire is no more.\n\n---------------------------------------------------------\nGAME OVER";

char* showdown_run_S = "\n***************************************************************************************\n\nYou run \
for the horse, and Firebrand immediately gives chase. Mounting the horse on the\nrun, you ride as hard as you can. You stick \
to the main roads to minimize collateral\ndamage, dodging the flames as you go. With impressive skill, you make it to the edge of \
town\nand race over the drawbridge and into the verdant fields beyond.\n";

char* showdown_run_F = "\n***************************************************************************************\n\nYou run \
for the horse, and Firebrand immediately gives chase. Mounting the horse on the\nrun, you ride as hard as you can. You stick \
to the main roads to minimize collateral\ndamage, dodging the flames as you go. But the horse isn't fast enough. Firebrand\n\
descends on you like a great hawk and rends you and the horse to pieces with his\nrazor-sharp talons.\n\nYou've come so far, \
only to perish without once lifting your blade. Destiny, it seems,\nis a fickle thing.\n\n------------\
---------------------------------------------\nGAME OVER";

char* field = "\n***************************************************************************************\n\nYou ride hard and \
far into the field at a safe distance from town. This is the ideal\nplace to face Firebrand. At last, the time has come \
to slay this beast! Strike him down!\nSave your people! Fulfill your destiny!\n\n--------------------------------------------\
-------------\n";

char* field_fight_S = "\n***************************************************************************************\n\n\
With sword drawn, you turn your horse hard to rush the dragon head-on. You leap from the\nsaddle and slash \
Firebrand from collar bone to groin. He perishes consumed by his own\nflames, burned down to a pile of charred bones and ash. \
Your kingdom is secure. You are\na living legend.\n\n---------------------------------------------------------\n\
CONGRATULATIONS! YOU WIN!";

char* field_fight_F = "\n***************************************************************************************\n\nWith sword \
drawn, you turn your horse hard to rush the dragon head-on. You leap from the\nsaddle poised to strike, but Firebrand catches \
you off guard. He lunges forth with his\nrazor-sharp talons and rends you and your horse to pieces.\n\nOn this day, Firebrand \
is satisfied with your death. For a time, your kingdom is spared\nhis wrath. Perhaps, one day, your son will prevail where you \
failed.\n\n---------------------------------------------------------\nGAME OVER";

char* field_run_S = "\n***************************************************************************************\n\n\
You escape on your horse. Fireband does not give chase. He takes no pleasure in killing\ncowards. He does, \
however, stamp out your kingdom down to the last pebble. Most of your\npeople die in his wake. Few survive, and those yet \
living will tell the tale of the\nCowardly King of Whitespire until the day they die. You will live the rest of your days\na \
common man, shamed in exile.\n\n---------------------------------------------------------\nGAME OVER";

char* field_run_F = "\n***************************************************************************************\n\n\
You attempt to escape on horseback, leaving your kingdom behind. But you fail to outrun\nFirebrand's talons. \
You die a coward's death. Your kingdom will suffer.\n\n---------------------------------------------------------\nGAME OVER";

// Present logo and intro text
void INTRO(void)
{
    printf("\n ___      _______  _______  _______  __    _  ______ \n");
    printf("|   |    |       ||       ||       ||  |  | ||      |\n");
    printf("|   |    |    ___||    ___||    ___||   |_| ||  _    |\n");
    printf("|   |    |   |___ |   | __ |   |___ |       || | |   |\n");
    printf("|   |___ |    ___||   ||  ||    ___||  _    || |_|   |\n");
    printf("|       ||   |___ |   |_| ||   |___ | | |   ||       |\n");
    printf("|_______||_______||_______||_______||_|  |__||______|\n\n");
    printf(" _______  _______\n");
    printf("|       ||       |\n");
    printf("|   _   ||    ___|\n");
    printf("|  | |  ||   |___\n");
    printf("|  |_|  ||    ___|\n");
    printf("|       ||   |\n");
    printf("|_______||___|\n\n");
    printf(" _     _  __   __  ___   _______  _______  _______  _______  ___   ______    _______\n");
    printf("| | _ | ||  | |  ||   | |       ||       ||       ||       ||   | |    _ |  |       |\n");
    printf("| || || ||  |_|  ||   | |_     _||    ___||  _____||    _  ||   | |   | ||  |    ___|\n");
    printf("|       ||       ||   |   |   |  |   |___ | |_____ |   |_| ||   | |   |_||_ |   |___ \n");
    printf("|       ||       ||   |   |   |  |    ___||_____  ||    ___||   | |    __  ||    ___|\n");
    printf("|   _   ||   _   ||   |   |   |  |   |___  _____| ||   |    |   | |   |  | ||   |___ \n");
    printf("|__| |__||__| |__||___|   |___|  |_______||_______||___|    |___| |___|  |_||_______|\n\n");

    printf("Written and Coded by Aaron Shotwell, May 2020\n\n-------------------------------------------------------------------\
------------------\n-------------------------------------------------------------------------------------\n");

    PRESS_KEY('C');

    if (PLAY != 'Y')
    {
        printf("\nWelcome to my very first game. A short and simple tabletop RPG simulator featuring\na D20 roll and D6 save \
mechanic, and a simple decision tree offering item rewards that\naffect roll outcomes.\n\nYou play as the king of Whitespire \
Kingdom, a monarchy founded by your ancestor,\na legendary warrior who defeated a terrible dragon and saved the people of this \
land\nfrom its wrath. He became their first king and, for eight generations, his sons have\ninherited the throne. Each with the \
promise to uphold the duty of the hero and protect\nhis people should the dreaded Firebrand ever return.\n\nToday is that \
fateful day. It is up to you to slay your family's mortal enemy once and\nfor all. Save your kingdom. Fulfill your destiny.\n");

        PRESS_KEY('C');
    }

    return;
}

// Scenario presentation and choice prompt
char SCENARIO(char type, char* scen)
{
    char FIGHT_SAVE_RUN; // RUN or FIGHT decision

    printf("%s", scen); // Print Audience Chamber scenario text

    if (type == 'A') // If this is a FIGHT or RUN scenario...
    {
        do //Prompt for FIGHT or RUN response, reject invalid input
        {
            printf("FIGHT (F), RUN (R): ");
            Sleep(1000);
            scanf(" %c", &FIGHT_SAVE_RUN);
        }while (FIGHT_SAVE_RUN != 'F' && FIGHT_SAVE_RUN != 'R' && FIGHT_SAVE_RUN != 'f'  && FIGHT_SAVE_RUN != 'r');
    }

    if (type == 'B') // If this is a VALOR chance scenario...
    {
        do //Prompt for SAVE or RUN response, reject invalid input
        {
            printf("SAVE (S), RUN (R): ");
            Sleep(1000);
            scanf(" %c", &FIGHT_SAVE_RUN);
        }while (FIGHT_SAVE_RUN != 'S' && FIGHT_SAVE_RUN != 's' && FIGHT_SAVE_RUN != 'R'  && FIGHT_SAVE_RUN != 'r');
    }

    if(islower(FIGHT_SAVE_RUN)) // Convert lower case entry to upper case
        FIGHT_SAVE_RUN = toupper(FIGHT_SAVE_RUN);

    if (type == 'A') // Return 'F' if player chooses to fight
    {
        if (FIGHT_SAVE_RUN == 'F')
        {
            return 'F';
        }
    }

    if (type == 'B') // Return 'S' if player chooses to save a character in distress
    {
        if (FIGHT_SAVE_RUN == 'S')
        {
            return 'S';
        }
    }

    if (FIGHT_SAVE_RUN == 'R') // Return 'R' if player chooses to run
    {
        return 'R'; // TO HIDDEN PASSAGE
    }
}

/**
 * Project Title: Platformer Game in C
 * Creator: Tyler Loeper, for CS50 Miami, Summer 2016 cohort.
 * Completed: 9/3/2016
 * 
 * Overview:
 * This is a small game in c I created to mimic the 1990s mario games. In it a small 2d world is rendered, and the player (graphically represented by the letter "t") is tasked 
 * with reaching the of the world and win by touching a flag "p". The player has several moves availible, including dashes and jumps, and must avoid spikes and falls in order to reach the end. 
 * 
 * The game makes use of several function prototypes, and uses pointers to track the position of the player. Pointers were necessary because these variables (worldpositionx, and worldpositiony) needed to be 
 * changed globally, and not locally, in order for the functions that tracked position to work together. I tried using local variables originally, but the tracking didnt work. 
 * Hence the current use of pointers.
 * 
 * For your reference, here is a list showing what each number in the array of arrays (2d game world) represents.
        0 = air
        1 = solid (ground)
        2 = player
        3 = kill condition
        4 = win condition
        5 = flag
        6 = flag mast
        7 = flag ground
        8 = animation
 * Each number is in the array of arrays, but is represented differently graphically in terminal by using printf (if number is present). For example all 0s print as " ", and the player "2" prints as "t".
 * 
 * I hope you enjoy the game!
 * 
 * Hints for playing the game:
 * Feel free to use dashes instead of regular movement to get around the big chunks of empty space faster. 
 * If you fall into the hole, get out by using jump.
 * */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int world[100][119];
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;
int o = 0;
int p = 0;
int q = 0;
int r = 0;
int length = 30;
int height = 119;
int lengthinitialized = 99;
int heightinitialized = 119;
int worldpositionx = 0;
int worldpositiony = 0;
int *wpx = &worldpositionx;
int *wpy = &worldpositiony;

//use array to track movements
int movement[1][1];
//win condition has to equal 1 to stop
int won[1][1];

//void clear(void);
void populateboard(void);
void placelimits(void);
void placeobjects(void);
void draw(void);
void initializeplayer(void);
void gravity(void);
void move(void);
void instructions(void);
void spikes(void);
void platforms(void);
void finishline(void);
void removeanimations(void);


int main(void)
{
    won[0][0] = 0;
    
    populateboard();
    placelimits();
    placeobjects();
    initializeplayer();
    spikes();
    platforms();
    finishline();
    draw();
    
    while(won[0][0] != 1)
    {
        worldpositiony = *wpy;
        worldpositionx = *wpx;
        removeanimations();

        if(world[worldpositionx+1][worldpositiony] == 0)
        {
            while(world[worldpositionx+1][worldpositiony] == 0)
            {
             gravity();
            }
        }

        draw();
        
        if( world[worldpositionx-1][worldpositiony]==4)
        {
            printf("You win! You reached the flag!\n");
            return 1;
        }
        if( world[worldpositionx+1][worldpositiony]==3)
        {
            printf("You have died. You lose. Try again.\n");
            return 0;
        }

        instructions();
        move();
        draw();
        sleep(1);
        
    }
    
}

// /**

void draw(void)
{
    //draw the whole map.
    for(m=0;m<length ;m++)
    {   
        if(world[m][n]==0)
        {
            printf(" ");
        }
        else if(world[m][n]==1)
        {
            printf("=");
        }
        else if(world[m][n]==2)
        {
            printf("t");
        }
        else if(world[m][n]==3)
        {
            printf("^");
        }
        else if(world[m][n]==4)
        {
            printf(" ");
        }
        else if(world[m][n]==5)
        {
            printf("p");
        }
        else if(world[m][n]==6)
        {
            printf("|");
        }
        else if(world[m][n]==7)
        {
            printf("-");
        }
        else if(world[m][n]==8)
        {
            printf(".");
        }
        else
        {
            printf("%i", world[m][n]);
        }
        
        for(n=0;n<height ;n++)
            {
                if(world[m][n]==0)
                {
                    printf(" ");
                }
                else if(world[m][n]==1)
                {
                    printf("=");
                }
                else if(world[m][n]==2)
                {
                    printf("t");
                }
                else if(world[m][n]==3)
                {
                    printf("^");
                }
                else if(world[m][n]==4)
                {
                    printf(" ");
                }
                else if(world[m][n]==5)
                {
                    printf("p");
                }
                else if(world[m][n]==6)
                {
                    printf("|");
                }
                else if(world[m][n]==7)
                {
                    printf("-");
                }
                else if(world[m][n]==8)
                {
                    printf(".");
                }
                else
                {
                    printf("%i", world[m][n]);
                }
            }
        
        printf("\n");
    }
}

// **/


void populateboard(void)
{
    //fill the board with values, to avoid garbage values being printed. and to form the basis of the world (0s are air). 
    for(i=0;i<lengthinitialized;i++) 
    {
        for(j=0;j<heightinitialized;j++)
        {
            world[i][j] = 0;
        }
        
    
    }
    
    
    /**
     * 0s represent air
     * 1s represent solid objects
     **/
     
}

void placelimits(void)
{
    //Boundaries are 10 layers thick to accomodate draw distance of 10.
    for(k=0;l<height; l++)
    {
        for(q=0; q<10;q++)
        {
        world[q][l] = 1;
        world[(length -1) - q][l]= 1;
        }
    }

    for(l=0;k<length;k++)
    {
        for(r=0;r<10;r++)
        {
         world[k][(height -1) - r] = 1;
         world[k][r] = 1;
        }
    }
    /**
     * 0s represent air
     * 1s represent solid objects
     **/
}

void placeobjects(void)
{
    //test object. not included in final release. 
    for(o = 1; o<4; o++)
    {
        world[(o * 20)][5] = 1;
        
        world[(o * 20)+1][5] = 1;
        world[(o * 20)-1][5] = 1;
        
        world[(o * 20)][6] = 1;
        world[(o * 20)][4] = 1;
        
    }
    
}

void initializeplayer(void)
{
    //set starting position of player and track it globally using pointers for x and y position on map.
    world[15][15] = 2;
    worldpositionx = 15;
    worldpositiony = 15;
    *wpy = worldpositiony;
    *wpx = worldpositionx;
    
}

void gravity(void)
{
    //if in air, fall until character reaches ground.
    worldpositionx = *wpx;
    worldpositiony = *wpy;
    
    if(world[worldpositionx+1][worldpositiony] == 0)
    {
        worldpositionx = worldpositionx +1;
        *wpx = worldpositionx;
        world[worldpositionx][worldpositiony] = 2;
        world[worldpositionx-1][worldpositiony] = 0;
    }
}


void move(void)
{ 
    //sideways movement and jumping. 
    movement[0][0] = GetInt();
    worldpositionx = *wpx;
    worldpositiony = *wpy;
    world[worldpositionx][worldpositiony] = 2; 
    
    if((movement[0][0] == 4) && (world[worldpositionx][worldpositiony-1] == 0))
    {
        worldpositiony = worldpositiony -1; 
        *wpy = worldpositiony;
        world[worldpositionx][worldpositiony] = 2;
        world[worldpositionx][worldpositiony+1] = 0;
    }
    else if((movement[0][0] == 6) && (world[worldpositionx][worldpositiony+1] == 0))
    {
        worldpositiony = worldpositiony +1; 
        *wpy = worldpositiony;
        world[worldpositionx][worldpositiony] = 2;
        world[worldpositionx][worldpositiony-1] = 0;
    }
    else if((movement[0][0] == 8) && (world[worldpositionx-3][worldpositiony] != 1) && (world[worldpositionx-2][worldpositiony] != 1) && (world[worldpositionx-1][worldpositiony] != 1) && (world[worldpositionx-3][worldpositiony+3] != 1) && (world[worldpositionx-3][worldpositiony+2] != 1)&& (world[worldpositionx-3][worldpositiony+1] != 1))
    {
        worldpositionx = worldpositionx -3;
        worldpositiony = worldpositiony +3; 
        *wpy = worldpositiony;
        *wpx = worldpositionx;
        world[worldpositionx][worldpositiony] = 2;
        world[worldpositionx+3][worldpositiony-3] = 0;
        //animation
        world[worldpositionx][worldpositiony-2] = 8;
        world[worldpositionx+1][worldpositiony-3] = 8;
        world[worldpositionx+2][worldpositiony-3] = 8;
    } 
    if((movement[0][0] == 7) && (world[worldpositionx][worldpositiony-3] == 0))
    {
        worldpositiony = worldpositiony -3; 
        *wpy = worldpositiony;
        world[worldpositionx][worldpositiony] = 2;
        //animation
        world[worldpositionx][worldpositiony+3] = 8;
        world[worldpositionx][worldpositiony+2] = 8;
        world[worldpositionx][worldpositiony+1] = 8;
    }
    else if((movement[0][0] == 9) && (world[worldpositionx][worldpositiony+3] == 0))
    {
        worldpositiony = worldpositiony +3; 
        *wpy = worldpositiony;
        world[worldpositionx][worldpositiony] = 2;
        //animation
        world[worldpositionx][worldpositiony-3] = 8;
        world[worldpositionx][worldpositiony-2] = 8;
        world[worldpositionx][worldpositiony-1] = 8;
        
    }
    else
    {
        printf("This move can't be complete, there is an obstacle. Try again. \n");
    }
    
}

void instructions(void)
{
    //present game instructions.
    printf("Instructions: \n Win Condition: Reach the flag at the end of the right end of the obstacle course to win.\n Controls: Press '4' (<-) and '6' (->) to move side to side, press '7'(<--) and '9'(-->) to dash side to side. Press '8' to jump. (HINT: Use jump if you get stuck in the hole)\n Please input your move (and press enter): \n");
}

void spikes(void)
{
    //draw spikes.
    for(i=0;i<10;i++)
    {
        world[20][70 + i] = 3;
    }
    
    world[20][50] = 3;
    world[20][51] = 3;
    
    //includes a ditch
    world[20][25] = 0;
    world[21][25] = 0;
    world[20][26] = 0;
    world[21][26] = 0;
    world[20][27] = 0;
    world[21][27] = 0;
    
}

void platforms(void)
{
    //draw platforms. 
    for(i=0;i<15;i++)
    {
        world[17][67 + i] = 1;
    }
}

void finishline(void)
{
    //draw win condition area
    for(i=0;i<5;i++)
    {
        world[15+i][108] = 4;
    
        for(j=0;j<5;j++)
        {
                    world[15+i][108-j] = 4;
        }
    }
    //draw the flag
    world[18][105] = 5;
    world[19][105] = 6;
    //leave some roon in win condition area so person can walk there since a 0 (empty) is required for movement. 
    world[19][104] = 0;
    world[19][103] = 0;
    //finish-line ground padding looks different. For visual clarity.
    world[20][103] = 7;
    world[20][104] = 7;
    world[20][105] = 7;
    world[20][106] = 7;
    world[20][107] = 7;
    
}

void removeanimations(void)
{
    //remove animations.
    for(i=0;i<lengthinitialized;i++) 
    {
        for(j=0;j<heightinitialized;j++)
        {
            if(world[i][j] == 8)
            {
            world[i][j] = 0;
            }
        }
        
    
    }    
}

/**
Code Ends.
*/



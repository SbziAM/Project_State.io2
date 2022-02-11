#ifndef __HEADER_INIT_H__
#define __HEADER_INIT_H__

#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;
const int SPEED = 100; /* pixels/second */

typedef struct Soldier
{
  float pos_x ;
  float pos_y ;
  float vel_x ;
  float vel_y ;
  int region_x ;
  int region_y ;
  int flag ;
  bool is_attack ;
  int attack_to_x ;
  int attack_to_y ;
} Soldier;

#define CELL_NUM  6
const int MaxRegion = CELL_NUM * CELL_NUM;
const int MaxSoldier = 7;
const int RegionWidth = SCREEN_WIDTH / CELL_NUM ;
const int RegionHeight = SCREEN_HEIGHT / CELL_NUM ;
const int soldierWidth = SCREEN_WIDTH / (12*CELL_NUM) ;
const int soldierHeight = SCREEN_HEIGHT / (12*CELL_NUM) ;

int flag[ CELL_NUM ][ CELL_NUM ];
int cnt[ CELL_NUM ][ CELL_NUM ];
int attack[ CELL_NUM ][ CELL_NUM ];
int cnt_attack[ CELL_NUM ][ CELL_NUM ]; /* number of soldiers that should attack */
int timer[ CELL_NUM ][ CELL_NUM ]; /* send soldiers every timer's loop */
int speed[ 3 ] ;
int timer_potion_1[ 3 ] ;
int timer_potion_4[ 3 ] ;
int timer_potion_6[ 3 ] ;
int timer_potion_7[ 3 ] ;

Soldier kolsoldiers[ 100 ]; /* soldiers that are attacking */
Soldier soldd ;

char s1[ 20 ] ;

char your_name[ 50 ];
char names[ 100 ][ 50 ];
int Scores[ 100 ];
int cnt_users = 0 ;

bool is_exist[ 1000 ];
int is_potion[ 3 ] ;/* if the player has a potion or not , if yes what? */

int potion_pos_x[ 9 ] ;
int potion_pos_y[ 9 ] ;
int timer_potion[ 9 ] ; 
int t1 = 5 ;
int t4 = 5 ;
int t6 = 5 ;
int t7 = 5 ;
int mulspeed_my = 2 ;
int mulspeed_enemy = 2 ;

int roundd = 0;
int cnt_myregions = 0 ;
int cnt_enregions = 0 ;
int cnt_bitaradregions = 0;
int cnt_soldiers = 0; 
int Score = 0 ;
int target_x ;
int target_y ;

float dis_x ;
float dis_y ;
float dis ;

FILE* fpread ;
FILE* fpwrite ;

SDL_Window *sdlWindow = NULL ;
SDL_Renderer* sdlRenderer = NULL ;
SDL_Surface* screenSurface = NULL ;
TTF_Font* sdlFont = NULL ;
SDL_bool shallExit = SDL_FALSE;
SDL_Texture* texx = NULL ;
SDL_Rect* destt = NULL ;
SDL_Texture* pot1 = NULL ;
SDL_Texture* pot4 = NULL ;
SDL_Texture* pot6 = NULL ;
SDL_Texture* pot7 = NULL ;
SDL_Rect dest_pot1 ;
SDL_Rect dest_pot4 ;
SDL_Rect dest_pot6 ;
SDL_Rect dest_pot7 ;

int min(int a, int b);
int max(int a, int b) ;
int mod(int a, int b);
bool inBetween(int number, int min, int max);

#endif
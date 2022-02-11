// In the name of Allah
// Ya Ali

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

#include "Init.h"

void swap( int* x1 , int* x2 ){
  int tmp = *x1 ;
  *x1 = *x2 ;
  *x2 = tmp ;
}

bool is_equal( char* s1 , char* s2 ){
  int po = 0;
  while( 1 ){
    if( s1[ po ] != s2[ po ] )return false ;
    if( (s1[ po ] == '\0') && (s2[ po ] == '\0') )return true ;
    po ++;
  }
}

int initialize(){
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 0; 
  }
  //Creat window
  sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if( sdlWindow == NULL ){
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    SDL_Quit();
    return 0; 
  }
  //Creat the Renderer
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if( !sdlRenderer ){
    printf("error creating renderer : %s\n" , SDL_GetError() );
    SDL_DestroyWindow( sdlWindow );
    SDL_Quit();
    return 0;
  }
  //Get window surface
  screenSurface = SDL_GetWindowSurface( sdlWindow );
  if( screenSurface == NULL ){
    printf( "screen Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
    SDL_DestroyRenderer( sdlRenderer );
    SDL_DestroyWindow( sdlWindow );
    SDL_Quit();
    return 0; 
  } 
  if( TTF_Init() == -1 ){
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    return 0;
  }
  return 1;
}


bool is_accident(float x1 , float y1 , float x2 , float y2){
    float dis_x = x2 - x1 ;
    float dis_y = y2 - y1 ;
    float dis = sqrt( (dis_x * dis_x) + (dis_y * dis_y) );
    if( dis < 5 )return true;
    else return false ;
} 

void drawBox(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color) {
    Sint16 width1 = SCREEN_WIDTH * y / CELL_NUM;
    Sint16 height1 = SCREEN_HEIGHT * x / CELL_NUM;
    boxColor(sdlRenderer, width1, height1, width1 + SCREEN_WIDTH / CELL_NUM, height1 + SCREEN_HEIGHT / CELL_NUM, color);
}

void drawCircle(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color) {
    Sint16 width1 = SCREEN_WIDTH * y / CELL_NUM;
    Sint16 height1 = SCREEN_HEIGHT * x / CELL_NUM;
    Sint16 ry = SCREEN_WIDTH / (2 * CELL_NUM), rx = SCREEN_HEIGHT / (2 * CELL_NUM);
    filledEllipseColor(sdlRenderer, width1 + ry, height1 + rx, ry/2 , rx/2 , color);
}

void drawSoldier(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color) {
    Sint16 width1 = y ;
    Sint16 height1 = x ;
    Sint16 ry = SCREEN_WIDTH / (2 * CELL_NUM), rx = SCREEN_HEIGHT / (2 * CELL_NUM);
    filledEllipseColor(sdlRenderer, width1 , height1 , ry/6 , rx/6 , color);
}

int Load_media( const char *address1 , SDL_Texture** tex , SDL_Rect* dest ){
  SDL_Surface* img = NULL ;
  img = IMG_Load( address1 );
  if( img == NULL ){
    printf( "Unable to load image %s! SDL Error: %s\n", "/home/amirmohammad/projects/Project_mabani/graphic-work-shop/snake.bmp", SDL_GetError() );
    SDL_DestroyRenderer( sdlRenderer );
    SDL_DestroyWindow( sdlWindow );
    SDL_Quit();
    return 0;
  } 
  *tex = SDL_CreateTextureFromSurface( sdlRenderer , img );
	//Get rid of old loaded surface
	SDL_FreeSurface( img );
  SDL_QueryTexture( *tex , NULL , NULL , &(dest->w) , &(dest->h) );
  dest->x = 0 ;
  dest->y = 0 ;
  return 1;
}

int LoadText( char* text , SDL_Color textcolor , SDL_Texture** tex , SDL_Rect* dest ){
   SDL_Surface* textsurface = NULL ; 
   if( sdlFont == NULL ){
     printf("Font doesn't found! Error: %s\n" , SDL_GetError() );
     return 0;
   }
   textsurface = TTF_RenderText_Solid( sdlFont , text , textcolor ) ;
   if( textsurface == NULL ){
     printf("Unable to load text %s! Error: %s\n" , text , SDL_GetError() );
     SDL_DestroyRenderer( sdlRenderer );
     SDL_DestroyWindow( sdlWindow );
     SDL_Quit();
     return 0;
   }
   *tex = SDL_CreateTextureFromSurface( sdlRenderer , textsurface );
   if(*tex == NULL){
     printf("Unable to load texture! Error: %s\n" , SDL_GetError() );
     SDL_DestroyRenderer( sdlRenderer );
     SDL_DestroyWindow( sdlWindow );
     SDL_Quit();
     return 0;     
   }
   SDL_FreeSurface( textsurface );
   SDL_QueryTexture( *tex , NULL , NULL , &(dest->w) , &(dest->h) );
   dest->x = (SCREEN_WIDTH - dest->w )/2 ;
   dest->y = (SCREEN_HEIGHT - dest->h )/2 ;
   return 1;
}

int LoadText2( char* text , SDL_Color textcolor ){
   SDL_Surface* textsurface = NULL ; 
   if( sdlFont == NULL ){
     printf("Font doesn't found! Error: %s\n" , SDL_GetError() );
     return 0;
   }
   textsurface = TTF_RenderText_Solid( sdlFont , text , textcolor ) ;
   if( textsurface == NULL ){
     printf("Unable to load text %s! Error: %s\n" , text , SDL_GetError() );
     SDL_DestroyRenderer( sdlRenderer );
     SDL_DestroyWindow( sdlWindow );
     SDL_Quit();
     return 0;
   }
   SDL_DestroyTexture( texx );
   texx = SDL_CreateTextureFromSurface( sdlRenderer , textsurface );
   if(texx == NULL){
     printf("Unable to load texture! Error: %s\n" , SDL_GetError() );
     SDL_DestroyRenderer( sdlRenderer );
     SDL_DestroyWindow( sdlWindow );
     SDL_Quit();
     return 0;       
   }
   SDL_FreeSurface( textsurface );
   return 1;   
}

int len( char* s1 ){
  int po = 0;
  while( s1[ po ] != '\0' ){
    po ++ ;
  }
  return po ;
}

int get_name( char* inputtext ){
  SDL_Color textcolor = { 0 , 0 , 0 , 0xFF };
  SDL_Event e;
  SDL_Texture* TextTex = NULL;
  SDL_Rect TextDest ;
  strcpy( inputtext , "Write your name" );
  if( !LoadText( inputtext , textcolor , &TextTex , &TextDest ) ) return 0;
  SDL_StartTextInput();
  bool endtext = false;
  while( !endtext ){
    bool renderText = false;
    
    while( SDL_PollEvent( &e ) != 0 ){
      if( e.type == SDL_QUIT ){
        shallExit = SDL_TRUE ;
        endtext = true ;
        break;
      }
      else if( e.type == SDL_KEYDOWN ){
        //Handle backspace
        int len1 = len( inputtext );
        if( e.key.keysym.sym == SDLK_BACKSPACE && len1 > 0 ){
          //lop off character
          inputtext[ len1-1 ] = '\0' ;
          renderText = true;
        }
        //Handle copy
        else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ){
          SDL_SetClipboardText( inputtext );
        }
        //Handle paste
        else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ){
          strcat( inputtext , SDL_GetClipboardText() );
          renderText = true;
        }
        else if( e.key.keysym.scancode == SDL_SCANCODE_RETURN ){
          endtext = true ;
          break;
        }
      }
      else if( e.type == SDL_TEXTINPUT ){
        //Not copy or pasting
        if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) ){
          //Append character
          strcat( inputtext , e.text.text ) ;
          renderText = true;
        }
      }      
    }

    if( renderText ){
      if( len( inputtext ) > 0 ){
        SDL_DestroyTexture( TextTex );
        LoadText( inputtext , textcolor , &TextTex , &TextDest );
      }
      else{
        SDL_DestroyTexture( TextTex );
        LoadText( " " , textcolor , &TextTex , &TextDest );
      }
    }
    //present
    SDL_SetRenderDrawColor( sdlRenderer , 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(sdlRenderer); 
    SDL_RenderCopy( sdlRenderer , TextTex , NULL , &TextDest );
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay( 1000 / FPS );
  }
  SDL_StopTextInput();
  return 1;
}

void randomperm( int* a , int sz ){
  for(int i = 0 ; i < sz ; i ++){
    int x = rand()%(sz-i) ;
    int ind = sz-x-1 ;
    swap( &a[ i ] , &a[ ind ] );
  }
}

int region_center_x( int x , int y ){
  /* x <==> HEIGHT , y <==> WIDTH */
  return (x*RegionHeight)+(RegionHeight/2) ; 
}

int region_center_y( int x , int y ){
  /* x <==> HEIGHT , y <==> WIDTH */
  return (y*RegionWidth)+(RegionWidth/2) ; 
}

void InitGame( bool is_random ){ 
   speed[ 1 ] = SPEED ;
   speed[ 2 ] = SPEED ;
   for(int i = 1 ; i <= 8 ; i ++){
     potion_pos_x[ i ] = -1 ;
     potion_pos_y[ i ] = -1 ;
     timer_potion[ i ] = 0 ;
   }
   is_potion[ 1 ] = -1 ;
   is_potion[ 2 ] = -1 ;
   for(int i = 1 ; i <= 2 ; i ++){
     timer_potion_1[ i ] = 0;
     timer_potion_4[ i ] = 0;
     timer_potion_6[ i ] = 0;
     timer_potion_7[ i ] = 0;
   }
 if( is_random ){
   cnt_myregions = rand()%(MaxRegion - 1);
   if( cnt_myregions == 0 )cnt_myregions = 1;
   cnt_enregions = rand()%(MaxRegion-cnt_myregions) ;
   if( cnt_enregions == 0 )cnt_enregions = 1;
   cnt_bitaradregions = rand()%(MaxRegion-cnt_myregions-cnt_enregions);
   if( cnt_bitaradregions == 0 )cnt_bitaradregions = 1;
   
   int per[ MaxRegion ];
   for(int i = 0 ; i < MaxRegion ; i ++)per[ i ] = i ;
   randomperm( per , MaxRegion );  
   int po = 0 ;
  
  for(int i = 0 ; i < cnt_myregions ; i ++){
     int va = per[ po ];
     int y = va/CELL_NUM ;
     int x = va%CELL_NUM ;
     flag[ y ][ x ] = 1 ;
     attack[ y ][ x ] = -1 ;
     cnt_attack[ y ][ x ] = 0;
     cnt[ y ][ x ] = MaxSoldier ;
     timer[ y ][ x ] = 0;
     po ++;  
  }
  for(int i = 0 ; i < cnt_enregions ; i ++){
     int va = per[ po ];
     int y = va/CELL_NUM ;
     int x = va%CELL_NUM ;
     flag[ y ][ x ] = 2 ;
     attack[ y ][ x ] = -1 ;
     cnt_attack[ y ][ x ] = 0;
     cnt[ y ][ x ] = MaxSoldier ;
     timer[ y ][ x ] = 0;
     po ++;  
  }
  for(int i = 0 ; i < cnt_bitaradregions ; i ++){
     int va = per[ po ];
     int y = va/CELL_NUM ;
     int x = va%CELL_NUM ;
     flag[ y ][ x ] = 0 ;
     attack[ y ][ x ] = -1 ;
     cnt_attack[ y ][ x ] = 0;
     cnt[ y ][ x ] = MaxSoldier ;
     timer[ y ][ x ] = 0;
     po ++;  
  }
  while( po < MaxRegion ){
     int va = per[ po ];
     int y = va/CELL_NUM ;
     int x = va%CELL_NUM ;
     flag[ y ][ x ] = -1 ;
     cnt[ y ][ x ] = 0 ;
     po ++;       
  }
 }
 else{
   //Preproduced map
    cnt_myregions = MaxRegion/3 ;
    cnt_bitaradregions = MaxRegion/3 ;
    cnt_enregions = MaxRegion/3 ;
    for(int i = 0 ; i < CELL_NUM ; i ++){
      for(int j = 0 ; j < (CELL_NUM/3) ; j ++ ){ 
        flag[ i ][ j ] = 1 ;
        attack[ i ][ j ] = -1 ;
        cnt_attack[ i ][ j ] = 0 ;
        cnt[ i ][ j ] = MaxSoldier ;
        timer[ i ][ j ] = 0;
      }
    } 
    for(int i = 0 ; i < CELL_NUM ; i ++){
      for(int j = (CELL_NUM/3) ; j < (2*(CELL_NUM/3)) ; j ++ ){ 
        flag[ i ][ j ] = 0 ;
        attack[ i ][ j ] = -1 ;
        cnt_attack[ i ][ j ] = 0;
        cnt[ i ][ j ] = MaxSoldier ;
        timer[ i ][ j ] = 0;
      }
    } 
    for(int i = 0 ; i < CELL_NUM ; i ++){
      for(int j = (2*(CELL_NUM/3)) ; j < CELL_NUM ; j ++ ){ 
        flag[ i ][ j ] = 2 ;
        attack[ i ][ j ] = -1 ;
        cnt_attack[ i ][ j ] = 0;
        cnt[ i ][ j ] = MaxSoldier ;
        timer[ i ][ j ] = 0;
      }
    } 
 }
}

void getregion( int x , int y , int* reg_x , int* reg_y ){
  /* x <==> WIDTH , y <==> HEIGHT */
  *reg_y = x/RegionWidth ;
  *reg_x = y/RegionHeight;
}
void drawregion(){
  for(int i = 0 ; i < CELL_NUM ; i ++){
   for(int j = 0 ; j < CELL_NUM ; j ++){
     if( flag[ i ][ j ] == 0 ){
       drawBox( sdlRenderer , i , j , 0xff00ff00 ); 
       drawCircle( sdlRenderer , i , j , 0xff008800 );
     }
     else if( flag[ i ][ j ] == 1 ){
       drawBox( sdlRenderer , i , j , 0xff0000ff ); 
       drawCircle( sdlRenderer , i , j , 0xff000088 );
     }
     else if( flag[ i ][ j ] == 2 ){
       drawBox( sdlRenderer , i , j , 0xffff0000 ); 
       drawCircle( sdlRenderer , i , j , 0xff880000 );
     }
   }
  }
  SDL_Color color = { 0 , 0 , 0 , 0xFF };
  if( is_potion[ 1 ] != -1 ){
    if(is_potion[ 1 ] == 1 )LoadText2("Potion 1 is running for you" , color ) ;
    else if(is_potion[ 1 ] == 4 )LoadText2("Potion 4 is running for you" , color ) ; 
    else if(is_potion[ 1 ] == 6 )LoadText2("Potion 6 is running for you" , color ) ; 
    else if(is_potion[ 1 ] == 7 )LoadText2("Potion 7 is running for you" , color ) ; 
    SDL_QueryTexture( texx , NULL , NULL , &(destt->w) , &(destt->h) );
    destt->y = 5 ;
    destt->x = 5 ;
    SDL_RenderCopy( sdlRenderer , texx , NULL , destt );
    SDL_DestroyTexture( texx );
  } 
  if( is_potion[ 2 ] != -1 ){
    if(is_potion[ 2 ] == 1 )LoadText2("Potion 1 is running for enemy" , color ) ;
    else if(is_potion[ 2 ] == 4 )LoadText2("Potion 4 is running for enemy" , color ) ; 
    else if(is_potion[ 2 ] == 6 )LoadText2("Potion 6 is running for enemy" , color ) ; 
    else if(is_potion[ 2 ] == 7 )LoadText2("Potion 7 is running for enemy" , color ) ; 
    SDL_QueryTexture( texx , NULL , NULL , &(destt->w) , &(destt->h) );
    destt->y = 5 ;
    destt->x = SCREEN_WIDTH - destt->w - 5 ;
    SDL_RenderCopy( sdlRenderer , texx , NULL , destt );
    SDL_DestroyTexture( texx ) ;
  }
}

void drawSoldiers(){
  for(int i = 0 ; i < cnt_soldiers ; i ++){
    Uint32 color = 0xff000000 ;
    if( kolsoldiers[ i ].flag == 1 )color = 0xff000044 ;
    else if( kolsoldiers[ i ].flag == 2 )color = 0xff440000 ;
    drawSoldier( sdlRenderer , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y , color );
  }
}

void buildSoldier(){
   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
       if( (flag[ i ][ j ] == -1) || (flag[ i ][ j ] == 0) )continue ;       
       if( cnt[ i ][ j ] >= MaxSoldier )continue ;
       cnt[ i ][ j ] ++;
     }
   }
}

void updateSoldiers(){
   for(int i = 0 ; i < cnt_soldiers ; i ++)is_exist[ i ] = true;
   //potion
     for(int i = 0 ; i < cnt_soldiers ; i ++){
       if( is_potion[ kolsoldiers[ i ].flag ] != -1 )continue ;
       if( (potion_pos_x[ 1 ] != -1) && (potion_pos_y[ 1 ] != -1) && (is_accident( (float)potion_pos_x[ 1 ] , (float)potion_pos_y[ 1 ] , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y)) ){
         is_potion[ kolsoldiers[ i ].flag ] = 1 ;
         timer_potion_1[ kolsoldiers[ i ].flag ] = t1*FPS ;
         potion_pos_x[ 1 ] = -1;
         potion_pos_y[ 1 ] = -1;
         speed[ kolsoldiers[ i ].flag ] *= mulspeed_my ;   
         //printf("get potion 1\n") ;
       }
       else if( (potion_pos_x[ 4 ] != -1) && (potion_pos_y[ 4 ] != -1) && (is_accident( (float)potion_pos_x[ 4 ] , (float)potion_pos_y[ 4 ] , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y)) ){
         is_potion[ kolsoldiers[ i ].flag ] = 4 ;
         timer_potion_4[ kolsoldiers[ i ].flag ] = t4*FPS ;
         potion_pos_x[ 4 ] = -1;
         potion_pos_y[ 4 ] = -1;
         int flg2 = (kolsoldiers[ i ].flag == 1 ) ? 2 : 1 ;
         speed[ flg2 ] *= mulspeed_enemy ;
         //printf("get potion 4\n") ;   
       }
       else if( (potion_pos_x[ 6 ] != -1) && (potion_pos_y[ 6 ] != -1) && (is_accident( (float)potion_pos_x[ 6 ] , (float)potion_pos_y[ 6 ] , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y)) ){
         is_potion[ kolsoldiers[ i ].flag ] = 6 ;
         timer_potion_6[ kolsoldiers[ i ].flag ] = t6*FPS ;
         potion_pos_x[ 6 ] = -1 ;
         potion_pos_y[ 6 ] = -1 ;
         //printf("get potion 6\n") ;   
       }
       else if( (potion_pos_x[ 7 ] != -1) && (potion_pos_y[ 7 ] != -1) && (is_accident( (float)potion_pos_x[ 7 ] , (float)potion_pos_y[ 7 ] , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y)) ){
         is_potion[ kolsoldiers[ i ].flag ] = 7 ;
         timer_potion_7[ kolsoldiers[ i ].flag ] = t7*FPS ;
         potion_pos_x[ 7 ] = -1 ;
         potion_pos_y[ 7 ] = -1 ;
         //printf("get potion 7\n") ;      
       }
     }
   //to target
   for(int i = 0 ; i < cnt_soldiers ; i ++){
    if( is_accident( region_center_x( kolsoldiers[ i ].attack_to_x , kolsoldiers[ i ].attack_to_y ) , region_center_y( kolsoldiers[ i ].attack_to_x , kolsoldiers[ i ].attack_to_y ) , kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y) ){
      is_exist[ i ] = false;
      int flg1 = kolsoldiers[ i ].flag ;
      int flg2 = flag[ kolsoldiers[ i ].attack_to_x ][ kolsoldiers[ i ].attack_to_y ];
      if( (flg1 == flg2) || (is_potion[ flg2 ] == 6) ){
        cnt[ kolsoldiers[ i ].attack_to_x ][ kolsoldiers[ i ].attack_to_y ] ++;
      }
      else{
        if( cnt[ kolsoldiers[ i ].attack_to_x ][ kolsoldiers[ i ].attack_to_y ]  == 0 ){
          int reg_x = kolsoldiers[ i ].attack_to_x ;
          int reg_y = kolsoldiers[ i ].attack_to_y ;
          flag[ reg_x ][ reg_y ] = flg1 ;
          attack[ reg_x ][ reg_y ] = -1 ;
          cnt_attack[ reg_x ][ reg_y ] = 0;
          cnt[ reg_x ][ reg_y ] = 1 ;
          timer[ reg_x ][ reg_y ] = 0;
        }
        else{
          cnt[ kolsoldiers[ i ].attack_to_x ][ kolsoldiers[ i ].attack_to_y ] -- ;
        }
      }
    }
   }

   // accidents
   for(int i = 0 ; i < cnt_soldiers-1 ; i ++){
     for(int j = i+1 ; j < cnt_soldiers ; j ++){
       int flg1 = kolsoldiers[ i ].flag ;
       int flg2 = kolsoldiers[ j ].flag ;
       float dis_x = kolsoldiers[ i ].pos_x - kolsoldiers[ j ].pos_x ;
       float dis_y = kolsoldiers[ i ].pos_y - kolsoldiers[ j ].pos_y ;
       float dis = sqrt( (dis_x * dis_x) + (dis_y * dis_y) );
       if( (is_accident(kolsoldiers[ i ].pos_x , kolsoldiers[ i ].pos_y , kolsoldiers[ j ].pos_x , kolsoldiers[ j ].pos_y)) && (flg1 != flg2) ){
         is_exist[ i ] = false ;
         is_exist[ j ] = false ;
       }
     }
   } 
   
   int tmp = cnt_soldiers ;
   for(int i = 0 ; i < tmp ; i ++){
     if( !is_exist[ i ] ){
       cnt_soldiers --;
     }
   }

   Soldier copy[ cnt_soldiers ];
   int po = 0 ;
   for(int i = 0 ; i < tmp ; i ++){
     if( is_exist[ i ] ){
       copy[ po ] = kolsoldiers[ i ] ;
       po ++;
     }
   }
   for(int i = 0 ; i < cnt_soldiers ; i ++){
     kolsoldiers[ i ] = copy[ i ] ; 
   }
}

void make_string( int va , char* s1 , int cntt){ 
  for(int i = cntt-1 ; i >= 0 ; i --){
    int x = va%10 ;
    s1[ i ] = '0'+x ; 
    va /= 10 ;  
  }
}

int drawnumbers(){
  SDL_Color color = { 0 , 0 , 0 , 0xFF };
  for(int i = 0 ; i < CELL_NUM ; i ++){
    for(int j = 0 ; j < CELL_NUM ; j ++){
      if( flag[ i ][ j ] == -1 )continue ;
      int va = cnt[ i ][ j ];
      int cntt = 0 , va2 = va ;
      while( va2 ){
       va2 /= 10 ;
       cntt ++ ;
      } 
      if( va == 0 )cntt = 1;
      make_string( va , s1 , cntt ) ;
      s1[ cntt ] = '\0' ;
      if( !LoadText2( s1 , color ) )return 0; 
      SDL_QueryTexture( texx , NULL , NULL , &(destt->w) , &(destt->h) );
      destt->y = region_center_x( i , j ) - ((destt->h)/2) ;
      destt->x = region_center_y( i , j ) - ((destt->w)/2) ;
      SDL_RenderCopy( sdlRenderer , texx , NULL , destt );
      SDL_DestroyTexture( texx ) ;
    }
  }
  return 1;
}

void move_soldiers(){
  for(int i = 0 ; i < cnt_soldiers ; i ++){
    soldd = kolsoldiers[ i ];
    target_x = region_center_x( soldd.attack_to_x , soldd.attack_to_y );
    target_y = region_center_y( soldd.attack_to_x , soldd.attack_to_y );
    dis_x = target_x - soldd.pos_x ;
    dis_y = target_y - soldd.pos_y ;
    dis = sqrt( (dis_x * dis_x) + (dis_y * dis_y) );
    kolsoldiers[ i ].vel_x = speed[ soldd.flag ] * ( dis_x / dis ) ;
    kolsoldiers[ i ].vel_y = speed[ soldd.flag ] * ( dis_y / dis ) ;
    kolsoldiers[ i ].pos_x += (kolsoldiers[ i ].vel_x / FPS) ;
    kolsoldiers[ i ].pos_y += (kolsoldiers[ i ].vel_y / FPS) ;
  }
}

bool finish(){
  bool is[ 3 ] ;
  is[ 0 ] = false ;
  is[ 1 ] = false ;
  is[ 2 ] = false ;
  for(int i = 0 ; i < CELL_NUM ; i ++){
    for(int j = 0 ; j < CELL_NUM ; j ++){
      if( flag[ i ][ j ] == -1 )continue ;
      is[ flag[ i ][ j ] ] = true;
    }
  }
  
  int ind ;
  for(int i = 0 ; i < cnt_users ; i ++){
    if( is_equal( your_name , names[ i ] ) ){
      ind = i ;
      break ;
    }
  }

  if( !is[ 2 ] ){
    //win
    Scores[ ind ] ++; 
    return 1 ;
  }
  else if( !is[ 1 ] ){
    //lose
    if( Scores[ ind ] > 0 )Scores[ ind ] -- ;
    return 1;
  }
  else return 0;
}

void buildPotion(){
//1
  if( timer_potion[ 1 ] == 0 ){
    potion_pos_x[ 1 ] = -1 ;
    potion_pos_y[ 1 ] = -1 ;
    if( (rand()%100) == 0 ){
      potion_pos_x[ 1 ] = (rand()%(SCREEN_HEIGHT-(2*RegionHeight)))+RegionHeight ; 
      potion_pos_y[ 1 ] = (rand()%(SCREEN_WIDTH-(2*RegionWidth)))+RegionWidth ; 
      timer_potion[ 1 ] ++;
      //printf("Potion1 is there: (%d , %d)\n" , potion_pos_x[ 1 ] , potion_pos_y[ 1 ] );
    } 
  } 
  else{
    timer_potion[ 1 ] ++;
    timer_potion[ 1 ] %= (10*FPS) ;
  }
//4
  if( timer_potion[ 4 ] == 0 ){
    potion_pos_x[ 4 ] = -1 ;
    potion_pos_y[ 4 ] = -1 ;
    if( (rand()%100) == 0 ){
      potion_pos_x[ 4 ] = (rand()%(SCREEN_HEIGHT-(2*RegionHeight)))+RegionHeight ; 
      potion_pos_y[ 4 ] = (rand()%(SCREEN_WIDTH-(2*RegionWidth)))+RegionWidth ; 
      timer_potion[ 4 ] ++;
      //printf("Potion4 is there: (%d , %d)\n" , potion_pos_x[ 4 ] , potion_pos_y[ 4 ] );
    } 
  } 
  else{
    timer_potion[ 4 ] ++;
    timer_potion[ 4 ] %= (10*FPS) ;
  }
//6
  if( timer_potion[ 6 ] == 0 ){
    potion_pos_x[ 6 ] = -1 ;
    potion_pos_y[ 6 ] = -1 ;
    if( (rand()%100) == 0 ){
      potion_pos_x[ 6 ] = (rand()%(SCREEN_HEIGHT-(2*RegionHeight)))+RegionHeight ; 
      potion_pos_y[ 6 ] = (rand()%(SCREEN_WIDTH-(2*RegionWidth)))+RegionWidth ; 
      timer_potion[ 6 ] ++;
      //printf("Potion6 is there: (%d , %d)\n" , potion_pos_x[ 6 ] , potion_pos_y[ 6 ] );
    } 
  } 
  else{
    timer_potion[ 6 ] ++;
    timer_potion[ 6 ] %= (10*FPS) ;
  }
//7
  if( timer_potion[ 7 ] == 0 ){
    potion_pos_x[ 7 ] = -1 ;
    potion_pos_y[ 7 ] = -1 ;
    if( (rand()%100) == 0 ){
      potion_pos_x[ 7 ] = (rand()%(SCREEN_HEIGHT-(2*RegionHeight)))+RegionHeight ; 
      potion_pos_y[ 7 ] = (rand()%(SCREEN_WIDTH-(2*RegionWidth)))+RegionWidth ; 
      timer_potion[ 7 ] ++;
      //printf("Potion7 is there: (%d , %d)\n" , potion_pos_x[ 7 ] , potion_pos_y[ 7 ] );
    } 
  } 
  else{
    timer_potion[ 7 ] ++;
    timer_potion[ 7 ] %= (10*FPS) ;
  }     
}

void drawPotion(){
  if( potion_pos_x[ 1 ] != -1 && potion_pos_y[ 1 ] != -1 ){
    dest_pot1.y = potion_pos_x[ 1 ] - ((dest_pot1.h)/2);
    dest_pot1.x = potion_pos_y[ 1 ] - ((dest_pot1.w)/2) ;
    SDL_RenderCopy( sdlRenderer , pot1 , NULL , &dest_pot1 );
  }
  if( potion_pos_x[ 4 ] != -1 && potion_pos_y[ 4 ] != -1 ){
    dest_pot4.y = potion_pos_x[ 4 ] - ((dest_pot4.h)/2)  ;
    dest_pot4.x = potion_pos_y[ 4 ] - ((dest_pot4.w)/2)  ;
    SDL_RenderCopy( sdlRenderer , pot4 , NULL , &dest_pot4 );
  }
  if( potion_pos_x[ 6 ] != -1 && potion_pos_y[ 6 ] != -1 ){
    dest_pot6.y = potion_pos_x[ 6 ] - ((dest_pot6.h)/2)  ;
    dest_pot6.x = potion_pos_y[ 6 ] - ((dest_pot6.w)/2)  ;
    SDL_RenderCopy( sdlRenderer , pot6 , NULL , &dest_pot6 );
  }
  if( potion_pos_x[ 7 ] != -1 && potion_pos_y[ 7 ] != -1 ){
    dest_pot7.y = potion_pos_x[ 7 ] - ((dest_pot7.h)/2)  ;
    dest_pot7.x = potion_pos_y[ 7 ] - ((dest_pot7.w)/2)  ;
    SDL_RenderCopy( sdlRenderer , pot7 , NULL , &dest_pot7 );
  }  
}

void update_PotionTimers(){
    if( is_potion[ 1 ] != -1 ){
      int pot = is_potion[ 1 ];
      if( pot == 1 ){
        timer_potion_1[ 1 ] -- ;
        if( timer_potion_1[ 1 ] == 0 ){
          is_potion[ 1 ] = -1 ;
          speed[ 1 ] /= mulspeed_my ;
        } 
      }
      else if( pot == 4 ){
        timer_potion_4[ 1 ] -- ;
        if( timer_potion_4[ 1 ] == 0 ){
          is_potion[ 1 ] = -1 ;
          speed[ 2 ] /= mulspeed_enemy ;
        } 
      }
      else if( pot == 6 ){
        timer_potion_6[ 1 ] -- ;
        if( timer_potion_6[ 1 ] == 0 ){
          is_potion[ 1 ] = -1 ;
        }        
      }
      else if( pot == 7 ){
        timer_potion_7[ 1 ] -- ;
        if( timer_potion_7[ 1 ] == 0 ){
          is_potion[ 1 ] = -1 ;
        }        
      }
    }   
    if( is_potion[ 2 ] != -1 ){
      int pot = is_potion[ 2 ];
      if( pot == 1 ){
        timer_potion_1[ 2 ] -- ;
        if( timer_potion_1[ 2 ] == 0 ){
          is_potion[ 2 ] = -1 ;
          speed[ 2 ] /= mulspeed_my ;
        } 
      }
      else if( pot == 4 ){
        timer_potion_4[ 2 ] -- ;
        if( timer_potion_4[ 2 ] == 0 ){
          is_potion[ 2 ] = -1 ;
          speed[ 1 ] /= mulspeed_enemy ;
        } 
      }
      else if( pot == 6 ){
        timer_potion_6[ 2 ] -- ;
        if( timer_potion_6[ 2 ] == 0 ){
          is_potion[ 2 ] = -1 ;
        }        
      }
      else if( pot == 7 ){
        timer_potion_7[ 2 ] -- ;
        if( timer_potion_7[ 2 ] == 0 ){
          is_potion[ 2 ] = -1 ;
        }        
      }
    }   
}

void updateAttacks(){
    for(int i = 0 ; i < CELL_NUM ; i ++){
      for(int j = 0 ; j < CELL_NUM ; j ++){
        if( (flag[ i ][ j ] == -1) || (flag[ i ][ j ] == 0 ) )continue ;
        if( attack[ i ][ j ] == -1 )continue ;
        if( (cnt_attack[ i ][ j ] == 0) || (cnt[ i ][ j ] == 0) ){
          attack[ i ][ j ] = -1 ;
          cnt_attack[ i ][ j ] = 0;
          timer[ i ][ j ] = 0;
          continue ;
        }
        if( (timer[ i ][ j ] % (FPS/4)) != 0 ){
          timer[ i ][ j ] ++;
          timer[ i ][ j ] %= (FPS/4) ;
          continue ;
        }
        //printf("updating attack\n");

        int attacked_region_x = attack[ i ][ j ]/CELL_NUM ;
        int attacked_region_y = attack[ i ][ j ]%CELL_NUM ;        

        cnt[ i ][ j ] -- ;
        cnt_attack[ i ][ j ] --;

        soldd.pos_x = region_center_x( i , j );
        soldd.pos_y = region_center_y( i , j );
        soldd.vel_x = 0 ;
        soldd.vel_y = 0 ;
        soldd.region_x = i ;
        soldd.region_y = j ;
        soldd.flag = flag[ i ][ j ] ;
        soldd.is_attack = true ;
        soldd.attack_to_x = attacked_region_x ;
        soldd.attack_to_y = attacked_region_y ;
        
        kolsoldiers[ cnt_soldiers ] = soldd ;
        cnt_soldiers ++;

        timer[ i ][ j ] ++;
        timer[ i ][ j ] %= (FPS/4) ;
      }
    }     
}

int get_near( int reg_x , int reg_y , int is_attack_to_you ){
   int flg = 2 ;
   int ans_x = -1 ;
   int ans_y = -1 ;
   float mn = 1000 ;
   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
      if( flag[ i ][ j ] != flg )continue ;
      if( i == reg_x && j == reg_y )continue ;
       float dis_x = reg_x - i ;
       float dis_y = reg_y - j ;
       float dis = sqrt( (dis_x*dis_x) + (dis_y*dis_y) );
       if( (dis < mn) ){
        if( !is_attack_to_you || cnt[ i ][ j ] >= (MaxSoldier/2) ){ 
          mn = dis ;
          ans_x = i ;
         ans_y = j ; 
        }
       }
     }
   }

   if( ans_x == -1 && ans_y == -1 )return -1 ;
   return (ans_x*CELL_NUM)+ans_y ;
}

void AI(){
  if( is_potion[ 1 ] == 7 ){
   // defensing
   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
       if( flag[ i ][ j ] == 1 && attack[ i ][ j ] != -1 ){
         int reg_x = attack[ i ][ j ]/CELL_NUM ;
         int reg_y = attack[ i ][ j ]%CELL_NUM ;
         if( flag[ reg_x ][ reg_y ] == 2 ){
           int reg1 = get_near( reg_x , reg_y , 0 ) ;
           if( reg1 == -1 )continue ;
           attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = (reg_x*CELL_NUM)+reg_y;
           cnt_attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = cnt[ reg1/CELL_NUM ][ reg1%CELL_NUM ] ;                               
           return ;
         }
       }
     }
   }
   return ;
  }

   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
       if( flag[ i ][ j ] == 1 && attack[ i ][ j ] != -1 ){
         int reg_x = attack[ i ][ j ]/CELL_NUM ;
         int reg_y = attack[ i ][ j ]%CELL_NUM ;
         if( flag[ reg_x ][ reg_y ] == 2 ){
           int reg1 = get_near( reg_x , reg_y , 0 ) ;
           int reg2 = get_near( i , j , 1 ) ;
           if( reg1 == reg2 ){
             if( reg1 == -1 )continue ;
             attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = (reg_x*CELL_NUM)+reg_y;
             cnt_attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = cnt[ reg1/CELL_NUM ][ reg1%CELL_NUM ] ;
             return ;
           } 
           else{
             if( reg1 != -1 ){
               attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = (reg_x*CELL_NUM)+reg_y;
               cnt_attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = cnt[ reg1/CELL_NUM ][ reg1%CELL_NUM ] ;                    
             } 
             if( reg2 != -1 ){
               attack[ reg2/CELL_NUM ][ reg2%CELL_NUM ] = (i*CELL_NUM)+j;
               cnt_attack[ reg2/CELL_NUM ][ reg2%CELL_NUM ] = cnt[ reg2/CELL_NUM ][ reg2%CELL_NUM ] ;
             }
             return ;
           }
         }
         else{
           int reg1 = get_near( i , j , 1 ) ;
           if( reg1 == -1 )continue ;
           attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = (i*CELL_NUM)+j;
           cnt_attack[ reg1/CELL_NUM ][ reg1%CELL_NUM ] = cnt[ reg1/CELL_NUM ][ reg1%CELL_NUM ] ;
           return ;
         } 
       }
     }
   }

   int reg_x = -1 , reg_y = -1 ;
   int mn = 1000 ;

   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
       if( flag[ i ][ j ] == 0 ){
         if( cnt[ i ][ j ] < mn ){
           mn = cnt[ i ][ j ];
           reg_x = i ;
           reg_y = j ;
         }
       }
     }
   }
   if( reg_x != -1 && reg_y != -1 ){
     //printf("AI attack to (%d , %d)\n" , reg_x , reg_y ); 
     int reg = get_near( reg_x , reg_y , 0 ) ;
     //printf("From (%d , %d)\n" , reg/CELL_NUM , reg%CELL_NUM );
     attack[ reg/CELL_NUM ][ reg%CELL_NUM ] = (reg_x*CELL_NUM)+reg_y;
     cnt_attack[ reg/CELL_NUM ][ reg%CELL_NUM ] = cnt[ reg/CELL_NUM ][ reg%CELL_NUM ] ;                    
     return ;
   }
   
   for(int i = 0 ; i < CELL_NUM ; i ++){
     for(int j = 0 ; j < CELL_NUM ; j ++){
       if( flag[ i ][ j ] == 1 ){
         if( cnt[ i ][ j ] < mn ){
           mn = cnt[ i ][ j ];
           reg_x = i ;
           reg_y = j ;
         }
       }
     }
   }
   //printf("AI attack to (%d , %d)\n" , reg_x , reg_y );    
   int reg = get_near( reg_x , reg_y , 1 ) ;
   //printf("From (%d , %d)\n" , reg/CELL_NUM , reg%CELL_NUM );
   attack[ reg/CELL_NUM ][ reg%CELL_NUM ] = (reg_x*CELL_NUM)+reg_y;
   cnt_attack[ reg/CELL_NUM ][ reg%CELL_NUM ] = cnt[ reg/CELL_NUM ][ reg%CELL_NUM ] ;                    
   return ;
}

bool show_menu1(){
  Uint32 time ;
  int mouse_x , mouse_y ;
  int num = 2 ;
  char* lables[ num ];
  lables[ 0 ] = "New Game";
  lables[ 1 ] = "Scoreboard";
  SDL_Surface* menus_surface[ num ] ;
  bool selected[ num ] ;
  selected[ 0 ] = false;
  selected[ 1 ] = false;
  SDL_Color color[ 2 ] = {{0,0,0} , {255,0,0}} ;
  SDL_Rect pos[ 2 ];
  SDL_Event e ;

  menus_surface[ 0 ] = TTF_RenderText_Solid( sdlFont , lables[ 0 ] , color[ 0 ]);
  menus_surface[ 1 ] = TTF_RenderText_Solid( sdlFont , lables[ 1 ] , color[ 0 ]);
  
  while( 1 ){
    time = SDL_GetTicks();
    while (SDL_PollEvent(&e)) {
      if( e.type == SDL_QUIT ){
        for(int i = 0 ; i < num ; i ++)SDL_FreeSurface( menus_surface[ i ] ) ;
        shallExit = true ;
        return 0;
      }
      else if( e.type == SDL_MOUSEMOTION ){
        mouse_x = e.motion.x ;
        mouse_y = e.motion.y ;
        for(int i = 0 ; i < num ; i ++){
          if( mouse_x >= pos[ i ].x && mouse_x <= (pos[ i ].x + pos[ i ].w) && mouse_y >= pos[ i ].y && mouse_y <= (pos[ i ].y + pos[ i ].h) ){
            if( !selected[ i ] ){
              selected[ i ] = 1;
              SDL_FreeSurface( menus_surface[ i ] );
              menus_surface[ i ] = TTF_RenderText_Solid( sdlFont , lables[ i ] , color[ 1 ]);
            }
          }
          else{
            if( selected[ i ] ){
              selected[ i ] = 0;
              SDL_FreeSurface( menus_surface[ i ] );
              menus_surface[ i ] = TTF_RenderText_Solid( sdlFont , lables[ i ] , color[ 0 ]);
            } 
          }
        }
      }
      else if( e.type == SDL_MOUSEBUTTONDOWN ){
        mouse_x = e.button.x ;
        mouse_y = e.button.y ;
        for(int i = 0 ; i < num ; i ++){
          if( mouse_x >= pos[ i ].x && mouse_x <= (pos[ i ].x + pos[ i ].w) && mouse_y >= pos[ i ].y && mouse_y <= (pos[ i ].y + pos[ i ].h) ){
             return i ;
          }
        }
      }
    } 
    SDL_SetRenderDrawColor( sdlRenderer , 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(sdlRenderer); 
    for(int i = 0 ; i < num ; i ++){
      SDL_DestroyTexture( texx );
      texx = SDL_CreateTextureFromSurface( sdlRenderer , menus_surface[ i ] );    
      SDL_QueryTexture( texx , NULL , NULL , &(pos[ i ].w) , &(pos[ i ].h) ) ;
      if( i == 0 ){
        pos[ i ].x = (SCREEN_WIDTH/2)-(pos[ i ].w/2) ;
        pos[ i ].y = (SCREEN_HEIGHT/2)-pos[ i ].h ;
      }
      else{
        pos[ i ].x = (SCREEN_WIDTH/2)-(pos[ i ].w/2) ;
        pos[ i ].y = (SCREEN_HEIGHT/2) ;
      }
      SDL_RenderCopy( sdlRenderer , texx , NULL , &pos[ i ] );
    }
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay( 1000 / FPS );
  }
}

bool show_menu2(){
  Uint32 time ;
  int mouse_x , mouse_y ;
  int num = 2 ;
  char* lables[ num ];
  lables[ 0 ] = "Preproduced Map";
  lables[ 1 ] = "Random Map";
  SDL_Surface* menus_surface[ num ] ;
  bool selected[ num ] ;
  selected[ 0 ] = false;
  selected[ 1 ] = false;
  SDL_Color color[ 2 ] = {{0,0,0} , {255,0,0}} ;
  SDL_Rect pos[ 2 ];
  SDL_Event e ;

  menus_surface[ 0 ] = TTF_RenderText_Solid( sdlFont , lables[ 0 ] , color[ 0 ]);
  menus_surface[ 1 ] = TTF_RenderText_Solid( sdlFont , lables[ 1 ] , color[ 0 ]);
  
  while( 1 ){
    time = SDL_GetTicks();
    while (SDL_PollEvent(&e)) {
      if( e.type == SDL_QUIT ){
        for(int i = 0 ; i < num ; i ++)SDL_FreeSurface( menus_surface[ i ] ) ;
        shallExit = true ;
        return 0;
      }
      else if( e.type == SDL_MOUSEMOTION ){
        mouse_x = e.motion.x ;
        mouse_y = e.motion.y ;
        for(int i = 0 ; i < num ; i ++){
          if( mouse_x >= pos[ i ].x && mouse_x <= (pos[ i ].x + pos[ i ].w) && mouse_y >= pos[ i ].y && mouse_y <= (pos[ i ].y + pos[ i ].h) ){
            if( !selected[ i ] ){
              selected[ i ] = 1;
              SDL_FreeSurface( menus_surface[ i ] );
              menus_surface[ i ] = TTF_RenderText_Solid( sdlFont , lables[ i ] , color[ 1 ]);
            }
          }
          else{
            if( selected[ i ] ){
              selected[ i ] = 0;
              SDL_FreeSurface( menus_surface[ i ] );
              menus_surface[ i ] = TTF_RenderText_Solid( sdlFont , lables[ i ] , color[ 0 ]);
            } 
          }
        }
      }
      else if( e.type == SDL_MOUSEBUTTONDOWN ){
        mouse_x = e.button.x ;
        mouse_y = e.button.y ;
        for(int i = 0 ; i < num ; i ++){
          if( mouse_x >= pos[ i ].x && mouse_x <= (pos[ i ].x + pos[ i ].w) && mouse_y >= pos[ i ].y && mouse_y <= (pos[ i ].y + pos[ i ].h) ){
             return i ;
          }
        }
      }
    } 
    SDL_SetRenderDrawColor( sdlRenderer , 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(sdlRenderer); 
    for(int i = 0 ; i < num ; i ++){
      SDL_DestroyTexture( texx );
      texx = SDL_CreateTextureFromSurface( sdlRenderer , menus_surface[ i ] );    
      SDL_QueryTexture( texx , NULL , NULL , &(pos[ i ].w) , &(pos[ i ].h) ) ;
      if( i == 0 ){
        pos[ i ].x = (SCREEN_WIDTH/2)-(pos[ i ].w/2) ;
        pos[ i ].y = (SCREEN_HEIGHT/2)-pos[ i ].h ;
      }
      else{
        pos[ i ].x = (SCREEN_WIDTH/2)-(pos[ i ].w/2) ;
        pos[ i ].y = (SCREEN_HEIGHT/2) ;
      }
      SDL_RenderCopy( sdlRenderer , texx , NULL , &pos[ i ] );
    }
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay( 1000 / FPS );
  }
}

void load_Scoreboard(){
  char ch[ 100 ];
  bool is_exist = false ;
  while( fscanf( fpread , "%[^\n] " , ch ) != EOF ){
     int po = 0; 
     while( ch[ po ] != ':' ){
       names[ cnt_users ][ po ] = ch[ po ] ;
       po ++;
     }
     names[ cnt_users ][ po ] = '\0' ;
     if( is_equal( your_name , names[ cnt_users ] ) )is_exist = true ;
     po += 2 ;
     Scores[ cnt_users ] = 0; 
     while( ch[ po ] != '\0' ){
       int x = ch[ po ]-'0' ;
       Scores[ cnt_users ] *= 10 ;
       Scores[ cnt_users ] += x ;
       po ++;
     }
     cnt_users ++ ;
  }
  if( !is_exist ){
    strcpy( names[ cnt_users ] , your_name ) ;
    Scores[ cnt_users ] = 0 ;
    cnt_users ++ ; 
  }
}

void apply_user( int i , int* la_h){
    char kol[ 100 ] ;
    strcpy( kol , names[ i ] );
    strcat( kol , ": " );
    char adad[ 20 ] ;
    int va = Scores[ i ] , cntt = 0 ;
    while( va ){
      cntt ++;
      va /= 10 ;
    }
    if( Scores[ i ] == 0 )cntt = 1; 
    va = Scores[ i ] ;
    for(int j = cntt-1 ; j >= 0 ; j --){
      int x = (va%10);
      char ch = '0'+x ;
      adad[ j ] = ch ; 
      va /= 10;
    }
    adad[ cntt ] = '\0' ;
    strcat( kol , adad ) ;
  SDL_Color color = { 0 , 0 , 0 , 0xFF };  
  LoadText2( kol , color );
  SDL_Rect poss ;
  SDL_QueryTexture( texx , NULL , NULL , &poss.w , &poss.h ) ;
  poss.x = 0 ;
  poss.y = *la_h ;
  *la_h += poss.h ;
  SDL_RenderCopy( sdlRenderer , texx , NULL , &poss );
}

bool show_Scoreboard(){ 
  SDL_Event e ;
  while( 1 ){
    while (SDL_PollEvent(&e)) {
      if( e.type == SDL_QUIT ){
        shallExit = true ;
        return 0;
      }
      else if( e.type == SDL_KEYDOWN ){
        if( e.key.keysym.sym == SDLK_ESCAPE ){
          return 1;
        } 
      }
    }
    SDL_SetRenderDrawColor( sdlRenderer , 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(sdlRenderer); 
    int la_h = 0 ;
    for(int i = 0 ; i < cnt_users ; i ++){
       apply_user( i , &la_h );
    }
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay( 1000 / FPS );
  }
}

void update_scoreboard(){
  for(int i = 0 ; i < cnt_users-1 ; i ++){
    for( int j = i+1 ; j < cnt_users ; j ++){
      if( Scores[ i ] < Scores[ j ] ){
        char* tmp ;
        strcpy( tmp , names[ i ] ) ;
        strcpy( names[ i ] , names[ j ] );
        strcpy( names[ j ] , tmp ) ;
        
       int va = Scores[ i ] ;
       Scores[ i ] = Scores[ j ];
       Scores[ j ] = va ;
      }
    }
  }  
}

void update_scoreboardFile(){
  char kol[ 5000 ];
  strcpy( kol , "" );
  for(int i = 0 ; i < cnt_users ; i ++){
    strcat( kol , names[ i ] );
    strcat( kol , ": " );
    char adad[ 20 ] ;
    int va = Scores[ i ] , cntt = 0 ;
    while( va ){
      cntt ++;
      va /= 10 ;
    }
    if( Scores[ i ] == 0 )cntt = 1; 
    va = Scores[ i ] ;
    for(int j = cntt-1 ; j >= 0 ; j --){
      int x = (va%10);
      char ch = '0'+x ;
      adad[ j ] = ch ; 
      va /= 10;
    }
    adad[ cntt ] = '\0' ;
    strcat( kol , adad ) ;
    strcat( kol , "\n" ) ;
  }
  fprintf( fpwrite , "%s" , kol );
}

int main(){  
  srand( time( NULL ) ); 
  if( !initialize() )return 0;
  sdlFont = TTF_OpenFont("/home/amirmohammad/projects/Project_mabani/IRNazanin.ttf" , 20);
  destt = (SDL_Rect*)malloc(sizeof(SDL_Rect));  
  //Load splash image 
  if( !Load_media( "/home/amirmohammad/projects/Project_mabani/pot1.jpg" , &pot1 , &dest_pot1) )return 0;
  if( !Load_media( "/home/amirmohammad/projects/Project_mabani/pot4.jpg" , &pot4 , &dest_pot4) )return 0;
  if( !Load_media( "/home/amirmohammad/projects/Project_mabani/pot6.jpg" , &pot6 , &dest_pot6) )return 0;
  if( !Load_media( "/home/amirmohammad/projects/Project_mabani/pot7.jpg" , &pot7 , &dest_pot7) )return 0;    
  dest_pot1.h /= 2 ;
  dest_pot1.w /= 2 ;
  dest_pot4.h /= 2 ;
  dest_pot4.w /= 2 ;
  dest_pot6.h /= 2 ;
  dest_pot6.w /= 2 ;
  dest_pot7.h /= 2 ;
  dest_pot7.w /= 2 ;
  
  get_name( your_name );
  fpread = fopen( "/home/amirmohammad/projects/Project_mabani/Scoreboard.txt" , "r" );
  if( fpread == NULL ){
    printf("Can't read Scoreboard!\n");
    return 0;
  }
  load_Scoreboard();
 
while( shallExit == SDL_FALSE ){  
  bool what = show_menu1();

  if( what == 1 ){
    //Scoreboard
    bool act = show_Scoreboard() ;
    if( !act )break ;
    else continue ;       
  }
  else if( what == 0 ){ 
   //New Game 
   InitGame( show_menu2() );
   int selected_region_x = -1;
   int selected_region_y = -1;
   int mouse_x , mouse_y ;
   int buttons ;
   int reg_x , reg_y ;
  while ( shallExit == SDL_FALSE ) {
    // draw the background
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
  //------------------------------------------    
   //drawing
    buildPotion();    
    if( roundd%FPS == 0 )buildSoldier();
    updateSoldiers();
    if( finish() )break ;
    drawregion();
    drawPotion();
    drawSoldiers();
    if( !drawnumbers() )return 0;
   //new attack
    buttons = SDL_GetMouseState( &mouse_x , &mouse_y );
    getregion( mouse_x , mouse_y , &reg_x , &reg_y );
    if( (buttons & SDL_BUTTON( SDL_BUTTON_LEFT )) && ( flag[ reg_x ][ reg_y ] != -1 ) ){
       if( (selected_region_x == -1) || (selected_region_y == -1) ){
          if( flag[ reg_x ][ reg_y ] == 1 ){
            selected_region_x = reg_x ;
            selected_region_y = reg_y ;
            //printf("%d --- %d :> %d .... selected successfully\n" , reg_x , reg_y , flag[ reg_x ][ reg_y ] ) ;
          }   
       }
       else{
         if( (selected_region_x != reg_x) || (selected_region_y != reg_y) ){
          if( is_potion[ flag[ reg_x ][ reg_y ] ] != 7 ){  
            attack[ selected_region_x ][ selected_region_y ] = (reg_x*CELL_NUM)+reg_y ;
            cnt_attack[ selected_region_x ][ selected_region_y ] = cnt[ selected_region_x ][ selected_region_y ];
            //printf("%d --- %d :> %d .... attack is happening\n" , reg_x , reg_y , flag[ reg_x ][ reg_y ] ) ;
            selected_region_x = -1 ;
            selected_region_y = -1 ;
          }
         }
       }
    }
  //AI
    if(roundd%FPS == 0 )AI();
  //update attacks
    updateAttacks();
  // move soldiers
    move_soldiers() ;  
  //update timers of potions 
    update_PotionTimers();

    roundd ++;
    roundd %= FPS ;
  //------------------------------------------  
    //SDL_RenderCopy( sdlRenderer , pot7 , NULL , &dest_pot7 );
    SDL_RenderPresent(sdlRenderer);
    SDL_Delay( 1000 / FPS );
  
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) /* this function remove the event that put it in the sdlEvent */) {
      if( sdlEvent.type == SDL_QUIT ){
        shallExit = SDL_TRUE ;
        break;
      }
    }
  }
//Update Scoreboard
  update_scoreboard();  
 }
 if( shallExit == SDL_TRUE ){
   break;
 }
}
// update_ScoreboardFile
  update_scoreboard();
  fpwrite = fopen( "/home/amirmohammad/projects/Project_mabani/Scoreboard.txt" , "w" );
  if( fpwrite == NULL ){
    printf("Can't write in Scoreboard!\n");
    return 0 ;
  } 
  update_scoreboardFile();

// Closing 
  SDL_FreeSurface( screenSurface );
  SDL_DestroyWindow( sdlWindow );
  SDL_DestroyRenderer( sdlRenderer );
  SDL_DestroyTexture( texx );
  SDL_DestroyTexture( pot1 );
  SDL_DestroyTexture( pot4 );
  SDL_DestroyTexture( pot6 );
  SDL_DestroyTexture( pot7 );
  TTF_CloseFont( sdlFont );
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  fclose( fpread ) ;
  fclose( fpwrite );
 
  return 0;
}
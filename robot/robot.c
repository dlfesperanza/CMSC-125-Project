/*
robotfindskittens
CMSC 125 T-5L

Authors:
ESPERANZA, Dannah Louise
LEGASPI, Stephanie
*/

#include "../../sdk/dexsdk.h"

void draw_line(int col, int row);
void init_board();
void move_player();
void setup_level();
void display_desc();
void init_desc();
void empty_desc();
void start_game();
void display_home();
char instruction();
char difficulty();
char display_gameover();

#define maxrow 20
#define maxcol 77
#define max_objects 30
#define str_len 128
#define pause_length 5
#define max_desc 30
#define num_objects 10

#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define robot '#'
#define default_obj "+++"

/*variable declarations*/
char screen_grid[maxrow][maxcol];
char board[maxrow][maxcol];
char desc_arr[max_desc][str_len] = {
                                      "mitten", "puzzle", "zigzag", "apples", "grapes",
                                      "flower", "clouds", "paints", "cactus", "iphone",
                                      "noodle", "string", "folder", "powder", "poster",
                                      "lights", "bottle", "turtle", "tv set", "laptop",
                                      "pencil", "lizard", "leaves", "friend", "orange",
                                      "plates", "mirror", "pillow", "cherry", "heater"
                                    };
char descriptions[num_objects][str_len];
char object_arr[max_objects] = {'!','@','$','%','^','&','*',
                                '~','`','(',')','{','}','-','_',
                                '=','+','[',']','|','/',';',':',
                                '"',',','<','>','?','¢','£'};
char direction;
int x_pos, y_pos;
int obstacles=4, firstpress, max_kittens=0, kittens_found=0, obj_num;

int main(){
  char keypress;

  do{
    display_home();
      gotoxy(1, 1);
      gotoxy(33,15); textcolor(YELLOW); printf("[1] Start");
      gotoxy(33,16); textcolor(YELLOW); printf("[2] Instruction");
      gotoxy(33,17); textcolor(YELLOW); printf("[3] Exit");
      gotoxy(1,1);
      keypress = (char)getch();
    switch(keypress){
      case '1': keypress = difficulty();
                if(keypress=='0') break;
                else{
                  start_game();
                  while(keypress!='0') keypress = display_gameover();
                }
                break;
      case '2': while(keypress!='0'){
                  keypress = instruction();   
                }
                break;
      case '3': clrscr(); return 0; break;
    }
  }while(keypress!='3');
}

/*main function for game play*/
void start_game(){
  char keypress;
   /* restart game loop */
    //srand(time());
  empty_desc();
  init_board();
  setup_level();
  init_desc();
  do{
    
   // delay(pause_length);

    if (kb_ready()){
      gotoxy(1,1);
      keypress=(char)getch();
      if((keypress==right_key)||(keypress==left_key)||
         (keypress==up_key)||(keypress==down_key))
        direction = keypress;
    }

    
    
    if(direction != 'n' && direction != 'x'){
      gotoxy(1,1);
      move_player();
      setup_level();
      gotoxy(1, 1);
    }
    
    
    direction='n';
    if (kittens_found == max_kittens) break;

  }while (keypress!='x');

  kittens_found = 0;

  
  clrscr();
  return 0;
}

/*randomizes the position of the objects in the board*/
void init_board(){
  int row, col;
  int i;

  x_pos=rand()%maxrow;
  y_pos=rand()%maxcol;
  screen_grid[x_pos][y_pos]=robot;

  for(i=0;i<obj_num;i++){
    srand(time(NULL));
    row= rand()%maxrow;
    col= rand()%maxcol;

    while(screen_grid[row][col]!=' '){
      row= rand()%maxrow;
      col= rand()%maxcol;
    }
   
    screen_grid[row][col]=object_arr[i];
  }
}

/*displays the home panel*/
void display_home(){
  int row,col;
  int i;

  for(row=0;row<maxrow;row++)
    for(col=0;col<maxcol;col++)
     screen_grid[row][col]= ' ';
  
  draw_line(1,1);
  for(row=0;row<maxrow;row++){
    gotoxy(1,row+2);
    textcolor(YELLOW); printf("|");
    textcolor(WHITE);
    for(col=0;col<maxcol;col++){
      printf("%c",screen_grid[row][col]);
    }
    textcolor(YELLOW); printf("|");
  }

  
  gotoxy(23,6); textcolor(YELLOW);  printf("R O B O T  F I N D S  K I T T E N S");
  gotoxy(17,9); textcolor(YELLOW);  printf("[-]                .::. .::.              |\\_/|     ");
  gotoxy(17,10); textcolor(YELLOW); printf("(+)=C              :::::::::              |o o|__   ");
  gotoxy(17,11); textcolor(YELLOW); printf("| |                ':::::::'              =-*-=__\\ ");
  gotoxy(17,12); textcolor(YELLOW); printf("OOO                  ':::'               c_c__(___)");
  
  gotoxy(1, 1);
 
  draw_line(1,maxrow+2);
}

/*displays the instruction panel*/
char instruction(){
  int row,col;
  int i;
  char keypress;

  for(row=0;row<maxrow;row++)
    for(col=0;col<maxcol;col++)
     screen_grid[row][col]= ' ';
  
  draw_line(1,1);
  for(row=0;row<maxrow;row++){
    gotoxy(1,row+2);
    textcolor(YELLOW); printf("|");
    textcolor(WHITE);
    for(col=0;col<maxcol;col++){
      printf("%c",screen_grid[row][col]);
    }
    textcolor(YELLOW); printf("|");
  }

  
  gotoxy(30,6); textcolor(YELLOW);  printf("I N S T R U C T I O N");
  gotoxy(17,9); textcolor(YELLOW);  printf("[-]                .::. .::.              |\\_/|     ");
  gotoxy(17,10); textcolor(YELLOW); printf("(+)=C              :::::::::              |o o|__   ");
  gotoxy(17,11); textcolor(YELLOW); printf("| |                ':::::::'              =-*-=__\\ ");
  gotoxy(17,12); textcolor(YELLOW); printf("OOO                  ':::'               c_c__(___)");

  gotoxy(13,14); textcolor(YELLOW); printf("You are the robot (#). Your goal is to find the kittens");  
  gotoxy(13,15); textcolor(YELLOW); printf("among the pool of characters. You can determine if an item");
  gotoxy(13,16); textcolor(YELLOW); printf("is a kitten from their description which is shown at the bottom");
  gotoxy(13,17); textcolor(YELLOW); printf("of the screen once you 'bumped' into them. Best of luck!");

  gotoxy(1, 1);
  gotoxy(33,19); textcolor(YELLOW); printf("[0] Back to Menu");
  keypress = (char)getch();
  gotoxy(1, 1);
 
  draw_line(1,maxrow+2);
  return keypress;
}

/*displays the difficulty panel where the player can choose difficulty*/
char difficulty(){
  char keypress;
  int row,col;
  int i;

  for(row=0;row<maxrow;row++)
    for(col=0;col<maxcol;col++)
     screen_grid[row][col]= ' ';
  
  draw_line(1,1);
  for(row=0;row<maxrow;row++){
    gotoxy(1,row+2);
    textcolor(YELLOW); printf("|");
    textcolor(WHITE);
    for(col=0;col<maxcol;col++){
      printf("%c",screen_grid[row][col]);
    }
    textcolor(YELLOW); printf("|");
  }

  gotoxy(30,6); textcolor(YELLOW);  printf("D I F F I C U L T Y");
  gotoxy(17,9); textcolor(YELLOW);  printf("[-]                .::. .::.              |\\_/|     ");
  gotoxy(17,10); textcolor(YELLOW); printf("(+)=C              :::::::::              |o o|__   ");
  gotoxy(17,11); textcolor(YELLOW); printf("| |                ':::::::'              =-*-=__\\ ");
  gotoxy(17,12); textcolor(YELLOW); printf("OOO                  ':::'               c_c__(___)");

  gotoxy(33,14); textcolor(YELLOW); printf("[1] Easy");  
  gotoxy(33,15); textcolor(YELLOW); printf("[2] Medium");
  gotoxy(33,16); textcolor(YELLOW); printf("[3] Hard");
  gotoxy(33,18); textcolor(YELLOW); printf("[0] Back to Menu");

  gotoxy(1, 1);
  keypress = (char)getch();
  gotoxy(1, 1);

  switch(keypress){
    case '1': obj_num = 10; max_kittens = 3; break;
    case '2': obj_num = 20; max_kittens = 6; break;
    case '3': obj_num = 30; max_kittens = 10; break;
  }

  gotoxy(1, 1);
 
  draw_line(1,maxrow+2);
  return keypress;
}

/*displays gameover panel; called when user has quit the game or when all kittens are found*/
char display_gameover(){
  int row,col;
  int i;
  char keypress;

  for(row=0;row<maxrow;row++)
    for(col=0;col<maxcol;col++)
     screen_grid[row][col]= ' ';
  
  draw_line(1,1);
  for(row=0;row<maxrow;row++){
    gotoxy(1,row+2);
    textcolor(YELLOW); printf("|");
    textcolor(WHITE);
    for(col=0;col<maxcol;col++){
      printf("%c",screen_grid[row][col]);
    }
    textcolor(YELLOW); printf("|");
  }

  
  gotoxy(32,6); textcolor(YELLOW);  printf("G A M E  O V E R");
  gotoxy(17,9); textcolor(YELLOW);  printf("[-]                .::. .::.              |\\_/|     ");
  gotoxy(17,10); textcolor(YELLOW); printf("(+)=C              :::::::::              |o o|__   ");
  gotoxy(17,11); textcolor(YELLOW); printf("| |                ':::::::'              =-*-=__\\ ");
  gotoxy(17,12); textcolor(YELLOW); printf("OOO                  ':::'               c_c__(___)");
  
   gotoxy(1, 1);
  gotoxy(33,19); textcolor(YELLOW); printf("[0] Back to Menu");
  keypress = (char)getch();
  gotoxy(1, 1);


 
  draw_line(1,maxrow+2);
  return keypress;
}

/*prints the 2d array of the map which contains the objects*/
void setup_level(){
  int row,col;
  int i;
  
  draw_line(1,1);
  for(row=0;row<maxrow;row++){
    gotoxy(1,row+2);
    textcolor(YELLOW); printf("|");
    textcolor(WHITE);
    for(col=0;col<maxcol;col++){
      if (screen_grid[row][col]=='#'){
        textcolor(YELLOW); printf("%c",screen_grid[row][col]);
      }else if (col%9 == 0){
        textcolor(LIGHTGREEN); printf("%c",screen_grid[row][col]);
      }else if (col%8 == 0){
        textcolor(LIGHTRED); printf("%c",screen_grid[row][col]);
      }else if (col%7 == 0){
        textcolor(LIGHTCYAN); printf("%c",screen_grid[row][col]);
      }else if (col%6 == 0){
        textcolor(MAGENTA); printf("%c",screen_grid[row][col]);
      }else if (col%5 == 0){
        textcolor(CYAN); printf("%c",screen_grid[row][col]);
      }else if (col%4 == 0){
        textcolor(BLUE); printf("%c",screen_grid[row][col]);
      }else if (col%3 == 0){
        textcolor(LIGHTMAGENTA); printf("%c",screen_grid[row][col]);
      }else if (col%2 == 0){
        textcolor(GREEN); printf("%c",screen_grid[row][col]);
      }else{
        textcolor(LIGHTGRAY); printf("%c",screen_grid[row][col]);
      }
    }
    textcolor(YELLOW); printf("|");
  }

  gotoxy(1, 1);
 
  draw_line(1,maxrow+2);
   
  gotoxy(2,maxrow+3);  textcolor(YELLOW); printf("CONTROLS");
  gotoxy(4,maxrow+4); printf("%c - UP\t  %c - LEFT\t  x - QUIT", up_key, left_key);
  gotoxy(4,maxrow+5); printf("%c - DOWN\t%c - RIGHT", down_key, right_key);
  gotoxy(65,maxrow+3); printf("Kittens: %d/%d\n", kittens_found, max_kittens);
  
  gotoxy(1, 1);
  
}

/*displays the top and bottom border*/
void draw_line(int col, int row){
  gotoxy(col,row); textcolor(YELLOW);
  for (col=0;col<maxcol+2;col++) printf("-");
  gotoxy(1, 1);
}

/*initializes the descriptions of the objects in random;*/
void init_desc(){
  int i, r, rndm;
  for(i=0; i<num_objects; i++){
    strcpy(descriptions[i], default_obj);
  }

  for(i=0;i<max_kittens;i++){
    srand(time(NULL));
    r=rand()%obj_num;
    while(strcmp(descriptions[r], default_obj)!=0 ){
      r=rand()%obj_num;
    }
    strcpy(descriptions[i], "kitten");
  }

  for(i=0;i<obj_num;i++){
    if(strcmp(descriptions[i], default_obj)==0 ){
      r=rand()%obj_num;
      while(strcmp(descriptions[i], desc_arr[r])==0){
        r=rand()%obj_num;
      }
      strcpy(descriptions[i], desc_arr[r]);
    }
  } 
}

/*displays the footer panel which contains the controls, kitten count and description of objects*/
void display_desc(int num){
  empty_desc();
  textcolor(LIGHTGRAY); gotoxy(50,maxrow+3); printf("%s", descriptions[num]);

  gotoxy(2,maxrow+3);  textcolor(YELLOW); printf("CONTROLS");
  gotoxy(4,maxrow+4); printf("%c - UP\t  %c - LEFT\t  x - QUIT", up_key, left_key);
  gotoxy(4,maxrow+5); printf("%c - DOWN\t%c - RIGHT", down_key, right_key);
  gotoxy(65,maxrow+3); printf("Kittens: %d/%d\n", kittens_found, max_kittens);
}

/*resets the footer field for reprinting*/
void empty_desc(){
  int col;
  //textcolor(LIGHTBLUE);
  gotoxy(1,maxrow+3);
  for(col=40;col<maxcol;col++)
     screen_grid[maxrow+3][col] = ' ';
  gotoxy(1,1);
}

/*moves the player around the map according to the controls*/
void move_player(){
  int i, j;

  

  for(i=0; i<maxrow; i++){
    for(j=0; j<maxcol; j++){
      if (screen_grid[i][j] == '#'){
        x_pos = i;
        y_pos = j;
        break;
      }
    }
  }

  gotoxy(1,1);

  switch(direction){
    case(up_key):
      if (screen_grid[x_pos-1][y_pos] == ' '){
        screen_grid[x_pos][y_pos] = ' ';
        x_pos -= 1;
        screen_grid[x_pos][y_pos] = '#';
        empty_desc();
      }else{
        for(i=0;i<obj_num;i++){
          if (screen_grid[x_pos-1][y_pos] == object_arr[i]){
            
            display_desc(i);
            if (strcmp(descriptions[i], "kitten") == 0){
              kittens_found++;
              screen_grid[x_pos-1][y_pos] = ' ';
            }
            break;
          }
        }
      }
      gotoxy(1,1);
      break;
    case(down_key): 
      if (screen_grid[x_pos+1][y_pos] == ' '){
        screen_grid[x_pos][y_pos] = ' ';
        x_pos += 1;
        screen_grid[x_pos][y_pos] = '#';
        empty_desc();
      }else{
        for(i=0;i<obj_num;i++){
          if (screen_grid[x_pos+1][y_pos] == object_arr[i]){
            display_desc(i);
            if (strcmp(descriptions[i], "kitten") == 0){
              kittens_found++;
              screen_grid[x_pos+1][y_pos] = ' ';
            }
            break;
          }
        }
      }
      gotoxy(1,1);
      break;
    case(left_key): 
      if (screen_grid[x_pos][y_pos-1] == ' '){
        screen_grid[x_pos][y_pos] = ' ';
        y_pos -= 1;
        screen_grid[x_pos][y_pos] = '#';
        empty_desc();
      }else{
        for(i=0;i<obj_num;i++){
          if (screen_grid[x_pos][y_pos-1] == object_arr[i]){
            display_desc(i);

            if (strcmp(descriptions[i], "kitten") == 0){
              kittens_found++;
              screen_grid[x_pos][y_pos-1] = ' ';
            }
            break;
          }
        }
      }
      gotoxy(1,1);
      break;
    case(right_key): 
      if (screen_grid[x_pos][y_pos+1] == ' '){
          screen_grid[x_pos][y_pos] = ' ';
          y_pos += 1;
          screen_grid[x_pos][y_pos] = '#';
          empty_desc();
      }else{
        for(i=0;i<obj_num;i++){
          if (screen_grid[x_pos][y_pos+1] == object_arr[i]){
            display_desc(i);

            if (strcmp(descriptions[i], "kitten") == 0){
              kittens_found++;
              screen_grid[x_pos][y_pos+1] = ' ';
            }
            break;
          }
        }
      }
      gotoxy(1,1);
      break;
    default:
      gotoxy(1,1);
      setup_level();
      break;
  }
  setup_level();
}
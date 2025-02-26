#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
// This is a fundamental representation for machines.
/*  
 In 1_machine any change that happens just before the machine next step is considered as the input applied for the previous step.
 Thus we consider that in fact only 1 change happened for each machine transition(the one still active at the transition time) and that others did not happen.
   */


int main() {
    initscr();          // Initialize the window
    cbreak();           // Disable line buffering
    noecho();           // Don't echo input
    nodelay(stdscr, TRUE); // Non-blocking input
    keypad(stdscr, TRUE);  // Enable special keys like arrows
   
    // machine's input variables 
    bool j=0; //value of A press j to modify it.
    bool k=0; //value of B press k to modify it.
    
    // machine's present variables
    bool a_p=0;
    bool b_p=1;
    
    // machine's futur variables
    bool a_f=0;
    bool b_f=0;
    
    int quit_flag=0;
    int counter=0;
    int loading_counter=0;
    unsigned int y_cursor=0;
    bool present_state[2]={0,0}; // this is the present state of the machine , it can be any interger between 0(0b0000)and 15(0b1111)
    bool state_history[20][4]={0};    
    //memset(state_history, 0, sizeof(state_history));

    bool state_history_past[20][4]={0};
    //memset(state_history_p, 0, sizeof(state_history_p));

    int ch;
    curs_set(0);
    printw("Press 'ESC' to exit and Press 'Space' to stop the machine\n");
    printw("In 1_machine the last change that happens just before the machine next step is considered as the input applied for the previous step.\n");
    // representation of the machine
    // Description of the graph of the machine:
    // [a_p b_p] is the starting vertex of the edges
    // [a_f b_f] is the destination vertex of the edges
    // [j   k  ] is the label of the edges
    mvprintw( 3,70,"Tabular representation");
    mvprintw( 4,70,"a_p b_p   j   k a_f b_f");  
    mvprintw( 5,70,"  0   0   0   0   0   1");
    mvprintw( 6,70,"  0   0   0   1   0   0");
    mvprintw( 7,70,"  0   0   1   0   1   1");
    mvprintw( 8,70,"  0   0   1   1   1   0");
    mvprintw( 9,70,"  0   1   0   0   0   1");
    mvprintw(10,70,"  0   1   0   1   1   1");
    mvprintw(11,70,"  0   1   1   0   1   1");
    mvprintw(12,70,"  0   1   1   1   0   1");
    mvprintw(13,70,"  1   0   0   0   0   0");
    mvprintw(14,70,"  1   0   0   1   1   1");
    mvprintw(15,70,"  1   0   1   0   1   0");
    mvprintw(16,70,"  1   0   1   1   0   1");
    mvprintw(17,70,"  1   1   0   0   1   1");
    mvprintw(18,70,"  1   1   0   1   1   0");
    mvprintw(19,70,"  1   1   1   0   0   1");
    mvprintw(20,70,"  1   1   1   1   0   0");
    mvprintw(3,48,"Instant state cursor"); // below it we need a super fast cursor
    // position of text about tables
    mvprintw(6,1,"Press j,k to switch the truth values of inputs");
    mvprintw(9,7,"Actual machine state");
    mvprintw(9,31,"%d    %d    %d    %d",a_p,b_p,j,k); 
    mvprintw(10,31,"a_p  b_p  j    k"); 
    mvprintw(13,1,"Choose before the end of this counter:");
    mvprintw(14,7,"|");
    mvprintw(14,27,"|");
    mvprintw(3,98,"History of existed states");
    mvprintw(4,98,"a_p b_p   j   k");  
    refresh();

    while (1) {
	// active text every 4 ms
	mvprintw(9,41,"%d    %d",j,k); // value for arbitrary chosen input

	mvprintw(5,65,"    "); // clear the previous cursor
	mvprintw(6,65,"    ");
	mvprintw(7,65,"    ");
	mvprintw(8,65,"    ");
	mvprintw(9,65,"    ");
	mvprintw(10,65,"    ");
	mvprintw(11,65,"    ");
	mvprintw(12,65,"    ");
	mvprintw(13,65,"    ");
	mvprintw(14,65,"    ");
	mvprintw(15,65,"    ");
	mvprintw(16,65,"    ");
	mvprintw(17,65,"    ");
	mvprintw(18,65,"    ");
	mvprintw(19,65,"    ");
	mvprintw(20,65,"    ");
	y_cursor=5+(a_p<<3)+(b_p<<2)+(j<<1)+k; // set cursor position
	mvprintw(y_cursor,65,"--->"); // display the cursor of instant state
	refresh();
        
	//input record   
	ch = getch();   // Get the current key pressed
        if (ch != ERR) {
		if (ch == 'j') j = !j;  // toggle input value j
		if (ch == 'k') k = !k;  // toggle input value k
		if (ch == ' ') {        // entering PAUSE loop
			while(1){
				mvprintw(0,70,"PAUSED");
				ch=getch();
				if (ch != ERR){
					if(ch =='j') j=!j;
					if(ch =='k') k=!k;
					if(ch == ' '){
						break;
					}
					if(ch == '\033' ){
						quit_flag=1;
						break;
					}
				}
				mvprintw(9,41,"%d    %d",j,k); // value for arbitrary chosen input
				mvprintw(5,65,"    "); // clear the previous cursor
				mvprintw(6,65,"    ");
				mvprintw(7,65,"    ");
				mvprintw(8,65,"    ");
				mvprintw(9,65,"    ");
				mvprintw(10,65,"    ");
				mvprintw(11,65,"    ");
				mvprintw(12,65,"    ");
				mvprintw(13,65,"    ");
				mvprintw(14,65,"    ");
				mvprintw(15,65,"    ");
				mvprintw(16,65,"    ");
				mvprintw(17,65,"    ");
				mvprintw(18,65,"    ");
				mvprintw(19,65,"    ");
				mvprintw(20,65,"    ");
				y_cursor=5+(a_p<<3)+(b_p<<2)+(j<<1)+k; //set cursor position
				mvprintw(y_cursor,65,"--->"); // display the cursor of instant state
				refresh();
				usleep(2000);
			}
			mvprintw(0,70,"      "); // clear PAUSED indicator
		}
        	if (ch == '\033' || quit_flag==1) break;
        }
	
	counter++; //counter increasing by 1 every 4 millisecond
	
	if (counter % 25 == 0){
		mvprintw(14,8+loading_counter,"_");
		refresh();
		loading_counter++;
	}
	
	//apply changes on the machine every 2 seconds
	
	if (counter==500) {
 	        //history storage assignement
		state_history[0][0]=a_p; // a_p assigned
		state_history[0][1]=b_p; // b_p assigned
		state_history[0][2]=j; // j   assigned
		state_history[0][3]=k; // k   assigned

		//machine definition a_f=f1(a_p,b_p,j,k) and b_f=f2(a_p,b_p,j,k) ,we will logical operator except xor(^) which only exists in bitwise .
		a_f=!a_p&&!b_p&&j||(a_p^b_p)&&(j^k)||a_p&&b_p&&!j; // formula
		b_f=!k&&(a_p&&b_p||!a_p&&!b_p)||!a_p&&b_p||(a_p&&!b_p)&&k; // formula
		

		// assignement: the future becomes the present
		a_p=a_f; 
		b_p=b_f;
	
		mvprintw(9,31,"%d    %d    %d    %d",a_p,b_p,j,k); //present state of the machine


		//fill state_history with the previous state stored in state_history_past
		for (unsigned int i=0;i<19;i++){
			state_history[i+1][0]=state_history_past[i][0]; // a_p assigned
			state_history[i+1][1]=state_history_past[i][1]; // b_p assigned
			state_history[i+1][2]=state_history_past[i][2]; // j   assigned
			state_history[i+1][3]=state_history_past[i][3]; // k   assigned
		}
		
		
		//displayed text every 2 seconds 
		// here I need to display the history an also to store it.
		for (unsigned int l=0;l<20;l++){
			mvprintw(5+l,100,"%d   %d   %d   %d",state_history[l][0],state_history[l][1],state_history[l][2],state_history[l][3]);  
		}
		
		
		mvprintw(14,8,"                   |");
		
		//counter resets
		loading_counter=0;
		counter=0; 
		//set the new state_history_past
		for (unsigned int i=0;i<20;i++){
			state_history_past[i][0]=state_history[i][0]; // a_p assigned
			state_history_past[i][1]=state_history[i][1]; // b_p assigned
			state_history_past[i][2]=state_history[i][2]; // j   assigned
			state_history_past[i][3]=state_history[i][3]; // k   assigned
		}
		refresh();


	}
        usleep(4000); // Sleep to prevent excessive CPU usage 4 ms period
    }
    endwin();           // Restore terminal settings
    system("clear"); // Sends the clear command to the terminal
    return 0;
}





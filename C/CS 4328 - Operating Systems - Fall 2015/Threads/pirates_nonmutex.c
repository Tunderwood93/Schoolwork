#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define NYTIMES 10

int pearls = 1000;
int A_total =0;
int B_total =0;
int C_total =0;
int D_total =0;

void *Pirate_A();
void *Pirate_B();
void *Pirate_C();
void *Pirate_D();
void final_result();

int main(){

  pthread_t tid;
  
  pthread_setconcurrency(4);

  printf("Setting up threads...\n");

  pthread_create(&tid, NULL, (void *(*) (void *))Pirate_A, NULL);
  pthread_create(&tid, NULL, (void *(*) (void *))Pirate_B, NULL);
  pthread_create(&tid, NULL, (void *(*) (void *))Pirate_C, NULL);
  pthread_create(&tid, NULL, (void *(*) (void *))Pirate_D, NULL);

  pthread_exit(0);
}

void *Pirate_A(){

  int res, i;
  float compare;
  float percent = 0.15;

  sleep(3);
  
  for(i=0;i<NYTIMES;i++){
     compare = pearls * percent;
     res = compare;

     compare = fmod(compare,1.0);

     if(compare != 0) res++;

     printf("Pirate_A took %d pearls.\n", res);

     A_total += res;
     pearls -= res;
     printf("Pearls left: %d\n\n",pearls);

     if(pearls<0){
	final_result();
	break;
     }
  }
}

void *Pirate_B(){

  int res, i;
  float compare;
  float percent = 0.15;

  sleep(3);  

  for(i=0;i< NYTIMES; i++){
     compare = pearls * percent;
     res = compare;

     compare = fmod(compare,1.0);

     if(compare != 0) res++;

     printf("Pirate_B took %d pearls.\n", res);

     B_total += res;
     pearls -= res;
     printf("Pearls left: %d\n\n",pearls);

     if(pearls<0){
	final_result();
        break;
     }
  }
}

void *Pirate_C(){

  int res, i;
  float compare;
  float percent = 0.10;

  sleep(3);  

  for(i=0;i< NYTIMES; i++){
     compare = pearls * percent;
     res = compare;

     compare = fmod(compare,1.0);

     if(compare != 0) res++;

     printf("Pirate_C took %d pearls.\n", res);

     C_total += res;
     pearls -= res;
     printf("Pearls left: %d\n\n",pearls);

     if(pearls<0){
	final_result();
        break;
     }
  }
}

void *Pirate_D(){

  int res, i;
  float compare;
  float percent = 0.10;

  sleep(3);  

  for(i=0;i< NYTIMES; i++){
     compare = pearls * percent;
     res = compare;

     compare = fmod(compare,1.0);

     if(compare != 0) res++;

     printf("Pirate_D took %d pearls.\n", res);

     D_total += res;
     pearls -= res;
     printf("Pearls left: %d\n\n",pearls);

     if(pearls<0){
	final_result();
        break;
     }
  }
}

void final_result(){

  int total = 0;
  
  printf("\n\n"); 
  printf("Pirate A total: %d\n", A_total);
  printf("Pirate B total: %d\n", B_total);
  printf("Pirate C total: %d\n", C_total);
  printf("Pirate D total: %d\n", D_total);

  total = A_total + B_total + C_total + D_total;

  printf("Amount of pearls: %d\n", total);
}

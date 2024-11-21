/*
We use the file phods_loopfusion_final.c and there we try different symmetric Block sizes (before the default was 5, now we try B=1,2,5,10)
Below is the full-code 
*/

#include "hal_data.h"
#include "stdio.h"
#include "string.h"
#include "images.h"
#define N 10    /*Frame dimension for QCIF format*/
#define M 10     /*Frame dimension for QCIF format*/
//#define B 5      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                  original location of the block.*/
volatile uint32_t clock_frequency = 0;
int B[4] = {1, 2, 5, 10};
void phods_motion_estimation(int z,const int current[N][M],const int previous[N][M],
      int vectors_x[N/B[z]][M/B[z]],int vectors_y[N/B[z]][M/B[z]])
{
int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
distx = 0;
disty = 0;
// int B=B[z];
/*Initialize the vector motion matrices*/
for(i=0; i<N/B[z]; i++)
{
  for(j=0; j<M/B[z]; j++)
  {
    vectors_x[i][j] = 0;
    vectors_y[i][j] = 0;
  }
}
/*For all blocks in the current frame*/
for(x=0; x<N/B[z]; x++)
{
  for(y=0; y<M/B[z]; y++)
  {
    S = 4;
    int tempx=B[z]*x + vectors_x[x][y];
    int tempy=B[z]*y + vectors_y[x][y];
    while(S > 0)
    {
      min1 = 255*B[z]*B[z];
      min2 = 255*B[z]*B[z];
      /*For all candidate blocks in X Y dimensionS*/
      for(i = -S; i < S + 1; i += S)
      {
          distx = 0;
          disty = 0;
          /* For all pixels in the block */
          for(k = 0; k < B[z]; k++)
          {
              for(l = 0; l < B[z]; l++)
              {
                  p1 = current[B[z]*x + k][B[z]*y + l];
                  // Calculate disty
                  if((tempx + k) < 0 ||
                     (tempx + k) > (N-1) ||
                     (tempy + i + l) < 0 ||
                     (tempy + i + l) > (M-1))
                  {
                      q2 = 0;
                  }
                  else
                  {
                      q2 = previous[tempx + k][tempy + i + l];
                  }
                                 if(p1 - q2 > 0)
                  {
                      disty += p1 - q2;
                  }
                  else
                  {
                      disty += q2 - p1;
                  }
                  // Calculate distx
                  if((tempx + i + k) < 0 ||
                     (tempx + i + k) > (N-1) ||
                     (tempy + l) < 0 ||
                     (tempy + l) > (M-1))
                  {
                      p2 = 0;
                  }
                  else
                  {
                      p2 = previous[tempx + i + k][tempy + l];
                  }
                                    if(p1 - p2 > 0)
                  {
                      distx += p1 - p2;
                  }
                  else
                  {
                      distx += p2 - p1;
                  }
              }
          }
          // Check if the current disty is the minimum
          if(disty < min2)
          {
              min2 = disty;
              besty = i;
          }
          // Check if the current distx is the minimum
          if(distx < min1)
          {
              min1 = distx;
              bestx = i;
          }
      }
      S = S/2;
      vectors_x[x][y] += bestx;
      vectors_y[x][y] += besty;
    }
  }
}
}
/*******************************************************************************************************************//**
* @brief  Blinky example application
*
* Blinks all leds at a rate of 1 second using the software delay function provided by the BSP.
* Only references two other modules including the BSP, IOPORT.
*
**********************************************************************************************************************/
void hal_entry(void) {
  // Code to initialize the DWT->CYCCNT register
  CoreDebug->DEMCR |= 0x01000000;
     ITM->LAR = 0xC5ACCE55;
     DWT->CYCCNT = 0;
     DWT->CTRL |= 1;
     /* Initialize your variables here */
     clock_frequency = SystemCoreClock;
     float time[10];
     uint32_t cycle[10];
   float maxtime[4]={0,0,0,0};
   float mintime[4]={0,0,0,0};
   float timecounter[4]={0,0,0,0};
   float avgtime[4]={0,0,0,0};
   for(int z=0; z<4; z++){
     int motion_vectors_x[N/B[z]][M/B[z]],motion_vectors_y[N/B[z]][M/B[z]];
     for(int i=0; i<10; i++){
       /* Add timer code here */
       DWT->CYCCNT = 0;
       phods_motion_estimation(z,current,previous,motion_vectors_x,motion_vectors_y);
       cycle[i]=DWT->CYCCNT;
       time[i]=(float)cycle[i] / (float)clock_frequency;
    }
     mintime[z]=time[0];
     for(int i=0; i<10; i++){
         if(time[i]>maxtime[z])
             maxtime[z]=time[i];
         if(time[i]<mintime[z])
             mintime[z]=time[i];
         timecounter[z]+=time[i];
     }
     avgtime[z]=timecounter[z]/10;
   }
    while(1){
    }
}


/*
We use the file phods_loopfusion_final.c and there we try different Block sizes 
with Asymmetric block sizes (before the default was B=5, now we try Bx,By=1,2,5,10)
Below is the full-code
*/

#include "hal_data.h"
#include "stdio.h"
#include "string.h"
#include "images.h"
#define N 10    /*Frame dimension for QCIF format*/
#define M 10    /*Frame dimension for QCIF format*/
#define p 7     /*Search space. Restricted in a [-p,p] region around the original location of the block.*/
volatile uint32_t clock_frequency = 0;
// Asymmetric block sizes for height (Bx) and width (By)
int Bx[4] = {1, 2, 5, 10};  // Block heights
int By[4] = {1, 2, 5, 10};  // Block widths
void phods_motion_estimation(int z1,int z2, const int current[N][M], const int previous[N][M],
     int vectors_x[N/Bx[z1]][M/By[z2]], int vectors_y[N/Bx[z1]][M/By[z2]])
{
   int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
   distx = 0;
   disty = 0;
   /*Initialize the vector motion matrices*/
   for(i = 0; i < N / Bx[z1]; i++)
   {
       for(j = 0; j < M / By[z2]; j++)
       {
           vectors_x[i][j] = 0;
           vectors_y[i][j] = 0;
       }
   }
   /*For all blocks in the current frame*/
   for(x = 0; x < N / Bx[z1]; x++)
   {
       for(y = 0; y < M / By[z2]; y++)
       {
           S = 4;
           int tempx = Bx[z1] * x + vectors_x[x][y];
           int tempy = By[z2] * y + vectors_y[x][y];
           while(S > 0)
           {
               min1 = 255 * Bx[z1] * By[z2];
               min2 = 255 * Bx[z1] * By[z2];
               /*For all candidate blocks in X Y dimensions*/
               for(i = -S; i < S + 1; i += S)
               {
                   distx = 0;
                   disty = 0;
                   /* For all pixels in the block */
                   for(k = 0; k < Bx[z1]; k++)
                   {
                       for(l = 0; l < By[z2]; l++)
                       {
                           p1 = current[Bx[z1] * x + k][By[z2] * y + l];
                           // Calculate disty
                           if((tempx + k) < 0 ||
                              (tempx + k) > (N - 1) ||
                              (tempy + i + l) < 0 ||
                              (tempy + i + l) > (M - 1))
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
                              (tempx + i + k) > (N - 1) ||
                              (tempy + l) < 0 ||
                              (tempy + l) > (M - 1))
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
               S = S / 2;
               vectors_x[x][y] += bestx;
               vectors_y[x][y] += besty;
           }
       }
   }
}
void hal_entry(void) {
   // Code to initialize the DWT->CYCCNT register
   CoreDebug->DEMCR |= 0x01000000;
   ITM->LAR = 0xC5ACCE55;
   DWT->CYCCNT = 0;
   DWT->CTRL |= 1;
   /* Initialize your variables here */
   clock_frequency = SystemCoreClock;
   float time[10];  // Store the times for each trial
   uint32_t cycle[10];  // Store the cycle counts for each trial
   // 1D arrays for storing the max, min, average times (flattened)
   float maxtime[16] = {0};  // Store the max time for each combination of Bx, By
   float mintime[16] = {100};  // Store the min time for each combination of Bx, By
   float timecounter[16] = {0};  // Store the total time for each combination
   float avgtime[16] = {0};  // Store the average time for each combination
   // Block height and width combinations
   int Bx[4] = {1, 2, 5, 10};  // Block heights
   int By[4] = {1, 2, 5, 10};  // Block widths
   int i=0;
   // Iterate through all combinations of Bx and By (16 combinations)
   for (int z1 = 0; z1 < 4; z1++) {
       for (int z2 = 0; z2 < 4; z2++) {
           int motion_vectors_x[N / Bx[z1]][M / By[z2]], motion_vectors_y[N / Bx[z1]][M / By[z2]];
           // Loop for 10 trials to calculate the timings
           for ( i = 0; i < 10; i++) {
               /* Add timer code here */
               DWT->CYCCNT = 0;
               phods_motion_estimation(z1,z2, current, previous, motion_vectors_x, motion_vectors_y);
               cycle[i] = DWT->CYCCNT;
               time[i] = (float)cycle[i] / (float)clock_frequency;
           }
               mintime[z1 * 4 + z2] = time[0];
               maxtime[z1 * 4 + z2] = time[0];
           // Calculate the min, max, and total time for this combination
           for ( i = 0; i < 10; i++) {
               if (time[i] > maxtime[z1 * 4 + z2]) {
                   maxtime[z1 * 4 + z2] = time[i];
               }
               if (time[i] < mintime[z1 * 4 + z2]) {
                   mintime[z1 * 4 + z2] = time[i];
               }
               timecounter[z1 * 4 + z2] += time[i];
           }
           // Calculate the average time
           avgtime[z1 * 4 + z2] = timecounter[z1 * 4 + z2] / 10;
       }
   }  
   while (1) {
   }
}


/*
We use Loop Unrolling to we increase the performance of loops by reducing 
the number of iterations and performing multiple calculations within each iteration.
Below is the modified PHODS function.
*/


#include "hal_data.h"
#include "stdio.h"
#include "string.h"
#include "images.h"
#define N 10    /*Frame dimension for QCIF format*/
#define M 10     /*Frame dimension for QCIF format*/
#define B 5      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                   original location of the block.*/
volatile uint32_t clock_frequency = 0;
void phods_motion_estimation(const int current[N][M], const int previous[N][M],
       int vectors_x[N/B][M/B],int vectors_y[N/B][M/B])
{
 int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;
 distx = 0;
 disty = 0;
 /*Initialize the vector motion matrices*/
 for(i=0; i<N/B; i++)
 {
   for(j=0; j<M/B; j++)
   {
     vectors_x[i][j] = 0;
     vectors_y[i][j] = 0;
   }
 }
 /*For all blocks in the current frame*/
 for(x=0; x<N/B; x++)
 {
   for(y=0; y<M/B; y++)
   {
     S = 4;
     while(S > 0)
     {
       min1 = 255*B*B;
       min2 = 255*B*B;
       /*For all candidate blocks in X dimension*/
       for(i=-S; i<S+1; i+=S)
       {
         distx = 0;
         /*For all pixels in the block (Loop unrolling by 2 for k and l)*/
         for(k = 0; k < B; k += 2) {    // Unrolling by 2
           for(l = 0; l < B; l += 2) {  // Unrolling by 2
             // Process the first pair (k, l)
             p1 = current[B*x + k][B*y + l];
             if((B*x + vectors_x[x][y] + i + k) < 0 ||
                (B*x + vectors_x[x][y] + i + k) > (N-1) ||
                (B*y + vectors_y[x][y] + l) < 0 ||
                (B*y + vectors_y[x][y] + l) > (M-1))
             {
               p2 = 0;
             } else {
               p2 = previous[B*x + vectors_x[x][y] + i + k][B*y + vectors_y[x][y] + l];
             }
             distx += abs(p1 - p2);
             // Process the second pair (k+1, l)
             if (k + 1 < B) {
               p1 = current[B*x + k + 1][B*y + l];
               if((B*x + vectors_x[x][y] + i + k + 1) < 0 ||
                  (B*x + vectors_x[x][y] + i + k + 1) > (N-1) ||
                  (B*y + vectors_y[x][y] + l) < 0 ||
                  (B*y + vectors_y[x][y] + l) > (M-1))
               {
                 p2 = 0;
               } else {
                 p2 = previous[B*x + vectors_x[x][y] + i + k + 1][B*y + vectors_y[x][y] + l];
               }
               distx += abs(p1 - p2);
             }
             // Process the first pair (k, l+1)
             if (l + 1 < B) {
               p1 = current[B*x + k][B*y + l + 1];
               if((B*x + vectors_x[x][y] + i + k) < 0 ||
                  (B*x + vectors_x[x][y] + i + k) > (N-1) ||
                  (B*y + vectors_y[x][y] + l + 1) < 0 ||
                  (B*y + vectors_y[x][y] + l + 1) > (M-1))
               {
                 p2 = 0;
               } else {
                 p2 = previous[B*x + vectors_x[x][y] + i + k][B*y + vectors_y[x][y] + l + 1];
               }
               distx += abs(p1 - p2);
             }
             // Process the second pair (k+1, l+1)
             if (k + 1 < B && l + 1 < B) {
               p1 = current[B*x + k + 1][B*y + l + 1];
               if((B*x + vectors_x[x][y] + i + k + 1) < 0 ||
                  (B*x + vectors_x[x][y] + i + k + 1) > (N-1) ||
                  (B*y + vectors_y[x][y] + l + 1) < 0 ||
                  (B*y + vectors_y[x][y] + l + 1) > (M-1))
               {
                 p2 = 0;
               } else {
                 p2 = previous[B*x + vectors_x[x][y] + i + k + 1][B*y + vectors_y[x][y] + l + 1];
               }
               distx += abs(p1 - p2);
             }
           }
         }
         if(distx < min1)
         {
           min1 = distx;
           bestx = i;
         }
       }
       /*For all candidate blocks in Y dimension*/
       for(i = -S; i < S + 1; i += S) {
           disty = 0;
           /* For all pixels in the block (Loop unrolling by 2 for k and l) */
           for(k = 0; k < B; k += 2) {    // Unrolling by 2
               for(l = 0; l < B; l += 2) {  // Unrolling by 2
                   // Process the first pair (k, l)
                   p1 = current[B*x + k][B*y + l];
                   if((B*x + vectors_x[x][y] + k) < 0 ||
                      (B*x + vectors_x[x][y] + k) > (N - 1) ||
                      (B*y + vectors_y[x][y] + i + l) < 0 ||
                      (B*y + vectors_y[x][y] + i + l) > (M - 1)) {
                       q2 = 0;
                   } else {
                       q2 = previous[B*x + vectors_x[x][y] + k][B*y + vectors_y[x][y] + i + l];
                   }
                   disty += abs(p1 - q2);
                   // Process the second pair (k+1, l)
                   if(k + 1 < B) {
                       p1 = current[B*x + k + 1][B*y + l];
                       if((B*x + vectors_x[x][y] + k + 1) < 0 ||
                          (B*x + vectors_x[x][y] + k + 1) > (N - 1) ||
                          (B*y + vectors_y[x][y] + i + l) < 0 ||
                          (B*y + vectors_y[x][y] + i + l) > (M - 1)) {
                           q2 = 0;
                       } else {
                           q2 = previous[B*x + vectors_x[x][y] + k + 1][B*y + vectors_y[x][y] + i + l];
                       }
                       disty += abs(p1 - q2);
                   }
                   // Process the first pair (k, l+1)
                   if(l + 1 < B) {
                       p1 = current[B*x + k][B*y + l + 1];
                       if((B*x + vectors_x[x][y] + k) < 0 ||
                          (B*x + vectors_x[x][y] + k) > (N - 1) ||
                          (B*y + vectors_y[x][y] + i + l + 1) < 0 ||
                          (B*y + vectors_y[x][y] + i + l + 1) > (M - 1)) {
                           q2 = 0;
                       } else {
                           q2 = previous[B*x + vectors_x[x][y] + k][B*y + vectors_y[x][y] + i + l + 1];
                       }
                       disty += abs(p1 - q2);
                   }
                   // Process the second pair (k+1, l+1)
                   if(k + 1 < B && l + 1 < B) {
                       p1 = current[B*x + k + 1][B*y + l + 1];
                       if((B*x + vectors_x[x][y] + k + 1) < 0 ||
                          (B*x + vectors_x[x][y] + k + 1) > (N - 1) ||
                          (B*y + vectors_y[x][y] + i + l + 1) < 0 ||
                          (B*y + vectors_y[x][y] + i + l + 1) > (M - 1)) {
                           q2 = 0;
                       } else {
                           q2 = previous[B*x + vectors_x[x][y] + k + 1][B*y + vectors_y[x][y] + i + l + 1];
                       }
                       disty += abs(p1 - q2);
                   }
               }
           }
           if(disty < min2) {
               min2 = disty;
               besty = i;
           }
       }
       S = S/2;
       vectors_x[x][y] += bestx;
       vectors_y[x][y] += besty;
     }
   }
 }
}

/*
We use Loop fusion to merge the computations of distx and disty in the same loop
The p1, p2, q2 values ​​are the same for both calculations, so by merging we achieve 
a better use of spatial locality since they are retrieved and used in the same iteration.
Below is the modified PHODS function
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

//below this point we compute distx, disty together
        for(i = -S; i < S + 1; i += S)
        {
           distx = 0;
           disty = 0;
          // printf("Processing i = %d\n", i);  // Debug output
           /* For all pixels in the block */
           for(k = 0; k < B; k++)
           {
               for(l = 0; l < B; l++)
               {
                   p1 = current[B*x + k][B*y + l];
                   // Calculate disty
                   if((B*x + vectors_x[x][y] + k) < 0 ||
                      (B*x + vectors_x[x][y] + k) > (N-1) ||
                      (B*y + vectors_y[x][y] + i + l) < 0 ||
                      (B*y + vectors_y[x][y] + i + l) > (M-1))
                   {   q2 = 0;       }
                   else
                   {
                       q2 = previous[B*x + vectors_x[x][y] + k][B*y + vectors_y[x][y] + i + l];
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
                   if((B*x + vectors_x[x][y] + i + k) < 0 ||
                      (B*x + vectors_x[x][y] + i + k) > (N-1) ||
                      (B*y + vectors_y[x][y] + l) < 0 ||
                      (B*y + vectors_y[x][y] + l) > (M-1))
                   {
                       p2 = 0;
                   }
                   else
                   {
                       p2 = previous[B*x + vectors_x[x][y] + i + k][B*y + vectors_y[x][y] + l];
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
           {  min1 = distx;
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



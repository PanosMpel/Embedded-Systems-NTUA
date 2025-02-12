/*Parallel Hierarchical One-Dimensional Search for motion estimation*/
/*Initial algorithm - Used for simulation and profiling             */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 144     /*Frame dimension for QCIF format*/
#define M 176     /*Frame dimension for QCIF format*/
#define B 16      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/

void read_sequence(int current[N][M], int previous[N][M])
{ 
	FILE *picture0, *picture1;
	int i, j;

	if((picture0=fopen("akiyo0.y","rb")) == NULL)
	{
		printf("Previous frame doesn't exist.\n");
		exit(-1);
	}

	if((picture1=fopen("akiyo1.y","rb")) == NULL) 
	{
		printf("Current frame doesn't exist.\n");
		exit(-1);
	}

  /*Input for the previous frame*/
  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    {
      previous[i][j] = fgetc(picture0);
    }
  }

	/*Input for the current frame*/
	for(i=0; i<N; i++)
  {
		for(j=0; j<M; j++)
    {
			current[i][j] = fgetc(picture1);
    }
  }

	fclose(picture0);
	fclose(picture1);
}


void phods_motion_estimation(int current[N][M], int previous[N][M],
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

          /*For all pixels in the block*/
          for(k=0; k<B; k++)     
          {
            for(l=0; l<B; l++)
            {
              p1 = current[B*x+k][B*y+l];

              if((B*x + vectors_x[x][y] + i + k) < 0 ||
                  (B*x + vectors_x[x][y] + i + k) > (N-1) ||
                  (B*y + vectors_y[x][y] + l) < 0 ||
                  (B*y + vectors_y[x][y] + l) > (M-1))
              {
                p2 = 0;
              } else {
                p2 = previous[B*x+vectors_x[x][y]+i+k][B*y+vectors_y[x][y]+l];
              }

              distx += abs(p1-p2);
            }
          }

          if(distx < min1)
          {
            min1 = distx;
            bestx = i;
          }
        }

        /*For all candidate blocks in Y dimension*/
        for(i=-S; i<S+1; i+=S)     
        {
          disty = 0;

          /*For all pixels in the block*/
          for(k=0; k<B; k++)     
          {
            for(l=0; l<B; l++)
            {
              p1 = current[B*x+k][B*y+l];

              if((B*x + vectors_x[x][y] + k) <0 ||
                  (B*x + vectors_x[x][y] + k) > (N-1) ||
                  (B*y + vectors_y[x][y] + i + l) < 0 ||
                  (B*y + vectors_y[x][y] + i + l) > (M-1))
              {
                q2 = 0;
              } else {
                q2 = previous[B*x+vectors_x[x][y]+k][B*y+vectors_y[x][y]+i+l];
              }

              disty += abs(p1-q2);
            }
          }

          if(disty < min2)
          {
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

int main()
{  
  int current[N][M], previous[N][M], motion_vectors_x[N/B][M/B],
      motion_vectors_y[N/B][M/B], i, j;

	read_sequence(current,previous);
  // added time measurement initializations
  struct timeval t1, t2;
  double time_res;
  gettimeofday(&t1,NULL);

  // code as given  
  phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);

  gettimeofday(&t2,NULL);
  time_res = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("%f\n", time_res);
  // code as given

  // save in file content of motion_vectors_x and motion_vectors_y
  FILE *fx,*fy;

  fx = fopen("./results/unoptimised_x.txt","w");
  fy = fopen("./results/unoptimised_y.txt","w");

  for(int i=0; i<N/B; i++)
  {
    for(int j=0; j<M/B; j++)
    {
      fprintf(fx,"%d ",motion_vectors_x[i][j]);
      fprintf(fy,"%d ",motion_vectors_y[i][j]);
    }
    fprintf(fx,"\n");
    fprintf(fy,"\n");
  }

  fclose(fx);
  fclose(fy);
  return 0;
}

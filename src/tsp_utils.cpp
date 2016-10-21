/*****************************************************************************/
/*
* Some utility routines
*
* MALIS Lab Session
*
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>

#include "tsp_utils.h"
#include "image.h"

static double distances[MAX_N_CITIES][MAX_N_CITIES];

/*****************************************************************************/
/* return a random number within the closed interval [low,high] */
int random_number(int low,int high){
  assert(high>=low);
  return low + (rand() % (high-low+1));
}

/*****************************************************************************/
/* Plot a route on the image France.ppm and save the plot in file:w
plots/route_<generation>_<length>.gif */
void tsp_plot_route(char *filename,int sequence[], int generation, double length, int pop_size, double mut_rate){
  int i;
  char ppm_filename[200];
  char gif_filename[200];
  char command[500];
  Image image;

  image_read(&image, filename);

  for(i = 0; i < n_cities; i++){
    int from = sequence[i];
    int to = sequence[(i + 1) % n_cities];
    image_drawline(&image, city[from].x, city[from].y, city[to].x, city[to].y, 0, 0, 0);
    image_drawline(&image,city[from].x+1,city[from].y, city[to].x+1, city[to].y, 0, 0, 0);
  }
	/* write the image and convert it to the GIF format */
  snprintf(ppm_filename, sizeof(ppm_filename), "./result/route_%04d_%05.2f_%03d_%01.3f.ppm",generation, length, pop_size, mut_rate);
  image_write(&image,ppm_filename);
	
  snprintf(gif_filename,sizeof(gif_filename),"./result/route_%04d_%05.2f_%03d_%01.3f.gif",generation,length, pop_size, mut_rate);
  
  sprintf(command, "convert %s %s", ppm_filename, gif_filename);
  system(command);
	
  //sprintf_s(command,sizeof(command),"erase /Q %s",ppm_filename);
  system("rm ./result/*.ppm");

}

/*****************************************************************************/
/* Remove all plots in the directory: */
void tsp_init_plots(){
  //	system("erase /Q *.ppm");
  //	system("erase /Q *.gif");
}

/*****************************************************************************/
/* Read cities coordinates */
void tsp_read_cities(char *filename){
  FILE *f;
  int i,j,x1,y1,x2,y2;
  
  f = fopen(filename,"r");

  if( f == (FILE *)0) {
    printf("* Error opening file %s\n",filename);
    getchar(); exit(1);
  }

  n_cities=0;
  while(fscanf(f, "%s %d %d\n", &city[n_cities].name,  &city[n_cities].x, &city[n_cities].y) == 3) {
    n_cities++;
  }
  fclose(f);
  
  /* precalculate distances to save time later */
  for(i=0; i<n_cities; i++){
    x1=city[i].x;
    y1=city[i].y;
    for(j=0; j<n_cities; j++){
      x2=city[j].x;
      y2=city[j].y;
      distances[i][j]=sqrt((double) (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }
  }
}

/*****************************************************************************/
/* Return the length of the round-trip determined by the sequence of city_ids */
double tsp_round_trip_length(int city_ids[]){
  int i;
  double length = 0.;
  
  for(i=0; i<n_cities; i++){
    length += distances[city_ids[i]][city_ids[(i+1)%n_cities]];
  }
  return length;
}

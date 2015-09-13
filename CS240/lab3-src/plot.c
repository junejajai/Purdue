
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
int k = 0;
  clearPlot();
double range = maxX - minX;
  // Evaluate function and store in vector yy
double ymax = 0;
double ymin = 0;
  //Compute maximum and minimum y in vector yy
  //double range1 = ymax - ymin;
  double div = range/MAXCOLS;
  double i = 0;
  for(i = minX ;i<maxX;i=i + div )//maxX
  {
  yy[k] = rpn_eval(funcFile,i);
// printf("y%d is %f x%d is %f \n ",k,yy[k],k,i);
 k++;
  }
  ymin = yy[0];
  int j = 0;
  for(j = 0;j<k;j++)
  {
  if(yy[j]< ymin)
  {
   ymin = yy[j];
  }
  if(ymax<yy[j])
  {
   ymax = yy[j];
  }
  }
double yrange = ymax-ymin;
double ydiv = yrange/MAXROWS;  
  //Plot x axis
if(ymin>=0)
{
int l = 0;
for(l=0;l<80;l++ )
{
plotXY(l,39,'_');
}
}
else
{
int f = 0;
for(f = 0;f<80;f++)
{
plotXY(f,19,'_');
}
}
  //Plot y axis
 
int n = 0; 
for(n = 0;n<40;n++)
{
plotXY(40,n,'|');
}
int x = 0;
double t = 0;
for(t = 0; t<80;t++){
//double e = 39- ((yy[x]-ymin)*40/ydiv);
//double e =( 40 - yy[x])*40;
double e = ymax-ymin;
int ymove = ((yy[x]-ymin)*40)/e;
plotXY(t,40 - ymove -1,'*');
x++;
}
  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  // Get arguments
  char * funcName = argv[1];
int xmin = atoi(argv[2]);
int xmax = atoi(argv[3]);
createPlot(funcName, xmin, xmax);
}

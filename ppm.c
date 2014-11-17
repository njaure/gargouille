#include "ppm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//============================================================================
//                           Structure declarations
//============================================================================
typedef  struct 
{
int x;
int y;
}Coordonnees;

typedef  struct 
{
int width;
int height;
u_char *image;
}Taille;



//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  Coordonnees point;
  Taille size;

  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
   
  size.image = NULL;
  
 FILE* ppm_input=NULL;
 char gar[30]="gargouille.ppm";
  ppm_read_from_file(&size.width, &size.height, &size.image, ppm_input, gar);
  

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw

  Taille size_bw; //struc pour image_bw

  size_bw.width  = size.width;
  size_bw.height = size.height;
  size_bw.image = (u_char*) malloc(3 * size.width * size.height * sizeof(*size_bw.image));
  memcpy(size_bw.image, size.image, 3 * size.width * size.height * sizeof(*size_bw.image));

  // Desaturate image_bw
  ppm_desaturate(size_bw.image, size.width, size.height, point.x, point.y);

  // Write the desaturated image into "gargouille_BW.ppm"
  FILE* ppm_output=NULL;
char gar_bw[30]="gargouille_BW.ppm"; 
  ppm_write_to_file(size.width, size.height, size_bw.image, ppm_output,gar_bw);
 

  // Free the desaturated image
  free(size_bw.image);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small

  Taille size_small; //struc pour image_small

  size_small.width  = size.width;
  size_small.height = size.height;
   size_small.image = (u_char*) malloc(3 * size_small.width * size_small.height * sizeof(*size_small.image));
  memcpy(size_small.image, size.image, 3 * size_small.width * size_small.height * sizeof(*size_small.image));

  // Shrink image_small size 2-fold
  ppm_shrink(&size_small.image, &size_small.width, &size_small.height, 2, point.x, point.y);

  // Write the desaturated image into "gargouille_small.ppm"
   FILE* ppm_output2=NULL;
   char gar_small[40]="gargouille_small.ppm";
  ppm_write_to_file(size_small.width, size_small.height, size_small.image, ppm_output2, gar_small);
    

  // Free the not yet freed images
  free(size.image);
  free(size_small.image);

  return 0;
}





































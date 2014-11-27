#include "picture.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  

  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  // creation of the class "mypicture"
  //--------------------------------------------------------------------------
   
   picture mypicture;

  FILE* ppm_input=NULL;

  mypicture.ppm_read_from_file(ppm_input, "gargouille.ppm");
  

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  
  // Copy image into mybwpicture
  picture mybwpicture(mypicture);

  // Desaturate image_bw
  mybwpicture.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  FILE* ppm_output=NULL;

  mybwpicture.ppm_write_to_file(ppm_output,"gargouille_BW.ppm");
 

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  
  // Copy image into image_small
  picture mysmallpicture(mypicture);

  
  // Shrink image_small size 2-fold
  mysmallpicture.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  FILE* ppm_output2=NULL;
 
  mysmallpicture.ppm_write_to_file(ppm_output2, "gargouille_small.ppm");
    

 
  return 0;
}

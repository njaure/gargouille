
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                           Structure declarations
//============================================================================
typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
int x;
int y;
};



//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(int width, int height, u_char* data, FILE* file, char* img);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(int *width, int *height, u_char** data, FILE* file,char* img );

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(u_char* image, int width, int height, Coordonnees* point );

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(u_char** image, int *width, int *height, int factor, Coordonnees* point );


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  Coordonnees monpoint;

  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
   
  u_char* image = NULL;
  int width;
  int height;
 FILE* ppm_input;
 char gar[30]="gargouille.ppm";
  ppm_read_from_file(&width, &height, &image, ppm_input,gar);
 

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  int width_bw  = width;
  int height_bw = height;
  u_char* image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));
  memcpy(image_bw, image, 3 * width * height * sizeof(*image_bw));

  // Desaturate image_bw
  ppm_desaturate(image_bw, width, height, &monpoint);

  // Write the desaturated image into "gargouille_BW.ppm"
  FILE* ppm_output;
char gar_bw[30]="gargouille_BW.ppm";
  ppm_write_to_file(width, height, image_bw, ppm_output,gar_bw);
 

  // Free the desaturated image
  free(image_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = width;
  int height_small = height;
  u_char* image_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*image_small));
  memcpy(image_small, image, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  ppm_shrink(&image_small, &width_small, &height_small, 2, &monpoint);

  // Write the desaturated image into "gargouille_small.ppm"
   FILE* ppm_output2;
   char gar_small[40]="gargouille_small.ppm";
  ppm_write_to_file(width_small, height_small, image_small, ppm_output2, gar_small);
    

  // Free the not yet freed images
  free(image);
  free(image_small);

  return 0;
}



//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(int width, int height, u_char* data,FILE* file,char* img)
{

  file=fopen(img, "wb");
  // Write header
  fprintf(file, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3, width*height,file);
  fclose(file);
 
}

void ppm_read_from_file(int *width, int *height, u_char** data,FILE* file,char* img)
{
  file = fopen(img, "rb");
  
  
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", width, height);

  // Allocate memory according to width and height
  *data = (u_char*) malloc(3 * (*width) * (*height) * sizeof(**data));

  // Read the actual image data
  fread(*data, 3, (*width) * (*height), file);
  fclose(file);

}

void ppm_desaturate(u_char* image, int width, int height, Coordonnees* point)
{
  

  // For each pixel ...
  for (point->x = 0 ; point->x < width ; point->x++)
  {
    for (point->y = 0 ; point->y < height ; point->y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image[ 3 * (point->y * width + point->x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&image[3 * (point->y * width + point->x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(u_char** image, int *width, int *height, int factor, Coordonnees* point)
{
  
  // Compute new image size and allocate memory for the new image
  int new_width   = (*width) / factor;
  int new_height  = (*height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...

  for (point->x = 0 ; point->x < new_width ; point->x++)
  {
    for (point->y = 0 ; point->y < new_height ; point->y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = point->x * factor;
      int y0 = point->y * factor;
      int i0 = 3 * (y0 * (*width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (*width) + dx);

          // Accumulate RGB values
          red   += (*image)[i0+delta_i];
          green += (*image)[i0+delta_i+1];
          blue  += (*image)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (point->y * new_width + point->x) ]     = red;
      new_image[ 3 * (point->y * new_width + point->x) + 1 ] = green;
      new_image[ 3 * (point->y * new_width + point->x) + 2 ] = blue;
    }
  }

  // Update image size
  *width  = new_width;
  *height = new_height;

  // Update image
  free(*image);
  *image = new_image;
}




































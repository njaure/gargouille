
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                           Class definition
//============================================================================


class picture
{

private:


  int width;
  int height;
  u_char *image;
  int x;
  int y;	

public:

// Definition of Getters
int getwidth() const;
int getheight() const;
u_char* getimage() const;

// Creation of Default constructor
picture();

// Creation of Copy constructor
picture(const picture& model);


// Definition of Destructor
~picture();



void ppm_write_to_file(FILE* file,const char* img);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(FILE* file, const char* img );

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate();

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink( int factor);

};




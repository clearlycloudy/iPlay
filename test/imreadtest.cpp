#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv/cv.h"
#include <iostream>

#include "ImageUtility.h"
#include "Capture.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  if(argc < 8)
  {
      cout<<"args: displayX, displayY, offx, offy, sizex, sizey, inputimage"<<endl;
      return -1;
  }

  int DisplaySizeX = atoi(argv[1]);
  int DisplaySizeY = atoi(argv[2]);
  int offsetx = atoi(argv[3]);
  int offsety = atoi(argv[4]);
  int sizex = atoi(argv[5]);
  int sizey = atoi(argv[6]);
  string inputImage(argv[7]);

  //capture screen area
  unsigned char * pImage;
  int ret = GetFrame(DisplaySizeX, DisplaySizeY, offsetx, offsety, sizex, sizey, pImage);
  if(ret != 0)
    cout<<"error"<<endl;

  //get input image
  Mat image = OpenImageMatRGB(inputImage);
  if(! image.data )                              // Check for invalid input
  {
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", image );                   // Show our image inside it.

  Size imgSize = image.size();
  cout<<"image size: "<<imgSize.width<<", "<<imgSize.height<<endl;

  for (int row=0;row<imgSize.height;row++) {
    unsigned char *data = image.ptr(row);
    for (int col=0;col<imgSize.width;col++) {
      // then use *data for the pixel value, assuming you know the order, RGB etc           
      // Note 'rgb' is actually stored B,G,R
      int red= *data++;
      int green = *data++;
      int blue = *data++;

      cout<<"r g b: "<<red<<" "<< green <<" "<< blue<<endl;
    }
  }
    
  waitKey(0);                                          // Wait for a keystroke in the window

  //create new mat from screen capture
  Mat newImg = ConvertUcharRgbToMat(pImage, sizex, sizey);

  imshow( "Display window", newImg );    
   
  waitKey(0);                                          // Wait for a keystroke in the window

  return 0;
}

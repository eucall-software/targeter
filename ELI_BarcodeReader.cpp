#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar64/include/zbar.h>

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>.

#include "globals.h"

using namespace cv;
using namespace std;
using namespace zbar;  

 
int scanForBarCodes(const cv::Mat& src, cv::Mat& dst)
{
	bool displayOK = true;

	//scanner setup
	ImageScanner scanner;  
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);  
       
	int width = src.cols;  
    int height = src.rows;

	// wrap image data  
	uchar *raw = (uchar *)src.data;
	Image image(width, height, "Y800", raw, width * height);

	// scan the image for barcodes  
	scanner.scan(image);

	std::string TAG;
	 
	// extract results  
	for(Image::SymbolIterator symbol = image.symbol_begin();  symbol != image.symbol_end(); ++symbol) 
	{
        TAG = symbol->get_data();
		if(TAG.size() != 14)
			continue;

		//print tag
		DBOUT(TAG);
		
		//define vector of points
		vector<Point> vp;

		if (displayOK)
		{
			int n = symbol->get_location_size();

			//get bar code location in image
			for(int i=0; i<n; i++)
			{
				vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i))); 
            }

			//build rectangle around the bar code
			RotatedRect r = minAreaRect(vp);
			Point2f pts[4];  
			r.points(pts);

			//draw lines
			for(int i=0; i<4; i++)
			{  
                line(dst, pts[i], pts[(i+1)%4], Scalar(255,0,0), 3);  
			}
		}
	}  

	//display information
	if(displayOK)
	{
		namedWindow( "TAG Identification", WINDOW_NORMAL );
		imshow("TAG Identification",dst);
	}
	  
   // clean up  
   image.set_data(NULL, 0);  
   waitKey();
 }  
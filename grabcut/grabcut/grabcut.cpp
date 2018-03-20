#include "opencv2/highgui/highgui.hpp"                                                                                               
#include "opencv2/imgproc/imgproc.hpp"
 
#include <iostream>
 
using namespace std;
using namespace cv; 
 
string filename;
Mat image;
string winName = "show";
Rect rect;
Mat mask;
const Scalar GREEN = Scalar(0,255,0);
Mat bgdModel, fgdModel;
 
void setRectInMask(){
	rect.x = 510;
	rect.y = 150;
	rect.width = 400;
	rect.height = 250;
}
 
static void getBinMask( const Mat& comMask, Mat& binMask ){
	binMask.create( comMask.size(), CV_8UC1 );
	binMask = comMask & 1;
}
 
int main(int argc, char* argv[]){
	Mat binMask, res;
	//filename = argv[1];
	filename = "timg.jpg";
	image = imread( filename, 1 );
	mask.create(image.size(), CV_8UC1);
	mask.setTo(GC_BGD);
	setRectInMask();
	(mask(rect)).setTo(Scalar(GC_PR_FGD));
	rectangle(image, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y + rect.height ), GREEN, 2);
	imshow(winName, image);
	image = imread( filename, 1 );
	grabCut(image, mask, rect, bgdModel, fgdModel, 1, GC_INIT_WITH_RECT);
	getBinMask(mask, binMask);
	image.copyTo(res, binMask);
	imshow("result", res);
 
	waitKey(0);
 
	return 0;
}
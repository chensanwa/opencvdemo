#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std;  
using namespace cv; 
int main ()
{
	IplImage *pSrcImg = NULL;     
	IplImage *pRolloverlnImg = NULL;  
	IplImage *pRoverselnImg = NULL;  
  
	pSrcImg = cvLoadImage("C:\\Users\\红菱\\Desktop\\OpenCV\\1.bmp",1);   
//cvLoadImage( filename, -1 ); 默认读取图像的原通道数  
//cvLoadImage( filename, 0 ); 强制转化读取图像为灰度图  
//cvLoadImage( filename, 1 ); 读取彩色图  
	if (pSrcImg == NULL)     
	{     
		cout <<"Fail to load image"<<endl;     
		return -1;     
	}     
  
	pRolloverlnImg = cvCloneImage(pSrcImg);       
	pRoverselnImg  = cvCloneImage(pSrcImg);  
  
  
	if ((pRolloverlnImg == NULL)&&(pRoverselnImg == NULL))     
	{     
		cout<<"Fail to clone the image"<<endl;     
		return -1;     
	}     
      
//-------------------------------------图像翻转处理-------------------------------  
  
  
	cvFlip(pRolloverlnImg, NULL,0);    //载入图像绕x轴上下翻转  
	cvFlip(pRoverselnImg,NULL,-1);
  
//--------------------------------------图像反转处理------------------------------  
	/*int length,width,step,channel;  
	uchar *data;  
	int i,j,k;  
  
	length=pRoverselnImg->height;  
	width=pRoverselnImg->width;  
	step=pRoverselnImg->widthStep;  
	channel=pRoverselnImg->nChannels;  
	data=(uchar *)pRoverselnImg->imageData;  
  
	for (i=0;i<length;i++)  
	{  
		for (j=0;j<width;j++)  
		{  
			for (k=0;k<channel;k++)  
			{  
				data[i*step+j*channel+k]=255-data[i*step+j*channel+k];  
			}  
		}  
	}  */
//*****************************************************************************************  
  
  
//cvNamedWindow("src",0);      //0表示以固定的窗口尺寸显示图像,不输入任何值默认和原图大小一样  
	cvNamedWindow(     "src"     );  
	cvNamedWindow(  "Xturnover"  );  
    cvNamedWindow(  "Picreverse" );  
  
cvShowImage("src", pSrcImg);     
cvShowImage("Xturnover", pRolloverlnImg);     
cvShowImage("Picreverse",pRoverselnImg );  
  
cvWaitKey(0);     
//  销毁已定义的指针变量
cvReleaseImage(&pSrcImg);     
cvReleaseImage(&pRolloverlnImg);  
cvReleaseImage(&pRoverselnImg);  
 //销毁生成的窗口
cvDestroyWindow("src");     
cvDestroyWindow("Xturnover");    
cvDestroyWindow("Picreverse");  
return 0;     
}
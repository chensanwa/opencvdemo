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
  
	pSrcImg = cvLoadImage("C:\\Users\\����\\Desktop\\OpenCV\\1.bmp",1);   
//cvLoadImage( filename, -1 ); Ĭ�϶�ȡͼ���ԭͨ����  
//cvLoadImage( filename, 0 ); ǿ��ת����ȡͼ��Ϊ�Ҷ�ͼ  
//cvLoadImage( filename, 1 ); ��ȡ��ɫͼ  
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
      
//-------------------------------------ͼ��ת����-------------------------------  
  
  
	cvFlip(pRolloverlnImg, NULL,0);    //����ͼ����x�����·�ת  
	cvFlip(pRoverselnImg,NULL,-1);
  
//--------------------------------------ͼ��ת����------------------------------  
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
  
  
//cvNamedWindow("src",0);      //0��ʾ�Թ̶��Ĵ��ڳߴ���ʾͼ��,�������κ�ֵĬ�Ϻ�ԭͼ��Сһ��  
	cvNamedWindow(     "src"     );  
	cvNamedWindow(  "Xturnover"  );  
    cvNamedWindow(  "Picreverse" );  
  
cvShowImage("src", pSrcImg);     
cvShowImage("Xturnover", pRolloverlnImg);     
cvShowImage("Picreverse",pRoverselnImg );  
  
cvWaitKey(0);     
//  �����Ѷ����ָ�����
cvReleaseImage(&pSrcImg);     
cvReleaseImage(&pRolloverlnImg);  
cvReleaseImage(&pRoverselnImg);  
 //�������ɵĴ���
cvDestroyWindow("src");     
cvDestroyWindow("Xturnover");    
cvDestroyWindow("Picreverse");  
return 0;     
}
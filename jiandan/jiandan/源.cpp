#include "stdio.h"
#include "stdlib.h"
#include <math.h>
//#include <opencv2\opencv.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>
#include "cv.h"
#include "highgui.h"
#include <iostream> 
#include <time.h>

using namespace std;  
using namespace cv;
//int count ;
#define NUMBER 1930

struct Line
{
    int i ; //ָ���ڼ�����
	double Length ;
};

struct VCLine
{
    int x1, x2 ;
	int y1 , y2;
	int i ; //��i���߶�
};


struct DOT
{
    int i ;			//ָ����͵�
	CvSeq*  line;	// ��͵��Ӧ�ı߿�
};

//ͼ����
IplImage*  Reverse_Img(IplImage* src)
{
	
	IplImage*reverse_img = NULL;

	reverse_img = cvCreateImage(cvGetSize(src),8,3); //1ͨ�� 
	reverse_img = cvCloneImage(src);  
	CvScalar s ;
	for(int i = 0 ; i < src->height ; i++)
	{
		for(int j = 0 ; j < src->width ; j++)
		{
			s = cvGet2D(src,i,j);
			cvSet2D(reverse_img,(src->height)-i-1,(src->width)-j-1,s);
		 }
	}

	return reverse_img;
}


//ͼ���ֵ��
IplImage* Binary_img(IplImage* src)
{

    IplImage *binary_image = NULL;
	binary_image = cvCloneImage(src);
    CvScalar s;
	
    for (int i=0;i<src->height;i++)
    {
        for (int j=0;j<src->width;j++)
        {
            s =  cvGet2D(src,i,j);
            
            if (s.val[0] > 128)
            {
                s.val[0]=s.val[1]=s.val[2]=255;
                cvSet2D(src,i,j,s);
            }
            else
            {
                s.val[0]=s.val[1]=s.val[2]=0;
                cvSet2D(src,i,j,s);
            }
        }
    }

	cvCopy(src,binary_image);

	return binary_image;
}


//����Ŀ������
IplImage* Find_ROI(IplImage* src)
{

	struct DOT dot;
	dot.i = -1;


	IplImage *Img = NULL;
	Img = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
	cvZero(Img);

	CvSeq *cont = NULL;
	CvMemStorage *storage = 0;
	storage = cvCreateMemStorage(0);

	IplImage *tempImg = 0;
	tempImg = cvCloneImage(src);


	cvFindContours( tempImg, storage, &cont, sizeof(CvContour),
					CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) ); //�ҵ���������

	///////////////////////////////////////////////////////////////////////////////////
	if(cont == NULL)
	{
	  return NULL;
	}


	for(;cont;cont = cont->h_next)
	{
		for (int i=0 ; i<cont->total; ++i)  
		{  
			CvPoint* p  =  CV_GET_SEQ_ELEM(CvPoint,cont,i);
			if(p->y > dot.i)
			{
				dot.i = p->y;
				dot.line = cont;
			}
			else continue ;
		}  
	}

	cvDrawContours( src,dot.line, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 0,  CV_FILLED, 8);

	CvRect aRect = cvBoundingRect( dot.line, 0 );
	cvSetImageROI(src, cvRect(aRect.x,aRect.y ,aRect.width,aRect.height ));

	IplImage *BwImg = NULL;

	BwImg = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
	cvCopy(src, BwImg, NULL);
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\BwImg.png",BwImg);

	cvReleaseImage(&Img);
	cvReleaseImage(&tempImg);
	cvReleaseMemStorage(&storage);

	return BwImg;
}

//ͼ��ɫ
IplImage* Oppose_color(IplImage* src)
{

	IplImage* temp_src = NULL;  



	temp_src = cvCreateImage(cvGetSize(src),8,1); //1ͨ��  
	temp_src = cvCloneImage(src);  
	CvScalar s;

	for(int i = 0 ; i < src->height ; i++)
	{
		for(int j = 0 ; j < src->width ; j++)
		{

			s = cvGet2D(src,i,j);
			if(s.val[0]>0)
			{
				s.val[0]=s.val[1]=s.val[2]=0;
				cvSet2D(src,i,j,s);
			}
			else
			{
				s.val[0] = s.val[1]=s.val[2]=255;
				cvSet2D(src,i,j,s);
			}
		}

	}

	cvCopy(src,temp_src);
	return temp_src;
}

//ͼ��ϸ��
void cvThin( IplImage* src, IplImage* dst, int iterations=1)
{
	CvSize size = cvGetSize(src);
	cvCopy(src, dst);
	int n = 0,i = 0,j = 0;

	for(n=0; n<iterations; n++)
	{
		IplImage* t_image = cvCloneImage(dst);
		for(i=0; i<size.height;  i++)
		{
			for(j=0; j<size.width; j++)
			{
				if(CV_IMAGE_ELEM(t_image,uchar,i,j)==1)
				{
					int ap=0;
					int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,uchar, i-1, j);
					int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar, i-1, j+1);
					if (p2==0 && p3==1)
					{
						ap++;
					}
					int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar,i,j+1);
					if(p3==0 && p4==1)
					{
						ap++;
					}
					int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j+1);
					if(p4==0 && p5==1)
					{
						ap++;
					}
					int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j);
					if(p5==0 && p6==1)
					{
						ap++;
					}
					int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j-1);
					if(p6==0 && p7==1)
					{
						ap++;
					}
					int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i,j-1);
					if(p7==0 && p8==1)
					{
						ap++;
					}
					int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i-1,j-1);
					if(p8==0 && p9==1)
					{
						ap++;
					}
					if(p9==0 && p2==1)
					{
						ap++;
					}
					if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)
					{
						if(ap==1)
						{
							if(!(p2 && p4 && p6))
							{
								if(!(p4 && p6 && p8))
								{
									CV_IMAGE_ELEM(dst,uchar,i,j)=0;
								}
							}
						}
					}
				}
			}
		}

		cvReleaseImage(&t_image);
		t_image = cvCloneImage(dst);
		for(i=0; i<size.height;  i++)
		{
			for(int j=0; j<size.width; j++)
			{
				if(CV_IMAGE_ELEM(t_image,uchar,i,j)==1)
				{
					int ap=0;
					int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,uchar, i-1, j);
					int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar, i-1, j+1);
					if (p2==0 && p3==1)
					{
						ap++;
					}
					int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar,i,j+1);
					if(p3==0 && p4==1)
					{
						ap++;
					}
					int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j+1);
					if(p4==0 && p5==1)
					{
						ap++;
					}
					int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j);
					if(p5==0 && p6==1)
					{
						ap++;
					}
					int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i+1,j-1);
					if(p6==0 && p7==1)
					{
						ap++;
					}
					int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i,j-1);
					if(p7==0 && p8==1)
					{
						ap++;
					}
					int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,uchar,i-1,j-1);
					if(p8==0 && p9==1)
					{
						ap++;
					}
					if(p9==0 && p2==1)
					{
						ap++;
					}
					if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)
					{
						if(ap==1)
						{
							if(p2*p4*p8==0)
							{
								if(p2*p6*p8==0)
								{
									CV_IMAGE_ELEM(dst, uchar,i,j)=0;
								}
							}
						}
					}                   
				}
			}
		}  

		cvReleaseImage(&t_image);
	}
}

//�Ǽ���ȡ
IplImage* Skeleton_Extraction(IplImage* src)
{

	IplImage *src_temp = NULL,*src_dst = NULL ;

	if(!src)
	{
		return 0;
	}

	src_temp = cvCloneImage(src);
	src_dst = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
	cvZero(src_dst);
	cvThreshold(src,src_temp,128,1,CV_THRESH_BINARY_INV);
	//����ֵ������ͼ��ת����0��1��ʽ


	for(int k = 0 ; k < 3 ; k++)
	{

		cvThin(src_temp,src_dst,4);//ϸ����ͨ���޸�iterations������һ��ϸ��
		
		src_dst = src_temp;
		
		//cvSaveImage("C:\\Users\\Administrator\\Desktop\\10.png",src_temp );
		//system("PAUSE");

	}//for ����ϸ��4�Σ�������ȡ�Ǽ�

	//����ֵͼ��ת���ɻҶȣ��Ա���ʾ
	int i = 0,j = 0;
	CvSize size = cvGetSize(src_dst);
	for(i=0; i<size.height;  i++)
	{
		for(j=0; j<size.width; j++)
		{
			if(CV_IMAGE_ELEM(src_dst,uchar,i,j)==1)
			{
				CV_IMAGE_ELEM(src_dst,uchar,i,j) = 0;
			}
			else
			{
				CV_IMAGE_ELEM(src_dst,uchar,i,j) = 255;
			}
		}
	}

	return src_dst;
}

//ͼ��Ŵ�
IplImage* Resize_Img(IplImage* src)
{  
	
    IplImage* resize_img=cvCreateImage(cvSize(src->width*2,src->height*2),8,1);
	//��ͨ��
	//ÿ��Ԫ�أ����أ�ͨ����.������ 1, 2, 3 �� 4.ͨ���ǽ����ȡ��
	//������ԭ��2��

   	cvResize(src,resize_img,CV_INTER_NN);

	return resize_img;
}


//ͼ��Ǽ��ٴ���ȡ
IplImage* Skeleton_Extraction_Again(IplImage* src)
{

	IplImage *src_temp = NULL,*src_dst = NULL ;

	if(!src)
	{
		return 0;
	}

	src_temp = cvCloneImage(src);

	src_dst = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
	cvZero(src_dst);
	cvThreshold(src,src_temp,128,1,CV_THRESH_BINARY_INV);

	//����ֵ������ͼ��ת����0��1��ʽ
	for(int k = 0 ; k < 4 ; k++)
	{

		cvThin(src_temp,src_dst,4);//ϸ����ͨ���޸�iterations������һ��ϸ��
		src_dst = src_temp;
	}//for ����ϸ��4�Σ�������ȡ�Ǽ�


	//����ֵͼ��ת���ɻҶȣ��Ա���ʾ
	int i = 0,j = 0;
	CvSize size = cvGetSize(src_dst);
	for(i=0; i<size.height;  i++)
	{
		for(j=0; j<size.width; j++)
		{
			if(CV_IMAGE_ELEM(src_dst,uchar,i,j)==1)
			{
				CV_IMAGE_ELEM(src_dst,uchar,i,j) = 0;
			}
			else
			{
				CV_IMAGE_ELEM(src_dst,uchar,i,j) = 255;
			}
		}
	}

	return src_dst;
}

//��ͨ��ͼ��ɫ
void Reserve_Color_1(IplImage* src)
{
	CvScalar s;
	for (int i=0;i<src->height;i++)
	{
		for (int j=0;j<src->width;j++)
		{
			s =  cvGet2D(src,i,j);
			if(s.val[0]==255)
			{
				s.val[0]=0;
				cvSet2D(src, i, j, s);
			}
			else if(s.val[0]==0)
			{
				s.val[0]=255;
				cvSet2D(src, i, j, s);
			}

		}
	}

}

//��ͨ��ͼ����ɫ
void Set(IplImage* src , IplImage* temp)
{
	CvScalar s;

	for (int i=0;i<src->height;i++)
	{
		for (int j=0;j<src->width;j++)
		{
			s =  cvGet2D(src,i,j);
			if(s.val[0]==255)
			{
				s.val[0]=s.val[1]=s.val[2]=255;
				cvSet2D(temp, i, j, s);
			}
			else if(s.val[0]==0)
			{
				s.val[0]=s.val[1]=s.val[2]=0;
				cvSet2D(temp, i, j, s);
			}
		}

	}

}

//��������
int Find_V(CvPoint* line)
{
    
	int X_length = abs(line[0].x - line[1].x);
	int Y_length = abs(line[0].y - line[1].y);

	if(X_length >= Y_length)
	{
		 return 0 ;
	}
	else
	{
		return 1;
	}

	return 0;

}

//������ߣ��ʺϲ�������ߺ�����ߣ�
int Search_largest_vline(struct VCLine Vline[5] ,int vnumber)  
{

	int i ,j;
	j = 0;
	int x_temp , y_temp , length1 , length2;

	x_temp = abs(Vline[0].x1 - Vline[0].x2);
	y_temp = abs(Vline[0].y1 - Vline[0].y2);
	length1 = x_temp*x_temp + y_temp*y_temp;

	for(i = 1 ; i < vnumber ; i++)
	{
		x_temp = abs(Vline[i].x1 - Vline[i].x2);
		y_temp = abs(Vline[i].y1 - Vline[i].y2);
		length2 = x_temp*x_temp + y_temp*y_temp;
		if(length1 < length2)
		{
		    j = i;
		    length1 =  length2;
		}
	
	}
	return j ;
}

//����任ֱ�����
int  HoughLines(IplImage* src , struct Line &Vertical ,struct Line &Across, int &Mark )
{
	 VCLine  Vline[5] ={0};
	 VCLine  Cline[5] ={0};

    static  int count = 0;

	IplImage* dst = NULL;
	IplImage* color_dst = NULL;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = NULL;

	int i ;

	int v_count, c_count;  //���ߺ��ߵ�ǰָ��ڵ�

	dst = cvCreateImage( cvGetSize(src), 8, 1 );
	cvCopy(src , dst ,  NULL);
	Reserve_Color_1(dst);
	color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
	Set(src , color_dst);




	lines = cvHoughLines2( dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 20 ,20 , 50 );

	int V_judge,C_judge; //�ж����ߺͺ����Ƿ����

	V_judge = C_judge = 0;

	for( i = 0 ,v_count =0,c_count = 0; i < lines->total; i++ )
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,i);

		int V = Find_V(line);

		if(V)
		{
			Vline[v_count].x1 = line[0].x;
			Vline[v_count].y1 = line[0].y;
			Vline[v_count].x2 = line[1].x;
			Vline[v_count].y2 = line[1].y;
			Vline[v_count].i = i;


			V_judge++;
			v_count++;
		}

		else
		{
			Cline[c_count].x1 = line[0].x;
			Cline[c_count].y1 = line[0].y;
			Cline[c_count].x2 = line[1].x;
			Cline[c_count].y2 = line[1].y;
			Cline[c_count].i = i;

			C_judge++;
			c_count++; 

		}
		
		//����������ϵ�ֱ��
		cvLine( color_dst, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

			
	}
   // cvSaveImage("C:\\Users\\Administrator\\Desktop\\color_dst.png",color_dst);

	int V_X, C_X;

	if((!v_count)&&(!c_count))
	{
	   Mark = 0;
	   return 0;
	}



	if(v_count)
	{
		v_count =  Search_largest_vline(Vline ,v_count);
		v_count =  Vline[v_count].i;
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,v_count);

		V_X = (line[0].x + line[1].x)/2;
	}

	if(c_count)
	{

		c_count =  Search_largest_vline(Cline ,c_count);
		c_count =  Cline[c_count].i;
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines,c_count);
		C_X = (line[0].x + line[1].x)/2;

	}


   //�ж��Ƿ��к������жϷ���
	if(C_judge == 0)
	{ 
		Mark = 1;
		printf("%d   ֱ�ߣ�\n",  count++);
	}
	else
	{
		if(C_X > V_X)
		{ 
			Mark = 2;
			printf("%d   �ҹգ�\n", count++);
		}
		else
		{
			Mark = 3;
			printf("%d   ��գ�\n", count++); 
		}

	}

	cvReleaseImage(&dst);	
	cvReleaseMemStorage(&storage);  

	return 1;
}



int main()
{	IplImage *src;
	src=cvLoadImage("1.jpg");
	int Result=-1;
 
	//ͼ����
	//IplImage *reverse_img = NULL;
	//reverse_img = Reverse_Img(src) ;
	//cvShowImage("reverse_img",reverse_img);
	//cvWaitKey(100);
	//if(!reverse_img)
	//{
	//	Result = -1;
	//	return Result;

	//   //printf("����ͼƬ���ش���1!\n");
	//   //return 0;
	//  // exit(-1);
	//}

	//ͼ��ҶȻ�
	IplImage* gray_image =  NULL;
	gray_image = cvCreateImage(cvGetSize(src),8,1);
	if(!gray_image)
	{
		Result = -1;
		return Result;
	  // printf("�Ҷ�ͼƬ���ش���2!\n");
	    // return 0;
	  // exit(-1);
	}
	cvCvtColor(src,gray_image,CV_BGR2GRAY);
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\gray_image .png",gray_image );

	////ͼ���ֵ��
	IplImage* binary_image = NULL;
	binary_image = Binary_img(gray_image);
	if(!binary_image)
	{
		Result = -1;
		return Result;
	   //printf("��ֵ��ͼƬ���ش���3!\n");
	     //return 0;
	  // exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\binary_image .png",binary_image );

	//ͼ��ʴ
	IplImage *eliminate_noise = NULL;  
	eliminate_noise = cvCreateImage(cvGetSize(binary_image), 8, 1);  
	cvErode(binary_image,eliminate_noise, NULL,1); //��ʴ  
	if(!eliminate_noise)
	{
		Result = -1;
		return Result;
	    //printf("��ʴͼƬ���ش���4!\n");
	     //return 0;
	  // exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\eliminate_noise .png",eliminate_noise );
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\eliminate_noise .bmp",eliminate_noise );
	/*
	IplImage *oppose_color1 = NULL;
	oppose_color1 = Oppose_color(eliminate_noise);
	if(!oppose_color1)
	{
		Result = -1;
		return Result;
		//printf("��ɫͼ����ش���6!\n");
		//return 0;
		// exit(-1);
	}
	cvSaveImage("C:\\Users\\Administrator\\Desktop\\oppose_color1 .png",oppose_color1);
	*/


	//Ŀ���������ȡ
	IplImage * ROI =NULL ;
	ROI = Find_ROI(eliminate_noise);
	if(!ROI)
	{
		Result = -1;
		return Result;
		//printf("Ŀ������ͼ����ش���5!\n");
		//return 0;
		// exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\ROI .png",ROI);

    //ͼ��ɫ
	IplImage *oppose_color = NULL;
	oppose_color = Oppose_color(ROI);
	if(!oppose_color)
	{
		Result = -1;
		return Result;
		//printf("��ɫͼ����ش���6!\n");
		//return 0;
		// exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\oppose_color .png",oppose_color);
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\oppose_color .bmp",oppose_color);

	////�Ǽ���ȡ
	 IplImage  *skeleton_extraction_img = NULL;
	 skeleton_extraction_img = Skeleton_Extraction( oppose_color);
	 if(!oppose_color)
	 {
		 Result = -1;
		return Result;
		// printf("�Ǽ���ȡͼ����ش���7!\n");
		// return 0;
		 // exit(-1);
	 }
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\skeleton_extraction_img .png",skeleton_extraction_img);


	 //ͼ��Ŵ�
	 IplImage* resize_img = NULL;
	 resize_img = Resize_Img(skeleton_extraction_img);
	 if(!resize_img)
	{
		Result = -1;
		return Result;
	    //printf("�Ŵ�ͼƬ���ش���8!\n");
	    //return 0;
	  // exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\resize_img .png",resize_img);

	//ͼ��Ǽ��ٴ���ȡ
    IplImage *skeleton_extraction_img_again = NULL;
	skeleton_extraction_img_again = Skeleton_Extraction_Again( resize_img);
	if(!skeleton_extraction_img_again)
	{
		Result = -1;
		return Result;
	   //printf("�ٴιǼ���ȡͼƬ���ش���9!\n");
	   //return 0;
	  // exit(-1);
	}
	//cvSaveImage("C:\\Users\\Administrator\\Desktop\\skeleton_extraction_img_again .png",skeleton_extraction_img_again);


	//����ֱ�����
	int houghlines = 0;

	struct Line Vertical , Across;
	houghlines = HoughLines(skeleton_extraction_img_again ,Vertical, Across ,Result);

	if(!houghlines)
	{
		Result = -1;
		return Result;
		//printf("����ͼ��ʶ�����10!\n");
		//return 0;
		// exit(-1);
	}

	////printf("%d\n",Mark);


	//cvReleaseImage(&reverse_img);
	cvReleaseImage(&gray_image);
	cvReleaseImage(&binary_image);
	cvReleaseImage(&eliminate_noise);
	cvReleaseImage(&ROI);
	cvReleaseImage(&oppose_color);
	cvReleaseImage(&skeleton_extraction_img);
	cvReleaseImage(&resize_img);
	cvReleaseImage(&skeleton_extraction_img_again);
	//cvReleaseImage(&oppose_color1);


	//
	////cvNamedWindow("reverse_img",CV_WINDOW_AUTOSIZE);  
	////cvShowImage( "reverse_img",reverse_img);

}




//int _tmain(int argc, _TCHAR* argv[])
//{
//	int Result = -1;
//	char filename[100];
//
////	int T_F = -1;
//	//int count = 0;
//
//	clock_t _start,_end;   //��������clock_t���ͱ��������Ƕ���long�ͣ����»��߿�ͷ�Ǳ�����ؼ����ظ�
//	float duration;  //���ε���clock������ʱ���
//	_start=clock();
////
//	for(int i = 0 ; i < 220 ; i++)
//	{
//
//		IplImage * src = NULL;
//		//src = cvLoadImage("C:/Users/Administrator/Desktop/4/img2/1 (1).bmp",1);
//		//src = cvLoadImage("C:\\Users\\Administrator\\Desktop\\1.bmp",1);
//		//sprintf(filename,".\\0324.bmp");
//		sprintf(filename,"/home/zou/Desktop/6.png",i);
//		src = cvLoadImage(filename,1);
//		if(src == NULL)
//		{
//			printf("ԭʼͼ����ش���!\n");
//			system("PAUSE");
//			return 0;
//		}
//
//
//	    Img_Result(src,Result);
//		//printf("%d\n", Result);
//		cvReleaseImage(&src);
//
//	}
//	_end=clock();
//	duration=(float)(_end-_start)/CLOCKS_PER_SEC;  // ��ʱ��ת��Ϊ��
//	//printf("%f \n",duration);
//	//printf("%f \n",duration*1.0/120);
//
//	system("PAUSE");
//
//	return 0;
//}
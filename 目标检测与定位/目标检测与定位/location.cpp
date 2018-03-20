#ifdef _CH_  
#pragma package <opencv>  
#endif  
  
#ifndef _EiC  
#include "cv.h"  
#include "highgui.h"  
#include <stdio.h>  
#include <math.h>  
#include <string.h>  
#endif  
  
int thresh = 50;  
IplImage* img = 0;  
IplImage* img0 = 0;  
CvMemStorage* storage =  cvCreateMemStorage(0);  
CvPoint pt[4];  
const char* wndname = "Square Detection Demo";  
  
// helper function:  
// finds a cosine of angle between vectors  
// from pt0->pt1 and from pt0->pt2   
double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )  
{  
    double dx1 = pt1->x - pt0->x;  
    double dy1 = pt1->y - pt0->y;  
    double dx2 = pt2->x - pt0->x;  
    double dy2 = pt2->y - pt0->y;  
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);  
}  
  
// returns sequence of squares detected on the image.  
//返回图像中的四边形序列  
// the sequence is stored in the specified memory storage  
//序列存储在特定的storage中  
CvSeq* findSquares4( IplImage* img, CvMemStorage* storage )  
{  
      
    CvSeq* contours;  
    int i, c, l, N = 11;  
    CvSize sz = cvSize( img->width & -2, img->height & -2 );  
    IplImage* timg = cvCloneImage( img ); // make a copy of input image复制输入图像  
    IplImage* gray = cvCreateImage( sz, 8, 1 );   
    IplImage* pyr = cvCreateImage( cvSize(sz.width/2, sz.height/2), 8, 3 );//尺度减小为1/2  
    IplImage* tgray;  
    CvSeq* result;  
    double s, t;  
    // create empty sequence that will contain points -  
    // 4 points per square (the square's vertices)  
    //建立一个空序列存储每个四边形的四个顶点  
    CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );  
      
    // select the maximum ROI in the image  
    // with the width and height divisible by 2  
    //设定timg的ROI为最大值（）  
    cvSetImageROI( timg, cvRect( 0, 0, sz.width, sz.height ));  
      
    // down-scale and upscale the image to filter out the noise  
    //金字塔方式升和降来滤波去除噪声  
    //cvPyrDown( timg, pyr, 7 );  
    //cvPyrUp( pyr, timg, 7 );  
    tgray = cvCreateImage( sz, 8, 1 );  
      
    // find squares in every color plane of the image  
    //寻找每个通道的四边形  
    for( c = 0; c < 3; c++ )  
    {  
        // extract the c-th color plane  
        //提取第c个通道  
        cvSetImageCOI( timg, c+1 );  
        cvCopy( timg, tgray, 0 );  
          
        // try several threshold levels  
        //尝试每个阈值等级  
        for( l = 0; l < N; l++ )  
        {  
            // hack: use Canny instead of zero threshold level.  
            // Canny helps to catch squares with gradient shading     
            //Canny代替零阈值，Canny通过梯度变化程度大来寻找四边形  
  
            if( l == 0 )  
            {  
                // apply Canny. Take the upper threshold from slider  
                // and set the lower to 0 (which forces edges merging)  
                // l=0使用Canny  
                cvCanny( tgray, gray,60, 180, 3 );  
                //   
                // dilate canny output to remove potential  
                // holes between edge segments   
                cvDilate( gray, gray, 0, 1 );  
            }  
            else  
            {  
                // apply threshold if l!=0:  
                // tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0  
                //cvThreshold( tgray, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );  
                cvThreshold( tgray, gray, 50, 255, CV_THRESH_BINARY );  
            }  
              
            // find contours and store them all as a list  
            cvFindContours( gray, storage, &contours, sizeof(CvContour),  
                CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );  
              
            // test each contour  
            while( contours )  
            {  
                // approximate contour with accuracy proportional  
                // to the contour perimeter  
                //用指定精度逼近多边形曲线   
                result = cvApproxPoly( contours, sizeof(CvContour), storage,  
                    CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );  
                // square contours should have 4 vertices after approximation  
                // relatively large area (to filter out noisy contours)  
                // and be convex.  
                // Note: absolute value of an area is used because  
                // area may be positive or negative - in accordance with the  
                // contour orientation  
                if( result->total == 4 &&  
                    fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 1000 &&   //cvContourArea计算整个轮廓或部分轮廓的面积   
                    cvCheckContourConvexity(result) )                   //CheckContourConvexity  
                {  
                    s = 0;  
                      
                    for( i = 0; i < 5; i++ )  
                    {  
                        // find minimum angle between joint  
                        // edges (maximum of cosine)  
                        if( i >= 2 )  
                        {  
                            t = fabs(angle(  
                            (CvPoint*)cvGetSeqElem( result, i ),  
                            (CvPoint*)cvGetSeqElem( result, i-2 ),  
                            (CvPoint*)cvGetSeqElem( result, i-1 )));  
                            s = s > t ? s : t;  
                        }  
                    }  
                      
                    // if cosines of all angles are small  
                    // (all angles are ~90 degree) then write quandrange  
                    // vertices to resultant sequence   
                    if( s < 0.3 )  
                        for( i = 0; i < 4; i++ )  
                            cvSeqPush( squares,  
                                (CvPoint*)cvGetSeqElem( result, i ));  
                }  
                  
                // take the next contour  
                contours = contours->h_next;  
            }  
        }  
    }  
      
    // release all the temporary images  
    cvReleaseImage( &gray );  
    cvReleaseImage( &pyr );  
    cvReleaseImage( &tgray );  
    cvReleaseImage( &timg );  
      
    return squares;  
}  
  
  
// the function draws all the squares in the image  
void drawSquares( IplImage* img, CvSeq* squares )  
{  
    CvSeqReader reader;  
    IplImage* cpy = cvCloneImage( img );  
    int i;  
      
    // initialize reader of the sequence  
    cvStartReadSeq( squares, &reader, 0 );  
      
    // read 4 sequence elements at a time (all vertices of a square)  
    for( i = 0; i < squares->total; i += 4 )  
    {  
        CvPoint* rect = pt;  
        int count = 4;  
          
        // read 4 vertices  
        memcpy( pt, reader.ptr, squares->elem_size );  
        CV_NEXT_SEQ_ELEM( squares->elem_size, reader );  
        memcpy( pt + 1, reader.ptr, squares->elem_size );  
        CV_NEXT_SEQ_ELEM( squares->elem_size, reader );  
        memcpy( pt + 2, reader.ptr, squares->elem_size );  
        CV_NEXT_SEQ_ELEM( squares->elem_size, reader );  
        memcpy( pt + 3, reader.ptr, squares->elem_size );  
        CV_NEXT_SEQ_ELEM( squares->elem_size, reader );  
          
        // draw the square as a closed polyline   
        cvPolyLine( cpy, &rect, &count, 1, 1, CV_RGB(0,255,0), 3, CV_AA, 0 );  
    }  
      
    // show the resultant image  
    cvShowImage( wndname, cpy );  
    cvReleaseImage( &cpy );  
}  
  
  
void on_trackbar( int a )  
{  
    if( img )  
        drawSquares( img, findSquares4( img, storage ) );  
}  
//char* names[] = { "D:/image/car/00.jpg", "D:/image/car/01.jpg", "D:/image/car/02.jpg",  
//                  "D:/image/car/03.jpg", "D:/image/car/04.jpg", "D:/image/car/05.jpg", 0 };  
//char* names[] = { "D:/image/car/car00.jpg", "D:/image/car/car01.jpg", "D:/image/car/car02.jpg",  
//                  "D:/image/car/car03.jpg", "D:/image/car/car04.jpg", "D:/image/car/car05.jpg", 0 };  
//char* names[] = { "D:/image/car/00sobel.jpg", "D:/image/car/01sobel.jpg", "D:/image/car/02sobel.jpg",  
//                "D:/image/car/03sobel.jpg", "D:/image/car/04sobel.jpg", "D:/image/car/05sobel.jpg", 0 };  
char* names[] = { "G:/l.jpg",   
                  /*"D:/image/car/0sobel_normal.jpg",  
                  "D:/image/car/08sobel_normal.jpg",  
                  "D:/image/car/09sobel_normal.jpg",   
                  "D:/image/car/10sobel_normal.jpg",  
                  "D:/image/car/11sobel_normal.jpg",  
                  "D:/image/car/12sobel_normal.jpg",   
                  "D:/image/car/13sobel_normal.jpg",  
                  "D:/image/car/14sobel_normal.jpg",  
                  "D:/image/car/15sobel_normal.jpg",   
                  "D:/image/car/16sobel_normal.jpg",  
                  "D:/image/car/17sobel_normal.jpg",  
                  "D:/image/car/18sobel_normal.jpg",   
                  "D:/image/car/19sobel_normal.jpg",  
                  "D:/image/car/20sobel_normal.jpg",  
                  "D:/image/car/21sobel_normal.jpg",   
                  "D:/image/car/22sobel_normal.jpg",  
                  "D:/image/car/23sobel_normal.jpg",  
                  "D:/image/car/00sobel_normal.jpg",   
                  "D:/image/car/01sobel_normal.jpg",  
                  "D:/image/car/02sobel_normal.jpg",  
                  "D:/image/car/03sobel_normal.jpg",   
                  "D:/image/car/04sobel_normal.jpg",  
                  "D:/image/car/05sobel_normal.jpg",  */
                  0 };  
int main(int argc, char** argv)  
{  
    int i, c;  
    // create memory storage that will contain all the dynamic data  
    storage = cvCreateMemStorage(0);  
  
    for( i = 0; names[i] != 0; i++ )  
    {  
        // load i-th image  
        img0 = cvLoadImage( names[i], 1 );  
        if( !img0 )  
        {  
            printf("Couldn't load %s/n", names[i] );  
            continue;  
        }  
        img = cvCloneImage( img0 );  
          
        // create window and a trackbar (slider) with parent "image" and set callback  
        // (the slider regulates upper threshold, passed to Canny edge detector)   
        cvNamedWindow( wndname,0 );  
        cvCreateTrackbar( "canny thresh", wndname, &thresh, 1000, on_trackbar );  
          
        // force the image processing  
        on_trackbar(0);  
        // wait for key.  
        // Also the function cvWaitKey takes care of event processing  
        c = cvWaitKey(0);  
        // release both images  
        cvReleaseImage( &img );  
        cvReleaseImage( &img0 );  
        // clear memory storage - reset free space position  
        cvClearMemStorage( storage );  
        if( c == 27 )  
            break;  
    }  
      
    cvDestroyWindow( wndname );  
      
    return 0;  
}  
  
#ifdef _EiC  
main(1,"squares.c");  
#endif  

// opencvDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "opencv.h"
#include "opencvDlg.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
//using namespace std;  
using namespace cv; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#define SCALE 1.0   //缩放比例




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopencvDlg 对话框




CopencvDlg::CopencvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CopencvDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CopencvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_STATIC, m_pictureControl);
}

BEGIN_MESSAGE_MAP(CopencvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CopencvDlg::On32771)
	ON_COMMAND(ID_32772, &CopencvDlg::On32772)
	ON_COMMAND(ID_32773, &CopencvDlg::On32773)
	ON_COMMAND(ID_32774, &CopencvDlg::On32774)
	ON_COMMAND(ID_32775, &CopencvDlg::On32775)
	ON_COMMAND(ID_32776, &CopencvDlg::On32776)
	ON_COMMAND(ID_32777, &CopencvDlg::On32777)
	ON_COMMAND(ID_32778, &CopencvDlg::On32778)
	ON_COMMAND(ID_32779, &CopencvDlg::On32779)
	ON_COMMAND(ID_32780, &CopencvDlg::On32780)
	ON_COMMAND(ID_32781, &CopencvDlg::On32781)
	ON_COMMAND(ID_32782, &CopencvDlg::On32782)
	ON_COMMAND(ID_32783, &CopencvDlg::On32783)
	ON_COMMAND(ID_32784, &CopencvDlg::On32784)
	ON_COMMAND(ID_32785, &CopencvDlg::On32785)
	ON_COMMAND(ID_32786, &CopencvDlg::On32786)
	ON_COMMAND(ID_32787, &CopencvDlg::On32787)
	ON_COMMAND(ID_32788, &CopencvDlg::On32788)
	ON_COMMAND(ID_32789, &CopencvDlg::On32789)
	ON_COMMAND(ID_32790, &CopencvDlg::On32790)
	ON_COMMAND(ID_32791, &CopencvDlg::On32791)
	ON_COMMAND(ID_32792, &CopencvDlg::On32792)
	ON_COMMAND(ID_32793, &CopencvDlg::On32793)
	ON_COMMAND(ID_32795, &CopencvDlg::On32795)
	ON_COMMAND(ID_32794, &CopencvDlg::On32794)
END_MESSAGE_MAP()


// CopencvDlg 消息处理程序

BOOL CopencvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CopencvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopencvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopencvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvDlg::On32771()
{	//插入图片
	// TODO: 在此添加命令处理程序代码
	CBitmap bitmap; // CBitmap对象，用于加载位图
    HBITMAP hBmp;   // 保存CBitmap加载的位图的句柄
 
    bitmap.LoadBitmapW(IDB_BITMAP1);    // 将位图IDB_BITMAP1加载到bitmap
    hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取bitmap加载位图的句柄
    m_pictureControl.SetBitmap(hBmp);   // 设置图片空间m_pictureControl的位图为IDB_BITMAP1
}

IplImage* BitmapToIplImage(HBITMAP hBmp)  
{  //bitmap转为iplimage格式
    BITMAP bmp;      
      
    GetObject(hBmp, sizeof(BITMAP), &bmp);  
    int depth     = (bmp.bmBitsPixel == 1) ? IPL_DEPTH_1U : IPL_DEPTH_8U;  
    int nChannels = (bmp.bmBitsPixel == 1) ? 1 : bmp.bmBitsPixel/8;      
      
    IplImage* img = cvCreateImage(cvSize(bmp.bmWidth,bmp.bmHeight), depth, nChannels);    
      
    BYTE *pBuffer = new BYTE[bmp.bmHeight*bmp.bmWidth*nChannels];      
    GetBitmapBits(hBmp, bmp.bmHeight*bmp.bmWidth*nChannels, pBuffer);  
    memcpy(img->imageData, pBuffer, bmp.bmHeight*bmp.bmWidth*nChannels);     
    delete pBuffer;  
  
    IplImage *dst = cvCreateImage(cvGetSize(img), img->depth,3);      
    cvCvtColor(img, dst, CV_BGRA2BGR);     
    cvReleaseImage(&img);     
    return dst;  
}  

void CopencvDlg::On32772()
{
	// 水平翻转，Y方向对称即X方向上翻滚
	IplImage *pSrcImg = NULL;
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);	

	HBITMAP bmp = HBITMAP(bitmap);


	pSrcImg=BitmapToIplImage(bmp);
	cvFlip(pSrcImg,NULL,1);		//翻转函数
	cvNamedWindow(  "Xturnover"  ); //建立窗口
	cvShowImage("Xturnover", pSrcImg);	//在窗口中显示图片
	cvWaitKey(0);	//暂停，需要用户敲击任意键
	cvReleaseImage(&pSrcImg);	//销毁指针
	cvDestroyWindow("Xturnover");	//销毁窗口

}


void CopencvDlg::On32773()
{
	// 垂直翻转，X方向对称即Y方向上翻滚
	IplImage *pSrcImg = NULL;
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);

	HBITMAP bmp = HBITMAP(bitmap);


	pSrcImg=BitmapToIplImage(bmp);
	cvFlip(pSrcImg,NULL,0);
	cvNamedWindow(  "Yturnover"  ); 
	cvShowImage("Yturnover", pSrcImg);
	cvWaitKey(0); 
	cvReleaseImage(&pSrcImg);
	cvDestroyWindow("Yturnover");
}


void CopencvDlg::On32774()
{
	// 水平垂直翻转，
	IplImage *pSrcImg = NULL;
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);

	HBITMAP bmp = HBITMAP(bitmap);


	pSrcImg=BitmapToIplImage(bmp);
	cvFlip(pSrcImg,NULL,-1);
	cvNamedWindow(  "Picreverse"  ); 
	cvShowImage("Picreverse", pSrcImg);
	cvWaitKey(0); 
	cvReleaseImage(&pSrcImg);
	cvDestroyWindow("Picreverse");
}

BOOL HBitmapToMat(HBITMAP& _hBmp,Mat& _mat)
{
	BITMAP bmp;    
	GetObject(_hBmp,sizeof(BITMAP),&bmp);    
	int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;   
	int depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;    
	Mat v_mat;
	v_mat.create(cvSize(bmp.bmWidth,bmp.bmHeight), CV_MAKETYPE(CV_8U,nChannels));
	GetBitmapBits(_hBmp,bmp.bmHeight*bmp.bmWidth*nChannels,v_mat.data);  
	_mat=v_mat;
	return TRUE;   
}

void CopencvDlg::On32775()
{
	// 膨胀
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat out;
	//进行膨胀操作
    dilate(image,out, element);
 
	namedWindow("dilate");
	imshow("dilate", out);
 //   //显示效果图
	//IplImage *pSrcImg = NULL;
	//*pSrcImg=(IplImage)(image);
	//cvNamedWindow(  "dilate"  ); //建立窗口
	//cvShowImage("dilate", pSrcImg);	//在窗口中显示图片
	//cvWaitKey(0);	//暂停，需要用户敲击任意键
	//cvReleaseImage(&pSrcImg);	//销毁指针
	//cvDestroyWindow("dilate");	//销毁窗口
}


void CopencvDlg::On32776()
{
	// TODO: 在此添加命令处理程序代码
	// 腐蚀
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat out;
	//进行腐蚀操作
    erode(image,out, element);
	namedWindow("erode");
	imshow("erode", out);
}


void CopencvDlg::On32777()
{
	// 开运算
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
    morphologyEx(image,image, MORPH_OPEN, element);
	//显示效果图   
    imshow("开运算", image); 
	waitKey(0);  
}


void CopencvDlg::On32778()
{
	//闭运算
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
    morphologyEx(image,image, MORPH_CLOSE, element);  
    //显示效果图   
    imshow("闭运算", image);   
   
    waitKey(0);  
}


void CopencvDlg::On32779()
{
	//Morphological Gradient(形态学梯度）
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	 //进行形态学操作  
    morphologyEx(image,image, MORPH_GRADIENT, element);  
       //显示效果图   
    imshow("Morphological Gradient(形态学梯度）", image);   
   
    waitKey(0);   
   
}


void CopencvDlg::On32780()
{
	//顶帽
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
       //进行形态学操作  
       morphologyEx(image,image, MORPH_TOPHAT, element);  
       //显示效果图   
       imshow("顶帽运算", image);   
   
       waitKey(0);   
}


void CopencvDlg::On32781()
{
	//黑帽
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作  
    morphologyEx(image,image, MORPH_BLACKHAT, element);  
       //显示效果图   
    imshow("黑帽运算", image);   
   
    waitKey(0);   
   
}


void CopencvDlg::On32782()
{
	// 均值滤波

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//均值滤波
	Mat dst;
    //image:输入图像
    //dst:输出图像
    //模板大小
    //Point(-1,-1):被平滑点位置，为负值取核中心
    blur(image,dst,Size(3,3),Point(-1,-1));
    imshow("均值滤波", dst);   
   
    waitKey(0);   
}


void CopencvDlg::On32783()
{
	// 高斯滤波
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//均值滤波
	Mat dst;
	//src:输入图像
    //dst:输出图像
   //Size(5,5)模板大小，为奇数
    //x方向方差
   //Y方向方差
    GaussianBlur(image,dst,Size(5,5),0,0);
	imshow("高斯滤波", dst);   
   
    waitKey(0);  
}


void CopencvDlg::On32784()
{
	//中值滤波
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//中值滤波
	Mat dst;
	//image:输入图像
        //dst::输出图像
        //模板宽度，为奇数
    medianBlur(image,dst,3);
	imshow("中值滤波", dst);   
   
    waitKey(0);  
}


void CopencvDlg::On32785()
{
	// 双边滤波
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//image:输入图像
    //dst:输入图像
    //滤波模板半径
    //颜色空间标准差
    //坐标空间标准差
    bilateralFilter(image,dst, 25, 25 * 2, 25 / 2);		//不清楚为什么这个函数在MFC中会报错
	namedWindow("双边滤波"); 
	imshow("双边滤波", dst);   
    waitKey(0);
}


void CopencvDlg::On32786()
{
	//放大(PyrUp)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//将图像放大两倍
	pyrUp(image, dst, Size(image.cols * 2, image.rows * 2));
	namedWindow("放大(PyrUp)"); 
	imshow("放大(PyrUp)", dst);
	waitKey(0);
}


void CopencvDlg::On32787()
{
	// 缩小（PyrDown)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//缩小两倍 
	pyrDown(image, dst, Size(image.cols / 2, image.rows / 2));
	namedWindow("缩小(PyrUp)"); 
	imshow("缩小(PyrUp)", dst);
	waitKey(0);

}


void CopencvDlg::On32788()
{
	// 放大（Resize)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//放大两倍
	resize(image,dst,Size(image.cols*2,image.rows*2),0,0,INTER_LINEAR);
	namedWindow("放大(Resize)"); 
	imshow("放大(Resize)", dst);
	waitKey(0);
}


void CopencvDlg::On32789()
{
	// 缩小（Resize)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//缩小两倍
	resize(image,dst,Size(image.cols/2,image.rows/2),0,0,INTER_LINEAR);
	namedWindow("缩小(Resize)"); 
	imshow("缩小(Resize)", dst);
	waitKey(0);
}


void CopencvDlg::On32790()
{
	// 顺时针无缩放
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = -30;//旋转角度(正值表示逆时针旋转)  
	int SCALE=1.0;	//缩放比例
    int length;//输出图像的宽度或高度  
    //为了保证无论如何旋转都能放下，输出图像的长和宽都设为输入图像对角线长度乘以SCALE  
    //但如果是缩小(SCALE<=1)，这样会导致临时图像中放不下原图，所以对于所有缩小的情况，输出图像和临时图像的长宽都设为原图的对角线长度  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //建立临时图像，长宽都是源图像的对角线长度，将源图像复制到临时图像的中心后再变换  
    Mat tempImg(length,length,src.type());//临时图像，大小和输出图像一样大  
    int ROI_x = length/2 - src.cols/2;//ROI矩形左上角的x坐标  
    int ROI_y = length/2 - src.rows/2;//ROI矩形左上角的y坐标  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI矩形  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg的中间部分  
    src.copyTo(tempImgROI2);//将原图复制到tempImg的中心  
  
    Point2f center(length/2,length/2);//旋转中心  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//计算旋转的仿射变换矩阵  
   
    
  
    warpAffine(tempImg,dst,M,Size(length,length));//仿射变换  
  
    //显示 
    imshow("顺时针无缩放",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32791()
{
	// 顺时针缩放
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = -30;//旋转角度(正值表示逆时针旋转)  
	float SCALE=0.5;	//缩放比例
    int length;//输出图像的宽度或高度  
    //为了保证无论如何旋转都能放下，输出图像的长和宽都设为输入图像对角线长度乘以SCALE  
    //但如果是缩小(SCALE<=1)，这样会导致临时图像中放不下原图，所以对于所有缩小的情况，输出图像和临时图像的长宽都设为原图的对角线长度  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //建立临时图像，长宽都是源图像的对角线长度，将源图像复制到临时图像的中心后再变换  
    Mat tempImg(length,length,src.type());//临时图像，大小和输出图像一样大  
    int ROI_x = length/2 - src.cols/2;//ROI矩形左上角的x坐标  
    int ROI_y = length/2 - src.rows/2;//ROI矩形左上角的y坐标  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI矩形  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg的中间部分  
    src.copyTo(tempImgROI2);//将原图复制到tempImg的中心  
  
    Point2f center(length/2,length/2);//旋转中心  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//计算旋转的仿射变换矩阵  
   
    
  
    warpAffine(tempImg,dst,M,Size(length,length));//仿射变换  
  
    //显示 
    imshow("顺时针缩放",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32792()
{
	// 逆时针
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = 30;//旋转角度(正值表示逆时针旋转)  
	float SCALE=0.8;	//缩放比例
    int length;//输出图像的宽度或高度  
    //为了保证无论如何旋转都能放下，输出图像的长和宽都设为输入图像对角线长度乘以SCALE  
    //但如果是缩小(SCALE<=1)，这样会导致临时图像中放不下原图，所以对于所有缩小的情况，输出图像和临时图像的长宽都设为原图的对角线长度  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //建立临时图像，长宽都是源图像的对角线长度，将源图像复制到临时图像的中心后再变换  
    Mat tempImg(length,length,src.type());//临时图像，大小和输出图像一样大  
    int ROI_x = length/2 - src.cols/2;//ROI矩形左上角的x坐标  
    int ROI_y = length/2 - src.rows/2;//ROI矩形左上角的y坐标  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI矩形  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg的中间部分  
    src.copyTo(tempImgROI2);//将原图复制到tempImg的中心  
  
    Point2f center(length/2,length/2);//旋转中心  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//计算旋转的仿射变换矩阵  
   warpAffine(tempImg,dst,M,Size(length,length));//仿射变换  
  
    //显示   
    imshow("逆时针",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32793()
{
	// 零旋转缩放
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = 0;//旋转角度(正值表示逆时针旋转)  
	float SCALE=0.7;	//缩放比例
    int length;//输出图像的宽度或高度  
    //为了保证无论如何旋转都能放下，输出图像的长和宽都设为输入图像对角线长度乘以SCALE  
    //但如果是缩小(SCALE<=1)，这样会导致临时图像中放不下原图，所以对于所有缩小的情况，输出图像和临时图像的长宽都设为原图的对角线长度  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //建立临时图像，长宽都是源图像的对角线长度，将源图像复制到临时图像的中心后再变换  
    Mat tempImg(length,length,src.type());//临时图像，大小和输出图像一样大  
    int ROI_x = length/2 - src.cols/2;//ROI矩形左上角的x坐标  
    int ROI_y = length/2 - src.rows/2;//ROI矩形左上角的y坐标  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI矩形  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg的中间部分  
    src.copyTo(tempImgROI2);//将原图复制到tempImg的中心  
  
    Point2f center(length/2,length/2);//旋转中心  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//计算旋转的仿射变换矩阵  
   warpAffine(tempImg,dst,M,Size(length,length));//仿射变换  
  
    //显示   
    imshow("零旋转缩放",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32795()
{
	//版权
	AfxMessageBox(_T("本程序均使用OpenCV库函数，相关版权见OpenCV官网！"));
}


void CopencvDlg::On32794()
{
	//关于
	AfxMessageBox(_T("详见后期补充"));
}

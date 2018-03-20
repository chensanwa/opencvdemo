
// opencvDlg.cpp : ʵ���ļ�
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

//#define SCALE 1.0   //���ű���




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CopencvDlg �Ի���




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


// CopencvDlg ��Ϣ�������

BOOL CopencvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CopencvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CopencvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvDlg::On32771()
{	//����ͼƬ
	// TODO: �ڴ���������������
	CBitmap bitmap; // CBitmap�������ڼ���λͼ
    HBITMAP hBmp;   // ����CBitmap���ص�λͼ�ľ��
 
    bitmap.LoadBitmapW(IDB_BITMAP1);    // ��λͼIDB_BITMAP1���ص�bitmap
    hBmp = (HBITMAP)bitmap.GetSafeHandle(); // ��ȡbitmap����λͼ�ľ��
    m_pictureControl.SetBitmap(hBmp);   // ����ͼƬ�ռ�m_pictureControl��λͼΪIDB_BITMAP1
}

IplImage* BitmapToIplImage(HBITMAP hBmp)  
{  //bitmapתΪiplimage��ʽ
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
	// ˮƽ��ת��Y����ԳƼ�X�����Ϸ���
	IplImage *pSrcImg = NULL;
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);	

	HBITMAP bmp = HBITMAP(bitmap);


	pSrcImg=BitmapToIplImage(bmp);
	cvFlip(pSrcImg,NULL,1);		//��ת����
	cvNamedWindow(  "Xturnover"  ); //��������
	cvShowImage("Xturnover", pSrcImg);	//�ڴ�������ʾͼƬ
	cvWaitKey(0);	//��ͣ����Ҫ�û��û������
	cvReleaseImage(&pSrcImg);	//����ָ��
	cvDestroyWindow("Xturnover");	//���ٴ���

}


void CopencvDlg::On32773()
{
	// ��ֱ��ת��X����ԳƼ�Y�����Ϸ���
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
	// ˮƽ��ֱ��ת��
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
	// ����
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat out;
	//�������Ͳ���
    dilate(image,out, element);
 
	namedWindow("dilate");
	imshow("dilate", out);
 //   //��ʾЧ��ͼ
	//IplImage *pSrcImg = NULL;
	//*pSrcImg=(IplImage)(image);
	//cvNamedWindow(  "dilate"  ); //��������
	//cvShowImage("dilate", pSrcImg);	//�ڴ�������ʾͼƬ
	//cvWaitKey(0);	//��ͣ����Ҫ�û��û������
	//cvReleaseImage(&pSrcImg);	//����ָ��
	//cvDestroyWindow("dilate");	//���ٴ���
}


void CopencvDlg::On32776()
{
	// TODO: �ڴ���������������
	// ��ʴ
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat out;
	//���и�ʴ����
    erode(image,out, element);
	namedWindow("erode");
	imshow("erode", out);
}


void CopencvDlg::On32777()
{
	// ������
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
    morphologyEx(image,image, MORPH_OPEN, element);
	//��ʾЧ��ͼ   
    imshow("������", image); 
	waitKey(0);  
}


void CopencvDlg::On32778()
{
	//������
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
    morphologyEx(image,image, MORPH_CLOSE, element);  
    //��ʾЧ��ͼ   
    imshow("������", image);   
   
    waitKey(0);  
}


void CopencvDlg::On32779()
{
	//Morphological Gradient(��̬ѧ�ݶȣ�
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	 //������̬ѧ����  
    morphologyEx(image,image, MORPH_GRADIENT, element);  
       //��ʾЧ��ͼ   
    imshow("Morphological Gradient(��̬ѧ�ݶȣ�", image);   
   
    waitKey(0);   
   
}


void CopencvDlg::On32780()
{
	//��ñ
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
       //������̬ѧ����  
       morphologyEx(image,image, MORPH_TOPHAT, element);  
       //��ʾЧ��ͼ   
       imshow("��ñ����", image);   
   
       waitKey(0);   
}


void CopencvDlg::On32781()
{
	//��ñ
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ȡ�Զ����
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//������̬ѧ����  
    morphologyEx(image,image, MORPH_BLACKHAT, element);  
       //��ʾЧ��ͼ   
    imshow("��ñ����", image);   
   
    waitKey(0);   
   
}


void CopencvDlg::On32782()
{
	// ��ֵ�˲�

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ֵ�˲�
	Mat dst;
    //image:����ͼ��
    //dst:���ͼ��
    //ģ���С
    //Point(-1,-1):��ƽ����λ�ã�Ϊ��ֵȡ������
    blur(image,dst,Size(3,3),Point(-1,-1));
    imshow("��ֵ�˲�", dst);   
   
    waitKey(0);   
}


void CopencvDlg::On32783()
{
	// ��˹�˲�
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ֵ�˲�
	Mat dst;
	//src:����ͼ��
    //dst:���ͼ��
   //Size(5,5)ģ���С��Ϊ����
    //x���򷽲�
   //Y���򷽲�
    GaussianBlur(image,dst,Size(5,5),0,0);
	imshow("��˹�˲�", dst);   
   
    waitKey(0);  
}


void CopencvDlg::On32784()
{
	//��ֵ�˲�
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	//��ֵ�˲�
	Mat dst;
	//image:����ͼ��
        //dst::���ͼ��
        //ģ���ȣ�Ϊ����
    medianBlur(image,dst,3);
	imshow("��ֵ�˲�", dst);   
   
    waitKey(0);  
}


void CopencvDlg::On32785()
{
	// ˫���˲�
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//image:����ͼ��
    //dst:����ͼ��
    //�˲�ģ��뾶
    //��ɫ�ռ��׼��
    //����ռ��׼��
    bilateralFilter(image,dst, 25, 25 * 2, 25 / 2);		//�����Ϊʲô���������MFC�лᱨ��
	namedWindow("˫���˲�"); 
	imshow("˫���˲�", dst);   
    waitKey(0);
}


void CopencvDlg::On32786()
{
	//�Ŵ�(PyrUp)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//��ͼ��Ŵ�����
	pyrUp(image, dst, Size(image.cols * 2, image.rows * 2));
	namedWindow("�Ŵ�(PyrUp)"); 
	imshow("�Ŵ�(PyrUp)", dst);
	waitKey(0);
}


void CopencvDlg::On32787()
{
	// ��С��PyrDown)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//��С���� 
	pyrDown(image, dst, Size(image.cols / 2, image.rows / 2));
	namedWindow("��С(PyrUp)"); 
	imshow("��С(PyrUp)", dst);
	waitKey(0);

}


void CopencvDlg::On32788()
{
	// �Ŵ�Resize)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//�Ŵ�����
	resize(image,dst,Size(image.cols*2,image.rows*2),0,0,INTER_LINEAR);
	namedWindow("�Ŵ�(Resize)"); 
	imshow("�Ŵ�(Resize)", dst);
	waitKey(0);
}


void CopencvDlg::On32789()
{
	// ��С��Resize)
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat image;
	HBitmapToMat(bmp,image);
	Mat dst;
	//��С����
	resize(image,dst,Size(image.cols/2,image.rows/2),0,0,INTER_LINEAR);
	namedWindow("��С(Resize)"); 
	imshow("��С(Resize)", dst);
	waitKey(0);
}


void CopencvDlg::On32790()
{
	// ˳ʱ��������
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = -30;//��ת�Ƕ�(��ֵ��ʾ��ʱ����ת)  
	int SCALE=1.0;	//���ű���
    int length;//���ͼ��Ŀ�Ȼ�߶�  
    //Ϊ�˱�֤���������ת���ܷ��£����ͼ��ĳ��Ϳ���Ϊ����ͼ��Խ��߳��ȳ���SCALE  
    //���������С(SCALE<=1)�������ᵼ����ʱͼ���зŲ���ԭͼ�����Զ���������С����������ͼ�����ʱͼ��ĳ�����Ϊԭͼ�ĶԽ��߳���  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //������ʱͼ�񣬳�����Դͼ��ĶԽ��߳��ȣ���Դͼ���Ƶ���ʱͼ������ĺ��ٱ任  
    Mat tempImg(length,length,src.type());//��ʱͼ�񣬴�С�����ͼ��һ����  
    int ROI_x = length/2 - src.cols/2;//ROI�������Ͻǵ�x����  
    int ROI_y = length/2 - src.rows/2;//ROI�������Ͻǵ�y����  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI����  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg���м䲿��  
    src.copyTo(tempImgROI2);//��ԭͼ���Ƶ�tempImg������  
  
    Point2f center(length/2,length/2);//��ת����  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//������ת�ķ���任����  
   
    
  
    warpAffine(tempImg,dst,M,Size(length,length));//����任  
  
    //��ʾ 
    imshow("˳ʱ��������",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32791()
{
	// ˳ʱ������
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = -30;//��ת�Ƕ�(��ֵ��ʾ��ʱ����ת)  
	float SCALE=0.5;	//���ű���
    int length;//���ͼ��Ŀ�Ȼ�߶�  
    //Ϊ�˱�֤���������ת���ܷ��£����ͼ��ĳ��Ϳ���Ϊ����ͼ��Խ��߳��ȳ���SCALE  
    //���������С(SCALE<=1)�������ᵼ����ʱͼ���зŲ���ԭͼ�����Զ���������С����������ͼ�����ʱͼ��ĳ�����Ϊԭͼ�ĶԽ��߳���  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //������ʱͼ�񣬳�����Դͼ��ĶԽ��߳��ȣ���Դͼ���Ƶ���ʱͼ������ĺ��ٱ任  
    Mat tempImg(length,length,src.type());//��ʱͼ�񣬴�С�����ͼ��һ����  
    int ROI_x = length/2 - src.cols/2;//ROI�������Ͻǵ�x����  
    int ROI_y = length/2 - src.rows/2;//ROI�������Ͻǵ�y����  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI����  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg���м䲿��  
    src.copyTo(tempImgROI2);//��ԭͼ���Ƶ�tempImg������  
  
    Point2f center(length/2,length/2);//��ת����  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//������ת�ķ���任����  
   
    
  
    warpAffine(tempImg,dst,M,Size(length,length));//����任  
  
    //��ʾ 
    imshow("˳ʱ������",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32792()
{
	// ��ʱ��
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = 30;//��ת�Ƕ�(��ֵ��ʾ��ʱ����ת)  
	float SCALE=0.8;	//���ű���
    int length;//���ͼ��Ŀ�Ȼ�߶�  
    //Ϊ�˱�֤���������ת���ܷ��£����ͼ��ĳ��Ϳ���Ϊ����ͼ��Խ��߳��ȳ���SCALE  
    //���������С(SCALE<=1)�������ᵼ����ʱͼ���зŲ���ԭͼ�����Զ���������С����������ͼ�����ʱͼ��ĳ�����Ϊԭͼ�ĶԽ��߳���  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //������ʱͼ�񣬳�����Դͼ��ĶԽ��߳��ȣ���Դͼ���Ƶ���ʱͼ������ĺ��ٱ任  
    Mat tempImg(length,length,src.type());//��ʱͼ�񣬴�С�����ͼ��һ����  
    int ROI_x = length/2 - src.cols/2;//ROI�������Ͻǵ�x����  
    int ROI_y = length/2 - src.rows/2;//ROI�������Ͻǵ�y����  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI����  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg���м䲿��  
    src.copyTo(tempImgROI2);//��ԭͼ���Ƶ�tempImg������  
  
    Point2f center(length/2,length/2);//��ת����  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//������ת�ķ���任����  
   warpAffine(tempImg,dst,M,Size(length,length));//����任  
  
    //��ʾ   
    imshow("��ʱ��",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32793()
{
	// ����ת����
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	HBITMAP bmp = HBITMAP(bitmap);

	Mat src;
	HBitmapToMat(bmp,src);
	Mat dst;
	int angle = 0;//��ת�Ƕ�(��ֵ��ʾ��ʱ����ת)  
	float SCALE=0.7;	//���ű���
    int length;//���ͼ��Ŀ�Ȼ�߶�  
    //Ϊ�˱�֤���������ת���ܷ��£����ͼ��ĳ��Ϳ���Ϊ����ͼ��Խ��߳��ȳ���SCALE  
    //���������С(SCALE<=1)�������ᵼ����ʱͼ���зŲ���ԭͼ�����Զ���������С����������ͼ�����ʱͼ��ĳ�����Ϊԭͼ�ĶԽ��߳���  
    if(SCALE <= 1)  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0);  
    else  
        length = sqrt((src.cols*src.cols + src.rows*src.rows)*1.0) * SCALE;  
    //������ʱͼ�񣬳�����Դͼ��ĶԽ��߳��ȣ���Դͼ���Ƶ���ʱͼ������ĺ��ٱ任  
    Mat tempImg(length,length,src.type());//��ʱͼ�񣬴�С�����ͼ��һ����  
    int ROI_x = length/2 - src.cols/2;//ROI�������Ͻǵ�x����  
    int ROI_y = length/2 - src.rows/2;//ROI�������Ͻǵ�y����  
    Rect ROIRect(ROI_x,ROI_y,src.cols,src.rows);//ROI����  
    Mat tempImgROI2(tempImg,ROIRect);//tempImg���м䲿��  
    src.copyTo(tempImgROI2);//��ԭͼ���Ƶ�tempImg������  
  
    Point2f center(length/2,length/2);//��ת����  
    Mat M = getRotationMatrix2D(center,angle,SCALE);//������ת�ķ���任����  
   warpAffine(tempImg,dst,M,Size(length,length));//����任  
  
    //��ʾ   
    imshow("����ת����",dst);  
  
    waitKey(0);  
}


void CopencvDlg::On32795()
{
	//��Ȩ
	AfxMessageBox(_T("�������ʹ��OpenCV�⺯������ذ�Ȩ��OpenCV������"));
}


void CopencvDlg::On32794()
{
	//����
	AfxMessageBox(_T("������ڲ���"));
}

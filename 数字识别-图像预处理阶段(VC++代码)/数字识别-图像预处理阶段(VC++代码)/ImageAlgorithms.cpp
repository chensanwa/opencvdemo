#include "StdAfx.h"
#include "ImageAlgorithms.h"
#include "CommonCompute.h"

#include <GdiPlus.h>
#include <math.h>

#define adjust4(x) ((((x) + 3)>>2)<<2)

#define TO_START_IMAGE 3
#define TO_END_IMAGE   97

#define BASE_NUM 10000
#define DISTANSE 1000

CImageAlgorithms::CImageAlgorithms(void)
{
}

CImageAlgorithms::~CImageAlgorithms(void)
{
}

int CImageAlgorithms::Init(int width, int height)
{
	m_Width = width;
	m_Height = height;

	return EXIT_SUCCESS;
}

int CImageAlgorithms::Release()
{
	m_Width = 0;
	m_Height = 0;

	return EXIT_SUCCESS;
}

/************************************************************************/
/* Function: RGB Image To Gray Image Algorithm
/* Param: Dst Image (Gray)
/* Param: Src Image (RGB)
/* Param: Algorithm Type
*/
/************************************************************************/
int CImageAlgorithms::RGB_To_Gray(uint_32 *pDst, uint_32 *pSrc, int nType)
{
	int nPixelsPerLine;
	if (m_Width % 2 == 0)
	{
		nPixelsPerLine = adjust4(m_Width);
	}
	else
	{
		nPixelsPerLine = m_Width;
	}

	if (!pDst || !pSrc)
	{
		return EXIT_FAILURE;
	}

    int x, y;
	for (y = 0; y < m_Height; y++)
	{
		int index = y * nPixelsPerLine;

		for (x = 0; x < m_Width; x++)
		{
			uint_32 color =  pSrc[index + x];

			byte r = GetRValue(color);
			byte g = GetGValue(color);
			byte b = GetBValue(color);

			uint_8 gray = 0;
			if (nType == 0)   // Max Value
			{
				gray = max(max(r, g), b); 
			} 
			else if (nType == 1)
			{
				gray = (uint_8)((r + g + b) / 3);
			} 
			else
			{
				gray = (uint_8)((r * 30 + g * 59 + b * 11) / 100);
			}

			pDst[index + x] = RGB(gray, gray, gray);
		}
	}

	return EXIT_SUCCESS;
}

/************************************************************************/
/* Function: Threshold Transform Algorithm
/* Param: Dst Image
/* Param: Src Image
/* Param: Threshold (阀值) 
/* 备注：RGB -> Gray, 值大于阀值的赋予, 小于阀值的赋予
*/
/************************************************************************/
int CImageAlgorithms::Threshold_Transform(uint_32 *pDst, uint_32 *pSrc, uint_8 uThreshold)
{
	if (!pDst || !pSrc)
	{
		return EXIT_FAILURE;
	}

	int x, y;
	int index;
	for (y = 0; y < m_Height; y++)
	{
		index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			uint_32 color = pSrc[index + x];
			uint_8 r = GetRValue(color);
			uint_8 g = GetGValue(color);
			uint_8 b = GetBValue(color);

			uint_8 gray = (uint_8)((r + g + b) / 3);
			gray = gray > uThreshold ? 255 : 0;

			pDst[index + x] = RGB(gray, gray, gray);
		}
	}

    return EXIT_SUCCESS;
}

/************************************************************************/
/* Function: Gradient Sharpening Algorithm (梯度锐化)
/* Param: Dst Image
/* Param: Src Image 
*/
/************************************************************************/
int CImageAlgorithms::Gradient_Sharpening(uint_32 *pDst, uint_32 *pSrc)
{
	if (!pDst || !pSrc)
	{
		return EXIT_FAILURE;
	}

    // 阀值
	uint_8 Threshold = 2;

    uint_8 r, r1, r2, rTemp;
	uint_8 g, g1, g2, gTemp;
	uint_8 b, b1, b2, bTemp;

    int x, y;
	for (y = 0; y < m_Height - 1; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			// 第y 行,第x 列
			uint_32 pixel = pSrc[index + x];

			// 第y 行,第x+1 列
			uint_32 pixel1 = pSrc[index + x + 1];

			// 第y+1 行,第x 列
			uint_32 pixel2 = pSrc[index + m_Width + x];

			// 分别计算R, G, B方向的梯度
			r  = GetRValue(pixel);
			r1 = GetRValue(pixel1);
			r2 = GetRValue(pixel2);
			rTemp = abs(r - r1) + abs(r - r2);
			if (rTemp < 255)
			{
				if (rTemp >= Threshold)
				{
					r = rTemp;
				}
			} 
			else
			{
				r = 255;
			}

			g  = GetGValue(pixel);
			g1 = GetGValue(pixel1);
			g2 = GetGValue(pixel2);
			gTemp = abs(g - g1) + abs(g - g2);
			if (gTemp < 255)
			{
				if (gTemp >= Threshold)
				{
					g = gTemp;
				}
			} 
			else
			{
				g = 255;
			}

			b  = GetBValue(pixel);
			b1 = GetBValue(pixel1);
			b2 = GetBValue(pixel2);
			bTemp = abs(b - b1) + abs(b - b2);
			if (bTemp < 255)
			{
				if (bTemp >= Threshold)
				{
					b = bTemp;
				}
			}
			else
			{
				b = 255;
			}

			// 创建目标RGB
			pDst[index + x] = RGB(r, g, b);
		}
	}

	// 最后一行
	{
		int index = (m_Height - 1) * m_Width;
		//int index = 0;

		for (x = 0; x < m_Width; x++)
		{
			//最后一行,第x 列
			uint_32 pixel = pSrc[index + x];
			
		    // 最后一行,第x+1 列
			uint_32 pixel1 = pSrc[index + x + 1];
			
			// 倒数第二行,第x 列
			uint_32 pixel2 = pSrc[index - m_Width + x];
			
		    // 分别计算R, G, B方向的梯度
			r  = GetRValue(pixel);
			r1 = GetRValue(pixel1);
			r2 = GetRValue(pixel2);
		    rTemp = abs(r - r1) + abs(r - r2);
			if (rTemp < 255)
			{
				if (rTemp > Threshold)
				{
					r = rTemp;
				}
			} 
			else
			{
				r = 255;
			}
			
			g  = GetGValue(pixel);
			g1 = GetGValue(pixel1);
			g2 = GetGValue(pixel2);
			gTemp = abs(g - g1) + abs(g - g2);
			if (gTemp < 255)
			{
				if (gTemp > Threshold)
				{
					g = gTemp;
				}
			} 
		    else
			{
				g = 255;
			}
			
			b  = GetBValue(pixel);
			b1 = GetBValue(pixel1);
			b2 = GetBValue(pixel2);
			bTemp = abs(b - b1) + abs(b - b2);
			if (bTemp < 255)
			{
				if (bTemp > Threshold)
				{
					b = bTemp;
				}
			}
			else
			{
				b = 255;
			}

			// 创建目标RGB
			pDst[index + x] = RGB(r, g, b);
		}
		
	}

	return EXIT_SUCCESS;
}

/************************************************************************/
/*                  Pattern Recognition Algorithm                       */
/************************************************************************/

/************************************************************************/
/* Function: Scatter Noise Algorithm (离散噪声)
/* Param: Dst Image
/* Param: Src Image 
*/
/************************************************************************/
int CImageAlgorithms::Scatter_Noise(uint_32 *pDst, uint_32 *pSrc)
{
	if (!pDst || !pSrc)
	{
		return EXIT_FAILURE;
	}

	// 连续数
	m_iContinuousNum = 0;

	// 初始化连续数
	//设置判定噪声的长度阈值为15
	//即如果与考察点相连接的黑点的数目小于15则认为考察点是噪声点
	int iLength = 15;

	// 循环变量
	int x, y, i;

	// 分配访问标志位空间
	bool* pbFlagLab = new bool[m_Width * m_Height];
	for (i = 0; i < m_Width * m_Height; i++)
	{
		pbFlagLab[i] = false;
	}

	// 保存中间变量的空间
	bool* pbTemp = new bool[m_Width * m_Height];

	// 位置空间
	POINT_I2 pLabPoint[21];

	// 寻找离散噪声
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			// 先把标志位置为 false
			for (i = 0; i < m_iContinuousNum; i++)
			{
				pbFlagLab[pLabPoint[i].Y * m_Width + pLabPoint[i].X] = false;
			}

			// 连续数置为 0
			m_iContinuousNum = 0;

			pbTemp[index + x] = Judge_Scatter_Noise(pSrc, pbFlagLab, x, y, pLabPoint, iLength);
		}
	}

	// 把离散点置为白色
	// 寻找离散噪声
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			if (pbTemp[index + x] == false)
			{
				pDst[index + x] = RGB(255, 255, 255);
			}
			else
			{
				pDst[index + x] = pSrc[index + x];
			}
		}
	}

	delete[] pbFlagLab;
	delete[] pbTemp;

	return EXIT_SUCCESS;
}

/************************************************************************/
/* Function: Judge Noise Algorithm (判断是否是离散噪声)
/*           利用递归算法统计连续点的个数，通过阈值来判定是否为离散点
/* Param: Src Image 
/* Param: 标志位数组
/* Param: 当前点的横坐标
/* Param: 当前点的纵坐标 
/* Param: 存放已考察过的连续点坐标
/* Param: 离散点的判定长度
/* Return:  是离散点返回false 不是离散点返回true
/* Description: 只能对2值图像进行处理
*/
/************************************************************************/
bool CImageAlgorithms::Judge_Scatter_Noise(uint_32 *pSrc, bool *pLab, int x, int y, POINT_I2 lab_point[], int lenght)
{
	// 如果连续长度满足要求，说明不是离散点，返回
	if(m_iContinuousNum >= lenght)
	{
		return true;
	}

	// 长度加一
	m_iContinuousNum++;

	// 设定访问标志
	pLab[m_Width * y + x] = true;

	// 保存访问点坐标
	lab_point[m_iContinuousNum - 1].X = x;
	lab_point[m_iContinuousNum - 1].Y = y;

	// 象素的灰度值
	uint_8 gray;

	// 索引值
	int index = 0;

	// 长度判定
	// 如果连续长度满足要求，说明不是离散点，返回
	if(m_iContinuousNum >= lenght)
	{
		return true;
	}
	else //下面进入递归
	{	
		// 考察上下左右以及左上、右上、左下、右下八个方向
		// 如果是黑色点，则调用函数自身进行递归

		// 考察上面点
		if ((y - 1) >= 0)
		{
			index = (y - 1) * m_Width + x;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x, y - 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察左上面点
		if (((y - 1) >= 0) && ((x - 1) >= 0))
		{
			index = (y - 1) * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y - 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察右上面点
		if (((y - 1) >= 0) && ((x + 1) < m_Width))
		{
			index = (y - 1) * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y - 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察左面点
		if ((x - 1) >= 0)
		{
			index = y * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察右面点
		if ((x + 1) < m_Width)
		{
			index = y * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		//考察下面点
		if ((y + 1) < m_Height)
		{
			index = (y + 1) * m_Width + x;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x, y + 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察左下面点
		if (((y + 1) < m_Height) && ((x - 1) >= 0))
		{
			index = (y + 1) * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y + 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// 考察右下面点
		if (((y + 1) < m_Height) && ((x + 1) < m_Width))
		{
			index = (y + 1) * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y + 1, lab_point, lenght);
			}
		}

		// 如果连续长度满足要求，说明不是离散点，返回
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}
	}

	// 如果递归结束，返回false，说明是离散点
	return false;
}

/************************************************************************/
/* Function: Slope Adjust Algorithm (倾斜调整)
/* Param: Dst Image
/* Param: Src Image 
*/
/************************************************************************/
int CImageAlgorithms::Slope_Adjust(uint_32 *pDst, uint_32 *pSrc)
{
	if (!pSrc || !pDst)
	{
		return EXIT_FAILURE;
	}

	// 高度计数
	long dCounts = 0;

	// 左边高度平均值
	double dLeftAvr = 0.0;

	// 右边高度平均值
	double dRightAvr = 0.0;

	// 整体倾斜度
	double dSlope;

	// 循环变量
	int x, y;

	// 计算左边
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width / 2; x++)
		{
			uint_32 gray = pSrc[index + x];

			if (gray == 0)
			{
				dCounts += m_Width / 2 - x;
				dLeftAvr += y * (m_Width / 2 - x);
			}
		}
	}

	dLeftAvr /= dCounts;

	dCounts = 0;

	// 计算右边
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = m_Width / 2; x < m_Width; x++)
		{
			uint_32 gray = pSrc[index + x];

			if (gray == 0)
			{
				dCounts += m_Width - x;
				dRightAvr += y * (m_Width - x);
			}
		}
	}

	dRightAvr /= dCounts;

	// 计算整体倾斜度
	dSlope = (dLeftAvr - dRightAvr) / (m_Width / 2);

	// 赋值
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			int srcIndex = (int)(y - (x - m_Width / 2) * dSlope);

			if (srcIndex < 0 || srcIndex >= m_Height)
			{
				pDst[index + x] = RGB(255, 255, 255);
			} 
			else
			{
				pDst[index + x] = pSrc[srcIndex * m_Width + x];
			}
		}
	}

	return EXIT_SUCCESS;
}

/************************************************************************/
/* Function: Char Segment Algorithm (分割字符)
/* Param: Src Image 
/* 说明:将图像中待识别的字符逐个分离出来并返回存放各个字符的位置信息的链表
*/
/************************************************************************/
CRectLink CImageAlgorithms::Char_Segment(uint_32 *pSrc)
{
	//清空用来保存每个字符区域的链表
	CRectLink rectLink1, rectLink2;
	rectLink1.clear();
	rectLink2.clear();

	// 保存顶部和底部位置
	int iTop, iBottom;

	// 循环变量
	int x, y;

	// 找顶部位置
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			uint_32 gray = pSrc[index + x];

			if (gray == 0)
			{
				iTop = y;

				y = m_Height;

				break;
			}
		}
	}

	// 找底部位置
	for (y = m_Height - 1; y >= 0; y--)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			uint_32 gray = pSrc[index + x];

			if (gray == 0)
			{
				iBottom = y;

				y = -1;

				break;
			}
		}
	}

	// 用作是否进入一个字符分割的标志
	bool bFlag = false;

	// 表明扫描一列中是否发现黑色点
	bool bBlack = false;

	// 存放位置信息的结构体
	CRect rect;

	// 计数器置零
	int iDigicount = 0;

	// 行
	for (x = 0; x < m_Width; x++)
	{
		// 扫描下一列
		bBlack = false;

		for (y = 0; y < m_Height; y++)
		{
			uint_32 gray = pSrc[y * m_Width + x];

			if (gray == 0)
			{
				// 发现黑点,把标志置为 true
				bBlack = true;

				// 判断是否进入下一个分割
				if (bFlag == false)
				{
					rect.left = x;

					bFlag = true;
				} 
				else  // 字符分割已经开始
				{
					break;
				}
			}
		}

		// 如果已经扫到了最右边那列，说明整副图像扫描完毕。退出
		if (x == m_Width - 1)
		{
			break;
		}

		// 如果到此 bBlack 仍为 false，说明扫描了一列，都没有发现黑点。表明当前字符分割结束
		if (bFlag == true && bBlack == false)
		{
			// 记录字符矩形信息
			rect.right = x;

			rect.top = iTop;

			rect.bottom = iBottom;

			// 将框外括一个象素，以免压到字符
			rect.InflateRect(1, 1);

			// 将这个结构体插入存放位置信息的链表1的后面
			rectLink1.push_back (rect);

			// 设置标志位，开始下一次的字符分割
			bFlag = false;

			//字符个数统计计数器加1
			iDigicount++;
		}
	}

	/**************************   精确计算每个矩形的边界  ***************/
	// 将 rectLink1 赋给 rectLink2
	rectLink2 = rectLink1;
	rectLink2.clear();

	// 重新定义一个矩形
	CRect rectNew;

	// 对于链表1从头至尾逐个进行扫描
	while(!rectLink1.empty())
	{
		rect = rectLink1.front();

		rectLink1.pop_front();

		rectNew.left  = rect.left  - 1;
		rectNew.right = rect.right + 1;

		// 由上而下扫描计算上边界
		for (y = rect.top; y < rect.bottom; y++)
		{
			for (x = rect.left; x < rect.right; x++)
			{
				uint_32 gray = pSrc[y * m_Width + x];

				if (gray == 0)
				{
					rectNew.top = y - 1;

					// 强制退出
					y = rect.bottom;

					break;
				}
			}
		}

		// 由下而上扫描计算下边界
		for (y = rect.bottom; y >= rect.top; y--)
		{
			for (x = rect.left; x < rect.right; x++)
			{
				uint_32 gray = pSrc[y * m_Width + x];

				if (gray == 0)
				{
					rectNew.bottom = y + 1;

					// 强制退出
					y = -1;

					break;
				}
			}
		}

		rectLink2.push_back(rectNew);
	}

	rectLink1 = rectLink2;

	return rectLink1;
}

/************************************************************************/
/* Function: Char Size Normalize Algorithm (字符大小归一化)
/* Param: 目标图像
/* Param: 源图像
/* Param: 每个字符的区域分割矩形链表
/* Param: 归一化宽度
/* Param: 归一化高度
/* Return: 返回归一化后的字符矩形链表
/* 说明: 将经过分割的字符，进行缩放处理使他们的宽和高一直，以方便特征的提取
*/
/************************************************************************/
CRectLink CImageAlgorithms::Char_Size_Normalize(uint_32 *pDst, uint_32 *pSrc, CRectLink rectLink, int norWidth, int norHeight)
{
	if (!pDst || !pSrc)
	{
		CRectLink rLink;
		rLink.clear();
		return rLink;
	}

	// 宽度伸缩因子
	double dWidthScale = 0.0;

	// 高度伸缩因子
	double dHeightScale = 0.0;

	// 归一化后的字符矩形链表
	CRectLink norRectLink;
	norRectLink.clear();

	// 循环变量
	int x, y, i;

	// 把目标图像置为白色
	for (i = 0; i< m_Width * m_Height; i++)
	{
		pDst[i] = RGB(255, 255, 255);
	}

	while (!rectLink.empty())
	{
		CRect rect = rectLink.front();
		rectLink.pop_front();

		// 计算宽度伸缩因子
		dWidthScale = (double)(1.0 * norWidth / rect.Width());

		// 计算高度伸缩因子
		dHeightScale = (double)(1.0 * norHeight / rect.Height());

		CRect rectNew;
		rectNew.left = rect.left;
		rectNew.right = rect.left + norWidth; 
		rectNew.top = rect.top;
		rectNew.bottom = rect.top + norHeight;

		// 核心部分
		for (y = rectNew.top; y < rectNew.bottom; y++)
		{
			for (x = rectNew.left; x < rectNew.right; x++)
			{
				// 计算当前点在源图像中对应点的位置
				int x_src = rectNew.left + (int)((x - rectNew.left) / dWidthScale);
				int y_src = rectNew.top + (int)((y - rectNew.top) / dHeightScale);

				pDst[y * m_Width + x] = pSrc[y_src * m_Width + x_src];
			}
		}

		// 添加归一化后的字符矩形
		norRectLink.push_back(rectNew);
	}

	return norRectLink;
}

/************************************************************************/
/* Function: Char Auto Align Algorithm (字符紧密排列)
/* Param: 目标图像
/* Param: 源图像
/* Param: 每个字符的区域分割矩形链表
/* Return: 返回归一化后的字符矩形链表
/* 说明: 将经过了标准化处理的字符进行规整的排列
*/
/************************************************************************/
CRectLink CImageAlgorithms::Char_Auto_Align(uint_32 *pDst, uint_32 *pSrc, CRectLink rectLink)
{
	if (!pDst || !pSrc)
	{
		CRectLink rLink;
		rLink.clear();
		return rLink;
	}

	// 每个字符的矩形的宽度
	int width = rectLink.front().Width();

	// 每个字符的矩形的高度
	int height = rectLink.front().Height();

    // 新的字符矩形链表
	CRectLink rectLinkNew;

	// 字符个数统计
	int Count = rectLink.size();
	int iWidth = Count * width;
	int iCounts = 0;

	// 循环变量
	int x, y;

	while(!rectLink.empty())
	{
		// 矩形 中间变量
		CRect rect, rectNew;

		rect = rectLink.front();
		rectLink.pop_front();

		rectNew.left = iCounts * width;
		rectNew.right = (iCounts + 1) * width;
		rectNew.top = 0;
		rectNew.bottom = height;

		rectLinkNew.push_back(rectNew);

		// 赋值
		for (y = 0; y < height; y++)
		{
			for (x = iCounts * width; x < (iCounts + 1) * width; x++)
			{
				// 计算当前点在源图像中对应点的位置
				int x_src = rect.left + (x - iCounts * width);
				int y_src = rect.top + y;

				pDst[y * iWidth + x] = pSrc[y_src * m_Width + x_src];
			}
		}

        iCounts++;
	}

	return rectLinkNew;
}
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
/* Param: Threshold (��ֵ) 
/* ��ע��RGB -> Gray, ֵ���ڷ�ֵ�ĸ���, С�ڷ�ֵ�ĸ���
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
/* Function: Gradient Sharpening Algorithm (�ݶ���)
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

    // ��ֵ
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
			// ��y ��,��x ��
			uint_32 pixel = pSrc[index + x];

			// ��y ��,��x+1 ��
			uint_32 pixel1 = pSrc[index + x + 1];

			// ��y+1 ��,��x ��
			uint_32 pixel2 = pSrc[index + m_Width + x];

			// �ֱ����R, G, B������ݶ�
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

			// ����Ŀ��RGB
			pDst[index + x] = RGB(r, g, b);
		}
	}

	// ���һ��
	{
		int index = (m_Height - 1) * m_Width;
		//int index = 0;

		for (x = 0; x < m_Width; x++)
		{
			//���һ��,��x ��
			uint_32 pixel = pSrc[index + x];
			
		    // ���һ��,��x+1 ��
			uint_32 pixel1 = pSrc[index + x + 1];
			
			// �����ڶ���,��x ��
			uint_32 pixel2 = pSrc[index - m_Width + x];
			
		    // �ֱ����R, G, B������ݶ�
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

			// ����Ŀ��RGB
			pDst[index + x] = RGB(r, g, b);
		}
		
	}

	return EXIT_SUCCESS;
}

/************************************************************************/
/*                  Pattern Recognition Algorithm                       */
/************************************************************************/

/************************************************************************/
/* Function: Scatter Noise Algorithm (��ɢ����)
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

	// ������
	m_iContinuousNum = 0;

	// ��ʼ��������
	//�����ж������ĳ�����ֵΪ15
	//������뿼��������ӵĺڵ����ĿС��15����Ϊ�������������
	int iLength = 15;

	// ѭ������
	int x, y, i;

	// ������ʱ�־λ�ռ�
	bool* pbFlagLab = new bool[m_Width * m_Height];
	for (i = 0; i < m_Width * m_Height; i++)
	{
		pbFlagLab[i] = false;
	}

	// �����м�����Ŀռ�
	bool* pbTemp = new bool[m_Width * m_Height];

	// λ�ÿռ�
	POINT_I2 pLabPoint[21];

	// Ѱ����ɢ����
	for (y = 0; y < m_Height; y++)
	{
		int index = y * m_Width;

		for (x = 0; x < m_Width; x++)
		{
			// �Ȱѱ�־λ��Ϊ false
			for (i = 0; i < m_iContinuousNum; i++)
			{
				pbFlagLab[pLabPoint[i].Y * m_Width + pLabPoint[i].X] = false;
			}

			// ��������Ϊ 0
			m_iContinuousNum = 0;

			pbTemp[index + x] = Judge_Scatter_Noise(pSrc, pbFlagLab, x, y, pLabPoint, iLength);
		}
	}

	// ����ɢ����Ϊ��ɫ
	// Ѱ����ɢ����
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
/* Function: Judge Noise Algorithm (�ж��Ƿ�����ɢ����)
/*           ���õݹ��㷨ͳ��������ĸ�����ͨ����ֵ���ж��Ƿ�Ϊ��ɢ��
/* Param: Src Image 
/* Param: ��־λ����
/* Param: ��ǰ��ĺ�����
/* Param: ��ǰ��������� 
/* Param: ����ѿ����������������
/* Param: ��ɢ����ж�����
/* Return:  ����ɢ�㷵��false ������ɢ�㷵��true
/* Description: ֻ�ܶ�2ֵͼ����д���
*/
/************************************************************************/
bool CImageAlgorithms::Judge_Scatter_Noise(uint_32 *pSrc, bool *pLab, int x, int y, POINT_I2 lab_point[], int lenght)
{
	// ���������������Ҫ��˵��������ɢ�㣬����
	if(m_iContinuousNum >= lenght)
	{
		return true;
	}

	// ���ȼ�һ
	m_iContinuousNum++;

	// �趨���ʱ�־
	pLab[m_Width * y + x] = true;

	// ������ʵ�����
	lab_point[m_iContinuousNum - 1].X = x;
	lab_point[m_iContinuousNum - 1].Y = y;

	// ���صĻҶ�ֵ
	uint_8 gray;

	// ����ֵ
	int index = 0;

	// �����ж�
	// ���������������Ҫ��˵��������ɢ�㣬����
	if(m_iContinuousNum >= lenght)
	{
		return true;
	}
	else //�������ݹ�
	{	
		// �������������Լ����ϡ����ϡ����¡����°˸�����
		// ����Ǻ�ɫ�㣬����ú���������еݹ�

		// ���������
		if ((y - 1) >= 0)
		{
			index = (y - 1) * m_Width + x;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x, y - 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// �����������
		if (((y - 1) >= 0) && ((x - 1) >= 0))
		{
			index = (y - 1) * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y - 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// �����������
		if (((y - 1) >= 0) && ((x + 1) < m_Width))
		{
			index = (y - 1) * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y - 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// ���������
		if ((x - 1) >= 0)
		{
			index = y * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// ���������
		if ((x + 1) < m_Width)
		{
			index = y * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		//���������
		if ((y + 1) < m_Height)
		{
			index = (y + 1) * m_Width + x;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x, y + 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// �����������
		if (((y + 1) < m_Height) && ((x - 1) >= 0))
		{
			index = (y + 1) * m_Width + x - 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x - 1, y + 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}

		// �����������
		if (((y + 1) < m_Height) && ((x + 1) < m_Width))
		{
			index = (y + 1) * m_Width + x + 1;
			gray = GetRValue(pSrc[index]);
			if (gray == 0 && pLab[index] == false)
			{
				Judge_Scatter_Noise(pSrc, pLab, x + 1, y + 1, lab_point, lenght);
			}
		}

		// ���������������Ҫ��˵��������ɢ�㣬����
		if(m_iContinuousNum >= lenght)
		{
			return true;
		}
	}

	// ����ݹ����������false��˵������ɢ��
	return false;
}

/************************************************************************/
/* Function: Slope Adjust Algorithm (��б����)
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

	// �߶ȼ���
	long dCounts = 0;

	// ��߸߶�ƽ��ֵ
	double dLeftAvr = 0.0;

	// �ұ߸߶�ƽ��ֵ
	double dRightAvr = 0.0;

	// ������б��
	double dSlope;

	// ѭ������
	int x, y;

	// �������
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

	// �����ұ�
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

	// ����������б��
	dSlope = (dLeftAvr - dRightAvr) / (m_Width / 2);

	// ��ֵ
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
/* Function: Char Segment Algorithm (�ָ��ַ�)
/* Param: Src Image 
/* ˵��:��ͼ���д�ʶ����ַ����������������ش�Ÿ����ַ���λ����Ϣ������
*/
/************************************************************************/
CRectLink CImageAlgorithms::Char_Segment(uint_32 *pSrc)
{
	//�����������ÿ���ַ����������
	CRectLink rectLink1, rectLink2;
	rectLink1.clear();
	rectLink2.clear();

	// ���涥���͵ײ�λ��
	int iTop, iBottom;

	// ѭ������
	int x, y;

	// �Ҷ���λ��
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

	// �ҵײ�λ��
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

	// �����Ƿ����һ���ַ��ָ�ı�־
	bool bFlag = false;

	// ����ɨ��һ�����Ƿ��ֺ�ɫ��
	bool bBlack = false;

	// ���λ����Ϣ�Ľṹ��
	CRect rect;

	// ����������
	int iDigicount = 0;

	// ��
	for (x = 0; x < m_Width; x++)
	{
		// ɨ����һ��
		bBlack = false;

		for (y = 0; y < m_Height; y++)
		{
			uint_32 gray = pSrc[y * m_Width + x];

			if (gray == 0)
			{
				// ���ֺڵ�,�ѱ�־��Ϊ true
				bBlack = true;

				// �ж��Ƿ������һ���ָ�
				if (bFlag == false)
				{
					rect.left = x;

					bFlag = true;
				} 
				else  // �ַ��ָ��Ѿ���ʼ
				{
					break;
				}
			}
		}

		// ����Ѿ�ɨ�������ұ����У�˵������ͼ��ɨ����ϡ��˳�
		if (x == m_Width - 1)
		{
			break;
		}

		// ������� bBlack ��Ϊ false��˵��ɨ����һ�У���û�з��ֺڵ㡣������ǰ�ַ��ָ����
		if (bFlag == true && bBlack == false)
		{
			// ��¼�ַ�������Ϣ
			rect.right = x;

			rect.top = iTop;

			rect.bottom = iBottom;

			// ��������һ�����أ�����ѹ���ַ�
			rect.InflateRect(1, 1);

			// ������ṹ�������λ����Ϣ������1�ĺ���
			rectLink1.push_back (rect);

			// ���ñ�־λ����ʼ��һ�ε��ַ��ָ�
			bFlag = false;

			//�ַ�����ͳ�Ƽ�������1
			iDigicount++;
		}
	}

	/**************************   ��ȷ����ÿ�����εı߽�  ***************/
	// �� rectLink1 ���� rectLink2
	rectLink2 = rectLink1;
	rectLink2.clear();

	// ���¶���һ������
	CRect rectNew;

	// ��������1��ͷ��β�������ɨ��
	while(!rectLink1.empty())
	{
		rect = rectLink1.front();

		rectLink1.pop_front();

		rectNew.left  = rect.left  - 1;
		rectNew.right = rect.right + 1;

		// ���϶���ɨ������ϱ߽�
		for (y = rect.top; y < rect.bottom; y++)
		{
			for (x = rect.left; x < rect.right; x++)
			{
				uint_32 gray = pSrc[y * m_Width + x];

				if (gray == 0)
				{
					rectNew.top = y - 1;

					// ǿ���˳�
					y = rect.bottom;

					break;
				}
			}
		}

		// ���¶���ɨ������±߽�
		for (y = rect.bottom; y >= rect.top; y--)
		{
			for (x = rect.left; x < rect.right; x++)
			{
				uint_32 gray = pSrc[y * m_Width + x];

				if (gray == 0)
				{
					rectNew.bottom = y + 1;

					// ǿ���˳�
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
/* Function: Char Size Normalize Algorithm (�ַ���С��һ��)
/* Param: Ŀ��ͼ��
/* Param: Դͼ��
/* Param: ÿ���ַ�������ָ��������
/* Param: ��һ�����
/* Param: ��һ���߶�
/* Return: ���ع�һ������ַ���������
/* ˵��: �������ָ���ַ����������Ŵ���ʹ���ǵĿ�͸�һֱ���Է�����������ȡ
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

	// �����������
	double dWidthScale = 0.0;

	// �߶���������
	double dHeightScale = 0.0;

	// ��һ������ַ���������
	CRectLink norRectLink;
	norRectLink.clear();

	// ѭ������
	int x, y, i;

	// ��Ŀ��ͼ����Ϊ��ɫ
	for (i = 0; i< m_Width * m_Height; i++)
	{
		pDst[i] = RGB(255, 255, 255);
	}

	while (!rectLink.empty())
	{
		CRect rect = rectLink.front();
		rectLink.pop_front();

		// ��������������
		dWidthScale = (double)(1.0 * norWidth / rect.Width());

		// ����߶���������
		dHeightScale = (double)(1.0 * norHeight / rect.Height());

		CRect rectNew;
		rectNew.left = rect.left;
		rectNew.right = rect.left + norWidth; 
		rectNew.top = rect.top;
		rectNew.bottom = rect.top + norHeight;

		// ���Ĳ���
		for (y = rectNew.top; y < rectNew.bottom; y++)
		{
			for (x = rectNew.left; x < rectNew.right; x++)
			{
				// ���㵱ǰ����Դͼ���ж�Ӧ���λ��
				int x_src = rectNew.left + (int)((x - rectNew.left) / dWidthScale);
				int y_src = rectNew.top + (int)((y - rectNew.top) / dHeightScale);

				pDst[y * m_Width + x] = pSrc[y_src * m_Width + x_src];
			}
		}

		// ��ӹ�һ������ַ�����
		norRectLink.push_back(rectNew);
	}

	return norRectLink;
}

/************************************************************************/
/* Function: Char Auto Align Algorithm (�ַ���������)
/* Param: Ŀ��ͼ��
/* Param: Դͼ��
/* Param: ÿ���ַ�������ָ��������
/* Return: ���ع�һ������ַ���������
/* ˵��: �������˱�׼��������ַ����й���������
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

	// ÿ���ַ��ľ��εĿ��
	int width = rectLink.front().Width();

	// ÿ���ַ��ľ��εĸ߶�
	int height = rectLink.front().Height();

    // �µ��ַ���������
	CRectLink rectLinkNew;

	// �ַ�����ͳ��
	int Count = rectLink.size();
	int iWidth = Count * width;
	int iCounts = 0;

	// ѭ������
	int x, y;

	while(!rectLink.empty())
	{
		// ���� �м����
		CRect rect, rectNew;

		rect = rectLink.front();
		rectLink.pop_front();

		rectNew.left = iCounts * width;
		rectNew.right = (iCounts + 1) * width;
		rectNew.top = 0;
		rectNew.bottom = height;

		rectLinkNew.push_back(rectNew);

		// ��ֵ
		for (y = 0; y < height; y++)
		{
			for (x = iCounts * width; x < (iCounts + 1) * width; x++)
			{
				// ���㵱ǰ����Դͼ���ж�Ӧ���λ��
				int x_src = rect.left + (x - iCounts * width);
				int y_src = rect.top + y;

				pDst[y * iWidth + x] = pSrc[y_src * m_Width + x_src];
			}
		}

        iCounts++;
	}

	return rectLinkNew;
}
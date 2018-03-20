#ifndef _IMAGE_ALGORITHM_H_
#define _IMAGE_ALGORITHM_H_

#include "TypeDefine.h"

#include <complex>
using namespace std;

#pragma once

class CImageAlgorithms
{
public:
	CImageAlgorithms(void);
	~CImageAlgorithms(void);

public:
	// Init
	int  Init(int width, int height);

	// Release
	int Release();

public:
        // RGB Image to Gray Image Algorithm
	int RGB_To_Gray(uint_32 * pDst, uint_32* pSrc, int nType);

        // Threshold Transformation
	int Threshold_Transform(uint_32* pDst, uint_32* pSrc, uint_8 uThreshold);

        // Ã›∂»»ÒªØ
        int Gradient_Sharpening(uint_32* pDst, uint_32* pSrc);

	/************************************************************************/
	/*                  Pattern Recognition Algorithm                       */
	/************************************************************************/
	// Scatter Noise Algorithm
	int Scatter_Noise(uint_32* pDst, uint_32* pSrc);
	bool Judge_Scatter_Noise(uint_32* pSrc, bool* pLab, int x, int y, POINT_I2 lab_point[], int length);

	// Slope Adjust
	int Slope_Adjust(uint_32* pDst, uint_32* pSrc);

    // Char Segment
	CRectLink Char_Segment(uint_32* pSrc);

	// Char Size Normalize
	CRectLink Char_Size_Normalize(uint_32* pDst, uint_32* pSrc, CRectLink rectLink, int norWidth, int norHeight);

	// Char Auto Align
	CRectLink Char_Auto_Align(uint_32* pDst, uint_32* pSrc, CRectLink rectLink);

private:
	// Image Width
	int m_Width;

	// Image Height
	int m_Height;

	// Scatter Noise Algorithm
	int m_iContinuousNum;
};

#endif
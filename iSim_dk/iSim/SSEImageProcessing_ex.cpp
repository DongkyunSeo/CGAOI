#include "StdAfx.h"
#include "SSEImageProcessing.h"
#include <intrin.h>

//영상반전
void SSEInversion(unsigned char* pSrc, unsigned char* pDest, int ImageHeight, int ImageWidth)
{
	int heightS = ImageHeight;
	int widthS = ImageWidth / 16;
	int rowIndex = 0;
	__m128i rowh0;
	__m128i result;
	__m128i mask255 = _mm_set1_epi8((unsigned char)255);

	for (int i = 0; i<heightS; i++)
	{
		rowIndex = i*widthS;
		__m128i* pSrc1 = (__m128i*)pSrc + rowIndex;
		__m128i* pDest1 = (__m128i*)pDest + rowIndex;
		for (int j = 0; j<widthS; j++)
		{
			// Make inversion

		}

	}
}
//EX2
void SSEImageAND(unsigned char* src, unsigned char* ref, unsigned char* output,
	int ImageHeight, int ImageWidth)
{
	// Make Image AND
	//----------------------------------------------------------------------------//
}

//EX3
void SSEDilation(unsigned char* src, unsigned char* output, int ImageHeight, int ImageWidth)
{

	// Make Dilation
	//----------------------------------------------------------------------------//

}

void SSEErosion(unsigned char* src, unsigned char* output, int ImageHeight, int ImageWidth)
{

	// Make Erosion
	//----------------------------------------------------------------------------//

}

//EX4
void SSEMeanFiltering3(unsigned char* src, unsigned char* output, int height, int width)
{

	// Make mean filter
	//----------------------------------------------------------------------------//

}


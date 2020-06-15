#pragma once

// 영상반전
void SSEInversion(unsigned char* pSrc, unsigned char* pDest, int ImageHeight, int ImageWidth);

//  Image AND
void SSEImageAND(unsigned char* src, unsigned char* ref, unsigned char* output,
	int ImageHeight, int ImageWidth);

// 3x3 Dilation 
void SSEDilation(unsigned char* src, unsigned char* output, int ImageHeight, int ImageWidth);

//3x3 Erosion
void SSEErosion(unsigned char* src, unsigned char* output, int ImageHeight, int ImageWidth);

// 3x3 mean filtering 
void SSEMeanFiltering3(unsigned char* src, unsigned char* output, int height, int width);

 
#pragma once

#include "../dist/cx/h/ximage.h" 
#include "../dist/ipl/h/ipl.h"  

using namespace ipl;

typedef struct _IMGINFO {
	int x;
	int y;
	int gl;
}IMGINFO;



class CAlgProc
{
public:
    CAlgProc(void);
    ~CAlgProc(void);
    int Edge_AvrDiff(CIMAGE &src, CIMAGE &dst, int pwin, int win,  int thre);

	int fnDiffMin(U8* pImg, U8* pOut, U8* insp_map, int wid, int hgt, int pitchX, int pitchY, int sx, int sy, int ex, int ey);
	int fnDiffMin_VERT(U8* pImg, U8* pOut, U8* insp_map, int wid, int hgt, int pitchX, int pitchY, int sx, int sy, int ex, int ey);

	int Defocus_Index(U8* im, int wid, int hgt, int offset, int nThrsholdH, int nThresholdL);
	void GetImageInfo(CIMAGE& cimg, int thre, std::vector<IMGINFO>& vdata, int highlowFlag);
	float Get_R_Squared_1st(_In_ std::vector<IMGINFO>& vImg, _Out_ int* dirAngle, CRECT rt, double* dAA, double* dBB);
	float Get_R_Squared_2nd(_In_ std::vector<IMGINFO>& vImg, _In_ int dirAngle, CRECT rt);
	float GetLinetDensity(uint8_t* pImg, int thre, int threFlag, int wid, int hgt, int sx, int sy, int ex, int ey, double AA, double BB);

	int GetLineEq(CPOS pt1, CPOS pt2, double* AA, double* BB);
	void Get_SSR_SSE(_In_ std::vector<IMGINFO>& vpos, _Out_ double* SSR_r, _Out_ double* SSE_r, double avgY, _In_ double AA, _In_ double BB);
	void Get_SSR_SSE_2nd(_In_ std::vector<IMGINFO>& vpos, _Out_ double* SSR_r, _Out_ double* SSE_r, double avgY, _In_ float AA, _In_ float BB, float CC);
	void Get2ndEq(CPOS pt1, CPOS pt2, CPOS pt3, float* fA, float* fB, float* fC);

	int GetEdgeAngle(uint8_t* pImg, int width, int height, CRECT& rt, int *angle_result, int mag_thre, double *stdA);
	float GetStdFromArr(std::vector<float>& arr, float avg);

	int GetSumofImg(CIMAGE img);

	int fnMedianFilter(CIMAGE& src, CIMAGE& dst, int dx, int dy);
};


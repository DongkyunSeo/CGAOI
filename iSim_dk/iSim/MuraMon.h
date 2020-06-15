#pragma once

/*
// CxImage dll link
#ifdef _WIN64
#if defined (_UNICODE)
#pragma comment(lib, "../dist/cx/lib/cximage64u.lib")
#else
#pragma comment(lib, "../dist/cx/lib/cximage64.lib")
#endif
#else
#if defined (_UNICODE)
#pragma comment(lib, "../dist/cx/lib/cximage32u.lib")
#else
#pragma comment(lib, "../dist/cx/lib/cximage32.lib")
#endif
#endif

// ipl dll link
#ifdef _WIN64
#pragma comment(lib,"../dist/ipl/lib/ipl64.lib")
#else // WIN32
#pragma comment(lib,"../dist/ipl/lib/ipl32.lib")
#endif
*/

#include "../dist/cx/h/ximage.h" 
#include "../dist/ipl/h/ipl.h"

using namespace ipl;

typedef struct
{
    int left;
    int top;
    int right;
    int bottom;
    int wid;
    int hgt;
} ROI;

typedef struct
{
    int cx;
    int cy;
    int lx;
    int ly;
    int sy;
    int ey;
    double peak;
    int mergenum;
} MURA;

class CMuraMon
{
public:
    CMuraMon();
    ~CMuraMon();
    
    vector<MURA> m_MuraList;
    unsigned char* m_pImageData;
    CString ErrMsg;

private:
    ROI m_ROI;
    BOOL m_bSetImage;
    BOOL m_bPreProcParam;
    BOOL m_bDetectParam;
    double m_Rotate;
    int m_MaskSize;
    double m_Sigma;
    double m_Gain;
    int m_PrjWid;
    int m_Thre;
    double m_LengthThre;
    int m_MergeMargin;
    int m_IndexThre;
    int m_ProcImageFlag;
    int m_PeakMargin;

public:
    int SetImage( unsigned char* ImgPtr, int ImgWid, int ImgHgt, int bpp, int Left, int Top, int Right, int Bottom);
    int SetPreProcParam(double rotate, int MaskSize, double Sigma, double Gain);
    int SetDetectParam(int ProjWidth, int Threshold, double LengthThre, int MergeMargin, int IndexThre, int ProcImageFlag, int PeakMargin);
    int DetectMura();
    int SaveMuraImage(CString Pathname);


    
};


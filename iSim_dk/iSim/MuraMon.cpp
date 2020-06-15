#include "StdAfx.h"
#include "MuraMon.h"

#define MAX_OBJ 100 // Vector 대신 array 사용. Vector 사용시 에러나는 경우에 대한 우회. 20180531 seonghoon.kim@lge.com

CMuraMon::CMuraMon()
{
    m_pImageData = NULL;
    m_bSetImage = FALSE;
    m_bPreProcParam = FALSE;
    m_bDetectParam = FALSE;
    ipl::ValidateIPL();
}


CMuraMon::~CMuraMon()
{
    if (m_pImageData != NULL) delete[] m_pImageData;
    m_MuraList.clear();
}

/**
@date 2018/05/10
@author 김성훈 (seonghoon@lge.com)
@brief 이미지의 메모리 포인터와 크기, Bit depth, ROI정보를 세팅.
@param ImgPtr : 이미지가 저장된 DIB의 이미지 데이터 영역 메모리 포인터
@param ImgWid : 이미지의 가로 폭 (Pixel), Effective Width가 아님.
@param ImgHgt : 이미지의 높이 (Pixel) 
@param bpp : 이미지의 bit depth. 8 또는 24만 허용됨.
@param Left : 지정영역(ROI)의 left 좌표 (이미지 좌표계).
@param Top : 지정영역(ROI)의 top 좌표 (이미지 좌표계).
@param Right : 지정영역(ROI)의 right 좌표 (이미지 좌표계).
@param Bottom : 지정영역(ROI)의 bottom 좌표 (이미지 좌표계).
@return : 무조건 0.
@remark
이미지 정보를 세팅함. 이미지 정보 세팅되어 있지 않으면 detect 진행 불가 .
*/
int CMuraMon::SetImage( unsigned char* ImgPtr, int ImgWid, int ImgHgt, int bpp
    , int Left, int Top, int Right, int Bottom)
{
    // Set ROI;
    m_ROI.left = Left;
    m_ROI.top = Top;
    m_ROI.right = Right;
    m_ROI.bottom = Bottom;
    m_ROI.wid = Right - Left;
    m_ROI.hgt = Bottom - Top;

    // Get Image Buffer;
    if (m_pImageData != NULL) delete[] m_pImageData;
    m_pImageData = new unsigned char[m_ROI.wid * m_ROI.hgt];


    int EffWidth = ((((bpp * ImgWid) + 31) / 32) * 4);
    int i, j;
    unsigned char* ptr;

    if (bpp == 8)
    {
        ptr = ImgPtr + (ImgHgt - Top - 1)*EffWidth + Left;

        for (j = 0; j < m_ROI.hgt; j++)
        {
            memcpy(m_pImageData + m_ROI.wid*j, ptr - EffWidth*j, m_ROI.wid);
        }
    }
    else if(bpp==24)
    {
        for (j = 0; j < m_ROI.hgt; j++)
        {
            ptr = ImgPtr + (ImgHgt - Top - j - 1)*EffWidth + Left * 3;
            for (i = 0; i < m_ROI.wid; i++)
            {
                m_pImageData[j*m_ROI.wid + i] = ptr[i * 3 + 1];
            }
        }
    }
    else return -1; 

    m_bSetImage = TRUE;

    return 0;
}

/**
@date 2018/05/10
@author 김성훈 (seonghoon@lge.com)
@brief 전처리 파라메터 설정.
@param rotate : 영상 회전 각도 (degree단위, CW방향). 
@param MaskSize : LoG필터의 size.
@param Sigma : LoG 필터 형상 정의. 대략 MaskSize의 0.12배 정도.
@param Gain : 필터 적용시 gain. 처리 결과에 따라 적절히 조정. 통상 MaskSize가 커지면 Gain은 줄여야 함.
@return : 무조건 0.
@remark
전저리 정보를 세팅함. 전처리 정보 세팅되어 있지 않으면 detect 진행 불가 .
*/
int CMuraMon::SetPreProcParam(double rotate, int MaskSize, double Sigma, double Gain)
{
    m_Rotate = rotate;
    m_MaskSize = MaskSize;
    m_Sigma = Sigma;
    m_Gain = Gain;

    m_bPreProcParam = TRUE;
    return 0;
}

/**
@date 2018/05/10
@author 김성훈 (seonghoon@lge.com)
@brief 검출 파라메터 설정.
@param ProjWidth : 단위 Slice의 폭.
@param Threshold : 후보점 검출기준 (상대적인 Gray value). 값이 작을수록 많이 검출. (10~30 정도가 적절)
@param LengthThre : 얼룩으로 판정할 길이 기준. 처리 영역 폭의 LengthThre배 이상일따 얼룩으로 인정.
@param MergeMargin : 후보점들을 merge할때 margin값. 값이 커지면 merge될 확률이 높아짐. 통상 0~5 사이값.
@param IndexThre : merge이후 평균 Peak 값에 따라 얼룩으로 판정할 기준값. 
@param ProcImageFlag : 1이면 Result Image에 처리 영상 표시, 0이면 원본 Gray영상 표시.
@param PeakMargin : Peak검출 마진. 지정 Size이하의 Peak는 무시함. 3 정도가 적당함.
@return : 무조건 0.
@remark
검출 파라메터 정보를 세팅함. 검출 정보 세팅되어 있지 않으면 detect 진행 불가 .
*/
int CMuraMon::SetDetectParam(int ProjWidth, int Threshold, double LengthThre, int MergeMargin, int IndexThre, int ProcImageFlag, int PeakMargin)
{
    m_PrjWid = ProjWidth;
    m_Thre = Threshold;
    m_LengthThre = LengthThre;
    m_MergeMargin = MergeMargin;
    m_IndexThre = IndexThre;
    m_ProcImageFlag = ProcImageFlag;
    m_PeakMargin = PeakMargin;

    m_bDetectParam = TRUE;

    return 0;
}

/**
@date 2018/05/10
@author 김성훈 (seonghoon@lge.com)
@brief 얼룩 검출 function.
@return : 성공하면 0, 아니면 -1.
@remark
미리 설정한 이미지 정보, 전처리 정보, 검출 정보에 기반하여 얼룩을 검출함.\n
검출 결과로, m_MuraList vector에 검출 정보 (위치, 크기, Peak값) 저장함.\n
*/
int CMuraMon::DetectMura()
{
    if (!m_bSetImage)
    {
        ErrMsg.Format(_T("Set Image Error"));
        return -1;
    }
    if (!m_bPreProcParam) 
    {
        ErrMsg.Format(_T("Set Pre-processing Parameter Error"));
        return -2;
    }
    if (!m_bDetectParam) 
    {
        ErrMsg.Format(_T("Set Detection Parameter Error"));
        return -3;
    }

    try
    {
        // 1. 전처리
        ipl::U64* buf;
        buf = new ipl::U64[m_ROI.wid*m_ROI.hgt]; // 임시 연산 영역 할당

        // Vector 대신 array 사용. Vector 사용시 에러나는 경우에 대한 우회. 20180531 seonghoon.kim@lge.com
        OBJECT* obuf;
        obuf = new ipl::OBJECT[MAX_OBJ];

        unsigned int* ProjData;
        ProjData = new unsigned int[m_ROI.hgt]; // Projection Data 영역 할당

        CIMAGE org(m_pImageData, 0, 0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);
        CIMAGE im(NULL, 0, 0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);
        CIMAGE im2(NULL,0,0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);

        transform::CopyImage(org, im);
        transform::RotateImage(im, im2, CPOS(m_ROI.wid / 2, m_ROI.hgt / 2), m_Rotate);
        filter::Average_3x3(im2,im);
        filter::Average_3x3(im, im2);

        // LoG Convolution 영상
        filter::LoG(im2, im, buf, m_MaskSize, m_Sigma, m_Gain);

        // 2. detection
        int i, j,k;
        int slice;

        slice = m_ROI.wid / m_PrjWid;

        m_MuraList.clear();

        vector<MURA> mlist;

        for (k = 0; k < slice; k++) // slice 별로
        {
            
            //2.1 Projection 구하기
            CIMAGE img(im.GetImgPtr() + k*m_PrjWid, 0, 0, m_PrjWid, m_ROI.hgt, m_ROI.wid);

            // 이미지 데이터에서 Horizontal Projection data 계산.
            calc::CalcProjection_Horz(img, ProjData);

            //2.2 Projection 보정하기
            calc::CompensateProjection(ProjData, ProjData, m_ROI.hgt, 1 ,m_PeakMargin);
          
            //2.3 보정 Projection을 이미지에 그려줌

            for (j = 0; j < m_ROI.hgt; j++)
            {
                for (i = 0; i < m_PrjWid; i++)
                {
                    img(i, j) = ProjData[j];
                }
            }

            CIMAGE slim(im2.GetImgPtr() + k*m_PrjWid, 0, 0, m_PrjWid, m_ROI.hgt, m_ROI.wid);

            //2.4 Projection으로부터 후보점 검출
            morph::Binarize(img, slim, 128-m_Thre, ipl::LOW);

            vector<OBJECT> olist;
            int onum;

            olist.clear();
            //onum = segment::DetectObject_8N(slim, olist, MAX_OBJ, m_PrjWid); // Vector 오류나는 경우가 있어 comment-out함 20180531 seonghoon.kim@lge.com

            // [시작] Vector 대신 array 사용. Vector 사용시 에러나는 경우에 대한 우회. 20180531 seonghoon.kim@lge.com
            onum = segment::DetectObject_8N(slim, obuf, MAX_OBJ, m_PrjWid); 

            for (i = 0; i < onum; i++)
            {
                olist.push_back(obuf[i]);
            }
            // [끝] Vector 대신 array 사용. Vector 사용시 에러나는 경우에 대한 우회. 20180531 seonghoon.kim@lge.com

            MURA m; int peak, temp;
            for (i = 0; i < olist.size(); i++)
            {
                m.cx = olist[i].cx+ k*m_PrjWid;
                m.cy = olist[i].cy;
                m.lx = olist[i].lx;
                m.ly = olist[i].ly;
                m.sy = olist[i].sy;
                m.ey = olist[i].ey;
                peak = 0;
                for (j = 0; j < m.ly; j++)
                {
                    temp = abs(128 - (int)ProjData[m.sy + j]);
                    if (peak < temp ) peak = temp;
                }
                m.peak = peak;
                m.mergenum = 1;
                mlist.push_back(m); 
            }
            //transform::CopyImage(slim, img);
        } // for slice


        CIMAGE tim(im.GetImgPtr() + slice*m_PrjWid, 0, 0, m_ROI.wid - slice*m_PrjWid, m_ROI.hgt, m_ROI.wid);
        if(m_ROI.wid - slice*m_PrjWid>0) // 예외 처리 : padding 영역크기가 0이 아닐때만 padding함. 20180531 seonghoon.kim@lge.com
            util::DrawRect(tim, CRECT(0, 0, m_ROI.wid - slice*m_PrjWid, m_ROI.hgt), 128, ipl::FILL);


        if (m_ProcImageFlag != 0)
        {
            transform::CopyImage(im, org);
        }


        // 3. filtering

        // 3.1 merge

        if (mlist.size() == 0) // 후보점이 없으면 종료.
        {
            m_MuraList.clear();
            delete[] buf;
            delete[] ProjData;
            return 0;
        }
        m_MuraList.push_back(mlist[0]);
        mlist.erase(mlist.begin());

        // Defect Merging
        for (j = 0; j < mlist.size() && j >= 0; j++)
        {
            for (i = 0; i < m_MuraList.size(); i++)
            {
                if (   (abs(m_MuraList[i].sy - mlist[j].sy) < m_MergeMargin)
                    || (abs(m_MuraList[i].sy - mlist[j].ey) < m_MergeMargin)
                    || (abs(m_MuraList[i].ey - mlist[j].sy) < m_MergeMargin)
                    || (abs(m_MuraList[i].ey - mlist[j].ey) < m_MergeMargin)
                    /*|| (abs(m_MuraList[i].cy - mlist[j].cy) < m_MergeMargin)*/)
                {
                    // merge
                    m_MuraList[i].cx = m_ROI.wid / 2;
                    m_MuraList[i].cy += mlist[j].cy;
                    m_MuraList[i].sy = min(m_MuraList[i].sy, mlist[j].sy);
                    m_MuraList[i].ey = max(m_MuraList[i].ey, mlist[j].ey);
                    m_MuraList[i].lx += mlist[j].lx;
                    m_MuraList[i].ly = m_MuraList[i].ey - m_MuraList[i].sy;
                    m_MuraList[i].peak += mlist[j].peak;
                    m_MuraList[i].mergenum++;
                    break;
                }
                else
                {
                    //m_MuraList에 추가
                    if (i==m_MuraList.size()-1)
                        m_MuraList.push_back(mlist[j]); 
                }
                //mlist.erase(mlist.begin() + j);
                //j--;
            }
        }

        // 3.2 Defect Filtering
        char msg[20];
        for (i = 0; i < m_MuraList.size() && i>=0 ; i++)
        {
            m_MuraList[i].peak = (m_MuraList[i].peak / (double)m_MuraList[i].mergenum);
            if ( (m_MuraList[i].lx < (int)(m_LengthThre*m_PrjWid*slice)) || (m_MuraList[i].peak<m_IndexThre) )
            {
                m_MuraList.erase(m_MuraList.begin() + i);
                i--;
                
            }
            else
            {
               // m_MuraList[i].peak = (m_MuraList[i].peak / (double)m_MuraList[i].mergenum);
                m_MuraList[i].cy = (int)((double)m_MuraList[i].cy / (double)m_MuraList[i].mergenum);

                sprintf_s(msg, "%.2f", (float)m_MuraList[i].peak);
                util::DrawRect(org, CRECT(m_MuraList[i].cx - m_MuraList[i].lx/2, m_MuraList[i].sy
                                        , m_MuraList[i].cx + m_MuraList[i].lx / 2, m_MuraList[i].ey), 200, ipl::UNFILL);
                util::DrawTextMsg(org, CPOS((m_ROI.wid - 40)*(i % 2), m_MuraList[i].cy - 5), msg, 255, 0);

                m_MuraList[i].cx += m_ROI.left;
                m_MuraList[i].cy += m_ROI.top;
                m_MuraList[i].sy += m_ROI.top;
                m_MuraList[i].ey += m_ROI.top;
            }
        }

        delete[] buf;
        delete[] ProjData;
        delete[] obuf; // Vector 대신 array 사용. Vector 사용시 에러나는 경우에 대한 우회. 20180531 seonghoon.kim@lge.com
        return m_MuraList.size();

    }
    catch (const char* msg)
    {
        ErrMsg.Format(_T("Processing Error :%c"),msg);
        throw (msg);
        return -4;
    }

    return 0;
}

/**
@date 2018/05/10
@author 김성훈 (seonghoon@lge.com)
@brief 결과 영상 저장 Function.
@param Pathname : 영상을 저장할 pathname (폴더경로+파일명). BMP, JPG, PNG 형식 지원
@return : 무조건 0.
@remark
검출 파라메터에 지정한 방식 (처리 영상, 원본 Gray 영상)으로 저장된 결과 영상을 지정된 path에 저장함.\n 
*/
int CMuraMon::SaveMuraImage(CString Pathname)
{
    CxImage imgs(m_ROI.wid, m_ROI.hgt, 8, CXIMAGE_FORMAT_BMP);
    imgs.GrayScale();
    CIMAGE img(m_pImageData, 0, 0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);
    img.CopyDataToDib(imgs.GetBits(), 0, 0, imgs.GetHeight(), imgs.GetEffWidth());

    imgs.Save(Pathname, CXIMAGE_FORMAT_JPG);
    return 0;
}

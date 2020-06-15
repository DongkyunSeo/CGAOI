#include "StdAfx.h"
#include "MuraMon.h"

#define MAX_OBJ 100 // Vector ��� array ���. Vector ���� �������� ��쿡 ���� ��ȸ. 20180531 seonghoon.kim@lge.com

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
@author �輺�� (seonghoon@lge.com)
@brief �̹����� �޸� �����Ϳ� ũ��, Bit depth, ROI������ ����.
@param ImgPtr : �̹����� ����� DIB�� �̹��� ������ ���� �޸� ������
@param ImgWid : �̹����� ���� �� (Pixel), Effective Width�� �ƴ�.
@param ImgHgt : �̹����� ���� (Pixel) 
@param bpp : �̹����� bit depth. 8 �Ǵ� 24�� ����.
@param Left : ��������(ROI)�� left ��ǥ (�̹��� ��ǥ��).
@param Top : ��������(ROI)�� top ��ǥ (�̹��� ��ǥ��).
@param Right : ��������(ROI)�� right ��ǥ (�̹��� ��ǥ��).
@param Bottom : ��������(ROI)�� bottom ��ǥ (�̹��� ��ǥ��).
@return : ������ 0.
@remark
�̹��� ������ ������. �̹��� ���� ���õǾ� ���� ������ detect ���� �Ұ� .
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
@author �輺�� (seonghoon@lge.com)
@brief ��ó�� �Ķ���� ����.
@param rotate : ���� ȸ�� ���� (degree����, CW����). 
@param MaskSize : LoG������ size.
@param Sigma : LoG ���� ���� ����. �뷫 MaskSize�� 0.12�� ����.
@param Gain : ���� ����� gain. ó�� ����� ���� ������ ����. ��� MaskSize�� Ŀ���� Gain�� �ٿ��� ��.
@return : ������ 0.
@remark
������ ������ ������. ��ó�� ���� ���õǾ� ���� ������ detect ���� �Ұ� .
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
@author �輺�� (seonghoon@lge.com)
@brief ���� �Ķ���� ����.
@param ProjWidth : ���� Slice�� ��.
@param Threshold : �ĺ��� ������� (������� Gray value). ���� �������� ���� ����. (10~30 ������ ����)
@param LengthThre : ������� ������ ���� ����. ó�� ���� ���� LengthThre�� �̻��ϵ� ������� ����.
@param MergeMargin : �ĺ������� merge�Ҷ� margin��. ���� Ŀ���� merge�� Ȯ���� ������. ��� 0~5 ���̰�.
@param IndexThre : merge���� ��� Peak ���� ���� ������� ������ ���ذ�. 
@param ProcImageFlag : 1�̸� Result Image�� ó�� ���� ǥ��, 0�̸� ���� Gray���� ǥ��.
@param PeakMargin : Peak���� ����. ���� Size������ Peak�� ������. 3 ������ ������.
@return : ������ 0.
@remark
���� �Ķ���� ������ ������. ���� ���� ���õǾ� ���� ������ detect ���� �Ұ� .
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
@author �輺�� (seonghoon@lge.com)
@brief ��� ���� function.
@return : �����ϸ� 0, �ƴϸ� -1.
@remark
�̸� ������ �̹��� ����, ��ó�� ����, ���� ������ ����Ͽ� ����� ������.\n
���� �����, m_MuraList vector�� ���� ���� (��ġ, ũ��, Peak��) ������.\n
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
        // 1. ��ó��
        ipl::U64* buf;
        buf = new ipl::U64[m_ROI.wid*m_ROI.hgt]; // �ӽ� ���� ���� �Ҵ�

        // Vector ��� array ���. Vector ���� �������� ��쿡 ���� ��ȸ. 20180531 seonghoon.kim@lge.com
        OBJECT* obuf;
        obuf = new ipl::OBJECT[MAX_OBJ];

        unsigned int* ProjData;
        ProjData = new unsigned int[m_ROI.hgt]; // Projection Data ���� �Ҵ�

        CIMAGE org(m_pImageData, 0, 0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);
        CIMAGE im(NULL, 0, 0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);
        CIMAGE im2(NULL,0,0, m_ROI.wid, m_ROI.hgt, m_ROI.wid);

        transform::CopyImage(org, im);
        transform::RotateImage(im, im2, CPOS(m_ROI.wid / 2, m_ROI.hgt / 2), m_Rotate);
        filter::Average_3x3(im2,im);
        filter::Average_3x3(im, im2);

        // LoG Convolution ����
        filter::LoG(im2, im, buf, m_MaskSize, m_Sigma, m_Gain);

        // 2. detection
        int i, j,k;
        int slice;

        slice = m_ROI.wid / m_PrjWid;

        m_MuraList.clear();

        vector<MURA> mlist;

        for (k = 0; k < slice; k++) // slice ����
        {
            
            //2.1 Projection ���ϱ�
            CIMAGE img(im.GetImgPtr() + k*m_PrjWid, 0, 0, m_PrjWid, m_ROI.hgt, m_ROI.wid);

            // �̹��� �����Ϳ��� Horizontal Projection data ���.
            calc::CalcProjection_Horz(img, ProjData);

            //2.2 Projection �����ϱ�
            calc::CompensateProjection(ProjData, ProjData, m_ROI.hgt, 1 ,m_PeakMargin);
          
            //2.3 ���� Projection�� �̹����� �׷���

            for (j = 0; j < m_ROI.hgt; j++)
            {
                for (i = 0; i < m_PrjWid; i++)
                {
                    img(i, j) = ProjData[j];
                }
            }

            CIMAGE slim(im2.GetImgPtr() + k*m_PrjWid, 0, 0, m_PrjWid, m_ROI.hgt, m_ROI.wid);

            //2.4 Projection���κ��� �ĺ��� ����
            morph::Binarize(img, slim, 128-m_Thre, ipl::LOW);

            vector<OBJECT> olist;
            int onum;

            olist.clear();
            //onum = segment::DetectObject_8N(slim, olist, MAX_OBJ, m_PrjWid); // Vector �������� ��찡 �־� comment-out�� 20180531 seonghoon.kim@lge.com

            // [����] Vector ��� array ���. Vector ���� �������� ��쿡 ���� ��ȸ. 20180531 seonghoon.kim@lge.com
            onum = segment::DetectObject_8N(slim, obuf, MAX_OBJ, m_PrjWid); 

            for (i = 0; i < onum; i++)
            {
                olist.push_back(obuf[i]);
            }
            // [��] Vector ��� array ���. Vector ���� �������� ��쿡 ���� ��ȸ. 20180531 seonghoon.kim@lge.com

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
        if(m_ROI.wid - slice*m_PrjWid>0) // ���� ó�� : padding ����ũ�Ⱑ 0�� �ƴҶ��� padding��. 20180531 seonghoon.kim@lge.com
            util::DrawRect(tim, CRECT(0, 0, m_ROI.wid - slice*m_PrjWid, m_ROI.hgt), 128, ipl::FILL);


        if (m_ProcImageFlag != 0)
        {
            transform::CopyImage(im, org);
        }


        // 3. filtering

        // 3.1 merge

        if (mlist.size() == 0) // �ĺ����� ������ ����.
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
                    //m_MuraList�� �߰�
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
        delete[] obuf; // Vector ��� array ���. Vector ���� �������� ��쿡 ���� ��ȸ. 20180531 seonghoon.kim@lge.com
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
@author �輺�� (seonghoon@lge.com)
@brief ��� ���� ���� Function.
@param Pathname : ������ ������ pathname (�������+���ϸ�). BMP, JPG, PNG ���� ����
@return : ������ 0.
@remark
���� �Ķ���Ϳ� ������ ��� (ó�� ����, ���� Gray ����)���� ����� ��� ������ ������ path�� ������.\n 
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

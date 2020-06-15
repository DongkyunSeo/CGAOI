#include "StdAfx.h"
#include "AlgProc.h"

#include <math.h>


CAlgProc::CAlgProc(void)
{
}


CAlgProc::~CAlgProc(void)
{
}

int CAlgProc::Edge_AvrDiff(CIMAGE &src, CIMAGE &dst,int pwin, int win, int thre)
{
//    if (!bValidIPL) throw("Invalid IPL");
    if (!src.IsValid()) throw ("Edge_AvrDiff : Invalid Image (src)");
    if (!dst.IsValid()) throw ("Edge_AvrDiff : Invalid Image (dest)");

    if (src.GetRoiPtr() == dst.GetRoiPtr()) throw("Edge_AvrDiff : src addr == dest addr");

    int wid, hgt;
    wid = src.Width();
    hgt = src.Height();

    if ((wid != dst.Width()) || (hgt != dst.Height()))
        throw ("Edge_AvrDiff : src size != dest size");

    if (wid <= 0 || hgt <= 0) throw ("Edge_AvrDiff : abnormal image size");

    CIMAGE im_src(src.GetRoiPtr(), 0, 0, src.Width(), src.Height(), src.Offset());
    CIMAGE im_dst(dst.GetRoiPtr(), 0, 0, dst.Width(), dst.Height(), dst.Offset());  

    int i,j,k,m,n;
    int dh,dv,dd,du, val;
    int hp,vp;
    int *hprj,*vprj;

    hprj= new int[pwin*2+1];
    vprj= new int[pwin*2+1];
    
    for(j=pwin;j<hgt-pwin;j++)
    {
        for(i=pwin;i<wid-pwin;i++)
        {
            dh =0;dv=0;dd=0;du=0;
            for(m=-pwin;m<=pwin;m++)
            {
                hp=0;
                vp=0;
                for(n=-pwin;n<=pwin;n++)
                {
                    hp+=src(i+n,j+m);
                    vp+=src(i+m,j+n);
                }
                hprj[m+pwin]=(int)((float)hp/(float)(pwin*2+1)+0.5);
                vprj[m+pwin]=(int)((float)vp/(float)(pwin*2+1)+0.5);

            }
            for(k=0;k<win;k++)
            {
                dh += hprj[pwin+k]-hprj[pwin-k];
                dv += vprj[pwin+k]-vprj[pwin-k];
                //dd += src(i+k,j+k)-src(i-k,j-k);
                //du += src(i+k,j-k)-src(i-k,j+k);
            }
            dh = (int)fabs( ((float)dh/(float)win+0.5) );
            dv = (int)fabs( ((float)dv/(float)win+0.5) );
            //dd = (int)fabs( ((float)dd/(float)win+0.5) );
            //du = (int)fabs( ((float)du/(float)win+0.5) );

            val = MAX(dh,dv);
            //val = MAX(val,dd);
            //val = MAX(val,du);

            if (val>thre) val = 255;
            else val = 0;
            dst(i,j) = val;
        }
    }

    delete [] hprj;
    delete [] vprj;

    for(j=0;j<hgt;j++)
    {
        for(i=0;i<pwin;i++)  
        {
            dst(i,j)=0;
            dst(wid-i-1,j)=0;
        }
    }

    for(i=0;i<wid;i++)
    {
        for(j=0;j<pwin;j++)
        {
            dst(i,j)=0;
            dst(i,hgt-j-1)=0;
        }
    }

    return 0;
}

// 기존
int CAlgProc::fnDiffMin(U8* pImg, U8* pOut, U8* insp_map, int wid, int hgt, int pitchX, int pitchY, int sx, int sy, int ex, int ey)
{
	enum DIRECTION { HOR, VER, DIA45, DIA135, TOTAL };
	const int N = TOTAL;

	if (pitchX * 3 >= wid || pitchY * 3 >= hgt)
		return 1;

	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {

			if (insp_map[y * wid + x] == 0)
				continue;

			int lp = x - pitchX >= sx ? x - pitchX : x + pitchX * 2;
			int rp = x + pitchX < ex ? x + pitchX : x - pitchX * 2;
			int tp = y - pitchY >= sx ? y - pitchY : y + pitchY * 2;
			int bp = y + pitchY < ey ? y + pitchY : y - pitchY * 2;

			lp = insp_map[y * wid + lp] > 0 ? lp : x + pitchX * 2;
			rp = insp_map[y * wid + rp] > 0 ? rp : x - pitchX * 2;
			tp = insp_map[tp * wid + x] > 0 ? tp : y + pitchY * 2;
			bp = insp_map[bp * wid + x] > 0 ? bp : y - pitchY * 2;

			int a = (int)pImg[y * wid + x];

			int al = (int)pImg[y * wid + lp];
			int ar = (int)pImg[y * wid + rp];
			int at = (int)pImg[tp * wid + x];
			int ab = (int)pImg[bp * wid + x];
			int alt = (int)pImg[tp * wid + lp];
			int alb = (int)pImg[bp * wid + lp];
			int art = (int)pImg[tp * wid + rp];
			int arb = (int)pImg[bp * wid + rp];

			int tempArr[N];

			tempArr[HOR] = al - ar;
			tempArr[VER] = at - ab;
			tempArr[DIA45] = alb - art;
			tempArr[DIA135] = alt - arb;

			int min_val = 9999;
			int min_idx = 0;

			for (int i = 0; i < N; i++) {
				if (abs(tempArr[i]) < min_val) {
					min_val = abs(tempArr[i]);
					min_idx = i;
				}
			}

			int diff_n = 0;

			if (min_idx == HOR)
				diff_n = a * 2 - (al + ar);
			else if (min_idx == VER)
				diff_n = a * 2 - (at + ab);
			else if (min_idx == DIA45)
				diff_n = a * 2 - (alb + art);
			else if (min_idx == DIA135)
				diff_n = a * 2 - (alt + arb);




			int proc_val = 128 + diff_n;

			if (proc_val < 0)
				proc_val = 0;
			if (proc_val > 255)
				proc_val = 255;

			pOut[y * wid + x] = proc_val;
		}
	}

	return 1;
}

// 상하
int CAlgProc::fnDiffMin_VERT(U8* pImg, U8* pOut, U8* insp_map, int wid, int hgt, int pitchX, int pitchY, int sx, int sy, int ex, int ey)
{
	enum DIRECTION { HOR, VER, HOR2, VER2, TOTAL };
	const int N = TOTAL;

	if (pitchX * 3 >= wid || pitchY * 3 >= hgt)
		return 1;

	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {

			if (insp_map[y * wid + x] == 0)
				continue;

			int ttp = y - pitchY*2 >= sy ? y - pitchY*2 : y + pitchY * 3;
			int bbp = y + pitchY * 2 < ey ? y + pitchY * 2 : y - pitchY * 3;

			int tp = y - pitchY >= sy ? y - pitchY : y + pitchY * 2;
			int bp = y + pitchY < ey ? y + pitchY : y - pitchY * 2;

			ttp = insp_map[ttp * wid + x] > 0 ? ttp : y + pitchY * 3;
			bbp = insp_map[bbp * wid + x] > 0 ? bbp : y - pitchY * 3;

			tp = insp_map[tp * wid + x] > 0 ? tp : y + pitchY * 2;
			bp = insp_map[bp * wid + x] > 0 ? bp : y - pitchY * 2;

			int a = (int)pImg[y * wid + x];

			int at = (int)pImg[tp * wid + x];
			int ab = (int)pImg[bp * wid + x];
			int att = (int)pImg[ttp * wid + x];
			int abb = (int)pImg[bbp * wid + x];


			int tempArr[N];

			tempArr[VER] = at - ab;
			tempArr[VER2] = att - abb;

			int min_val = 9999;
			int min_idx = 0;

			for (int i = 0; i < N; i++) {
				if (abs(tempArr[i]) < min_val) {
					min_val = abs(tempArr[i]);
					min_idx = i;
				}
			}

			int diff_n = 0;

			if (min_idx == VER2)
				diff_n = a * 2 - (att + abb);
			else if (min_idx == VER)
				diff_n = a * 2 - (at + ab);

			int proc_val = 128 + diff_n;

			if (proc_val < 0)
				proc_val = 0;
			if (proc_val > 255)
				proc_val = 255;

			pOut[y * wid + x] = proc_val;
		}
	}

	return 1;
}

int CAlgProc::Defocus_Index(U8* im, int wid, int hgt, int offset, int nThrsholdH, int nThresholdL)
{
	int i = 0, j = 0, sumh = 0, suml = 0, tmp = 0, ph = 0, pl = 0, hith = 0, loth = 0;
	double cntl = 0, cnth = 0;
	U8* pMem;
	int ret = 0;

	hith = 128 + nThrsholdH;
	loth = 128 - nThresholdL;

	//pMem = new U8[wid*hgt];

	//전 영역에 대해서 Hi, Lo 각각의 Threshold 이상되는 영역의 적분값
	for (j = 2; j < hgt - 2; j++)
	{
		//BlkMoveIn((U32*)(im + j*offset), (U32*)pMem, wid>>2, 1, wid);
		pMem = (im + j * offset);

		for (i = 2; i < wid - 2; i++)
		{
			tmp = pMem[i];
			if (tmp < loth)
			{
				suml = suml + 128 - tmp;
				cntl++;
				tmp = 128 - tmp;
				if (tmp > pl) pl = tmp;	//pl difference max
			}
			if (tmp > hith)
			{
				sumh += (tmp - 128);
				cnth++;
				tmp = (tmp - 128);
				if (tmp > ph) ph = tmp;	//ph difference max
			}
		}
	}

	// 적분 값 * Relative Gradient
	if (cntl > 0) suml = (int)(suml*pl / (sqrt(cntl) * 128));
	else suml = 0;

	if (cnth > 0) sumh = (int)(sumh/(sqrt(cnth)*128)*ph);
	else sumh = 0;

	//jcyoon.edit, 2013.09.02

	if (sumh > suml) ret = sumh;
	else ret = suml;

	return ret;
}

void CAlgProc::GetImageInfo(CIMAGE& cimg, int thre, std::vector<IMGINFO>& vdata, int highlowFlag)
{
	IMGINFO pxl;

	if (highlowFlag == ipl::LO_HI_FLAG::HIGH)
	{
		for (int j = cimg.Top(); j < cimg.Bottom(); j++)
		{
			for (int i = cimg.Left(); i < cimg.Right(); i++)
			{
				if (cimg(i, j) > thre)
				{
					pxl.x = i;
					pxl.y = j;
					pxl.gl = cimg(i, j);
					vdata.emplace_back(pxl);
				}
			}
		}
	}
	else
	{

	}
}

float CAlgProc::Get_R_Squared_1st(_In_ std::vector<IMGINFO>& vImg, _Out_ int* dirAngle, CRECT rt, double* dAA, double* dBB)
{
	double AA1, BB1, AA2, BB2;
	CPOS pt1, pt2, pt3, pt4;

	//model1 +
	pt1 = rt.PosLT();
	pt2 = rt.PosRB();
	pt3.SetPos(rt.Left(), rt.Bottom());
	pt4.SetPos(rt.Right(), rt.Top());

	GetLineEq(pt1, pt2, &AA1, &BB1);
	GetLineEq(pt3, pt4, &AA2, &BB2);

	double S_sqare = 0;
	int sumY = 0;

	for (int i = 0; i < vImg.size(); i++)
	{
		sumY += vImg[i].y;
	}

	if (vImg.size() < 5)
		return -1;

	double avgY = (double)sumY / (double)vImg.size();

	double SSR1, SSE1, SSR2, SSE2;
	Get_SSR_SSE(vImg, &SSR1, &SSE1, avgY, AA1, BB1);
	Get_SSR_SSE(vImg, &SSR2, &SSE2, avgY, AA2, BB2);

	double R_sq1 = 1 - (SSR1 / (SSE1 + SSR1));
	double R_sq2 = 1 - (SSR2 / (SSE2 + SSR2));

	//S_sqare = (R_sq1 < R_sq2) ? R_sq1 : R_sq2;
	if (R_sq1 < R_sq2)
	{
		S_sqare = R_sq2;
		*dirAngle = -1;
		*dAA = AA2;
		*dBB = BB2;
	}
	else
	{
		S_sqare = R_sq1;
		*dirAngle = 1;
		*dAA = AA1;
		*dBB = BB1;
	}

	return (float)S_sqare;
}

float CAlgProc::GetLinetDensity(uint8_t* pImg, int thre, int threFlag, int wid, int hgt, int sx, int sy, int ex, int ey, double AA, double BB)
{
	double AA1, BB1, AA2, BB2;
	CPOS pt1, pt2, pt3, pt4;
	//model1 +
	pt1.SetPos(sx, sy);
	pt2.SetPos(ex, ey);
	pt3.SetPos(sx, ey);
	pt4.SetPos(ex, sy);

	std::vector<int> v_hori, v_vert;
	int val = 0;

	CIMAGE cimg(pImg, sx, sy, ex, ey, wid);
	float dx = (float)(ex - sx) + 1;
	float dy = (float)(ey - sy) + 1;

	int cnt1 = 0, cnt2 = 0;
	float y_i = 0, x_i = 0;
	float density = 0;
	if (dx > dy)
	{
		for (int i = sx; i <= ex; i++)
		{
			for (int j = -2; j <= 2; j++)
			{
				y_i = AA * i + BB + j;

				if (y_i < 0) continue;

				if (cimg(i, y_i) > thre)
				{
					cnt1++;
					break;
				}
			}
		}
		int maxcnt = cnt1;

		density = (float)maxcnt / (float)dx;
	}
	else
	{
		for (int i = sy; i <= ey; i++)
		{
			for (int j = -3; j <= 3; j++)
			{
				x_i = (i - BB + AA*j) / AA;

				if (x_i < 0) continue;

				if (cimg(x_i, i) > thre)
				{
					cnt1++;
					break;
				}
			}
		}
		int maxcnt = cnt1;

		density = (float)maxcnt / (float)dy;
	}

	return density;
}

int CAlgProc::GetLineEq(CPOS pt1, CPOS pt2, double* AA, double* BB)
{
	if (pt2.X() == pt1.X())	return 0;
	double A1 = (double)(pt2.Y() - pt1.Y()) / (double)(pt2.X() - pt1.X());

	double B1 = pt1.Y() - A1 * pt1.X();

	*AA = A1;
	*BB = B1;

	return 1;
}

void CAlgProc::Get_SSR_SSE(_In_ std::vector<IMGINFO>& vpos, _Out_ double* SSR_r, _Out_ double* SSE_r, double avgY, _In_ double AA, _In_ double BB)
{
	double y_i = 0;
	double SSE = 0, SSR = 0;

	for (int i = 0; i < vpos.size(); i++)
	{
		y_i = AA * vpos[i].x + BB;
		SSE = SSE + pow((y_i - avgY), 2);
		SSR = SSR + pow((vpos[i].y - y_i), 2);
	}

	//	double R_sq1 = 1 - (SSR / (SSE + SSR));
	*SSR_r = SSR;
	*SSE_r = SSE;
}

void CAlgProc::Get_SSR_SSE_2nd(_In_ std::vector<IMGINFO>& vpos, _Out_ double* SSR_r, _Out_ double* SSE_r, double avgY, _In_ float AA, _In_ float BB, float CC)
{
	float y_i = 0;
	float SSE = 0, SSR = 0;

	for (int i = 0; i < vpos.size(); i++)
	{
		y_i = CC * (vpos[i].x - AA)*(vpos[i].x - AA) + BB;
		SSE = SSE + pow((y_i - avgY), 2);
		SSR = SSR + pow((vpos[i].y - y_i), 2);
	}

	*SSR_r = SSR;
	*SSE_r = SSE;
}

void CAlgProc::Get2ndEq(CPOS pt1, CPOS pt2, CPOS pt3, float* fA, float* fB, float* fC)
{
	int a = pt1.X();
	int b = pt1.Y();
	int c = pt2.X();
	int d = pt2.Y();
	int f = pt3.X();
	int g = pt3.Y();

	*fA = (float)(g*(a*a - c * c) + d * (f*f - a * a) + b * (c*c - f * f)) / (float)(2 * ((g - d)*a + (b - g)*c + (d - b)*f));

	*fC = (float)(b - d) / (float)(a*a - c * c + 2 * (*fA)*(c - a));

	*fB = (float)(d - (*fC)*(c - (*fA))*(c - (*fA)));
}

float CAlgProc::Get_R_Squared_2nd(_In_ std::vector<IMGINFO>& vImg, _In_ int dirAngle, CRECT rt)
{
	float AA, BB, CC;
	CPOS pt1, pt2, pt3, pt;

	//model1 +
	if (dirAngle == 1)
	{
		pt1 = rt.PosLT();
		pt2 = rt.PosRB();
	}
	else
	{
		pt1.SetPos(rt.Left(), rt.Bottom());
		pt2.SetPos(rt.Right(), rt.Top());
	}

	pt3.SetPos(rt.Left(), rt.Bottom());

	CRECT rtSmall = rt;
	rtSmall.ExtendRect(-rt.Width() / 4, -rt.Height() / 4);

	int maxv = 0;
	for (int i = 0; i < vImg.size(); i++)
	{
		pt.SetPos(vImg[i].x, vImg[i].y);
		if (rtSmall.IsInside(pt))
		{
			if (maxv < vImg[i].gl) {
				maxv = vImg[i].gl;
				pt3 = pt;
			}
		}
	}

	if (maxv == 0)
		return -1;

	Get2ndEq(pt1, pt2, pt3, &AA, &BB, &CC);

	double S_sqare = 0;
	int sumY = 0;

	for (int i = 0; i < vImg.size(); i++)
	{
		sumY += vImg[i].y;
	}

	if (vImg.size() < 5)
		return -1;

	double avgY = (double)sumY / (double)vImg.size();

	double SSR, SSE;
	Get_SSR_SSE_2nd(vImg, &SSR, &SSE, avgY, AA, BB, CC);

	double R_sq = 1 - (SSR / (SSE + SSR));

	S_sqare = (R_sq < R_sq) ? R_sq : R_sq;
	return (float)S_sqare;
}

float CAlgProc::GetStdFromArr(std::vector<float>& arr, float avg)
{
	float diffsum = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		diffsum += ((arr[i] - avg)*(arr[i] - avg));
	}

	float dataNo = (float)arr.size();
	float dv = sqrt(diffsum / dataNo);

	return dv;
}

#define RadToDeg		57.29577951f

int CAlgProc::GetEdgeAngle(uint8_t* pImg, int width, int height, CRECT& rt, int *angle_result, int mag_thre, double *stdA)
{
	float fangle, magnitude;
	int angle;
	int sx, sy, ex, ey;
	int i, j, sumx, sumy;
	int cnt, thre;
	std::vector<float> anglehisto;
	anglehisto.assign(360, 0);

	sx = (rt.Left() < 0) ? 0 : rt.Left();
	sy = (rt.Top() < 0) ? 0 : rt.Top();
	ex = (rt.Right() > width - 1) ? width - 1 : rt.Right();
	ey = (rt.Bottom() > height - 1) ? height - 1 : rt.Bottom();

	cnt = 0;
	thre = 100;

	int val;

	for (i = sy + 1; i < ey - 1; i++)
	{
		for (j = sx + 1; j < ex - 1; j++)
		{
			sumx = pImg[(i - 1)*width + (j + 1)] - pImg[(i - 1)*width + (j - 1)]
				+ pImg[(i + 1)*width + (j + 1)] - pImg[(i + 1)*width + (j - 1)]
				+ (pImg[(i)*width + (j + 1)] - pImg[(i)*width + (j - 1)]) * 2;

			sumy = pImg[(i + 1)*width + (j - 1)] - pImg[(i - 1)*width + (j - 1)]
				+ pImg[(i + 1)*width + (j + 1)] - pImg[(i - 1)*width + (j + 1)]
				+ (pImg[(i + 1)*width + (j)] - pImg[(i - 1)*width + (j)]) * 2;

			fangle = (float)atan2((float)sumy, (float)sumx);
			angle = (int)(fangle*RadToDeg + 0.5f);
			magnitude = (float)(sqrt((double)(sumx*sumx + sumy * sumy)));

			val = (int)(angle) % 360;

			if (val < 0)
				val += 360;

			if (val > 180)
				val -= 180;

			if (magnitude > mag_thre)
			{
				anglehisto[val]++;
			}
		}
	}
	float mean = 0;
	int max = 0, sum = 0;
	int band;
	band = 5;
	int ct = 0;
	for (i = 0; i < 360; i++)
	{
		sum += anglehisto[i];
		if (anglehisto[i] > 0)	ct++;
	}

	if (ct == 0)	return FALSE;
	mean = (float)sum / (float)ct;
	for (i = 0; i < 360 - band; i++)
	{
		sum = 0;
		for (j = i; j < i + band; j++)
		{
			sum += anglehisto[j];
		}

		if (max < sum)
		{
			*angle_result = i;
			max = sum;
		}
	}

	double var = 0.;


	var = GetStdFromArr(anglehisto, mean);

	*angle_result = (*angle_result + 90) % 360;

	if (*angle_result > 180)
		*angle_result -= 180;

	anglehisto.clear();

	*stdA = var;
	if (var < 1.0)// 2.5)
	{
		*angle_result = -1;
		return FALSE;
	}
	return TRUE;
}

int CAlgProc::GetSumofImg(CIMAGE img)
{
	int sum = 0;
	for (int j = img.Top(); j < img.Bottom(); j++)
	{
		for (int i = img.Left(); i < img.Right(); i++)
		{
			sum += (img(i, j) - 128);
		}
	}
	return sum;
}

int CAlgProc::fnMedianFilter(CIMAGE& src, CIMAGE& dst, int dx, int dy)
{
	int sx = src.Left();
	int sy = src.Top();
	int ex = src.Right();
	int ey = src.Bottom();
//	int hgt = ey;
//	int histo[256] = { 0 };
	int** histo; 
	histo = new int*[ey];
	for (int i = 0; i < ey; i++)
	{
		histo[i] = new int[256];
		memset(histo[i], 0, sizeof(int) * 256);
	}

	//memset(histo, 0, sizeof(int) * 256);

	int hdx = dx / 2;
	int hdy = dy / 2;

	int sum = 0, sum2 = 0, hsum = 0, median = 0;
	int* beforeArr = new int[dy];
	int cnt = 0;

	sum = dx * dy;
	hsum = sum / 2;

	uint8_t* img = src.GetImgPtr();
	uint8_t* pdst = dst.GetImgPtr();
	int wid = src.Offset();

	int min = 0, max = 0;
	int yy = 0;
	int* phisto = NULL;
	for (int j = sy+hdy; j < ey-hdy; j++)
	{
		//첫번째 히스토그램
		phisto = histo[j];
		for (int l = -hdy; l < hdy + 1; l++)
		{
			yy = (j + l)*wid;
			for (int k = -hdx; k < hdx + 1; k++)
			{
				phisto[ *(img+(sx + hdx + k)+yy)]++;
			}

			beforeArr[l + hdy] = *(img+sx+yy);
		}
		min = 0;
		for (int p = 0; p < 256; p++)
		{
			if (phisto[p] > min)
			{
				min = p;
				if (min > 0)
					break;
			}
		}
		
		for (int i = sx+hdx; i < ex-hdx; i++)
		{
			//앞에꺼 빼주고
			for (int k = 0; k < dy; k++)
			{
				phisto[beforeArr[k]]--;
			}
			int xx;
			//새로운거 추가, 앞에꺼는 기록
			for (int l = -hdy; l < hdy + 1; l++)
			{
				yy = (j + l)*wid;
				beforeArr[l+hdy] = *(img+i-hdx+ yy);
				xx = *(img+i+hdx+ yy);
				phisto[xx]++;
				if (min > xx)
					min = xx;
			}

			int p = 0;
			for (p = min; p < 256; p++)
			{
				sum2 += phisto[p];
				if (sum2 > hsum)
					break;
			}
			median = p;

			*(pdst + i + j * wid) = median;
			sum2 = 0;

		}
	}

	delete[] beforeArr;
	return 1;
}
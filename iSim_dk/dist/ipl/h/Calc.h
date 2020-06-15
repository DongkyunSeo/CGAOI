/**
    @file calc.h
    @date 2016/08/24
    @author seonghoon.kim@lge.com
    @brief 산술 연산함수 선언 
*/

#ifndef _CALC_
#define _CALC_

#include "ipl_def.h"

#include <vector>
using namespace std;

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{
/** 
	@namespace ipl::calc
	@brief 이미지 정보 및 계산 관련 function 모듈
*/	
namespace calc
{

/// Vertical Projection을 계산함.
IPL_API int CalcProjection_Vert(CIMAGE& src, U32* prj_array);

/// Horizontal Projection을 계산함.
IPL_API int CalcProjection_Horz(CIMAGE& src, U32* prj_array);

/// Histogram을 계산함.
IPL_API int CalcHistogram(CIMAGE& src, U32* histo_array);

/// 누적 Histogram을 계산함.
IPL_API int CalcHistogram_Accumulated(CIMAGE& src, U32* histo_array);

/// 영역내 pixel의 평균값을 계산함.
IPL_API float CalcAverage(CIMAGE& src);

/// 영역내 pixel의 분산값을 계산함.
IPL_API float CalcVariance(CIMAGE& src);

/// 영역내 pixel의 표준편차값을 계산함.
IPL_API float CalcStdDeviation(CIMAGE& src);

/// 영역내 pixel의 개수를 계산함.
IPL_API int CountPixel_WithRange(CIMAGE& src, int range_low, int range_high, int range_flag);

/// 영역내 Min, Max 값을 계산함.
IPL_API int CalcMinMax(CIMAGE& src, int& min, int& max);

/// 영역내 첫 번째 Edge 위치를 찾음. (derivative of projection)
IPL_API int FindFirstEdge_Horz(CIMAGE& src, int& pos, int slope_thre, int edge_type, int search_dir);

/// 영역내 첫 번째 Edge 위치를 찾음. (derivative of projection)
IPL_API int FindFirstEdge_Vert(CIMAGE& src, int& pos, int slope_thre, int edge_type, int search_dir);

/// Projection으로부터 첫 번째 Edge 위치를 찾음. (averaged difference of projection)
IPL_API float FindFirstEdge_AvrDiffProj_Subpixel(U32* prj, int prj_wid, float* prj_avr, float& pos, float slope_thre, int edge_type, int edge_band_max, int search_dir);

/// Projection을 Peak 기준으로 보상 정렬함
IPL_API int CompensateProjection(U32* prj, U32* comp_prj, int prj_wid, int baseline_dir, int peak_spacing);

} // namespace calc
} // namespace ipl

#endif
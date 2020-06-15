/**
    @file morph.h
    @date 2016/08/26
    @author seonghoon.kim@lge.com
    @brief binary / morphology 관련 함수 선언 
*/

#ifndef _MORPH_
#define _MORPH_

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
	@namespace ipl::morph
	@brief binary, morphology 관련 function 모듈
*/	
namespace morph
{
/// 이미지를 이진화 함.
IPL_API int Binarize(CIMAGE& src, CIMAGE&  dest, int thre, int lo_hi_flag);

/// 이미지를 이진화 함.(Range base)
IPL_API int Binarize_WithRange(CIMAGE& src, CIMAGE& dest, int thre_lo, int thre_hi, int range_flag);

/// 이미지에 NOT 논리 연산 적용함.
IPL_API int OperateNOT(CIMAGE& src, CIMAGE&  dest);

/// 이미지에 AND 논리 연산 적용함.
IPL_API int OperateAND(CIMAGE& src1, CIMAGE& src2, CIMAGE&  dest);

/// 이미지에 OR 논리 연산 적용함.
IPL_API int OperateOR(CIMAGE& src1, CIMAGE& src2, CIMAGE&  dest);

/// 이미지에 XOR 논리 연산 적용함.
IPL_API int OperateXOR(CIMAGE& src1, CIMAGE& src2, CIMAGE&  dest);

/// erode(침식) 연산 적용함.
IPL_API int Erode(CIMAGE& src, CIMAGE&  dest);

/// 수평 방향 erode(침식) 연산 적용함.
IPL_API int Erode_Horz(CIMAGE& src, CIMAGE&  dest);

/// 수직 방향 erode(침식) 연산 적용함.
IPL_API int Erode_Vert(CIMAGE& src, CIMAGE&  dest);

/// Dilate(팽창) 연산 적용함.
IPL_API int Dilate(CIMAGE& src, CIMAGE&  dest);

/// 수평 방향 Dilate(팽창) 연산 적용함.
IPL_API int Dilate_Horz(CIMAGE& src, CIMAGE&  dest);

/// 수직 방향 Dilate(팽창) 연산 적용함.
IPL_API int Dilate_Vert(CIMAGE& src, CIMAGE&  dest);

/// Opening(제거) 연산 적용함.
IPL_API int Opening(CIMAGE& src, CIMAGE&  dest, CIMAGE&  temp);

/// Closing(채움) 연산 적용함.
IPL_API int Closing(CIMAGE& src, CIMAGE&  dest, CIMAGE&  temp);

/// Thinning(세선화) 연산 적용함.
IPL_API int Thinning(CIMAGE& src, CIMAGE&  dest);

} // namespace morph
} // namespace ipl

#endif
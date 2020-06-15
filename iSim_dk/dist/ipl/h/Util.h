/**
    @file util.h
    @date 2016/08/25
    @author seonghoon.kim@lge.com
    @brief Drawing 등 입출력/기타 관련 함수 선언 
*/

#ifndef _UTIL_
#define _UTIL_

#include <vector>

using namespace std;

#include "ipl_def.h"

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{
/// 라이센스 확인
IPL_API int ValidateIPL();

/** 
	@namespace ipl::util
	@brief 도형, text 출력 등 untility function 모듈
*/	
namespace util
{

/// 이미지에 사각형을 그림.
IPL_API int DrawRect(CIMAGE& src, CRECT rect, int color, int fill_flag);

/// 이미지에 직선을 그림.
IPL_API int DrawLine(CIMAGE& src, CPOS pt1, CPOS pt2, int color);

/// 이미지에 원을 그림.
IPL_API int DrawCircle(CIMAGE& src, CPOS center, int radius, int color, int fill_flag);

/// 이미지에 타원을 그림.
IPL_API int DrawElipse(CIMAGE& src, CRECT rect, int color, int fill_flag);

/// 이미지에 타원(부분)을 그림.
IPL_API int DrawElipseQuad(CIMAGE& src, CRECT rect, int quadrant, int color, int fill_flag);

/// 이미지에 Text를 출력함.
IPL_API int DrawTextMsg(CIMAGE& src, CPOS pos, char* szMsg, int color_ch, int color_bk);

/// 이미지에 연결된 직선들을 그림.
IPL_API int DrawPolyLine(CIMAGE& src, CPOS* pt_list, int pt_num, int color, int close_flag);

} // namespace util
} // namespace ipl

#endif
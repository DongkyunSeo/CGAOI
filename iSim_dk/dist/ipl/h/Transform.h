/**
    @file transform.h
    @date 2016/08/25
    @author seonghoon.kim@lge.com
    @brief 기하학적 영상 변환 관련 함수 선언 
*/

#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "ipl_def.h"

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{
	
/** 
	@namespace ipl::transform
	@brief 이미지의 기하학적 형상 변환 관련 function 모듈
*/		
namespace transform
{
/// 이미지를 좌우 반전함.
IPL_API int FlipImage_Horz(CIMAGE& src, CIMAGE& dest);

/// 이미지를 상하 반전함.
IPL_API int FlipImage_Vert(CIMAGE& src, CIMAGE& dest);

/// 이미지를 90도 회전함 (CCW)
IPL_API int RotateImage_90(CIMAGE& src, CIMAGE& dest);

/// 이미지를 180도 회전함 (CCW)
IPL_API int RotateImage_180(CIMAGE& src, CIMAGE& dest);

/// 이미지를 270도 회전함 (CCW)
IPL_API int RotateImage_270(CIMAGE& src, CIMAGE& dest);

/// 이미지를 복사함.
IPL_API int CopyImage(CIMAGE& src, CIMAGE& dest);

/// 이미지를 Masking 함.
IPL_API int MaskImage(CIMAGE& src, CIMAGE& mask, CIMAGE& dest,  int mask_value);

/// 두 이미지를 가로 방향으로 Stitching 함.
IPL_API int StitchImage_Horz(CIMAGE& src1, CIMAGE& src2, CIMAGE& dest);

/// 두 이미지를 세로 방향으로 Stitching 함.
IPL_API int StitchImage_Vert(CIMAGE& src1, CIMAGE& src2, CIMAGE& dest);

/// 두 이미지의 차 이미지를 구함
IPL_API int SubtractImage(CIMAGE& src1, CIMAGE& src2, CIMAGE& dest, int bias);

/// Image translate (subpixel)
IPL_API int TranslateImage_Subpixel(CIMAGE& src, CIMAGE& dest, float shift_x, float shift_y);

/// Src 이미지를 Destination 이미지 사이즈로 scaling 함 (확대 or 축소).
IPL_API int ScaleImage(CIMAGE& src, CIMAGE& dest);

/// 이미지를 degree 단위로 회전함 (CCW)
IPL_API int RotateImage(CIMAGE& src, CIMAGE& dest, CPOS rot_center, double rot_angle);

/// 임의의 사각형 이미지를 직사각형으로 변형함.
IPL_API int Retangularize(CIMAGE& src, CIMAGE& dest, CPOS LeftTop, CPOS RightTop, CPOS LeftBottom, CPOS RightBottom);

/// 이미지를 원근 보정함.
IPL_API int CorrectPerspective(CIMAGE& src, CIMAGE& dest, CPOS FarLeft, CPOS FarRight, CPOS NearLeft, CPOS NearRight);
} // namespace transform
} // namespace ipl

#endif
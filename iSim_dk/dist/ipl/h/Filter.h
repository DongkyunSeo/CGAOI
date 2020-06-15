/**
    @file filter.h
    @date 2016/08/25
    @author seonghoon.kim@lge.com
    @brief 전처리 filtering 함수 선언 
*/

#ifndef _FILTER_
#define _FILTER_

#include "ipl_def.h"

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{
/** 
	@namespace ipl::filter
	@brief 이미지 filtering 모듈. convolution 등 이미지의 밝기 특성 변환과 관련된 function 들 모음.
*/		
namespace filter
{
/// Histogram stretch 필터링함.
IPL_API int StretchHistogram(CIMAGE& src, CIMAGE& dest, int offset, float scale);

/// Histogram adjust 필터링함.(gamma)
IPL_API int AdjustHistogram(CIMAGE& src, CIMAGE& dest, int low, int high, float gamma);

/// 이미지 제곱을 연산함
IPL_API int MultiplySelf(CIMAGE& src, CIMAGE& dest, float gain);

/// average 연산
IPL_API int Average(CIMAGE& src, CIMAGE& dest, U64* buf, int avr_wid, int avr_hgt);

/// average 3x3 연산
IPL_API int Average_3x3(CIMAGE& src, CIMAGE& dest);

/// Sobel edge detector 연산
IPL_API int Sobel(CIMAGE& src, CIMAGE& dest);

/// Sobel edge detector 연산 (Horz)
IPL_API int Sobel_Horz(CIMAGE& src, CIMAGE& dest);

/// Sobel edge detector 연산 (Vert)
IPL_API int Sobel_Vert(CIMAGE& src, CIMAGE& dest);

/// Laplacian edge detector 연산 
IPL_API int Laplacian(CIMAGE& src, CIMAGE& dest);

/// Median Filter 
IPL_API int Median(CIMAGE& src, CIMAGE& dest, int win_size);

/// Gaussian Filter 
IPL_API int Gaussian(CIMAGE& src, CIMAGE& dest, U64* buf, int mask_size, double sigma);

/// Gaussian Filter 
IPL_API int LoG(CIMAGE& src, CIMAGE& dest, U64* buf, int mask_size, double sigma, double gain);

/// Convolution-2D Filter 
IPL_API int Conv2D(CIMAGE& src, CIMAGE& dest, U64* buf, int mask_size, double* kernel, double gain, int bias);

/// Canny Edge Filter 
IPL_API int Canny(CIMAGE& src, CIMAGE& dest, U64* buf, int mask_size, double sigma, int thre_lo, int thre_hi);

/// double threshold
IPL_API int Threshold_LowHigh(CIMAGE& src, CIMAGE& dest, int thre_lo, int thre_hi);

/// vertical uniformize
IPL_API int Uniformize_Vert(CIMAGE& src, CIMAGE& dest, int exclude_low, int exclude_high, int method_flag);

/// horizontal uniformize
IPL_API int Uniformize_Horz(CIMAGE& src, CIMAGE& dest, int exclude_low, int exclude_high, int method_flag);

/// Binning Enhance 
IPL_API int Enhance_Binning(CIMAGE& src, CIMAGE& dest, int bin_size, int bias_src, int bias_dest, double gain);

/// DynamicBias Enhance 
IPL_API int Enhance_DynamicBias(CIMAGE& src, CIMAGE& dest, U64* buf, int win_wid, int win_hgt, float gain);

/// 4C Enhance 
IPL_API int Enhance_4C(CIMAGE& src, CIMAGE& dest, int bias_src, int bias_dest,float gain);

/// 9C Enhance 
IPL_API int Enhance_9C(CIMAGE& src, CIMAGE& dest, int bias_src, int bias_dest, float gain);

/// Compress 2x2 
IPL_API int Compress_2x2(CIMAGE& src, CIMAGE& dest);

/// Pitch compare 8-Dir
IPL_API int ComparePitch_8Dir(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y, 
    float gain, int boundary_flag);

/// Pitch compare 4-Dir
IPL_API int ComparePitch_4Dir(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y, 
    float gain, int boundary_flag);

/// Pitch compare 4-Dir (suppress ghost)
IPL_API int ComparePitch_4Dir_NoGhost(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y, 
    float gain, int boundary_flag);

/// Pitch compare Diagonal
IPL_API int ComparePitch_Diagonal(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y,
    float gain, int boundary_flag);

/// Pitch compare Diagonal (suppress ghost)
IPL_API int ComparePitch_Diagonal_NoGhost(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y,
    float gain, int boundary_flag);

/// Pitch compare (Edge shift)
IPL_API int ComparePitch_EdgeShift(CIMAGE& src, CIMAGE& dest, int pitch_x, int pitch_y, 
    float edge_shift, int boundary_flag);


} // namespace filter
} // namespace ipl

#endif
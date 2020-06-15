/**
    @file match.h
    @date 2016/08/25
    @author seonghoon.kim@lge.com
    @brief Template matching 관련 함수 선언
	@remark 2016/10/04 ChamferMethod 추가
*/

#ifndef _MATCH_
#define _MATCH_

#include "ipl_def.h"

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{
/** 
	@namespace ipl::match
	@brief template matching function 모듈
*/	

namespace match
{

    /**
    @brief edge의 좌표값을 담는 structure. edge base matching 시 사용함.
    */
	typedef struct Edge {
        int x; ///< x of edge
        int y; ///< y of edge
	} Edge;

/// Matching score 계산함수(SSE2)
IPL_API int EvaluateMatch_SSE2(CIMAGE& src, CIMAGE& ref, float& score);

/// Matching score 계산함수(AVX2)
IPL_API int EvaluateMatch_AVX2(CIMAGE& src, CIMAGE& ref, float& score);

/// Matching Position 찾기
IPL_API float FindMatchPosition(CIMAGE& src, CIMAGE& ref, CPOS& match_pos, int SIMD_LEVEL);

/// Matching Position 찾기 (sub-pixel)
IPL_API float FindMatchPosition_Subpixel(CIMAGE& src, CIMAGE& ref, CPOSF& match_pos, int SIMD_LEVEL);



/// raw image를 distancemap image로 변환하기
IPL_API void MakeDistanceImage(CIMAGE& src, CIMAGE& ref, int edge_threshold);
/// Image로부터 1 pixel 라인의 엣지 리스트 구하기  
IPL_API int GetSingleLineEdges(CIMAGE& src, CIMAGE& dest, int edge_threshold, Edge *edge_list);
/// 주어진 edge template으로 distance map중 최적의 matching position을 찾는 함수.
IPL_API float FindMatchPosition_FromEdgeDistMap(CIMAGE& dstMap, int nedges, Edge *edge_list, int sample_every, CPOS& match_pos);

/// 주어진 template image로 source image중 최적의 matching position을 찾는 함수.
IPL_API float FindMatchPosition_EdgeBase(CIMAGE& src, CIMAGE& ref, int edge_threshold, int sample_every, CPOS& match_pos);

} // namespace match
} // namespace ipl

#endif
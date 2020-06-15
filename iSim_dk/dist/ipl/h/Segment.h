/**
    @file segment.h
    @date 2016/08/25
    @author seonghoon.kim@lge.com
    @brief segmentation(detection)  관련 함수 선언 
*/

#ifndef _SEGMENT_
#define _SEGMENT_

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
	@namespace ipl::segment
	@brief object detection (= labeling, segmentation ) 관련 function 모듈
*/	
namespace segment
{

/// 이진화 이미지로부터 object를 추출하여 list로 만듬.
IPL_API int DetectObject_8N(CIMAGE& src, OBJECT* obj_arr, int max_num, int min_area);
IPL_API int DetectObject_8N(CIMAGE& src, vector<OBJECT>& obj_arr, int max_num, int min_area);
/// 이진화 이미지로부터 object를 추출하여 list로 만듬. (size filtering 전 최대 object 수 제한 : 만약 넘으면 음수값으로 반환) 
IPL_API int DetectObject_8N_Limited(CIMAGE& src, OBJECT* obj_arr, int max_num, int temp_num, int min_area);
IPL_API int DetectObject_8N_Limited(CIMAGE& src, vector<OBJECT>& obj_arr, int max_num, int temp_num, int min_area);


#if !defined(IPLDLL_EXPORTS)

/**
@date 2016/09/20
@author 김성훈 (seonghoon@lge.com)
@brief Object array를 object vector로 변환함.
@param obj_arr : object array pointer
@param obj_list : object vector (참조)
@param obj_num : object array의 object 개수
@return 정상 처리되면 0
@remark
2016/09/20 최초 작성
*/
static int ConvertObject_ArrToVec(OBJECT* obj_arr, vector<OBJECT>& obj_list, int obj_num)
{
    obj_list.clear();

    for (int i = 0; i < obj_num; i++)
        obj_list.push_back(obj_arr[i]);

    return 0;
}

/**
@date 2016/09/06
@author 김성훈 (seonghoon@lge.com)
@brief Object list를 거리에 따라 merge함.
@param obj_list : object의 list vector
@param merge_dist : merge 할 거리 기준
@return 정상 처리되면 0
@remark
2016/09/06 최초 작성
*/
static int MergeObject(vector<OBJECT>& obj_list, int merge_dist)
{
    int i, j;

    CRECT r1, r2;
    int area1, area2;

    for (i = 0; i < obj_list.size(); i++)
    {
        r1.SetRect(obj_list[i].sx - merge_dist, obj_list[i].sy - merge_dist
            , obj_list[i].ex + merge_dist, obj_list[i].ey + merge_dist);

        for (j = 0; j < obj_list.size(); j++)
        {
            if (i == j) continue;

            r2.SetRect(obj_list[j].sx, obj_list[j].sy, obj_list[j].ex, obj_list[j].ey);
            // merge조건에 부합하면
            if (r1.IsOverlapped(r2))
            {
                //j element를 i element에 merge한다.
                obj_list[i].sy = MIN(obj_list[i].sy, obj_list[j].sy);
                obj_list[i].ey = MAX(obj_list[i].ey, obj_list[j].ey);
                obj_list[i].sx = MIN(obj_list[i].sx, obj_list[j].sx);
                obj_list[i].ex = MAX(obj_list[i].ex, obj_list[j].ex);

                area1 = obj_list[i].area;
                area2 = obj_list[j].area;
                obj_list[i].mx = (obj_list[i].mx* area1 + obj_list[j].mx* area2) / (area1 + area2);
                obj_list[i].my = (obj_list[i].my* area1 + obj_list[j].my* area2) / (area1 + area2);
                obj_list[i].area = area1 + area2;

                obj_list[i].lx = obj_list[i].ex - obj_list[i].sx + 1;
                obj_list[i].ly = obj_list[i].ey - obj_list[i].sy + 1;
                obj_list[i].cx = obj_list[i].sx + obj_list[i].lx / 2;
                obj_list[i].cy = obj_list[i].sy + obj_list[i].ly / 2;


                r1.SetRect(obj_list[i].sx - merge_dist, obj_list[i].sy - merge_dist
                    , obj_list[i].ex + merge_dist, obj_list[i].ey + merge_dist);

                obj_list.erase(obj_list.begin() + j);
                if (j < i) i--;
                j--;

            }

        }
    }

    return 0;
}

#endif // !defined(IPLDLL_EXPORTS)

} // namespace segment
} // namespace ipl

#endif // _SEGMENT_
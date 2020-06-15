/**
    @file ipl_def.h
    @date 2016/08/23
    @author seonghoon.kim@lge.com
    @brief core type 정의 
*/

#ifndef _IPL_DEF_
#define _IPL_DEF_

#if defined(IPLDLL_EXPORTS)
#define IPL_API __declspec(dllexport)
#else
//#elif defined(_MSC_VER)&&(_MSC_VER<1200)
#define IPL_API __declspec(dllimport)
//#else
//#define IPL_API
#endif

/********************************************************
CIMAGE Class 사용법


생성에 필요한 parameter는 이미지 포인터, 영역정보, 이미지 offset 이다.

이미지 포인터는 기존에 할당된 이미지 메모리의 pointer를 전달하여 사용하며, 
NULL pointer를 전달하면 영역 정보에 따라 새로 메모리를 할당한다.
할당한 메모리는 소멸자에서 해제해 주므로, 별도의 과정은 필요없다. 
ex 1)
CImageT<U8> img(pOrg_image, 100,100, 256,256, org_image_ofs); // 기존 이미지 포인터에 256x256 영역만 지정
ex 2)
CImageT<U8> img(NULL,0,0,256,256,256); // 256x256 메모리를 새로 할당하고 영역 지정함. 
이때 시작좌표는 무조건 (0,0)으로 지정됨.

영역 정보는 다음과 같이 3가지 방법으로 지정할 수 있다.
ex 3)
CImageT<U8> img(NULL, 0,0, 256,256, 256); 
CImageT<U8> img(NULL, CPOS(0,0), 256,256, 256);
CImageT<U8> img(NULL, CRECT(0,0, 256,256), 256);

이미지 offset은 영역의 폭이 아닌 전체 이미지의 폭을 의미하며, img[ x+ y*offset ]과 같이 pointing에 사용된다 .
DIB에서의 efficient width도 이미지 offset으로 볼 수 있다.

parameter 지정은 생성자를 통해도 되고, 나중에 SetData(...) 를 호출해도 된다. (재지정 가능) 
ex 4)
CImageT<U8> img;
img.SetData(NULL,0,0,256,256,256);

Data를 pointing할 때는 전달된 이미지 포인터를 이미지 원점으로 하며, 영역시작점은 이미지 원점과 독립적으로 지정한다.
다음 두 가지 경우에 지정된 영역의 이미지 데이터는 동일하며, 좌표 원점만 달라진다.
ex 5)
img(pImg, 100,100, 256,256, org_ofs);  // 이미지 원점 != 영역시작점 
img(pImg+100+100*org_ofs, 0,0, 256,256, org_ofs); // 이미지원점 == 영역시작점 

pixel 좌표 포인팅은 다음 3가지 방법을 사용할 수 있다. 
ex 6)
U8* pImg = img.GetImgPtr();
U8 value = pImg[i + j*img.Offset()]; // 이미지 시작점(좌표원점)으로부터 (i,j)인 좌표에서의 Pixel 값 

U8* pImg = img.GetRoiPtr();
U8 value = pImg[i + j*img.Offset()]; // 영역 시작점으로부터 (i,j)인 좌표에서의 Pixel 값 

ex 7)
U8* pLine = img.GetLine(j);
U8 value = pLine[i];  // 이미지 시작점(좌표원점) (i,j)인 좌표에서의 Pixel 값

U8* pLine = img.GetLine(j+img.Top());
U8 value = pLine[i+img.Left()];  // 영역시작점으로부터 (i,j)인 좌표에서의 Pixel 값

ex 8) 
U8 value = img(i,j) --> 이미지 원점으로부터 (i,j) 인 좌표에서의 Pixel 값

U8 value = img(i+img.Left(),j+img.Top())  // 영역 시작점으로부터 (i,j) 인 좌표에서의 Pixel 값

********************************************************/

/** 
	@namespace ipl
	@brief image processing library
*/
namespace ipl
{

#define FALSE   0
#define TRUE    1
#define NULL    0

#define MIN(X,Y) (X < Y ? X : Y)  
#define MAX(X,Y) (X > Y ? X : Y)  

#ifndef _TYPE_DEF_
#define _TYPE_DEF_

/**
    @var typedef unsigned char 	U8
    @brief unsigned 8-bit type 정의 
*/
typedef unsigned char 	U8; 
/**
    @var typedef unsigned short 	U16
    @brief unsigned 16-bit type 정의 
*/
typedef unsigned short 	U16;
/**
    @var typedef short 	S16
    @brief signed 16-bit type 정의 
*/
typedef short		   	S16;
/**
    @var typedef unsigned int 	U32
    @brief unsigned 32-bit type 정의 
*/
typedef unsigned int  	U32;
/**
    @var typedef int 	S32
    @brief signed 32-bit type 정의 
*/
typedef int			  	S32;

/**
@var typedef unsigned int 	U64
@brief unsigned 64-bit type 정의
*/
typedef unsigned long long  	U64;
/**
@var typedef int 	S64
@brief signed 64-bit type 정의
*/
typedef long long			  	S64;

#endif 
/**
    @date 2016/08/23
    @author 김성훈 (seonghoon@lge.com)
    @brief 좌표를 표현하는 class 
    @remark
    김일목 (ilmoek.kim@lge.com)의 코드를 base로 함.\n
    많이 사용되는 Type에 대해서는 다음과 같이 미리 정의함.
    typedef CPositionT<int>   CPOS;  integer 기반 좌표 type. 가장 많이 쓰임. \n
    typedef CPositionT<float> CPOSF; float 기반 좌표 type. subpixel 연산 등에 사용.\n
   
    2016/08/23 최초 작성 
*/

template <typename Te > 
class CPositionT
{
public:
    /// 생성자
	CPositionT() : m_x(0), m_y(0) {}
    /// 생성자 ( x좌표, y좌표 )
	CPositionT(Te x, Te y) : m_x(x), m_y(y) {}

    /// X좌표 반환
	Te X() const { return m_x; }
    /// Y좌표 반환
	Te Y() const { return m_y; }

    /// X,Y 좌표 지정
    void SetPos(Te x, Te y) { m_x = x; m_y = y; }

    /// 연산자 정의 : 상수와의 곱
	CPositionT operator* (Te a) const { return CPositionT(m_x*a, m_y*a); }
    /// 연산자 정의 : 상수 나눗셈
	CPositionT operator/ (Te a) const { return CPositionT(m_x/a, m_y/a); }
    /// 연산자 정의 : 좌표간 덧셈
	CPositionT operator+ (const CPositionT& B) const { return CPositionT(m_x+B.m_x, m_y+B.m_y); }
    /// 연산자 정의 : 좌표간 뺄셈
	CPositionT operator- (const CPositionT& B) const { return CPositionT(m_x-B.m_x, m_y-B.m_y); }
    /// 연산자 정의 : 좌표 음수(-)화
    CPositionT operator- () const { return CPositionT(-m_x, -m_y); }

private:
	Te m_x;
	Te m_y;
};

/**
    @var typedef CPositionT<int>   CPOS 
    @brief integer 기반 좌표 type. 가장 많이 쓰임.
*/
typedef CPositionT<int>   CPOS; 
/**
    @var typedef CPositionT<float>   CPOSF 
    @brief float 기반 좌표 type. subpixel 연산 등에 사용.
*/
typedef CPositionT<float> CPOSF;

/**
    @date 2016/08/23
    @author 김성훈 (seonghoon@lge.com)
    @brief rectangle(직사각형 영역)을 표현하는 class 
    @remark
    김일목(ilmoek.kim@lge.com)의 코드를 base로 함.\n
    \n
    2016/08/23 최초 작성 
*/    
class CRECT
{
public:
    /// 생성자
	CRECT() : m_left(0), m_top(0), m_right(0), m_bottom(0) {}
    /// 생성자 : 좌(x), 상(y), 우(x), 하(y) 값으로부터 영역 생성 
	CRECT(int l, int t, int r, int b) : m_left(l), m_top(t),  m_right(r), m_bottom(b) {}
    /// 생성자 : CPOS type의 좌상단, 우하단 좌표로부터 영역 생성
	CRECT(CPOS lt, CPOS rb) : m_left(lt.X()), m_top(lt.Y()), m_right(rb.X()), m_bottom(rb.Y()) {}

    /// 좌(x), 상(y), 우(x), 하(y) 값 설정
	void SetRect(int l, int t, int r, int b) {m_left = l; m_top = t; m_right = r; m_bottom = b; }
	/// CPOS type의 좌상단, 우하단 좌표 설정
    void SetRectPt(CPOS lt, CPOS rb) {m_left = lt.X(); m_top = lt.Y(); m_right = rb.X(); m_bottom = rb.Y(); }

    /// 영역의 가로 크기를 반환
	int Width() const { return m_right-m_left+1; }
	/// 영역의 세로 크기를 반환
    int Height() const { return m_bottom-m_top+1; }
    /// x축 시작 값을 반환
	int Left() const { return m_left; }
    /// y축 시작 값을 반환
	int Top() const { return m_top; }
    /// X축 끝 값을 반환
	int Right() const { return m_right; }
    /// Y축 끝 값을 반환
	int Bottom() const { return m_bottom; }

    /// 영역의 면적값을 반환
	int Area() const { return Width() * Height(); }
    /// 영역의 중심좌표를 반환
	CPOS PosCenter() const { return CPOS((m_left+m_right)/2, (m_top+m_bottom)/2); }
    /// 좌상단 좌표를 반환
	CPOS PosLT() const { return CPOS(m_left, m_top); }
    /// 우하단 좌표를 반환
	CPOS PosRB() const { return CPOS(m_right, m_bottom); }
	
    /// 연산자 정의 : 두 CRECT 간 겹치는 영역이 있으면 확인
	bool operator&(const CRECT& roi) const { return IsOverlapped(roi); }
    /// 연산자 정의 : 두 CRECT 가 동일한 영역인지 확인
	bool operator==(const CRECT& roi) 
        { return m_left==roi.m_left && m_top==roi.m_top && m_right==roi.m_right && m_bottom==roi.m_bottom; }
    /// 연산자 정의 : 두 CRECT 가 동일한 영역이 아닌지 확인
	bool operator!=(const CRECT& roi) { return !(*this==roi); }

    /// 주어진 좌표가 영역 내부에 있으면 TRUE
	bool IsInside(const CPOS& pos) 
        { return ((pos.X()>=m_left) && (pos.Y()>=m_top) && (pos.X()<=m_right) && (pos.Y()<=m_bottom)); }
    /// 주어진 CRECT와 겹치는 영역이 있는지 확인. 연산자 "&"와 동일
	bool IsOverlapped(const CRECT& roi) 
        const { return (m_left <= roi.m_right && m_right >= roi.m_left && m_top <= roi.m_bottom && m_bottom >= roi.m_top); }

    /// 영역을 X축, Y축으로 각각 확장함
	void ExtendRect(int x, int y) { m_left-=x; m_top-=y; m_right+=x; m_bottom+=y; }
    /// 영역을 X축, Y축 방향으로 주어진 값만큼 이동함
	void Translate(int dx, int dy) { m_left+=dx; m_top+=dy; m_right+=dx; m_bottom+=dy; }
    /// 주어진 영역과의 교집합 영역을 반환함
	CRECT Intersect(const CRECT& roi) 
        const { return CRECT(MAX(m_left, roi.m_left), MAX(m_top, roi.m_top), MIN(m_right, roi.m_right), MIN(m_bottom, roi.m_bottom)); }

private:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;

};

/**
    @date 2016/09/28
    @author 김성훈 (seonghoon@lge.com)
    @brief 이미지 포인터와 영역을 표현하는 class
    @remark
    김일목(ilmoek.kim@lge.com)의 코드를 base로 하여 간략화함.\n

    가장 많이 사용하는 CImageT<U8>은 CIMAGE type으로 미리 정의함.\n
    알고리즘은 현재 버젼에서 CIMAGE type에 대해서만 동작하며, 이 외의 type에 대해서는 별도 구현 필요함.
    \n
    2016/08/24 최초 작성 \n
    2016/09/28 CopyDataFromDib()/CopyDataToDib()에 예외처리 추가\n
    2018/05/08 CopyDataToDib24() 함수 추가\n
*/     
template <typename Te>
class CImageT
{
public:
    /// 생성자
    CImageT()
    {
        m_pImg = NULL; m_bAlloc=FALSE;
        m_sx = 0; m_sy=0; m_wid = 0; m_hgt = 0; m_ofs = 0;
    }
    /**
    @brief 생성자
    @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
    @param sx : 영역 시작점 x좌표.
    @param sy : 영역 시작점 y좌표.
    @param wid : 영역의 가로 크기.
    @param hgt : 영역의 세로 크기.
    @param ofs : 이미지의 가로 크기.
    @code
    CImageT<U8> img(pOrg, 100,100, 256,256, 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
    @endcode
    @code
    CImageT<U8> img(NULL, 0,0, 256,256, 256); // 256x256 이미지 메모리를 새로 생성함.
    @endcode
    */
    CImageT(Te* pMem, int sx, int sy, int wid, int hgt, int ofs)
    {
        m_pImg = pMem; m_bAlloc = FALSE;
        m_sx = sx; m_sy = sy; m_wid = wid; m_hgt = hgt; m_ofs = ofs;
        if (pMem == NULL) GetMem();
    }
    /**
    @brief 생성자
    @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
    @param pos : 영역 시작점 좌표 pos(x,y).
    @param wid : 영역의 가로 크기.
    @param hgt : 영역의 세로 크기.
    @param ofs : 이미지의 가로 크기.
    @code
    CImageT<U8> img(pOrg, CPOS(100,100), 256,256, 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
    @endcode
    @code
    CImageT<U8> img(NULL, CPOS(0,0), 256,256, 256); // 256x256 이미지 메모리를 새로 생성함.
    @endcode
    */
    CImageT(Te* pMem, CPOS pos, int wid, int hgt, int ofs)
    {
        m_pImg = pMem; m_bAlloc = FALSE;
        m_sx = pos.X(); m_sy = pos.Y(); m_wid = wid; m_hgt = hgt; m_ofs = ofs;
        if (pMem == NULL) GetMem();
    }
    /**
    @brief 생성자
    @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
    @param r : 영역 시작점 좌표 r(l,t,r,b).
    @param ofs : 이미지의 가로 크기.
    @code
    CImageT<U8> img(pOrg, CRECT(100,100,356,356), 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
    @endcode
    @code
    CImageT<U8> img(NULL, CRECT(0,0,256,256), 256); // 256x256 이미지 메모리를 새로 생성함.
    @endcode
    */
    CImageT(Te* pMem, CRECT r, int ofs)
    {
        m_pImg = pMem;  m_bAlloc = FALSE;
        m_sx = r.Left(); m_sy = r.Top(); m_wid = r.Width(); m_hgt = r.Height(); m_ofs = ofs;
        if (pMem == NULL) GetMem();
    }
    /// 소멸자
    virtual ~CImageT()
    { 
        FreeMem(); 
    }
    /**
        @brief 데이터를 설정한다. 
        @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
        @param sx : 영역 시작점 x좌표. 
        @param sy : 영역 시작점 y좌표. 
        @param wid : 영역의 가로 크기.
        @param hgt : 영역의 세로 크기.
        @param ofs : 이미지의 가로 크기.
        @code 
        img.SetData(pOrg, 100,100, 256,256, 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
        @endcode
        @code 
        img.SetData(NULL, 0,0, 256,256, 256); // 256x256 이미지 메모리를 새로 생성함.
        @endcode
    */
    void SetData(Te* pMem, int sx, int sy, int wid, int hgt, int ofs)
    {
        FreeMem();

        m_sx = sx; m_sy=sy; m_wid = wid; m_hgt = hgt; m_ofs = ofs;
        m_pImg = pMem; m_bAlloc=FALSE;
        if (pMem==NULL) GetMem();
    }
    /**
        @brief 데이터를 설정한다.
        @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
        @param pos : 영역 시작점 좌표 pos(x,y). 
        @param wid : 영역의 가로 크기.
        @param hgt : 영역의 세로 크기.
        @param ofs : 이미지의 가로 크기.
        @code
        img.SetData(pOrg, CPOS(100,100), 256,256, 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
        @endcode
        @code 
        img.SetData(NULL, CPOS(0,0), 256,256, 256); // 256x256 이미지 메모리를 새로 생성함.
        @endcode
    */
    void SetData(Te* pMem, CPOS pos, int wid, int hgt, int ofs)
    {
        FreeMem();
        m_pImg = pMem; m_bAlloc=FALSE;
        m_sx = pos.X(); m_sy=pos.Y(); m_wid = wid; m_hgt = hgt; m_ofs = ofs;
        if (pMem==NULL) GetMem();
    } 
    /**
        @brief 데이터를 설정한다.
        @param pMem : image 포인터, NULL로 지정하면 메모리를 새로 할당함.
        @param r : 영역 시작점 좌표 r(l,t,r,b). 
        @param ofs : 이미지의 가로 크기.
        @code 
        img.SetData(pOrg, CRECT(100,100,356,356), 8192); // 가로폭이 8192인 이미지 pOrg의 (100,100)위치에 256x256 영역을 설정함.
        @endcode
        @code 
        img.SetData(NULL, CRECT(0,0,256,256), 256); // 256x256 이미지 메모리를 새로 생성함.
        @endcode
    */
    void SetData(Te* pMem, CRECT r, int ofs)
    {
        FreeMem();
        m_pImg = pMem;  m_bAlloc=FALSE;
        m_sx = r.Left(); m_sy=r.Top(); m_wid = r.Width(); m_hgt = r.Height(); m_ofs = ofs;
        if (pMem==NULL) GetMem();
    }

    /// 이미지 정상 여부를 확인. 
    bool IsValid () 
    {   if ( m_pImg==NULL ||  Area()==0 ) return 0;         else return 1; }
    
    /// 영역의 가로크기를 반환
    int Width() {return m_wid;}
    /// 영역의 세로크기를 반환
    int Height() {return m_hgt;}
    /// 이미지의 offset(가로폭)을 반환
    int Offset() {return m_ofs;}
    /// 영역의 x축 시작 값을 반환
	int Left() const { return m_sx; }
    /// 영역의 y축 시작 값을 반환
	int Top() const { return m_sy; }
    /// 영역의 x축 끝 값을 반환
	int Right() const { return m_sx+m_wid-1; }
    /// 영역의 y축 끝 값을 반환
	int Bottom() const { return m_sy+m_hgt-1; }

    /// 영역의 면적을 반환
	int Area() const { return m_wid * m_hgt; }
    /// 영역의 중심 좌표를 반환
	CPOS PosCenter() const { return CPOS(m_sx+m_wid/2, m_sy+m_hgt/2); }
    /// 영역의 좌상단 좌표를 반환
	CPOS PosLT() const { return CPOS(m_sx, m_sy); }
    /// 영역의 우하단 좌표를 반환
	CPOS PosRB() const { return CPOS(m_sx+m_wid-1, m_sy+m_hgt-1); }
    /// 영역 정보를 CRECT 형식으로 반환
    CRECT Rect() const { return CRECT(m_sx,m_sy,m_sx+m_wid-1, m_sy+m_hgt-1);}

    /// 이미지 원점의 포인터를 반환
    Te* GetImgPtr() {return m_pImg;}
    /// 영역시작점의 포인터를 반환
    Te* GetRoiPtr() {return m_pImg+m_sx + m_sy*m_ofs;}
    ///이미지 원점기준 y번째 line의 포인터를 반환
    Te* GetLine(int y) {return m_pImg + y*m_ofs;}

    /// 이미지 원점기준 (x,y) pixel의 값을 반환/설정
    Te& operator() (int x, int y) {return m_pImg [x + y * m_ofs];} 


    /// 1 pixel data가 몇 byte인지 반환
    int GetTypeSize() {return sizeof(T);}
 


    /**
    @brief DIB의 선택 영역 내의 raw data를 Image 영역내로 Flip Copy해 옴.
    @param pSrc : Header를 제외한 DIB의 raw data.
    @param src_sx : DIB내 선택 영역 시작점 x좌표.
    @param src_sy : DIB내 선택 영역 시작점 y좌표.
    @param src_hgt : DIB 이미지 세로 크기. (영역의 세로 크기가 아님에 주의)
    @param src_ofs : DIB 이미지의 Effective Width
    */
    void CopyDataFromDib(U8* pSrc, int src_sx, int src_sy, int src_hgt, int src_ofs)
    {
        if (src_hgt - src_sy < Height()) throw ("CopyDataFromDib : DIB Height is too small");
        if (src_ofs - src_sx < Width()) throw ("CopyDataFromDib : DIB Offset is too small");

        U8 *pSrc_line, *pDest_line;
        int nSize = Offset();//Width();
        for (int j = 0; j<Height(); j++)
        {
            pDest_line = GetLine(j + m_sy) + m_sx;
            pSrc_line = pSrc + src_sx + (src_hgt - src_sy - j - 1) * src_ofs;
            memcpy_s(pDest_line, nSize, pSrc_line, nSize);
        }
    }
    /**
    @brief 영역내의 이미지 data를 DIB의 raw data 선택 영역으로 Flip Copy함.
    @param pDest : Header를 제외한 DIB의 raw data.
    @param dest_sx : DIB내 선택 영역 시작점 x좌표.
    @param dest_sy : DIB내 선택 영역 시작점 y좌표.
    @param dest_hgt : DIB 이미지 세로 크기. (영역의 세로 크기가 아님에 주의)
    @param dest_ofs : DIB 이미지의 Effective Width
    */
    void CopyDataToDib(U8* pDest, int dest_sx, int dest_sy, int dest_hgt, int dest_ofs)
    {
        if (dest_hgt - dest_sy < Height()) throw ("CopyDataToDib : DIB Height is too small");
        if (dest_ofs - dest_sx < Width()) throw ("CopyDataToDib : DIB Offset is too small");

        U8 *pSrc_line, *pDest_line;
        int nSize = Width();
        for (int j = 0; j<Height(); j++)
        {
            pSrc_line = GetLine(j + m_sy) + m_sx;
            pDest_line = pDest + dest_sx + (dest_hgt - dest_sy - j - 1) * dest_ofs;
            memcpy_s(pDest_line, nSize, pSrc_line, nSize);
        }
    }


    /**
    @brief 영역내의 이미지 data (8Bit)를 24bit DIB의 raw data 선택 영역으로 Flip Copy함.
    @param pDest : Header를 제외한 DIB의 raw data.
    @param dest_sx : DIB내 선택 영역 시작점 x좌표.
    @param dest_sy : DIB내 선택 영역 시작점 y좌표.
    @param dest_hgt : DIB 이미지 세로 크기. (영역의 세로 크기가 아님에 주의)
    @param dest_ofs : DIB 이미지의 Effective Width
    */
    void CopyDataToDib24(U8* pDest, int dest_sx, int dest_sy, int dest_hgt, int dest_ofs)
    {
        if (dest_hgt - dest_sy < Height()) throw ("CopyDataToDib24 : DIB Height is too small");
        if (dest_ofs - dest_sx < Width()) throw ("CopyDataToDib24 : DIB Offset is too small");

        U8 *pSrc_line, *pDest_line;
        int nSize = Width();
        for (int j = 0; j<Height(); j++)
        {
            pSrc_line = GetLine(j + m_sy) + m_sx;
            pDest_line = pDest + dest_sx*3 + (dest_hgt - dest_sy - j - 1) * dest_ofs;
            for (int i = 0; i < nSize; i++)
            {
                pDest_line[i * 3] = pSrc_line[i];
                pDest_line[i * 3 + 1] = pSrc_line[i];
                pDest_line[i * 3 + 2] = pSrc_line[i];
            }
            
        }
   }

	void CopyDataToDib241(U8* pDest, int dest_sx, int dest_sy, int dest_hgt, int dest_ofs)
	{
		if (dest_hgt - dest_sy < Height()) throw ("CopyDataToDib24 : DIB Height is too small");
		if (dest_ofs - dest_sx < Width()) throw ("CopyDataToDib24 : DIB Offset is too small");

		U8 *pSrc_line, *pDest_line;
		int nSize = Width();
		for (int j = 0; j<Height(); j++)
		{
			pSrc_line = GetLine(j + m_sy) + m_sx;
			pDest_line = pDest + dest_sx*3 + (dest_hgt - dest_sy - j - 1) * dest_ofs;
			for (int i = 0; i < nSize; i++)
			{
				pDest_line[i * 3] = pSrc_line[i*3];
				pDest_line[i * 3 + 1] = pSrc_line[i*3+1];
				pDest_line[i * 3 + 2] = pSrc_line[i*3+2];
			}

		}
	}
   
private:
    Te* m_pImg;
    int m_sx;
    int m_sy;
    int m_wid;
    int m_hgt;
    int m_ofs;
    bool m_bAlloc;

    void GetMem()
    {
        m_pImg = new Te[m_wid*m_hgt * sizeof(Te)];
        m_bAlloc = TRUE;
        m_sx = 0; m_sy = 0; m_ofs = m_wid;
    }

    void FreeMem()
    {
        if (m_bAlloc) delete[] m_pImg;
    }


};

/**
    @var typedef typedef CImageT<U8> CIMAGE
    @brief unsigned 8-bit data 기반 Image class 정의
*/
typedef CImageT<U8> CIMAGE;

/// 두개의 threshold 적용시 범위의 안쪽인지 바깥쪽인지 정해줌
enum RANGE_FLAG
{
    IN_RANGE = 0, ///<이진화 등에서 low와 high 의 Range 내를 대상으로 함. 
    OUT_RANGE = 1 ///< 이진화 등에서 low와 high 의 Range 밖을 대상으로 함.
};

/// 이진화 시에 threshold 보다 작은쪽/큰쪽을 255로 할지 정해줌 
enum LO_HI_FLAG
{
    LOW = 0,  ///<이진화 시 threshold 보다 큰 값을 대상으로 함.
    HIGH = 1 ///< 이진화 시 threshold 보다 작은 값을 대상으로 함.
};

/// 도형 내부를 채울지 말지 정해줌
enum FILL_FLAG
{
    UNFILL = 0, ///< 도형 내부를 채우지 않음. 
    FILL = 1    ///< 도형 내부를 채움.
};

/// Uniformize 시에 보정 방식을 정해줌
enum UNIFORM_FLAG
{
    BIAS = 0,  ///< Uniformize 시 기준 선을 중심으로 +,- 보정함.
    SCALE = 1  ///< Uinformize 시 기준 선을 중심으로 *,/ 보정함.
};

/// Pitch compare 시에 외곽부 처리 방법 지정
enum PITCH_BOUNDARY_FLAG
{
    NONE = 0,   ///< pitch 비교시 Boundary 처리 하지 않음.
    FILL_CONST = 1,  ///< pitch 비교시 Boundary는 상수(=128) 로 채움.
    APPROX = 2 ///< pitch 비교시 Boundary는 근사위치의 값으로 계산함.
};

/// poly line closing 여부를 지정
enum POLYLINE_CLOSE_FLAG
{
    OPEN = 0, ///< Poly line 그릴때 폐곡선으로 만들지 않음.
    CLOSE = 1 ///< Poly line 그릴때 처음과 끝점을 이어 폐곡선으로 만듬.
};

/// SIMD 최적화 함수 level을 지정. VS2015로 컴파일된 경우에는 AVX2가 작동한다.
enum SIMD_LEVEL_FLAG
{
    SSE2 = 0, ///< SIMD 최적화 SSE2
    AVX2 = 1  ///< SIMD 최적화 AVX2
};

/// Edge find 시에 탐색 방향 지정
enum SEARCH_DIR_FLAG
{
    FORWARD = 0, ///< LEFT to RIGHT / TOP to BOTTOM
    BACKWARD = 1 ///< RIGHT to LEFT / BOTTOM to TOP
};

/// edge find시에 탐색할 edge의 종류를 지정
enum RISE_FALL_FLAG
{
    RISE = 0, ///< RISING EDGE
    FALL = 1, ///< FALLING EDGE
    BOTH = 2 ///< RISING or FALLING EDGE
};

/**
@brief object의 기본 feature값을 담는 structure. segmentation 시 사용함.
*/
struct OBJECT
{
    int cx; ///< center x
    int cy; ///< center y
    int mx; ///< center of mass x
    int my; ///< center of mass y
    int sx; ///< left
    int sy; ///< top
    int ex; ///< right
    int ey; ///< bottom
    int lx; ///< lx = ex - sx + 1
    int ly; ///< ly = ey - sy + 1
    int area; ///< area
};


} // namespace ipl
#endif
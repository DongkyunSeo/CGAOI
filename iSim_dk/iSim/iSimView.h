
// iSimView.h : CiSimView 클래스의 인터페이스
//

#pragma once

#include "Tracker.h"
#include "PrjDraw.h"


// CxImage dll link
#ifdef _WIN64
    #if defined (_UNICODE)
        #pragma comment(lib, "../dist/cx/lib/cximage64u.lib")
    #else
        #pragma comment(lib, "../dist/cx/lib/cximage64.lib")
    #endif
#else
    #if defined (_UNICODE)
        #pragma comment(lib, "../dist/cx/lib/cximage32u.lib")
    #else
        #pragma comment(lib, "../dist/cx/lib/cximage32.lib")
    #endif
#endif

// ipl dll link
#ifdef _WIN64
    #pragma comment(lib,"../dist/ipl/lib/ipl64.lib")
#else // WIN32
    #pragma comment(lib,"../dist/ipl/lib/ipl32.lib")
#endif


#include "../dist/cx/h/ximage.h" 
#include "../dist/ipl/h/ipl.h"  
#include "AlgProc.h"

using namespace ipl;



class CiSimView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
  CiSimView();
  DECLARE_DYNCREATE(CiSimView)

// 특성입니다.
public:
  CxImage m_Image;
  CString m_OpenedFile;
  int m_ImgWid;
  int m_ImgHgt;
  CTracker m_Tracker;
  CPrjDraw  m_Proj;
  int m_PrjType;

// 작업입니다.
public:
  CiSimDoc* GetDocument() const;
  int FileSave(TCHAR* PathName);
  int FileOpen(TCHAR* PathName);
  int UpdateImageInfo(void);

  int m_mergeParam[12];

// 재정의입니다.
public:
  virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
  virtual ~CiSimView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
  DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnFileOpen();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg void OnEditUndo();
    afx_msg void OnProc1Histogram();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnProc1Grayscale();
    afx_msg void OnFileSave();
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg void OnPrjCheck(UINT nID);
    void ResetProjection(void);
    void DrawProjection(CDC* pDC);
    afx_msg void OnProcessingTest();
    afx_msg void OnTransformFliphorz();
    afx_msg void OnTransformFlipvert();
    afx_msg void OnTransformCopyimage();
    afx_msg void OnTransformMaskimage();
    afx_msg void OnTransformStitchimage();
    afx_msg void OnImageHistogramAcc();
    afx_msg void OnMorphBinarize();
    afx_msg void OnMorphBinarizeRange();
    afx_msg void OnUtilDrawdemo();
	afx_msg void OnImageStat();
    afx_msg void OnMorphLogicalOp();

    afx_msg void OnMorphMorphologydemo();
    afx_msg void OnFilterAverage();
    afx_msg void OnMorphErode32831();
    afx_msg void OnMorphErodehorz();
    afx_msg void OnMorphErodevert();
    afx_msg void OnMorphDilate();
    afx_msg void OnMorphDilatehorz();
    afx_msg void OnMorphDilatevert();
    afx_msg void OnMorphOpening();
    afx_msg void OnMorphClosing();
    afx_msg void OnFilterSobel();
    afx_msg void OnFilterSobelhorz();
    afx_msg void OnFilterSobelvert();
    afx_msg void OnFilterLaplacian();
    afx_msg void OnFilterMedian();
    afx_msg void OnFilterGaussian();
    afx_msg void OnFilterLog();
    afx_msg void OnFilterMultiplyself();
    afx_msg void OnFilterCanny();
    afx_msg void OnFilterThresholdlo();
    afx_msg void OnFilterUniformizevert();
    afx_msg void OnFilterUniformizehorz();
    afx_msg void OnFilterEnhancebinning();
    afx_msg void OnFilterDynamicbias();
    afx_msg void OnFilterEnhance4c();
    afx_msg void OnFilterEnhance9c();
    afx_msg void OnFilterAverage3x3();
    afx_msg void OnFilterCompress2x2();
    afx_msg void OnTransformRotate90();
    afx_msg void OnTransformRotate180();
    afx_msg void OnTransformRotate270();
    afx_msg void OnFilterComparepitch8dir();
    afx_msg void OnFilterComparepitch4dir();
    afx_msg void OnFilterComparepitch4dir_noghost();
    afx_msg void OnFilterComparepitchdiagonal();
    afx_msg void OnFilterComparePitch_Diagonal_NoGhost();
    afx_msg void OnFilterComparePitch_EdgeShift();
    afx_msg void OnSegmentDetectObject();
    afx_msg void OnMatchingFindpos();
    afx_msg void OnMatchingFindposSub();
    afx_msg void OnCalcFindfirstedge();
    afx_msg void OnMatchingEdgematch();
    afx_msg void OnSaveProj();
    afx_msg void OnCalcFindfirstedgeAvrdiff();
    afx_msg void OnTransformScaleimagedemo();
    afx_msg void OnTransformRotateimage();
    afx_msg void OnTransformRectangularizedemo();
    afx_msg void OnTransformCorrectperspective();
    afx_msg void OnMorphThinning();
    afx_msg void OnChanelR();
    afx_msg void OnChanelG();
    afx_msg void OnChanelB();
    afx_msg void OnUtilSuperimpose();
    afx_msg void OnAlgotestPrjcompensation();
    afx_msg void OnAlgotestElamon();
    afx_msg void OnMatchingMatch();
    afx_msg void OnAlgotestPrint();
	afx_msg void OnMakepdMakepddefect();
	afx_msg void OnMakepdMakecalpattern();
	afx_msg void OnMakepdMakecalpattern32898();
	afx_msg void OnCosmetictestMergeimage();
	afx_msg void OnCosmetictestPitchcomparemin();
	afx_msg void OnFeatureinfoDefocusindex();
	afx_msg void OnFeatureinfoGetallfeature();
	afx_msg void OnFeatureinfoDetection();
	afx_msg void OnCosmetictestNormalize();
};

#ifndef _DEBUG  // iSimView.cpp의 디버그 버전
inline CiSimDoc* CiSimView::GetDocument() const
   { return reinterpret_cast<CiSimDoc*>(m_pDocument); }
#endif


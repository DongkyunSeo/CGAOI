
// iSimView.cpp : CiSimView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "iSim.h"
#endif

#include "iSimDoc.h"
#include "iSimView.h"
#include "MainFrm.h"
#include "DlgHisto.h"
#include "DlgParam.h"
#include "StopWatch.h"
#include "SSEImageProcessing.h"
#include "MuraMon.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CiSimView

IMPLEMENT_DYNCREATE(CiSimView, CScrollView)

BEGIN_MESSAGE_MAP(CiSimView, CScrollView)
  // 표준 인쇄 명령입니다.
    ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
    ON_COMMAND(ID_FILE_OPEN, &CiSimView::OnFileOpen)
    ON_WM_MOUSEMOVE()
    ON_WM_DROPFILES()
    ON_WM_DESTROY()
    ON_COMMAND(ID_EDIT_UNDO, &CiSimView::OnEditUndo)
    ON_COMMAND(ID_PROC1_HISTOGRAM, &CiSimView::OnProc1Histogram)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_COMMAND(ID_PROC1_GRAYSCALE, &CiSimView::OnProc1Grayscale)
    ON_COMMAND(ID_FILE_SAVE, &CiSimView::OnFileSave)
    ON_WM_CONTEXTMENU()
    ON_COMMAND_RANGE(ID_PRJ_NONE,ID_PRJ_V, &CiSimView::OnPrjCheck)

    ON_COMMAND(ID_PROCESSING_TEST, &CiSimView::OnProcessingTest)
    ON_COMMAND(ID_TRANSFORM_FLIPHORZ, &CiSimView::OnTransformFliphorz)
    ON_COMMAND(ID_TRANSFORM_FLIPVERT, &CiSimView::OnTransformFlipvert)
    ON_COMMAND(ID_TRANSFORM_COPYIMAGE, &CiSimView::OnTransformCopyimage)
    ON_COMMAND(ID_TRANSFORM_MASKIMAGE, &CiSimView::OnTransformMaskimage)
    ON_COMMAND(ID_TRANSFORM_STITCHIMAGE, &CiSimView::OnTransformStitchimage)
    ON_COMMAND(ID_IMAGE_HISTOGRAM, &CiSimView::OnImageHistogramAcc)
    ON_COMMAND(ID_MORPH_BINARIZE, &CiSimView::OnMorphBinarize)
    ON_COMMAND(ID_MORPH_BINARIZE32823, &CiSimView::OnMorphBinarizeRange)
    ON_COMMAND(ID_UTIL_DRAWDEMO, &CiSimView::OnUtilDrawdemo)
    ON_COMMAND(ID_IMAGE_STAT, &CiSimView::OnImageStat)
    ON_COMMAND(ID_MORPH_LOGICALOP, &CiSimView::OnMorphLogicalOp)

    ON_COMMAND(ID_MORPH_MORPHOLOGYDEMO, &CiSimView::OnMorphMorphologydemo)
    ON_COMMAND(ID_FILTER_AVERAGE, &CiSimView::OnFilterAverage)
    ON_COMMAND(ID_MORPH_ERODE32831, &CiSimView::OnMorphErode32831)
    ON_COMMAND(ID_MORPH_ERODEHORZ, &CiSimView::OnMorphErodehorz)
    ON_COMMAND(ID_MORPH_ERODEVERT, &CiSimView::OnMorphErodevert)
    ON_COMMAND(ID_MORPH_DILATE32834, &CiSimView::OnMorphDilate)
    ON_COMMAND(ID_MORPH_DILATEHORZ, &CiSimView::OnMorphDilatehorz)
    ON_COMMAND(ID_MORPH_DILATEVERT, &CiSimView::OnMorphDilatevert)
    ON_COMMAND(ID_MORPH_OPENING, &CiSimView::OnMorphOpening)
    ON_COMMAND(ID_MORPH_CLOSING, &CiSimView::OnMorphClosing)
    ON_COMMAND(ID_FILTER_SOBEL, &CiSimView::OnFilterSobel)
    ON_COMMAND(ID_FILTER_SOBELHORZ, &CiSimView::OnFilterSobelhorz)
    ON_COMMAND(ID_FILTER_SOBELVERT, &CiSimView::OnFilterSobelvert)
    ON_COMMAND(ID_FILTER_LAPLACIAN, &CiSimView::OnFilterLaplacian)
    ON_COMMAND(ID_FILTER_MEDIAN, &CiSimView::OnFilterMedian)
    ON_COMMAND(ID_FILTER_GAUSSIAN, &CiSimView::OnFilterGaussian)
    ON_COMMAND(ID_FILTER_LOG, &CiSimView::OnFilterLog)
    ON_COMMAND(ID_FILTER_MULTIPLYSELF, &CiSimView::OnFilterMultiplyself)
    ON_COMMAND(ID_FILTER_CANNY, &CiSimView::OnFilterCanny)
    ON_COMMAND(ID_FILTER_THRESHOLDLO, &CiSimView::OnFilterThresholdlo)
    ON_COMMAND(ID_FILTER_UNIFORMIZEVERT, &CiSimView::OnFilterUniformizevert)
    ON_COMMAND(ID_FILTER_UNIFORMIZEHORZ, &CiSimView::OnFilterUniformizehorz)
    ON_COMMAND(ID_FILTER_ENHANCEBINNING, &CiSimView::OnFilterEnhancebinning)
    ON_COMMAND(ID_FILTER_DYNAMICBIAS, &CiSimView::OnFilterDynamicbias)
    ON_COMMAND(ID_FILTER_ENHANCE4C, &CiSimView::OnFilterEnhance4c)
    ON_COMMAND(ID_FILTER_ENHANCE9C, &CiSimView::OnFilterEnhance9c)
    ON_COMMAND(ID_FILTER_AVERAGE3X3, &CiSimView::OnFilterAverage3x3)
    ON_COMMAND(ID_FILTER_COMPRESS2X2, &CiSimView::OnFilterCompress2x2)
    ON_COMMAND(ID_TRANSFORM_ROTATE90, &CiSimView::OnTransformRotate90)
    ON_COMMAND(ID_TRANSFORM_ROTATE180, &CiSimView::OnTransformRotate180)
    ON_COMMAND(ID_TRANSFORM_ROTATE270, &CiSimView::OnTransformRotate270)
    ON_COMMAND(ID_FILTER_COMPAREPITCH8DIR, &CiSimView::OnFilterComparepitch8dir)
    ON_COMMAND(ID_FILTER_COMPAREPITCH4DIR, &CiSimView::OnFilterComparepitch4dir)
    ON_COMMAND(ID_FILTER_COMPAREPITCH4DIRLOW, &CiSimView::OnFilterComparepitch4dir_noghost)
    ON_COMMAND(ID_FILTER_COMPAREPITCHDIAGONAL, &CiSimView::OnFilterComparepitchdiagonal)
    ON_COMMAND(ID_FILTER_COMPAREPITCHDIAGONALNOGHOST, &CiSimView::OnFilterComparePitch_Diagonal_NoGhost)
    ON_COMMAND(ID_FILTER_COMPAREPITCHEDGESHIFT, &CiSimView::OnFilterComparePitch_EdgeShift)
    ON_COMMAND(ID_SEGMENT_DETECTOBJECT, &CiSimView::OnSegmentDetectObject)
    ON_COMMAND(ID_MATCHING_FINDPOS, &CiSimView::OnMatchingFindpos)
    ON_COMMAND(ID_MATCHING_FINDPOS_SUB, &CiSimView::OnMatchingFindposSub)
    ON_COMMAND(ID_CALC_FINDFIRSTEDGE, &CiSimView::OnCalcFindfirstedge)
    ON_COMMAND(ID_MATCHING_EDGEMATCH, &CiSimView::OnMatchingEdgematch)
    ON_COMMAND(ID_SAVE_PROJ, &CiSimView::OnSaveProj)
    ON_COMMAND(ID_CALC_FINDFIRSTEDGE_AVRDIFF, &CiSimView::OnCalcFindfirstedgeAvrdiff)
    ON_COMMAND(ID_TRANSFORM_SCALEIMAGEDEMO, &CiSimView::OnTransformScaleimagedemo)
    ON_COMMAND(ID_TRANSFORM_ROTATEIMAGE, &CiSimView::OnTransformRotateimage)
    ON_COMMAND(ID_TRANSFORM_RECTANGULARIZEDEMO, &CiSimView::OnTransformRectangularizedemo)
    ON_COMMAND(ID_TRANSFORM_CORRECTPERSPECTIVE, &CiSimView::OnTransformCorrectperspective)
    ON_COMMAND(ID_MORPH_THINNING, &CiSimView::OnMorphThinning)
    ON_COMMAND(ID_CHANEL_R, &CiSimView::OnChanelR)
    ON_COMMAND(ID_CHANEL_G, &CiSimView::OnChanelG)
    ON_COMMAND(ID_CHANEL_B, &CiSimView::OnChanelB)
    ON_COMMAND(ID_UTIL_SUPERIMPOSE, &CiSimView::OnUtilSuperimpose)
    ON_COMMAND(ID_ALGOTEST_PRJCOMPENSATION, &CiSimView::OnAlgotestPrjcompensation)
    ON_COMMAND(ID_ALGOTEST_ELAMON, &CiSimView::OnAlgotestElamon)
    ON_COMMAND(ID_MATCHING_MATCH, &CiSimView::OnMatchingMatch)
    ON_COMMAND(ID_ALGOTEST_PRINT, &CiSimView::OnAlgotestPrint)
	ON_COMMAND(ID_MAKEPD_MAKEPDDEFECT, &CiSimView::OnMakepdMakepddefect)
	ON_COMMAND(ID_MAKEPD_MAKECALPATTERN, &CiSimView::OnMakepdMakecalpattern)
	ON_COMMAND(ID_MAKEPD_MAKECALPATTERN32898, &CiSimView::OnMakepdMakecalpattern32898)
	ON_COMMAND(ID_COSMETICTEST_MERGEIMAGE, &CiSimView::OnCosmetictestMergeimage)
	ON_COMMAND(ID_COSMETICTEST_PITCHCOMPAREMIN, &CiSimView::OnCosmetictestPitchcomparemin)
	ON_COMMAND(ID_FEATUREINFO_DEFOCUSINDEX, &CiSimView::OnFeatureinfoDefocusindex)
	ON_COMMAND(ID_FEATUREINFO_GETALLFEATURE, &CiSimView::OnFeatureinfoGetallfeature)
	ON_COMMAND(ID_FEATUREINFO_DETECTION, &CiSimView::OnFeatureinfoDetection)
	ON_COMMAND(ID_COSMETICTEST_NORMALIZE, &CiSimView::OnCosmetictestNormalize)
END_MESSAGE_MAP()

// CiSimView 생성/소멸

CString sf_GetComputerDir()
{
    IMalloc                *pShellMalloc = NULL;
    IShellFolder        *psfParent;
    LPITEMIDLIST        pidlItem = NULL;
    LPITEMIDLIST        pidlRelative = NULL;
    STRRET                str;
    WCHAR                szDisplayName[MAX_PATH] = L"";
    WCHAR                szPath[MAX_PATH] = L"";

    HRESULT hres = SHGetMalloc(&pShellMalloc);
    if (FAILED(hres))
        return _T("");

    hres = SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlItem);
    if (SUCCEEDED(hres))
    {
        hres = SHBindToParent(pidlItem, IID_IShellFolder, (void**)&psfParent, (LPCITEMIDLIST*)&pidlRelative);
        if (SUCCEEDED(hres))
        {
            memset(&str, 0, sizeof(str));
            hres = psfParent->GetDisplayNameOf(pidlRelative, SHGDN_NORMAL, &str);
            if (SUCCEEDED(hres))
                StrRetToBuf(&str, pidlItem, szDisplayName, ARRAYSIZE(szDisplayName));

            memset(&str, 0, sizeof(str));
            hres = psfParent->GetDisplayNameOf(pidlRelative, SHGDN_NORMAL | SHGDN_FORPARSING, &str);
            if (SUCCEEDED(hres))
                StrRetToBuf(&str, pidlItem, szPath, ARRAYSIZE(szPath));

            psfParent->Release();
        }
    }

    if (pidlItem)
        pShellMalloc->Free(pidlItem);
    pShellMalloc->Release();

    return szPath;
}


CiSimView::CiSimView()
{
  // TODO: 여기에 생성 코드를 추가합니다.
	for (int i = 0; i < 9; i++)
		m_mergeParam[i] = 0;
}

CiSimView::~CiSimView()
{

}

BOOL CiSimView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: CREATESTRUCT cs를 수정하여 여기에서
  //  Window 클래스 또는 스타일을 수정합니다.

  return CScrollView::PreCreateWindow(cs);
}

// CiSimView 그리기

void CiSimView::OnDraw(CDC* pDC)
{
  CiSimDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  if (!pDoc)
    return;

  if (m_Image.IsValid()) m_Image.Draw(pDC->m_hDC,0,0);

  DrawProjection(pDC);

  m_Tracker.Draw(pDC);




}

void CiSimView::OnInitialUpdate()
{
  CScrollView::OnInitialUpdate();

  CSize sizeTotal;
  // TODO: 이 뷰의 전체 크기를 계산합니다.
  sizeTotal.cx = sizeTotal.cy = 100;
  SetScrollSizes(MM_TEXT, sizeTotal);

  DragAcceptFiles(TRUE);

  m_Tracker = CTracker(this,3,1);

  //ipl::ValidateIPL(); // ipl license activation을 위해 instance 생성시 호출

  ResetProjection();

}


// CiSimView 인쇄

BOOL CiSimView::OnPreparePrinting(CPrintInfo* pInfo)
{
  // 기본적인 준비
  return DoPreparePrinting(pInfo);
}

void CiSimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CiSimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CiSimView 진단

#ifdef _DEBUG
void CiSimView::AssertValid() const
{
  CScrollView::AssertValid();
}

void CiSimView::Dump(CDumpContext& dc) const
{
  CScrollView::Dump(dc);
}

CiSimDoc* CiSimView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CiSimDoc)));
  return (CiSimDoc*)m_pDocument;
}
#endif //_DEBUG


// CiSimView 메시지 처리기


void CiSimView::OnFileOpen()
{
  CWaitCursor wait;

  CString FileName;
  CString FileExt;
  CString Filter;

  Filter = "Image File(*.bmp,*.jpg,*.png)|*.bmp;*.jpg;*.png|";
  Filter+= "Bitmap (*.bmp)|*.bmp|";
  Filter+= "JPG Image(*.jpg)|*.jpg|";
  Filter+= "PNG Image(*.png)|*.png|";
  Filter+= "All files(*.*)|*.*||";

  CFileDialog dlg( TRUE, NULL,  NULL, OFN_HIDEREADONLY,  (LPCTSTR) Filter,NULL,0,0);


  if (dlg.DoModal()==IDOK)
  {
    m_OpenedFile = dlg.GetPathName();
    FileOpen(m_OpenedFile.GetBuffer());
  }
}


void CiSimView::OnMouseMove(UINT nFlags, CPoint point)
{
  m_Tracker.m_ScrollPos = GetScrollPosition(); 
  m_Tracker.OnMouseMove(nFlags,point);

  CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
  CString			strMsg;


  if(m_Image.IsValid()) {

    strMsg.Format(_T("(%4dx%4d)"), m_Tracker.GetCurRect().Width(),m_Tracker.GetCurRect().Height());
    pFrame->SetPaneText(INDICATOR_ROI, (LPCTSTR)strMsg);

    CPoint			ptPos;
    ptPos = point + GetScrollPosition(); 

    if((uint32_t)ptPos.x < m_Image.GetWidth() && (uint32_t)ptPos.y < m_Image.GetHeight()) {

      strMsg.Format(_T("(%d,%d)"), ptPos.x, ptPos.y);
      pFrame->SetPaneText(INDICATOR_POS, (LPCTSTR)strMsg);

      RGBQUAD cpx;
      cpx = m_Image.GetPixelColor(ptPos.x,m_Image.GetHeight()-ptPos.y);
      if(m_Image.GetBpp()==8)
        strMsg.Format(_T("%3d"),cpx.rgbRed);
      else
        strMsg.Format(_T("%3d,%3d,%3d"),cpx.rgbRed,cpx.rgbGreen,cpx.rgbBlue);
      pFrame->SetPaneText(INDICATOR_VAL, (LPCTSTR)strMsg);



    }

  }


  CScrollView::OnMouseMove(nFlags, point);
}


void CiSimView::OnDropFiles(HDROP hDropInfo)
{
  TCHAR szPathName[_MAX_PATH];

//	UINT DragQueryFile(HDROP hDrop,UINT iFile,LPTSTR lpszFile, UINT cch);
  ::DragQueryFile(hDropInfo,0,szPathName,_MAX_PATH);

    FileOpen(szPathName);

    m_OpenedFile = CString(szPathName);

  CScrollView::OnDropFiles(hDropInfo);
}


int CiSimView::FileOpen(TCHAR* PathName)
{
	TCHAR szFileName[_MAX_PATH];
	TCHAR szExt[_MAX_EXT];

  CString FileName;
  CString FileExt;

  CWaitCursor wc;


  _tsplitpath_s(PathName,NULL,0,NULL,0,szFileName,_MAX_PATH,szExt,_MAX_EXT);
  FileExt = CString(szExt);
  FileExt.TrimLeft('.');
  FileName = CString(szFileName);

  int nType = m_Image.GetTypeIdFromName(FileExt);

  if (m_Image.Load(PathName, nType ) )
  {
    GetDocument()->SetTitle(FileName+_T(".")+FileExt);
    
    UpdateImageInfo();

    Invalidate(TRUE);
  
  }
  else
  {
    AfxMessageBox(_T("File Loading Error"));
  }
  return 0;
}

int CiSimView::UpdateImageInfo(void)
{
    CSize m_sWinSize = CSize(m_Image.GetWidth(),m_Image.GetHeight()); // 전체 스크롤 싸이즈

    SetScrollSizes(MM_TEXT, m_sWinSize);

    CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
    CString			strMsg;
    
    
    strMsg.Format(_T("%dx%d"), m_Image.GetWidth(),m_Image.GetHeight());
    pFrame->SetPaneText(INDICATOR_SIZE, (LPCTSTR)strMsg);


    strMsg.Format(_T("%d bpp"),  m_Image.GetBpp());
    pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);

 
    m_ImgWid = m_Image.GetWidth();
    m_ImgHgt= m_Image.GetHeight();


    m_Tracker.SetRect(CRect(0,0,m_Image.GetWidth(),m_Image.GetHeight()));
    m_Tracker.Hide();

    strMsg.Format(_T("(%4dx%4d)"), m_Tracker.GetRect().Width(),m_Tracker.GetRect().Height());
    pFrame->SetPaneText(INDICATOR_ROI, (LPCTSTR)strMsg);

    ResetProjection();

    return 0;
}

void CiSimView::OnEditUndo()
{
  if(!m_OpenedFile.IsEmpty())
      FileOpen(m_OpenedFile.GetBuffer());
}

void CiSimView::OnLButtonDown(UINT nFlags, CPoint point)
{
  m_Tracker.m_ScrollPos = GetScrollPosition(); 
  m_Tracker.OnLButtonDown(nFlags,point);

  m_Tracker.Show();

  CScrollView::OnLButtonDown(nFlags, point);
}


void CiSimView::OnLButtonUp(UINT nFlags, CPoint point)
{
  m_Tracker.m_ScrollPos = GetScrollPosition(); 
  m_Tracker.OnLButtonUp(nFlags,point);


  Invalidate(FALSE);

  CScrollView::OnLButtonUp(nFlags, point);
}


void CiSimView::OnLButtonDblClk(UINT nFlags, CPoint point)
{

  m_Tracker.SetRect(CRect(0,0,m_Image.GetWidth(),m_Image.GetHeight()));
  m_Tracker.Hide();

  CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
  CString			strMsg;

  strMsg.Format(_T("(%4dx%4d)"), m_Tracker.GetRect().Width(),m_Tracker.GetRect().Height());
  pFrame->SetPaneText(INDICATOR_ROI, (LPCTSTR)strMsg);

  ResetProjection();


  CScrollView::OnLButtonDblClk(nFlags, point);
}


void CiSimView::OnProc1Grayscale()
{
  if (!m_Image.IsValid()) return;

  m_Image.GrayScale();

  CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
  CString			strMsg;


  strMsg.Format(_T("%d bpp"), m_Image.GetBpp());
  pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);


  Invalidate(FALSE);
}

void CiSimView::OnFileSave()
{

  if (!m_Image.IsValid()) return;

  CWaitCursor wait;

  CString FileName;
  CString FileExt;
  CString Filter;

  Filter = _T("Image File(*.bmp,*.jpg,*.png)|*.bmp;*.jpg;*.png|");
  Filter+= _T("Bitmap (*.bmp)|*.bmp|");
  Filter+= _T("JPG Image(*.jpg)|*.jpg|");
  Filter+= _T("PNG Image(*.png)|*.png|");
  Filter+= _T("All files(*.*)|*.*||");

  TCHAR path[MAX_PATH] = { 0 };
  //현재의 작업경로를 얻어와 저장 한다. 
  GetCurrentDirectory(MAX_PATH, path);

  CFileDialog dlg( FALSE, NULL,  NULL, OFN_OVERWRITEPROMPT, Filter,this,0);

  //dlg.m_ofn.lpstrInitialDir = sf_GetComputerDir();
  int ret = dlg.DoModal();

 
  if (ret == IDOK)
  {
    m_OpenedFile = dlg.GetPathName();
    FileSave((TCHAR*)m_OpenedFile.GetString());
  }
  else
  {
    AfxMessageBox(_T("File saving canceled."));
  }

  SetCurrentDirectory(path);

}


int CiSimView::FileSave(TCHAR* PathName)
{
    TCHAR szDrv[_MAX_DRIVE];
    TCHAR szDir[_MAX_DIR];
    TCHAR szFName[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];

  CString FileName;
  CString FileExt;
  CString str;

  CWaitCursor wc;

  _tsplitpath_s(PathName,szDrv,_MAX_DRIVE,szDir,_MAX_DIR,szFName,_MAX_FNAME,szExt,_MAX_EXT);

  FileExt = CString(szExt);
  FileExt.TrimLeft('.');
  FileExt.MakeUpper();
  FileName = CString(szFName);

  int nType = m_Image.GetTypeIdFromName((TCHAR*)FileExt.GetString());

  str.Format(_T(" %d"), nType);
  str = FileName + _T(" ")+ FileExt + str;
  //AfxMessageBox(str);

  if ( !m_Image.Save(PathName, nType ) )
  {
    AfxMessageBox(_T("Error in File Saving"));
  }
  return 0;

}


void CiSimView::OnContextMenu(CWnd* pWnd, CPoint point)
{

  CMenu* mmenu = AfxGetMainWnd()->GetMenu();
  CMenu* submenu = mmenu->GetSubMenu(2);

  submenu->CheckMenuRadioItem(ID_PRJ_NONE,ID_PRJ_V,m_PrjType,MF_BYCOMMAND);

  submenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);

}

void CiSimView::OnProc1Histogram()
{
try
{
  if (!m_Image.IsValid()) return;

  CDlgHisto dlg;

  int sx,sy,w,h;
  sx = m_Tracker.GetRect().left;
  sy = m_Tracker.GetRect().top;
  w = m_Tracker.GetRect().Width();
  h = m_Tracker.GetRect().Height();

  CIMAGE img(NULL,0,0,w,h,w);

  img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

  calc::CalcHistogram(img,dlg.HistoData);
  
  if (dlg.DoModal() ==IDOK ) {
      CStopWatch sw;
      sw.Start();

      filter::AdjustHistogram(img,img,dlg.m_nLowBound,dlg.m_nHighBound, dlg.m_fGamma);
    
      sw.Stop();

    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());
    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());

    Invalidate(FALSE);
  }
}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}

}

void CiSimView::OnPrjCheck(UINT nID)
{
  CMenu* mmenu = AfxGetMainWnd()->GetMenu();
  CMenu* submenu = mmenu->GetSubMenu(2);
  submenu->CheckMenuRadioItem(ID_PRJ_NONE,ID_PRJ_V,nID,MF_BYCOMMAND);

  TRACE("%d checked\n",nID);

  m_PrjType = nID;
  m_Proj.Init();

  Invalidate(FALSE);
}


void CiSimView::ResetProjection(void)
{
  CMenu* mmenu = AfxGetMainWnd()->GetMenu();
  CMenu* submenu = mmenu->GetSubMenu(2);
  submenu->CheckMenuRadioItem(ID_PRJ_NONE,ID_PRJ_V,ID_PRJ_NONE,MF_BYCOMMAND);

  m_PrjType = ID_PRJ_NONE;
  m_Proj.Init();
}


void CiSimView::DrawProjection(CDC* pDC)
{
  if (m_PrjType == ID_PRJ_NONE ) return;

  if (!m_Image.IsValid()) return;

  if (m_Proj.IsChanged(m_Tracker.GetRect(),m_PrjType))
  {
    CWaitCursor wait;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);
    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    if (m_PrjType == ID_PRJ_H )
    {
      m_Proj.GetMem(m_Tracker.m_rect.Height());

      calc::CalcProjection_Horz(img,m_Proj.m_pData);

    }
    else // ID_PRJ_V
    {
      m_Proj.GetMem(m_Tracker.m_rect.Width());

      calc::CalcProjection_Vert(img,m_Proj.m_pData);

    } // Horz, Vert
  } // new ROI, re-calc Projection 

  if (m_PrjType == ID_PRJ_H )
    m_Proj.DrawProjHorz(pDC,m_Tracker.m_rect,m_Image.GetWidth(),m_Image.GetHeight());
  else // ID_PRJ_V
    m_Proj.DrawProjVert(pDC,m_Tracker.m_rect,m_Image.GetWidth(),m_Image.GetHeight());

}



void CiSimView::OnTransformFliphorz()
{
    if (!m_Image.IsValid()) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    CStopWatch sw;
    sw.Start();

    transform::FlipImage_Horz(img,img);

    sw.Stop();

    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);
       
}


void CiSimView::OnTransformFlipvert()
{
    if (!m_Image.IsValid()) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());
    
    CStopWatch sw;
    sw.Start();

    transform::FlipImage_Vert(img,img);

    sw.Stop();
  
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);
}


void CiSimView::OnTransformCopyimage()
{
    if (!m_Image.IsValid()) return;

    int w,h;

    w = m_Image.GetWidth();
    h = m_Image.GetHeight();

    CIMAGE img(NULL,0,0,w,h,w);
    img.CopyDataFromDib(m_Image.GetBits(),0,0,m_Image.GetHeight(),m_Image.GetEffWidth());
   
    CIMAGE img2(img.GetImgPtr(),CPOS(  0,0),256,256,img.Width());
    CIMAGE img3(img.GetImgPtr(),CPOS(256,0),256,256,img.Width());

    CStopWatch sw;
    sw.Start();

    transform::CopyImage(img3,img2);

    sw.Stop();
  
    img2.CopyDataToDib(m_Image.GetBits(),0,0,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);
}


void CiSimView::OnTransformMaskimage()
{
try
{
    if (!m_Image.IsValid()) return;

    CDlgParam dlg;

    dlg.SetParam(0,_T("threhold low"),108,_T(""));
    dlg.SetParam(1,_T("threhold high"),148,_T(""));
    dlg.SetParam(2,_T("flag"),1,_T("0=IN_RANGE, 1=OUT_RANGE"));

    if (dlg.DoModal() != IDOK) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    CIMAGE mask(NULL,img.Rect(),img.Width());
    CStopWatch sw;

    morph::Binarize_WithRange(img,mask,dlg.GetParam(0),dlg.GetParam(1),dlg.GetParam(2));

    sw.Start();

    transform::MaskImage(img,mask,img,128);

    sw.Stop();
   
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);

}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}
}


void CiSimView::OnTransformStitchimage()
{
    if (!m_Image.IsValid()) return;

    int sx,sy,w,h;

    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    int ww = img.Width()/3;
    int wh = img.Height()/3;
   
    CIMAGE img2(img.GetImgPtr(),CPOS(  0,0),ww,wh,img.Width());
    CIMAGE img3(img.GetImgPtr(),CPOS(ww,wh),ww,wh,img.Width());

    util::DrawRect(img3,img3.Rect(),128,FILL);

    CIMAGE ovl_imgh(img.GetImgPtr(),CPOS(ww,0),ww*2-ww/2,wh,img.Width());
    CIMAGE ovl_imgv(img.GetImgPtr(),CPOS(0,wh),ww,wh*2-wh/2,img.Width());

    CStopWatch sw;
    sw.Start();

    transform::StitchImage_Horz(img2,img3,ovl_imgh);
    transform::StitchImage_Vert(img2,img3,ovl_imgv);

    sw.Stop();
  
    util::DrawRect(img,img2.Rect(),255,UNFILL);
    util::DrawRect(img3,img3.Rect(),255,UNFILL);
    util::DrawRect(ovl_imgh,ovl_imgh.Rect(),255,UNFILL);
    util::DrawRect(ovl_imgv,ovl_imgv.Rect(),255,UNFILL);

    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);   
}


void CiSimView::OnImageHistogramAcc()
{
try
{
    if (!m_Image.IsValid()) return;

    CDlgHisto dlg;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    calc::CalcHistogram_Accumulated(img,dlg.HistoData);
  
    if (dlg.DoModal() ==IDOK ) 
    {
        filter::AdjustHistogram(img,img,dlg.m_nLowBound,dlg.m_nHighBound, dlg.m_fGamma);
    
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());


    Invalidate(FALSE);
    }
}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}
}


void CiSimView::OnMorphBinarize()
{
try
{
    if (!m_Image.IsValid()) return;

    CDlgParam dlg;

    dlg.SetParam(0,_T("threhold"),148,_T(""));
    dlg.SetParam(1,_T("flag"),1,_T("0=low, 1=high"));

    if (dlg.DoModal() != IDOK) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());
    CStopWatch sw;
    sw.Start();

    morph::Binarize(img,img,dlg.GetParam(0),dlg.GetParam(1));
    
    sw.Stop();
  
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());

    Invalidate(FALSE);

}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}

}


void CiSimView::OnMorphBinarizeRange()
{
try
{
    if (!m_Image.IsValid()) return;

    CDlgParam dlg;

    dlg.SetParam(0,_T("threhold low"),108,_T(""));
    dlg.SetParam(1,_T("threhold high"),148,_T(""));
    dlg.SetParam(2,_T("flag"),1,_T("0=IN_RANGE, 1=OUT_RANGE"));

    if (dlg.DoModal() != IDOK) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    CStopWatch sw;
    sw.Start();

    morph::Binarize_WithRange(img,img,dlg.GetParam(0),dlg.GetParam(1),dlg.GetParam(2));

    sw.Stop();
   
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);



}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}

}


void CiSimView::OnUtilDrawdemo()
{

try
{
    if (!m_Image.IsValid()) return;

    int sx,sy,w,h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL,0,0,w,h,w);

    img.CopyDataFromDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());
    CStopWatch sw;
    sw.Start();

    util::DrawRect(img,img.Rect(),255,UNFILL);
    util::DrawRect(img,CRECT(80,80,120,120),255,FILL);
    
    util::DrawLine(img,CPOS(img.PosCenter().X(),img.Top()) ,CPOS(img.PosCenter().X(),img.Bottom()),255);
    util::DrawLine(img,CPOS(img.Left(),img.PosCenter().Y() ) ,CPOS(img.Right(),img.PosCenter().Y() ),255);

    util::DrawLine(img,CPOS(img.Left(),img.PosCenter().Y()+20),CPOS(img.Right(),img.PosCenter().Y()-20),255);
    util::DrawLine(img,CPOS(img.PosCenter().X()-20,img.Top()),CPOS(img.PosCenter().X()+20,img.Bottom()),255);

    util::DrawCircle(img,CPOS( 100, 100 ), 80, 255, UNFILL);
    util::DrawCircle(img,CPOS( 100, 250 ), 40, 255, FILL);

    util::DrawElipse(img,CRECT(200, 100, 300, 300), 255, UNFILL);

    util::DrawElipseQuad(img, CRECT(240, 160, 250, 200), 2, 255, UNFILL);

    util::DrawElipseQuad(img,CRECT(img.PosCenter().X()+50, img.PosCenter().Y() + 50, img.PosCenter().X() + 150, img.PosCenter().Y() + 150), 1, 64, FILL);

    CIMAGE img2(img.GetImgPtr(),CRECT(240,220,260,240),img.Width());
    util::DrawElipse(img2,CRECT(240, 160, 260, 240), 255, UNFILL);

    img2.SetData(img.GetImgPtr(),CPOS(30,30),400,60,img.Width());
	util::DrawTextMsg(img2, CPOS(30, 30), "~!@#$%^&*()_+`1234567890-=", 128, 0);
	util::DrawTextMsg(img2, CPOS(30, 42), "ABCDEFGHIJKLMNOPQRSTUVWXYZ{}|:\"<>?", 0, 128);
	util::DrawTextMsg(img2, CPOS(30, 54), "abcdefghijklmnopqrstuvwxyz[]\\;',./", 255, 128);
	util::DrawTextMsg(img2, CPOS(30, 70), "Love potion No.9 (#9)", 192, 64);

    CPOS* pt_list;
    pt_list = new CPOS[img.Width()];

    int i,y;
    for (i = 0; i < img.Width(); i++)
    {
        y = (int)( sin(i * 6.28 / (img.Width())) * img.Height()/2) ;
        pt_list[i] = CPOS(i + img.Left() / 2, y+img.PosCenter().Y());
    }
    util::DrawPolyLine(img, pt_list,img.Width(), 0,OPEN);


    sw.Stop();
    delete[] pt_list;
    img.CopyDataToDib(m_Image.GetBits(),sx,sy,m_Image.GetHeight(),m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);

}
catch( const char* msg)
{
    AfxMessageBox(CString(msg));
}

}


void CiSimView::OnImageStat()
{
	try
	{
		if (!m_Image.IsValid()) return;

		int sx, sy, w, h;
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();

		CIMAGE img(NULL, 0, 0, w, h, w);

		img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
		CStopWatch sw;

		char msg[256];

		sw.Start();

        float av = calc::CalcAverage(img);
        float vr = calc::CalcVariance(img);
        float dv = calc::CalcStdDeviation(img);
        int ct = calc::CountPixel_WithRange(img, 108, 148, ipl::IN_RANGE);
        int min_val, max_val;
        calc::CalcMinMax(img, min_val, max_val);

		sprintf_s(msg, sizeof(msg),"Avr : %.3f", av);
		util::DrawTextMsg(img, CPOS(10, 10), msg,255,128);

        sprintf_s(msg, sizeof(msg), "Var : %.3f", vr);
		util::DrawTextMsg(img, CPOS(10, 25), msg,255,128);

        sprintf_s(msg, sizeof(msg), "StDev : %.3f", dv);
		util::DrawTextMsg(img, CPOS(10, 40), msg, 255, 128);

        sprintf_s(msg, sizeof(msg), "Cnt : %d", ct);
		util::DrawTextMsg(img, CPOS(10, 55), msg, 255, 128);


        sprintf_s(msg, sizeof(msg), "Min: %d, Max: %d",min_val, max_val );
        util::DrawTextMsg(img, CPOS(10, 70), msg, 255, 128);

		sw.Stop();
		img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);

	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}
}


void CiSimView::OnMorphLogicalOp()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
        CStopWatch sw;

        int ww, wh;
        ww = w / 4;
        wh = h / 2;

        sw.Start();

        CIMAGE im(img.GetImgPtr(),     0,   0, ww, wh, img.Offset());
        CIMAGE imb(img.GetImgPtr(), ww  ,   0, ww, wh, img.Offset());
        CIMAGE imb2(img.GetImgPtr(),ww*2,   0, ww, wh, img.Offset());
        CIMAGE imn(img.GetImgPtr(), ww*3,   0, ww, wh, img.Offset());
        CIMAGE ima(img.GetImgPtr(),    0,  wh, ww, wh, img.Offset());
        CIMAGE imo(img.GetImgPtr(), ww  ,  wh, ww, wh, img.Offset());
        CIMAGE imx(img.GetImgPtr(), ww*2,  wh, ww, wh, img.Offset());

        morph::Binarize(im, imb, 158, ipl::HIGH);
        morph::Binarize(im, imb2, 148, ipl::HIGH);
        morph::OperateNOT(imb, imn);
        morph::OperateAND(imb, imb2, ima);
        morph::OperateOR(imb, imb2, imo);
        morph::OperateXOR(imb, imb2, imx);

        util::DrawTextMsg(im, im.PosLT(), "ORG", 255, 128);
        util::DrawTextMsg(imb, imb.PosLT(), "BIN1", 255, 128);
        util::DrawTextMsg(imb2, imb2.PosLT(), "BIN2", 255, 128);
        util::DrawTextMsg(imn, imn.PosLT(), "NOT", 255, 128);
        util::DrawTextMsg(ima, ima.PosLT(), "AND", 255, 128);
        util::DrawTextMsg(imo, imo.PosLT(), "OR ", 255, 128);
        util::DrawTextMsg(imx, imx.PosLT(), "XOR", 255, 128);

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}




void CiSimView::OnMorphMorphologydemo()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int ww, wh;

        ww = w / 5;
        wh = h / 2;
        CStopWatch sw;
        

        CIMAGE imo(img.GetImgPtr(),   0,   0, ww, wh, img.Offset());
        CIMAGE imb(img.GetImgPtr(),   0,  wh, ww, wh, img.Offset());
        CIMAGE ime(img.GetImgPtr(),  ww,   0, ww, wh, img.Offset());
        CIMAGE imd(img.GetImgPtr(),  ww,  wh, ww, wh, img.Offset());
        CIMAGE imeh(img.GetImgPtr(), ww*2, 0, ww, wh, img.Offset());
        CIMAGE imev(img.GetImgPtr(), ww*3, 0, ww, wh, img.Offset());
        CIMAGE imdh(img.GetImgPtr(), ww*2, wh, ww, wh, img.Offset());
        CIMAGE imdv(img.GetImgPtr(), ww*3, wh, ww, wh, img.Offset());
        CIMAGE imop(img.GetImgPtr(), ww * 4,  0, ww, wh, img.Offset());
        CIMAGE imcl(img.GetImgPtr(), ww * 4, wh, ww, wh, img.Offset());

        sw.Start();

        morph::Binarize(imo, imb, 158, ipl::HIGH);
        morph::Erode(imb, ime);
        morph::Dilate(imb, imd);
        morph::Erode_Horz(imb, imeh);
        morph::Erode_Vert(imb, imev);
        morph::Dilate_Horz(imb, imdh);
        morph::Dilate_Vert(imb, imdv);
        morph::Opening(imb, imop, ime);
        morph::Closing(imb, imcl, imd);

        sw.Stop();

        util::DrawTextMsg(imo, imo.PosLT(), "ORG", 255, 128);
        util::DrawTextMsg(imb, imb.PosLT(), "BIN", 255, 128);
        util::DrawTextMsg(ime, ime.PosLT(), "ERD", 255, 128);
        util::DrawTextMsg(imd, imd.PosLT(), "DLT", 255, 128);
        util::DrawTextMsg(imeh, imeh.PosLT(), "ERD H", 255, 128);
        util::DrawTextMsg(imdh, imdh.PosLT(), "DLT H", 255, 128);
        util::DrawTextMsg(imev, imev.PosLT(), "ERD V", 255, 128);
        util::DrawTextMsg(imdv, imdv.PosLT(), "DLT V", 255, 128);
        util::DrawTextMsg(imop, imop.PosLT(), "OPEN", 255, 128);
        util::DrawTextMsg(imcl, imcl.PosLT(), "CLOSE", 255, 128);

        
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphErode32831()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Erode(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphErodehorz()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Erode_Horz(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphErodevert()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Erode_Vert(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphDilate()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Dilate(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphDilatehorz()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Dilate_Horz(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphDilatevert()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Dilate_Vert(img, ims);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphOpening()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CIMAGE tmp(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Opening(img, ims, tmp);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphClosing()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE ims(NULL, 0, 0, w, h, w);

        CIMAGE tmp(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        morph::Closing(img, ims, tmp);

        sw.Stop();
        ims.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterAverage()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("average wid"), 3, _T("홀수"));
        dlg.SetParam(1, _T("average hgt"), 3, _T("홀수"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        U64* buffer;
        buffer = new U64[w*h];
        CStopWatch sw;
        sw.Start();

        filter::Average(img, img, buffer, dlg.GetParam(0), dlg.GetParam(1));

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        delete[] buffer;

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}



void CiSimView::OnFilterSobel()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Sobel(img, imt);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterSobelhorz()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Sobel_Horz(img, imt);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterSobelvert()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Sobel_Vert(img, imt);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterLaplacian()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Laplacian(img, imt);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterMedian()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("win size"), 3, _T("N x N pixel"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

       // filter::Median(img, imt,dlg.GetParam(0));
		CAlgProc alg;
		alg.fnMedianFilter(img, imt, dlg.GetParam(0), dlg.GetParam(0));

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterGaussian()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("mask size"), 5, _T("N x N pixel"));
        dlg.SetParam(1, _T("sigma"), 100, _T("/100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        U64* buf = new U64[w*h];

        filter::Gaussian(img, imt,buf,dlg.GetParam(0),dlg.GetParam(1)/100.);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);
        
        delete[] buf;
    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }

}


void CiSimView::OnFilterLog()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("mask size"), 13, _T("N x N pixel"));
        dlg.SetParam(1, _T("sigma"), 210, _T("N / 100"));
        dlg.SetParam(2, _T("gain"), 100, _T("N / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        U64* buf = new U64[w*h];

        filter::LoG(img, imt, buf, dlg.GetParam(0), (double)dlg.GetParam(1) / 100., (double)dlg.GetParam(2)/100. );

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

        delete[] buf;
    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterMultiplyself()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("gain"), 4, _T("N / 1000"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::MultiplySelf(img, imt, dlg.GetParam(0)/1000.);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterCanny()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("gaussian mask size"), 5, _T("N x N pixel"));
        dlg.SetParam(1, _T("sigma"), 100, _T("N / 100"));
        dlg.SetParam(2, _T("thre lo"), 108, _T("gray level"));
        dlg.SetParam(3, _T("thre hi"), 148, _T("gray level"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        U64* buf = new U64[w*h];

        filter::Canny(img, imt, buf, dlg.GetParam(0), dlg.GetParam(1) / 100., dlg.GetParam(2), dlg.GetParam(3));

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

        delete[] buf;
    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterThresholdlo()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("thre lo"), 108, _T("gray"));
        dlg.SetParam(1, _T("thre hi"), 148, _T("gray"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Threshold_LowHigh(img, imt, dlg.GetParam(0), dlg.GetParam(1));

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterUniformizevert()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("exclude low"), 0, _T("gray"));
        dlg.SetParam(1, _T("exclude high"), 255, _T("gray"));
        dlg.SetParam(2, _T("Uniform method"), 0, _T("0=BIAS, 1=SCALE"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;
        sw.Start();

        filter::Uniformize_Vert(img, img, dlg.GetParam(0), dlg.GetParam(1),dlg.GetParam(2));

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterUniformizehorz()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("exclude low"), 0, _T("gray"));
        dlg.SetParam(1, _T("exclude high"), 255, _T("gray"));
        dlg.SetParam(2, _T("Uniform method"), 0, _T("0=BIAS, 1=SCALE"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;
        sw.Start();

        filter::Uniformize_Horz(img, img, dlg.GetParam(0), dlg.GetParam(1), dlg.GetParam(2));

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterEnhancebinning()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("bin size"), 2, _T("N*N pixel"));
        dlg.SetParam(1, _T("bias src"), 128, _T("gray"));
        dlg.SetParam(2, _T("bias dest"), 128, _T("gray"));
        dlg.SetParam(3, _T("gain"), 100, _T(" / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;
        sw.Start();

        filter::Enhance_Binning(img, img, dlg.GetParam(0), dlg.GetParam(1), dlg.GetParam(2),dlg.GetParam(3)/100);

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterDynamicbias()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("win wid"), 13, _T("pixel"));
        dlg.SetParam(1, _T("win hgt"), 13, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 200, _T(" / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        U64 *buf;
        buf = new U64[w*h];

        CStopWatch sw;
        sw.Start();

        filter::Enhance_DynamicBias(img, img, buf, dlg.GetParam(0), dlg.GetParam(1),  dlg.GetParam(2) / 100);

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        delete[] buf;

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterEnhance4c()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("bias src"), 128, _T("gray"));
        dlg.SetParam(1, _T("bias dest"), 128, _T("gray"));
        dlg.SetParam(2, _T("gain"), 200, _T(" / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Enhance_4C(img, imt, dlg.GetParam(0), dlg.GetParam(1), dlg.GetParam(2) / 100);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());


        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterEnhance9c()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("bias src"), 128, _T("gray"));
        dlg.SetParam(1, _T("bias dest"), 128, _T("gray"));
        dlg.SetParam(2, _T("gain"), 300, _T(" / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Enhance_9C(img, imt, dlg.GetParam(0), dlg.GetParam(1), dlg.GetParam(2) / 100);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());


        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterAverage3x3()
{
    try
    {
        if (!m_Image.IsValid()) return;

        //CDlgParam dlg;

        //dlg.SetParam(0, _T("bias src"), 128, _T("gray"));
        //dlg.SetParam(1, _T("bias dest"), 128, _T("gray"));
        //dlg.SetParam(2, _T("gain"), 300, _T(" / 100"));

        //if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::Average_3x3(img, imt);

        sw.Stop();
        imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());


        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterCompress2x2()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imt(img.GetImgPtr(),img.PosLT(), img.Width()/2, img.Height()/2, img.Offset());

        CStopWatch sw;
        sw.Start();

        filter::Compress_2x2(img, imt);

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());


        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformRotate90()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE ims(img.GetImgPtr(), 0, 0, rw, rw, w);
        CIMAGE imd(NULL, 0,0,rw,rw,w);

        CStopWatch sw;
        sw.Start();

        transform::RotateImage_90(ims, imd);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformRotate180()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        transform::RotateImage_180(img, imd);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }

}


void CiSimView::OnTransformRotate270()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE ims(img.GetImgPtr(), 0, 0, rw, rw, w);
        CIMAGE imd(NULL, 0, 0, rw, rw, w);

        CStopWatch sw;
        sw.Start();

        transform::RotateImage_270(ims, imd);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparepitch8dir()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
        dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_8Dir(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, dlg.GetParam(3));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparepitch4dir()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
        dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_4Dir(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, dlg.GetParam(3));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparepitch4dir_noghost()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
        dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_4Dir_NoGhost(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, dlg.GetParam(3));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparepitchdiagonal()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
        dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_Diagonal(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, dlg.GetParam(3));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparePitch_Diagonal_NoGhost()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
        dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_Diagonal_NoGhost(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, dlg.GetParam(3));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnFilterComparePitch_EdgeShift()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
        dlg.SetParam(1, _T("pitch y"), 8, _T("pixel"));
        dlg.SetParam(2, _T("esge shift"), 80, _T(" / 100"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        filter::ComparePitch_EdgeShift(img, imd, dlg.GetParam(0), dlg.GetParam(1)
            , dlg.GetParam(2) / 100, ipl::APPROX);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnSegmentDetectObject()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("max obj num"), 100000, _T(" ea"));
        dlg.SetParam(1, _T("min area"), 1, _T("pixel"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        vector<OBJECT> obj_list;
        obj_list.clear();

        CStopWatch sw;
        int onum;

        CWaitCursor wc;
        char msg[4096];
        //OBJECT* pObj;
        //pObj = new OBJECT[dlg.GetParam(0)];

        sw.Start();

        // Array(pointer) of OBJECT 
		OBJECT *pObj = new OBJECT[dlg.GetParam(0)];
        onum = segment::DetectObject_8N(img, pObj, dlg.GetParam(0) , dlg.GetParam(1));
        segment::ConvertObject_ArrToVec(pObj, obj_list, onum);
        //segment::MergeObject(obj_list, 3);

        // vector of OBJECT
        //onum = segment::DetectObject_8N(img, obj_list, dlg.GetParam(0), dlg.GetParam(1));

        sw.Stop();
        
        for (int i = 0; i < onum; i++)
        {
            util::DrawRect(img
                , CRECT(obj_list[i].sx - 2, obj_list[i].sy - 2, obj_list[i].ex + 2, obj_list[i].ey + 2)
                , 128, UNFILL);
        }

        //delete[] pObj;

        sprintf_s(msg, "%d objs ", onum);
        util::DrawTextMsg(img, CPOS(0, 0), msg, 255, 0);

        CString str;
        str.Format(_T("%d objs detected"), onum);
        AfxMessageBox(str);

        
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);

		delete[] pObj;
    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMatchingFindpos()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);
		
		int nType = m_Image.GetTypeIdFromName(_T("bmp"));
		CxImage ref;
		int res = ref.Load(_T("d:\\poref.bmp"), nType);

		ref.GrayScale();


// 		wt = ref.GetWidth(); ht = ref.GetHeight();
// 		CIMAGE imgTemplate(NULL, 0, 0, wt,ht,wt);
// 		imgTemplate.CopyDataFromDib(xImgTmp.GetBits(), 0, 0, ht,xImgTmp.GetEffWidth());

		int widref = ref.GetWidth();
		int hgtref = ref.GetHeight();
		CIMAGE cref(NULL, 0, 0, widref, hgtref, widref);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
		cref.CopyDataFromDib(ref.GetBits(), 0, 0, ref.GetHeight(), ref.GetEffWidth());


     //   CIMAGE imr(img.GetImgPtr(), sx, sy, ,  101, 101, 256, 256, img.Offset());
      //  CIMAGE ims(img.GetImgPtr(), 0, 0, 512, 512, img.Offset());

      
        CStopWatch sw;
        CWaitCursor wc;

        char msg[4096];

        sw.Start();
        CPOS match_pos;
        float score;
        score = match::FindMatchPosition(img, cref, match_pos, SSE2);

        sw.Stop();

        sprintf_s(msg, "Match at (%d,%d) : score %f ",match_pos.X(),match_pos.Y(),score);
        util::DrawTextMsg(img, CPOS(0, 0), msg, 255, 0);

        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMatchingFindposSub()
{
    try
    {
        if (!m_Image.IsValid()) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imr(img.GetImgPtr(), 101, 101, 256, 256, img.Offset());
        CIMAGE ims1(img.GetImgPtr(), 2, 2, 512, 512, img.Offset());
        CIMAGE ims2(img.GetImgPtr(), 0, 0, 512, 512, img.Offset());

        CIMAGE ref(NULL, 0, 0, 256, 256, 256);
        transform::CopyImage(imr, ref);

        transform::TranslateImage_Subpixel(ims1, ims2, 0.1, 0.2);

        CStopWatch sw;
        CWaitCursor wc;

        char msg[4096];

        sw.Start();
        CPOSF match_pos;
        float score;
        score = match::FindMatchPosition_Subpixel(ims2, ref, match_pos, AVX2);

        sw.Stop();

        sprintf_s(msg, "Match at (%f,%f) : score %f ", match_pos.X(), match_pos.Y(), score);
        util::DrawTextMsg(img, CPOS(0, 0), msg, 255, 0);

        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnCalcFindfirstedge()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("Horz/Vert"), 0, _T(" 0 =Horz / 1 =Vert"));
        dlg.SetParam(1, _T("thre"), 20, _T("gray diff"));
        dlg.SetParam(2, _T("Rise/Fall"), 0, _T("edge type 0 =rise / 1 =fall / 2 =Both"));
        dlg.SetParam(3, _T("Scan Dir"), 0, _T("0 =Fwd / 1 =Bwd"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;

        CWaitCursor wc;
        char msg[4096];

        sw.Start();

        int pos, slope;

        if (dlg.GetParam(0) == 0) // horz
        {
            slope = calc::FindFirstEdge_Horz(img, pos, dlg.GetParam(1), dlg.GetParam(2), dlg.GetParam(3));
            if (pos>0) util::DrawLine(img, CPOS(img.Left(), pos), CPOS(img.Right(), pos), 64);
        }
        else // vert
        {
            slope = calc::FindFirstEdge_Vert(img, pos, dlg.GetParam(1), dlg.GetParam(2), dlg.GetParam(3));
            if (pos>0) util::DrawLine(img, CPOS(pos, img.Top()), CPOS(pos, img.Bottom()), 64);
        }

        sw.Stop();


        sprintf_s(msg, "Edge at %d : sl %d ", pos, slope);
        util::DrawTextMsg(img, CPOS(0, 0), msg, 255, 0);

        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}




/*
void CiSimView::OnProcessingTest()
{
	
    if (!m_Image.IsValid()) return;

    int sx, sy, w, h;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL, 0, 0, w, h, w);

    img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

    

    vector<OBJECT> olist;
    
    //extern vector<OBJECT> ipl_obj_list;

    OBJECT* pObj;
    int onum;

    //pObj = (OBJECT*)img.GetRoiPtr();
    pObj = NULL;
    CStopWatch sw;
    sw.Start();

    //ipl::Test(img,&pObj,onum);

    sw.Stop();

    CString str;

    str.Format(_T("olist %d"), onum);
    AfxMessageBox(str);

    delete[] pObj;

    img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
    Invalidate(FALSE);
	
	/**********************************************************************
	// font extraction 

    CIMAGE fim(NULL,0,0,m_Image.GetWidth(),m_Image.GetHeight(),m_Image.GetWidth());

    fim.CopyDataFromDib(m_Image.GetBits(),0,0,m_Image.GetHeight(),m_Image.GetEffWidth());
    
    int tmp;

   
	CStdioFile file;
	CFileException e;

	if (!file.Open(_T("d:\\temp\\font.txt"), CFile::modeCreate|CFile::modeWrite, &e))
	{
		TRACE("error %u\n", e.m_cause);
	}

	CString str;
	
    int i,j,k,m,n;
	int x, y;

    for(n=0;n<3;n++)
    {
        for(m=0;m<32;m++)
        {

            for(k=0;k<3;k++)
            {
                tmp=0;
                for(j=0;j<4;j++)
                {
                    for(i=0;i<6;i++)
                    {
						x = m * 6 + i;
						y = n * 12 + 12 + k * 4 + j;
                        if (fim(x,y)==0) 
                            tmp |= (0x80000000)>>(i+j*8);
                    }
                    
                } //j
				str.Format(_T("0x%08x, "), tmp);
				file.WriteString(str);
                
            } // k 1 char
			if (m % 2 == 1)
			{
				str.Format(_T("\n"));
				file.WriteString(str);
			}
        } //m 32 char
    }//n 3 line
    

	file.Close();

    return;
	**********************************************/
	/***********************************************
	// CIMAGE class Test
	CIMAGE img(NULL,0,0,512,256,512);

    img.CopyDataFromDib(m_Image.GetBits(),0,0,m_Image.GetHeight(),m_Image.GetEffWidth());
 
    TRACE("TypeSize(BYTE) %d\n",img.GetTypeSize());
    TRACE("LTRB: %d, %d, %d,%d   ofs : %d\n",img.Left(),img.Top(),img.Right(),img.Bottom(), img.Offset());

    // Array pointing 방식
    U8* pim = img.GetRoiPtr();
    for(int j=0;j<10;j++)
    {
        for(int i=0;i<10;i++)
        {
            pim[i+j*img.Offset()] = 0;
        }
    }
    TRACE("%d,%d : value %d\n",  0, 0,img( 0, 0));

    CIMAGE im1(img.GetImgPtr(),10,10,10,10,512);

    CPOS p = im1.PosCenter();
    TRACE("Center : %d,%d\n", p.X(), p.Y());
    p = im1.PosLT();
    TRACE("LT : %d,%d\n", p.X(), p.Y());
    p = im1.PosRB();
    TRACE("RB : %d,%d\n", p.X(), p.Y());

    CRECT r = im1.Rect();
    TRACE("LTRB: %d, %d, %d,%d \n",r.Left(),r.Top(),r.Right(),r.Bottom());

    // ()operator pointing
    for(int j=im1.Top();j<im1.Bottom();j++)
    {
        for(int i=im1.Left();i<im1.Right();i++)
        {
            im1(i,j) = im1(i,j)-50;
        }
    }
    TRACE("%d,%d : value %d\n", 10,10,img(10,10));

    CIMAGE im2(img.GetImgPtr(),CPOS(20,20),10,10,512);

    // Pixel() 함수 pointing
    for(int j=im2.Top();j<im2.Bottom();j++)
    {
        for(int i=im2.Left();i<im2.Right();i++)
        {
            im2.SetPixel(i,j, im2.GetPixel(i,j)+50 );
        }
    }
    TRACE("%d,%d : value %d\n", 20,20,img(20,20));

    // line pointing
    CIMAGE im3(img.GetImgPtr(),CRECT(30,30,40,40),512);
    U8* pLine;
    for(int j=im3.Top();j<im3.Bottom();j++)
    {
        pLine = im3.GetLine(j);
        for(int i=im3.Left();i<im3.Right();i++)
        {
            pLine[i] = 255;
        }
    }
    r = im3.Rect();
    TRACE("LTRB: %d, %d, %d,%d \n",r.Left(),r.Top(),r.Right(),r.Bottom());
    TRACE("%d,%d : value %d\n", 30,30,img(30,30));
   
    
    img.CopyDataToDib(m_Image.GetBits(),256,256,m_Image.GetHeight(),m_Image.GetEffWidth());

    Invalidate();

    CxImage imgs(512,256,8,CXIMAGE_FORMAT_BMP);
    imgs.GrayScale();
    img.CopyDataToDib(imgs.GetBits(),0,0,imgs.GetHeight(),imgs.GetEffWidth());

    imgs.Save(_T("d:/temp/a.bmp"),CXIMAGE_FORMAT_BMP);
    imgs.Save(_T("d:/temp/a.png"),CXIMAGE_FORMAT_PNG);
    imgs.Save(_T("d:/temp/a.jpg"),CXIMAGE_FORMAT_JPG);
	
}
*/

void CiSimView::OnProcessingTest()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("Prj Win size"), 15, _T(" pixel "));
        dlg.SetParam(1, _T("Win size"), 15, _T(" pixel "));
        dlg.SetParam(2,_T("Thre"),10,_T("gray level"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE src(NULL, 0, 0, w, h, w);
        CIMAGE dst(NULL, 0, 0, w, h, w);


        src.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;

        CAlgProc alp;

        CWaitCursor wc;
        sw.Start();

        
        alp.Edge_AvrDiff(src,dst,dlg.GetParam(0),dlg.GetParam(1),dlg.GetParam(2));

        sw.Stop();

        dst.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }



}

void CiSimView::OnMatchingEdgematch()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("Edge Thre"), 100, _T("Gray Value"));
        dlg.SetParam(1, _T("sampling"), 10, _T("pixel"));
        dlg.SetParam(2, _T("Flow"), 0, _T("0:DistMap 1:Step-by-step 2:one-shot"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CPOS match_pos;
        int threshold = 100;
        CStopWatch sw;
        CWaitCursor wc;

        
        // Step 1. Distance map 생성 
        //CIMAGE img(NULL, 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        //img.CopyDataFromDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

        CIMAGE imgSel(NULL, 0, 0, w, h, w);
        CIMAGE imgDstMap(NULL, 0, 0, w, h, w); 
        imgSel.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());


        sw.Start();
        

        
        int edge_threshold = dlg.GetParam(0);
        int sampling = dlg.GetParam(1);
        int nedges;

        if (dlg.GetParam(2) != 1 && dlg.GetParam(2) !=2 )
        {
            //match::Edge *edge_list0 = new match::Edge[w*h];
            match::MakeDistanceImage(imgSel, imgDstMap, edge_threshold);    
            //match::GetSingleLineEdges(imgSel, imgDstMap, edge_threshold, edge_list0);
            //delete [] edge_list0;

            sw.Stop();
            imgDstMap.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

            ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
            Invalidate(FALSE);

            return ;
        }

        // Step 2. 검색 Template Edge 
        int wt, ht;
        float score;
        CxImage xImgTmp;
        xImgTmp.Load(_T("d:\\cd_template.jpg"),0);
        xImgTmp.GrayScale();

  
        wt = xImgTmp.GetWidth(); ht = xImgTmp.GetHeight();
        CIMAGE imgTemplate(NULL, 0, 0, wt,ht,wt);
        imgTemplate.CopyDataFromDib(xImgTmp.GetBits(), 0, 0, ht,xImgTmp.GetEffWidth());

        // Call-method 1 : input으로 distancemap과 edge list전달 
        CIMAGE imgEdge(NULL, 0, 0, wt,ht,wt);
        match::Edge *tmpl_edge = new match::Edge[wt*ht];

        switch (dlg.GetParam(2))
        {
        case 1:
            match::MakeDistanceImage(imgSel, imgDstMap, edge_threshold); 
            nedges = match::GetSingleLineEdges(imgTemplate, imgEdge, edge_threshold, tmpl_edge);
            score = match::FindMatchPosition_FromEdgeDistMap(imgDstMap, nedges, tmpl_edge, sampling, match_pos);

        break;
        case 2:
            // Call-method 2 : input으로 image to image
            score = match::FindMatchPosition_EdgeBase(imgSel, imgTemplate, edge_threshold, sampling, match_pos);
        break;
        }
        
        sw.Stop();

        CString rslt;
        rslt.Format(_T(" %f  at (%d,%d) "),score,match_pos.X(),match_pos.Y());
        AfxMessageBox(rslt);

        delete [] tmpl_edge;

        util::DrawRect(imgSel,CRECT(match_pos.X(),match_pos.Y(),match_pos.X()+wt,match_pos.Y()+ht),255,ipl::UNFILL);

        // --------------------------------------------------------------------------------------------------
        imgSel.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}

void CiSimView::OnMatchingMatch()
{
    try
    {
        if (!m_Image.IsValid()) return;

        /*
        CDlgParam dlg;

        dlg.SetParam(0, _T("Edge Thre"), 100, _T("Gray Value"));
        dlg.SetParam(1, _T("sampling"), 10, _T("pixel"));
        dlg.SetParam(2, _T("Flow"), 0, _T("0:DistMap 1:Step-by-step 2:one-shot"));

        if (dlg.DoModal() != IDOK) return;
        */

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CStopWatch sw;
        CWaitCursor wc;


        CIMAGE img(NULL, 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        img.CopyDataFromDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

        sw.Start();

        int wt, ht;
        CxImage xImgTmp;
        xImgTmp.Load(_T("d:\\cd_template.jpg"), 0);
        xImgTmp.GrayScale();


        wt = xImgTmp.GetWidth(); ht = xImgTmp.GetHeight();
        CIMAGE imgTemplate(NULL, 0, 0, wt, ht, wt);
        imgTemplate.CopyDataFromDib(xImgTmp.GetBits(), 0, 0, ht, xImgTmp.GetEffWidth());

        CPOS match_pos;
        float score;
        score = match::FindMatchPosition(img, imgTemplate, match_pos, ipl::SIMD_LEVEL_FLAG::SSE2);

        sw.Stop();

        CString rslt;
        rslt.Format(_T(" %f  at (%d,%d) "), score, match_pos.X(), match_pos.Y());
        AfxMessageBox(rslt);

        util::DrawRect(img, CRECT(match_pos.X(), match_pos.Y(), match_pos.X() + wt, match_pos.Y() + ht), 255, ipl::UNFILL);

        // --------------------------------------------------------------------------------------------------
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}
void CiSimView::OnSaveProj()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
    if (m_PrjType == ID_PRJ_NONE) return;

    if (!m_Image.IsValid()) return;

    int num;

    if (m_PrjType ==ID_PRJ_V)
        num = m_Tracker.GetRect().Width();
    else
        num = m_Tracker.GetRect().Height();

    CString FileName;
    CString Filter;

    Filter = "CSV file(*.csv)|*.csv|";
    Filter += "TXT file(*.txt)|*.txt|";
    Filter += "All files(*.*)|*.*||";


    CFileDialog dlg(FALSE, _T("csv"), _T("proj"), OFN_OVERWRITEPROMPT, Filter,NULL,0);

    // SUCCESS
    CString lpstrInitialDir = _T("C:");
    dlg.m_ofn.lpstrInitialDir = lpstrInitialDir.GetBuffer(256);

    if (dlg.DoModal() == IDOK)
    {
        FileName = dlg.GetPathName();

        //USES_CONVERSION;  //W2A()

        FILE* fp;
        fp = _tfopen(FileName, _T("wt"));

        for (int i = 0; i < num; i++)
        {
            _ftprintf(fp, _T("%d,\n"), m_Proj.m_pData[i]);
        }
        fclose(fp);
    }

    


}


void CiSimView::OnCalcFindfirstedgeAvrdiff()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;

        dlg.SetParam(0, _T("Horz/Vert"), 1, _T(" 0 =Horz / 1 =Vert"));
        dlg.SetParam(1, _T("slope thre"), 800, _T("derivative * 100 "));
        dlg.SetParam(2, _T("Rise/Fall"), 2, _T("edge type 0 =rise / 1 =fall / 2 =Both"));
        dlg.SetParam(3, _T("Edge Band"), 15, _T("> 1"));
        dlg.SetParam(4, _T("Scan Dir"), 0, _T("0 =Fwd / 1 =Bwd"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        CStopWatch sw;

        CWaitCursor wc;
        char msg[4096];

        sw.Start();

        int pos, slope;

        U32* prj;
        float* prj_av;
        float edge_pos,edge_pos2;
        int prj_wid;
        float fret;

        if (dlg.GetParam(0) == 0) // horz
        {
            prj_wid = h;
            prj = new U32[prj_wid];
            prj_av = new float[prj_wid];
            calc::CalcProjection_Horz(img, prj);

        }
        else // vert
        {
            prj_wid = w;
            prj = new U32[prj_wid];
            prj_av = new float[prj_wid];
            calc::CalcProjection_Vert(img, prj);

        }

        fret = calc::FindFirstEdge_AvrDiffProj_Subpixel(prj, prj_wid, prj_av, edge_pos
            , (float)dlg.GetParam(1) / 100., dlg.GetParam(2), dlg.GetParam(3), dlg.GetParam(4));


        sw.Stop();

        if (dlg.GetParam(0) == 0) // horz
        {
            if (edge_pos>0.) util::DrawLine(img, CPOS(img.Left(), (int)(edge_pos+0.5)), CPOS(img.Right(), (int)(edge_pos + 0.5)), 64);
            util::DrawLine(img, CPOS(img.PosCenter().X(), img.Top()), CPOS(img.PosCenter().X(), img.Bottom()), 64);

        }
        else // vert
        {
            if (edge_pos>0.) util::DrawLine(img, CPOS((int)(edge_pos + 0.5), img.Top()), CPOS((int)(edge_pos + 0.5), img.Bottom()), 64);
            util::DrawLine(img, CPOS(img.Left(), img.PosCenter().Y()), CPOS(img.Right(), img.PosCenter().Y()), 64);
        }

        sprintf(msg, "edge at %.2f : slp %.2f", edge_pos, fret);
        util::DrawTextMsg(img, CPOS(0, 0), msg, 0, 128);

        

        CPOS* pt_list;

        pt_list = new CPOS[prj_wid];

        for (int i = 0; i < prj_wid; i++)
        {
            if (dlg.GetParam(0) == 0) // horz
            {
                pt_list[i] = CPOS((int)prj_av[i]+img.PosCenter().X(),img.Top()+i);
            }
            else
            {
                pt_list[i] = CPOS(i+img.Left(),img.PosCenter().Y()-(int)prj_av[i]);
            }
            
        }

        util::DrawPolyLine(img, pt_list, prj_wid, 0, OPEN);


        delete[] pt_list;
        delete[] prj;
        delete[] prj_av;


        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformScaleimagedemo()
{
    try
    {
        if (!m_Image.IsValid()) return;

//        CDlgParam dlg;
//        dlg.SetParam(0, _T("pitch x"), 8, _T("pixel"));
//        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, 256, 256, w);

        CStopWatch sw;
        sw.Start();

        transform::ScaleImage(img, imd);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformRotateimage()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;
        dlg.SetParam(0, _T("Roate Angle"), 100, _T("0.01 degree"));
        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

        transform::RotateImage(img, imd, CPOS(w / 2, h / 2), dlg.GetParam(0) / 100.);

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformRectangularizedemo()
{
    try
    {
        if (!m_Image.IsValid()) return;

//        CDlgParam dlg;
//        dlg.SetParam(0, _T("Roate Angle"), 100, _T("0.01 degree"));
//        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, w, h, w);

        CStopWatch sw;
        sw.Start();

//        transform::Retangularize(img, imd, CPOS(10, 10), CPOS(w - 20, 20), CPOS(20, h - 20), CPOS(w - 30, h - 30));
        transform::Retangularize(img, imd, CPOS(10, 30), CPOS(145, 55), CPOS(40, 210), CPOS(156, 213));

        sw.Stop();
        imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnTransformCorrectperspective()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;
        dlg.SetParam(0, _T("Far Left X"), 40, _T("pixel coord"));
        dlg.SetParam(1, _T("Far Left Y"), 40, _T("pixel coord"));
        dlg.SetParam(2, _T("Far Right X"), 160, _T("pixel coord"));
        dlg.SetParam(3, _T("Far Right Y"), 40, _T("pixel coord"));
        dlg.SetParam(4, _T("Near Left X"), 0, _T("pixel coord"));
        dlg.SetParam(5, _T("Near Left Y"), 200, _T("pixel coord"));
        dlg.SetParam(6, _T("Near Right X"), 200, _T("pixel coord"));
        dlg.SetParam(7, _T("Near Right Y"), 200, _T("pixel coord"));
        dlg.SetParam(8, _T("Dest Width"), 200, _T("pixel"));
        dlg.SetParam(9, _T("Near Height"), 200, _T("pixel coord"));

        if (dlg.DoModal() != IDOK) return;


        CWaitCursor WC;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CIMAGE imd(NULL, 0, 0, dlg.GetParam(8), dlg.GetParam(9), dlg.GetParam(8));

        CStopWatch sw;
        sw.Start();

        transform::CorrectPerspective(img, imd, CPOS(dlg.GetParam(0), dlg.GetParam(1)), CPOS(dlg.GetParam(2),dlg.GetParam(3))
            , CPOS(dlg.GetParam(4), dlg.GetParam(5)), CPOS(dlg.GetParam(6), dlg.GetParam(7)));


        sw.Stop();

        m_Image.Create(dlg.GetParam(8), dlg.GetParam(9), 8, CXIMAGE_FORMAT_BMP);

        m_Image.GrayScale();

        imd.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());
        UpdateImageInfo();

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(TRUE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMorphThinning()
{
    try
    {
        if (!m_Image.IsValid()) return;

        //CDlgParam dlg;
        //dlg.SetParam(0, _T("Roate Angle"), 100, _T("0.01 degree"));
        //if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CIMAGE img(NULL, 0, 0, w, h, w);

        img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        int rw;
        if (w > h) rw = h;
        else rw = w;

        CWaitCursor wtcsr;
        CStopWatch sw;


        sw.Start();

        morph::Thinning(img, img);

        sw.Stop();
        img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnChanelR()
{
    if (!m_Image.IsValid()) return;

    if (m_Image.GetBpp() < 24)
    {
        AfxMessageBox(_T("Only for Color Image above 24bit/pixel"));
        return;
    }

    CWaitCursor wtcsr;
    CStopWatch sw;


    sw.Start();

    int i, j, w,h;

    w = m_Image.GetWidth();
    h = m_Image.GetHeight();

    CIMAGE img(NULL, 0, 0, w, h, w);

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            RGBQUAD a;
            a = m_Image.GetPixelColor(i, j, FALSE);
            img(i, h-j-1) = a.rgbRed;
        }
    }

    m_Image.GrayScale();

    sw.Stop();

    img.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

    CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
    CString			strMsg;

    strMsg.Format(_T("%d bpp"), m_Image.GetBpp());
    pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);
    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());


    Invalidate(FALSE);
}


void CiSimView::OnChanelG()
{
    if (!m_Image.IsValid()) return;

    if (m_Image.GetBpp() < 24)
    {
        AfxMessageBox(_T("Only for Color Image above 24bit/pixel"));
        return;
    }

    CWaitCursor wtcsr;
    CStopWatch sw;


    sw.Start();

    int i, j, w, h;

    w = m_Image.GetWidth();
    h = m_Image.GetHeight();

    CIMAGE img(NULL, 0, 0, w, h, w);

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            RGBQUAD a;
            a = m_Image.GetPixelColor(i, j, FALSE);
            img(i, h - j - 1) = a.rgbGreen;
        }
    }

    m_Image.GrayScale();

    sw.Stop();

    img.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

    CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
    CString			strMsg;

    strMsg.Format(_T("%d bpp"), m_Image.GetBpp());
    pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);
    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());


    Invalidate(FALSE);
}


void CiSimView::OnChanelB()
{
    if (!m_Image.IsValid()) return;

    if (m_Image.GetBpp() < 24)
    {
        AfxMessageBox(_T("Only for Color Image above 24bit/pixel"));
        return;
    }

    CWaitCursor wtcsr;
    CStopWatch sw;


    sw.Start();

    int i, j, w, h;

    w = m_Image.GetWidth();
    h = m_Image.GetHeight();

    CIMAGE img(NULL, 0, 0, w, h, w);

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            RGBQUAD a;
            a = m_Image.GetPixelColor(i, j, FALSE);
            img(i, h - j - 1) = a.rgbBlue;
        }
    }

    m_Image.GrayScale();

    sw.Stop();

    img.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

    CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
    CString			strMsg;

    strMsg.Format(_T("%d bpp"), m_Image.GetBpp());
    pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);
    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());


    Invalidate(FALSE);

}


void CiSimView::OnUtilSuperimpose()
{

    CString FileName;
    CString FileExt;
    CString Filter;

    Filter = "Image File(*.bmp,*.jpg,*.png)|*.bmp;*.jpg;*.png|";
    Filter += "Bitmap (*.bmp)|*.bmp|";
    Filter += "JPG Image(*.jpg)|*.jpg|";
    Filter += "PNG Image(*.png)|*.png|";
    Filter += "All files(*.*)|*.*||";

    CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, (LPCTSTR)Filter, NULL, 0, 0);

    
    //dlg.GetNextPathName(dlg.GetStartPosition());
    int num=0;
    int* buf = NULL;
    int i, j, w, h;
        
    if (dlg.DoModal() == IDOK)
    {
        POSITION p (dlg.GetStartPosition());
        

        while (p)
        {
            FileName = dlg.GetNextPathName(p);
            m_OpenedFile = FileName;
            FileOpen(m_OpenedFile.GetBuffer());
            num++;

            if (num == 1)
            {
                w = m_Image.GetWidth();
                h = m_Image.GetHeight();
                buf = new int[w*h];
                ::ZeroMemory(buf, w*h * 4);
            }

            for (j = 0; j < h; j++)
            {
                for (i = 0; i < w; i++)
                {
                    buf[i + j*w] += m_Image.GetPixelIndex(i, j);
                }
                
            }

            //FileName = dlg.GetNextPathName(p);
        }

    }
    else
    {
        return;
    }




    CWaitCursor wtcsr;
    CStopWatch sw;


    sw.Start();

    CIMAGE img(NULL, 0, 0, w, h, w);

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            img(i, h - j - 1) = (buf[i+j*w]/num);
        }
    }

    sw.Stop();

    delete[] buf;

    img.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

    CMainFrame*		pFrame = (CMainFrame*)AfxGetMainWnd();
    CString			strMsg;

    strMsg.Format(_T("%d bpp"), m_Image.GetBpp());
    pFrame->SetPaneText(INDICATOR_BPP, (LPCTSTR)strMsg);
    ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());


    Invalidate(FALSE);

}


void CiSimView::OnAlgotestPrjcompensation()
{
    if (m_PrjType == ID_PRJ_NONE) return;

    // 0. data 확인

    CString str;

    unsigned int* prj = m_Proj.m_pData;
    int wid;

    if (m_PrjType == ID_PRJ_H)
    {
        wid = m_Tracker.GetRect().Height();
    }
    else // ID_PRJ_V
    {
        wid = m_Tracker.GetRect().Width();

    } // Horz, Vert

    try
    {
        calc::CompensateProjection(prj, prj, wid, 1, 3);
    }
    catch (const char* msg)
    {

    }

    int sx, sy, w, h,i,j;
    sx = m_Tracker.GetRect().left;
    sy = m_Tracker.GetRect().top;
    w = m_Tracker.GetRect().Width();
    h = m_Tracker.GetRect().Height();

    CIMAGE img(NULL, 0, 0, w, h, w);

    img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

    CWaitCursor wtcsr;
    CStopWatch sw;


    sw.Start();

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            img(i, j) = prj[j];
        }

    }

    sw.Stop();
    img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
    
        
    Invalidate(FALSE);
}


void CiSimView::OnAlgotestElamon()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;
        dlg.SetParam(0, _T("Roate Angle"), 0, _T("0.01 degree"));
        dlg.SetParam(1, _T("LoG Mask Size"), 25, _T("Odd Number"));
        dlg.SetParam(2, _T("LoG Sigma"), 300, _T("0.01 unit"));
        dlg.SetParam(3, _T("LoG Gain"), 70, _T("0.01 unit"));
        dlg.SetParam(4, _T("PRJ width"), 40, _T("pixel"));
        dlg.SetParam(5, _T("Detect Thre"), 20, _T("GV"));
        dlg.SetParam(6, _T("Length Thre"), 50, _T("% of ROI width"));
        dlg.SetParam(7, _T("Merge Margin"), 3, _T("pixel"));
        dlg.SetParam(8, _T("Index Thre"), 30, _T("GV"));
        dlg.SetParam(9, _T("ProcImageFlag"), 1, _T("1 or 0"));
        
        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CWaitCursor wtcsr;
        CStopWatch sw;
        CMuraMon mm;

        int ret;
        sw.Start();

        mm.SetImage(m_Image.GetBits(), m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetBpp()
            , sx, sy, sx + w, sy + h);
        mm.SetPreProcParam(dlg.GetParam(0)/100., dlg.GetParam(1), dlg.GetParam(2) / 100., dlg.GetParam(3) / 100.);
        mm.SetDetectParam(dlg.GetParam(4), dlg.GetParam(5), dlg.GetParam(6) / 100., dlg.GetParam(7), dlg.GetParam(8), dlg.GetParam(9),3);
        ret = mm.DetectMura();

        //if (ret < 1) return;
        sw.Stop();

        CString str;
        str.Format(_T("%d mura detected"), ret);
        AfxMessageBox(str);

        mm.SaveMuraImage(_T("d:\\mura.jpg"));

        
        
        CIMAGE img(mm.m_pImageData,0,0,w,h,w);

        if (m_Image.GetBpp()==8)
            img.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

        if (m_Image.GetBpp() == 24)
            img.CopyDataToDib24(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
            

        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    } 
}





void CiSimView::OnAlgotestPrint()
{
    try
    {
        if (!m_Image.IsValid()) return;

        CDlgParam dlg;
        dlg.SetParam(0, _T("Ofs x"), -9, _T("pixel"));
        dlg.SetParam(1, _T("Ofs y"), 138, _T("pixel"));
        dlg.SetParam(2, _T("Match Block Wid"), 64, _T("pixel"));
        dlg.SetParam(3, _T("Match Block Hgt"), 64, _T("pixel"));
        dlg.SetParam(4, _T("Match Margin"), 16, _T("pixel"));

        if (dlg.DoModal() != IDOK) return;

        int sx, sy, w, h;
        sx = m_Tracker.GetRect().left;
        sy = m_Tracker.GetRect().top;
        w = m_Tracker.GetRect().Width();
        h = m_Tracker.GetRect().Height();

        CWaitCursor wtcsr;
        CStopWatch sw;

        int ret;

        CxImage cx_ref;
        cx_ref.Load(_T("D:\\Doc\\2018\\02.과제\\검토\\생명과학\\표시자재\\ref_bin.jpg"));
        cx_ref.GrayScale();

             
        sw.Start();

        m_Image.GrayScale();

        CIMAGE img (NULL , 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        img.CopyDataFromDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());
        CIMAGE bin(NULL, 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        CIMAGE msk(NULL, 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        CIMAGE msk2(NULL, 0, 0, m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetWidth());
        morph::Binarize(img, bin, 180, ipl::LOW);
        morph::Dilate(bin, msk);
        transform::SubtractImage(msk, bin, msk2, 0);

        int i, j,m,n;
        int m_margin = dlg.GetParam(4);
        int blk_x = dlg.GetParam(2);
        int blk_y = dlg.GetParam(3);
        int ofs_x = dlg.GetParam(0);
        int ofs_y = dlg.GetParam(1);

        //CIMAGE ims(NULL, 0, 0, blk_x, blk_y, blk_x);
        CIMAGE ref(NULL, 0, 0, blk_x + m_margin * 2, blk_y + m_margin * 2, blk_x + m_margin * 2);
        CIMAGE ref2(NULL, 0, 0, blk_x + m_margin * 2, blk_y + m_margin * 2, blk_x + m_margin * 2);
        CIMAGE ims(img.GetImgPtr(), 0, 0, blk_x, blk_y, img.Width());

        CPOSF match_pos;
        CPOS m_pos;
        float score;
        int temp,tmin;

        for (j = m_margin; j < 1500-blk_y; j += blk_y )
        {
            for (i = m_margin; i < 3000 - blk_x; i += blk_x)
            {
                ref.CopyDataFromDib(cx_ref.GetBits(), i-m_margin+ofs_x, j-m_margin+ofs_y, cx_ref.GetHeight(), cx_ref.GetEffWidth());
                ims.SetData(img.GetImgPtr()+i+j*img.Width(), 0,0, blk_x, blk_y, img.Width());

                score = match::FindMatchPosition(ref, ims, m_pos, SSE2);
                //score = match::FindMatchPosition_Subpixel(ref, ims, match_pos, SSE2);
                //transform::TranslateImage_Subpixel(ref, ref2, -match_pos.X(), -match_pos.Y());
                tmin = 10000;
                for (n = 0; n < blk_y; n++)
                {
                    for (m = 0; m < blk_x; m++)
                    {
                        temp = ims(m, n) - ref(m+m_pos.X(), n+m_pos.Y())+128;
                        if (temp > 255) temp = 255;
                        if (temp < 0) temp = 0;
                        ims(m, n) = temp ;
                        if (msk(m + i, n + j) == 255) ims(m, n) = 128;

                        /*
                        temp = abs(ims(m, n) - ref(m+m_pos.X()-1, n+m_pos.Y()-1)) ;
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() - 1, n + m_pos.Y() ));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() - 1, n + m_pos.Y() + 1));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() , n + m_pos.Y() - 1));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() , n + m_pos.Y() ));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() , n + m_pos.Y() + 1));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() + 1, n + m_pos.Y() - 1));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() + 1, n + m_pos.Y()));
                        tmin = MIN(tmin, temp);
                        temp = abs(ims(m, n) - ref(m + m_pos.X() + 1, n + m_pos.Y() + 1));
                        tmin = MIN(tmin, temp);
                        tmin = tmin + 128;
                        if (tmin > 255) tmin = 255;
                        //if (temp < 0) temp = 0;
                        ims(m, n) = tmin;
                        */
                    }
                }
                
                
            }
        }

        //if (ret < 1) return;
        sw.Stop();

        img.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());



        ((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
        Invalidate(FALSE);


    }
    catch (const char* msg)
    {
        AfxMessageBox(CString(msg));
    }
}


void CiSimView::OnMakepdMakepddefect()
{
	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;
		dlg.SetParam(0, _T("start Pos X"), 40, _T("pixel coord"));
		dlg.SetParam(1, _T("start Pos Y"), 40, _T("pixel coord"));
		dlg.SetParam(2, _T("Start Gray Level"), 10, _T("Gray Level"));
		dlg.SetParam(3, _T("Step Gray Level"), 1, _T("Gray Level"));
		dlg.SetParam(4, _T("Count defect"), 20, _T("pixel coord"));
		dlg.SetParam(5, _T("Step Pos"), 2, _T("pixel coord"));
		dlg.SetParam(6, _T("Direction"), 1, _T("dx:1, dy:2"));
		dlg.SetParam(7, _T("Which RGB"), 1, _T("R:1 G:2 B:3"));

		if (dlg.DoModal() != IDOK) return;

		int stx = dlg.GetParam(0);
		int sty = dlg.GetParam(1);
		int stGL = dlg.GetParam(2);
		int stepGL = dlg.GetParam(3);
		int cntdft = dlg.GetParam(4);
		int stepPos = dlg.GetParam(5);
		int direct = dlg.GetParam(6);
		int nRGB = dlg.GetParam(7);

		int sx, sy, w, h;
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();
		int offset = m_Image.GetEffWidth();

		U8* ptmp = new U8[w*3*h];
		U8* psrc = m_Image.GetBits();
		U8 *pSrc_line, *pDest_line;
		int nSize = offset;
		for (int j = 0; j<h; j++)
		{
			pDest_line = ptmp+(j*offset);
			pSrc_line =psrc + (h-j-1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}


		//CIMAGE ims(img.GetImgPtr(), 0, 0, w, h,  m_Image.GetEffWidth());

		CStopWatch sw;
		sw.Start();

//		transform::CopyImage(ims, imd);

		if(direct==1)
		{
			int cnt=0;
			int glval = stGL;
			for( int i=stx ; i<w ; i=i+stepPos )
			{
				if( nRGB == 1)	//R
				{
					ptmp[sty*offset+i*3+2] = glval;
				}
				else if( nRGB == 2)
				{
					ptmp[sty*offset+(i*3)+1] = glval;
				}
				else if( nRGB == 3)
				{
					ptmp[sty*offset+(i*3)] = glval;
				}
				glval = glval+stepGL;
				cnt++;
				if( cnt >= cntdft || glval >= 256)	
					break;
			}
		}
		else if( direct == 2)
		{
			int cnt=0;
			int glval = stGL;
			for( int i=sty ; i<h ; i=i+stepPos )
			{
				if( nRGB == 1)	//R
				{
					ptmp[i*offset+stx*3+2] = glval;
				}
				else if( nRGB == 2)
				{
					ptmp[i*offset+(stx*3)+1] = glval;
				}
				else if( nRGB == 3)
				{
					ptmp[i*offset+(stx*3)] = glval;
				}
				glval = glval+stepGL;
				cnt++;
				if( cnt >= cntdft || glval >= 256)	
					break;
			}
		}
		else
			return;
		

		sw.Stop();


		for (int j = 0; j<h; j++)
		{
			pSrc_line = ptmp+(j*offset);
			pDest_line =psrc + (h-j-1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}

		delete[] ptmp;


		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);


	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}
}


void CiSimView::OnMakepdMakecalpattern()
{
	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;
		dlg.SetParam(0, _T("start Pos X"), 40, _T("pixel coord"));
		dlg.SetParam(1, _T("start Pos Y"), 40, _T("pixel coord"));
		dlg.SetParam(2, _T("Gray Level"), 255, _T("Gray Level"));
		dlg.SetParam(3, _T("CountX"), 10, _T("pixel coord"));
		dlg.SetParam(4, _T("CountY"), 20, _T("pixel coord"));
		dlg.SetParam(5, _T("StepX"), 100, _T("pixel coord"));
		dlg.SetParam(6, _T("StepY"), 100, _T("pixel coord"));
		dlg.SetParam(7, _T("Which RGB"), 1, _T("R:1 G:2 B:3, ALL:4"));
		dlg.SetParam(8, _T("size"), 1, _T("pixel coord"));
		
		if (dlg.DoModal() != IDOK) return;

		int stx = dlg.GetParam(0);
		int sty = dlg.GetParam(1);
		int GL = dlg.GetParam(2);
		int cntX = dlg.GetParam(3);
		int cntY = dlg.GetParam(4);
		int stepX = dlg.GetParam(5);
		int stepY = dlg.GetParam(6);
		int nRGB = dlg.GetParam(7);
		int sz = dlg.GetParam(8);

		int sx, sy, w, h;
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();
		int offset = m_Image.GetEffWidth();

		U8* ptmp = new U8[w*3*h];
		U8* psrc = m_Image.GetBits();
		U8 *pSrc_line, *pDest_line;
		int nSize = offset;
		for (int j = 0; j<h; j++)
		{
			pDest_line = ptmp+(j*offset);
			pSrc_line =psrc + (h-j-1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}


		//CIMAGE ims(img.GetImgPtr(), 0, 0, w, h,  m_Image.GetEffWidth());

		CStopWatch sw;
		sw.Start();

		//		transform::CopyImage(ims, imd);
		int glval = GL;
		for( int j=sty ; j<h ; j=j+stepY )
		{
			for( int i=stx ; i<w ; i=i+stepX )
			{
				for( int k=0 ; k<sz ; k++)
				{
					for( int l=0 ; l<sz ; l++)
					{
						if( nRGB == 1)	//R
						{
							ptmp[(j+k)*offset+(i+l)*3+2] = glval;
						}
						else if( nRGB == 2)
						{
							ptmp[(j+k)*offset+(i+l)*3+1] = glval;
						}
						else if( nRGB == 3)
						{
							ptmp[(j+k)*offset+(i+l)*3] = glval;
						}
						else if( nRGB == 4)
						{
							ptmp[(j+k)*offset+(i+l)*3] = glval;
							ptmp[(j+k)*offset+(i+l)*3+1] = glval;
							ptmp[(j+k)*offset+(i+l)*3+2] = glval;
						}

					}
				}
					
			}
		}

		sw.Stop();


		for (int j = 0; j<h; j++)
		{
			pSrc_line = ptmp+(j*offset);
			pDest_line =psrc + (h-j-1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}

		delete[] ptmp;


		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);


	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}



}


void CiSimView::OnMakepdMakecalpattern32898()
{
	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;
		dlg.SetParam(0, _T("start Pos X"), 40, _T("pixel coord"));
		dlg.SetParam(1, _T("start Pos Y"), 40, _T("pixel coord"));
		dlg.SetParam(2, _T("Gray Level"), 255, _T("Gray Level"));
		dlg.SetParam(3, _T("CountX"), 10, _T("pixel coord"));
		dlg.SetParam(4, _T("CountY"), 20, _T("pixel coord"));
		dlg.SetParam(5, _T("StepX"), 100, _T("pixel coord"));
		dlg.SetParam(6, _T("StepY"), 100, _T("pixel coord"));
		dlg.SetParam(7, _T("Which RGB"), 1, _T("R:1 G:2 B:3, ALL:4"));
		dlg.SetParam(8, _T("size"), 1, _T("pixel coord"));
		dlg.SetParam(9, _T("end Pos Y"), 50, _T("pixel coord"));

		if (dlg.DoModal() != IDOK) return;

		int stx = dlg.GetParam(0);
		int sty = dlg.GetParam(1);
		int GL = dlg.GetParam(2);
		int cntX = dlg.GetParam(3);
		int cntY = dlg.GetParam(4);
		int stepX = dlg.GetParam(5);
		int stepY = dlg.GetParam(6);
		int nRGB = dlg.GetParam(7);
		int sz = dlg.GetParam(8);
		int eny = dlg.GetParam(9);

		int sx, sy, w, h;
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();
		int offset = m_Image.GetEffWidth();

		U8* ptmp = new U8[w * 3 * h];
		U8* psrc = m_Image.GetBits();
		U8 *pSrc_line, *pDest_line;
		int nSize = offset;
		for (int j = 0; j < h; j++)
		{
			pDest_line = ptmp + (j*offset);
			pSrc_line = psrc + (h - j - 1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}

		int thickness = sz / 3;
		stepX = (w- (stx+stx+sz) ) / (cntX-1);
		stepY = (h- (sty+eny+sz) ) / (cntY-1);
		
		//CIMAGE ims(img.GetImgPtr(), 0, 0, w, h,  m_Image.GetEffWidth());

		CStopWatch sw;
		sw.Start();

		//		transform::CopyImage(ims, imd);
		int glval = GL;
		int cntXX = 0, cntYY = 0;
		for (int j = sty; j < h-sz; j = j + stepY)
		{
			if (cntYY == cntY)
				break;
			cntXX = 0;
			for (int i = stx; i < w-sz; i = i + stepX)
			{
				if (cntXX == cntX)
					break;
				for (int k = 0; k < sz; k++)
				{
					for (int l = thickness; l < thickness*2 ; l++)
					{
						if (nRGB == 1)	//R
						{
							ptmp[(j + k)*offset + (i + l) * 3 + 2] = glval;
						}
						else if (nRGB == 2)
						{
							ptmp[(j + k)*offset + (i + l) * 3 + 1] = glval;
						}
						else if (nRGB == 3)
						{
							ptmp[(j + k)*offset + (i + l) * 3] = glval;
						}
						else if (nRGB == 4)
						{
							ptmp[(j + k)*offset + (i + l) * 3] = glval;
							ptmp[(j + k)*offset + (i + l) * 3 + 1] = glval;
							ptmp[(j + k)*offset + (i + l) * 3 + 2] = glval;
						}

					}
				}
				for (int k = thickness; k < thickness*2; k++)
				{
					for (int l = 0; l < sz; l++)
					{
						if (nRGB == 1)	//R
						{
							ptmp[(j + k)*offset + (i + l) * 3 + 2] = glval;
						}
						else if (nRGB == 2)
						{
							ptmp[(j + k)*offset + (i + l) * 3 + 1] = glval;
						}
						else if (nRGB == 3)
						{
							ptmp[(j + k)*offset + (i + l) * 3] = glval;
						}
						else if (nRGB == 4)
						{
							ptmp[(j + k)*offset + (i + l) * 3] = glval;
							ptmp[(j + k)*offset + (i + l) * 3 + 1] = glval;
							ptmp[(j + k)*offset + (i + l) * 3 + 2] = glval;
						}

					}
				}
				cntXX++;
			}
			cntYY++;
		}

		sw.Stop();


		for (int j = 0; j < h; j++)
		{
			pSrc_line = ptmp + (j*offset);
			pDest_line = psrc + (h - j - 1)*offset;
			memcpy_s(pDest_line, nSize, pSrc_line, nSize);
		}

		delete[] ptmp;


		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);


	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}


}


void CiSimView::OnCosmetictestMergeimage()
{



	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;
		dlg.SetParam(0, _T("img1 - shiftX"), m_mergeParam[0], _T("pixel coord"));
		dlg.SetParam(1, _T("img1 - shiftY"), m_mergeParam[1], _T("pixel coord"));
		dlg.SetParam(2, _T("img2 - shiftX"), m_mergeParam[2], _T("pixel coord"));
		dlg.SetParam(3, _T("img2 - shiftY"), m_mergeParam[3], _T("pixel coord"));
		dlg.SetParam(4, _T("img3 - shiftX"), m_mergeParam[4], _T("pixel coord"));
		dlg.SetParam(5, _T("img3 - shiftY"), m_mergeParam[5], _T("pixel coord"));
		dlg.SetParam(6, _T("img4 - shiftX"), m_mergeParam[6], _T("pixel coord"));
		dlg.SetParam(7, _T("img4 - shiftY"), m_mergeParam[7], _T("pixel coord"));
		dlg.SetParam(8, _T("size"), 1, _T("pixel coord"));
		dlg.SetParam(9, _T("end Pos Y"), 50, _T("pixel coord"));

		if (dlg.DoModal() != IDOK) return;

		for( int i=0 ; i<9 ; i++)
			m_mergeParam[i] = dlg.GetParam(i);

		int x1 = dlg.GetParam(0);
		int y1 = dlg.GetParam(1);
		int x2 = dlg.GetParam(2);
		int y2 = dlg.GetParam(3);
		int x3 = dlg.GetParam(4);
		int y3 = dlg.GetParam(5);
		int x4 = dlg.GetParam(6);
		int y4 = dlg.GetParam(7);
		
		int wid = 9000;
		int hgt = 18000;

		U8* pImg = new U8[wid*hgt];
		CIMAGE base(pImg, 0, 0, wid, hgt, wid);

		CxImage ref;
		int res = ref.Load(_T("d:\\4.bmp"));
		ref.GrayScale();

		int widref = ref.GetWidth();
		int hgtref = ref.GetHeight();
		CIMAGE cref(NULL, 0, 0, widref, hgtref, widref);
		cref.CopyDataFromDib(ref.GetBits(), 0, 0, ref.GetHeight(), ref.GetEffWidth());
		U8* pref = cref.GetImgPtr();
		int wid1 = m_ImgWid;
		int hgt1 = m_ImgHgt;
		
		CIMAGE img(NULL, 0, 0, wid1, hgt1, wid1);
		img.CopyDataFromDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());
		U8* prefImg = img.GetImgPtr();

		int cpywid1 = wid / 2; //wid1 + x1;
		int cpywid2 = wid / 2; //wid - cpywid1;
		int t = cpywid1 - x2;

		int sty1 = y1;
		int sty2 = y2;

		int cpyhgt = y1 < y2 ? hgt1 - y2 : hgt1 - y1;

		for (int j = 0; j < cpyhgt; j++)
		{
			memcpy(pImg + (j*wid), prefImg - x1 + ( (sty1+j)*wid1), cpywid1);
			memcpy(pImg + cpywid1 + (j*wid), pref + x2 + ( (sty2+j)*wid1), cpywid2);
		
		}

		CxImage imgs(wid, hgt, 8, CXIMAGE_FORMAT_BMP);
		imgs.GrayScale();
		base.CopyDataToDib(imgs.GetBits(), 0, 0, imgs.GetHeight(), imgs.GetEffWidth());

		imgs.Save(_T("d:/merge.bmp"), CXIMAGE_FORMAT_BMP);
		delete[] pImg;
	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}

}


void CiSimView::OnCosmetictestPitchcomparemin()
{
	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;

		dlg.SetParam(0, _T("pitch x"), 20, _T("pixel"));
		dlg.SetParam(1, _T("pitch y"), 30, _T("pixel"));
		dlg.SetParam(2, _T("gain"), 100, _T(" / 100"));
		dlg.SetParam(3, _T("boundary flag"), 2, _T("NONE==0/FILL_CONST==1 / APPROX==2"));

		if (dlg.DoModal() != IDOK) return;

		int sx, sy, w, h;
		
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();

		m_Image.GrayScale();
		if (w < 10 || h < 10)
		{
			sx = 0;
			sy = 0;
			w = m_Image.GetEffWidth();
			h = m_Image.GetHeight();
		}

		CIMAGE img(NULL, 0, 0, w, h, w);

		img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		int rw;
		if (w > h) rw = h;
		else rw = w;

		CIMAGE imd(NULL, 0, 0, w, h, w);
		CIMAGE imd2(NULL, 0, 0, w, h, w);
		CIMAGE roi(NULL, 0, 0, w, h, w);

		CStopWatch sw;
		sw.Start();

	/*	CxImage cxROI;
		cxROI.Load(_T("e4.bmp"), 1);
		cxROI.GrayScale();
		roi.CopyDataFromDib(cxROI.GetBits(), sx, sy, cxROI.GetHeight(), cxROI.GetEffWidth());
	//	cxROI.Save(_T("roisave.bmp"), 1);
	*/
		memset(roi.GetImgPtr(), 255, w*h);
		CAlgProc alp;
//		alp.fnDiffMin_VERT(img.GetImgPtr(), imd2.GetImgPtr(), proi, w, h, 20, 32, 0, 0, w, h);

		alp.fnDiffMin(img.GetImgPtr(), imd2.GetImgPtr(), roi.GetImgPtr(), w, h, dlg.GetParam(0), dlg.GetParam(1), 0, 0, w, h);

		ipl::filter::Median(imd2, imd, 3);

		sw.Stop();
		imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
	//	imd.CopyDataToDib(proi, 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());


		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);
	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}

}


void CiSimView::OnFeatureinfoDefocusindex()
{
	try
	{
		if (!m_Image.IsValid()) return;

		int sx, sy, w, h;

		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();

		if (w < 10 || h < 10)
		{
			sx = 0;
			sy = 0;
			w = m_Image.GetEffWidth();
			h = m_Image.GetHeight();
		}

		CIMAGE img(NULL, 0, 0, w, h, w);

		img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		int rw;
		if (w > h) rw = h;
		else rw = w;

		CStopWatch sw;
		sw.Start();

		CAlgProc alp;
		int index = alp.Defocus_Index(img.GetImgPtr(), w, h, w, 1, 15);
		sw.Stop();
		//imd.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());
		CString str;
		str.Format(_T("defocus index : %d"), index);
		AfxMessageBox(str);

		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);
	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}

}


void CiSimView::OnFeatureinfoGetallfeature()
{
	try
	{
		if (!m_Image.IsValid()) return;

		int sx, sy, w, h;

		int off = 4;

		sx = m_Tracker.GetRect().left- off;
		sy = m_Tracker.GetRect().top- off;
		w = m_Tracker.GetRect().Width()+ off+ off;
		h = m_Tracker.GetRect().Height()+ off+ off;

		if (w < 10 || h < 10)
		{
			sx = 0;
			sy = 0;
			w = m_Image.GetEffWidth();
			h = m_Image.GetHeight();
		}

		CIMAGE img(NULL, 0, 0, w, h, w);

		img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		int rw;
		if (w > h) rw = h;
		else rw = w;

		CStopWatch sw;
		sw.Start();

		int threH = 128 + 15;
		int threL = 128 - 15;

		int widnorm = 48;
		CIMAGE norm(NULL, 0, 0, widnorm, widnorm, widnorm);
		ipl::transform::ScaleImage(img, norm);

		CAlgProc alp;
		int index = alp.Defocus_Index(img.GetImgPtr(), widnorm, widnorm, widnorm, 1, 15);


		std::vector<IMGINFO> vImg;
		alp.GetImageInfo(img, 128+15, vImg, ipl::LO_HI_FLAG::HIGH);

		CRECT rt(0, 0, w, h);
		int dirAngle = 0, dtotalA=0;
		double dAA, dBB, dstdA ;
		double dR_squared = alp.Get_R_Squared_1st(vImg, &dirAngle, rt, &dAA, &dBB);
		double dProj_density = alp.GetLinetDensity(img.GetImgPtr(), threH, ipl::LO_HI_FLAG::HIGH, w, h, 0, 0, w, h, dAA, dBB);
		double dR_squared_2nd = alp.Get_R_Squared_2nd(vImg, dirAngle, rt);
		double dtotalAngle = alp.GetEdgeAngle(img.GetImgPtr(), w, h, rt, &dtotalA, 15, &dstdA);

		sw.Stop();
		
		norm.CopyDataToDib(m_Image.GetBits(), 0, 0, m_Image.GetHeight(), m_Image.GetEffWidth());
		
		CString str;
		str.Format(_T("defocus index : %d \r\n Rsqaured : %.3f \r\n Rsqaured2nd : %.3f \r\n prj_density : %.3f \r\n totalAngle : %d, \r\n stdAngle : %.3f"), 
			index, dR_squared, dR_squared_2nd, dProj_density, dtotalA, dstdA);
		AfxMessageBox(str);

		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);
	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}

}


void CiSimView::OnFeatureinfoDetection()
{
	try
	{
		if (!m_Image.IsValid()) return;

		int sx, sy, w, h;

		int off = 0;

		sx = m_Tracker.GetRect().left - off;
		sy = m_Tracker.GetRect().top - off;
		w = m_Tracker.GetRect().Width() + off + off;
		h = m_Tracker.GetRect().Height() + off + off;

		CPoint pt = m_Tracker.GetRect().CenterPoint();
		int index = pt.x / 256;

		sx = sx - 256 * index;
		if (w < 10 || h < 10)
		{
			sx = 0;
			sy = 0;
			w = m_Image.GetEffWidth();
			h = m_Image.GetHeight();
		}

		CIMAGE roi[8];
		int wid = 256;
		int hgt = m_Image.GetHeight();

		CIMAGE img[9];
		for (int i = 0; i < 8; i++)
		{
			img[i].SetData(NULL, CRECT(0, 0, wid-1, hgt-1), wid);
			img[i].CopyDataFromDib(m_Image.GetBits(), i*wid, 0, m_Image.GetHeight(), m_Image.GetEffWidth());
		}

		for (int i = 0; i < 8; i++)
		{
			roi[i].SetData(img[i].GetImgPtr(), sx, sy+((index-i)*4) , w, h, wid);
		}

		int rw;
		if (w > h) rw = h;
		else rw = w;

		CStopWatch sw;
		sw.Start();

		CAlgProc alp;
		int refSum = alp.GetSumofImg(roi[index]);
	
		float sumArr[8] = { 0 };
		sumArr[index] = 1;
		for (int i = 0; i < 8; i++)
		{
			//if (i == index)	continue;

			int tmpSum = alp.GetSumofImg(roi[i]);
			sumArr[i] = (float)tmpSum / (float)refSum;

			char ch[32];
			sprintf(ch, "%.2f", sumArr[i]);
			util::DrawTextMsg(img[i], CPOS(0, 0), ch, 255, 0);
		}


		

		sw.Stop();

		for (int i = 0; i < 8; i++)
		{


			img[i].CopyDataToDib(m_Image.GetBits(), i*wid, 0, m_Image.GetHeight(), m_Image.GetEffWidth());

		}


		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);
	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}
}


void CiSimView::OnCosmetictestNormalize()
{
	try
	{
		if (!m_Image.IsValid()) return;

		CDlgParam dlg;

		dlg.SetParam(0, _T("win size"), 3, _T("N x N pixel"));

		if (dlg.DoModal() != IDOK) return;

		int sx, sy, w, h;
		sx = m_Tracker.GetRect().left;
		sy = m_Tracker.GetRect().top;
		w = m_Tracker.GetRect().Width();
		h = m_Tracker.GetRect().Height();

		CIMAGE img(NULL, 0, 0, w, h, w);

		img.CopyDataFromDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		CIMAGE imt(NULL, 0, 0, w, h, w);
		CIMAGE imt2(NULL, 0, 0, w, h, w);

		CStopWatch sw;
		sw.Start();

		// filter::Median(img, imt,dlg.GetParam(0));
		CAlgProc alg;
		alg.fnMedianFilter(img, imt2, dlg.GetParam(0), dlg.GetParam(0));

		ipl::transform::SubtractImage(img, imt2, imt, 128);

		sw.Stop();
		imt.CopyDataToDib(m_Image.GetBits(), sx, sy, m_Image.GetHeight(), m_Image.GetEffWidth());

		((CMainFrame*)AfxGetMainWnd())->SetPaneText(INDICATOR_TIME, sw.GetStrElapsed());
		Invalidate(FALSE);

	}
	catch (const char* msg)
	{
		AfxMessageBox(CString(msg));
	}
}

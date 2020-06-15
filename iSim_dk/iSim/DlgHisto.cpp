// DlgHisto.cpp : implementation file
//

#include "stdafx.h"
#include "iSim.h"
#include "DlgHisto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto dialog


CDlgHisto::CDlgHisto(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHisto::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHisto)
	m_nLowBound = 0;
    m_nHighBound = 255;
	m_fGamma = 1.0;
	//}}AFX_DATA_INIT
}


void CDlgHisto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHisto)
	DDX_Text(pDX, IDC_EDIT1, m_nLowBound);
	DDX_Text(pDX, IDC_EDIT3, m_nHighBound);
	DDX_Text(pDX, IDC_EDIT2, m_fGamma);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgHisto, CDialog)
	//{{AFX_MSG_MAP(CDlgHisto)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto message handlers

void CDlgHisto::OnPaint() 
{
	CPaintDC dc(this); // device context for painting


	DrawHisto();
    
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgHisto::DrawHisto()
{

    CDC* pDC;
     
    pDC = (GetDlgItem(IDC_HISTO_PANEL)) -> GetDC();

    CPen pen(PS_SOLID,1,RGB(0,0,150));
    CPen* pOldPen;
    pOldPen = pDC->SelectObject(&pen);

    CBrush br(RGB(220, 250, 220)); 
	CBrush* pOldBrush;
    pOldBrush=pDC->SelectObject(&br);

    CRect rect;
    (GetDlgItem(IDC_HISTO_PANEL))->GetClientRect(&rect);

    int i, idx, idy, HistoBase;



    HistoBase = rect.Height() - 20 ;
    idx = 30;
    idy = HistoBase+2;

	pDC->Rectangle(&rect);
    

    int top;

    pDC->MoveTo(idx,idy);
    pDC->LineTo(idx+256,idy);

    for(i=0;i<256;i+=10)
    {
        pDC->MoveTo(idx+i,idy);
        pDC->LineTo(idx+i,idy+5);
    }
    for(i=0;i<256;i+=50)
    {
        pDC->MoveTo(idx+i,idy);
        pDC->LineTo(idx+i,idy+10);
    }

    for(i=0;i<256;i++)
    {
        pDC->MoveTo(idx+i,HistoBase);
        top = HistoBase-HistoData[i];
        if (top<0) top = 0;
        pDC->LineTo(idx+i,top);
    }


    pDC->SelectObject(pOldPen);
    ::DeleteObject((HPEN)pen);
    pDC->SelectObject(pOldBrush);
    ::DeleteObject((HBRUSH)br);

    ReleaseDC(pDC);

}

void CDlgHisto::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	CDialog::OnOK();
}

BOOL CDlgHisto::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

  UpdateData(FALSE);

  unsigned int max = 0;
  float scale;
  for(int i=0;i<256;i++)
      if (max<HistoData[i] ) max = HistoData[i];
  scale = (float)256./(float)max;
  for(int i=0;i<256;i++)
    HistoData[i] = (unsigned int)((float)HistoData[i]*scale);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

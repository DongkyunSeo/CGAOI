#include "StdAfx.h"
#include "PrjDraw.h"


CPrjDraw::CPrjDraw(void)
{
  m_rectPrev = CRect(0,0,0,0);
  m_nTypePrev = -1;
  m_pData = NULL;
}


CPrjDraw::~CPrjDraw(void)
{
  if (m_pData != NULL ) delete [] m_pData;

}



void CPrjDraw::Init(void)
{
  m_rectPrev = CRect(0,0,0,0);
  m_nTypePrev = -1;
}


int CPrjDraw::GetMem(int nDataNum)
{
  if (m_pData != NULL ) delete [] m_pData;

  m_pData = new unsigned int[nDataNum];

  return 0;
}

void CPrjDraw::DrawProjHorz(CDC* pDC, CRect rectRoi, int iwid, int ihgt)
{
  int i;
  CPen	penY,penG,penDG;
  CPen* pOldPen;

  VERIFY(penY.CreatePen(PS_SOLID,1,RGB(224,224,0))  );
  VERIFY(penG.CreatePen(PS_SOLID,1,RGB(  0,255,0))  );
  VERIFY(penDG.CreatePen(PS_SOLID,1,RGB(  0,200,0)) );

  int w,h,t,l;

  w=rectRoi.Width();
  h=rectRoi.Height();
  t=rectRoi.top;
  l=rectRoi.left;

  if (w < 1) return;
  if (h < 1) return;


  if (l+255 > iwid && l-255 > 0) l = l+w-255;
  

  pOldPen=pDC->SelectObject(&penDG);
  for (i=0;i<255;i+=50)
  {
    pDC->MoveTo(l+i,t);
    pDC->LineTo(l+i,t+h);
  }
  pOldPen=pDC->SelectObject(&penY);
    i=128;

    pDC->MoveTo(l+i,t);
    pDC->LineTo(l+i,t+h);

  pOldPen=pDC->SelectObject(&penG);
  for (i=1;i<h;i++)
  {
    pDC->MoveTo(l+m_pData[i-1],t+i-1);
    pDC->LineTo(l+m_pData[i  ],t+i);
  }

  VERIFY(penY.DeleteObject());
  VERIFY(penG.DeleteObject());  
  VERIFY(penDG.DeleteObject());
}

void CPrjDraw::DrawProjVert(CDC* pDC, CRect rectRoi, int iwid, int ihgt)
{
  int i;
  CPen	penY,penG,penDG;
  CPen* pOldPen;

  VERIFY(penY.CreatePen(PS_SOLID,1,RGB(224,224,0)) );
  VERIFY(penG.CreatePen(PS_SOLID,1,RGB(  0,255,0)) );
  VERIFY(penDG.CreatePen(PS_SOLID,1,RGB(  0,200,0)) );

  int w,h,t,l;

  w=rectRoi.Width();
  h=rectRoi.Height();
  t=rectRoi.top;
  l=rectRoi.left;

  if (w < 1) return;
  if (h < 1) return;


  if (t<255) h=255;

  pOldPen=pDC->SelectObject(&penDG);
  for (i=0;i<255;i+=50)
  {
    pDC->MoveTo(l  ,t+h-i);
    pDC->LineTo(l+w,t+h-i);
  }
  pOldPen=pDC->SelectObject(&penY);
    i=128;

    pDC->MoveTo(l  ,t+h-i);
    pDC->LineTo(l+w,t+h-i);

  pOldPen=pDC->SelectObject(&penG);
  for (i=1;i<w;i++)
  {
    pDC->MoveTo(l+i-1,t+h-m_pData[i-1]);
    pDC->LineTo(l+i  ,t+h-m_pData[i  ]);
  }

  VERIFY(penY.DeleteObject());
  VERIFY(penG.DeleteObject());  
  VERIFY(penDG.DeleteObject());

}


BOOL CPrjDraw::IsChanged(CRect rectRoi, int nPrjType)
{
  if (rectRoi != m_rectPrev || nPrjType != m_nTypePrev )
  {
    m_rectPrev = rectRoi;
    m_nTypePrev = nPrjType;

    return TRUE;
  }
  else
    return FALSE;
}

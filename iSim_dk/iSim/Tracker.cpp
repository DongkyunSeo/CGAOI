#include "stdafx.h"
#include "Tracker.h"

//������
CTracker::CTracker()
{
	m_rect=CRect(0,0,0,0);
	m_bDown=FALSE;
	m_pWnd=NULL;
	m_nMode=1;
	m_nLineDot=1;
	m_nLineThick=1;
	m_nHandleNum=-1;
	m_bHandleSet=FALSE;
	m_OldPoint=CPoint(0,0);
	m_ScrollPos=CPoint(0,0);
	
}
CTracker::CTracker(CWnd *pWnd,int dot,int thick)
{
	m_rect=CRect(0,0,1,1);
	m_pWnd=pWnd;
	m_bDown=FALSE;
	m_nMode=1;
	m_nLineDot=dot;
	m_nLineThick=thick;
	m_nHandleNum=-1;
	m_bHandleSet=FALSE;
	m_OldPoint=CPoint(0,0);
	m_ScrollPos=CPoint(0,0);


}
//�����ڽ��׸���
void CTracker::Draw(CDC* pDC)
{
	if(m_rect.left==0 && m_rect.top==0 && m_rect.bottom==0 && m_rect.right==0)
		return;

  if (m_bShow==FALSE) return;

//  CDC* pDC=m_pWnd->GetDC();

	CPen pen,*oldPen;
	CBrush brush,*oldBrush;


  //pDC->SetROP2(R2_XORPEN);

	pen.CreatePen(PS_SOLID,m_nLineThick,RGB(0,255,0));
	oldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(m_rect.left ,m_rect.top);
	pDC->LineTo(m_rect.right,m_rect.top);
	pDC->LineTo(m_rect.right,m_rect.bottom);
	pDC->LineTo(m_rect.left ,m_rect.bottom);
	pDC->LineTo(m_rect.left ,m_rect.top);


	pDC->SetROP2(R2_COPYPEN);
	brush.CreateSolidBrush(RGB(100,255,100));
	oldBrush=pDC->SelectObject(&brush);

  //8�� ������ �ڽ��� �׸���.
	for( int i=0;i<8;i++)
		pDC->Rectangle(m_rectHandle[i]);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	pDC->SelectObject(oldBrush);
	brush.DeleteObject();

//  m_pWnd->ReleaseDC(pDC);
}

//�����ڽ��� 8�� ���� ������ �̵�������
//���콺 �����Ͱ� �ִ°��� ã�� �Լ�
int CTracker::PtInHandle(CPoint point)
{
	//12���� �ڵ� ���� ������ �ش� ��ȣ��
	//�����Ѵ�.
	for(int i=0;i<12;i++)
		if(m_rectHandle[i].PtInRect(point))
		{
			return i;
		}
	
	return -1; //���� �ڽ� �ڵ� �������� �ƴϸ� -1�� ����
}
//�ش� ���⿡ ���� ���콺 Ŀ���� �����Ѵ�.

#ifndef GCL_HCURSOR
	#define GCL_HCURSOR -12
#endif

void CTracker::SetMouseCursor()
{
	switch(m_nHandleNum)
	{
		case 0:
		case 2:
				SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNWSE));
				break;
		case 1:
		case 3:
				SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNESW));
				break;
		case 4:
		case 5:
				SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKNS));
				break;
		case 6:
		case 7:
				SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACKWE));
				break;
		case 8:
		case 9:
		case 10:
		case 11:
				SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(AFX_IDC_TRACK4WAY));
				break;
		default:
			SetClassLongPtr(m_pWnd->m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
				break;
	}
}
//���콺 �̵���
void CTracker::OnMouseMove(UINT nFlags, CPoint point)
{

  point += m_ScrollPos;
	
	if(m_bDown && m_nMode!=0)
	{
		m_rectTrack.right=point.x;
		m_rectTrack.bottom=point.y;

    Redraw();

	}
	if(m_nMode==0 && !m_bDown && m_bHandleSet)
	{
		m_nHandleNum=PtInHandle(point);
		SetMouseCursor();
	}
	else if(m_nMode==0 && m_bHandleSet)
	{
		//�����ڽ� ������ �ƴϸ� ����
		if(m_nHandleNum<0)
			return;
		//�����ڽ� �����ϰ��
		switch(m_nHandleNum)
		{
			case 0://���� ��� ���ý�
					m_rectTrack.left=point.x;
					m_rectTrack.top=point.y;
					break;
			case 1://���� ��� ���ý�
					m_rectTrack.right=point.x;
					m_rectTrack.top=point.y;
					break;
			case 2://���� �ϴ� ���ý�
					m_rectTrack.right=point.x;
					m_rectTrack.bottom=point.y;
					break;
			case 3://���� �ϴ� ���ý�
					m_rectTrack.left=point.x;
					m_rectTrack.bottom=point.y;
					break;
			case 4://��������
					m_rectTrack.top=point.y;
					break;
			case 5://�Ʒ���
					m_rectTrack.bottom=point.y;
					break;
			case 6://��������
					m_rectTrack.left=point.x;
					break;
			case 7://��������
					m_rectTrack.right=point.x;
					break;
					//�̵��ϰ��
			case 8:case 9:case 10:case 11:
				{
					CPoint def;
					def                =point-m_OldPoint;
					m_rectTrack.top   +=def.y;
					m_rectTrack.bottom+=def.y;
					m_rectTrack.left  +=def.x;
					m_rectTrack.right +=def.x;
					m_OldPoint         =point;
				}
					break;
		} //switch

    Redraw();


	}


}
//���콺 ��ư ��������
void CTracker::OnLButtonDown(UINT nFlags, CPoint point)
{
  point += m_ScrollPos;

  if (PtInHandle(point)==-1) 
    m_nMode = 1;
  else  
    m_nMode = 0;

	if(m_nHandleNum<0)
	{
		//ȭ��ǥ Ŀ�� ����
		SetClassLong(m_pWnd->m_hWnd,GCL_HCURSOR,(long)LoadCursor(NULL,IDC_ARROW));
		//m_rectTrack�� m_rectOld�� ���� point�� �������� ����
		m_rectTrack.left=point.x;
		m_rectTrack.right=point.x;
		m_rectTrack.top=point.y;
		m_rectTrack.bottom=point.y;
		m_rectOld=m_rectTrack;
	}
	//m_OldPoint�� point�� ����
	m_OldPoint=point;
	m_bDown=TRUE;
}
//���콺 ��ư ����
void CTracker::OnLButtonUp(UINT nFlags, CPoint point)
{

  point += m_ScrollPos;

/*
	CDC* pDC=m_pWnd->GetDC();
	CPen pen,*oldPen;
	pDC->SetROP2(R2_XORPEN);
	pen.CreatePen(PS_DOT,1,RGB(0,255,0));
	oldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(m_rectOld.left,m_rectOld.top);
	pDC->LineTo(m_rectOld.right,m_rectOld.top);
	pDC->LineTo(m_rectOld.right,m_rectOld.bottom);
	pDC->LineTo(m_rectOld.left,m_rectOld.bottom);
	pDC->LineTo(m_rectOld.left,m_rectOld.top);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	m_pWnd->ReleaseDC(pDC);
*/
	m_rectOld=CRect(0,0,0,0);
  SetRect(m_rectTrack);
  m_nMode = 0;
	m_bDown=FALSE;
}

//12���� ������ ����� �ش�.
void CTracker::MakeHandle()
{
	m_rect=CRect(min(m_rect.left,m_rect.right),
				       min(m_rect.top,m_rect.bottom),
				       max(m_rect.left,m_rect.right),
				       max(m_rect.top,m_rect.bottom));
	m_rectTrack=m_rect;

	int pos;
	m_rectHandle[0]=CRect(m_rect.left - m_nLineDot, m_rect.top - m_nLineDot,
		                    m_rect.left + m_nLineDot, m_rect.top + m_nLineDot);
	m_rectHandle[1]=CRect(m_rect.right -m_nLineDot, m_rect.top -m_nLineDot,
			                  m_rect.right +m_nLineDot, m_rect.top +m_nLineDot);

	m_rectHandle[2]=CRect(m_rect.right - m_nLineDot, m_rect.bottom - m_nLineDot,
		                    m_rect.right + m_nLineDot, m_rect.bottom + m_nLineDot);

	m_rectHandle[3]=CRect(m_rect.left - m_nLineDot, m_rect.bottom - m_nLineDot,
		                    m_rect.left + m_nLineDot, m_rect.bottom + m_nLineDot);

	pos=(m_rect.Width()/2)+m_rect.TopLeft().x;
	m_rectHandle[4]=CRect(pos - m_nLineDot, m_rect.top - m_nLineDot,
		                    pos + m_nLineDot, m_rect.top + m_nLineDot);
	pos=(m_rect.Width()/2)+m_rect.TopLeft().x;
	m_rectHandle[5]=CRect(pos - m_nLineDot, m_rect.bottom - m_nLineDot,
		                    pos + m_nLineDot, m_rect.bottom + m_nLineDot);
	pos=(m_rect.Height()/2)+m_rect.TopLeft().y;
	m_rectHandle[6]=CRect(m_rect.left - m_nLineDot, pos - m_nLineDot,
		                    m_rect.left + m_nLineDot, pos + m_nLineDot);
	m_rectHandle[7]=CRect(m_rect.right- m_nLineDot, pos - m_nLineDot,
		                    m_rect.right+ m_nLineDot, pos + m_nLineDot);

	m_rectHandle[8] =CRect(m_rect.left, m_rect.top - m_nLineDot,
		                     m_rect.right,m_rect.top + m_nLineDot);
	m_rectHandle[9] =CRect(m_rect.left - m_nLineDot,m_rect.top,
		                     m_rect.left + m_nLineDot,m_rect.bottom);
	m_rectHandle[10]=CRect(m_rect.right - m_nLineDot,m_rect.top,
		                     m_rect.right + m_nLineDot,m_rect.bottom);
	m_rectHandle[11]=CRect(m_rect.left, m_rect.bottom - m_nLineDot,
		                     m_rect.right,m_rect.bottom + m_nLineDot);

  m_bHandleSet=TRUE; 	//8�� ������ ������ �����Ǹ� m_bHandleSet�� TRUE��

}
//�����ڽ�  ������ �����Ѵ�.
void CTracker::SetRect(CRect rect)
{
	m_rect=rect;
	m_rect=CRect(min(m_rect.left,m_rect.right),
				       min(m_rect.top,m_rect.bottom),
				       max(m_rect.left,m_rect.right),
				       max(m_rect.top,m_rect.bottom));
	m_rectTrack=m_rect;

  MakeHandle();
}

void CTracker::SetCWnd(CWnd *pWnd)
{
	m_pWnd=pWnd;

}


void CTracker::Reset(void)
{
  SetRect(CRect(0,0,0,0));
}


void CTracker::Redraw(void)
{
  CRect rectTemp;

	rectTemp=m_rectTrack;

  m_rectOld  -=m_ScrollPos;
	m_rectTrack-=m_ScrollPos;

	CDC* pDC=m_pWnd->GetDC();
	CPen pen,*oldPen;
	pDC->SetROP2(R2_XORPEN);
	//���� �׷��� ���� �����
	pen.CreatePen(PS_DOT,1,RGB(0,200,0));
	oldPen=pDC->SelectObject(&pen);
	pDC->MoveTo(m_rectOld.left,m_rectOld.top);
	pDC->LineTo(m_rectOld.right,m_rectOld.top);
	pDC->LineTo(m_rectOld.right,m_rectOld.bottom);
	pDC->LineTo(m_rectOld.left,m_rectOld.bottom);
	pDC->LineTo(m_rectOld.left,m_rectOld.top);
		
	//���ο� ������ �׸���.
	pDC->MoveTo(m_rectTrack.left,m_rectTrack.top);
	pDC->LineTo(m_rectTrack.right,m_rectTrack.top);
	pDC->LineTo(m_rectTrack.right,m_rectTrack.bottom);
	pDC->LineTo(m_rectTrack.left,m_rectTrack.bottom);
	pDC->LineTo(m_rectTrack.left,m_rectTrack.top);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	m_rectTrack=rectTemp;

	m_rectOld=m_rectTrack;
	m_pWnd->ReleaseDC(pDC);
}


CRect CTracker::GetRect(void)
{
  return m_rect;
}


void CTracker::Hide(void)
{
  m_bShow = FALSE;
}


void CTracker::Show(void)
{
   m_bShow = TRUE;
}


CRect CTracker::GetCurRect(void)
{
  return m_rectTrack;
}

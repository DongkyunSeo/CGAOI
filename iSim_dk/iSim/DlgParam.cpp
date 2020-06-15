// DlgParam.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "iSim.h"
#include "DlgParam.h"
#include "afxdialogex.h"

#define MAX_PARAM 10

// CDlgParam 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgParam, CDialogEx)

CDlgParam::CDlgParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgParam::IDD, pParent)
{
  for(int i= 0;i<MAX_PARAM;i++)
    m_nParam[i] = 0;
}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
END_MESSAGE_MAP()


// CDlgParam 메시지 처리기입니다.

int CDlgParam::SetParam(int index, CString strParam, int nParam, CString strComment)
{
  m_strParam[index] = strParam;
  m_strComment[index] = strComment;
  m_nParam[index] = nParam;

  return 0;
}


BOOL CDlgParam::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // TODO:  여기에 추가 초기화 작업을 추가합니다.
  for(int i=0;i<MAX_PARAM;i++)
  {
    SetDlgItemText(IDC_STC_PARAM1+i,m_strParam[i]);
    SetDlgItemText(IDC_STC_COMMENT1+i,m_strComment[i]);
    SetDlgItemInt(IDC_EDIT_PARAM1+i,m_nParam[i]);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgParam::OnOK()
{
  // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
  for(int i=0;i<MAX_PARAM;i++)
  {
    m_nParam[i]= GetDlgItemInt(IDC_EDIT_PARAM1+i,NULL,TRUE);
  }

  CDialogEx::OnOK();
}


int CDlgParam::GetParam(int index)
{
    return m_nParam[index];
}

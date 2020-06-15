// DlgParam.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "iSim.h"
#include "DlgParam.h"
#include "afxdialogex.h"

#define MAX_PARAM 10

// CDlgParam ��ȭ �����Դϴ�.

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


// CDlgParam �޽��� ó�����Դϴ�.

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

  // TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
  for(int i=0;i<MAX_PARAM;i++)
  {
    SetDlgItemText(IDC_STC_PARAM1+i,m_strParam[i]);
    SetDlgItemText(IDC_STC_COMMENT1+i,m_strComment[i]);
    SetDlgItemInt(IDC_EDIT_PARAM1+i,m_nParam[i]);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgParam::OnOK()
{
  // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

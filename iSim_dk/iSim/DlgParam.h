#pragma once


// CDlgParam ��ȭ �����Դϴ�.

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgParam();
  int m_nParam[10];
  int SetParam(int index, CString strParam, int nParam, CString strComment);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
  CString m_strParam[10];
  CString m_strComment[10];

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  int GetParam(int index);
};

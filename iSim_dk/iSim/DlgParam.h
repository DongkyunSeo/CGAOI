#pragma once


// CDlgParam 대화 상자입니다.

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgParam();
  int m_nParam[10];
  int SetParam(int index, CString strParam, int nParam, CString strComment);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
  CString m_strParam[10];
  CString m_strComment[10];

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  int GetParam(int index);
};

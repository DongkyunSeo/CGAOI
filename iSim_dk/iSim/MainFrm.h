
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once


#define  INDICATOR_TIME 1
#define  INDICATOR_ROI  2
#define  INDICATOR_SIZE 3
#define  INDICATOR_BPP 4
#define  INDICATOR_POS 5
#define  INDICATOR_VAL 6


class CMainFrame : public CFrameWnd
{
  
protected: // serialization������ ��������ϴ�.
  CMainFrame();
  DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
  virtual ~CMainFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
  CToolBar          m_wndToolBar;
  CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  DECLARE_MESSAGE_MAP()

public:
  int SetPaneText(int nIndex, LPCTSTR strMsg);
};



#if !defined(AFX_DLGHISTO_H__FF4909CB_2AB0_42A9_94EA_A3FF831C79A7__INCLUDED_)
#define AFX_DLGHISTO_H__FF4909CB_2AB0_42A9_94EA_A3FF831C79A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHisto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHisto dialog

class CDlgHisto : public CDialog
{
// Construction
public:
	void DrawHisto();
	int ColorUsed;
	int ImgSize;
	unsigned int HistoData[256];
	CDlgHisto(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHisto)
	enum { IDD = IDD_DLG_HISTO };
	int		m_nLowBound;
    int     m_nHighBound;
	float	m_fGamma;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHisto)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHisto)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTO_H__FF4909CB_2AB0_42A9_94EA_A3FF831C79A7__INCLUDED_)

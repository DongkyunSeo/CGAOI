
// iSim.h : iSim ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CiSimApp:
// �� Ŭ������ ������ ���ؼ��� iSim.cpp�� �����Ͻʽÿ�.
//

class CiSimApp : public CWinApp
{
public:
	CiSimApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CiSimApp theApp;

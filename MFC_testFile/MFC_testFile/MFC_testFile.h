// MFC_testFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_testFileApp:
// �йش����ʵ�֣������ MFC_testFile.cpp
//

class CMFC_testFileApp : public CWinApp
{
public:
	CMFC_testFileApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_testFileApp theApp;
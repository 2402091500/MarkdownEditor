
// MarkdownEditor.h : MarkdownEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMarkdownEditorApp:
// �йش����ʵ�֣������ MarkdownEditor.cpp
//

class CMarkdownEditorApp : public CWinApp
{
public:
	CMarkdownEditorApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CMarkdownEditorApp theApp;

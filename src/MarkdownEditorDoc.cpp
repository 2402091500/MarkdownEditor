
// MarkdownEditorDoc.cpp : CMarkdownEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "./Util.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MarkdownEditor.h"
#endif

#include "MarkdownEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMarkdownEditorDoc

IMPLEMENT_DYNCREATE(CMarkdownEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMarkdownEditorDoc, CDocument)

END_MESSAGE_MAP()


// CMarkdownEditorDoc ����/����

CMarkdownEditorDoc::CMarkdownEditorDoc()
{
	// TODO: �ڴ����һ���Թ������
	resetData();
}

CMarkdownEditorDoc::~CMarkdownEditorDoc()
{
}

BOOL CMarkdownEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	resetData();
	this->UpdateAllViews(NULL);
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	return TRUE;
}




// CMarkdownEditorDoc ���л�

void CMarkdownEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar.WriteString(Util::ANSIToUTF8(_strText.c_str()).c_str());
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		CString str;
		const int BUF_SIZE = 64*1024;
		unsigned char buf[BUF_SIZE + 1];
		while(true){
			UINT uRead = ar.Read(buf, BUF_SIZE);
			buf[uRead] = '\0';
			str += (const char*)buf;
			if(uRead < BUF_SIZE)
				break;
		}

		_strText = Util::UTF8ToANSI(str);
		this->UpdateAllViews(NULL);
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMarkdownEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMarkdownEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMarkdownEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMarkdownEditorDoc ���

#ifdef _DEBUG
void CMarkdownEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMarkdownEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMarkdownEditorDoc ����
//�����ı�����
void CMarkdownEditorDoc::UpdateText(const string& text, CView* pSender){
	_strText = text;
	this->UpdateAllViews(pSender);
	this->SetModifiedFlag();
}

void CMarkdownEditorDoc::resetData(void)
{
	_strText = "";
}

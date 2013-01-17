
// LeftView.cpp : CLeftView ���ʵ��
//

#include "stdafx.h"
#include "MarkdownEditor.h"

#include "MarkdownEditorDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CEditView)

BEGIN_MESSAGE_MAP(CLeftView, CEditView)
	ON_CONTROL_REFLECT(EN_CHANGE, &CLeftView::OnEnChange)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CLeftView ����/����

CLeftView::CLeftView()
{
	// TODO: �ڴ˴���ӹ������
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bCreate = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	return bCreate;
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	//return CEditView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
}


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CEditView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMarkdownEditorDoc* CLeftView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMarkdownEditorDoc)));
	return (CMarkdownEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView ��Ϣ�������


void CLeftView::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEditView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С� 

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	this->GetWindowText(str);
	string strText(str.GetBuffer());
	GetDocument()->UpdateText(strText, this);
	GetEditCtrl().SetFocus();
}


void CLeftView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pSender == this)
		return;
	GetEditCtrl().SetWindowText(GetDocument()->getText().c_str());
}


int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	_font.CreatePointFont(110,(LPCTSTR)"Consolas"); 
	SetFont(&_font); 
	this->SetTabStops(16);
	//this->ShowScrollBar(SB_HORZ,FALSE);
	return 0;
}

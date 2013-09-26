
// MarkdownEditorView.cpp : CMarkdownEditorView ���ʵ��
//

#include "stdafx.h"
#include "Util.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MarkdownEditor.h"
#endif

#include "MarkdownEditorDoc.h"
#include "MarkdownEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMarkdownEditorView

IMPLEMENT_DYNCREATE(CMarkdownEditorView, CHtmlView)

BEGIN_MESSAGE_MAP(CMarkdownEditorView, CHtmlView)
END_MESSAGE_MAP()

// CMarkdownEditorView ����/����

CMarkdownEditorView::CMarkdownEditorView()
{
	// TODO: �ڴ˴���ӹ������
	_bFirstNavigate = true;
	initCSS();
}

CMarkdownEditorView::~CMarkdownEditorView()
{
}

BOOL CMarkdownEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CHtmlView::PreCreateWindow(cs);
}

void CMarkdownEditorView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

}


// CMarkdownEditorView ���

#ifdef _DEBUG
void CMarkdownEditorView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMarkdownEditorView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMarkdownEditorDoc* CMarkdownEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMarkdownEditorDoc)));
	return (CMarkdownEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMarkdownEditorView ��Ϣ�������

void CMarkdownEditorView::NavigateHTML(const string& strHtml)
{
	IDispatch* pDoc = GetHtmlDocument();
	if(NULL == pDoc)
		return;
	// ȡ���ĵ��е�IPersistStreamInit����
    CComPtr<IHTMLDocument2> pHtmlDoc;
	HRESULT hr = pDoc ->QueryInterface(IID_IHTMLDocument2, (void**)&pHtmlDoc);
    if (FAILED(hr))
        return;

 // Empty URL and parameters opens the current document
        CComBSTR    bstrURL;
        CComVariant varDummy;
        pHtmlDoc->open(bstrURL, varDummy, varDummy, varDummy, NULL);

        // Create a safearray to store the HTML text
        SAFEARRAY      *pSA;
        SAFEARRAYBOUND  saBound = {1, 0};
        pSA = SafeArrayCreate(VT_VARIANT, 1, &saBound);

        // Copy the HTML into the one and only element
        VARIANT   *pVar;
        CComBSTR   bstrHTML = strHtml.c_str();              // Load the text
        varDummy = bstrHTML;                        // .. into a variant

        SafeArrayAccessData(pSA, (void**)&pVar);    // Access safearray data
        pVar[0] = varDummy;                         // Set the text data
        SafeArrayUnaccessData(pSA);                 // Release access

        // Write the HTML as the document's new text
        pHtmlDoc->write(pSA);                           // Overwrite HTML
        pHtmlDoc->close();                              // Update browser

        SafeArrayDestroy(pSA);                      // Finished with the safearray
}

CComPtr<IHTMLTextContainer> getContainer(IDispatch* pDisp){
	if(NULL == pDisp)
		return NULL;
		CComPtr<IHTMLDocument2> pDocument2 = NULL; 
            if (S_OK == pDisp->QueryInterface(IID_IHTMLDocument2, (LPVOID*)&pDocument2)) 
            { 
                CComPtr<IHTMLElement> pElement = NULL; 
                if (S_OK == pDocument2->get_body(&pElement)) 
                { 
                    CComPtr<IHTMLTextContainer> pTextContainer = NULL; 
                    if (S_OK == pElement->QueryInterface(IID_IHTMLTextContainer, (LPVOID*)&pTextContainer)) 
                    { 
						return pTextContainer;
                    } 
                }                 
           } 
		return NULL;
}
float getScrollTop(IDispatch* pDisp)
{
    long scrollTop;
	CComPtr<IHTMLTextContainer> pTextContainer = getContainer(pDisp);
    if (pTextContainer &&  S_OK == pTextContainer->get_scrollTop(&scrollTop) ) 
    {
		long height;
		pTextContainer->get_scrollHeight(&height);
		return ((float)scrollTop)/height ;
    } 
	return 0.0;
}
void setScrollTop(IDispatch* pDisp, float scrollPercent)
{
	CComPtr<IHTMLTextContainer> pTextContainer = getContainer(pDisp);
    if (pTextContainer)
    {
		long top,height;
		pTextContainer->get_scrollTop(&top);
		pTextContainer->get_scrollHeight(&height);
		pTextContainer->put_scrollTop(scrollPercent * height);
    } 
}
void CMarkdownEditorView::OnUpdate(CView* pSender, LPARAM /*lHint*/lParam, CObject* /*pHint*/)
{
	if(_bFirstNavigate){
		_bFirstNavigate = false;
		Navigate2(_T("about:blank"),NULL,NULL);
	}
	float scrollTop = 0;
	IDispatch* pDisp =GetHtmlDocument();
	
	if(pSender != NULL){
		scrollTop = getScrollTop(pDisp);
	}
	const string& str = GetDocument()->getText();	

	UpdateMd(str);
	if(lParam == 1){
		scrollTop = 1.0;
	}
	if(pSender != NULL){
		setScrollTop(pDisp,scrollTop);
	}



	// TODO: �ڴ����ר�ô����/����û���
}


void CMarkdownEditorView::initCSS(){
	string strUserCss = Util::GetExePath() + "user.css";
	if(PathFileExists(strUserCss.c_str())){
		_strCSS = Util::ReadStringFile(strUserCss.c_str());
	}else{
		Util::LoadStringRes(IDR_CSS,"CSS",_strCSS); 
	}
}

const string HTML_TMPL = "<html><head><style type=\"text/css\">{{0}}</style></head><body>{{1}}</body></html>";

string CMarkdownEditorView::GetMdHtml(const string& str){
	string strHtml = HTML_TMPL;
	Util::ReplaceAllStr(strHtml,"{{0}}", _strCSS);
	Util::ReplaceAllStr(strHtml, "{{1}}", Util::Text2Md(str));
	return strHtml;
}

void CMarkdownEditorView::UpdateMd(const string& strMd)
{
	string strHtml = GetMdHtml(strMd);
	NavigateHTML(strHtml);
}



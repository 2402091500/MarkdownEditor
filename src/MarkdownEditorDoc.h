
// MarkdownEditorDoc.h : CMarkdownEditorDoc ��Ľӿ�
//


#pragma once
#include <string>
using namespace std;
class CMarkdownEditorDoc : public CDocument
{
private:
	string _strText;
public:
	void UpdateText(const string& text,  CView* pSender = NULL);
	const string& getText(){return _strText;} 

protected: // �������л�����
	CMarkdownEditorDoc();
	DECLARE_DYNCREATE(CMarkdownEditorDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMarkdownEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	void resetData(void);
};

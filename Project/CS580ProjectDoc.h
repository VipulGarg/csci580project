// CS580ProjectDoc.h : interface of the CCS580ProjectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CS580ProjectDOC_H__C28F4603_B299_4DB1_9E4D_835F8AA79918__INCLUDED_)
#define AFX_CS580ProjectDOC_H__C28F4603_B299_4DB1_9E4D_835F8AA79918__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCS580ProjectDoc : public CDocument
{
protected: // create from serialization only
	CCS580ProjectDoc();
	DECLARE_DYNCREATE(CCS580ProjectDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS580ProjectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCS580ProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCS580ProjectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS580ProjectDOC_H__C28F4603_B299_4DB1_9E4D_835F8AA79918__INCLUDED_)

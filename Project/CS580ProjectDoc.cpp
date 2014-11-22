// CS580ProjectDoc.cpp : implementation of the CCS580ProjectDoc class
//

#include "stdafx.h"
#include "CS580Project.h"

#include "CS580ProjectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectDoc

IMPLEMENT_DYNCREATE(CCS580ProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CCS580ProjectDoc, CDocument)
	//{{AFX_MSG_MAP(CCS580ProjectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectDoc construction/destruction

CCS580ProjectDoc::CCS580ProjectDoc()
{
	// TODO: add one-time construction code here

}

CCS580ProjectDoc::~CCS580ProjectDoc()
{
}

BOOL CCS580ProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectDoc serialization

void CCS580ProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectDoc diagnostics

#ifdef _DEBUG
void CCS580ProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCS580ProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectDoc commands

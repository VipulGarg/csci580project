// IncreaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580Project.h"
#include "IncreaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncreaseDlg dialog


CIncreaseDlg::CIncreaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncreaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIncreaseDlg)
	m_bEdge = false;
	m_bLoose = false;
	m_bBlur = false;
	//}}AFX_DATA_INIT
}


void CIncreaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIncreaseDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIncreaseDlg, CDialog)
	//{{AFX_MSG_MAP(CIncreaseDlg)
	ON_BN_CLICKED(IDC_CHECK_EDGE, OnEdge)
	ON_BN_CLICKED(IDC_CHECK_LOOSE, OnLoose)
	ON_BN_CLICKED(IDC_CHECK_BLUR, OnBlur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncreaseDlg message handlers

void CIncreaseDlg::OnEdge() 
{
	// TODO: Add your control notification handler code here
	m_bEdge = true;
	UpdateData(false);
}

void CIncreaseDlg::OnLoose() 
{
	// TODO: Add your control notification handler code here
	m_bLoose = true;
	UpdateData(false);
}

void CIncreaseDlg::OnBlur() 
{
	// TODO: Add your control notification handler code here
	m_bBlur = true;
	UpdateData(false);
}

BOOL CIncreaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_bEdge = false;
	m_bLoose = false;
	m_bBlur = false;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

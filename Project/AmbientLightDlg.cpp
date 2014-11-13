// AmbientLightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580HW.h"
#include "AmbientLightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmbientLightDlg dialog


CAmbientLightDlg::CAmbientLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAmbientLightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleDlg)
	m_r = 0.0f;
	m_g = 0.0f;
	m_b = 0.0f;
	//}}AFX_DATA_INIT
}


void CAmbientLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_R_A, m_r);
	DDX_Text(pDX, IDC_EDIT_G_A, m_g);
	DDX_Text(pDX, IDC_EDIT_B_A, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmbientLightDlg, CDialog)
	//{{AFX_MSG_MAP(CAmbientLightDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmbientLightDlg message handlers

void CAmbientLightDlg::Initialize(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}
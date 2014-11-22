// Light2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CS580Project.h"
#include "Light2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLight2Dlg dialog


CLight2Dlg::CLight2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLight2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleDlg)
	m_dirx = 0.0f;
	m_diry = 0.0f;
	m_dirz = 0.0f;
	m_r = 0.0f;
	m_g = 0.0f;
	m_b = 0.0f;
	//}}AFX_DATA_INIT
}


void CLight2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg)
	DDX_Text(pDX, IDC_EDIT_DIRX_2, m_dirx);
	DDX_Text(pDX, IDC_EDIT_DIRY_2, m_diry);
	DDX_Text(pDX, IDC_EDIT_DIRZ_2, m_dirz);
	DDX_Text(pDX, IDC_EDIT_R_2, m_r);
	DDX_Text(pDX, IDC_EDIT_G_2, m_g);
	DDX_Text(pDX, IDC_EDIT_B_2, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLight2Dlg, CDialog)
	//{{AFX_MSG_MAP(CLight2Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLight2Dlg message handlers

void CLight2Dlg::Initialize(float dirx, float diry, float dirz, float r, float g, float b)
{
	m_dirx = dirx;
	m_diry = diry;
	m_dirz = dirz;
	m_r = r;
	m_g = g;
	m_b = b;
}
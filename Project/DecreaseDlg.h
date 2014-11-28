#if !defined(AFX_DECREASEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_)
#define AFX_DECREASEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecreaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDecreaseDlg dialog

class CDecreaseDlg : public CDialog
{
// Construction
public:
	bool m_bEdge;
	bool m_bLoose;
	bool m_bBlur;

	CDecreaseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDecreaseDlg)
	enum { IDD = IDD_DECREASE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecreaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateDlg)
	afx_msg void OnEdge();
	afx_msg void OnLoose();
	afx_msg void OnBlur();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECREASEDLG_H__5FF9F00A_12D3_4CE2_858C_3CAF9D561CFA__INCLUDED_)

#if !defined(AFX_LIGHT1DLG_H__8FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_)
#define AFX_LIGHT2DLG_H__8FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Light2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLight2Dlg dialog

class CLight2Dlg : public CDialog
{
// Construction
public:
	CLight2Dlg(CWnd* pParent = NULL);   // standard constructor
	void Initialize(float dirx, float diry, float dirz, float r, float g, float b);

// Dialog Data
	//{{AFX_DATA(CLight1Dlg)
	enum { IDD = IDD_LIGHT2 };
	float	m_dirx;
	float	m_diry;
	float	m_dirz;
	float	m_r;
	float	m_g;
	float	m_b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLight2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLight2Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHT2DLG_H__8FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_)

#if !defined(AFX_AMBIENTLIGHTDLG_H__9FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_)
#define AFX_AMBIENTLIGHTDLG_H__9FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmbientLightDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAmbientLightDlg dialog

class CAmbientLightDlg : public CDialog
{
// Construction
public:
	CAmbientLightDlg(CWnd* pParent = NULL);   // standard constructor
	void Initialize(float r, float g, float b);

// Dialog Data
	//{{AFX_DATA(CLight1Dlg)
	enum { IDD = IDD_AMBIENT_LIGHT };
	float	m_r;
	float	m_g;
	float	m_b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmbientLightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAmbientLightDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMBIENTLIGHTDLG_H__9FAFBEB4_9C06_4E8A_92F3_DD1111331F90__INCLUDED_)

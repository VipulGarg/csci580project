// CS580Project.h : main header file for the CS580Project application
//

#if !defined(AFX_CS580Project_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_)
#define AFX_CS580Project_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectApp:
// See CS580Project.cpp for the implementation of this class
//
#include "OBJParser.h"
#include "gz.h"

extern OBJParser objParser;
extern GzLight light1;
extern GzLight light2;
extern GzLight ambientLight;
extern int currRenderFunc;
extern int lastTexture;
extern float m_fthreshold;
extern int m_ifilterLength;
extern int m_idistanceInPixels;


class CCS580ProjectApp : public CWinApp
{
public:
	CCS580ProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS580ProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCS580ProjectApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS580Project_H__D4F247BC_D609_4BAC_8C3E_871F891962B3__INCLUDED_)

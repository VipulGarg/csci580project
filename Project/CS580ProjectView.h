// CS580ProjectView.h : interface of the CCS580ProjectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CS580ProjectVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_)
#define AFX_CS580ProjectVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Application.h"
#include "Gz.h"

class CCS580ProjectView : public CView
{
protected: // create from serialization only
	CCS580ProjectView();
	DECLARE_DYNCREATE(CCS580ProjectView)

// Attributes
public:
	CCS580ProjectDoc* GetDocument();

// Operations
public:
	Application* m_pApplication;
	void DrawFrameBuffer(CDC *pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCS580ProjectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCS580ProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCS580ProjectView)
	afx_msg void OnRender();
	afx_msg void OnDepthMap();
	afx_msg void OnEdgeMap();
	afx_msg void OnGaussianBlur();
	afx_msg void OnTextureP();
	afx_msg void OnTexture();
	afx_msg void OnStrokes();
	afx_msg void OnLooseAndSketchy();
	afx_msg void OnRotate();
	afx_msg void OnTranslate();
	afx_msg void OnScale();
	afx_msg void OnLight1();
	afx_msg void OnLight2();
	afx_msg void OnAmbientLight();
	afx_msg void OnRotateXP();
	afx_msg void OnRotateXN();
	afx_msg void OnRotateYP();
	afx_msg void OnRotateYN();
	afx_msg void OnRotateZP();
	afx_msg void OnRotateZN();
	afx_msg void OnIncrease();
	afx_msg void OnDecrease();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void ChooseRenderFunc();
};

#ifndef _DEBUG  // debug version in CS580ProjectView.cpp
inline CCS580ProjectDoc* CCS580ProjectView::GetDocument()
   { return (CCS580ProjectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS580ProjectVIEW_H__F4D29CBB_F832_426E_9878_3B454FBDB8F6__INCLUDED_)

// CS580ProjectView.cpp : implementation of the CCS580ProjectView class
//

#include "stdafx.h"
#include "CS580Project.h"

#include "CS580ProjectDoc.h"
#include "CS580ProjectView.h"
#include "RotateDlg.h"
#include "TranslateDlg.h"
#include "ScaleDlg.h"
#include "Light1Dlg.h"
#include "Light2Dlg.h"
#include "AmbientLightDlg.h"
#include "IncreaseDlg.h"
#include "DecreaseDlg.h"

#include "disp.h"
#include "Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectView

IMPLEMENT_DYNCREATE(CCS580ProjectView, CView)

BEGIN_MESSAGE_MAP(CCS580ProjectView, CView)
	//{{AFX_MSG_MAP(CCS580ProjectView)
	ON_COMMAND(IDM_RENDER, OnRender)
	ON_COMMAND(IDM_RENDERDEPTHMAP, OnDepthMap)
	ON_COMMAND(IDM_RENDEREDGEMAP, OnEdgeMap)
	ON_COMMAND(IDM_RENDERGAUSSIANBLUR, OnGaussianBlur)
	ON_COMMAND(IDM_RENDERTEXTUREP, OnTextureP)
	ON_COMMAND(IDM_RENDERTEXTURE, OnTexture)
	ON_COMMAND(IDM_RENDERSTROKES, OnStrokes)
	ON_COMMAND(IDM_RENDERLOOSESKETCHY, OnLooseAndSketchy)
	ON_COMMAND(IDM_ROTATE, OnRotate)
	ON_COMMAND(IDM_TRANSLATE, OnTranslate)
	ON_COMMAND(IDM_SCALE, OnScale)
	ON_COMMAND(IDM_LIGHT1, OnLight1)
	ON_COMMAND(IDM_LIGHT2, OnLight2)
	ON_COMMAND(IDM_AMBIENT_LIGHT, OnAmbientLight)
	ON_COMMAND(IDM_ROTATE_X_P, OnRotateXP)
	ON_COMMAND(IDM_ROTATE_X_N, OnRotateXN)
	ON_COMMAND(IDM_ROTATE_Y_P, OnRotateYP)
	ON_COMMAND(IDM_ROTATE_Y_N, OnRotateYN)
	ON_COMMAND(IDM_ROTATE_Z_P, OnRotateZP)
	ON_COMMAND(IDM_ROTATE_Z_N, OnRotateZN)
	ON_COMMAND(IDM_INCREASE, OnIncrease)
	ON_COMMAND(IDM_DECREASE, OnDecrease)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectView construction/destruction

CCS580ProjectView::CCS580ProjectView()
{
	// TODO: add construction code here
	m_pApplication = NULL;
}

CCS580ProjectView::~CCS580ProjectView()
{
	if(m_pApplication != NULL)
	{
		delete m_pApplication;
	}
}

BOOL CCS580ProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectView drawing

void CCS580ProjectView::OnDraw(CDC* pDC)
{
	CCS580ProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(m_pApplication != NULL)
		DrawFrameBuffer(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectView diagnostics

#ifdef _DEBUG
void CCS580ProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CCS580ProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCS580ProjectDoc* CCS580ProjectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCS580ProjectDoc)));
	return (CCS580ProjectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCS580ProjectView message handlers

void CCS580ProjectView::OnRender() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 0;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnDepthMap() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 1;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnEdgeMap() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 2;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnGaussianBlur() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 3;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnTextureP() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 4;
	lastTexture = 0;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnTexture() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 5;
	lastTexture = 1;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnStrokes() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 6;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}


void CCS580ProjectView::OnLooseAndSketchy() 
{
	// TODO: Add your command handler code here

	// Call renderer 
	currRenderFunc = 7;

	// Application 4
	if(m_pApplication != NULL)
		((Project *)m_pApplication)->Render();
	else 
		AfxMessageBox("Application was not allocated\n");

	// Set window size
	CRect clientRect, windowRect;
	int x_offset, y_offset;

	GetClientRect(&clientRect);
	AfxGetMainWnd()->GetWindowRect(&windowRect);
	
	x_offset = windowRect.Width() - clientRect.Width();
	y_offset = windowRect.Height() - clientRect.Height();

	AfxGetMainWnd()->SetWindowPos(NULL, 0, 0, x_offset+m_pApplication->m_nWidth, y_offset+m_pApplication->m_nHeight, NULL/*,SWP_SHOWWINDOW*/);

	Invalidate(true);	
}

void CCS580ProjectView::DrawFrameBuffer(CDC *pDC)
{
	if(m_pApplication->m_pFrameBuffer == NULL)
    {
        return;
    }

	if(!m_pApplication->m_pRender->open)
	{
		AfxMessageBox("Renderer was not opened\n");
		return;
	}

    HDC hdc;
    hdc = ::CreateCompatibleDC(pDC->m_hDC);
	HBITMAP m_bitmap;

    // Display the current image
    char buffer[sizeof(BITMAPINFO)];
    BITMAPINFO* binfo = (BITMAPINFO*)buffer;
    memset(binfo, 0, sizeof(BITMAPINFOHEADER));
    binfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    
	// Create the bitmap
    BITMAPINFOHEADER* bih = &binfo->bmiHeader;
	bih->biBitCount = 3*8;
	bih->biWidth = m_pApplication->m_nWidth;
	bih->biHeight = m_pApplication->m_nHeight;
    bih->biPlanes = 1;
    bih->biCompression = BI_RGB;
    bih->biSizeImage = 0;
    
    m_bitmap = CreateDIBSection(hdc, binfo, 0, 0, 0, DIB_RGB_COLORS);

    int colors = DIB_RGB_COLORS;
    
    ::SelectObject(hdc, m_bitmap);
	binfo->bmiHeader.biBitCount = 0;
	GetDIBits(hdc, m_bitmap, 0, 0, 0, binfo, colors);
    binfo->bmiHeader.biBitCount = 24;
    binfo->bmiHeader.biHeight = -abs(binfo->bmiHeader.biHeight);
    SetDIBits(hdc, m_bitmap, 0, m_pApplication->m_nHeight, m_pApplication->m_pFrameBuffer, binfo, colors);

    ::SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
    CRect client;
    GetClientRect(&client);
    ::BitBlt(pDC->m_hDC, 0, 0, m_pApplication->m_nWidth, m_pApplication->m_nHeight, 
        hdc, 0, 0, SRCCOPY);
    ::DeleteDC(hdc);
    DeleteObject(m_bitmap); 
}


void CCS580ProjectView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	// Assign Application 4
	if(m_pApplication == NULL)
	{
		m_pApplication = new Project;
	}
	
	// Initialize and begin renderer
	((Project *)m_pApplication)->Initialize();
}


void CCS580ProjectView::ChooseRenderFunc()
{
	switch(currRenderFunc)
	{
	case 0:
		OnRender();
		break;

	case 1:
		OnDepthMap();
		break;

	case 2:
		OnEdgeMap();
		break;

	case 3:
		OnGaussianBlur();
		break;

	case 4:
		OnTextureP();
		break;

	case 5:
		OnTexture();
		break;

	case 6:
		OnStrokes();
		break;

	case 7:
		OnLooseAndSketchy();
		break;
	}
}


// Callback function for rotation  
void CCS580ProjectView::OnRotate() 
{
	// TODO: Add your command handler code here
	CRotateDlg dlg;
	GzInput* input;
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	input->rotation[0] = input->rotation[1] = input->rotation[2] = 0;
	dlg.Initialize(input->rotation[0], input->rotation[1], input->rotation[2]);

	if(dlg.DoModal() == IDOK)
	{
		// Update input rotation value
		input->rotation[dlg.m_nAxis] = dlg.m_fRot;
				
		//  Create Rotation Matrix 
		switch(dlg.m_nAxis)
		{
		case 0 :
			// Create matrix for Rot X
			GzRotXMat(input->rotation[0], rotMat);
			break;
		case 1:
			// Create matrix for Rot Y
			GzRotYMat(input->rotation[1], rotMat);
			break;
		case 2:
			// Create matrix for Rot Z
			GzRotZMat(input->rotation[2], rotMat);
			break;
		}

		// Accumulate matrix
		GzPushMatrix(m_pApplication->m_pRender, rotMat); 
	}
}


// Callback function for rotation  
void CCS580ProjectView::OnIncrease() 
{
	// TODO: Add your command handler code here
	CIncreaseDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		if (dlg.m_bEdge == true)
		{
			if (m_fthreshold > 50)
				m_fthreshold -= 50;
		}
		if (dlg.m_bLoose == true)
		{
			m_idistanceInPixels += 1;
		}
		if (dlg.m_bBlur == true)
		{
			m_ifilterLength += 2;
		}
		dlg.m_bBlur = false;
		dlg.m_bEdge = false;
		dlg.m_bLoose = false;
		ChooseRenderFunc();
	}
}


// Callback function for rotation  
void CCS580ProjectView::OnDecrease() 
{
	// TODO: Add your command handler code here
	CDecreaseDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		if (dlg.m_bEdge == true)
		{
			m_fthreshold += 50;
		}
		if (dlg.m_bLoose == true)
		{
			if (m_idistanceInPixels > 1)
				m_idistanceInPixels -= 1;
		}
		if (dlg.m_bBlur == true)
		{
			if (m_ifilterLength > 3)
				m_ifilterLength -= 2;
		}
		dlg.m_bBlur = false;
		dlg.m_bEdge = false;
		dlg.m_bLoose = false;
		ChooseRenderFunc();
	}
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateXP() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotXMat(10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateXN() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotXMat(-10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateYP() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotYMat(10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateYN() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotYMat(-10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateZP() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotZMat(10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for rotation  
void CCS580ProjectView::OnRotateZN() 
{
	// TODO: Add your command handler code here
	GzMatrix	rotMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;
	// Create matrix for Rot X
	GzRotZMat(-10, rotMat);

	// Accumulate matrix
	GzPushMatrix(m_pApplication->m_pRender, rotMat);
	ChooseRenderFunc();
}

// Callback function for Translation
void CCS580ProjectView::OnTranslate() 
{
	// TODO: Add your command handler code here
	CTranslateDlg dlg;
	GzInput* input;
	GzMatrix	trxMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	input->translation[0] = input->translation[1] = input->translation[2] = 0;
	dlg.Initialize(input->translation[0], input->translation[1], input->translation[2]);

	if(dlg.DoModal() == IDOK)
	{
		// Update input translation value
		input->translation[0] = dlg.m_fTx; input->translation[1] = dlg.m_fTy; input->translation[2] = dlg.m_fTz;

		//  Create Translation Matrix
		GzTrxMat(input->translation, trxMat);

		// Accumulate matrix
		GzPushMatrix(m_pApplication->m_pRender, trxMat); 
	}
}

// Callback function for Scaling
void CCS580ProjectView::OnScale() 
{
	// TODO: Add your command handler code here
	CScaleDlg dlg;
	GzInput* input;
	GzMatrix scaleMat = 
	{ 
		1.0,	0.0,	0.0,	0.0, 
		0.0,	1.0,	0.0,	0.0, 
		0.0,	0.0,	1.0,	0.0, 
		0.0,	0.0,	0.0,	1.0 
	};


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	input->scale[0] = input->scale[1] = input->scale[2] = 1;
	dlg.Initialize(input->scale[0], input->scale[1], input->scale[2]);

	if(dlg.DoModal() == IDOK)
	{
		// Update input scale value
		input->scale[0] = dlg.m_fSx; input->scale[1] = dlg.m_fSy; input->scale[2] = dlg.m_fSz;

		//  Create Scaling Matrix
		GzScaleMat(input->scale, scaleMat);

		// Accumulate matrix
		GzPushMatrix(m_pApplication->m_pRender, scaleMat); 
	}
}


// Callback function for Scaling
void CCS580ProjectView::OnLight1()
{
	// TODO: Add your command handler code here
	CLight1Dlg dlg;
	GzInput* input;


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	//input->scale[0] = input->scale[1] = input->scale[2] = 1;
	dlg.Initialize(light1.direction[0], light1.direction[1], light1.direction[2], light1.color[0], light1.color[1], light1.color[2]);

	if(dlg.DoModal() == IDOK)
	{
		light1.direction[0] = dlg.m_dirx;
		light1.direction[1] = dlg.m_diry;
		light1.direction[2] = dlg.m_dirz;

		light1.color[0] = dlg.m_r;
		light1.color[1] = dlg.m_g;
		light1.color[2] = dlg.m_b;
		
		GzPutLight(m_pApplication->m_pRender, light1, 0);
		OnRender();
	}
}


// Callback function for Scaling
void CCS580ProjectView::OnLight2()
{
	// TODO: Add your command handler code here
	CLight2Dlg dlg;
	GzInput* input;


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	//input->scale[0] = input->scale[1] = input->scale[2] = 1;
	dlg.Initialize(light2.direction[0], light2.direction[1], light2.direction[2], light2.color[0], light2.color[1], light2.color[2]);

	if(dlg.DoModal() == IDOK)
	{
		light2.direction[0] = dlg.m_dirx;
		light2.direction[1] = dlg.m_diry;
		light2.direction[2] = dlg.m_dirz;

		light2.color[0] = dlg.m_r;
		light2.color[1] = dlg.m_g;
		light2.color[2] = dlg.m_b;
		
		GzPutLight(m_pApplication->m_pRender, light2, 1);
		OnRender();
	}
}


// Callback function for Scaling
void CCS580ProjectView::OnAmbientLight()
{
	// TODO: Add your command handler code here
	CAmbientLightDlg dlg;
	GzInput* input;


	if(m_pApplication == NULL) return;

	input = m_pApplication->m_pUserInput;
	if(input == NULL) return;

	// Initialize
	//input->scale[0] = input->scale[1] = input->scale[2] = 1;
	dlg.Initialize(ambientLight.color[0], ambientLight.color[1], ambientLight.color[2]);

	if(dlg.DoModal() == IDOK)
	{
		ambientLight.color[0] = dlg.m_r;
		ambientLight.color[1] = dlg.m_g;
		ambientLight.color[2] = dlg.m_b;

		GzToken     nameListLights[1];		/* light info */
		GzPointer   valueListLights[1];
		nameListLights[0] = GZ_AMBIENT_LIGHT;
		valueListLights[0] = (GzPointer)&ambientLight;
		GzPutAttribute(m_pApplication->m_pRender, 1, nameListLights, valueListLights);
		OnRender();
	}
}

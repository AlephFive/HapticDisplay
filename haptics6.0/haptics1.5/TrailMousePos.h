// TrailMousePos.h : main header file for the TRAILMOUSEPOS application
//

#if !defined(AFX_TRAILMOUSEPOS_H__176041F9_8AE0_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_TRAILMOUSEPOS_H__176041F9_8AE0_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrailMousePosApp:
// See TrailMousePos.cpp for the implementation of this class
//

class CTrailMousePosApp : public CWinApp
{
public:
	CTrailMousePosApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrailMousePosApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrailMousePosApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAILMOUSEPOS_H__176041F9_8AE0_11D6_8F32_00E04CE76240__INCLUDED_)

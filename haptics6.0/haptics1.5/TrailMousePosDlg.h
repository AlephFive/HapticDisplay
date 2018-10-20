// TrailMousePosDlg.h : header file
//

#include "mscomm1.h"
#include "afxwin.h"
#if !defined(AFX_TRAILMOUSEPOSDLG_H__176041FB_8AE0_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_TRAILMOUSEPOSDLG_H__176041FB_8AE0_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTrailMousePosDlg dialog

class CTrailMousePosDlg : public CDialog
{
// Construction
public:
	CTrailMousePosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTrailMousePosDlg)
	enum { IDD = IDD_TRAILMOUSEPOS_DIALOG };

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrailMousePosDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTrailMousePosDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CMscomm1 m_mscomm;
	CString m_EditRecieve;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

	afx_msg void OnBnClickedButton6();

	afx_msg void OnBnClickedButton7();




	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAILMOUSEPOSDLG_H__176041FB_8AE0_11D6_8F32_00E04CE76240__INCLUDED_)


// Figure InvadersDlg.h : header file
//

#pragma once
#include "Figures.h"
#include "ColorEdit.h"

#define FRAMERATE 1000
#define SPAWN 1001
#define ShotRate 1002

// CFigureInvadersDlg dialog
class CFigureInvadersDlg : public CDialogEx
{
// Construction
public:
	CFigureInvadersDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIGURE_INVADERS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CTypedPtrArray< CObArray, Figure*> GameObj;
	bool Pause = true;
	bool Running = false;
	bool canShoot = true;
	int	ptsScore = 0;
	RECT area;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedIdplay();
	afx_msg void OnClickedIdsave();
	afx_msg void OnClickedIdload();
	afx_msg void OnClickedIdresume();
	afx_msg void OnBnClickedExit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedRestart();
	afx_msg void OnEnChangeScore();
	afx_msg void OnBnClickedLoad2();

	CColorEdit m_ebCtl;
};

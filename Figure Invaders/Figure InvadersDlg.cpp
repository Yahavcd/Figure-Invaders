
// Figure InvadersDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Figure Invaders.h"
#include "Figure InvadersDlg.h"
#include "afxdialogex.h"
#include "Figures.h"
#include <typeinfo>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFigureInvadersDlg dialog


CFigureInvadersDlg::CFigureInvadersDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIGURE_INVADERS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFigureInvadersDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, IDC_SCORE, ptsScore);
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFigureInvadersDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDPLAY, &CFigureInvadersDlg::OnClickedIdplay)
ON_BN_CLICKED(IDSAVE, &CFigureInvadersDlg::OnClickedIdsave)
ON_BN_CLICKED(IDLOAD, &CFigureInvadersDlg::OnClickedIdload)
ON_BN_CLICKED(IDRESUME, &CFigureInvadersDlg::OnClickedIdresume)
ON_BN_CLICKED(IDEXIT, &CFigureInvadersDlg::OnBnClickedExit)
ON_WM_TIMER()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(RESTART, &CFigureInvadersDlg::OnBnClickedRestart)
ON_EN_CHANGE(IDC_SCORE, &CFigureInvadersDlg::OnEnChangeScore)
ON_BN_CLICKED(IDLOAD2, &CFigureInvadersDlg::OnBnClickedLoad2)
END_MESSAGE_MAP()


// CFigureInvadersDlg message handlers

BOOL CFigureInvadersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ebCtl.SubclassDlgItem(IDC_SCORE, this);
	m_ebCtl.SetTextColor(WHITE); //Changes the Edit Box text to Blue
	m_ebCtl.SetBkColor(BLACK);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFigureInvadersDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFigureInvadersDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CMyMemDC pDC(&dc); //Added librery to eliminate flickering
	ASSERT_VALID(this);
	CRect rect;
	GetClientRect(&rect);

	//Pen for use in object painting
	CPen pen(PS_SOLID, 0, RGB(255, 255, 255));

	//Paint screen in black
	CBrush myBlack;
	myBlack.CreateSolidBrush(RGB(0, 0, 0));
	pDC.FillRect(&rect, &myBlack);

	
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(pDC.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		pDC.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//Create objects with the pen
		CPen* pOldPen = pDC.SelectObject(&pen);
		for (int i = 0; i < GameObj.GetSize(); i++)
			GameObj[i]->Draw(&pDC);

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFigureInvadersDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFigureInvadersDlg::OnClickedIdplay()
{
	if (!Running) //Init game
	{
		area.left = 0;
		area.right = 600;
		area.top = 530;
		area.bottom = 30;

		Running = true;
		int start1 = 140;
		int start2 = 70;
		int next = 40;
		GetDlgItem(IDPLAY)->ShowWindow(false);
		GetDlgItem(IDLOAD)->ShowWindow(false);
		GetDlgItem(IDLOAD2)->ShowWindow(false);
		GetDlgItem(IDEXIT)->ShowWindow(false);

		Alien::setAmount(18);
		GameObj.Add(new Player(CPoint(280, 320), 15));
		GameObj.Add(new Spaceship(CPoint(600, 50), 40, 25));
		GameObj.Add(new Alien(CPoint(start1, start2), next));
		start1 += 15;
		for (int i = 0; i < 17; i++)
		{
			GameObj.Add(new Alien(CPoint(start1 + next, start2), next));
			start1 += next + 15;
			if (start1 >= 415)
			{
				start1 = 100;
				start2 += next + 15;
			}
		}
		Pause = false;
		SetTimer(FRAMERATE, 4, NULL);
		SetTimer(SPAWN, 2000, NULL);
		Invalidate();
	}
}


void CFigureInvadersDlg::OnClickedIdsave()
{
	CFileDialog dlg(FALSE, _T(".GameObj"), NULL, 0, _T("Figure_Wars (*.GameObj)|*.GameObj|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName();
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		GameObj.Serialize(ar);
		ar.Close();
		file.Close();
	}
}


void CFigureInvadersDlg::OnClickedIdload()
{
	CFileDialog dlg(TRUE, _T(".GameObj"), NULL, 0, _T("Figure_Wars (*.GameObj)|*.GameObj|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		GameObj.Serialize(ar);
		ar.Close();
		file.Close();
		GetDlgItem(IDPLAY)->ShowWindow(false);
		GetDlgItem(IDLOAD)->ShowWindow(false);
		GetDlgItem(IDLOAD2)->ShowWindow(false);
		GetDlgItem(IDEXIT)->ShowWindow(false);
		Running = true;
		Pause = false;
		SetTimer(FRAMERATE, 4, NULL);
		SetTimer(SPAWN, 2000, NULL);
		ptsScore = dynamic_cast<Player*>(GameObj[0])->getScore();
		area.left = 0;
		area.right = 600;
		area.top = 530;
		area.bottom = 30;
		UpdateData(false);
		Invalidate();
	}
	else if (Running)
	{
		GetDlgItem(IDRESUME)->ShowWindow(true);
		GetDlgItem(IDSAVE)->ShowWindow(true);
		GetDlgItem(IDLOAD2)->ShowWindow(true);
		GetDlgItem(IDEXIT)->ShowWindow(true);
	}

}


void CFigureInvadersDlg::OnClickedIdresume()
{
	Pause = false;
	GetDlgItem(IDRESUME)->ShowWindow(false);
	GetDlgItem(IDSAVE)->ShowWindow(false);
	GetDlgItem(IDLOAD2)->ShowWindow(false);
	GetDlgItem(IDEXIT)->ShowWindow(false);
}


void CFigureInvadersDlg::OnBnClickedExit()
{

	return CDialog::OnCancel();
}


//Action
BOOL CFigureInvadersDlg::PreTranslateMessage(MSG* pMsg) {
	int x = (int)pMsg->wParam;

	if (pMsg->message == WM_KEYDOWN && !Pause)
	{
		if (x == VK_LEFT) //Left movment
		{
			if (dynamic_cast<Player*>(GameObj[0])->getPoint().x > 20)
			{
				dynamic_cast<Player*>(GameObj[0])->moveLeft();
			}
		}
		if (x == VK_RIGHT) //Right movment
		{
			if (dynamic_cast<Player*>(GameObj[0])->getPoint().x < 540)
			{
				dynamic_cast<Player*>(GameObj[0])->moveRight();
			}
		}
		//Shot
		if (x == VK_SPACE && canShoot)
		{
			GameObj.Add(new Shot(GameObj[0]->getPoint(), 15));
			SetTimer(ShotRate, 500, NULL);
			canShoot = false;
		}
	
		//Pause
		if (x == VK_RETURN)
		{
			if (Pause)
			{
				Pause = false;
				GetDlgItem(IDRESUME)->ShowWindow(false);
				GetDlgItem(IDSAVE)->ShowWindow(false);
				GetDlgItem(IDLOAD2)->ShowWindow(false);
				GetDlgItem(IDEXIT)->ShowWindow(false);
			}
			else
			{
				Pause = true;
				GetDlgItem(IDRESUME)->ShowWindow(true);
				GetDlgItem(IDSAVE)->ShowWindow(true);
				GetDlgItem(IDLOAD2)->ShowWindow(true);
				GetDlgItem(IDEXIT)->ShowWindow(true);
			}
		}
		InvalidateRect(&area);
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CFigureInvadersDlg::OnTimer(UINT_PTR nIDEvent) //Gameclock
{
	if (!Pause)
	{
		if (nIDEvent == FRAMERATE)
		{
			for (int i = 1; i < GameObj.GetSize(); i++)
			{
				if (typeid(*GameObj[i]).name() == typeid(Explosion).name())
				{
					dynamic_cast<Explosion*>(GameObj[i])->Boom();
					if (dynamic_cast<Explosion*>(GameObj[i])->chkDone())
					{
						delete GameObj[i];
						GameObj.RemoveAt(i, 1);
						i--;
					}

				}
				if (typeid(*GameObj[i]).name() == typeid(Alien).name())
				{
					dynamic_cast<Alien*>(GameObj[i])->MoveLR();
					if (dynamic_cast<Alien*>(GameObj[i])->isInside(GameObj[0]->getPoint()))
					{
						Pause = true;
						Running = false;
						GetDlgItem(RESTART)->ShowWindow(true);
					}
				}

				if (typeid(*GameObj[i]).name() == typeid(Spaceship).name() && Spaceship::isAlive())
				{
					dynamic_cast<Spaceship*>(GameObj[i])->Move();
					if (GameObj[i]->getPoint().x <= -20)
					{
						Spaceship::Kill();
						dynamic_cast<Spaceship*>(GameObj[i])->Reset();
						SetTimer(SPAWN, 10000, NULL);
					}

				}
				if (typeid(*GameObj[i]).name() == typeid(Shot).name())
				{
					dynamic_cast<Shot*>(GameObj[i])->Move();
					if (GameObj[i]->getPoint().y <= 0)
					{
						delete GameObj[i];
						GameObj.RemoveAt(i, 1);
					}
					else
					{
						for (int j = 1; j < GameObj.GetSize(); j++)
						{
							if (typeid(*GameObj[j]).name() == typeid(Alien).name())
								if (dynamic_cast<Alien*>(GameObj[j])->isInside(GameObj[i]->getPoint()))
								{
									GameObj.Add(new Explosion(GameObj[i]->getPoint(), 5));
									dynamic_cast<Player*>(GameObj[0])->addScore(dynamic_cast<Alien*>(GameObj[j])->getPoints());
									ptsScore = dynamic_cast<Player*>(GameObj[0])->getScore();
									UpdateData(false);
									delete GameObj[j];
									GameObj.RemoveAt(j, 1);
									Alien::setAmount(Alien::getAmount() - 1);
									i--;
									delete GameObj[i];
									GameObj.RemoveAt(i, 1);
									i--;
									break;
								}
							if (typeid(*GameObj[j]).name() == typeid(Spaceship).name())
								if (dynamic_cast<Spaceship*>(GameObj[j])->isInside(GameObj[i]->getPoint()))
								{
									{
										dynamic_cast<Player*>(GameObj[0])->addScore(dynamic_cast<Spaceship*>(GameObj[j])->getPoints());
										ptsScore = dynamic_cast<Player*>(GameObj[0])->getScore();
										UpdateData(false);
										GameObj.Add(new Explosion(GameObj[i]->getPoint(), 5));
										Spaceship::Kill();
										dynamic_cast<Spaceship*>(GameObj[j])->Reset();
										SetTimer(SPAWN, 10000, NULL);
									}
								}

						}
					}
				}
			}
			if (Alien::isMoveDown())
			{
				for (int i = 1; i < GameObj.GetSize(); i++)
				{
					if (typeid(*GameObj[i]).name() == typeid(Alien).name())
					{
						dynamic_cast<Alien*>(GameObj[i])->MoveD();
						if (dynamic_cast<Alien*>(GameObj[i])->isInside(GameObj[0]->getPoint()))
						{
							Pause = true;
							Running = false;
							GetDlgItem(RESTART)->ShowWindow(true);

						}
					}
					if (GameObj[i]->getPoint().y >= 400)
					{
						delete GameObj[i];
						GameObj.RemoveAt(i, 1);
						Alien::setAmount(Alien::getAmount() - 1);
						i--;
					}
				}
				Alien::setMoveDown();
			}
			InvalidateRect(&area);
		}
		if (nIDEvent == SPAWN)
		{
			if (!Spaceship::isAlive())
			{
				Spaceship::Alive();
				KillTimer(SPAWN);
				InvalidateRect(&area);
			}
		}
	}
	if (nIDEvent == ShotRate)
	{
		KillTimer(ShotRate);
		canShoot = true;
	}

	if (!Spaceship::isAlive() && Alien::getAmount() == 0 && !Pause)
	{
		Pause = true;
		Running = false;
		GetDlgItem(RESTART)->ShowWindow(true);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CFigureInvadersDlg::OnEraseBkgnd(CDC* pDC) //Added to elimenate flicketing
{
	return true;
}


void CFigureInvadersDlg::OnBnClickedRestart()
{
	if (!Running)
	{
		for (int i = 0; i < GameObj.GetSize(); i++)
			delete GameObj[i];
		GameObj.RemoveAll();
		GetDlgItem(RESTART)->ShowWindow(false);
		ptsScore = 0;
		UpdateData(false);
		OnClickedIdplay();
	}

}

void CFigureInvadersDlg::OnEnChangeScore()
{
}


void CFigureInvadersDlg::OnBnClickedLoad2()
{
	GetDlgItem(IDRESUME)->ShowWindow(false);
	GetDlgItem(IDSAVE)->ShowWindow(false);
	GetDlgItem(IDLOAD2)->ShowWindow(false);
	GetDlgItem(IDEXIT)->ShowWindow(false);
	OnClickedIdload();
}



// BaseAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BaseApp.h"
#include "BaseAppDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <thread>
#include <fstream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <cstring>
#include "MathFactorial.h"
#include <future>


using namespace MathFactorial;

// CAboutDlg dialog used for App About

CString a;
vector<long long> b;

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


// CBaseAppDlg dialog



CBaseAppDlg::CBaseAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASEAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBaseAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CBaseAppDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CBaseAppDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &CBaseAppDlg::OnEnChangeEdit2)
	ON_COMMAND(ID_32773, &CBaseAppDlg::ReadingFile)
	ON_COMMAND(ID_32774, &CBaseAppDlg::WriteDialog)
END_MESSAGE_MAP()


// CBaseAppDlg message handlers

BOOL CBaseAppDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBaseAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBaseAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBaseAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBaseAppDlg::OnBnClickedButton2()
{
	OnEnChangeEdit2();
}

void CBaseAppDlg::OnMyExit()
{
	// TODO: Add your command handler code here
	CDialogEx::OnOK();
}

void CBaseAppDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	this->DestroyWindow();
}

UINT func(LPVOID pParam) {
	b = factorial(b);
	a = ConvertFromMassValueToMassSimbol(b);
	CBaseAppDlg* ad = (CBaseAppDlg*)pParam;
	if (a[0] == '0') {
		a = "!Некоректное значение";
	}
	ad->SetDlgItemTextW(IDC_EDIT2, a);
	return 0;
}

void CBaseAppDlg::OnEnChangeEdit2()
{
	GetDlgItemTextW(IDC_EDIT1, a);
	b = ConvertFromMassSimbolToMassValue(a);
	AfxBeginThread(func, this);
}

void CBaseAppDlg::ReadingFile()
{
	CFileDialog fileDialog(TRUE, 0, L"*.txt");
	int result = fileDialog.DoModal();
	if (result == IDOK) {
		ifstream in;
		in.open(fileDialog.GetPathName());
		if (in.is_open()) {
			string dataString;
			in >> dataString;
			char* dataChar = new char[dataString.size() + 1];
			dataChar[dataString.size()] = '\0';
			for (int i = 0; i < dataString.size(); i++) {
				dataChar[i] = dataString[i];
			}
			CString cstring(dataChar);
			a = cstring;
			SetDlgItemTextW(IDC_EDIT1, a);
		}
		in.close();
	}
}


void CBaseAppDlg::WriteDialog()
{
	CFileDialog fileDialog(FALSE, 0, L"*.txt");
	int result = fileDialog.DoModal();
	if (result == IDOK) {
		ofstream out;
		out.open(fileDialog.GetPathName());
		if (out.is_open()) {
			for (int i = 0; i < a.GetLength(); i++) {
				out << char(a[i]);
			}
			out << endl;
		}
		out.close();
	}
}

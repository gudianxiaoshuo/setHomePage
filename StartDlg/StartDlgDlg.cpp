
// StartDlgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StartDlg.h"
#include "StartDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartDlgDlg 对话框



CStartDlgDlg::CStartDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStartDlgDlg::IDD, pParent)
	, bSetHomePage(TRUE)
	, bSeeYingshi(TRUE)
	, bSafe(TRUE)
	, bPic(TRUE)
	, bYunjisuan(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, bSetHomePage);
	DDX_Check(pDX, IDC_CHECK2, bSeeYingshi);
	DDX_Check(pDX, IDC_CHECK3, bSafe);
	DDX_Check(pDX, IDC_CHECK4, bPic);
	DDX_Check(pDX, IDC_CHECK5, bYunjisuan);
}

BEGIN_MESSAGE_MAP(CStartDlgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStartDlgDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStartDlgDlg 消息处理程序

BOOL CStartDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	CenterWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStartDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStartDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStartDlgDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (bSetHomePage)
		homePage.SetHomePage();


	CString path;
	CString exePath;

	TCHAR szPath[255];
	GetModuleFileName(NULL, szPath, 255);
	*(_tcsrchr(szPath, _T('\\')) + 1) = 0;
	path = szPath;

	exePath = path +L"homePage\\2345_kqq869321632_movie.exe";

	if (bSeeYingshi)
		ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);

	exePath = path + L"homePage\\2345pcsafe_kqq869321632.exe";

	if (bSafe)
		ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);


	exePath = path + L"homePage\\2345pic_kqq869321632.exe";

	if (bPic)
	ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);




	exePath = path + L"cc_kqq869321632_201066.exe";
	if(bYunjisuan)
		ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);

	//homePage.OpenExe(exePath);
	exePath = path + L"任性动图.exe";
	ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);

	CDialogEx::OnOK();
}

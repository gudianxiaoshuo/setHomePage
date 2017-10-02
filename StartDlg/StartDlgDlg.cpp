
// StartDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StartDlg.h"
#include "StartDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartDlgDlg �Ի���



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


// CStartDlgDlg ��Ϣ�������

BOOL CStartDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	CenterWindow();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStartDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStartDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStartDlgDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	exePath = path + L"���Զ�ͼ.exe";
	ShellExecute(NULL, L"open", exePath, NULL, NULL, SW_SHOWNORMAL);

	CDialogEx::OnOK();
}


// StartDlgDlg.h : ͷ�ļ�
//

#pragma once

#include"HomePage.h"

// CStartDlgDlg �Ի���
class CStartDlgDlg : public CDialogEx
{
// ����
public:
	CStartDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STARTDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	CHomePage homePage;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL bSetHomePage;
	BOOL bSeeYingshi;
	BOOL bSafe;
	BOOL bPic;
};

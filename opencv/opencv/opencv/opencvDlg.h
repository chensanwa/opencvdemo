
// opencvDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CopencvDlg �Ի���
class CopencvDlg : public CDialogEx
{
// ����
public:
	CopencvDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENCV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	CStatic m_pictureControl;
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32776();
	afx_msg void On32777();
	afx_msg void On32778();
	afx_msg void On32779();
	afx_msg void On32780();
	afx_msg void On32781();
	afx_msg void On32782();
	afx_msg void On32783();
	afx_msg void On32784();
	afx_msg void On32785();
	afx_msg void On32786();
	afx_msg void On32787();
	afx_msg void On32788();
	afx_msg void On32789();
	afx_msg void On32790();
	afx_msg void On32791();
	afx_msg void On32792();
	afx_msg void On32793();
	afx_msg void On32795();
	afx_msg void On32794();
};

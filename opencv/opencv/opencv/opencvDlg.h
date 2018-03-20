
// opencvDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CopencvDlg 对话框
class CopencvDlg : public CDialogEx
{
// 构造
public:
	CopencvDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPENCV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

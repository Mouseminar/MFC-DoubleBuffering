
// MyTestDlg.h: 头文件
//

#pragma once


// CMyTestDlg 对话框
class CMyTestDlg : public CDialogEx
{
// 构造
public:
	CMyTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTEST_DIALOG };
#endif

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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	// 矩形的偏移
	int dx;
	int dy;
	CString m_time;

	//内存DC
	CDC* m_pMemDC;
	//设备DC
	CClientDC* m_pDC;
	//内存位图
	CBitmap* m_pMemBitmap;

	afx_msg void OnDestroy();
};

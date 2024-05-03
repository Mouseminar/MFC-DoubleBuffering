
// MyTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyTest.h"
#include "MyTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMyTestDlg 对话框



CMyTestDlg::CMyTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYTEST_DIALOG, pParent)
	, m_time(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_time);
}

BEGIN_MESSAGE_MAP(CMyTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyTestDlg::OnBnClickedButton2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyTestDlg 消息处理程序

BOOL CMyTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	dx = 0;
	dy = 0;

	CRect rc;
	GetClientRect(rc);

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC, rc.Width(), rc.Height());

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyTestDlg::OnPaint()
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
		LARGE_INTEGER start, end, freq;
		QueryPerformanceFrequency(&freq);  // 获取计数器的频率
		QueryPerformanceCounter(&start);  // 开始计时
		
		CRect rect;
		GetClientRect(&rect);

		// 先在内存中绘制内容

		// 模拟计算
		for (int i = 0; i < 1000000000; i++)
		{

		}

		// 创建一个画刷，设定为淡蓝色背景
		CBrush brush(RGB(173, 216, 230)); // 例如：淡蓝色

		// 填充对话框背景
		m_pMemDC->FillRect(rect, &brush);

		// 绘制随时间移动的矩形
		m_pMemDC->Rectangle(50 + dx * 10, 50 + dy * 10, 100 + dx * 10, 100 + dy * 10);

		// 将内存中的内容一次性绘制到屏幕上
		m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_pMemDC, 0, 0, SRCCOPY);


		QueryPerformanceCounter(&end);  // 结束计时
		double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;  // 计算经过的时间（毫秒）
		m_time.Format(_T("%.3f milliseconds"), elapsed);
		UpdateData(FALSE);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	dx++;
	dy++;

	//Invalidate(TRUE);	// 清除画板再画
	Invalidate(FALSE);	//不清除画板，直接画

	CDialogEx::OnTimer(nIDEvent);
}


void CMyTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1, 1000, NULL);
}


void CMyTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}

void CMyTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

// MFC_testFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_testFile.h"
#include "MFC_testFileDlg.h"
#include "ButtonDraw.h"
#include "SliderDraw.h"
#include "mmsystem.h"  
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_TRAYNOTIFY WM_USER + 11
#define TIMER_MOVE 1 
UINT ThreadFun(LPVOID pParam)
{  
	//线程要调用的函数
	//MessageBox(NULL,_T("i am called by a thread."), _T("thread func"),MB_OK);
	CEdit* m_edit1=(CEdit*)GetDlgItem(NULL,IDC_EDIT1); 
	int i=0;
	while(1)
	{
		//m_edit1->
		HWND hWnd = AfxGetMainWnd()->m_hWnd;
		//CString str;
		//str.Format(_T("%d"),i);
		//SetDlgItemText(hWnd,IDC_EDIT1, str);
		//i++;
		CString str; //获取系统时间 　　
		SYSTEMTIME st; 
		GetLocalTime(&st); 
		str.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); 
		SetDlgItemText(hWnd,IDC_EDIT1, str);
		Sleep(1000);
	}
	return 1;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFC_testFileDlg 对话框




CMFC_testFileDlg::CMFC_testFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFC_testFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_nid, 0, sizeof(m_nid)); // Initialize NOTIFYICONDATA struct
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
}

CMFC_testFileDlg::~CMFC_testFileDlg()
{
	m_nid.hIcon = NULL;
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
}


void CMFC_testFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_testFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_TRAYNOTIFY, &CMFC_testFileDlg::OnTrayNotify)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_DRAWITEM()
	//ON_BN_CLICKED(IDC_BUTTON_MIN, &CMFC_testFileDlg::OnBnClickedButtonMin)
	//ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFC_testFileDlg::OnBnClickedButtonStop)
	//ON_BN_CLICKED(6001, &CMFC_testFileDlg::OnMycreatbutton1)
END_MESSAGE_MAP()


// CMFC_testFileDlg 消息处理程序

BOOL CMFC_testFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//任务栏隐藏
	//根据双色图片设置窗口形状（非黑色区域有效）  
    SetRegion(GetDC(),IDB_BITMAP_BACKGROUND,RGB(0,0,0));
	//初始时居中  
    CenterWindow();  
	//sndPlaySound(TEXT("cf_bgm.wav"),SND_ASYNC);
    //设置定时器，处理悬浮窗的显隐移动  
    SetTimer(TIMER_MOVE,10,NULL);  


	m_nid.hWnd = GetSafeHwnd();
	m_nid.uCallbackMessage = UM_TRAYNOTIFY;
	// Set tray icon and tooltip
	m_nid.hIcon = m_hIcon;
	// Set tray notification tip information
	CString strToolTip = _T("直尺");
	_tcsncpy_s(m_nid.szTip, strToolTip, strToolTip.GetLength());
	Shell_NotifyIcon(NIM_ADD, &m_nid);

	//::AfxBeginThread(ThreadFun, NULL);  //这就是创建一个线程并执行了,调用上面的函数弹出一个对话框

	//CButtonDraw *m_Button = new CButtonDraw();
	//m_Button->Create( _T("创建"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,CRect(128,4,178,54) , this, 6001 ); //创建按钮
	//CSliderCtrl* m_Slider = new CSliderCtrl();
	//m_Slider.Create( WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,CRect(10,10,1000,60) , this, 6001 ); //创建按钮
	//m_Slider.SetRang(0,100);//设置滑动范围
	//m_Slider.SetTicFreq(10);//每10个单位画一刻度
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_testFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_testFileDlg::OnPaint()
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
		//CDialog::OnPaint();
		CPaintDC  dc(this);     
        CRect  rect;     
        GetWindowRect(&rect);     
        CDC  dcMem;     
        dcMem.CreateCompatibleDC(&dc);     
        CBitmap  bmpBackground;     
        bmpBackground.LoadBitmap(IDB_BITMAP_BACKGROUND);  //背景图  
        BITMAP  bitmap;     
        bmpBackground.GetBitmap(&bitmap);     
        CBitmap  *pbmpOld=dcMem.SelectObject(&bmpBackground);   
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_testFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFC_testFileDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = (UINT)lParam;
	switch(uMsg)
	{
		case WM_RBUTTONUP:
		{
			//右键处理
			CMenu menuTray;
			CPoint point;
			int id;
			GetCursorPos(&point);

			menuTray.LoadMenu(IDR_MENU_TRAY);
			id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);
#if 0
				CString strInfo;
				strInfo.Format(L"menuid %d", id);
				LPCTSTR strtmp;
				strtmp = strInfo.GetBuffer(0);
				MessageBox(strtmp, L"test");
#endif
			switch(id)
			{
				case IDR_TRAY_EXIT:
					OnOK();
					break;
				case IDR_TRAY_RESTORE:
					//窗口前端显示
					SetForegroundWindow();
					ShowWindow(SW_SHOWNORMAL);
					break;
				case IDR_TRAY_HIDE:
					//窗口隐藏显示
					ShowWindow(SW_HIDE);
					break;
				default:
					break;
			}
			break;
		}
		case WM_LBUTTONDBLCLK:
			SetForegroundWindow();
			ShowWindow(SW_SHOWNORMAL);
			break;
		default:
			break;
	}
	return 0;
}

void CMFC_testFileDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CMFC_testFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
	}
	// TODO: 在此处添加消息处理程序代码
}


//是否靠近屏幕上边缘  
BOOL CMFC_testFileDlg::NearUpBorder()  
{  
    CRect rc;  
    GetWindowRect(rc);  
    if(rc.top<20)  
    {  
        return TRUE;  
    }  
    return FALSE;  
}  

BOOL CMFC_testFileDlg::MouseInWnd()  
{  
    CRect rc;  
    GetWindowRect(rc);  
    POINT pt;  
    GetCursorPos(&pt);  
    if (PtInRect(&rc,pt))  
    {  
        return TRUE;  
    }  
    return FALSE;  
} 

void CMFC_testFileDlg::MoveUp()  
{  
    CRect rc;  
    GetWindowRect(rc);  
    //鼠标进入则下移，显示出来  
    if(MouseInWnd())  
    {  
        int height = rc.Height();  
        if (rc.top>=0)  
        {  
            rc.top = 0;  
        }  
        else  
        {  
            rc.top++;  
        }  
        rc.bottom = rc.top + height;  
        MoveWindow(rc);  
    }  
    //鼠标在别处，窗口就往上移出屏幕  
    else  
    {  
        int height = rc.Height();  
        //窗口向上移动一像素，如果快隐藏(露20)就不移了  
        if (rc.top<= 5 - height)  
        {  
            rc.top = 5 - height;  
            //ShowWindow(SW_HIDE);  
            //m_upDlg-> = this;  
            //m_upDlg->DoModal();  
        }  
        else  
        {  
            rc.top--;  
        }  
        rc.bottom = rc.top + height;  
        MoveWindow(rc);  
    }  
}  

void CMFC_testFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if (nIDEvent == TIMER_MOVE)  
    {  
        //鼠标按着的，就怎么都不移动  
        if (GetKeyState(VK_LBUTTON)<0)  
        {  
            return;  
        }  
        //靠近屏幕上边缘  
        if (NearUpBorder())  
        {  
            //根据鼠标动作进行窗口的移动（鼠标进入区域就向下平移显示，鼠标离开就向上平移隐藏）  
            MoveUp();  
            return;  
        }  
    }  

	CDialog::OnTimer(nIDEvent);
}

void CMFC_testFileDlg::SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor)  
{  
    CDC dcMem;  
    if(!dcMem.CreateCompatibleDC(pDC))  
    {  
        MessageBox(_T("创建兼容DC失败！"));  
    }  
  
    CBitmap bitmap;  
    if(!bitmap.LoadBitmap(BackBitmapID))  
    {  
        MessageBox(_T("加载位图失败！"));  
    }  
  
    if(!dcMem.SelectObject(&bitmap))  
    {  
        MessageBox(_T("选进设备描述表失败！"));  
    }  
  
    BITMAP bitmapinfo;  
    bitmap.GetBitmap(&bitmapinfo);  
    //把窗口设为图片的大小,去掉这个的话，那么程序分割会不正确  
    MoveWindow(0,0,bitmapinfo.bmWidth,bitmapinfo.bmHeight,true);   
    //整体区域  
    CRgn rgn;  
    CRgn tmpRgn;  
    rgn.CreateRectRgn(0,0,bitmapinfo.bmWidth,bitmapinfo.bmHeight);  
    //从整体区域中剔除所有黑色像素区域  
    for(int i=0;i<bitmapinfo.bmWidth;i++)  
    {  
        for(int j=0;j<bitmapinfo.bmHeight;j++)  
        {  
            COLORREF cl=dcMem.GetPixel(i,j);  
            if(cl== TransColor)  
            {  
                tmpRgn.CreateRectRgn(i,j,i+1,j+1);  
                rgn.CombineRgn(&rgn,&tmpRgn,RGN_XOR);  
                tmpRgn.DeleteObject();  
            }  
        }  
    }  
    //设置窗口显示区域  
    SetWindowRgn(rgn,true);  
}  
void CMFC_testFileDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 实现拖动窗口  
    // 发送WM_NCLBUTTONDOWN消息  
    // 使Windows认为鼠标在标题条上  
    // 或SendMessage(WM_SYSCOMMAND,SC_MOVE | HTCAPTION,0);     
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}


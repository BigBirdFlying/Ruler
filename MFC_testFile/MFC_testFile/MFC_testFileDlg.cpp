// MFC_testFileDlg.cpp : ʵ���ļ�
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
	//�߳�Ҫ���õĺ���
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
		CString str; //��ȡϵͳʱ�� ����
		SYSTEMTIME st; 
		GetLocalTime(&st); 
		str.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); 
		SetDlgItemText(hWnd,IDC_EDIT1, str);
		Sleep(1000);
	}
	return 1;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFC_testFileDlg �Ի���




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


// CMFC_testFileDlg ��Ϣ�������

BOOL CMFC_testFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//����������
	//����˫ɫͼƬ���ô�����״���Ǻ�ɫ������Ч��  
    SetRegion(GetDC(),IDB_BITMAP_BACKGROUND,RGB(0,0,0));
	//��ʼʱ����  
    CenterWindow();  
	//sndPlaySound(TEXT("cf_bgm.wav"),SND_ASYNC);
    //���ö�ʱ���������������������ƶ�  
    SetTimer(TIMER_MOVE,10,NULL);  


	m_nid.hWnd = GetSafeHwnd();
	m_nid.uCallbackMessage = UM_TRAYNOTIFY;
	// Set tray icon and tooltip
	m_nid.hIcon = m_hIcon;
	// Set tray notification tip information
	CString strToolTip = _T("ֱ��");
	_tcsncpy_s(m_nid.szTip, strToolTip, strToolTip.GetLength());
	Shell_NotifyIcon(NIM_ADD, &m_nid);

	//::AfxBeginThread(ThreadFun, NULL);  //����Ǵ���һ���̲߳�ִ����,��������ĺ�������һ���Ի���

	//CButtonDraw *m_Button = new CButtonDraw();
	//m_Button->Create( _T("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,CRect(128,4,178,54) , this, 6001 ); //������ť
	//CSliderCtrl* m_Slider = new CSliderCtrl();
	//m_Slider.Create( WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,CRect(10,10,1000,60) , this, 6001 ); //������ť
	//m_Slider.SetRang(0,100);//���û�����Χ
	//m_Slider.SetTicFreq(10);//ÿ10����λ��һ�̶�
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_testFileDlg::OnPaint()
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
		//CDialog::OnPaint();
		CPaintDC  dc(this);     
        CRect  rect;     
        GetWindowRect(&rect);     
        CDC  dcMem;     
        dcMem.CreateCompatibleDC(&dc);     
        CBitmap  bmpBackground;     
        bmpBackground.LoadBitmap(IDB_BITMAP_BACKGROUND);  //����ͼ  
        BITMAP  bitmap;     
        bmpBackground.GetBitmap(&bitmap);     
        CBitmap  *pbmpOld=dcMem.SelectObject(&bmpBackground);   
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
			//�Ҽ�����
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
					//����ǰ����ʾ
					SetForegroundWindow();
					ShowWindow(SW_SHOWNORMAL);
					break;
				case IDR_TRAY_HIDE:
					//����������ʾ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CMFC_testFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
	}
	// TODO: �ڴ˴������Ϣ����������
}


//�Ƿ񿿽���Ļ�ϱ�Ե  
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
    //�����������ƣ���ʾ����  
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
    //����ڱ𴦣����ھ������Ƴ���Ļ  
    else  
    {  
        int height = rc.Height();  
        //���������ƶ�һ���أ����������(¶20)�Ͳ�����  
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (nIDEvent == TIMER_MOVE)  
    {  
        //��갴�ŵģ�����ô�����ƶ�  
        if (GetKeyState(VK_LBUTTON)<0)  
        {  
            return;  
        }  
        //������Ļ�ϱ�Ե  
        if (NearUpBorder())  
        {  
            //������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�  
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
        MessageBox(_T("��������DCʧ�ܣ�"));  
    }  
  
    CBitmap bitmap;  
    if(!bitmap.LoadBitmap(BackBitmapID))  
    {  
        MessageBox(_T("����λͼʧ�ܣ�"));  
    }  
  
    if(!dcMem.SelectObject(&bitmap))  
    {  
        MessageBox(_T("ѡ���豸������ʧ�ܣ�"));  
    }  
  
    BITMAP bitmapinfo;  
    bitmap.GetBitmap(&bitmapinfo);  
    //�Ѵ�����ΪͼƬ�Ĵ�С,ȥ������Ļ�����ô����ָ�᲻��ȷ  
    MoveWindow(0,0,bitmapinfo.bmWidth,bitmapinfo.bmHeight,true);   
    //��������  
    CRgn rgn;  
    CRgn tmpRgn;  
    rgn.CreateRectRgn(0,0,bitmapinfo.bmWidth,bitmapinfo.bmHeight);  
    //�������������޳����к�ɫ��������  
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
    //���ô�����ʾ����  
    SetWindowRgn(rgn,true);  
}  
void CMFC_testFileDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
// ʵ���϶�����  
    // ����WM_NCLBUTTONDOWN��Ϣ  
    // ʹWindows��Ϊ����ڱ�������  
    // ��SendMessage(WM_SYSCOMMAND,SC_MOVE | HTCAPTION,0);     
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}


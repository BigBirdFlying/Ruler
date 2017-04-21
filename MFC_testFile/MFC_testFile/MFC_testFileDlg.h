// MFC_testFileDlg.h : 头文件
//

#pragma once


// CMFC_testFileDlg 对话框
class CMFC_testFileDlg : public CDialog
{
// 构造
public:
	CMFC_testFileDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMFC_testFileDlg();	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_TESTFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	BOOL NearUpBorder(); 
	BOOL MouseInWnd(); 
	void MoveUp();  
	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);  

	//UINT ThreadFun();

// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_nid;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

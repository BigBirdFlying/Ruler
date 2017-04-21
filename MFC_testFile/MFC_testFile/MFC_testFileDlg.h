// MFC_testFileDlg.h : ͷ�ļ�
//

#pragma once


// CMFC_testFileDlg �Ի���
class CMFC_testFileDlg : public CDialog
{
// ����
public:
	CMFC_testFileDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMFC_testFileDlg();	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_TESTFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	BOOL NearUpBorder(); 
	BOOL MouseInWnd(); 
	void MoveUp();  
	void SetRegion(CDC* pDC, UINT BackBitmapID, COLORREF TransColor);  

	//UINT ThreadFun();

// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_nid;

	// ���ɵ���Ϣӳ�亯��
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

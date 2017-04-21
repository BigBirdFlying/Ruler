#pragma once


// CButtonDraw

class CButtonDraw : public CButton
{
	DECLARE_DYNAMIC(CButtonDraw)

public:
	CButtonDraw();
	virtual ~CButtonDraw();


	BOOL m_bOver;
	int m_nTimerId;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};



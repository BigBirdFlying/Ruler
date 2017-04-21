// ButtonDraw.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_testFile.h"
#include "ButtonDraw.h"


// CButtonDraw

IMPLEMENT_DYNAMIC(CButtonDraw, CButton)

CButtonDraw::CButtonDraw()
{
	m_bOver=false;
}

CButtonDraw::~CButtonDraw()
{
}


BEGIN_MESSAGE_MAP(CButtonDraw, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CButtonDraw 消息处理程序



void CButtonDraw::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

void CButtonDraw::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	//CRect rect;
	//GetClientRect(rect);
	//CDC dc;
	//dc.Attach(lpDrawItemStruct->hDC);
	//int x,y,r;
	//x=rect.Width()/2;
	//y=rect.top;
	//r=rect.Height()/2;
	//dc.Ellipse(0,0,rect.Width(),rect.Height());
	//dc.DrawText(TEXT(""),rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	CPen m_OutBorderPen;
	CRect rect = lpDrawItemStruct->rcItem;
   CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
   int nSavedDC = pDC->SaveDC();

   // 绘制按钮的外边框
   POINT pt;
   pt.x = 5;
   pt.y = 5;
   CPen *pOldPen = pDC->SelectObject(&m_OutBorderPen);
   pDC->RoundRect(&rect, pt);
   pDC->SelectObject(pOldPen);

   // 绘制按钮的底色
   CBrush m_BackgroundBrush;
	m_BackgroundBrush.CreateSolidBrush(RGB(0,255,0));
       rect.DeflateRect(3, 3, 3, 3);
       CBrush *pOldBrush = pDC->SelectObject(&m_BackgroundBrush);
       pDC->Rectangle(rect);
       pDC->SelectObject(pOldBrush);

	   // 绘制按钮文本
       TCHAR strButtonText[MAX_PATH + 1];
       ::GetWindowText(m_hWnd, strButtonText, MAX_PATH); // 获取按钮文本
       if (strButtonText != NULL)
       {
              CFont *pFont = GetFont();
              CFont *pOldFont = pDC->SelectObject(pFont);
              CSize szExtent = pDC->GetTextExtent(strButtonText, _tcslen(strButtonText));
              CRect rectText = lpDrawItemStruct->rcItem;
              rectText.DeflateRect(rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2, rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
              int nOldBkMode = pDC->SetBkMode(TRANSPARENT);

				UINT state = lpDrawItemStruct->itemState;
				if (state & ODS_SELECTED)
				{
					rectText.OffsetRect(1, 1);
				}

              pDC->DrawText(strButtonText, -1, rectText, DT_WORDBREAK | DT_CENTER);
              pDC->SelectObject(pOldFont);
              pDC->SetBkMode(nOldBkMode);
       }
}

void CButtonDraw::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (!m_bOver)
 //   {
 //       m_nTimerId = SetTimer(1, 50, TimerProc);
 //       m_bOver = TRUE;
 //   } 

	CButton::OnMouseMove(nFlags, point);
}


void CButtonDraw::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnTimer(nIDEvent);
}

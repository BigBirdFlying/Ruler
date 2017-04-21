// SliderDraw.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_testFile.h"
#include "SliderDraw.h"


// SliderDraw

IMPLEMENT_DYNAMIC(SliderDraw, CSliderCtrl)

SliderDraw::SliderDraw()
{

}

SliderDraw::~SliderDraw()
{
}


BEGIN_MESSAGE_MAP(SliderDraw, CSliderCtrl)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// SliderDraw 消息处理程序



void SliderDraw::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	rect.DeflateRect(13, 13, 13, 13);
	CBrush *pOldBrush = pDC->SelectObject(&m_BackgroundBrush);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);

	CSliderCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

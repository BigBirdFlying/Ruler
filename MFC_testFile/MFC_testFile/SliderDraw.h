#pragma once


// SliderDraw

class SliderDraw : public CSliderCtrl
{
	DECLARE_DYNAMIC(SliderDraw)

public:
	SliderDraw();
	virtual ~SliderDraw();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};



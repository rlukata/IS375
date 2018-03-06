#pragma once
#include "Element.h"
class CCircle :
	public CElement
{
	DECLARE_SERIAL(CCircle)
public:
	CCircle();
	virtual ~CCircle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a circle
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override; // Serialize object
	// Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color);
protected:
	CPoint m_BottomRight; // Bottom-right point for defining circle
};


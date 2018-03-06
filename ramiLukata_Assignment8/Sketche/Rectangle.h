#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
	DECLARE_SERIAL(CRectangle)
public:
	CRectangle();
	virtual ~CRectangle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a rectangle
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override; // Serialize object
	// Constructor for a rectangle object
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);
//	void CRectangle::Draw(CDC* pDC);
protected:
	CPoint m_BottomRight;	// Bottom-right point for the rectangle
};


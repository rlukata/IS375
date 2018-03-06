#pragma once
#include "Element.h"
class CLine :
	public CElement
{
DECLARE_SERIAL(CLine)
public:
	CLine();
	virtual ~CLine(void);
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; // Function to display a line
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override; // Serialize object
	// Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor);
protected:
	CPoint m_EndPoint; // End point of line
};




// SketcherDoc.h : interface of the CSketcherDoc class
//


#pragma once
#include <list>
#include "Elements.h"

class CSketcherDoc : public CDocument
{
	protected: // create from serialization only
		CSketcherDoc();
		DECLARE_DYNCREATE(CSketcherDoc)

	// Attributes
	public:

	// Operations
	public:
		unsigned int GetElementType() const	{ return m_Element; }	// Get the element type
		COLORREF GetElementColor() const { return m_Color;}			// Get the element color
		int GetElementPenStyle() const { return m_PenStyle;}		// Get the element pen style
		void AddElement(CElement* pElement); // Add an element to the list
		std::list<CElement*>::const_iterator begin() const { return m_ElementList.begin(); } // Get list begin iterator
		std::list<CElement*>::const_iterator end() const { return m_ElementList.end(); } // Get list end iterator
		CElement* FindElement(const CPoint & point)const;		// Determine is object has been selected
		void DeleteElement(CElement* pElement); // Delete an element
		void SendToBack(CElement* pElement);	// Send an element backwards in the list
		int GetPenWidth() const { return m_PenWidth; }	// Get the current pen width
		CSize GetDocSize() const { return m_DocSize; }  // Retrieve the document size

	// Overrides
	public:
		virtual BOOL OnNewDocument();
		virtual void Serialize(CArchive& ar);
	#ifdef SHARED_HANDLERS
		virtual void InitializeSearchContent();
		virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
	#endif // SHARED_HANDLERS

	// Implementation
	public:
		virtual ~CSketcherDoc();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:

	// Generated message map functions
	protected:
		DECLARE_MESSAGE_MAP()

	#ifdef SHARED_HANDLERS
		// Helper function that sets search content for a Search Handler
		void SetSearchContent(const CString& value);
	#endif // SHARED_HANDLERS
	public:
		afx_msg void OnColorBlack();
		afx_msg void OnColorGreen();
		afx_msg void OnColorRed();
		afx_msg void OnColorBlue();
		afx_msg void OnColorPink();
		afx_msg void OnElementLine();
		afx_msg void OnElementRectangle();
		afx_msg void OnElementCircle();
		afx_msg void OnElementCurve();
	protected:
		// Current Element Type
		ElementType m_Element;
		// Current Color Type
		COLORREF m_Color;
		// Current Pen Style
		int m_PenStyle;
		// Container to keep track of elements
		std::list<CElement*> m_ElementList; // List of elements in the sketch
		int m_PenWidth;		// Current pen width
		CSize m_DocSize; // Document size

	public:
		afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
		afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
		afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
		afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
		afx_msg void OnUpdateColorPink(CCmdUI *pCmdUI);
		afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
		afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
		afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
		afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
		afx_msg void OnElementEllipse();
		afx_msg void OnUpdateElementEllipse(CCmdUI *pCmdUI);
		afx_msg void OnPenstyleSolid();
		afx_msg void OnPenstyleDashed();
		afx_msg void OnPenstyleDotted();
		afx_msg void OnPenstyleDashDotted();
		afx_msg void OnPenstyleDashDotDotted();
		afx_msg void OnUpdatePenstyleSolid(CCmdUI *pCmdUI);
		afx_msg void OnUpdatePenstyleDashed(CCmdUI *pCmdUI);
		afx_msg void OnUpdatePenstyleDotted(CCmdUI *pCmdUI);
		afx_msg void OnUpdatePenstyleDashDotted(CCmdUI *pCmdUI);
		afx_msg void OnUpdatePenstyleDashDotDotted(CCmdUI *pCmdUI);
		afx_msg void OnPenWidth();
		afx_msg void OnElementText();
		afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
};

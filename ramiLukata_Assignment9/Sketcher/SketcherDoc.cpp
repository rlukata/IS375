
// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "PenDialog.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_PINK, &CSketcherDoc::OnColorPink)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketcherDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_PINK, &CSketcherDoc::OnUpdateColorPink)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcherDoc::OnUpdateElementCurve)
	ON_COMMAND(ID_ELEMENT_ELLIPSE, &CSketcherDoc::OnElementEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_ELLIPSE, &CSketcherDoc::OnUpdateElementEllipse)
	ON_COMMAND(ID_PENSTYLE_SOLID, &CSketcherDoc::OnPenstyleSolid)
	ON_COMMAND(ID_PENSTYLE_DASHED, &CSketcherDoc::OnPenstyleDashed)
	ON_COMMAND(ID_PENSTYLE_DOTTED, &CSketcherDoc::OnPenstyleDotted)
	ON_COMMAND(ID_PENSTYLE_DASH_DOTTED, &CSketcherDoc::OnPenstyleDashDotted)
	ON_COMMAND(ID_PENSTYLE_DASH_DOT_DOTTED, &CSketcherDoc::OnPenstyleDashDotDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_SOLID, &CSketcherDoc::OnUpdatePenstyleSolid)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASHED, &CSketcherDoc::OnUpdatePenstyleDashed)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DOTTED, &CSketcherDoc::OnUpdatePenstyleDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASH_DOTTED, &CSketcherDoc::OnUpdatePenstyleDashDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASH_DOT_DOTTED, &CSketcherDoc::OnUpdatePenstyleDashDotDotted)
	ON_COMMAND(ID_PEN_WIDTH, &CSketcherDoc::OnPenWidth)
	ON_COMMAND(ID_ELEMENT_TEXT, &CSketcherDoc::OnElementText)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CSketcherDoc::OnUpdateElementText)
END_MESSAGE_MAP()


// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc() : m_Element(LINE), m_Color(BLACK), m_PenStyle(PS_SOLID), m_DocSize(CSize(800, 600)), m_PenWidth(0)
{
	// TODO: add one-time construction code here

}

CSketcherDoc::~CSketcherDoc()
{

	// Delete the element pointed to by each list entry
	for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
	{
		delete *iter;
	}
	m_ElementList.clear(); // Finally delete all pointers

}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar	<< m_Color // Store the current color
			<< static_cast<int>(m_Element) // the current element type as an integer
			<< m_PenWidth // and the current pen width
			<< m_DocSize; // and the current document size
		
		ar	<< m_ElementList.size(); // Store the number of elements in the list
		
		// Now store the elements from the list
		for(auto iter = m_ElementList.begin() ; iter != m_ElementList.end() ; ++iter)
		{
			ar << *iter; // Store the element
		}
		
	}
	else
	{
		int elementType(0); // Stores element type
		ar	>> m_Color // Retrieve the current color
			>> elementType // the current element type as an integer
			>> m_PenWidth // and the current pen width
			>> m_DocSize; // and the current document size
		
		m_Element = static_cast<ElementType>(elementType);
		size_t elementCount(0); // Count of number of elements
		
		CObject* pElement(nullptr); // Element pointer
		ar >> elementCount; // retrieve the element count
		
		// Now retrieve all the elements and store in the list
		for(size_t i = 0 ; i < elementCount ; ++i)
		{
			ar >> pElement;
			m_ElementList.push_back(static_cast<CElement*>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc commands

void CSketcherDoc::OnColorBlack()
{
	
	m_Color = BLACK;  // Set the drawing color to black

}

void CSketcherDoc::OnColorGreen()
{
	
	m_Color = GREEN;  // Set the drawing color to green

}

void CSketcherDoc::OnColorRed()
{
		
	m_Color = RED;  // Set the drawing color to red

}

void CSketcherDoc::OnColorBlue()
{
	
	m_Color = BLUE;  // Set the drawing color to blue

}

void CSketcherDoc::OnColorPink()
{

	m_Color = PINK;  // Set the drawing color to blue

}

void CSketcherDoc::OnElementLine()
{
	
	m_Element = LINE;  // Set the drawing element to Line

}

void CSketcherDoc::OnElementRectangle()
{
	
	m_Element = RECTANGLE;  // Set the drawing element to rectangle

}

void CSketcherDoc::OnElementCircle()
{
	
	m_Element = CIRCLE;  // Set the drawing element to circle

}

void CSketcherDoc::OnElementCurve()
{
	
	m_Element = CURVE;  // Set the drawing element to curve

}

void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current color is black
	pCmdUI->SetCheck(m_Color==BLACK);

}

void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current color is green
	pCmdUI->SetCheck(m_Color==GREEN);

}

void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current color is red
	pCmdUI->SetCheck(m_Color==RED);

}

void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current color is blue
	pCmdUI->SetCheck(m_Color==BLUE);

}

void CSketcherDoc::OnUpdateColorPink(CCmdUI *pCmdUI)
{

	// Set menu item Checked if the current color is blue
	pCmdUI->SetCheck(m_Color==PINK);

}

void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current element is line
	pCmdUI->SetCheck(m_Element==LINE);

}

void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current element is rectangle
	pCmdUI->SetCheck(m_Element==RECTANGLE);

}

void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current element is circle
	pCmdUI->SetCheck(m_Element==CIRCLE);

}

void CSketcherDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	
	
	// Set menu item Checked if the current element is curve
	pCmdUI->SetCheck(m_Element==CURVE);


}

void CSketcherDoc::OnElementEllipse()
{
	
	m_Element = ELLIPSE;  // Set the drawing element to ellipse

}

void CSketcherDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current element is curve
	pCmdUI->SetCheck(m_Element==ELLIPSE);

}

void CSketcherDoc::OnPenstyleSolid()
{
	
	m_PenStyle = PS_SOLID;

}

void CSketcherDoc::OnPenstyleDashed()
{
	
	m_PenStyle = PS_DASH;

}

void CSketcherDoc::OnPenstyleDotted()
{
	
	m_PenStyle = PS_DOT;

}

void CSketcherDoc::OnPenstyleDashDotted()
{
	
	m_PenStyle = PS_DASHDOT;

}

void CSketcherDoc::OnPenstyleDashDotDotted()
{
	
	m_PenStyle = PS_DASHDOTDOT;

}

void CSketcherDoc::OnUpdatePenstyleSolid(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current line style is solid
	pCmdUI->SetCheck(m_PenStyle==PS_SOLID);

}

void CSketcherDoc::OnUpdatePenstyleDashed(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current line style is dash
	pCmdUI->SetCheck(m_PenStyle==PS_DASH);

}

void CSketcherDoc::OnUpdatePenstyleDotted(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current line style is dashdot
	pCmdUI->SetCheck(m_PenStyle==PS_DOT);

}

void CSketcherDoc::OnUpdatePenstyleDashDotted(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current line style is dashdot
	pCmdUI->SetCheck(m_PenStyle==PS_DASHDOT);

}

void CSketcherDoc::OnUpdatePenstyleDashDotDotted(CCmdUI *pCmdUI)
{
	
	// Set menu item Checked if the current line style is dashdot
	pCmdUI->SetCheck(m_PenStyle==PS_DASHDOTDOT);

}

CElement* CSketcherDoc::FindElement(const CPoint & point)const
{
	// Finds the element under the point
	for(auto rIter = m_ElementList.rbegin() ; rIter != m_ElementList.rend() ; ++rIter)
	{
		if((*rIter)->GetBoundRect().PtInRect(point))
		return *rIter;
	}
	return nullptr;
}

// Add an element to the sketch
void CSketcherDoc::AddElement(CElement* pElement)
{

	m_ElementList.push_back(pElement);
	SetModifiedFlag();

}

// Delete an element from the sketch
void CSketcherDoc::DeleteElement(CElement* pElement)
{
	if(pElement)
	{
		m_ElementList.remove(pElement); // Remove the pointer from the list
		delete pElement; // Delete the element from the heap
		SetModifiedFlag();
	}

}

void CSketcherDoc::SendToBack(CElement* pElement)
{

	if(pElement)
	{
		m_ElementList.remove(pElement); // Remove the element from the list
		m_ElementList.push_front(pElement); // Put it back at the beginning of the list
	}

}

// Handler for the pen width menu item
void CSketcherDoc::OnPenWidth()
{
	CPenDialog aDlg; // Create a local dialog object
	// Set the pen width in the dialog to that stored in the document
	aDlg.m_PenWidth = m_PenWidth;
	// Display the dialog as modal
	// When closed with OK, get the pen width
	if(aDlg.DoModal() == IDOK)
	{
		m_PenWidth = aDlg.m_PenWidth;
	}
}


void CSketcherDoc::OnElementText()
{
	m_Element = TEXT;
}


void CSketcherDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
	// Set checked if the current element is text
	pCmdUI->SetCheck(m_Element == TEXT);
}
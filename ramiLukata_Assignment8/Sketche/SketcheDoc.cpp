
// SketcheDoc.cpp : implementation of the CSketcheDoc class
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketche.h"
#endif

#include "SketcheDoc.h"
#include <propkey.h>
#include <sqltypes.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcheDoc

IMPLEMENT_DYNCREATE(CSketcheDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcheDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLAC, &CSketcheDoc::OnColorBlac)
	ON_COMMAND(ID_COLOR_RED, &CSketcheDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcheDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcheDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_PINK, &CSketcheDoc::OnColorPink)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcheDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcheDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcheDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketcheDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLAC, &CSketcheDoc::OnUpdateColorBlac)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcheDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcheDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcheDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_PINK, &CSketcheDoc::OnUpdateColorPink)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcheDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcheDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcheDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcheDoc::OnUpdateElementCurve)
END_MESSAGE_MAP()


// CSketcheDoc construction/destruction

CSketcheDoc::CSketcheDoc(): m_Element(ElementType::LINE), m_Color(ElementColor::BLACK)/*, m_PenWidth(0), m_DocSize(CSize(3000, 3000))*/
{
	// TODO: add one-time construction code here

}

CSketcheDoc::~CSketcheDoc()
{
	// Get the position at the head of the list
	/*POSITION aPosition = m_ElementList.GetHeadPosition();

	// Now delete the element pointed to by each list entry
	while (aPosition)
		delete m_ElementList.GetNext(aPosition);

	m_ElementList.RemoveAll();   // Finally delete all pointers*/
}

BOOL CSketcheDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketcheDoc serialization

void CSketcheDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << static_cast<COLORREF>(m_Color)        // Store the current color
			<< static_cast<int>(m_Element);         // the element type as an integer

		ar << m_Sketch.size();                      // Store the number of elements in the list

		// Now store the elements from the list
		for (auto& pElement : m_Sketch) {
			ar << pElement.get();                     // Store the element pointer
		}
	}
	else
	{
		COLORREF color(0);
		int elementType(0);
		ar >> color                                 // Retrieve the current color
			>> elementType;                         // the element type as an integer
		m_Color = static_cast<ElementColor>(color);
		m_Element = static_cast<ElementType>(elementType);

		// Now retrieve all the elements and store in the list
		size_t elementCount(0);                     // Count of number of elements
		ar >> elementCount;                         // retrieve the element count
		CElement* pElement;
		for(size_t i = 0 ; i < elementCount ; ++i)
		{
			ar >> pElement;
			m_Sketch.push_back(std::shared_ptr<CElement>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketcheDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSketcheDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcheDoc::SetSearchContent(const CString& value)
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

// CSketcheDoc diagnostics

#ifdef _DEBUG
void CSketcheDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcheDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcheDoc commands


void CSketcheDoc::OnColorBlac()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::BLACK;          // Set the drawing color to black
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnColorGreen()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::GREEN;          // Set the drawing color to green
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnColorRed()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::RED;          // Set the drawing color to red
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnColorPink()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::PINK;          // Set the drawing color to pink
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnColorBlue()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::BLUE;          // Set the drawing color to blue
	SetModifiedFlag(); // Set the modified flag
}

void CSketcheDoc::OnElementLine()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::LINE; // Set element type as a line
	SetModifiedFlag(); // Set the modified flag
}

void CSketcheDoc::OnElementRectangle()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::RECTANGLE; // Set element type as a rectangle
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnElementCircle()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::CIRCLE; // Set element type as a circle
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnElementCurve()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::CURVE; // Set element type as a CURVE
	SetModifiedFlag(); // Set the modified flag
}


void CSketcheDoc::OnUpdateColorBlac(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set menu item Checked if the current color is black
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CSketcheDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set menu item Checked if the current color is blue
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}


void CSketcheDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set menu item Checked if the current color is GREEN
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CSketcheDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set menu item Checked if the current color is RED
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CSketcheDoc::OnUpdateColorPink(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set menu item Checked if the current color is PINK
	pCmdUI->SetCheck(m_Color == ElementColor::PINK);
}


void CSketcheDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set Checked if the current element is a line
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CSketcheDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set Checked if the current element is a RECTANGLE
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CSketcheDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set Checked if the current element is a CIRCLE
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CSketcheDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// Set Checked if the current element is a CURVE	
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}

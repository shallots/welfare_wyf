#pragma once


// CCListBox

class CCListBox : public CListBox
{
	DECLARE_DYNAMIC(CCListBox)

public:
	CCListBox();
	virtual ~CCListBox();
    int AddString( LPCTSTR lpszItem);
    int AddString( LPCTSTR lpszItem, COLORREF rgb);
    int InsertString( int nIndex, LPCTSTR lpszItem, COLORREF rgb);
	int CCListBox::InsertString(int nIndex,LPCTSTR lpszItem);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};



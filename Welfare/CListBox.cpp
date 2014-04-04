// CListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Welfare.h"
#include "CListBox.h"


// CCListBox

IMPLEMENT_DYNAMIC(CCListBox, CListBox)

CCListBox::CCListBox()
{

}

CCListBox::~CCListBox()
{
}


BEGIN_MESSAGE_MAP(CCListBox, CListBox)
	ON_WM_DRAWITEM_REFLECT()
END_MESSAGE_MAP()



// CCListBox 消息处理程序

int CCListBox::AddString( LPCTSTR lpszItem)
{
	return ((CListBox*)this)->AddString(lpszItem);
}

int CCListBox::AddString( LPCTSTR lpszItem, COLORREF rgb)
{
	int item = AddString(lpszItem);
	if(item>=0)
	{
		SetItemData(item,rgb);
	}
	return item;
}

int CCListBox::InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb)
{
	int item = ((CListBox*)this)->InsertString(nIndex,lpszItem);
	if(item>=0)
		SetItemData(item,rgb);
	return item;
}

int CCListBox::InsertString(int nIndex,LPCTSTR lpszItem)
{
	return ((CListBox*)this)->InsertString(nIndex,lpszItem);
}


void CCListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此处添加消息处理程序代码
	if(lpDrawItemStruct->itemID < 0)
		return;
	COLORREF cvText;
	COLORREF cvBack;

	CString itemString;
	if((lpDrawItemStruct->itemState && ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction && (ODA_SELECT | ODA_DRAWENTIRE)))
		DrawFocusRect(lpDrawItemStruct->hDC,&lpDrawItemStruct->rcItem);
	if(!(lpDrawItemStruct->itemState && ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction && ODA_SELECT))
		DrawFocusRect(lpDrawItemStruct->hDC,&lpDrawItemStruct->rcItem);
	if(lpDrawItemStruct->itemData)
		cvText = SetTextColor(lpDrawItemStruct->hDC,lpDrawItemStruct->itemData);
	else
		cvText = SetTextColor(lpDrawItemStruct->hDC,GetSysColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
	cvBack = SetBkColor(lpDrawItemStruct->hDC, GetSysColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_WINDOW)); 
	GetText(lpDrawItemStruct->itemID, itemString );
	DrawText(lpDrawItemStruct->hDC, itemString, -1, &lpDrawItemStruct->rcItem, DT_LEFT | DT_SINGLELINE);
	SetTextColor(lpDrawItemStruct->hDC, cvText);
	SetBkColor(lpDrawItemStruct->hDC, cvBack);
}

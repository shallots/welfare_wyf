// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "D:\\Program Files (x86)\\Microsoft Office\\OFFICE11\\MSWORD.OLB" no_namespace
// CParagraphs ��װ��
#pragma once
#include <afxdisp.h>        // MFC �Զ�����

class CParagraphs : public COleDispatchDriver
{
public:
	CParagraphs(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CParagraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CParagraphs(const CParagraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// Paragraphs ����
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_First()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Last()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Format()
	{
		LPDISPATCH result;
		InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Format(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_TabStops()
	{
		LPDISPATCH result;
		InvokeHelper(0x44f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_TabStops(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Borders()
	{
		LPDISPATCH result;
		InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Borders(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Style()
	{
		VARIANT result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Style(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Alignment()
	{
		long result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Alignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_KeepTogether()
	{
		long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_KeepTogether(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_KeepWithNext()
	{
		long result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_KeepWithNext(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PageBreakBefore()
	{
		long result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PageBreakBefore(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_NoLineNumber()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_NoLineNumber(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_RightIndent()
	{
		float result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_RightIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_LeftIndent()
	{
		float result;
		InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_LeftIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_FirstLineIndent()
	{
		float result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_FirstLineIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_LineSpacing()
	{
		float result;
		InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_LineSpacing(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_LineSpacingRule()
	{
		long result;
		InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LineSpacingRule(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_SpaceBefore()
	{
		float result;
		InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_SpaceBefore(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_SpaceAfter()
	{
		float result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_SpaceAfter(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Hyphenation()
	{
		long result;
		InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Hyphenation(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_WidowControl()
	{
		long result;
		InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_WidowControl(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Shading()
	{
		LPDISPATCH result;
		InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_FarEastLineBreakControl()
	{
		long result;
		InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_FarEastLineBreakControl(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_WordWrap()
	{
		long result;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_WordWrap(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HangingPunctuation()
	{
		long result;
		InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HangingPunctuation(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HalfWidthPunctuationOnTopOfLine()
	{
		long result;
		InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HalfWidthPunctuationOnTopOfLine(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AddSpaceBetweenFarEastAndAlpha()
	{
		long result;
		InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AddSpaceBetweenFarEastAndAlpha(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AddSpaceBetweenFarEastAndDigit()
	{
		long result;
		InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AddSpaceBetweenFarEastAndDigit(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BaseLineAlignment()
	{
		long result;
		InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BaseLineAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AutoAdjustRightIndent()
	{
		long result;
		InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoAdjustRightIndent(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DisableLineHeightGrid()
	{
		long result;
		InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DisableLineHeightGrid(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_OutlineLevel()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OutlineLevel(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	LPDISPATCH Add(VARIANT * Range)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Range);
		return result;
	}
	void CloseUp()
	{
		InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OpenUp()
	{
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OpenOrCloseUp()
	{
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void TabHangingIndent(short Count)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Count);
	}
	void TabIndent(short Count)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x132, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Count);
	}
	void Reset()
	{
		InvokeHelper(0x138, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Space1()
	{
		InvokeHelper(0x139, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Space15()
	{
		InvokeHelper(0x13a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Space2()
	{
		InvokeHelper(0x13b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void IndentCharWidth(short Count)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x140, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Count);
	}
	void IndentFirstLineCharWidth(short Count)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x142, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Count);
	}
	void OutlinePromote()
	{
		InvokeHelper(0x144, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OutlineDemote()
	{
		InvokeHelper(0x145, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OutlineDemoteToBody()
	{
		InvokeHelper(0x146, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Indent()
	{
		InvokeHelper(0x14d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Outdent()
	{
		InvokeHelper(0x14e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	float get_CharacterUnitRightIndent()
	{
		float result;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_CharacterUnitRightIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_CharacterUnitLeftIndent()
	{
		float result;
		InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_CharacterUnitLeftIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_CharacterUnitFirstLineIndent()
	{
		float result;
		InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_CharacterUnitFirstLineIndent(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_LineUnitBefore()
	{
		float result;
		InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_LineUnitBefore(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_LineUnitAfter()
	{
		float result;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_LineUnitAfter(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ReadingOrder()
	{
		long result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ReadingOrder(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SpaceBeforeAuto()
	{
		long result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SpaceBeforeAuto(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SpaceAfterAuto()
	{
		long result;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SpaceAfterAuto(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void IncreaseSpacing()
	{
		InvokeHelper(0x14f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DecreaseSpacing()
	{
		InvokeHelper(0x150, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// Paragraphs ����
public:

};


// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "Welfare.h"
#include "DlgProxy.h"
#include "WelfareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWelfareDlgAutoProxy

IMPLEMENT_DYNCREATE(CWelfareDlgAutoProxy, CCmdTarget)

CWelfareDlgAutoProxy::CWelfareDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CWelfareDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CWelfareDlg)))
		{
			m_pDialog = reinterpret_cast<CWelfareDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CWelfareDlgAutoProxy::~CWelfareDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CWelfareDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CWelfareDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWelfareDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IWelfare 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {5ED7BFFF-BF58-4689-A65C-11D4A2C93DA8}
static const IID IID_IWelfare =
{ 0x5ED7BFFF, 0xBF58, 0x4689, { 0xA6, 0x5C, 0x11, 0xD4, 0xA2, 0xC9, 0x3D, 0xA8 } };

BEGIN_INTERFACE_MAP(CWelfareDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CWelfareDlgAutoProxy, IID_IWelfare, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {064F636F-DB71-4D4A-BA15-5F33353F180B}
IMPLEMENT_OLECREATE2(CWelfareDlgAutoProxy, "Welfare.Application", 0x64f636f, 0xdb71, 0x4d4a, 0xba, 0x15, 0x5f, 0x33, 0x35, 0x3f, 0x18, 0xb)


// CWelfareDlgAutoProxy 消息处理程序

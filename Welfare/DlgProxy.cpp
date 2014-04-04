
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CWelfareDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CWelfareDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWelfareDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IWelfare ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {5ED7BFFF-BF58-4689-A65C-11D4A2C93DA8}
static const IID IID_IWelfare =
{ 0x5ED7BFFF, 0xBF58, 0x4689, { 0xA6, 0x5C, 0x11, 0xD4, 0xA2, 0xC9, 0x3D, 0xA8 } };

BEGIN_INTERFACE_MAP(CWelfareDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CWelfareDlgAutoProxy, IID_IWelfare, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {064F636F-DB71-4D4A-BA15-5F33353F180B}
IMPLEMENT_OLECREATE2(CWelfareDlgAutoProxy, "Welfare.Application", 0x64f636f, 0xdb71, 0x4d4a, 0xba, 0x15, 0x5f, 0x33, 0x35, 0x3f, 0x18, 0xb)


// CWelfareDlgAutoProxy ��Ϣ�������


// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CWelfareDlg;


// CWelfareDlgAutoProxy ����Ŀ��

class CWelfareDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CWelfareDlgAutoProxy)

	CWelfareDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CWelfareDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CWelfareDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CWelfareDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


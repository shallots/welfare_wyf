
// WelfareDlg.h : 头文件
//

#pragma once
#include "Encode.h"
#include "CListBox.h"
#include <stack>
#include "afxwin.h"

using std::stack;
class CWelfareDlgAutoProxy;

typedef struct
{
	CodeType ctCode;
	CString code;
	int index;
}RECOVER;
// CWelfareDlg 对话框
class CWelfareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWelfareDlg);
	friend class CWelfareDlgAutoProxy;

// 构造
public:
	CWelfareDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CWelfareDlg();

// 对话框数据
	enum { IDD = IDD_WELFARE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// zi自定义函数
// 自定义变量
private:
	CString GetFileVer();
public:
	Encode *ec;
	BOOL forcastFlag; // 预测标志
	CWinThread *pThread;
	HANDLE CreateThreadEvent;

	int totalCodeCount; // 总数
	int killCodeCount;	// 杀码数
	int oddCodeCount;	// 余码数

	CStatusBar m_StatusBar; // 状态栏
	stack<RECOVER> recoverCodeStack;
// 实现
protected:
	CWelfareDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_arr1;
	CEdit m_arr2;
	CEdit m_arr3;
	CEdit m_boldCode;
	CButton m_checkTip;
	CButton m_export;
	CButton m_forcast;
	CEdit m_issue;
	CButton m_killCode;
	CCListBox m_listCode;
	CEdit m_plusTail;
	CRichEditCtrl m_REInfo;
	CButton m_reset;
	CButton m_revocation;
	CEdit m_twoCode;
	afx_msg void OnSetfocusIssue();
	afx_msg void OnSetfocusArr1();
	afx_msg void OnSetfocusArr2();
//	afx_msg void OnChangeArr3();
	afx_msg void OnSetfocusBoldcode();
	afx_msg void OnSetfocusPlustail();
	afx_msg void OnSetfocusTwocode();
	afx_msg void OnSetfocusArr3();
	afx_msg void OnBnClickedForcast();
	afx_msg void OnBnClickedKillcode();
	afx_msg void OnBnClickedExport();
	afx_msg void OnBnClickedReset();
	afx_msg void OnDblclkListcode();
	afx_msg void OnBnClickedRevocation();
	afx_msg void OnEnChangeTwocode();
	CButton m_sift;
	//CButton m_direct;
	afx_msg void OnClickedSift();
//	afx_msg void OnDoubleclickedSift();
//	afx_msg void OnLbnSelchangeListcode();
	afx_msg void OnSave();
	afx_msg void OnQuit();
//	CButton m_prePrint;
//	afx_msg void OnBnClickedPreprint();
	CEdit m_arr4;
	afx_msg void OnSetfocusArr4();
	afx_msg void OnAbout();
	afx_msg void OnSelchangeListcode();
	CButton m_killABL;
	CButton m_killAOE;
//	CButton m_killPair;
	afx_msg void OnBnClickedKillpair();
	afx_msg void OnBnClickedKilloddeven();
	afx_msg void OnBnClickedKillbiglittle();
	CButton m_groupChoose;
	CEdit m_hundred;
	CEdit m_decade;
	CEdit m_unit;
	CEdit m_dshou;
	CButton m_deCheck;
	afx_msg void OnEnChangeDshou();
	afx_msg void OnSetfocusDshou();
	afx_msg void OnClickedDecheck();
};
int isInSift(CString code);
BOOL isExtreme(const vector<CodeType>::iterator it);
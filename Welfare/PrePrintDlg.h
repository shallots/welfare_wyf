#pragma once
#include "WelfareDlg.h"

// CPrePrintDlg 对话框

class CPrePrintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrePrintDlg)

public:
	CPrePrintDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrePrintDlg();

// 对话框数据
	enum { IDD = IDD_PREPRINTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	virtual void OnCancel();

	// 自定义变量
	BOOL resSave;
	int totalAmount;
	int totalCount;

	DECLARE_MESSAGE_MAP()
public:
	CWelfareDlg *cParentWnd;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedExport2();
	CButton m_export2;
	CEdit m_gos;
	CButton m_preView;
	CEdit m_rsc;
	CButton m_static_gos;
	CButton m_static_rsc;
	CListBox m_gosNList;
	//CListBox m_gosPList;
	CListBox m_rscNList;
	//CListBox m_rscPList;
	CStatic m_sgosNonpair;
	//CStatic m_sgosPair;
	CStatic m_srscNonpair;
	//CStatic m_srscPair;
};

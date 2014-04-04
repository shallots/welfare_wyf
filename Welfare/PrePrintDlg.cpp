// PrePrintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Welfare.h"
#include "PrePrintDlg.h"
#include "afxdialogex.h"


// 定义控件ID
//#define IDC_RSC_PAIRS		5201
//#define IDC_RSC_PLIST		5202
//#define IDC_RSC_NONPAIRS	5203
//#define IDC_RSC_NLIST		5204
//#define IDC_GOS_PAIRS		5205
//#define IDC_GOS_PLIST		5206
//#define IDC_GOS_NONPAIRS	5202
//#define IDC_GOS_NLIST		5207
// CPrePrintDlg 对话框

IMPLEMENT_DYNAMIC(CPrePrintDlg, CDialogEx)

CPrePrintDlg::CPrePrintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrePrintDlg::IDD, pParent)
{

}

CPrePrintDlg::~CPrePrintDlg()
{
}

void CPrePrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPORT2, m_export2);
	DDX_Control(pDX, IDC_GOS, m_gos);
	DDX_Control(pDX, IDC_PREVIEW, m_preView);
	DDX_Control(pDX, IDC_RSC, m_rsc);
	DDX_Control(pDX, IDC_STATIC_GOS, m_static_gos);
	DDX_Control(pDX, IDC_STATIC_RSC, m_static_rsc);
	DDX_Control(pDX, IDC_GOS_NLIST, m_gosNList);
	//DDX_Control(pDX, IDC_GOS_PLIST, m_gosPList);
	DDX_Control(pDX, IDC_RSC_NLIST, m_rscNList);
	//DDX_Control(pDX, IDC_RSC_PLIST, m_rscPList);
	DDX_Control(pDX, IDC_STATIC_GOS_NONPAIR, m_sgosNonpair);
	//DDX_Control(pDX, IDC_STATIC_GOS_PAIR, m_sgosPair);
	DDX_Control(pDX, IDC_STATIC_RSC_NONPAIR, m_srscNonpair);
	//DDX_Control(pDX, IDC_STATIC_RSC_PAIR, m_srscPair);
}


BEGIN_MESSAGE_MAP(CPrePrintDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PREVIEW, &CPrePrintDlg::OnBnClickedPreview)
	ON_BN_CLICKED(IDC_EXPORT2, &CPrePrintDlg::OnBnClickedExport2)
END_MESSAGE_MAP()

void CPrePrintDlg::OnOK()
{
	NextDlgCtrl();
}

void CPrePrintDlg::OnCancel()
{
	//if (CanExit())
	//	CDialogEx::OnCancel();
	int key=0;
	if(!resSave)
	{	
		key = MessageBox(_T("不导出结果关闭?"),_T("关闭？"),MB_OKCANCEL);
	}else{
		key = IDOK;
	}
	if(key == IDOK)
		CDialog::OnCancel();
}

//BOOL IsPair(CString code)
//{
//	int length = code.GetLength();
//	if(length <= 0)
//		return false;
//	char *p = (LPSTR)(LPCTSTR)code;
//	if( *p == *(p+2) || *p == *(p+4) || *(p+2) == *(p+4))
//	{
//		return true;
//	}
//	return false;
//}
// CPrePrintDlg 消息处理程序


BOOL CPrePrintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	resSave = TRUE;
	totalAmount = 0;
	totalCount = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL isInPlusTail(int tailVal, vector<int> plusTail)
{
	for(vector<int>::iterator it = plusTail.begin(); it != plusTail.end(); it++)
	{
		if(tailVal == *it)
			return TRUE;
	}
	return FALSE;
}

BOOL isPair(vector<CodeType>::iterator code)
{
	if(code->codeSeq[0] == code->codeSeq[1] || code->codeSeq[0] == code->codeSeq[2]
	|| code->codeSeq[1] == code->codeSeq[2])
		return TRUE;
	return FALSE;
}

void CPrePrintDlg::OnBnClickedPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<int> arrkc[2]; // 单选单复式和组选和尾值数字序列
	CString csstr[2]; // 单选单复式和组选和尾值

	m_rsc.GetWindowTextW(csstr[0]);
	m_gos.GetWindowTextW(csstr[1]);

	// 取得两组筛选码
	if(csstr[0].GetLength()||csstr[1].GetLength())
	{
		for(int i=0; i<2; i++)
		{
			int length = csstr[i].GetLength();
			char *p = (LPSTR)(LPCTSTR)csstr[i];
			for(int j=0; j<2*length; j=j+2)
			{
				int tmp = *(p+j) - 48;
				arrkc[i].push_back(tmp);
			}
		}
	}else{
		MessageBox(_T("请输入筛选和值尾！"));
		return;
	}
	m_rscNList.ResetContent();
	m_gosNList.ResetContent();
	// 遍历3D码，分别插入对应的列表中
	for(vector<CodeType>::iterator it = cParentWnd->ec->dvCode.begin(); it!=cParentWnd->ec->dvCode.end(); it++)
	{
		CString tmp;
		tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		if(isInPlusTail(it->mantissa,arrkc[0]))
		{
			if(isPair(it))
			{
				//m_rscPList.AddString(tmp);
			}else{
				m_rscNList.AddString(tmp);
			}
		}else if(isInPlusTail(it->mantissa,arrkc[1]))
		{
			if(isPair(it))
			{
				//m_gosPList.AddString(tmp);
			}else{
				m_gosNList.AddString(tmp);
			}
		}
	}
	// 统计信息
	//int nrscPList = m_rscPList.GetCount();			// 单选单复式对子3D码个数
	//int nrscPAmount = nrscPList * 6 ;				// 单选单复式对子3D码投注金额
	int nrscNList = m_rscNList.GetCount();			// 单选单复式非对子3D码个数
	int nrscNAmount = nrscNList * 12 ;				// 单选单复式非对子3D码投注金额
	int nrscTAmount = nrscNAmount;	// 单选单复式3D码投注金额小计

	//int ngosPList = m_gosPList.GetCount();			// 组选对子个数
	//int ngosPAmount = ngosPList * 2;				// 组选对子金额
	int ngosNList = m_gosNList.GetCount();			// 组选非对子个数
	int ngosNAmount = ngosNList * 2;				// 组选非对子金额
	int ngosTAmount = ngosNAmount;	// 组选非对子金额小计

	totalCount = nrscNList + ngosNList;
	totalAmount = nrscTAmount + ngosTAmount;

	CString text;
	CString tmp;

	tmp.Format(_T("※ 单选单复式 ( 共 %d 注，投注金额: ￥%d.00 )"),nrscNList,nrscTAmount);
	text += tmp;
	m_static_rsc.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();

	tmp.Format(_T("非对子 ( 共 %d 注，投注金额: ￥%d.00 )"),nrscNList,nrscNAmount);
	text += tmp;
	m_srscNonpair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	/*
	m_srscPair.GetWindowTextW(text);
	tmp.Format(_T(" ( 共 %d 注，投注金额: ￥%d.00 )"),nrscPList,nrscPAmount);
	text += tmp;
	
	m_srscPair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	*/


	//m_sgosNonpair.GetWindowTextW(text);
	tmp.Format(_T(" 非对子( 共 %d 注，投注金额: ￥%d.00 )"),ngosNList,ngosNAmount);
	text += tmp;
	m_sgosNonpair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	/*
	m_sgosPair.GetWindowTextW(text);
	tmp.Format(_T(" ( 共 %d 注，投注金额: ￥%d.00 )"),ngosPList,ngosPAmount);
	text += tmp;
	m_sgosPair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	*/
	//m_static_gos.GetWindowTextW(text);
	tmp.Format(_T(" ※ 组选 ( 共 %d 注，投注金额: ￥%d.00 )"),ngosNList,ngosTAmount);
	text += tmp;
	m_static_gos.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();

	UpdateWindow();
	resSave = FALSE;
}


void CPrePrintDlg::OnBnClickedExport2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(resSave)
	{
		MessageBox(_T("请预览后再导出,^_^!!"));
		return;
	}
	int countnrsc = m_rscNList.GetCount();
	//int countprsc = m_rscPList.GetCount();
	int countngos = m_gosNList.GetCount();
	//int countpgos = m_gosPList.GetCount();

	if(totalCount <= 0)
	{
		MessageBox(_T("列表3D编码为空,无需导出"));
		return;
	}

	TCHAR szFilter[] = _T("Word文件(*.doc)|*.doc|文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	
	TCHAR *filename = NULL;
	CString cf;
	cParentWnd->m_issue.GetWindowTextW(cf);
	int issue = 888;
	if(cf.GetLength())
	{
		cf += _T("期3D码预测");
		issue = _ttoi(cf);
		filename = cf.GetBuffer(cf.GetLength());
	}

	CFileDialog f_Export(FALSE,
		_T("doc"),
		filename,
		OFN_OVERWRITEPROMPT |OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
		szFilter,
		this);	
	CString fpath;

	if(f_Export.DoModal() == IDOK)
	{
		fpath = f_Export.GetPathName();
	}else{
		MessageBox(_T("请输入导出文件名"),_T("导出"),MB_OK);
		return;
	}
	CFile fout(fpath,CFile::modeCreate | CFile::modeReadWrite);
	fout.Write("\xff\xfe",2);

	CString str;
	//str.Format(_T("\t\t\t\t\t第 %d 期 福彩3D码预测打印报表\n\t\t共计 %d 个3D码.杀码 %d 个.余码 %d 个 建议投注金额: ￥%d.00  \n\n"),issue,cParentWnd->totalCodeCount,
	//	cParentWnd->totalCodeCount-totalCount,totalCount,totalAmount);
	str.Format(_T("\t\t\t\t\t第 %d 期 福彩3D码预测打印报表\n\t\t\t\t\t\t(共计 %d 注3D码)\n\n\n"),issue,cParentWnd->totalCodeCount);
	fout.Write(str,sizeof(TCHAR)*str.GetLength());

	CString codeString;
	CString itemString;
	CString subitem;
	int sizetchar = sizeof(TCHAR);
	// 导出单选单复式

	//m_static_rsc.GetWindowTextW(itemString);
	//m_srscNonpair.GetWindowTextW(subitem);
	//itemString += _T("\n") + subitem + _T("\n");
	itemString.Format(_T("单选单复式： %d 注\n"),countnrsc);
	fout.Write(itemString, sizetchar*itemString.GetLength());
	itemString.Empty();
	subitem.Empty();

	for(int i=0; i<countnrsc; i++)
	{
		m_rscNList.GetText(i,codeString);
		if(1 + i != countnrsc)
			codeString += _T("     ");
		fout.Write(codeString,sizetchar * codeString.GetLength());
	}
	fout.Write(_T("\n\n\n\n"),sizetchar);
	/* 关于对子的预测另有程式预测
	m_srscPair.GetWindowTextW(subitem);
	subitem += _T("\n");
	fout.Write(subitem, sizetchar * subitem.GetLength());
	for(int i=0; i<countprsc; i++)
	{
		m_rscPList.GetText(i,codeString);
		if(1 + i != countprsc)
			codeString += _T("     ");
		fout.Write(codeString,sizetchar * codeString.GetLength());
	}
	fout.Write(_T("\n\n"),sizetchar*2);
	*/

	// 导出组选
	/*
	m_static_gos.GetWindowTextW(itemString);
	m_sgosNonpair.GetWindowTextW(subitem);
	itemString += _T("\n") + subitem + _T("\n");
	*/
	itemString.Format(_T("\n\n组选: %d 注 \n"),countngos);
	fout.Write(itemString, sizetchar*itemString.GetLength());
	
	itemString.Empty();
	subitem.Empty();

	for(int i=0; i<countngos; i++)
	{
		m_gosNList.GetText(i,codeString);
		if(1 + i != countngos)
			codeString += _T("     ");
		fout.Write(codeString,sizetchar * codeString.GetLength());
	}
	fout.Write(_T("\n"),sizetchar);
	/*
	m_sgosPair.GetWindowTextW(subitem);
	subitem += _T("\n");
	fout.Write(subitem, sizetchar * subitem.GetLength());
	for(int i=0; i<countpgos; i++)
	{
		m_gosPList.GetText(i,codeString);
		if(1 + i != countpgos)
			codeString += _T("     ");
		fout.Write(codeString,sizetchar * codeString.GetLength());
	}
	fout.Write(_T("\n"),sizetchar);
	*/
	fout.Close();
	resSave = TRUE;
	MessageBox(_T("导出成功"),_T("提示"));
}

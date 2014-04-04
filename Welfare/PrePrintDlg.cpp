// PrePrintDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Welfare.h"
#include "PrePrintDlg.h"
#include "afxdialogex.h"


// ����ؼ�ID
//#define IDC_RSC_PAIRS		5201
//#define IDC_RSC_PLIST		5202
//#define IDC_RSC_NONPAIRS	5203
//#define IDC_RSC_NLIST		5204
//#define IDC_GOS_PAIRS		5205
//#define IDC_GOS_PLIST		5206
//#define IDC_GOS_NONPAIRS	5202
//#define IDC_GOS_NLIST		5207
// CPrePrintDlg �Ի���

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
		key = MessageBox(_T("����������ر�?"),_T("�رգ�"),MB_OKCANCEL);
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
// CPrePrintDlg ��Ϣ�������


BOOL CPrePrintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	resSave = TRUE;
	totalAmount = 0;
	totalCount = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	vector<int> arrkc[2]; // ��ѡ����ʽ����ѡ��βֵ��������
	CString csstr[2]; // ��ѡ����ʽ����ѡ��βֵ

	m_rsc.GetWindowTextW(csstr[0]);
	m_gos.GetWindowTextW(csstr[1]);

	// ȡ������ɸѡ��
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
		MessageBox(_T("������ɸѡ��ֵβ��"));
		return;
	}
	m_rscNList.ResetContent();
	m_gosNList.ResetContent();
	// ����3D�룬�ֱ�����Ӧ���б���
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
	// ͳ����Ϣ
	//int nrscPList = m_rscPList.GetCount();			// ��ѡ����ʽ����3D�����
	//int nrscPAmount = nrscPList * 6 ;				// ��ѡ����ʽ����3D��Ͷע���
	int nrscNList = m_rscNList.GetCount();			// ��ѡ����ʽ�Ƕ���3D�����
	int nrscNAmount = nrscNList * 12 ;				// ��ѡ����ʽ�Ƕ���3D��Ͷע���
	int nrscTAmount = nrscNAmount;	// ��ѡ����ʽ3D��Ͷע���С��

	//int ngosPList = m_gosPList.GetCount();			// ��ѡ���Ӹ���
	//int ngosPAmount = ngosPList * 2;				// ��ѡ���ӽ��
	int ngosNList = m_gosNList.GetCount();			// ��ѡ�Ƕ��Ӹ���
	int ngosNAmount = ngosNList * 2;				// ��ѡ�Ƕ��ӽ��
	int ngosTAmount = ngosNAmount;	// ��ѡ�Ƕ��ӽ��С��

	totalCount = nrscNList + ngosNList;
	totalAmount = nrscTAmount + ngosTAmount;

	CString text;
	CString tmp;

	tmp.Format(_T("�� ��ѡ����ʽ ( �� %d ע��Ͷע���: ��%d.00 )"),nrscNList,nrscTAmount);
	text += tmp;
	m_static_rsc.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();

	tmp.Format(_T("�Ƕ��� ( �� %d ע��Ͷע���: ��%d.00 )"),nrscNList,nrscNAmount);
	text += tmp;
	m_srscNonpair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	/*
	m_srscPair.GetWindowTextW(text);
	tmp.Format(_T(" ( �� %d ע��Ͷע���: ��%d.00 )"),nrscPList,nrscPAmount);
	text += tmp;
	
	m_srscPair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	*/


	//m_sgosNonpair.GetWindowTextW(text);
	tmp.Format(_T(" �Ƕ���( �� %d ע��Ͷע���: ��%d.00 )"),ngosNList,ngosNAmount);
	text += tmp;
	m_sgosNonpair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	/*
	m_sgosPair.GetWindowTextW(text);
	tmp.Format(_T(" ( �� %d ע��Ͷע���: ��%d.00 )"),ngosPList,ngosPAmount);
	text += tmp;
	m_sgosPair.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();
	*/
	//m_static_gos.GetWindowTextW(text);
	tmp.Format(_T(" �� ��ѡ ( �� %d ע��Ͷע���: ��%d.00 )"),ngosNList,ngosTAmount);
	text += tmp;
	m_static_gos.SetWindowTextW(text);
	text.Empty();
	tmp.Empty();

	UpdateWindow();
	resSave = FALSE;
}


void CPrePrintDlg::OnBnClickedExport2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(resSave)
	{
		MessageBox(_T("��Ԥ�����ٵ���,^_^!!"));
		return;
	}
	int countnrsc = m_rscNList.GetCount();
	//int countprsc = m_rscPList.GetCount();
	int countngos = m_gosNList.GetCount();
	//int countpgos = m_gosPList.GetCount();

	if(totalCount <= 0)
	{
		MessageBox(_T("�б�3D����Ϊ��,���赼��"));
		return;
	}

	TCHAR szFilter[] = _T("Word�ļ�(*.doc)|*.doc|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	
	TCHAR *filename = NULL;
	CString cf;
	cParentWnd->m_issue.GetWindowTextW(cf);
	int issue = 888;
	if(cf.GetLength())
	{
		cf += _T("��3D��Ԥ��");
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
		MessageBox(_T("�����뵼���ļ���"),_T("����"),MB_OK);
		return;
	}
	CFile fout(fpath,CFile::modeCreate | CFile::modeReadWrite);
	fout.Write("\xff\xfe",2);

	CString str;
	//str.Format(_T("\t\t\t\t\t�� %d �� ����3D��Ԥ���ӡ����\n\t\t���� %d ��3D��.ɱ�� %d ��.���� %d �� ����Ͷע���: ��%d.00  \n\n"),issue,cParentWnd->totalCodeCount,
	//	cParentWnd->totalCodeCount-totalCount,totalCount,totalAmount);
	str.Format(_T("\t\t\t\t\t�� %d �� ����3D��Ԥ���ӡ����\n\t\t\t\t\t\t(���� %d ע3D��)\n\n\n"),issue,cParentWnd->totalCodeCount);
	fout.Write(str,sizeof(TCHAR)*str.GetLength());

	CString codeString;
	CString itemString;
	CString subitem;
	int sizetchar = sizeof(TCHAR);
	// ������ѡ����ʽ

	//m_static_rsc.GetWindowTextW(itemString);
	//m_srscNonpair.GetWindowTextW(subitem);
	//itemString += _T("\n") + subitem + _T("\n");
	itemString.Format(_T("��ѡ����ʽ�� %d ע\n"),countnrsc);
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
	/* ���ڶ��ӵ�Ԥ�����г�ʽԤ��
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

	// ������ѡ
	/*
	m_static_gos.GetWindowTextW(itemString);
	m_sgosNonpair.GetWindowTextW(subitem);
	itemString += _T("\n") + subitem + _T("\n");
	*/
	itemString.Format(_T("\n\n��ѡ: %d ע \n"),countngos);
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
	MessageBox(_T("�����ɹ�"),_T("��ʾ"));
}

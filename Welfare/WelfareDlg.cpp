
// WelfareDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Welfare.h"
#include "WelfareDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "PrePrintDlg.h"
#include <iostream>
#include <fstream>

#include "CApplication.h"
#include "CMyDocument.h"
#include "CDocuments.h"
#include "CMyFont.h"
#include "CRange.h"
#include "CSelection.h"
#include "CParagraphFormat.h"
#include "CParagraph.h"
#include "CParagraphs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAXSIZE 10


enum WdUnits
{
    wdCharacter = 1, // ��ĸ
    wdWord = 2, // ����
    wdSentence = 3, // ����
    wdParagraph = 4, // ����
    wdLine = 5, // ��
    wdStory = 6, // ��ѡ����
    wdScreen = 7, // ��ǰ��Ļ
    wdSection = 8, // ����
    wdColumn = 9, // ��
    wdRow = 10, // ��
    wdWindow = 11, // ����
    wdCell = 12, // ��Ԫ��
    wdCharacterFormatting = 13, // �����ʽ
    wdParagraphFormatting = 14, // �����ʽ
    wdTable = 15, // ���
    wdItem = 16 // ��Ŀ
};

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_ABOUT, &CAboutDlg::OnAbout)
END_MESSAGE_MAP()


// CWelfareDlg �Ի���




IMPLEMENT_DYNAMIC(CWelfareDlg, CDialogEx);

CWelfareDlg::CWelfareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelfareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CWelfareDlg::~CWelfareDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CWelfareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARR1, m_arr1);
	DDX_Control(pDX, IDC_ARR2, m_arr2);
	DDX_Control(pDX, IDC_ARR3, m_arr3);
	DDX_Control(pDX, IDC_BOLDCODE, m_boldCode);
	DDX_Control(pDX, IDC_CHECKTIP, m_checkTip);
	DDX_Control(pDX, IDC_EXPORT, m_export);
	DDX_Control(pDX, IDC_FORCAST, m_forcast);
	DDX_Control(pDX, IDC_ISSUE, m_issue);
	DDX_Control(pDX, IDC_KILLCODE, m_killCode);
	DDX_Control(pDX, IDC_LISTCODE, m_listCode);
	DDX_Control(pDX, IDC_PLUSTAIL, m_plusTail);
	DDX_Control(pDX, IDC_REINFO, m_REInfo);
	DDX_Control(pDX, IDC_RESET, m_reset);
	DDX_Control(pDX, IDC_REVOCATION, m_revocation);
	DDX_Control(pDX, IDC_TWOCODE, m_twoCode);
	DDX_Control(pDX, IDC_SIFT, m_sift);
	//DDX_Control(pDX, IDC_DIRECT, m_direct);
	//  DDX_Control(pDX, IDC_PREPRINT, m_prePrint);
	DDX_Control(pDX, IDC_ARR4, m_arr4);
	DDX_Control(pDX, IDC_KILLBIGLITTLE, m_killABL);
	DDX_Control(pDX, IDC_KILLODDEVEN, m_killAOE);
	//  DDX_Control(pDX, IDC_KILLPAIR, m_killPair);
	//  DDX_Control(pDX, IDC_GROUPC, m_groupChoose);
	DDX_Control(pDX, IDC_HUNDRED, m_hundred);
	DDX_Control(pDX, IDC_DECADE, m_decade);
	DDX_Control(pDX, IDC_UNIT, m_unit);
	DDX_Control(pDX, IDC_DShou, m_dshou);
	DDX_Control(pDX, IDC_DECheck, m_deCheck);
	DDX_Control(pDX, IDC_BIGSUM, m_bigSum);
	DDX_Control(pDX, IDC_THREE, m_three);
	//  DDX_Control(pDX, IDC_ISSUETTITLE, m_issueTitle);
	DDX_Control(pDX, IDC_LIST1, mListc);
	DDX_Control(pDX, IDC_ADDQUEUE, mAddQueue);
	DDX_Control(pDX, IDC_RADIO1, mGenType);
	DDX_Control(pDX, IDC_CLASSOUTPUT, outputCheck);
	DDX_Control(pDX, IDC_KUADU, m_kuaDu);
	DDX_Control(pDX, IDC_HundredAndUnit, m_huandrdunit);
}

BEGIN_MESSAGE_MAP(CWelfareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_SETFOCUS(IDC_ISSUE, &CWelfareDlg::OnSetfocusIssue)
	ON_EN_SETFOCUS(IDC_ARR1, &CWelfareDlg::OnSetfocusArr1)
	ON_EN_SETFOCUS(IDC_ARR2, &CWelfareDlg::OnSetfocusArr2)
//	ON_EN_CHANGE(IDC_ARR3, &CWelfareDlg::OnChangeArr3)
	ON_EN_SETFOCUS(IDC_BOLDCODE, &CWelfareDlg::OnSetfocusBoldcode)
	ON_EN_SETFOCUS(IDC_PLUSTAIL, &CWelfareDlg::OnSetfocusPlustail)
	ON_EN_SETFOCUS(IDC_TWOCODE, &CWelfareDlg::OnSetfocusTwocode)
	ON_EN_SETFOCUS(IDC_ARR3, &CWelfareDlg::OnSetfocusArr3)
	ON_BN_CLICKED(IDC_FORCAST, &CWelfareDlg::OnBnClickedForcast)
	ON_BN_CLICKED(IDC_KILLCODE, &CWelfareDlg::OnBnClickedKillcode)
	ON_BN_CLICKED(IDC_EXPORT, &CWelfareDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDC_RESET, &CWelfareDlg::OnBnClickedReset)
	ON_LBN_DBLCLK(IDC_LISTCODE, &CWelfareDlg::OnDblclkListcode)
	ON_BN_CLICKED(IDC_REVOCATION, &CWelfareDlg::OnBnClickedRevocation)
	ON_EN_CHANGE(IDC_TWOCODE, &CWelfareDlg::OnEnChangeTwocode)
	ON_BN_CLICKED(IDC_SIFT, &CWelfareDlg::OnClickedSift)
//	ON_BN_DOUBLECLICKED(IDC_SIFT, &CWelfareDlg::OnDoubleclickedSift)
//ON_LBN_SELCHANGE(IDC_LISTCODE, &CWelfareDlg::OnLbnSelchangeListcode)
ON_COMMAND(ID_SAVE, &CWelfareDlg::OnSave)
ON_COMMAND(ID_QUIT, &CWelfareDlg::OnQuit)
//ON_BN_CLICKED(IDC_PREPRINT, &CWelfareDlg::OnBnClickedPreprint)
ON_EN_SETFOCUS(IDC_ARR4, &CWelfareDlg::OnSetfocusArr4)
ON_COMMAND(ID_ABOUT, &CWelfareDlg::OnAbout)
ON_LBN_SELCHANGE(IDC_LISTCODE, &CWelfareDlg::OnSelchangeListcode)
//ON_BN_CLICKED(IDC_KILLPAIR, &CWelfareDlg::OnBnClickedKillpair)
ON_BN_CLICKED(IDC_KILLODDEVEN, &CWelfareDlg::OnBnClickedKilloddeven)
ON_BN_CLICKED(IDC_KILLBIGLITTLE, &CWelfareDlg::OnBnClickedKillbiglittle)
ON_EN_CHANGE(IDC_DShou, &CWelfareDlg::OnEnChangeDshou)
ON_EN_SETFOCUS(IDC_DShou, &CWelfareDlg::OnSetfocusDshou)
ON_BN_CLICKED(IDC_DECheck, &CWelfareDlg::OnClickedDecheck)
ON_BN_CLICKED(IDC_BIGSUM, &CWelfareDlg::OnClickedBigsum)
ON_EN_CHANGE(IDC_THREE, &CWelfareDlg::OnEnChangeEdit1)
ON_EN_SETFOCUS(IDC_THREE, &CWelfareDlg::OnSetfocusThree)
ON_BN_CLICKED(IDC_ADDQUEUE, &CWelfareDlg::OnBnClickedAddqueue)
ON_NOTIFY(NM_CLICK, IDC_FORCASTQUEUE, &CWelfareDlg::OnClickForcastqueue)
ON_NOTIFY(NM_DBLCLK, IDC_FORCASTQUEUE, &CWelfareDlg::OnDblclkForcastqueue)
ON_BN_CLICKED(IDC_CLEARALL, &CWelfareDlg::OnBnClickedClearall)
ON_BN_CLICKED(IDC_COMPOSITESELECT, &CWelfareDlg::OnBnClickedCompositeselect)
END_MESSAGE_MAP()

// CWelfareDlg ��Ϣ�������

BOOL CWelfareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_arr1.SetLimitText(10);
	m_arr2.SetLimitText(10);
	m_arr3.SetLimitText(10);
	m_arr4.SetLimitText(10);
	m_checkTip.SetCheck(1);
	outputCheck.SetCheck(1);
	m_deCheck.EnableWindow(false);
	// test
	//m_listCode.AddString(_T("234-9"),RGB(154,50,205));
	//m_sift.SetCheck(TRUE);
	//m_direct.SetCheck(TRUE);

	CreateThreadEvent = CreateEvent(NULL,TRUE,TRUE,NULL);
	
	ec = new Encode();
	
	forcastFlag = FALSE;
	
	// ��ʼ��Ԥ�����
	//mListc.SetExtendedStyle(LVS_EX_CHECKBOXES);
	mListc.InsertColumn(0,_T("Ԥ�����"));
	mListc.SetColumnWidth(0,85);

	// ��ʼ��ͳ�Ʊ���
	totalCodeCount = 0;
	killCodeCount = 0;
	oddCodeCount = 0;

	queueNum = 0;

	// ��ʼ��״̬��
	static UINT indicators[2] = 
	 { 
	  ID_SEPARATOR,
	  ID_SEPARATOR,
	 }; 
	  if (!m_StatusBar.Create(this) || !m_StatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	 { 
	  TRACE0( "Failed   to   create   status   bar/n "); 
	  return FALSE;             //   fail   to   create 
	 } 

	 m_StatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,240); 
	 m_StatusBar.ShowWindow(SW_SHOW); 
	 CRect   rect; 
	 GetClientRect(&rect); 
	 int StatusBarH = 20;
	 m_StatusBar.MoveWindow(0,rect.bottom- StatusBarH,rect.right,StatusBarH,TRUE);
	 m_StatusBar.SetPaneText(0,_T("��ӭʹ��!"));
	 m_StatusBar.SetPaneText(1,_T("��Ҫ����518 (2017.05.08)"));
	 
	 mGenType.SetCheck(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWelfareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWelfareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWelfareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CWelfareDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CWelfareDlg::OnOK()
{
	NextDlgCtrl();
}

void CWelfareDlg::OnCancel()
{
	//if (CanExit())
	//	CDialogEx::OnCancel();
	int key = MessageBox(_T("�����Ҫ�˳�?"),_T("�˳���"),MB_OKCANCEL);
	if(key == IDOK)
		CDialog::OnCancel();
}

BOOL CWelfareDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CWelfareDlg::OnSetfocusIssue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("������Ԥ���ں�"));
}


void CWelfareDlg::OnSetfocusArr1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("����������һ"));
}


void CWelfareDlg::OnSetfocusArr2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("���������ж�"));
}


void CWelfareDlg::OnSetfocusArr3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("������������"));
}

void CWelfareDlg::OnSetfocusArr4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("������������"));
}

void CWelfareDlg::OnSetfocusBoldcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("�����뵨��"));
}


void CWelfareDlg::OnSetfocusPlustail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("�������ֵβ"));
}


void CWelfareDlg::OnSetfocusTwocode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("��������Զ��룬�ԡ�#������/������,�������ⵥ�ַ�������Ÿ���,\n�磬09#34#45,68/23/90/69"));
}


void CWelfareDlg::OnBnClickedForcast()
{
	if(ec == NULL || ec->getIsInQueue()){  // ��Ԥ��,�����¶���
		ec = new Encode();
		//forcastFlag = false;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(forcastFlag)
	{
		ec->eraseCode();
		m_listCode.ResetContent();
		forcastFlag = FALSE;
	}

	CString csarr[4];
	int arrCount = 0;
	int nullArrIndex = -1;
	m_arr1.GetWindowTextW(csarr[0]);
	m_arr2.GetWindowTextW(csarr[1]);
	m_arr3.GetWindowTextW(csarr[2]);
	m_arr4.GetWindowTextW(csarr[3]);

	//MessageBoxW(csarr[0] + "-" + csarr[1] + "-" + csarr[2] + "-" + csarr[3]);
	
	for(int i=0; i<4; i++)
	{
		if(csarr[i].GetLength()>=1)
			arrCount++;
		else
			nullArrIndex = i;
	}

	if(arrCount >= 3 && arrCount <= 4)
	{
		vector<int> arr[4];
		
		for(int i=0; i<4; i++)
		{
			int length = csarr[i].GetLength();
			char *p = (LPSTR)(LPCTSTR)csarr[i];
			for(int j=0; j<2*length; j=j+2)
			{
				int tmp = *(p+j) - 48;
				arr[i].push_back(tmp);
			}
		}
		
		// �жϸ��������Ƿ��������ظ�
		for(int i=0; i<4; i++)
		{
			int flag[MAXSIZE] = {0};// = new int(MAXSIZE);
			//memset(flag,0,MAXSIZE);
			for(vector<int>::iterator it = arr[i].begin(); it != arr[i].end(); it++)
			{
				if( flag[*it] == 1)
				{
					CString tmp;
					tmp.Format(_T("���� %d �������ظ�,����������"),i+1);
					m_REInfo.SetWindowTextW(tmp);
					return;
				}else{
					flag[*it] = 1;
				}
			}
		}
		if(arrCount ==3)
		{
			int indexFlag[3];
			int j=0;
			for(int i=0; i<4; i++)
			{
				if(i==nullArrIndex)
					continue;
				indexFlag[j++] = i;
			}
			if(ec->encoding(arr[indexFlag[0]],arr[indexFlag[1]],arr[indexFlag[2]],mGenType.GetCheck()))
			{
				forcastFlag = TRUE;
				arr[0].clear();
				arr[1].clear();
				arr[2].clear();
			}else
				return;
		}else if (arrCount == 4 && ec->encoding(arr[0],arr[1],arr[2],arr[3],mGenType.GetCheck())){

			forcastFlag = TRUE;
			arr[0].clear();
			arr[1].clear();
			arr[2].clear();
			arr[3].clear();
		}

		ec->groupChoose();

		// ��ֵβ����
		ec->ordering();

		// ������ұ��б���
		for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);	
		}
		totalCodeCount = ec->dvCode.size();
		CString stat;
		stat.Format(_T("��ѡ������Ԥ��3D����: %dע��"),ec->dvCode.size());
		m_StatusBar.SetPaneText(0,_T("�������: ��ѡ"));		
		m_REInfo.SetWindowTextW(stat);
		m_deCheck.EnableWindow(true);
	}else{
		m_REInfo.SetWindowTextW(_T("�������ݲ�����,����ϸ���!"));
	}
}


void CWelfareDlg::OnBnClickedKillcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!forcastFlag)
	{
		MessageBox(_T("Ԥ�����ɱ��"),_T("��ʾ"),MB_OK);
		return;
	}
	vector<Gossip> gossip;
	vector<int> arrkc[5];
	CString csstr[5];
	CString sgossip;
	CString mKuadu;
	CString hundredAndUnit;

	m_plusTail.GetWindowTextW(csstr[0]);
	m_boldCode.GetWindowTextW(csstr[1]);
	m_hundred.GetWindowTextW(csstr[2]);
	m_decade.GetWindowTextW(csstr[3]);
	m_unit.GetWindowTextW(csstr[4]);
	m_twoCode.GetWindowTextW(sgossip);
	m_kuaDu.GetWindowTextW(mKuadu);
	m_huandrdunit.GetWindowTextW(hundredAndUnit);

	int count = 0;
	if(csstr[0].GetLength()||csstr[1].GetLength()
		|| sgossip.GetLength()||csstr[2].GetLength()||csstr[3].GetLength()
		||csstr[4].GetLength())
	{
		for(int i=0; i<5; i++)
		{
			int length = csstr[i].GetLength();
			char *p = (LPSTR)(LPCTSTR)csstr[i];
			for(int j=0; j<2*length; j=j+2)
			{
				int tmp = *(p+j) - 48;
				arrkc[i].push_back(tmp);
			}
		}

		int length = sgossip.GetLength();
		if(length>2)
		{
			char *p = (LPSTR)(LPCTSTR)sgossip;
			int k=1;
			for(int j=0; j<2*length; j=j+2)
			{
				if(!(k%3))
				{
					k += 1;
					continue;
				}
				Gossip tmp;
				tmp.x=  *(p+j)-48;
				j = j+2;
				tmp.y =  *(p+j)-48;
				gossip.push_back(tmp);

				k += 2;
			}
		}
		count = ec->killCode(arrkc[0],arrkc[1],arrkc[2],arrkc[3],arrkc[4],gossip);
	}else{
		m_REInfo.SetWindowTextW(_T("����������һ�������ɱ�롣"));
	}

	// ���ѡ��
	if(mKuadu.GetLength()>0){
		int kLength = mKuadu.GetLength();
		if(kLength>0){
			vector<int> kd;
			char *p = (LPSTR)(LPCTSTR)mKuadu;
			for(int j=0; j<2*kLength; j=j+2)
			{
				int tmp = *(p+j) - 48;
				kd.push_back(tmp);
			}
			// ���ѡ��
			count += ec->selectBasedSpan(kd);
		}
	}
	// ����������
	CString threeStr;
	m_three.GetWindowTextW(threeStr);
	// ��ת��CString����
	wchar_t *ptrz;             
	char buft[256];        // Ŀ��洢�ռ�
	memset(buft,'\0',256);
	int tclength = threeStr.GetLength()>255?255:threeStr.GetLength();
	ptrz=threeStr.GetBuffer(tclength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrz, -1, buft, sizeof(buft), NULL, NULL);
	int  tcSelCount=0;
	int tclen = strlen(buft);
	// ����ѡ��
	if(tclen > 0){
		tcSelCount = ec->tcSelect(buft);
	}

	// ����������
	CString dshouStr;
	m_dshou.GetWindowTextW(dshouStr);
	// ��ת��CString����
	wchar_t *ptrx;             
	char bufx[256];        // Ŀ��洢�ռ�
	memset(bufx,'\0',256);
	int dslength = dshouStr.GetLength()>255?255:dshouStr.GetLength();
	ptrx=dshouStr.GetBuffer(dslength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrx, -1, bufx, sizeof(bufx), NULL, NULL);
	int  dsSelCount=0;
	int selStrlen = strlen(bufx);
	// ����ѡ��
	if(selStrlen > 0){
		
		dsSelCount = ec->dsSelect(bufx);
	}

	// ɱ���
	int bigCount = 0;
	if(m_bigSum.GetCheck()){
		bigCount = ec->killBig();
	}

	// �ٸ�λɱ��
	if (hundredAndUnit.GetLength()>0) {
		int huLength = hundredAndUnit.GetLength();
		if (huLength>0) {
			set<int> hu;
			char *p = (LPSTR)(LPCTSTR)hundredAndUnit;
			for (int j = 0; j<2 * huLength; j = j + 2)
			{
				int tmp = *(p + j) - 48;
				hu.insert(tmp);
			}
			// �ٸ�λɱ��
			count += ec->killCodeOnHundredAndUnit(hu);
		}
	}


	m_listCode.ResetContent();
	int siftCount = 0;
	int oeCount = 0;
	int blCount = 0;
	int flag = m_sift.GetCheck();
	int pairCount = 0;
	// 
	for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); )
	{
		// ɱ��ͷ
		if(m_sift.GetCheck())
		{
			int codeSum = it->codeSeq[0]+it->codeSeq[1]+it->codeSeq[2];
			if(codeSum>20 || codeSum < 10)
			{
				//if(ec->getIsMerge())
				//	ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				siftCount++;
				continue;
			}
		}
		// ɱȫ��ȫż
		if(m_killAOE.GetCheck())
		{
			if((it->codeSeq[0]%2!=0 && it->codeSeq[1]%2!=0 && it->codeSeq[2] % 2 !=0) || 
				(it->codeSeq[0]%2==0 && it->codeSeq[1]%2==0 && it->codeSeq[2]%2==0))
			{
				oeCount++;
				//if(ec->getIsMerge())
				//	ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				continue;
			}
		}
		// ɱȫ��ȫС
		if(m_killABL.GetCheck())
		{
			if(isExtreme(it))
			{
				blCount++;
				//if(ec->getIsMerge())
				//	ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				continue;
			}
		}

		if(it->codeSeq[0] == it->codeSeq[1] || it->codeSeq[1] == it->codeSeq[2]
		|| it->codeSeq[0] == it->codeSeq[2])
		{
			pairCount ++;
		}
		CString tmp;
		tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		m_listCode.AddString(tmp);
		it++;
	}



	CString ts;
	if((siftCount|oeCount|blCount|dsSelCount|bigCount|tcSelCount) != 0)
	{
		int delTotal = count+siftCount+oeCount+blCount+dsSelCount+bigCount+tcSelCount;
		ts.Format(_T("ɱ�� %d ע(ɱ��ͷ: %d ע, ȫ��ȫС�� %d��ȫ��ȫż: %dע,���: %dע,\n���ţ�%dע������: %d ע,����:%d ע)��ѡ�� %d ע."),delTotal,siftCount,blCount,oeCount,bigCount,dsSelCount,tcSelCount,count, ec->dvCode.size());
	}else
		ts.Format(_T("ɱ�� %d ע���� %d ע(���ж��� %d ע,�Ƕ��� %d ע)."),count,ec->dvCode.size(),pairCount,ec->dvCode.size()-pairCount);
	m_REInfo.SetWindowTextW(ts);
}

BOOL IsPair(CString code)
{
	int length = code.GetLength();
	if(length <= 0)
		return false;
	char *p = (LPSTR)(LPCTSTR)code;
	if( *p == *(p+2) || *p == *(p+4) || *(p+2) == *(p+4))
	{
		return true;
	}
	return false;
}

BOOL IsPair(vector<CodeType>::iterator it){
	if(it->codeSeq[0] == it->codeSeq[1] || it->codeSeq[1]==it->codeSeq[2]
	||it->codeSeq[0] == it->codeSeq[2]){
		return true;
	}
	return false;
}

// ȫ��ȫС
bool isABM(const vector<CodeType>::iterator it){
	if(isExtreme(it)){
		return true;
	}	
	return false;
}
// ȫ��ȫż
bool isAOE(const vector<CodeType>::iterator it){
	if((it->codeSeq[0]%2!=0 && it->codeSeq[1]%2!=0 && it->codeSeq[2] % 2 !=0) || 
		(it->codeSeq[0]%2==0 && it->codeSeq[1]%2==0 && it->codeSeq[2]%2==0))
	{
		return true;
	}
	return false;
}
// ��ͷ
bool isTD(const vector<CodeType>::iterator it){
	int codeSum = it->codeSeq[0]+it->codeSeq[1]+it->codeSeq[2];
	if(codeSum>20 || codeSum < 10){
		return true;
	}
	return false;
}

// ���
bool isBS(const vector<CodeType>::iterator it){
	if((it->codeSeq[0] + it->codeSeq[1] + it->codeSeq[2])>20){
		return true;
	}
	return false;
}


// �ӻ���վ�ҳ��ض����͵�3D�룬�����ֶ��ӷǶ���
void selectCode(vector<CodeType> &vp,vector<CodeType> &vn, vector<CodeType> vec,bool (*func)(const vector<CodeType>::iterator)){
	for(vector<CodeType>::iterator it = vec.begin(); it!=vec.end(); it++){
		if(func(it)){
			if(IsPair(it)){
				vp.push_back(*it);
			}else{
				vn.push_back(*it);
			}
		}
	}
}

// �ӻ���վ�ҳ��ض����͵�3D�룬�����ֶ��ӷǶ���
void selectCode(vector<CodeType> &vp,vector<CodeType> &vn, vector<CodeType> vec,
				bool (*func)(const vector<CodeType>::iterator),bool (*func2)(const vector<CodeType>::iterator)){
	for(vector<CodeType>::iterator it = vec.begin(); it!=vec.end(); it++){
		if(func(it) || func2(it)){
			if(IsPair(it)){
				vp.push_back(*it);
			}else{
				vn.push_back(*it);
			}
		}
	}
}

// ��ӡ����
void printVector(CSelection oSel,vector<CodeType> vec, CString mTitle){
	CString spacestr = _T("      ");
	CString separator = _T("\n-------------------------------");
	CMyFont font = oSel.get_Font();
	font.put_Size( 12 );
	CString str;
	str.Format(_T(" \n\n�� "));
	oSel.TypeText(str + mTitle);
	oSel.TypeText(separator);
	font.put_Size( 14 );
	oSel.TypeParagraph();
	for(vector<CodeType>::iterator it =vec.begin(); it!=vec.end(); it++){
			CString tmp ;
			tmp.Format(_T("[%d]%d%d%d-%d"),it->frequency,it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			oSel.TypeText(tmp);
			oSel.MoveLeft(COleVariant((short)2),COleVariant((short)1),COleVariant((short)1));
			font.put_Size( 10 );
			oSel.MoveRight(COleVariant((short)2),COleVariant((short)1),COleVariant((short)0));
			font.put_Size( 14 );
			oSel.TypeText(spacestr);
	}
}

/**
*	����������������ѡ
*
*/
void CWelfareDlg::OnBnClickedExport()
{
	int count = m_listCode.GetCount();

	oddCodeCount = count;
	killCodeCount = totalCodeCount - oddCodeCount ;
	if(!forcastFlag ||(count <= 0 && ec->dvCode.size() <= 0))
	{
		m_REInfo.SetWindowTextW(_T("δԤ����б����Ϊ��"));
		return;
	}

	m_REInfo.SetWindowTextW(_T("Ԥ�ⱨ������������,���Ժ�..."));

	CString cf;
	m_issue.GetWindowTextW(cf);
	int issue = 888;
	if(cf.GetLength())
	{
		issue = _ttoi(cf);
		//cf += _T("��3D��Ԥ��");
		//filename = cf.GetBuffer(cf.GetLength());
	}

	vector<CString> pairCode;
	vector<CString> nonpairCode;

	CString spacestr = _T("      ");
	CString separator = _T("\n-------------------------------");

	// ���� ec->dvCode ����
	for(vector<CodeType>::iterator it = ec->dvCode.begin(); it!=ec->dvCode.end(); it++){
		CString tmp;
		if(ec->getIsMerge())
			tmp.Format(_T("[%d]%d%d%d-%d"),it->frequency,it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		else
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		if(IsPair(it)){
			pairCode.push_back(tmp);
		}else{
			nonpairCode.push_back(tmp);
		}
	}

	// ����word��������
	COleVariant  vTrue((short)TRUE),  
                  vFalse((short)FALSE),  
                  vopt((long)DISP_E_PARAMNOTFOUND,  VT_ERROR); 	
	CApplication oWordApp ; 
	CSelection oSel ;  
	CDocuments oDocs ; 
	CMyDocument oDoc ; 
	CParagraphs paragraphs;

	//WdUnits fv;

	if (!oWordApp.CreateDispatch(_T("Word.Application")) ){ 
		AfxMessageBox( _T( "word��ʼ��ʧ�ܣ�" ) , MB_OK & MB_SETFOREGROUND);  
		return;  // ���أ����������� 
	}
	// �Ȳ���ʾ
	oWordApp.put_Visible(false);

	oDocs = oWordApp.get_Documents(); 
	oDoc = oDocs.Add(vopt,vopt,vopt,vopt);
	oSel = oWordApp.get_Selection();
	oSel.WholeStory();
	
	CParagraphFormat cformat = oSel.get_ParagraphFormat();
	cformat.put_Alignment(0);

	CString codetype;
	if(ec->getCodeType() == DIRECT){
		codetype.Format(_T("ֱѡ"));
	}else{
		codetype.Format(_T("��ѡ"));
	}

	CMyFont font = oSel.get_Font();
	CString str;
	str.Format(_T("\t\t�� %d �� ����3D��Ԥ�⣨%s����ӡ����\n"),issue,codetype);	
	font.put_Name(_T("����"));
	font.put_Size(18);
	oSel.TypeText(str);
	str.Format(_T("\t\t\t\t���� %d ע3D��,�������� ��Ҫ����518 ��������\n"),count);
	font.put_Name(_T("����"));
	font.put_Size(12);
	oSel.TypeText(str);
	oSel.TypeParagraph();
	font.put_Size(14);

	font.put_Size( 12 );
	str.Format(_T("�� ����: %d ע "),pairCode.size());
	oSel.TypeText(str);
	oSel.TypeText(separator);
	font.put_Size( 14 );
	oSel.TypeParagraph();
	
	bool flagExport = false;
	vector<CodeType> vp;
	vector<CodeType> vn;

	if(ec->getIsMerge() && outputCheck.GetCheck() && ec->recycleBin.size()>0){
		ec->orderForRecycleBin();
		selectCode(vp,vn,ec->recycleBin,isTD,isAOE);
		flagExport = true;
	}

	// ��������
	for(vector<CString>::iterator it = pairCode.begin(); it != pairCode.end(); it++)
	{
		CString tmp = *it;
		oSel.TypeText(tmp);
		oSel.MoveLeft(COleVariant((short)2),COleVariant((short)1),COleVariant((short)1));
		font.put_Size( 10 );
		oSel.MoveRight(COleVariant((short)2),COleVariant((short)1),COleVariant((short)0));
		font.put_Size( 14 );
		oSel.TypeText(spacestr);
	}
	// ���������ɶ���
	if(flagExport){
		CString mTitle;
		mTitle.Format(_T("�����ɡ�����[ %d ]ע"),vp.size());
		printVector(oSel,vp,mTitle);
	}
	font.put_Size( 12 );
	str.Format(_T(" \n\n�� �Ƕ���: %d ע "),nonpairCode.size());
	oSel.TypeText(str);
	oSel.TypeText(separator);
	font.put_Size( 14 );
	oSel.TypeParagraph();

	// ��������
	for(vector<CString>::iterator it = nonpairCode.begin(); it != nonpairCode.end(); it++)
	{
		CString tmp = *it;
		oSel.TypeText(tmp);
		oSel.MoveLeft(COleVariant((short)2),COleVariant((short)1),COleVariant((short)1));
		font.put_Size( 10 );
		oSel.MoveRight(COleVariant((short)2),COleVariant((short)1),COleVariant((short)0));
		font.put_Size( 14 );
		oSel.TypeText(spacestr);
	}
	pairCode.clear();
	nonpairCode.clear();

	// ���������ɷǶ���
	if(flagExport){
		CString mTitle;
		mTitle.Format(_T("�����ɡ��Ƕ���[ %d ]ע"),vn.size());
		printVector(oSel,vn,mTitle);
		vp.clear();
		vn.clear();
	}
	CString stat;
	stat.Format(_T("Ԥ���Ѿ�����,3D��:%d ע"),count);
	m_REInfo.SetWindowTextW(stat);

	// ��ʾ����
	oWordApp.put_Visible(true);
	
}

void CWelfareDlg::OnBnClickedReset()
{
	if(!ec->getIsInQueue())
		ec->eraseCode();
	m_listCode.ResetContent();

	while(!recoverCodeStack.empty())
	{
		recoverCodeStack.pop();
	}
	totalCodeCount = 0;
	killCodeCount = 0;
	oddCodeCount = 0;
	queueNum = 0;
	m_issue.SetWindowTextW(_T(""));
	m_arr1.SetWindowTextW(_T(""));
	m_arr2.SetWindowTextW(_T(""));
	m_arr3.SetWindowTextW(_T(""));
	m_arr4.SetWindowTextW(_T(""));
	m_plusTail.SetWindowTextW(_T(""));
	m_boldCode.SetWindowTextW(_T(""));
	m_twoCode.SetWindowTextW(_T(""));
	m_REInfo.SetWindowTextW(_T(""));
	m_hundred.SetWindowTextW(_T(""));
	m_decade.SetWindowTextW(_T(""));
	m_unit.SetWindowTextW(_T(""));
	m_dshou.SetWindowTextW(_T(""));
	m_deCheck.EnableWindow(false);
	m_deCheck.SetCheck(false);
	m_bigSum.SetCheck(false);
	m_killABL.SetCheck(false);
	m_killAOE.SetCheck(false);
	m_sift.SetCheck(false);
	m_StatusBar.SetPaneText(0,_T("��ӭʹ�ã�"));
	forcastFlag = FALSE;
}


void CWelfareDlg::OnDblclkListcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_checkTip.GetCheck())
	{
		if(IDOK!=MessageBox(_T("ȷ��������ɾ����ѡԤ���룬����ȡ��"),_T("��ʾ"),MB_OKCANCEL))
		{
			return;
		}
	}
	RECOVER tmp;
	tmp.index = m_listCode.GetCurSel();
	m_listCode.GetText(tmp.index,tmp.code);

	//memcpy(&tmp.ctCode,&(ec->dvCode.begin()+tmp.index),sizeof(CodeType));
	vector<CodeType>::iterator it = ec->dvCode.begin()+tmp.index;
	tmp.ctCode.mantissa = it->mantissa;
	tmp.ctCode.codeSeq[0] = it->codeSeq[0];
	tmp.ctCode.codeSeq[1] = it->codeSeq[1];
	tmp.ctCode.codeSeq[2] = it->codeSeq[2];
	recoverCodeStack.push(tmp);
	m_listCode.DeleteString(tmp.index);
	ec->dvCode.erase(ec->dvCode.begin()+tmp.index);
	m_listCode.SetCurSel(tmp.index-1);
	CString delString(tmp.code);
	delString += _T(" ��ɾ����");
	m_REInfo.SetWindowTextW(delString);
}


void CWelfareDlg::OnBnClickedRevocation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(recoverCodeStack.empty())
	{
		return;
	}
	RECOVER tmp;
	tmp = recoverCodeStack.top();
	recoverCodeStack.pop();
	//int flag = isInSift(tmp.code);
	//if(m_sift.GetCheck() && flag)
	//{
	//	if(flag == 1)
	//	{
	//		m_listCode.InsertString(tmp.index,tmp.code,RGB(154,50,205));
	//	}else{
	//		m_listCode.InsertString(tmp.index,tmp.code,RGB(255,0,0));
	//	}
	//}else
	//	m_listCode.InsertString(tmp.index,tmp.code);

	m_listCode.InsertString(tmp.index,tmp.code);
	ec->dvCode.insert(ec->dvCode.begin()+tmp.index,tmp.ctCode);
	CString revocationString(tmp.code);
	revocationString += _T(" �ѳ���ɾ����");
	m_REInfo.SetWindowTextW(revocationString);
}


void CWelfareDlg::OnEnChangeTwocode()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

/*
 return -1,0,1
*/
int isInSift(CString code)
{
	int length = code.GetLength()-2;
	char *p = (LPSTR)(LPCTSTR)code;
	int arr[3];
	for(int j=0; j<2*length; j=j+2)
	{
		int tmp = *(p+j) - 48;
		arr[j/2] = tmp;
	}
	int codesum = arr[0] + arr[1] + arr[2];
	if (codesum <10)
		return -1;
	else if(codesum > 20)
		return 1;
	return 0;
}

void CWelfareDlg::OnClickedSift()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(forcastFlag && m_sift.GetCheck())
	{
		if(IDOK != MessageBox(_T("ѡ��ȷ������ɾ����ֵ����10~20��3D�룬����ɾ��"),_T("��ʾ"),MB_OKCANCEL))
		{
			m_sift.SetCheck(FALSE);
			return;
		}
		// ֱ��ɾ��ec�����е����ݣ������´�ӡ
		int delCount = 0;
		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			int codeSum = it->codeSeq[0]+it->codeSeq[1]+it->codeSeq[2];
			if(codeSum>20 || codeSum < 10)
			{
				if(ec->getIsMerge())
					ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				delCount++;
				continue;
			}
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}
		CString info;
		info.Format(_T("ɸѡɾ�� %d ע3D�룬��%d ע3D�룬�� %d ע3D��!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}
}

//void CWelfareDlg::OnLbnSelchangeListcode()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CWelfareDlg::OnSave()
{
	// TODO: �ڴ���������������
	m_export.SendMessage(BN_CLICKED);
	OnBnClickedExport();
}


void CWelfareDlg::OnQuit()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CLOSE);
}


//void CWelfareDlg::OnBnClickedPreprint()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	if(!forcastFlag)
//	{
//		MessageBox(_T("��Ԥ����ٲ���"),_T("��ʾ"),MB_OK);
//		return;
//	}
//	CPrePrintDlg cpp;
//	cpp.cParentWnd = this;
//	cpp.DoModal();
//}




//void CAboutDlg::OnAbout()
//{
//	// TODO: �ڴ���������������
//	CAboutDlg about;
//	about.DoModal();
//}


void CWelfareDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg about;
	about.DoModal();
}


void CWelfareDlg::OnSelchangeListcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void CWelfareDlg::OnBnClickedKilloddeven()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(forcastFlag && m_killAOE.GetCheck())
	{
		if(IDOK != MessageBox(_T("ѡ��ȷ������ɾ����λȫ���ȫż��3D�룬����ɾ��"),_T("��ʾ"),MB_OKCANCEL))
		{
			m_killAOE.SetCheck(FALSE);
			return;
		}
		// ֱ��ɾ��ec�����е����ݣ������´�ӡ
		int delCount = 0;
		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			if((it->codeSeq[0]%2!=0 && it->codeSeq[1]%2!=0 && it->codeSeq[2] % 2 !=0) || 
				(it->codeSeq[0]%2==0 && it->codeSeq[1]%2==0 && it->codeSeq[2]%2==0))
			{
				delCount++;
				if(ec->getIsMerge())
					ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				continue;
			}
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}
		CString info;
		info.Format(_T("ɸѡɾ�� %d ע3D�룬��%d ע3D�룬�� %d ע3D��!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}

}
// �ж�ȫ��ȫС
BOOL isExtreme(const vector<CodeType>::iterator it){
	int high = 0;
	int low = 0;
	for(int i=0; i<3; i++){
		if(it->codeSeq[i] == 0 || it->codeSeq[i]>5){
			high++;
		}else{
			low++;
		}
	}
	if(high == 3 || low == 3){
		return true;
	}else{
		return false;
	}
}

void CWelfareDlg::OnBnClickedKillbiglittle()
{
	if(forcastFlag && m_killABL.GetCheck())
	{
		if(IDOK != MessageBox(_T("ѡ��ȷ������ɾ����λȫ���ȫС��3D�룬����ɾ��"),_T("��ʾ"),MB_OKCANCEL))
		{
			m_killABL.SetCheck(FALSE);
			return;
		}
		// ֱ��ɾ��ec�����е����ݣ������´�ӡ
		int delCount = 0;
		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			//if((it->codeSeq[0]>5 && it->codeSeq[1]>5 && it->codeSeq[2]>5) || 
			//	(it->codeSeq[0]<5 && it->codeSeq[1]<5 && it->codeSeq[2]<5))
			if(isExtreme(it))
			{
				delCount++;
				if(ec->getIsMerge())
					ec->recycleBin.push_back(*it);
				it = ec->dvCode.erase(it);
				continue;
			}
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}
		CString info;
		info.Format(_T("ɸѡɾ�� %d ע3D�룬��%d ע3D�룬�� %d ע3D��!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}
}

CString CWelfareDlgGetFileVer()
{ /*
 TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion("hello");

 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //���Ȼ�ð汾��Ϣ��Դ�ĳ���
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //���汾��Ϣ��Դ���뻺����
 if(InfoSize==0) return _T("None VerSion Supprot");
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //��������ļ�ʹ�õĴ���ҳ���ļ��汾
 unsigned int  cbTranslate = 0;
 struct LANGANDCODEPAGE {
  WORD wLanguage;
  WORD wCodePage;
 } *lpTranslate;
 VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
 // Read the file description for each language and code page.
 for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
 {
  TCHAR  SubBlock[200];
  wsprintf( SubBlock,
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);
  void *lpBuffer=NULL;
  unsigned int dwBytes=0;
  VerQueryValue(InfoBuf,
   SubBlock,
   &lpBuffer,
   &dwBytes);
  CString strTemp=(char *)lpBuffer;
  strVersion+=strTemp;
  
 }
 */
 return _T("");
}

void CWelfareDlg::OnEnChangeDshou()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CWelfareDlg::OnSetfocusDshou()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_REInfo.SetWindowTextW(_T("����������������룬�м���#��/��*���ַ����������磺\n\t168#2518#56789\n\t123456 32457 45678"));
}

// ת��Ϊֱѡ
void CWelfareDlg::OnClickedDecheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(forcastFlag && m_deCheck.GetCheck()){
		ec->grouptodirect();

		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}

		CString info;
		info.Format(_T("��ת��Ϊֱѡ���� %d ע3D��!!"),ec->dvCode.size());
		m_StatusBar.SetPaneText(0,_T("�������: ֱѡ"));
		m_REInfo.SetWindowTextW(info);
	}
}

// ɱ���
void CWelfareDlg::OnClickedBigsum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(forcastFlag && m_bigSum.GetCheck()){

		if(IDOK != MessageBox(_T("ѡ���ǣ���ɱ����βֵ����20��3D�룿"),_T("ɱ�����ʾ"),MB_OKCANCEL))
		{
			m_bigSum.SetCheck(FALSE);
			return;
		}

		int count = 0;
		count = ec->killBig(20);

		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}

		CString info;
		info.Format(_T("���ɱ�� %d ע���� %d ע3D��!!"),count,ec->dvCode.size());
		m_REInfo.SetWindowTextW(info);
	}
}


void CWelfareDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CWelfareDlg::OnSetfocusThree()
{
	m_REInfo.SetWindowTextW(_T("�����������鶨���룬�м���#��/��*���ַ����������磺\n\t168#2518#56789\n\t123456 32457 45678"));
}


void CWelfareDlg::OnBnClickedAddqueue()
{
	// ����ǰԤ����뵽Ԥ�����
	if(ec->getIsInQueue())
		return;
	ecVector.push_back(ec);
	ec->setInQueue(true);
	queueNum ++;
	CString listItemStr;
	listItemStr.Format(_T("�� %d ��"),queueNum);
	mListc.InsertItem(mListc.GetItemCount(),listItemStr);
}


void CWelfareDlg::OnClickForcastqueue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// ����ecֵ,�ⲻ�Ǳ����
	 NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	 if(pNMListView->iItem != -1){
		ec = ecVector[pNMListView->iItem];
		// ������ұ��б���
		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
		}
		// ��ʾ��Ϣ
		CString info;
		info.Format(_T(" ��Ԥ��,�� %d ע3D��."),m_listCode.GetCount());
		m_REInfo.SetWindowTextW(mListc.GetItemText(pNMListView->iItem,0) + info);
	 }
	*pResult = 0;
}

// ** ˫��ʱ��ʾ�û��Ƿ�ɾ������Ԥ����
void CWelfareDlg::OnDblclkForcastqueue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1){
		if(IDOK == MessageBox(_T("�Ƿ�ɾ������Ԥ���룿"),_T("��ʾ"),MB_OKCANCEL))
		{
			mListc.DeleteItem(mListc.GetNextItem(-1,LVNI_SELECTED));
			return;
		}
		
	}
	*pResult = 0;
}


void CWelfareDlg::OnBnClickedClearall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedReset();
	ecVector.clear();
	//if(ecVector.empty()){
	//	MessageBoxW(_T("Ԥ������Ѿ����"));
	//}
	// ���Ԥ�����
	mListc.DeleteAllItems();
}


void CWelfareDlg::OnBnClickedCompositeselect()
{
	if(mListc.GetItemCount() == 0)
	{
		 MessageBox(_T("��������Ԥ�����"),_T("��ʾ"),MB_OKCANCEL);
		 return;
	}
	CString mergeTitle(_T("��"));
	// ����Ƶ��
	ec = new Encode();
	for (int i=0; i<mListc.GetItemCount(); i++){
		//if(mListc.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED || mListc.GetCheck(i)){
			if(((i+1)>ecVector.size()) || ecVector[i]->getIsMerge() ||!ecVector[i]->getIsInQueue())
				continue;
			int flag = ec->merge(ecVector[i]);
			if(flag == -1){
				MessageBoxW(_T("��������(��ѡ/ֱѡ)��һ��,������ѡ��"));
				break;
			}else{
				mergeTitle += _T("-") + mListc.GetItemText(i,0);
			}
		//}
	}

	// �Զ���ӵ�Ԥ�����
	ecVector.push_back(ec);
	ec->setInQueue(true);
	mListc.InsertItem(mListc.GetItemCount(),mergeTitle);
	

	// ��ӡ���ұ�
	m_listCode.ResetContent();
	for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
	{
		CString tmp;
		tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		m_listCode.AddString(tmp);
	}

	// ��ʾ��Ϣ
	CString infoM;
	infoM.Format(_T("�鲢��ɣ��� %d ע3D��.����鿴Ƶ�ȣ��뵼���ļ���"),ec->dvCode.size());
	m_REInfo.SetWindowTextW(infoM);
}

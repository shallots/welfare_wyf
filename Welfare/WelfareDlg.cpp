
// WelfareDlg.cpp : 实现文件
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
    wdCharacter = 1, // 字母
    wdWord = 2, // 单词
    wdSentence = 3, // 句子
    wdParagraph = 4, // 段落
    wdLine = 5, // 行
    wdStory = 6, // 所选区域
    wdScreen = 7, // 当前屏幕
    wdSection = 8, // 部分
    wdColumn = 9, // 列
    wdRow = 10, // 行
    wdWindow = 11, // 窗口
    wdCell = 12, // 单元格
    wdCharacterFormatting = 13, // 字体格式
    wdParagraphFormatting = 14, // 段落格式
    wdTable = 15, // 表格
    wdItem = 16 // 项目
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CWelfareDlg 对话框




IMPLEMENT_DYNAMIC(CWelfareDlg, CDialogEx);

CWelfareDlg::CWelfareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelfareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CWelfareDlg::~CWelfareDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
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

// CWelfareDlg 消息处理程序

BOOL CWelfareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	
	// 初始化预测次数
	//mListc.SetExtendedStyle(LVS_EX_CHECKBOXES);
	mListc.InsertColumn(0,_T("预测队列"));
	mListc.SetColumnWidth(0,85);

	// 初始化统计变量
	totalCodeCount = 0;
	killCodeCount = 0;
	oddCodeCount = 0;

	queueNum = 0;

	// 初始化状态栏
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
	 m_StatusBar.SetPaneText(0,_T("欢迎使用!"));
	 m_StatusBar.SetPaneText(1,_T("我要发·518 (2016.03.13)"));
	 
	 mGenType.SetCheck(true);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWelfareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWelfareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

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
	int key = MessageBox(_T("你真的要退出?"),_T("退出？"),MB_OKCANCEL);
	if(key == IDOK)
		CDialog::OnCancel();
}

BOOL CWelfareDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CWelfareDlg::OnSetfocusIssue()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入预测期号"));
}


void CWelfareDlg::OnSetfocusArr1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入序列一"));
}


void CWelfareDlg::OnSetfocusArr2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入序列二"));
}


void CWelfareDlg::OnSetfocusArr3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入序列三"));
}

void CWelfareDlg::OnSetfocusArr4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入序列四"));
}

void CWelfareDlg::OnSetfocusBoldcode()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入胆码"));
}


void CWelfareDlg::OnSetfocusPlustail()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入和值尾"));
}


void CWelfareDlg::OnSetfocusTwocode()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("请输入八卦二码，以“#”、“/”、“,”等任意单字符间隔符号隔开,\n如，09#34#45,68/23/90/69"));
}


void CWelfareDlg::OnBnClickedForcast()
{
	if(ec == NULL || ec->getIsInQueue()){  // 新预测,创建新对象
		ec = new Encode();
		//forcastFlag = false;
	}
	// TODO: 在此添加控件通知处理程序代码
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
		
		// 判断各组序列是否有数字重复
		for(int i=0; i<4; i++)
		{
			int flag[MAXSIZE] = {0};// = new int(MAXSIZE);
			//memset(flag,0,MAXSIZE);
			for(vector<int>::iterator it = arr[i].begin(); it != arr[i].end(); it++)
			{
				if( flag[*it] == 1)
				{
					CString tmp;
					tmp.Format(_T("序列 %d 有数字重复,请重新输入"),i+1);
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

		// 和值尾有序化
		ec->orderingByMant();

		// 输出到右边列表中
		for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);	
		}
		totalCodeCount = ec->dvCode.size();
		CString stat;
		stat.Format(_T("组选：初步预测3D码数: %d注。"),ec->dvCode.size());
		m_StatusBar.SetPaneText(0,_T("组码规则: 组选"));		
		m_REInfo.SetWindowTextW(stat);
		m_deCheck.EnableWindow(true);
	}else{
		m_REInfo.SetWindowTextW(_T("输入数据不完整,请仔细检查!"));
	}
}


void CWelfareDlg::OnBnClickedKillcode()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!forcastFlag)
	{
		MessageBox(_T("预测后再杀码"),_T("提示"),MB_OK);
		return;
	}
	vector<Gossip> gossip;
	vector<int> arrkc[5];
	CString csstr[5];
	CString sgossip;
	CString mKuadu;

	m_plusTail.GetWindowTextW(csstr[0]);
	m_boldCode.GetWindowTextW(csstr[1]);
	m_hundred.GetWindowTextW(csstr[2]);
	m_decade.GetWindowTextW(csstr[3]);
	m_unit.GetWindowTextW(csstr[4]);
	m_twoCode.GetWindowTextW(sgossip);
	m_kuaDu.GetWindowTextW(mKuadu);
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
		m_REInfo.SetWindowTextW(_T("请至少输入一类编码作杀码。"));
	}

	// 跨度选码
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
			// 跨度选码
			count += ec->selectBasedSpan(kd);
		}
	}
	// 解析定三码
	CString threeStr;
	m_three.GetWindowTextW(threeStr);
	// 待转换CString变量
	wchar_t *ptrz;             
	char buft[256];        // 目标存储空间
	memset(buft,'\0',256);
	int tclength = threeStr.GetLength()>255?255:threeStr.GetLength();
	ptrz=threeStr.GetBuffer(tclength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrz, -1, buft, sizeof(buft), NULL, NULL);
	int  tcSelCount=0;
	int tclen = strlen(buft);
	// 定三选码
	if(tclen > 0){
		tcSelCount = ec->tcSelect(buft);
	}

	// 解析钓叟码
	CString dshouStr;
	m_dshou.GetWindowTextW(dshouStr);
	// 待转换CString变量
	wchar_t *ptrx;             
	char bufx[256];        // 目标存储空间
	memset(bufx,'\0',256);
	int dslength = dshouStr.GetLength()>255?255:dshouStr.GetLength();
	ptrx=dshouStr.GetBuffer(dslength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrx, -1, bufx, sizeof(bufx), NULL, NULL);
	int  dsSelCount=0;
	int selStrlen = strlen(bufx);
	// 钓叟选码
	if(selStrlen > 0){
		
		dsSelCount = ec->dsSelect(bufx);
	}

	// 杀大和
	int bigCount = 0;
	if(m_bigSum.GetCheck()){
		bigCount = ec->killBig();
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
		// 杀两头
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
		// 杀全奇全偶
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
		// 杀全大全小
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
		ts.Format(_T("杀码 %d 注(杀两头: %d 注, 全大全小： %d，全奇全偶: %d注,大和: %d注,\n钓叟：%d注，三码: %d 注,其他:%d 注)，选出 %d 注."),delTotal,siftCount,blCount,oeCount,bigCount,dsSelCount,tcSelCount,count, ec->dvCode.size());
	}else
		ts.Format(_T("杀码 %d 注，余 %d 注(其中对子 %d 注,非对子 %d 注)."),count,ec->dvCode.size(),pairCount,ec->dvCode.size()-pairCount);
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

// 全大全小
bool isABM(const vector<CodeType>::iterator it){
	if(isExtreme(it)){
		return true;
	}	
	return false;
}
// 全集全偶
bool isAOE(const vector<CodeType>::iterator it){
	if((it->codeSeq[0]%2!=0 && it->codeSeq[1]%2!=0 && it->codeSeq[2] % 2 !=0) || 
		(it->codeSeq[0]%2==0 && it->codeSeq[1]%2==0 && it->codeSeq[2]%2==0))
	{
		return true;
	}
	return false;
}
// 两头
bool isTD(const vector<CodeType>::iterator it){
	int codeSum = it->codeSeq[0]+it->codeSeq[1]+it->codeSeq[2];
	if(codeSum>20 || codeSum < 10){
		return true;
	}
	return false;
}

// 大和
bool isBS(const vector<CodeType>::iterator it){
	if((it->codeSeq[0] + it->codeSeq[1] + it->codeSeq[2])>20){
		return true;
	}
	return false;
}


// 从回收站找出特定类型的3D码，并区分对子非对子
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

// 从回收站找出特定类型的3D码，并区分对子非对子
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

// 打印数据
void printVector(CSelection oSel,vector<CodeType> vec, CString mTitle){
	CString spacestr = _T("      ");
	CString separator = _T("\n-------------------------------");
	CMyFont font = oSel.get_Font();
	font.put_Size( 12 );
	CString str;
	str.Format(_T(" \n\n※ "));
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
*	导出函数加入了组选
*
*/
void CWelfareDlg::OnBnClickedExport()
{
	int count = m_listCode.GetCount();

	oddCodeCount = count;
	killCodeCount = totalCodeCount - oddCodeCount ;
	if(!forcastFlag ||(count <= 0 && ec->dvCode.size() <= 0))
	{
		m_REInfo.SetWindowTextW(_T("未预测或列表编码为空"));
		return;
	}

	m_REInfo.SetWindowTextW(_T("预测报表正在生成中,请稍后..."));

	CString cf;
	m_issue.GetWindowTextW(cf);
	int issue = 888;
	if(cf.GetLength())
	{
		issue = _ttoi(cf);
		//cf += _T("期3D码预测");
		//filename = cf.GetBuffer(cf.GetLength());
	}

	vector<CString> pairCode;
	vector<CString> nonpairCode;

	CString spacestr = _T("      ");
	CString separator = _T("\n------------------------------");
	CString shortSeparator = _T("\n---------------");
	int stdIndex = ec->getIsMerge()?3:0;

	// 根据 ec->dvCode 组码
	//ec->classify();
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

	// 定义word操作变量
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
		AfxMessageBox( _T( "word初始化失败！" ) , MB_OK & MB_SETFOREGROUND);  
		return;  // 返回，否则程序崩溃 
	}
	// 先不显示
	oWordApp.put_Visible(false);

	oDocs = oWordApp.get_Documents(); 
	oDoc = oDocs.Add(vopt,vopt,vopt,vopt);
	oSel = oWordApp.get_Selection();
	oSel.WholeStory();
	
	CParagraphFormat cformat = oSel.get_ParagraphFormat();
	cformat.put_Alignment(0);

	CString codetype;
	if(ec->getCodeType() == DIRECT){
		codetype.Format(_T("直选"));
	}else{
		codetype.Format(_T("组选"));
	}

	CMyFont font = oSel.get_Font();
	CString str;
	str.Format(_T("\t\t第 %d 期 福彩3D码预测（%s）打印报表\n"),issue,codetype);	
	font.put_Name(_T("黑体"));
	font.put_Size(18);
	oSel.TypeText(str);
	str.Format(_T("\t\t\t\t共计 %d 注3D码,本报表由 我要发·518 导出！！\n"),count);
	font.put_Name(_T("宋体"));
	font.put_Size(12);
	oSel.TypeText(str);
	oSel.TypeParagraph();
	font.put_Size(14);

	font.put_Name(_T("黑体"));
	str.Format(_T("※ 对子: %d 注 "),pairCode.size());
	oSel.TypeText(str);
	font.put_Size( 10 );
	font.put_Name(_T("宋体"));
	if(ec->getCodeType() == GROUP){
		oSel.TypeText(separator);
	}
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

	bool segFlag = false;
	bool headDesc = true;
	int low500Count = 0;
	for(vector<CString>::iterator it = pairCode.begin(); it != pairCode.end(); it++){
		CString tmp = *it;
		if(tmp[stdIndex] < '5')
			low500Count ++;
		else
			break;
	}
	// 导出对子
	for(vector<CString>::iterator it = pairCode.begin(); it != pairCode.end(); it++)
	{
		CString tmp = *it;
		if(ec->getCodeType() == DIRECT){
			if(headDesc){
				headDesc = false;
				font.put_Size( 12 );
				str.Format(_T(" △小于500者: %d 注"),low500Count);
				oSel.TypeText(str);
				oSel.TypeText(shortSeparator);
				font.put_Size( 14 );
				oSel.TypeParagraph();
			}
			if(!segFlag && tmp[stdIndex] >= '5'){
				segFlag = true;
				font.put_Size( 12 );
				str.Format(_T(" \n\n△大于500者: %d 注"),pairCode.size() - low500Count);
				oSel.TypeText(str);
				oSel.TypeText(shortSeparator);
				font.put_Size( 14 );
				oSel.TypeParagraph();
			}
		}
		oSel.TypeText(tmp);
		oSel.MoveLeft(COleVariant((short)2),COleVariant((short)1),COleVariant((short)1));
		font.put_Size( 10 );
		oSel.MoveRight(COleVariant((short)2),COleVariant((short)1),COleVariant((short)0));
		font.put_Size( 14 );
		oSel.TypeText(spacestr);
	}
	
	// 导出少数派对子
	if(flagExport){
		CString mTitle;
		mTitle.Format(_T("少数派·对子[ %d ]注"),vp.size());
		printVector(oSel,vp,mTitle);
	}
	font.put_Name(_T("黑体"));
	font.put_Size( 14 );
	str.Format(_T(" \n\n※ 非对子: %d 注 "),nonpairCode.size());
	oSel.TypeText(str);
	font.put_Size( 10 );
	font.put_Name(_T("宋体"));
	if(ec->getCodeType() == GROUP){
		oSel.TypeText(separator);
	}
	font.put_Size( 14 );
	oSel.TypeParagraph();

	segFlag = false;
	low500Count = 0;
	headDesc = true;

	for(vector<CString>::iterator it = nonpairCode.begin(); it != nonpairCode.end(); it++){
		CString tmp = *it;
		if(tmp[stdIndex] < '5')
			low500Count ++;
		else
			break;
	}
	// 导出非对子
	for(vector<CString>::iterator it = nonpairCode.begin(); it != nonpairCode.end(); it++)
	{
		CString tmp = *it;
		if(ec->getCodeType() == DIRECT){
			if(headDesc){
				headDesc = false;
				font.put_Size( 12 );
				str.Format(_T("△小于500者: %d 注"),low500Count);
				oSel.TypeText(str);
				oSel.TypeText(shortSeparator);
				font.put_Size( 14 );
				oSel.TypeParagraph();
			}
			if(!segFlag && tmp[stdIndex] >= '5'){
				segFlag = true;
				font.put_Size( 12 );
				str.Format(_T(" \n\n△大于500者: %d 注"),nonpairCode.size() - low500Count);
				oSel.TypeText(str);
				oSel.TypeText(shortSeparator);
				font.put_Size( 14 );
				oSel.TypeParagraph();
			}
		}

		oSel.TypeText(tmp);
		oSel.MoveLeft(COleVariant((short)2),COleVariant((short)1),COleVariant((short)1));
		font.put_Size( 10 );
		oSel.MoveRight(COleVariant((short)2),COleVariant((short)1),COleVariant((short)0));
		font.put_Size( 14 );
		oSel.TypeText(spacestr);
	}
	pairCode.clear();
	nonpairCode.clear();
	segFlag = false;
	low500Count = 0;
	// 导出少数派非对子
	if(flagExport){
		CString mTitle;
		mTitle.Format(_T("少数派·非对子[ %d ]注"),vn.size());
		printVector(oSel,vn,mTitle);
		vp.clear();
		vn.clear();
	}
	CString stat;
	stat.Format(_T("预测已经导出,3D码:%d 注"),count);
	m_REInfo.SetWindowTextW(stat);

	// 显示报表
	oWordApp.put_Visible(true);
	
}

void CWelfareDlg::OnBnClickedReset()
{
	if(!ec->getIsInQueue()){
		ec->eraseCode();
		queueNum = 0;
	}
	m_listCode.ResetContent();

	while(!recoverCodeStack.empty())
	{
		recoverCodeStack.pop();
	}
	totalCodeCount = 0;
	killCodeCount = 0;
	oddCodeCount = 0;
	//m_issue.SetWindowTextW(_T(""));
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
	m_StatusBar.SetPaneText(0,_T("欢迎使用！"));
	forcastFlag = FALSE;
}


void CWelfareDlg::OnDblclkListcode()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_checkTip.GetCheck())
	{
		if(IDOK!=MessageBox(_T("确定，将会删除所选预测码，否则取消"),_T("提示"),MB_OKCANCEL))
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
	delString += _T(" 已删除！");
	m_REInfo.SetWindowTextW(delString);
}


void CWelfareDlg::OnBnClickedRevocation()
{
	// TODO: 在此添加控件通知处理程序代码
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
	revocationString += _T(" 已撤销删除！");
	m_REInfo.SetWindowTextW(revocationString);
}


void CWelfareDlg::OnEnChangeTwocode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if(forcastFlag && m_sift.GetCheck())
	{
		if(IDOK != MessageBox(_T("选择确定，则删除和值不在10~20的3D码，否则不删除"),_T("提示"),MB_OKCANCEL))
		{
			m_sift.SetCheck(FALSE);
			return;
		}
		// 直接删除ec对象中的数据，再重新打印
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
		info.Format(_T("筛选删除 %d 注3D码，余%d 注3D码，共 %d 注3D码!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}
}

//void CWelfareDlg::OnLbnSelchangeListcode()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CWelfareDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	m_export.SendMessage(BN_CLICKED);
	OnBnClickedExport();
}


void CWelfareDlg::OnQuit()
{
	// TODO: 在此添加命令处理程序代码
	SendMessage(WM_CLOSE);
}


//void CWelfareDlg::OnBnClickedPreprint()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if(!forcastFlag)
//	{
//		MessageBox(_T("请预测后再操作"),_T("提示"),MB_OK);
//		return;
//	}
//	CPrePrintDlg cpp;
//	cpp.cParentWnd = this;
//	cpp.DoModal();
//}




//void CAboutDlg::OnAbout()
//{
//	// TODO: 在此添加命令处理程序代码
//	CAboutDlg about;
//	about.DoModal();
//}


void CWelfareDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg about;
	about.DoModal();
}


void CWelfareDlg::OnSelchangeListcode()
{
	// TODO: 在此添加控件通知处理程序代码
}



void CWelfareDlg::OnBnClickedKilloddeven()
{
	// TODO: 在此添加控件通知处理程序代码
	if(forcastFlag && m_killAOE.GetCheck())
	{
		if(IDOK != MessageBox(_T("选择确定，则删除各位全奇或全偶的3D码，否则不删除"),_T("提示"),MB_OKCANCEL))
		{
			m_killAOE.SetCheck(FALSE);
			return;
		}
		// 直接删除ec对象中的数据，再重新打印
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
		info.Format(_T("筛选删除 %d 注3D码，余%d 注3D码，共 %d 注3D码!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}

}
// 判定全大全小
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
		if(IDOK != MessageBox(_T("选择确定，则删除各位全大或全小的3D码，否则不删除"),_T("提示"),MB_OKCANCEL))
		{
			m_killABL.SetCheck(FALSE);
			return;
		}
		// 直接删除ec对象中的数据，再重新打印
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
		info.Format(_T("筛选删除 %d 注3D码，余%d 注3D码，共 %d 注3D码!!"),delCount,m_listCode.GetCount(),m_listCode.GetCount()+delCount);
		m_REInfo.SetWindowTextW(info);
	}
}

CString CWelfareDlgGetFileVer()
{ /*
 TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion("hello");

 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
 if(InfoSize==0) return _T("None VerSion Supprot");
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CWelfareDlg::OnSetfocusDshou()
{
	// TODO: 在此添加控件通知处理程序代码
	m_REInfo.SetWindowTextW(_T("可输入任意组钓叟码，中间用#、/、*等字符隔开，例如：\n\t168#2518#56789\n\t123456 32457 45678"));
}

// 转换为直选
void CWelfareDlg::OnClickedDecheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if(forcastFlag && m_deCheck.GetCheck()){
		ec->grouptodirect();
		ec->ordering();

		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it = ec->dvCode.begin(); it != ec->dvCode.end(); )
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
			it++;
		}

		CString info;
		info.Format(_T("已转换为直选，共 %d 注3D码!!"),ec->dvCode.size());
		m_StatusBar.SetPaneText(0,_T("组码规则: 直选"));
		m_REInfo.SetWindowTextW(info);
	}
}

// 杀大和
void CWelfareDlg::OnClickedBigsum()
{
	// TODO: 在此添加控件通知处理程序代码
	if(forcastFlag && m_bigSum.GetCheck()){

		if(IDOK != MessageBox(_T("选择是，将杀掉和尾值大于20的3D码？"),_T("杀大和提示"),MB_OKCANCEL))
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
		info.Format(_T("大和杀码 %d 注，共 %d 注3D码!!"),count,ec->dvCode.size());
		m_REInfo.SetWindowTextW(info);
	}
}


void CWelfareDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CWelfareDlg::OnSetfocusThree()
{
	m_REInfo.SetWindowTextW(_T("可输入任意组定三码，中间用#、/、*等字符隔开，例如：\n\t168#2518#56789\n\t123456 32457 45678"));
}


void CWelfareDlg::OnBnClickedAddqueue()
{
	// 将当前预测加入到预测队列
	if(ec->getIsInQueue())
		return;
	if(ecVector.size()>0 && ecVector[0]->getCodeType() != ec->getCodeType()){
		MessageBox(_T("组码类型不一致，无法加入到队列？"),_T("提示"),MB_OK);
		return;
	}
	ecVector.push_back(ec);
	ec->setInQueue(true);
	queueNum ++;
	CString listItemStr;
	listItemStr.Format(_T("第 %d 组"),queueNum);
	mListc.InsertItem(mListc.GetItemCount(),listItemStr);
}


void CWelfareDlg::OnClickForcastqueue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// 更新ec值,这不是必须的
	 NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	 if(pNMListView->iItem != -1){
		ec = ecVector[pNMListView->iItem];
		// 输出到右边列表中
		m_listCode.ResetContent();
		for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
		{
			CString tmp;
			tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
			m_listCode.AddString(tmp);
		}
		// 提示信息
		CString info;
		info.Format(_T(" 组预测,共 %d 注3D码."),m_listCode.GetCount());
		m_REInfo.SetWindowTextW(mListc.GetItemText(pNMListView->iItem,0) + info);
	 }
	*pResult = 0;
}

// ** 双击时提示用户是否删除该组预测码
void CWelfareDlg::OnDblclkForcastqueue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1){
		if(IDOK == MessageBox(_T("是否删除该组预测码？"),_T("提示"),MB_OKCANCEL))
		{
			mListc.DeleteItem(mListc.GetNextItem(-1,LVNI_SELECTED));
			return;
		}
		
	}
	*pResult = 0;
}


void CWelfareDlg::OnBnClickedClearall()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedReset();
	ecVector.clear();
	queueNum = 0;
	m_issue.SetWindowTextW(_T(""));
	//if(ecVector.empty()){
	//	MessageBoxW(_T("预测队列已经清空"));
	//}
	// 清除预测队列
	mListc.DeleteAllItems();
}


void CWelfareDlg::OnBnClickedCompositeselect()
{
	if(mListc.GetItemCount() == 0)
	{
		 MessageBox(_T("请先设置预测队列"),_T("提示"),MB_OKCANCEL);
		 return;
	}
	CString mergeTitle(_T("组"));
	// 计算频度
	ec = new Encode();
	for (int i=0; i<mListc.GetItemCount(); i++){
		//if(mListc.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED || mListc.GetCheck(i)){
			if(((i+1)>ecVector.size()) || ecVector[i]->getIsMerge() ||!ecVector[i]->getIsInQueue())
				continue;
			int flag = ec->merge(ecVector[i]);
			if(flag == -1){
				MessageBoxW(_T("组码类型(组选/直选)不一致,请重新选择"));
				break;
			}else{
				mergeTitle += _T("-") + mListc.GetItemText(i,0);
			}
		//}
	}

	// 自动添加到预测队列
	ecVector.push_back(ec);
	ec->setInQueue(true);
	mListc.InsertItem(mListc.GetItemCount(),mergeTitle);
	

	// 打印到右边
	m_listCode.ResetContent();
	for(vector<CodeType>::iterator it=ec->dvCode.begin(); it != ec->dvCode.end(); it++)
	{
		CString tmp;
		tmp.Format(_T("%d%d%d-%d"),it->codeSeq[0],it->codeSeq[1],it->codeSeq[2],it->mantissa);
		m_listCode.AddString(tmp);
	}

	// 提示信息
	CString infoM;
	infoM.Format(_T("归并完成，共 %d 注3D码.如需查看频度，请导出文件。"),ec->dvCode.size());
	m_REInfo.SetWindowTextW(infoM);
}

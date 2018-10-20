// TrailMousePosDlg.cpp : implementation file
//  Download by http://www.codefans.net

#include "stdafx.h"
#include "TrailMousePos.h"
#include "TrailMousePosDlg.h"
#include "atlimage.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

CString gImgPath,gImgPath1;
CImage MyImage,MyImage1;
unsigned char image[600][800];
char image1[600][800];
char signal_1=0,signal_2=0,signal_3=0,signal_4=0,signal_5=0;
CString str;
int x_count,y_count;


double result;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL imgPosition=FALSE;
BOOL checkimage=FALSE;
int flag_count1=0,flag2=0,flag3=0;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrailMousePosDlg dialog

CTrailMousePosDlg::CTrailMousePosDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrailMousePosDlg::IDD, pParent)
	, m_EditRecieve(_T(""))
{
	//{{AFX_DATA_INIT(CTrailMousePosDlg)

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CTrailMousePosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrailMousePosDlg)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	//	DDX_Text(pDX, IDC_EDIT1, m_EditRecieve);


}

BEGIN_MESSAGE_MAP(CTrailMousePosDlg, CDialog)
	//{{AFX_MSG_MAP(CTrailMousePosDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTrailMousePosDlg::OnBnClickedButton1)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrailMousePosDlg message handlers

BOOL CTrailMousePosDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrailMousePosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrailMousePosDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect lImg(450,300,1250,900);
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		CBitmap bitmap; 
		bitmap.LoadBitmap(IDB_BITMAP2); //���IDB_BITMAP1Ҫ�Լ����
		CBrush brush; 
		brush.CreatePatternBrush(&bitmap); 
		CBrush* pOldBrush =dc.SelectObject(&brush); 
		dc.Rectangle(0,0,2160,1440); // ��Щ�������Ե���ͼƬ���λ�úʹ�С 
		dc.SelectObject(pOldBrush);
		if(gImgPath.IsEmpty())
		{
			dc.FillSolidRect(&lImg, RGB(96,96,96));			
		}                         
		else 
		{

				MyImage1.Draw(dc.m_hDC,lImg.left,lImg.top,lImg.Width(),lImg.Height());
			if(checkimage)
			{
				MyImage.Draw(dc.m_hDC,lImg.left,lImg.top,lImg.Width(),lImg.Height());
				checkimage=FALSE;
			}
	
		}
		HBITMAP   hBitmap1, hBitmap2,hBitmap3;   
		if(flag_count1==0)
		{
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image1//1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image1//2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap1);
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image1//3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image1//4.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap1); 	
		}
		if(flag_count1==1)
		{
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image2//1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image2//2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap1);
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image2//3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image2//4.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap1); 
		}
		if(flag_count1==2)
		{
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image3//1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image3//2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap1);
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image3//3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image3//4.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap1); 	
		}
		if(flag_count1==3)
		{
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image4//1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image4//2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap1);
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image4//3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image4//4.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap1); 	
		}
		if(flag_count1==4)
		{
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image5//1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image5//2.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap1);
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image5//3.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap1); 	
		hBitmap1 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//image5//4.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON6))->SetBitmap(hBitmap1); 	
		}
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//start.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap2); 	
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//quit.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap2);
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//��һ��1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON7))->SetBitmap(hBitmap2); 	
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//��һ��1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON8))->SetBitmap(hBitmap2); 
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//���ѡͼ1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON9))->SetBitmap(hBitmap2); 	
		hBitmap2 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//�鿴��1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap2); 

		hBitmap3 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//��ѡ��.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap3); 
	
		if(flag3==1)
		{
		hBitmap3 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//ѡ����ȷ1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap3); 
		flag3=0;
		}
		if(flag3==2)
		{
		hBitmap3 = (HBITMAP)::LoadImage(NULL,"C://haptic//haptics6.0//imagelib61//ѡ�����1.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION); 
		((CButton *)GetDlgItem(IDC_BUTTON11))->SetBitmap(hBitmap3); 
		flag3=0;
		}


		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrailMousePosDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTrailMousePosDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	//�����굱ǰλ��

	x_count=point.x;
	y_count=point.y;
	if((x_count>=450)&&(x_count<1250)&&(y_count>=300)&&(y_count<900))
		{
	/***********************************�ڰ�ͼ*********************************/	
		   signal_1=image[y_count-300][x_count-450];
		   signal_2=image1[y_count-300][x_count-450];
		   signal_3=3;
		   signal_4=5;
		   signal_5=8;

	TRACE(_T("ԭʼ: %d ��Ե: %d ����: %d Ƶ��: %d ����: %d\n"),signal_1,signal_2,signal_3,signal_4,signal_5);
	
	
	UpdateData(FALSE);

	if(m_mscomm.get_PortOpen())	
	{
		CString strtemp;
	
			strtemp.Format(_T("b%c%c%c%c%c"),signal_1,signal_2,signal_3,signal_4,signal_5);

		str = strtemp;
		//TRACE(_T("B������: %s \n"),strtemp);
		TRACE(_T("���ڷ���: %s \n"),str);
		m_mscomm.put_Output(COleVariant(strtemp));
	}
}
else 
	{
     signal_1=0;signal_2=0;signal_5=0;
	UpdateData(FALSE);

	if(m_mscomm.get_PortOpen())	
	{
		CString strtemp;
	
			strtemp.Format(_T("b%c%c%c%c%c"),signal_1,signal_2,signal_3,signal_4,signal_5);

		str = strtemp;
		//TRACE(_T("B������: %s \n"),strtemp);
		TRACE(_T("���ڷ���: %s \n"),str);
		m_mscomm.put_Output(COleVariant(strtemp));
	}
	}
	CDialog::OnMouseMove(nFlags, point);
}


void CTrailMousePosDlg::OnBnClickedButton1()
{
 
	//ѡ��ͼ���ļ�
	

		if(m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);
	}
	m_mscomm.put_CommPort(4);//ѡ��COM1
	m_mscomm.put_InBufferSize(1024);//���ջ�����
	m_mscomm.put_OutBufferSize(1024);//���ͻ�����
	m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0����ʾȫ����ȡ
	m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
	m_mscomm.put_RThreshold(1);//���ջ�������һ������һ����������ʱ���������������ݵ�OnComm�¼�
	m_mscomm.put_Settings(_T("9600,n,8,1"));
	if(!m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(TRUE);
		//AfxMessageBox(_T("�����ɹ�"));
	AfxMessageBox(_T("�����ɹ�"));

	}
	else
	{
		m_mscomm.put_OutBufferCount(0);
		AfxMessageBox(_T("����ʧ��"));
	}

	Invalidate();
}


void CTrailMousePosDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	signal_1=0;signal_2=0;signal_5=0;
	UpdateData(FALSE);

	if(m_mscomm.get_PortOpen())	
	{
		CString strtemp;
	
			strtemp.Format(_T("b%c%c%c%c%c"),signal_1,signal_2,signal_3,signal_4,signal_5);

		str = strtemp;
		//TRACE(_T("B������: %s \n"),strtemp);
		TRACE(_T("���ڷ���: %s \n"),str);
		m_mscomm.put_Output(COleVariant(strtemp));
	}
	CDialog::OnCancel();

}

		

BEGIN_EVENTSINK_MAP(CTrailMousePosDlg, CDialog)
	ON_EVENT(CTrailMousePosDlg, IDC_MSCOMM1, 1, CTrailMousePosDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CTrailMousePosDlg::OnCommMscomm1()
{
	// TODO: �ڴ˴������Ϣ����������
	static unsigned int cnt=0;
	VARIANT variant_inp;
	COleSafeArray safearray_inp; 
	long len,k;
	unsigned int data[1024]={0};
	byte rxdata[1024];//����BYTE����
	CString strtemp;
	if(m_mscomm.get_CommEvent()==2)
	{
		cnt++;
		variant_inp=m_mscomm.get_Input();//������������
		safearray_inp=variant_inp;//����ת��
		len=safearray_inp.GetOneDimSize();//�õ���Ч�����ݳ���
		for(k=0;k<len;k++)
		{
			safearray_inp.GetElement(&k,rxdata+k);
		}
		for(k=0;k<len;k++)//������ת��ΪCString�ͱ���
		{
			strtemp.Format(_T("%c"),*(rxdata+k));
			m_EditRecieve+=strtemp;
			CString temp = _T(" ");
			m_EditRecieve += temp;
			//temp=_T("\r\n");
			//m_EditRecieve+=temp;
		}
	}
	UpdateData(FALSE);//���±༭������
}


void CTrailMousePosDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MyImage.Destroy();MyImage1.Destroy();
	srand((unsigned)time(0));
	flag2=(rand()%4);
	if(flag_count1==0)
       {
		if(flag2==0)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image1//1.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==1)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image1//2.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==2)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image1//3.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==3)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image1//4.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
	    }
	if(flag_count1==1)
       {
		if(flag2==0)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image2//1.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==1)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image2//2.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==2)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image2//3.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==3)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image2//4.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}	
	    }
	if(flag_count1==2)
        {
		if(flag2==0)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image3//1.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==1)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image3//2.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==2)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image3//3.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==3)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image3//4.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}	
	    }
	if(flag_count1==3)
       {
		if(flag2==0)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image4//1.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==1)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image4//2.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==2)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image4//3.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==3)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image4//4.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}	
	    }
	if(flag_count1==4)
        {
		if(flag2==0)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image5//1.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==1)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image5//2.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==2)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image5//3.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}
		if(flag2==3)
		{
	   gImgPath="C://haptic//haptics6.0//imagelib6//image5//4.jpg";	    
	   MyImage.Load(gImgPath);
	   gImgPath1="C://haptic//haptics6.0//imagelib6//0.jpg";	    
	   MyImage1.Load(gImgPath1);	
		}	
	    }
		for(int x=0; x<800; x++)
		{
			for(int y=0; y<600; y++)
			{
				COLORREF pixel = MyImage.GetPixel(x,y);//����COLORREF pixel = NewImage.GetPixel(x,y);
				//NewImage.SetPixel(x,y,pixel);
				unsigned char r,g,b,t;
				r=GetRValue(pixel);
				g=GetGValue(pixel);
				b=GetBValue(pixel);
				t=(r+g+b)/3;
				image[y][x]=t/8;
			}
		}
       for(int x=0; x<799; x++)
	     {
		for(int y=0; y<599; y++)
		   {
          byte s;
	      result=sqrt(((image[y][x]-image[y+1][x+1])*(image[y][x]-image[y+1][x+1]))*1.0+((image[y+1][x]-image[y][x+1])*(image[y+1][x]-image[y][x+1]))*1.0);
		  s=char(result);
		  if(s>5)
			  image1[y][x]=s;
		  
		  else
			   image1[y][x]=0;
		    }	   
	      }	
	
	Invalidate();
}



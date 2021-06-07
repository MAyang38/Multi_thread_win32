#include "stdafx.h"
#include "ThreadDamo1.h"
#include<windows.h> 
#define MAX_LOADSTRING 100

HWND ThrhWnd1=NULL;																														//##线程1的编辑框句柄
HWND ThrhWnd2=NULL;
HWND ThrhWnd3=NULL;

HANDLE ThrHandle1=NULL;																													//##线程1的线程句柄
HANDLE ThrHandle2=NULL;
HANDLE ThrHandle3=NULL;

int thrCoins1=0;																																		//##线程1的硬币数
int thrCoins2=0;
int thrCoins3=0;

//##
DWORD WINAPI ThreadProc1(LPVOID lpParameter);
DWORD WINAPI ThreadProc2(LPVOID lpParameter);
DWORD WINAPI ThreadProc3(LPVOID lpParameter);

/*void DrawCoins(int x,int y,int thrCoins,int);	*/																								//?????????????????

// 全局变量:
HWND hWnd;
HMENU hMenu;														//##
HINSTANCE hInst;													// 当前实例
TCHAR szTitle[MAX_LOADSTRING];							// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);                                                                         //##用于注册窗口类，注册类后才能调用createwindows函数创建窗口
BOOL				InitInstance(HINSTANCE, int);																							//##createwindows函数在initinstance函数中调用
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
																																								//##这几个函数都是被winmain函数调用的，winmain函数代表的是gui主线程的入口函数
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THREADDAMO1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADDAMO1));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREADDAMO1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CTLCOLOR_BTN+1);																						//##原本的COLOR_WINDOW改成CTLCOLOR_BTN
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_THREADDAMO1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   //##这里正用createwindow函数创建窗口
   //##去掉最大化按钮的方法
   /*##方法1---原本的WS_OVERLAPPEDWINDOW改成WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX取消了“最大化”
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX,	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	  if (!hWnd)
	  {	  return FALSE;	}
	*/
   //##方法2
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {	return FALSE;   }
   
   LONG lStyle=GetWindowLong(hWnd,GWL_STYLE);				//##GetWindowLong是一个Windows API函数，获得指定窗口的有关信息，也获得在额外窗口内存中指定偏移位地址的32位度整型值。
   lStyle &=~WS_MAXIMIZEBOX;
   SetWindowLong(hWnd,GWL_STYLE,lStyle);							//##设置窗口的风格

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//##
HWND CreateEditControlForMainWnd(int x,int y,int nWindth,int nHeight,HWND hWndParent,HINSTANCE hInstance)
{
	return CreateWindow(_T("EDIT"),_T("0"),WS_CHILD|WS_VISIBLE,x,y,nWindth,nHeight,hWndParent,NULL,hInstance,NULL);
}

void CreateStaticForMainWnd(LPCTSTR lpWindowName ,int x,int y,int nWidth,int nHeight,HWND hWndParent,HINSTANCE hInstance)
{
	CreateWindow(_T("STATIC"),lpWindowName,WS_CHILD|WS_VISIBLE,x,y,nWidth,nHeight,hWndParent,NULL,hInstance,NULL);
}



//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{	
	case WM_CREATE:
		{
			ThrhWnd1 = CreateEditControlForMainWnd(100,300,100,20,hWnd,hInst);
			ThrhWnd2 = CreateEditControlForMainWnd(300,300,100,20,hWnd,hInst);
			ThrhWnd3 = CreateEditControlForMainWnd(500,300,100,20,hWnd,hInst);

			CreateStaticForMainWnd(_T("线程1"),100,270,100,20,hWnd,hInst);
			CreateStaticForMainWnd(_T("线程2"),300,270,100,20,hWnd,hInst);
			CreateStaticForMainWnd(_T("线程3"),500,270,100,20,hWnd,hInst);

			ThrHandle1 = CreateThread(NULL,0,ThreadProc1,NULL,CREATE_SUSPENDED,NULL);														//##创建3个线程
			ThrHandle2 = CreateThread(NULL,0,ThreadProc2,NULL,CREATE_SUSPENDED,NULL);
			ThrHandle3 = CreateThread(NULL,0,ThreadProc3,NULL,CREATE_SUSPENDED,NULL);

			hMenu = GetMenu(hWnd);
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_RESUME:																																									//##启动的消息事件 
			{
				EnableMenuItem(hMenu,IDM_SUSPEN,MF_ENABLED);																		//##这两个函数语句放在resumethread函数后面比较好理解
				EnableMenuItem(hMenu,IDM_RESUME,MF_GRAYED);
				DrawMenuBar(hWnd);

				ResumeThread(ThrHandle1);
				ResumeThread(ThrHandle2);
				ResumeThread(ThrHandle3);
			}		
			break;
		case IDM_SUSPEN:
			{
				EnableMenuItem(hMenu,IDM_SUSPEN,MF_GRAYED);
				EnableMenuItem(hMenu,IDM_RESUME,MF_ENABLED);
				DrawMenuBar(hWnd);

				SuspendThread(ThrHandle1);
				SuspendThread(ThrHandle2);
				SuspendThread(ThrHandle3);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
// 		DrawCoins(100,200,thrCoins1,RGB(255,0,0));
// 		DrawCoins(300,400,thrCoins1,RGB(0,255,0));
// 		DrawCoins(500,600,thrCoins1,RGB(0,0,255));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	TCHAR szBuf[10]={0};
	int index = 0;

	//获得DC

	HDC hdc = GetDC(hWnd);
	//创建一个红色的画刷并选到DC中去
	HBRUSH hBr = CreateSolidBrush(RGB(255,0,0));
	HBRUSH h01dBR = static_cast <HBRUSH>(SelectObject(hdc,hBr));

	for (int i=0;i<1000;i++)
	{
		wsprintf(szBuf,_T("%d"),i+1);
		SetWindowText(ThrhWnd1,szBuf);
		if (0==i%100)
		{
			int y=250-10*index;
			Ellipse(hdc,100,y,200,y-30);
			index++;
			thrCoins1=index;
		}
		Sleep(50);
	}
	//把旧的画刷选回去，并删除新的画刷
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//释放DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	TCHAR szBuf[10]={0};
	int index = 0;

	//获得DC
	HDC hdc = GetDC(hWnd);
	//创建一个红色的画刷并选到DC中去
	HBRUSH hBr = CreateSolidBrush(RGB(0,255,0));
	HBRUSH h01dBR = static_cast <HBRUSH>(SelectObject(hdc,hBr));

	for (int i=0;i<1000;i++)
	{
		wsprintf(szBuf,_T("%d"),i+1);
		SetWindowText(ThrhWnd2,szBuf);
		if (0==i%100)
		{
			int y=250-10*index;
			Ellipse(hdc,300,y,400,y-30);
			index++;
			thrCoins2=index;
		}
		Sleep(70);
	}
	//把旧的画刷选回去，并删除新的画刷
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//释放DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	TCHAR szBuf[10]={0};
	int index = 0;

	//获得DC
	HDC hdc = GetDC(hWnd);
	//创建一个红色的画刷并选到DC中去
	HBRUSH hBr = CreateSolidBrush(RGB(0,0,255));
	HBRUSH h01dBR = static_cast <HBRUSH>(SelectObject(hdc,hBr));

	for (int i=0;i<1000;i++)
	{
		wsprintf(szBuf,_T("%d"),i+1);
		SetWindowText(ThrhWnd3,szBuf);
		if (0==i%100)
		{
			int y=250-10*index;
			Ellipse(hdc,500,y,600,y-30);
			index++;
			thrCoins3=index;
		}
		Sleep(90);
	}
	//把旧的画刷选回去，并删除新的画刷
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//释放DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

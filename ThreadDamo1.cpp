#include "stdafx.h"
#include "ThreadDamo1.h"
#include<windows.h> 
#define MAX_LOADSTRING 100

HWND ThrhWnd1=NULL;																														//##�߳�1�ı༭����
HWND ThrhWnd2=NULL;
HWND ThrhWnd3=NULL;

HANDLE ThrHandle1=NULL;																													//##�߳�1���߳̾��
HANDLE ThrHandle2=NULL;
HANDLE ThrHandle3=NULL;

int thrCoins1=0;																																		//##�߳�1��Ӳ����
int thrCoins2=0;
int thrCoins3=0;

//##
DWORD WINAPI ThreadProc1(LPVOID lpParameter);
DWORD WINAPI ThreadProc2(LPVOID lpParameter);
DWORD WINAPI ThreadProc3(LPVOID lpParameter);

/*void DrawCoins(int x,int y,int thrCoins,int);	*/																								//?????????????????

// ȫ�ֱ���:
HWND hWnd;
HMENU hMenu;														//##
HINSTANCE hInst;													// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];							// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);                                                                         //##����ע�ᴰ���࣬ע�������ܵ���createwindows������������
BOOL				InitInstance(HINSTANCE, int);																							//##createwindows������initinstance�����е���
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
																																								//##�⼸���������Ǳ�winmain�������õģ�winmain�����������gui���̵߳���ں���
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THREADDAMO1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADDAMO1));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
	wcex.hbrBackground	= (HBRUSH)(CTLCOLOR_BTN+1);																						//##ԭ����COLOR_WINDOW�ĳ�CTLCOLOR_BTN
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_THREADDAMO1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   //##��������createwindow������������
   //##ȥ����󻯰�ť�ķ���
   /*##����1---ԭ����WS_OVERLAPPEDWINDOW�ĳ�WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOXȡ���ˡ���󻯡�
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX,	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	  if (!hWnd)
	  {	  return FALSE;	}
	*/
   //##����2
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {	return FALSE;   }
   
   LONG lStyle=GetWindowLong(hWnd,GWL_STYLE);				//##GetWindowLong��һ��Windows API���������ָ�����ڵ��й���Ϣ��Ҳ����ڶ��ⴰ���ڴ���ָ��ƫ��λ��ַ��32λ������ֵ��
   lStyle &=~WS_MAXIMIZEBOX;
   SetWindowLong(hWnd,GWL_STYLE,lStyle);							//##���ô��ڵķ��

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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

			CreateStaticForMainWnd(_T("�߳�1"),100,270,100,20,hWnd,hInst);
			CreateStaticForMainWnd(_T("�߳�2"),300,270,100,20,hWnd,hInst);
			CreateStaticForMainWnd(_T("�߳�3"),500,270,100,20,hWnd,hInst);

			ThrHandle1 = CreateThread(NULL,0,ThreadProc1,NULL,CREATE_SUSPENDED,NULL);														//##����3���߳�
			ThrHandle2 = CreateThread(NULL,0,ThreadProc2,NULL,CREATE_SUSPENDED,NULL);
			ThrHandle3 = CreateThread(NULL,0,ThreadProc3,NULL,CREATE_SUSPENDED,NULL);

			hMenu = GetMenu(hWnd);
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_RESUME:																																									//##��������Ϣ�¼� 
			{
				EnableMenuItem(hMenu,IDM_SUSPEN,MF_ENABLED);																		//##����������������resumethread��������ȽϺ����
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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

	//���DC

	HDC hdc = GetDC(hWnd);
	//����һ����ɫ�Ļ�ˢ��ѡ��DC��ȥ
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
	//�ѾɵĻ�ˢѡ��ȥ����ɾ���µĻ�ˢ
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//�ͷ�DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	TCHAR szBuf[10]={0};
	int index = 0;

	//���DC
	HDC hdc = GetDC(hWnd);
	//����һ����ɫ�Ļ�ˢ��ѡ��DC��ȥ
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
	//�ѾɵĻ�ˢѡ��ȥ����ɾ���µĻ�ˢ
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//�ͷ�DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	TCHAR szBuf[10]={0};
	int index = 0;

	//���DC
	HDC hdc = GetDC(hWnd);
	//����һ����ɫ�Ļ�ˢ��ѡ��DC��ȥ
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
	//�ѾɵĻ�ˢѡ��ȥ����ɾ���µĻ�ˢ
	SelectObject(hdc,h01dBR);
	DeleteObject(hBr);
	//�ͷ�DC
	ReleaseDC(hWnd,hdc);
	return 0;
}

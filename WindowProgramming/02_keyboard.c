#include <windows.h>
#include <WindowsX.h>
#include <math.h>
#include <stdlib.h>
#define BSIZE 20


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("Mid-Exam");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
	LPSTR lpszCmdLine, int nCmdShow)                   //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{                                                 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	HWND   hwnd;                                     //iCmdShow : 윈도우가 화면에 출력될 형태
	MSG      msg;
	WNDCLASS WndClass;                                  //WndClass 라는 구조체 정의                            
	WndClass.style = CS_HREDRAW | CS_VREDRAW;          //출력스타일 : 수직/수평의 변화시 다시 그림
	WndClass.lpfnWndProc = WndProc;                      //프로시저 함수명
	WndClass.cbClsExtra = 0;                         //O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra = 0;                         //O/s 사용 여분 메모리 (Window)
	WndClass.hInstance = hInstance;                   //응용 프로그램 ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //아이콘 유형
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);       //커서 유형
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
	WndClass.lpszMenuName = NULL;                         //메뉴 이름
	WndClass.lpszClassName = lpszClass;                   //클래스 이름
	RegisterClass(&WndClass);                            //앞서 정의한 윈도우 클래스의 주소

	hwnd = CreateWindow(lpszClass,                         //윈도우가 생성되면 핸들(hwnd)이 반환
		lpszClass,                                     //윈도우 클래스, 타이틀 이름
		WS_OVERLAPPEDWINDOW,                            //윈도우 스타일
		200,                                  //윈도우 위치, x좌표
		100,                                  //윈도우 위치, y좌표
		300,                                  //윈도우 폭   
		200,                                  //윈도우 높이   
		NULL,                                        //부모 윈도우 핸들    
		NULL,                                        //메뉴 핸들
		hInstance,                                      //응용 프로그램 ID
		NULL                                          //생성된 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow);                            //윈도우의 화면 출력
	UpdateWindow(hwnd);                                  //O/S 에 WM_PAINT 메시지 전송

	while (GetMessage(&msg, NULL, 0, 0))                      //WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);                            //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;


	static int count = 0;
	static int line = 0;
	static char str[20][21];
	static SIZE size;


	switch (iMsg)
	{
	case WM_CREATE:

		count = 0;
		line = 0;
		break;


	case WM_CHAR:
		if ((wParam == VK_BACK) && (count > 0))
		{
			count--;
		}
		else if (wParam == VK_RETURN)     // Enter키 사용시
		{
			if (line < 19)         //10행 까지만 입력 허용
			{
				count = 0;         //엔터키 입력이 들어왔을때 str[line][0]으로 이동, count 초기화
				line++;          // line증가, 줄 내려감
			}
			else
			{
				break;
			}
		}
		else
		{
			if (count < 20)        // count에 글자를 나열하되 자 이하로
			{
				str[line][count++] = wParam;   // 해당 line에 count에 차곡차곡 보냄
			}
			else
			{
				count = 0;
				line++;
			}

		}
		str[line][count] = '\0';      // 마지막에 입력 문자가 저장된 곳, 즉\0값으로 입력

		InvalidateRgn(hwnd, NULL, FALSE);    // 윈도우 화면을 무효화, 화면의 내용을 삭제, WM_PAINT 함수 이벤트발생 (강제 발생)
		break;

	case WM_KEYDOWN:
		if (wParam == VK_UP)
		{
			if (line > 0)
			{
				line--;

				if (str[line][count] == NULL)
				{
					str[line][count++] = wParam;
				}
			}
			else
			{
				break;
			}

		}
		else if (wParam == VK_DOWN)
		{
			if (line < 19)
			{
				line++;
				if (str[line][count] == NULL)
				{
					str[line][count++] = wParam;
				}
			}
			else
			{
				break;
			}

		}
		InvalidateRgn(hwnd, NULL, FALSE);    // 윈도우 화면을 무효화, 화면의 내용을 삭제, WM_PAINT 함수 이벤트발생 (강제 발생)
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < line + 1; i++)
		{
			GetTextExtentPoint(hdc, str[i], strlen(str[i]), &size); //(도화지, 크기를 측정할 문자열, 몇번째 문자까지 크기측정, 문자열의 폭)
			TextOut(hdc, 0, i * 20, str[i], strlen(str[i]));  //도화지에 (0, i*20)좌표에 str에 저장된 문자열을 출력
			SetCaretPos(size.cx, i * 20);      // 커서 자리 값
		}
		EndPaint(hwnd, &ps);
		break;







	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}

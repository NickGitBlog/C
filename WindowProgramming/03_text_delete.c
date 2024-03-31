#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("New Title Hong Gil Dong");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	RegisterClass(&WndClass);

	hwnd = CreateWindow(lpszClass,
		lpszClass,
		WS_OVERLAPPEDWINDOW,
		100,
		50,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

HDC hdc;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static char linebfr[] = "0123456789";
	static int length = 10;
	const char* str1 = "완료되었습니다.";

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_CHAR:
		if (wParam == 'a' && length > 0) {
			linebfr[--length] = '\0';
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (wParam == 's' && length < 19) {
			// 's' 입력 시 문자열 길이가 최대 길이보다 작은 경우에만 문자 추가
			linebfr[length++] = 'a' + length; // 예시로 'a'부터 순서대로 추가
			linebfr[length] = '\0'; // 문자열의 끝을 나타내는 null 문자 추가
			InvalidateRect(hwnd, NULL, TRUE); // 화면을 다시 그리도록 함
		}
		else if (length == 0) {
			HDC hdc = GetDC(hwnd);
			TextOut(hdc, 150, 150, str1, strlen(str1));
			ReleaseDC(hwnd, hdc);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, linebfr, length);
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "마우스를 클릭했습니다.", "마우스 메시지", MB_OK);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

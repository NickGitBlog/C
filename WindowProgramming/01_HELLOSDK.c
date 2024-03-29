WindowProgramming#include <windows.h>

// WinMain 함수에서 참조하므로 함수 원형을 선언한다.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// hlnstanace : ID  , IpCmdLine 확실히 알아두기!
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wndclass;
    HWND hwnd;
    MSG msg;

    // 윈도우 클래스를 초기화하고 운영체제에 등록한다.
    wndclass.style = CS_HREDRAW | CS_VREDRAW; // 스타일 지정
    wndclass.lpfnWndProc = WndProc; // 윈도우 프로시저 이름
    wndclass.cbClsExtra = 0; // 여분 메모리(0바이트)
    wndclass.cbWndExtra = 0; // 여분 메모리(0바이트)
    wndclass.hInstance = hInstance; // 인스턴스 핸들
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘 모양
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경(흰색)
    wndclass.lpszMenuName = NULL; // 메뉴(NULL->메뉴 없음)
    wndclass.lpszClassName = "Nick"; // 윈도우 클래스 이름

    if (!RegisterClass(&wndclass)) return 1;// 등록 해주고 등록 안되면 1(종료)


    /*
    HWND hWnd = CreateWindow(
    L"ClassName",               // 윈도우 클래스 이름
    L"Hello World",             // 윈도우 타이틀
    WS_OVERLAPPEDWINDOW,        // 윈도우 스타일
    CW_USEDEFAULT,              // X 좌표
    CW_USEDEFAULT,              // Y 좌표
    400,                        // 너비
    300,                        // 높이
    NULL,                       // 부모 윈도우
    NULL,                       // 메뉴 핸들
    hInstance,                  // 응용 프로그램 인스턴스 핸들
    NULL                        // 추가적인 매개변수);
    */
    // 윈도우를 생성하고 화면에 보이게 한다.
    hwnd = CreateWindow("Nick", "Nick", WS_OVERLAPPEDWINDOW, 400, 200, 640, 480, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    // 메시지 큐에서 메시지를 하나씩 꺼내서 처리한다. // 무한루프
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// UINT : 메세지 종류    WPARM, LPARM : 메세지 상세값
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    const char* str1 = "2019E8038";
    const char* str2 = "유건";

    // 발생한 메시지의 종류에 따라 적절히 처리한다.
    // WM_CREATE, WM_DESTORY : 시작과 끝 
    switch (message) {
    case WM_CREATE:
        return 0;

    case WM_LBUTTONDOWN:
        MessageBox(hwnd, "마우스를 클릭했습니다.", "마우스 메시지", MB_OK);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 200, 100, str1, lstrlen(str1));
        TextOut(hdc, 200, 120, str2, lstrlen(str2));
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // 응용 프로그램이 처리하지 않은 메시지는 운영체제가 처리한다.
    return DefWindowProc(hwnd, message, wParam, lParam);
}

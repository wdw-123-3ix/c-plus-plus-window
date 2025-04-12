#include <windows.h>

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 设置背景颜色为白色
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        // 设置文本颜色为黑色
        SetTextColor(hdc, RGB(0, 0, 0));

        // 获取窗口大小
        RECT rect;
        GetClientRect(hwnd, &rect);

        // 计算文本的位置以使其居中
        int textWidth = 8 * 12; // 假设每个字符宽度为 8，"Hello, world!" 长度为 12
        int textHeight = 16;    // 假设文本高度为 16
        int x = (rect.right - rect.left - textWidth) / 2;
        int y = (rect.bottom - rect.top - textHeight) / 2;

        // 输出文本
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, x, y, "Hello, world!", 13);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    // 注册窗口类
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"HelloWorldClass";
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow(wc.lpszClassName, L"Hello, World!", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

    // 显示窗口
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

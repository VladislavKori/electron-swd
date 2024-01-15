// hello.cc
#include <node_api.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void PrintErrorMessage(DWORD dwErr)
{
  setlocale(LC_ALL, "Russian");
  LPVOID lpMsgBuf;

  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
          FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      dwErr,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR)&lpMsgBuf,
      0, NULL);

  printf("Error code: %d\n", dwErr);
  printf("Error message: %s\n", (char *)lpMsgBuf);

  LocalFree(lpMsgBuf);
}

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_WINDOWPOSCHANGING:
    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    break;
  case WM_WINDOWPOSCHANGED:
    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    break;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

napi_value InitListener(napi_env env, napi_callback_info info)
{
  bool status = true;
  size_t argc = 1;
  napi_value argv[1];
  napi_value result;
  char16_t buffer[100];
  size_t value;

  // [START] convert "info" from napi_value to HWND structure
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  napi_get_value_string_utf16(env, argv[0], buffer, sizeof(buffer) / sizeof(buffer[0]), &value);

  std::u16string utf16str(buffer, value);
  std::string str(utf16str.begin(), utf16str.end());

  unsigned long num = std::stoul(str, nullptr, 16);
  HWND hwnd = reinterpret_cast<HWND>(num);
  // [END] convert "info" from napi_value to HWND structure

  if (IsWindow(hwnd))
  {
    WNDPROC wndproc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);
    // WNDPROC oldWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC); - for remove listener
    // SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)oldWndProc); - for remove listener
  }
  else
  {
    cout << "HWND not correct, please check that your give there value in hexadezimale тotation."
         << "\n"
         << "You can use this template if you use electron `win.getNativeWindowHandle().readUInt32LE().toString(16)` "
         << endl;
  }

  napi_get_boolean(env, status, &result);
  return result;
}

napi_value setToBottom(napi_env env, napi_callback_info info)
{
  bool status = false;
  size_t argc = 1;
  napi_value argv[1];
  napi_value result;
  char16_t buffer[100];
  size_t value;

  // [START] convert "info" from napi_value to HWND structure
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  napi_get_value_string_utf16(env, argv[0], buffer, sizeof(buffer) / sizeof(buffer[0]), &value);

  std::u16string utf16str(buffer, value);
  std::string str(utf16str.begin(), utf16str.end());

  unsigned long num = std::stoul(str, nullptr, 16);
  HWND hwnd = reinterpret_cast<HWND>(num);
  // [END] convert "info" from napi_value to HWND structure

  status = SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
  if (!status)
  {
    DWORD errorCode = GetLastError();
    PrintErrorMessage(errorCode);
  }

  napi_get_boolean(env, status, &result);
  return result;
}

napi_value init(napi_env env, napi_value exports)
{
  napi_status status;

  napi_value fn;
  napi_value fn2;

  // Function - initListener - function who listen window events and set window position to bottom
  status = napi_create_function(env, nullptr, 0, InitListener, nullptr, &fn);
  if (status != napi_ok)
    return NULL;

  status = napi_set_named_property(env, exports, "initListener", fn);
  if (status != napi_ok)
    return NULL;

  // Function - toBottom - set window to bottom
  status = napi_create_function(env, nullptr, 0, setToBottom, nullptr, &fn2);
  if (status != napi_ok)
    return NULL;

  status = napi_set_named_property(env, exports, "toBottom", fn2);
  if (status != napi_ok)
    return NULL;

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
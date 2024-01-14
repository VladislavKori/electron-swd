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

napi_value MyFunc(napi_env env, napi_callback_info info)
{
  size_t argc = 1;
  napi_value argv[1];
  bool ok = true;
  napi_value result;

  char16_t buffer[100];
  size_t value;

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  napi_get_value_string_utf16(env, argv[0], buffer, sizeof(buffer) / sizeof(buffer[0]), &value);

  std::u16string utf16str(buffer, value);
  std::string str(utf16str.begin(), utf16str.end());

  cout << str << endl;
  unsigned long num = std::stoul(str, nullptr, 16);
  HWND hwnd = reinterpret_cast<HWND>(num);

  DWORD hel = SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
  if (hel == 0)

  {
    ok = false;
    DWORD errorCode = GetLastError();
    PrintErrorMessage(errorCode);
  }
  else
  {
    ok = true;
  }
  napi_get_boolean(env, ok, &result);
  return result;
}

napi_value init(napi_env env, napi_value exports)
{
  napi_status status;

  napi_value fn;

  status = napi_create_function(env, nullptr, 0, MyFunc, nullptr, &fn);
  if (status != napi_ok)
    return NULL;

  status = napi_set_named_property(env, exports, "sayHello", fn);
  if (status != napi_ok)
    return NULL;

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
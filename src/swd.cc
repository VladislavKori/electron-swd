// hello.cc
#include <node_api.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

void PrintErrorMessage(DWORD dwErr)
{
  setlocale(LC_ALL, "English");
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

napi_value setToBottom(napi_env env, napi_callback_info info)
{
  napi_status funcStatus;
  size_t argc = 1;
  napi_value argv[1];

  funcStatus = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (funcStatus != napi_ok)
  {
    cout << "Error in napi_get_cb_info" << endl;
    return nullptr;
  };

  uint64_t hwndBigInt;
  bool lossless;
  funcStatus = napi_get_value_bigint_uint64(env, argv[0], &hwndBigInt, &lossless);
  if (funcStatus != napi_ok)
  {
    cout << "Error in napi_get_value_bigint_uint64" << endl;
    return nullptr;
  };

  // Cast the bigint to a HWND
  HWND hwnd = reinterpret_cast<HWND>(reinterpret_cast<void *>(_byteswap_uint64(hwndBigInt)));

  bool isWindow = IsWindow(hwnd);
  if (!isWindow)
  {
    cout << "window not found" << endl;
  }

  boolean status;
  status = SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
  if (!status)
  {
    DWORD errorCode = GetLastError();
    PrintErrorMessage(errorCode);
  }

  return nullptr;
}

napi_value init(napi_env env, napi_value exports)
{
  napi_status status;

  napi_value fn1;

  // Function - toBottom - set window to bottom
  status = napi_create_function(env, nullptr, 0, setToBottom, nullptr, &fn1);
  if (status != napi_ok)
    return NULL;

  status = napi_set_named_property(env, exports, "toBottom", fn1);
  if (status != napi_ok)
    return NULL;

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
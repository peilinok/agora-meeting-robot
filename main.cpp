#include <Windows.h>

#include <iostream>

#include "ini.h"
#include "rtc_robot.h"

const wchar_t* KEY_SECTION = L"Robot";
const wchar_t* KEY_RID = L"rid";
const wchar_t* KEY_PREFIX = L"prefix";
const wchar_t* KEY_ELAPSED = L"elapsed";
const wchar_t* KEY_SOURCE = L"source";
const wchar_t* KEY_APPID = L"appid";
const wchar_t* KEY_AUDIO = L"audio";

int main() {
  const std::wstring ini_file(L".\\robot.ini");

  std::wstring appid =
      WinIni::Read(ini_file, KEY_SECTION, KEY_APPID, std::wstring(L""));
  std::wstring rid =
      WinIni::Read(ini_file, KEY_SECTION, KEY_RID, std::wstring(L"ROBOT"));
  std::wstring prefix =
      WinIni::Read(ini_file, KEY_SECTION, KEY_PREFIX, std::wstring(L"robot"));
  std::wstring source = WinIni::Read(ini_file, KEY_SECTION, KEY_SOURCE,
                                     std::wstring(L".\\test.mp4"));
  bool pub_audio = WinIni::Read(ini_file, KEY_SECTION, KEY_AUDIO, false);

  int elapsed =
      WinIni::Read(ini_file, KEY_SECTION, KEY_ELAPSED, 1000);  // seconds

  if (appid.empty()) {
    std::wcout << L"invalid appid" << std::endl;
    system("pause");
    return 0;
  }

  std::wcout << L"initialize robot with" << L" rid:" << rid << L" prefix:"
             << prefix << L" elapsed:" << elapsed << L" source:" << source
             << std::endl;

  RtcRobot(appid, rid, prefix, source, pub_audio, elapsed).Run();

  return 0;
}

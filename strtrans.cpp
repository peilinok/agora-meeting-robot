#include "strtrans.h"

#include <Windows.h>

std::wstring strtrans::ascii_unicode(const std::string& str) {
  if (str.empty()) return std::wstring(L"");

  int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);

  wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);

  MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);

  std::wstring ret_str = pUnicode;

  free(pUnicode);

  return ret_str;
}

std::string strtrans::unicode_ascii(const std::wstring& wstr) {
  if (wstr.empty()) return std::string("");

  int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0,
                                     nullptr, nullptr);
  char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
  WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr,
                      nullptr);
  std::string ret_str = pAssii;
  free(pAssii);
  return ret_str;
}

std::string strtrans::ascii_utf8(const std::string& str) {
  return unicode_utf8(ascii_unicode(str));
}

std::string strtrans::utf8_ascii(const std::string& utf8) {
  return unicode_ascii(utf8_unicode(utf8));
}

std::string strtrans::unicode_utf8(const std::wstring& wstr) {
  if (wstr.empty()) return std::string("");

  int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0,
                                     nullptr, nullptr);
  char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
  WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr,
                      nullptr);
  std::string ret_str = pAssii;
  free(pAssii);
  return ret_str;
}

std::wstring strtrans::utf8_unicode(const std::string& utf8) {
  if (utf8.empty()) return std::wstring(L"");

  int unicodeLen =
      MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
  wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
  MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, pUnicode, unicodeLen);
  std::wstring ret_str = pUnicode;
  free(pUnicode);
  return ret_str;
}

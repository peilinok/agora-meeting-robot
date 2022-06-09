#include "ini.h"

#include <Windows.h>

#include <sstream>

bool WinIni::Read(const std::wstring& file, const std::wstring& section,
                  const std::wstring& key, const std::wstring& default_value,
                  std::wstring& value) {
  bool ret = false;

  do {
    TCHAR buff[MAX_PATH] = {0};

    if (!GetPrivateProfileString(section.c_str(), key.c_str(),
                                 default_value.c_str(), buff, MAX_PATH,
                                 file.c_str()))
      break;

    value = buff;

    ret = true;
  } while (0);

  return ret;
}

std::wstring WinIni::Read(const std::wstring& file, const std::wstring& section,
                          const std::wstring& key,
                          const std::wstring& default_value) {
  std::wstring value = TEXT("");
  Read(file, section, key, default_value, value);

  return value;
}

int WinIni::Read(const std::wstring& file, const std::wstring& section,
                 const std::wstring& key, const int default_value) {
  return GetPrivateProfileInt(section.c_str(), key.c_str(), default_value,
                              file.c_str());
}

unsigned int WinIni::Read(const std::wstring& file, const std::wstring& section,
                          const std::wstring& key,
                          const unsigned int default_value) {
  return GetPrivateProfileInt(section.c_str(), key.c_str(), default_value,
                              file.c_str());
}

bool WinIni::Read(const std::wstring& file, const std::wstring& section,
                  const std::wstring& key, const bool default_value) {
  int ret = Read(file, section, key, static_cast<int>(default_value));

  return ret == 1;
}

bool WinIni::Write(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const std::wstring& value) {
  return WritePrivateProfileString(section.c_str(), key.c_str(), value.c_str(),
                                   file.c_str());
}

bool WinIni::Write(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const int value) {
  std::wstringstream ass;
  ass << value;

  return Write(file, section, key, ass.str());
}

bool WinIni::Write(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const unsigned int value) {
  std::wstringstream ass;
  ass << value;

  return Write(file, section, key, ass.str());
}

bool WinIni::Write(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const bool value) {
  return Write(file, section, key, static_cast<int>(value));
}

bool WinIni::DeleteSection(const std::wstring& file,
                           const std::wstring& section) {
  return WritePrivateProfileString(section.c_str(), NULL, NULL, file.c_str());
}

bool WinIni::DeleteKey(const std::wstring& file, const std::wstring& section,
                       const std::wstring& key) {
  return WritePrivateProfileString(section.c_str(), key.c_str(), NULL,
                                   file.c_str());
}
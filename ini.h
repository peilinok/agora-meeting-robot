#pragma once

#include <string>

class WinIni {
 public:
  static bool Read(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const std::wstring& default_value,
                   std::wstring& value);

  static std::wstring Read(const std::wstring& file,
                           const std::wstring& section, const std::wstring& key,
                           const std::wstring& default_value);

  static int Read(const std::wstring& file, const std::wstring& section,
                  const std::wstring& key, const int default_value);

  static unsigned int Read(const std::wstring& file,
                           const std::wstring& section, const std::wstring& key,
                           const unsigned int default_value);

  static bool Read(const std::wstring& file, const std::wstring& section,
                   const std::wstring& key, const bool default_value);

  static bool Write(const std::wstring& file, const std::wstring& section,
                    const std::wstring& key, const std::wstring& value);

  static bool Write(const std::wstring& file, const std::wstring& section,
                    const std::wstring& key, const int value);

  static bool Write(const std::wstring& file, const std::wstring& section,
                    const std::wstring& key, const unsigned int value);

  static bool Write(const std::wstring& file, const std::wstring& section,
                    const std::wstring& key, const bool value);

  static bool DeleteSection(const std::wstring& file,
                            const std::wstring& section);

  static bool DeleteKey(const std::wstring& file, const std::wstring& section,
                        const std::wstring& key);
};
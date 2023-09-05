#pragma once
#include <string>
#include <fstream>

// File Logger クラス宣言
class FileLogger
{
private:
    // ログファイルパス
    std::string m_FilePath;
    // ファイル出力ストリーム
    std::ofstream m_Stream;
public: // コンストラクタ
    FileLogger();
    FileLogger(const std::string &file_path);
    ~FileLogger();
    void Open(const std::string &file_path);
    void Close();
    bool IsOpened();
    void Write(const std::string &log);
};
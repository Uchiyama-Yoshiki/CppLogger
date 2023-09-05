#include "FileLogger.h"

// コンストラクタ
FileLogger::FileLogger()
    : m_FilePath(""),
      m_Stream()
{
    // 処理なし
}

/// @brief Constructor
/// @param file_path 
FileLogger::FileLogger(const std::string &file_path)
    : m_FilePath(file_path),
      m_Stream()
{
    /* ファイルオープン */
    this->Open(file_path);
}

// デストラクタ
FileLogger::~FileLogger()
{
    /* ファイルクローズ */
    this->Close();
}
// ファイルオープン
void FileLogger::Open(const std::string &file_path)
{
    this->m_Stream.open(file_path, std::ios::app);
    /* ファイルが開いていなかったら */
    if (this->IsOpened() == false)
    {
    }
}
// ファイルクローズ
void FileLogger::Close()
{
    /* ファイルが開いていたら */
    if (this->IsOpened() == true)
    {
        this->m_Stream.close();
    }
}
// ファイルオープン確認
bool FileLogger::IsOpened()
{
    return this->m_Stream.is_open();
}

// ファイル書き込み
void FileLogger::Write(const std::string &log)
{
    /* ファイルが開いていたら */
    if (this->IsOpened() == true)
    {
        /* ファイルストリームに書き込み */
        this->m_Stream << log << std::endl;
    }
}
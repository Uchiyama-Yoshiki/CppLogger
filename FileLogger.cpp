/**
 * @file FileLogger.cpp
 * @author your name (you@domain.com)
 * @brief  File Logger class implementation.
 * @details This class is a class that outputs logs to a file.
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "FileLogger.h"

FileLogger::FileLogger()
    : m_FilePath(""),
      m_Stream()
{
    // do nothing
}

FileLogger::FileLogger(const std::string &file_path)
    : m_FilePath(file_path),
      m_Stream()
{
    this->Open(file_path);
}

FileLogger::~FileLogger()
{
    this->Close();
}

void FileLogger::Open(const std::string &file_path)
{
    this->m_Stream.open(file_path, std::ios::app);
    if (this->IsOpened() == false)
    {
    }
}

void FileLogger::Close()
{
    if (this->IsOpened() == true)
    {
        this->m_Stream.close();
    }
}

bool FileLogger::IsOpened()
{
    return this->m_Stream.is_open();
}

void FileLogger::Write(const std::string &log)
{
    /* ファイルが開いていたら */
    if (this->IsOpened() == true)
    {
        /* ファイルストリームに書き込み */
        this->m_Stream << log << std::endl;
    }
}
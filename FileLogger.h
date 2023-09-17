/**
 * @file FileLogger.h
 * @author your name (you@domain.com)
 * @brief  File Logger class declaration.
 * @details This class is a class that outputs logs to a file.
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <string>
#include <fstream>

// File Logger クラス宣言
class FileLogger
{
private:
    std::string m_FilePath;
    std::ofstream m_Stream;
public:
    /**
     * @brief Construct a new File Logger object
     * 
     */
    FileLogger();

    /**
     * @brief Construct a new File Logger object
     * 
     * @param file_path 
     */
    FileLogger(const std::string &file_path);

    /**
     * @brief Destroy the File Logger object
     * 
     */
    ~FileLogger();

    /**
     * @brief Open file
     * 
     * @param file_path 
     */
    void Open(const std::string &file_path);

    /**
     * @brief Close file
     * 
     */
    void Close();

    /**
     * @brief Check file is opened
     * 
     * @return true 
     * @return false 
     */
    bool IsOpened();

    /**
     * @brief Write log
     * 
     * @param log 
     */
    void Write(const std::string &log);
};
/**
 * @file Logger.h
 * @author
 * @brief Logger class declaration.
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <windows.h>
#include <cstdio>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include "FileLogger.h"



/**
 * @brief   Logger class
 * @details This class is a class that outputs logs.
 * 
 */
class Logger
{
private:
    FileLogger m_FileLogger;
    std::mutex outputMutex;
    std::mutex stopMutex;

    std::mutex queueMutex;
    std::queue<std::string> messageQue;
    std::condition_variable signal;
    std::thread writeWorker;
    std::atomic<bool> stopFlag;

    /**
     * @brief Get the Instance object
     * @details Get the singlton instance.
     * @return Logger& 
     */
    static Logger &GetInstance();

    /**
     * @brief Construct a new Logger object
     * 
     */
    Logger();
    
    /**
     * @brief Destroy the Logger object
     * 
     */
    ~Logger();

    /**
     * @brief Get the Now Time object
     * @details Get the current time and return it as a string.
     * @return std::string string of current time.
     */
    std::string Logger::GetNowTime();
    
    /**
     * @brief Opuput information log
     * @details Output a message to the log file.
     * @param message  output a message.
     */
    void LogInfo(const std::string &message);

    /**
     * @brief Opuput warning log
     * @details Output a message to the log file.
     * @param message output a message.
     */
    void LogWarn(const std::string &message);
    
    /**
     * @brief Opuput error log
     * @details Output a message to the log file.
     * @param message output a message.
     */
    void LogError(const std::string &message);
    
    /**
     * @brief Pop a message from the queue.
     * 
     * @param msg message
     * @return true 
     * @return false 
     */
    bool Logger::PopMsgQueue(std::string& msg);

    /**
     * @brief Push a message to the queue.
     * 
     * @param msg message
     */
    void Logger::PushMsgQueue(const std::string& msg);
    
    /**
     * @brief Start the write worker.
     * @details Start the write worker thread.
     */
    void Logger::StartWriteWorker();

    /**
     * @brief Stop the write worker.
     * @details Stop the write worker thread.
     */
    void Logger::StopWriteWorker();

    /**
     * @brief Write worker
     * @details Write worker thread.
     */
    void Logger::WriteWorker();
    
    /**
     * @brief Output a message to the log file.
     * @details Output a message to the log file.
     * if the write worker thread is running, the message is queued.
     * @param message log message
     */
    void Logger::Output(const std::string &message);
    
    /**
     * @brief Format a string.
     * @details Format a string.
     * @tparam Args 
     * @param fmt  format string
     * @param args  arguments
     * @return std::string  formatted string
     */
    template <typename... Args>
    static std::string StringFormat(const std::string &fmt, Args... args)
    {
        size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
        std::vector<char> buf(len + 1);
        std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);

        return std::string(&buf[0], &buf[0] + len);
    }

public:
    
    /**
     * @brief Construct a new Logger object
     * @details delete copy constructor
     */
    Logger(const Logger &) = delete;

    /**
     * @brief Construct a new Logger object
     * @details delete move constructor
     */
    Logger(Logger &&) = delete;

    Logger &operators(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;
    
    /**
     * @brief Start the logger.
     * 
     */
    static void Logger::Start()
    {
        Logger::GetInstance().StartWriteWorker();
    };
    
    /**
     * @brief Stop the logger.
     * 
     */
    static void Logger::Stop()
    {
        Logger::GetInstance().StopWriteWorker();
    };

    /**
     * @brief Output a message to the log file.
     * @details Output a informaion message to the log file.
     * @tparam Args 
     * @param format 
     * @param args 
     */
    template <typename... Args>
    static void Info(const std::string &format, Args &&...args)
    {
        Logger::GetInstance().LogInfo(StringFormat(format, args...));
    }

    /**
     * @brief Output a message to the log file.
     * @details Oputput a warning message to the log file.
     * @tparam Arge 
     * @param format 
     * @param args 
     */
    template <typename... Arge>
    static void Warn(const std::string &format, Arge &&...args)
    {
        // 書式フォーマットしてシングルトンインスタンスのWarning呼び出し
        Logger::Get Instance().LogWarn(StringFormat(format, args...));
    }

    /**
     * @brief  Output a message to the log file.
     * @details Output a error message to the log file.
     * @tparam Args 
     * @param format 
     * @param args 
     */
    template <typename... Args>
    static void Error(const std::string &format, Args &&...args)
    {
        Logger::GetInstance().LogError(StringFormat(format, args...));
    }

};
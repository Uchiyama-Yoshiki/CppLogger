/**
 * @file Logger.cpp
 * @author your name (you@domain.com)
 * @brief  Logger class implementation.
 * @version 0.1
 * @date 2023-09-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Logger.h"

Logger &Logger::GetInstance()
{
    static Logger Instance;
    return Instance;
}

Logger::Logger()
    : m_FileLogger(),
      stopFlag(false)
{
    this->m_FileLogger.Open("log.txt");
}

Logger::~Logger()
{
    this->m_FileLogger.Close();
    StopWriteWorker();
}

void Logger::WriteWorker()
{
    std::string log_message;

    while (true)
    {
        if (this->PopMsgQueue(log_message))
        {
            this->m_FileLogger.Write(log_message);
        }
        else
        {
            break;
        }
    }
}

void Logger::StartWriteWorker()
{
    this->writeWorker = std::thread(&Logger::WriteWorker, this);
}

void Logger::StopWriteWorker()
{
    {
        std::lock_guard<std::mutex> lock(stopMutex);
        this->stopFlag.store(true);
        this->signal.notify_one();
    }

    if (writeWorker.joinable())
    {
        writeWorker.join();
    }
}

void Logger::Output(const std::string &message)
{
    if (this->writeWorker.joinable())
    {
        this->PushMsgQueue(message);
    }
    else
    {
        this->m_FileLogger.Write(message);
    }
}

void Logger::LogInfo(const std::string &message)
{
    std::lock_guard<std::mutex> lock(this->outputMutex);
    std::string log_message = this->GetNowTime() + ",INFO," + message;
    this->Output(log_message);
}

void Logger::LogWarn(const std::string &message)
{
    std::lock_guard<std::mutex> lock(this->outputMutex);
    std::string log_message = this->GetNowTime() + ",WARN," + message;
    this->Output(log_message);
}

void Logger::LogError(const std::string &message)
{
    std::lock_guard<std::mutex> lock(this->outputMutex);
    std::string log_message = this->GetNowTime() + ",ERROR," + message;
    this->Output(log_message);
}

std::string Logger::GetNowTime()
{
    char time[32];
    SYSTEMTIME stTime;

    GetLocalTime(&stTime);

    // Use "snprintf" with priority given to speed.
    snprintf(time, sizeof(time), "%d/%02d/%02d %02d:%02d:%02d.%03d",
             stTime.wYear, stTime.wMonth, stTime.wDay,
             stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);

    std::string ret = time;

    return ret;
}

void Logger::PushMsgQueue(const std::string &msg)
{
    {
        std::lock_guard<std::mutex> lockQueue(this->queueMutex);
        this->messageQue.push(msg);
    }

    this->signal.notify_one();
}

bool Logger::PopMsgQueue(std::string &msg)
{
    std::unique_lock<std::mutex> lock(this->queueMutex);

    // wait実行 or notify_oneが実行されるまで待機
    // 実行されたらラムダ式を評価する。
    // true(キューが空　もしくは　停止要求があり)なら待機終了
    // false(キューが空ではない　もしくは　停止要求が無し)なら待機継続
    this->signal.wait(lock, [this]()
    { return !this->messageQue.empty() || this->stopFlag.load(); });

    if (this->messageQue.empty()) 
    {
        return false;
    }

    msg = this->messageQue.front();
    this->messageQue.pop();
    
    return true;
}

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <iostream>
#include "FileLogger.h"

class Logger
{
private:
    // ミューテックス
    HANDLE hMutex;
    // File Logger クラスインスタンス
    FileLogger m_FileLogger;

private:
    // シングルトンインスタンス取得
    static Logger &GetInstance();
    // コンストラクタ
    Logger();
    // デストラクタ
    ~Logger();
    std::string InsertTime(std::string &message);
    // Information ログ出力
    void LogInfo(const std::string &message);
    // Warning
    void LogWarn(const std::string &message);
    // Errorログ出力
    void LogError(const std::string &message);

    template <typename... Args>
    static std::string StringFormat(const std::string &fmt, Args... args)
    {
        size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
        std::vector<char> buf(len + 1);
        std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
        return std::string(&buf[0], &buf[0] + len);
    }

public:
    // コピーコンストラクタを削除
    Logger(const Logger &) = delete;
    // ムーブコンストラクタを削除
    Logger(Logger &&) = delete;
    // コピー代入オペレータを削除
    Logger &operators(const Logger &) = delete;
    // ムーブ代入オペレータを削除
    Logger &operator=(Logger &&) = delete;

    // 書式指定 Information ログ
    template <typename... Args>
    static void Info(const std::string &format, Args &&...args)
    {
        // 書式フォーマットシンインスタンスのInformation ログ出力呼び出し
        Logger::GetInstance().LogInfo(StringFormat(format, args...));
    }
    // 書式指定Warning ログ
    template <typename... Arge>
    static void Warn(const std::string &format, Arge &&...args)
    {
        // 書式フォーマットしてシングルトンインスタンスのWarning呼び出し
        Logger::Get Instance().LogWarn(StringFormat(format, args...));
    }
    // 書式指定 Errorログ
    template <typename... Args>
    static void Error(const std::string &format, Args &&...args)
    {
        // 書式フォーマットしてシングルトンインスタンスのErrorログ出力呼び出し
        Logger::GetInstance().LogError(StringFormat(format, args...));
    }
};
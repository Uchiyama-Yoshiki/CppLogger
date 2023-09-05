#include "Logger.h"
/// @brief シングルトンインスタンス取得
/// @retval Logger&
Logger &Logger::GetInstance()
{
    static Logger Instance;
    return Instance;
}

/// @brief コンストラクタ
Logger::Logger()
    : hMutex(),
      m_FileLogger()
{
    hMutex = CreateMutex(NULL, FALSE, NULL);
    /* ログファイルオープン */
    this->m_FileLogger.Open("log.txt");
}
/// @brief デストラクタ
Logger::~Logger()
{

    /* ログファイルクローズ */
    this->m_FileLogger.Close();
}
/// @brief Information
/// @param message 出力文字列
void Logger::LogInfo(const std::string &message)
{

    /* ミューテックスによる排他処理 */
    WaitForSingleObject(this->hMutex, INFINITE);
    /* Information**/
    std::string messageInfo = ",[INFO]," + message;
    std::string log_message = InsertTime(messageInfo);
    /* Information ログを標準出力に出力(シアン) */
    std::cout << log_message << std::endl;
    /* Information ログをファイルに出力 */
    this->m_FileLogger.Write(log_message);
    ReleaseMutex(this->hMutex);
}
///@brief  Warningログ出力
///@param message 出力文字列
void Logger::LogWarn(const std::string &message)
{
    /* ミューテックスによる排他処理 */
    WaitForSingleObject(this->hMutex, INFINITE);

    /* Warning */
    std::string messageInfo = ",[WARN]," + message;
    std::string log_message = InsertTime(messageInfo);
    std::cerr << log_message << std::endl;
    /*Warningログをファイルに出力 */
    this->m_FileLogger.Write(log_message);
    ReleaseMutex(this->hMutex);
}

///@brief Errorログ出力
///@param message 出力文字列
void Logger::LogError(const std::string &message)
{
    /* ミューテックスによる排他処理 */
    WaitForSingleObject(this->hMutex, INFINITE);
    /* Errorログを生成 */
    std::string messageInfo = ", [ERROR]," + message;
    std::string log_message = InsertTime(messageInfo);
    /* Errorログを標準出力に出力(赤色) */
    std::cerr << log_message << std::endl;
    /* Errorログをファイルに出力 */
    this->m_FileLogger.Write(log_message);
    ReleaseMutex(this->hMutex);
}
/// @brief 文字列の先頭に現在時刻を挿入
/// @param message
/// @retval std::string
std::string Logger::InsertTime(std::string &message)
{
    time_t t = time(nullptr);
    struct tm now;
    std::string timeString;
    localtime_s(&now, &t);
    timeString =
        std::to_string(now.tm_year + 1900) + "/" +
        std::to_string(now.tm_mon) + "/" +
        std::to_string(now.tm_mday) +" " +
        std::to_string(now.tm_hour) + ":" +
        std::to_string(now.tm_min) +":"+
        std::to_string(now.tm_sec) +" ";
        return timeString + message;
}

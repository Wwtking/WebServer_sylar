#ifndef __SYLAR_UTIL_H
#define __SYLAR_UTIL_H

#include <stdint.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>
#include "hash_util.h"
#include "json_util.h"

namespace sylar {

//返回当前线程的ID
pid_t getThreadId();     // pid_t用于定义进程ID，本质上为int

//返回当前协程的ID
uint32_t getFiberId();

/**
 * @brief 获取当前的调用栈
 * @param[out] bt 保存调用栈
 * @param[in] size 最多返回层数
 * @param[in] skip 跳过栈顶的层数
*/
void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);

/**
 * @brief 获取当前栈信息的字符串
 * @param[in] size 栈的最大层数
 * @param[in] skip 跳过栈顶的层数
 * @param[in] prefix 栈信息前输出的内容
*/
std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");

//获取当前时间的毫秒
uint64_t GetCurrentMS();

//获取当前时间的微秒
uint64_t GetCurrentUS();

// 将字符串name转换为大写字母
std::string ToUpper(const std::string& name);

// 将字符串name转换为小写字母
std::string ToLower(const std::string& name);

// 将时间戳形式的time按format格式转化成可读性字符串time
std::string TimeToStr(time_t time = time(0), const std::string& format = "%Y-%m-%d %H:%M:%S");

// 将format格式的字符串形式time转化成时间戳形式的time
time_t StrToTime(const char* str, const char* format = "%Y-%m-%d %H:%M:%S");

/**
 * @brief 根据key值找Map数据类型中的value值
 * @param[in] m 要查找的Map数据类型容器
 * @param[in] key 要查找的key值
 * @param[in] defValue 默认value值
 * @return 返回value值，找不到返回默认值
*/
template<class Map, class Key, class Value>
Value GetParamValue(const Map& m, const Key& key, const Value& defValue = Value()) {
    auto it = m.find(key);
    if(it == m.end()) {
        return defValue;
    }
    try {
        return boost::lexical_cast<Value>(it->second);
    }
    catch(...) {
    }
    return defValue;
}

/**
 * @brief 根据key值找Map数据类型中的value值
 * @param[in] m 要查找的Map数据类型容器
 * @param[in] key 要查找的key值
 * @param[out] Value 存放找到后的value值
 * @return 返回是否找到
*/
template<class Map, class Key, class Value>
bool CheckGetParamValue(const Map& m, const Key& key, Value& Val) {
    auto it = m.find(key);
    if(it == m.end()) {
        return false;
    }
    try {
        Val = boost::lexical_cast<Value>(it->second);
        return true;
    }
    catch(...) {
    }
    return false;
}

class FilesUtil {
public:
    /**
     * @brief 存储指定路径下指定后缀名的所有文件
     * @param[out] files 存放符合条件的文件名(绝对路径)
     * @param[in] path 指定路径
     * @param[in] subfix 指定文件后缀名
    */
    static void ListAllFiles(std::vector<std::string>& files
                            , const std::string& path
                            , const std::string& subfix = "");

    /**
     * @brief 验证pidfile文件是否存在，并且文件中是否存在正在运行的进程ID
     * @param[in] pidfile 文件路径
     * @return 返回进程ID是否正在运行
    */
    static bool IsRunningPidfile(const std::string& pidfile);
    
    /**
     * @brief 创建目录
     * @param[in] pidfile 目录
     * @return 是否创建成功
    */
    static bool Mkdir(const std::string& dirname);

    /**
     * @brief 提取路径名
     * @param[in] pidfile 文件路径
     * @example /home/wwt/sylar --> /home/wwt
    */
    static std::string Dirname(const std::string& filename);

    /**
     * @brief 提取文件名
     * @param[in] pidfile 文件路径
     * @example /home/wwt/sylar --> sylar
    */
    static std::string Basename(const std::string& filename);
};

/**
 * @brief 类型转换封装
*/
class TypeUtil {
public:
    // string[0] --> ASCII
    static int8_t ToChar(const std::string& str);

    // string --> int64_t
    static int64_t Atoi(const std::string& str);

    // string --> double
    static double Atof(const std::string& str);

    // char[0] --> ASCII
    static int8_t ToChar(const char* str);

    // char* --> int64_t
    static int64_t Atoi(const char* str);
    
    // char* --> double
    static double Atof(const char* str);
};

/**
 * @brief 字符串封装
*/
class StringUtil {
public:
    /**
     * @brief URL编码(百分号编码)/解码
     * @details 将字符按指定编码方式(UTF-8编码)转化为字节流，
     *          每个字节按16进制表示，并添加%组成一个percent编码
     * @example 例如：汉字“你好”
     *          UTF-8字节流打印为：-28 -67 -96 -27 -91 -67
     *          对应的16进制表示为：E4 BD A0 E5 A5 BD
     *          URLEncode编译后为：%E4%BD%A0%E5%A5%BD
    */
    static std::string UrlEncode(const std::string& str, bool space_as_plus = true);
    static std::string UrlDecode(const std::string& str, bool space_as_plus = true);

    /**
     * @brief 去除字符串 str 两端/左端/右端指定的字符 delimit
     * @details 找 str 左端第一个不属于 delimit 字符集合的位置
     *          找 str 右端最后一个不属于 delimit 字符集合的位置
    */
    static std::string Trim(const std::string& str, const std::string& delimit = " \t\r\n");
    static std::string TrimLeft(const std::string& str, const std::string& delimit = " \t\r\n");
    static std::string TrimRight(const std::string& str, const std::string& delimit = " \t\r\n");

    static std::string WStringToString(const std::wstring& ws);
    static std::wstring StringToWString(const std::string& s);
};

} // namespace sylar


#endif
#ifndef __SYLAR_HTTP_SESSION_DATA_H__
#define __SYLAR_HTTP_SESSION_DATA_H__

#include "thread.h"
#include "singleton.h"
#include <unordered_map>
#include <boost/any.hpp>


namespace sylar{
namespace http{


/**
 * @brief Session数据封装，实现保存用户登录状态功能
 * @details 服务端需要记录各个用户的状态，需要用Session机制来识具体的用户
 *   服务端为特定的用户创建了特定的Session，用于标识这个用户，并且跟踪用户
 * @note 服务端如何识别特定的用户？
 *   每次 HTTP 请求的时候，客户端都会发送相应的 Cookie 信息到服务端，
 *   其中在 Cookie 里面记录一个 Session ID 就可以让服务器识别到用户
*/
class SessionData {
public:
    typedef std::shared_ptr<SessionData> ptr;
    typedef RWMutex MutexType;

    /**
     * @brief 构造函数
     * @param[in] auto_gen 是否自动生成，如果为true，则随机生成Session ID
    */
    SessionData(bool auto_gen);

    /**
     * @brief 存放session数据
    */
    template<class T>
    void setData(const std::string& key, const T& value) {
        MutexType::WriteLock lock(m_mutex);
        m_datas[key] = value;
    }

    /**
     * @brief 获取session数据
    */
    template<class T>
    T getData(const std::string& key, const T& def = T()) {
        MutexType::ReadLock lock(m_mutex);
        auto it = m_datas.find(key);
        if(it == m_datas.end()) {
            return def;
        }
        // boost::any定义的变量可以存放任意类型的数据
        boost::any v = it->second;
        lock.unlock();
        try {
            // 取出any对象中存放的数据
            return boost::any_cast<T>(v);
        }
        catch(...) {
        }
        return def;
    }

    /**
     * @brief 删除session数据
    */
    void del(const std::string& key);

    /**
     * @brief 是否存在key键对应的数据
    */
    bool has(const std::string& key);

    uint64_t getLastAccessTime() const { return m_lastAccessTime; }
    void setLastAccessTime(uint64_t v) { m_lastAccessTime = v; }

    const std::string& getId() const { return m_id; }
    void setId(const std::string& val) { m_id = val; }

private:
    /// 读写锁
    MutexType m_mutex;
    /// session数据 (boost::any是一种类型,定义的变量可以存放任意类型数据)
    std::unordered_map<std::string, boost::any> m_datas;
    /// 记录用户最后一次访问网站或与服务器进行交互的时间
    uint64_t m_lastAccessTime;
    /// Session ID
    std::string m_id;
};

/**
 * @brief Session管理封装
*/ 
class SessionDataManager {
public:
    typedef RWMutex MutexType;

    /**
     * @brief 添加Session
    */
    void add(SessionData::ptr info);

    /**
     * @brief 删除Session
    */
    void del(const std::string& id);

    /**
     * @brief 获取Session
    */
    SessionData::ptr get(const std::string& id);

    /**
     * @brief 删除超时ts的Session
    */
    void check(int64_t ts = 3600);

private:
    /// 读写锁
    MutexType m_mutex;
    /// Session ID --> SessionData
    std::unordered_map<std::string, SessionData::ptr> m_datas;
};

typedef sylar::Singleton<SessionDataManager> SessionDataMgr;


} // namespace http  
} // namespace sylar


#endif
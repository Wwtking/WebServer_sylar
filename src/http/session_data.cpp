#include "session_data.h"
#include "util.h"

namespace sylar {
namespace http {

// 构造函数
SessionData::SessionData(bool auto_gen)
    :m_lastAccessTime(time(0)) {
    // 随机生成Session ID
    if(auto_gen) {
        std::stringstream ss;
        ss << sylar::GetCurrentUS() << "|" << rand() << "|" << rand() << "|" << rand();
        m_id = sylar::md5(ss.str());
    }
}

// 删除session数据
void SessionData::del(const std::string& key) {
    MutexType::WriteLock lock(m_mutex);
    m_datas.erase(key);
}

// 是否存在key键对应的数据
bool SessionData::has(const std::string& key) {
    MutexType::ReadLock lock(m_mutex);
    auto it = m_datas.find(key);
    return it != m_datas.end();
}


// 添加Session
void SessionDataManager::add(SessionData::ptr info) {
    MutexType::WriteLock lock(m_mutex);
    m_datas[info->getId()] = info;
}

// 删除Session
void SessionDataManager::del(const std::string& id) {
    MutexType::WriteLock lock(m_mutex);
    m_datas.erase(id);
}

// 获取Session
SessionData::ptr SessionDataManager::get(const std::string& id) {
    MutexType::ReadLock lock(m_mutex);
    auto it = m_datas.find(id);
    if(it != m_datas.end()) {
        it->second->setLastAccessTime(time(0));
        return it->second;
    }
    return nullptr;
}

// 删除 最后访问时间到现在超过ts 的Session
void SessionDataManager::check(int64_t ts) {
    uint64_t now = time(0) - ts;
    std::vector<std::string> keys;
    MutexType::ReadLock lock(m_mutex);
    for(auto& i : m_datas) {
        if(i.second->getLastAccessTime() < now) {
            keys.push_back(i.first);
        }
    }
    lock.unlock();
    for(auto& i : keys) {
        del(i);
    }
}


}
}

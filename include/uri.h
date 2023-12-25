#ifndef __SYLAR_URI_H__
#define __SYLAR_URI_H__

#include <iostream>
#include <memory>
#include <string.h>
#include "address.h"

namespace sylar {

/*
     foo://user@sylar.com:8042/over/there?name=ferret#nose
       \_/   \______________/\_________/ \_________/ \__/
        |           |            |            |        |
     scheme     authority       path        query   fragment
*/


class Uri {
public:
    typedef std::shared_ptr<Uri> ptr;

    static Uri::ptr CreateUri(const std::string& uriStr);

    Uri();
    
    const std::string& getScheme() const { return m_scheme; }
    const std::string& getUserinfo() const { return m_userinfo; }
    const std::string& getHost() const { return m_host; }
    const std::string& getPath() const;
    const std::string& getQuery() const { return m_query; }
    const std::string& getFragment() const { return m_fragment; }
    uint32_t getPort() const;

    void setScheme(const std::string& scheme) { m_scheme = scheme; }
    void setUserinfo(const std::string& userinfo) { m_userinfo = userinfo; }
    void setHost(const std::string& host) { m_host = host; }
    void setPath(const std::string& path) { m_path = path; }
    void setQuery(const std::string& query) { m_query = query; }
    void setFragment(const std::string& fragment) { m_fragment = fragment; }
    void setPort(uint32_t port) { m_port = port; }

    std::ostream& dump(std::ostream& os) const;
    std::string toString() const;

    Address::ptr getAddress() const;

private:
    bool isDefaultPort() const;

private:
    std::string m_scheme;       // 表示URI的协议方案，例如"http"或"https"
    std::string m_userinfo;     // 表示URI的用户信息
    std::string m_host;         // 表示URI的主机名或IP地址
    std::string m_path;         // 表示URI的资源路径
    std::string m_query;        // 表示URI的查询部分
    std::string m_fragment;     // 表示URI的片段标识符
    uint32_t m_port;            // 表示URI的端口号
};

}

#endif
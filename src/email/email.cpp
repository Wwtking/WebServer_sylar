#include "email.h"
#include <fstream>
#include <sstream>
#include "util.h"
#include "hash_util.h"

namespace sylar {

// 创建邮件附件
EMailEntity::ptr EMailEntity::CreateAttach(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    std::string buf;
    buf.resize(1024);
    EMailEntity::ptr entity(new EMailEntity);
    // 将 filename 附件内容存到 entity->m_content 中
    while(!ifs.eof()) {
        ifs.read(&buf[0], buf.size());
        entity->m_content.append(buf.c_str(), ifs.gcount());
    }
    // 对附件内容进行base64编码
    entity->m_content = sylar::base64encode(entity->m_content);
    // 标明头部信息
    // 表示用base64编码方式
    entity->addHeader("Content-Transfer-Encoding", "base64");
    // 表明是附件描述方式，指定邮件中的附件的处理方式
    entity->addHeader("Content-Disposition", "attachment");
    // 表明消息体的类型是二进制格式，name=文件名
    entity->addHeader("Content-Type", "application/octet-stream;name=" + sylar::FilesUtil::Basename(filename));
    return entity;

    /** 传递普通文本，不需要加密
    std::ifstream ifs(filename);
    std::string buf;
    buf.resize(1024);
    EMailEntity::ptr entity(new EMailEntity);
    while(!ifs.eof()) {
        ifs.read(&buf[0], buf.size());
        entity->m_content.append(buf.c_str(), ifs.gcount());
    }
    entity->addHeader("Content-Disposition", "attachment");
    entity->addHeader("Content-Type", "application/octet-stream;name=" + sylar::FilesUtil::Basename(filename));
    // Content-Type类型可以为如下：
    //     text/plain：纯文本文件
    //     text/html：HTML 文件
    //     image/jpeg：JPEG 图像文件
    //     image/png：PNG 图像文件
    //     application/pdf：PDF 文件
    //     application/msword：Word 文档文件
    //     application/vnd.ms-excel：Excel 表格文件
    //     application/zip：ZIP 压缩文件
    return entity;
    */
}

// 添加头部信息
void EMailEntity::addHeader(const std::string& key, const std::string& val) {
    m_headers[key] = val;
}

// 获取头部信息
std::string EMailEntity::getHeader(const std::string& key, const std::string& def) {
    auto it = m_headers.find(key);
    return it == m_headers.end() ? def : it->second;
}

// 字符串形式输出
std::string EMailEntity::toString() const {
    std::stringstream ss;
    for(auto& i : m_headers) {
        ss << i.first << ": " << i.second << "\r\n";
    }
    ss << m_content << "\r\n";
    return ss.str();
}

// 创建邮件
EMail::ptr EMail::Create(const std::string& from_address, const std::string& from_passwd
                         ,const std::string& title, const std::string& body
                         ,const std::vector<std::string>& to_address
                         ,const std::vector<std::string>& cc_address
                         ,const std::vector<std::string>& bcc_address) {
    EMail::ptr email(new EMail);
    email->setFromEMailAddress(from_address);
    email->setFromEMailPasswd(from_passwd);
    email->setTitle(title);
    email->setBody(body);
    email->setToEMailAddress(to_address);
    email->setCcEMailAddress(cc_address);
    email->setBccEMailAddress(bcc_address);
    return email;
}

// 添加附件
void EMail::addEntity(EMailEntity::ptr entity) {
    m_entitys.push_back(entity);
}

}

#pragma once
#include <string>
#include <vector>
#include <utility>
#include <curl/curl.h>
#include <iostream>
#include <sstream>

#include "../../../../HttpServer/include/utils/JsonUtil.h"
#include"../../../../HttpServer/include/utils/MysqlUtil.h"


//��߷�װcurlȥ���ʶ԰����ģ��

class AIHelper {
public:
    // ���캯������ʼ��API Key
    AIHelper(const std::string& apiKey);

    // ����Ĭ��ģ��
    void setModel(const std::string& modelName);

    // ���һ����Ϣ
    void addMessage(int userId, const std::string& userName, bool is_user, const std::string& userInput);
    // �ָ�һ����Ϣ
    void restoreMessage(const std::string& userInput, long long ms);

    // ����������Ϣ������AI����Ӧ����
    // messages: [{"role":"system","content":"..."}, {"role":"user","content":"..."}]
    std::string chat(int userId, std::string userName);

    // ��ѡ�������Զ���������
    json request(const json& payload);

    std::vector<std::pair<std::string, long long>> GetMessages();

private:
    //���뵽mysql�Ľӿڣ��ṩ���뵽�̳߳صĽӿڣ��̳߳����첽mysql���²�����
    //todo: 
    void pushMessageToMysql(int userId, const std::string& userName, bool is_user, const std::string& userInput, long long ms);

    // �ڲ�������ִ��curl���󣬷���ԭʼJSON
    json executeCurl(const json& payload);
    // curl �ص��������ѷ��ص�����д�� string buffer
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

private:
    std::string apiKey_;
    //Ĭ����ͨ��ǧ��
    std::string model_ = "qwen-plus";
    //��Ӧ��ַ
    std::string apiUrl_ = "https://dashscope.aliyuncs.com/compatible-mode/v1/chat/completions";

    //һ���û����һ��AIHelper��messages����û�����ʷ�Ի�
    //ż���±�����û�����Ϣ�������±���ai���ص�����
    //���ߴ���ʱ���
    std::vector<std::pair<std::string, long long>> messages;

    //http::MysqlUtil mysqlUtil_;
};

#include"../include/AIUtil/AIHelper.h"
#include"../include/AIUtil/MQManager.h"
#include <stdexcept>
#include<chrono>

// ���캯��
AIHelper::AIHelper(const std::string& apiKey)
    : apiKey_(apiKey) {
}

// ����Ĭ��ģ��
void AIHelper::setModel(const std::string& modelName) {
    model_ = modelName;
}

// ���һ���û���Ϣ
void AIHelper::addMessage(int userId,const std::string& userName, bool is_user,const std::string& userInput ) {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    messages.push_back({ userInput,ms });
    //��Ϣ�����첽���
    pushMessageToMysql(userId, userName, is_user, userInput,ms);
}

void AIHelper::restoreMessage(const std::string& userInput,long long ms) {
    messages.push_back({ userInput,ms });
}


// ����������Ϣ
std::string AIHelper::chat(int userId,std::string userName) {
    // ���� payload
    json payload;
    payload["model"] = model_;
    json msgArray = json::array();

    for (size_t i = 0; i < messages.size(); ++i) {
        json msg;
        if (i % 2 == 0) { // ż���±꣺�û�
            msg["role"] = "user";
            msg["content"] = messages[i].first;
        }
        else { // �����±꣺AI
            msg["role"] = "assistant";
            msg["content"] = messages[i].first;
        }
        msgArray.push_back(msg);
    }

    payload["messages"] = msgArray;

    // ��ӡ payload������ 4 ���ո�
    std::cout << "[DEBUG] payload = " << payload.dump(4) << std::endl;

    // ִ������
    json response = executeCurl(payload);

    if (response.contains("choices") && !response["choices"].empty()) {
        std::string answer = response["choices"][0]["message"]["content"];
        // ���� AI �ظ�
        addMessage(userId,userName, false,answer);
        return answer;
    }

    return "[Error] �޷�������Ӧ";
}

// �����Զ���������
json AIHelper::request(const json& payload) {
    return executeCurl(payload);
}

std::vector<std::pair<std::string, long long>> AIHelper::GetMessages() {
    return this->messages;
}


// �ڲ�������ִ�� curl ����
json AIHelper::executeCurl(const json& payload) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize curl");
    }

    std::string readBuffer;
    struct curl_slist* headers = nullptr;
    std::string authHeader = "Authorization: Bearer " + apiKey_;

    headers = curl_slist_append(headers, authHeader.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    std::string payloadStr = payload.dump();
    std::cout << "test json->payloadStr " << payloadStr << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, apiUrl_.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }

    try {
        return json::parse(readBuffer);
    }
    catch (...) {
        throw std::runtime_error("Failed to parse JSON response: " + readBuffer);
    }
}

// curl �ص��������ѷ��ص�����д�� string buffer
size_t AIHelper::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* buffer = static_cast<std::string*>(userp);
    buffer->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void AIHelper::pushMessageToMysql(int userId, const std::string& userName, bool is_user, const std::string& userInput,long long ms) {
    std::string sql = "INSERT INTO chat_message (id, username, is_user, content, ts) VALUES ("
        + std::to_string(userId) + ", "  // ������ userId ��Ϊ id���������Լ�����
        + "'" + userName + "', "
        + std::to_string(is_user ? 1 : 0) + ", "
        + "'" + userInput + "', "
        + std::to_string(ms) + ")";
    //�ĳ���Ϣ�����첽ִ��mysql������������������������߼�
    //mysqlUtil_.executeUpdate(sql);

    MQManager::instance().publish("sql_queue", sql);
}

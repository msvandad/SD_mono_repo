#include "billboard.h"

std::mutex Billboard::mtx;

void Billboard::subscribe(MessageID messageID, MessageCallback callback) {
    std::lock_guard<std::mutex> lock(mtx);
    subscribers[messageID].push_back(callback);
}

void Billboard::unsubscribe(MessageID messageID, MessageCallback callback) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& callbacks = subscribers[messageID];
    callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), callback), callbacks.end());
}

void Billboard::publish(MessageID messageID, const std::vector<uint8_t>& data) {
    std::lock_guard<std::mutex> lock(mtx);
    if (subscribers.find(messageID) != subscribers.end()) {
        Message message{messageID, std::chrono::system_clock::now(), data};
        for (const auto& callback : subscribers[messageID]) {
            callback(message);
        }
    }
}

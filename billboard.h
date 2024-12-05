#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <chrono>
#include <algorithm> // For std::remove

class Billboard {
public:
    enum class MessageID {
        TELEMETRY,
        AHRS,
        CONTROLS,
        HIGH_CURRENT
    };

    struct Message {
        MessageID id;
        std::chrono::system_clock::time_point timestamp;
        std::vector<uint8_t> data;
    };

    using MessageCallback = std::function<void(const Message&)>;

    // Subscribe to a message type
    void subscribe(MessageID messageID, MessageCallback callback);

    // Unsubscribe from a message type
    void unsubscribe(MessageID messageID, MessageCallback callback);

    // Publish a message
    void publish(MessageID messageID, const std::vector<uint8_t>& data);

private:
    std::unordered_map<MessageID, std::vector<MessageCallback>> subscribers;
    std::mutex mtx; // Mutex for thread-safe operations
};

#endif // BILLBOARD_H

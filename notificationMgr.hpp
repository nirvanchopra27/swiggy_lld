#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <algorithm> // for std::find_if

#include "common.hpp"
#include "inotificationSender.hpp"

// This class corresponds to the subject in the Observer design pattern
// INotificationSender is the observer interface

class NotificationMgr {
private:
    NotificationMgr() = default;

    static NotificationMgr* notificationMgrInstance;
    static std::mutex mtx;

    std::unordered_map<std::string, std::vector<std::pair<std::string, INotificationSender*>>> notificationSendersMap;

public:
    // Get the singleton instance
    static NotificationMgr* getNotificationMgr();

    // Register observer
    void addNotificationSender(const std::string& pOrderId, const std::string& pUserId, INotificationSender* pNotificationSender) {
        auto& vec = notificationSendersMap[pOrderId];

        auto it = std::find_if(vec.begin(), vec.end(),
            [&](const std::pair<std::string, INotificationSender*>& entry) {
                return entry.first == pUserId && entry.second == pNotificationSender;
            });

        if (it == vec.end()) {
            vec.emplace_back(pUserId, pNotificationSender);
        }
    }

    // Unregister observer
    void removeNotificationSender(const std::string& pOrderId, const std::string& pUserId, INotificationSender* pNotificationSender) {
        auto& vec = notificationSendersMap[pOrderId];

        auto it = std::find_if(vec.begin(), vec.end(),
            [&](const std::pair<std::string, INotificationSender*>& entry) {
                return entry.first == pUserId && entry.second == pNotificationSender;
            });

        if (it != vec.end()) {
            vec.erase(it);
        }
    }

    // Notify all observers for a given order
    void notify(const std::string& pOrderId, const std::string& pMsg) {
        for (const auto& sender : notificationSendersMap[pOrderId]) {
            sender.second->sendNotification(sender.first, pMsg);
        }
    }

    // Notify a particular user via a specific sender
    void notifyParticularUser(const std::string& pUserId, const std::string& pMsg, INotificationSender* sender) {
        sender->sendNotification(pUserId, pMsg);
    }
};

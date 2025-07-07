#include "notificationMgr.hpp"

NotificationMgr* NotificationMgr::notificationMgrInstance = nullptr;
std::mutex NotificationMgr::mtx;

NotificationMgr* NotificationMgr::getNotificationMgr() {
    if (notificationMgrInstance == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        if (notificationMgrInstance == nullptr) {
            notificationMgrInstance = new NotificationMgr();
        }
    }
    return notificationMgrInstance;
}

#include "EventMgr.h"

void EventMgr::PollEvents()
{
    for (auto& [key, callbacks] : push_subscribers_) {
        DWORD key_state = DINPUT->GetKey(key);
        if (key_state == KGCA41B::KEY_PUSH) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }

    for (auto& [key, callbacks] : free_subscribers_) {
        DWORD key_state = DINPUT->GetKey(key);
        if (key_state == KGCA41B::KEY_FREE) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }

    for (auto& [key, callbacks] : hold_subscribers_) {
        DWORD key_state = DINPUT->GetKey(key);
        if (key_state == KGCA41B::KEY_HOLD) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }

    for (auto& [key, callbacks] : up_subscribers_) {
        DWORD key_state = DINPUT->GetKey(key);
        if (key_state == KGCA41B::KEY_UP) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }
}

void EventMgr::Subscribe(int key, std::function<void()> callback, DWORD key_state)
{
    switch (key_state) {
    case KGCA41B::KEY_PUSH:
        push_subscribers_[key].push_back(callback);
        break;
    case KGCA41B::KEY_FREE:
        free_subscribers_[key].push_back(callback);
        break;
    case KGCA41B::KEY_HOLD:
        hold_subscribers_[key].push_back(callback);
        break;
    case KGCA41B::KEY_UP:
        up_subscribers_[key].push_back(callback);
        break;
    }
}

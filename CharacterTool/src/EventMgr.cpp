#include "EventMgr.h"
#include "Movements.h"

void EventMgr::PollEvents()
{
    for (auto& [key, callbacks] : push_subscribers_) {
        DWORD key_state = DINPUT->GetKeyState(key);
        if (key_state == KGCA41B::KEY_PUSH) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }

    for (auto& [key, callbacks] : free_subscribers_) {
        DWORD key_state = DINPUT->GetKeyState(key);
        if (key_state == KGCA41B::KEY_FREE) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }

    int num_held_keys = 0;
    for (int key = 0;key < 256;key++) {
        DWORD key_state = DINPUT->GetKeyState(key);
        if (key_state == KGCA41B::KEY_HOLD) {
            num_held_keys++;
        }
    }
    for (auto& [keys, callbacks] : combination_hold_subscribers_) {
        bool all_pressed = true;
        for (auto key : keys) {
            DWORD key_state = DINPUT->GetKeyState(key);
            if (key_state != KGCA41B::KEY_HOLD) {
                all_pressed = false;
                break;
            }
            else {
                std::cout << "a";
            }
        }
        
        if (all_pressed && num_held_keys == keys.size()) {
            for (auto callback : callbacks) {
                callback();
            }
        }
    }

    for (auto& [key, callbacks] : up_subscribers_) {
        DWORD key_state = DINPUT->GetKeyState(key);
        if (key_state == KGCA41B::KEY_UP) {
            for (auto& callback : callbacks) {
                callback();
            }
        }
    }
}

void EventMgr::Subscribe(vector<int> key, std::function<void()> callback, DWORD key_state)
{
    switch (key_state) {
    case KGCA41B::KEY_PUSH:
        push_subscribers_[key[0]].push_back(callback);
        break;
    case KGCA41B::KEY_FREE:
        free_subscribers_[key[0]].push_back(callback);
        break;
    case KGCA41B::KEY_HOLD:
        combination_hold_subscribers_[key].push_back(callback);
        break;
    case KGCA41B::KEY_UP:
        up_subscribers_[key[0]].push_back(callback);
        break;
    }
}

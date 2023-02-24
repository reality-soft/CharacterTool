#pragma once
#include "Engine_include.h"
#include <functional>

class EventMgr
{
	SINGLETON(EventMgr)
#define EVENT EventMgr::GetInst()
public:
    void PollEvents();
    void Subscribe(vector<int> key, std::function<void()> callback, DWORD key_state);
private:
    std::unordered_map<int, std::vector<std::function<void()>>> push_subscribers_;
    std::map<vector<int>, std::vector<std::function<void()>>> combination_hold_subscribers_;
    std::unordered_map<int, std::vector<std::function<void()>>> free_subscribers_;
    std::unordered_map<int, std::vector<std::function<void()>>> up_subscribers_;

};


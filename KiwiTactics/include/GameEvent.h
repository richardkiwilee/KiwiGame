#pragma once
#include <functional>
#include <vector>


class EventSystem {
public:
    // 定义一个事件类型，事件是一个 void() 函数
    using EventHandler = std::function<void()>;
    // 向事件列表中添加事件处理器
    void addEventHandler(const EventHandler& handler) {
        eventHandlers.push_back(handler);
    }
    // 移除事件处理器
    void removeEventHandler(const EventHandler& handler) {
        // 使用 std::remove_if 和 erase 来移除匹配的事件处理器
        auto it = std::remove_if(eventHandlers.begin(), eventHandlers.end(),
            [&handler](const EventHandler& storedHandler) {
                return storedHandler.target_type() == handler.target_type() &&
                    *storedHandler.target<void()>() == *handler.target<void()>();
            });

        eventHandlers.erase(it, eventHandlers.end());
    }
    // 触发所有事件处理器
    void triggerEvent() {
        for (auto& handler : eventHandlers) {
            handler();  // 执行事件处理器
        }
    }
private:
    std::vector<EventHandler> eventHandlers;  // 存储事件处理器
};

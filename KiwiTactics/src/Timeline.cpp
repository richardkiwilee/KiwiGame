#include "Timeline.h"
#include <iostream>
#include <thread>
#include <chrono>

void Timeline::add_to_list(bool blocking, int delay_ms) {
    _timeline.push_back({ blocking, delay_ms });
}

void Timeline::AddNode(TimelineNode node) {
    _timeline.push_back(node);
}

std::future<void> Timeline::do_coroutine(TimelineNode ms) {
    return std::async(std::launch::async, [ms]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms.delay_ms));  // 延迟
        std::cout << "Completed: delay " << ms.delay_ms << " ms, blocking: " << ms.is_blocking << "\n";
    });
}

void Timeline::play() {
    for (auto& ms : _timeline) {
        // 如果需要阻塞，等待当前协程执行完毕
        if (ms.is_blocking) {
            auto future = do_coroutine(ms);
            future.get(); // 阻塞直到当前协程完成
        }
        else {
            // 启动非阻塞协程
            do_coroutine(ms);
        }
    }
}

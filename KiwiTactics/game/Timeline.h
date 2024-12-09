#include <list>
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <future>
struct TimelineNode
{
	bool is_blocking;    // 是否阻塞
	int delay_ms;        // 延迟毫秒数
};
class Timeline {
public:
    // 用来存储 mystruct 的列表
    std::list<TimelineNode> _timeline;

    // 添加 mystruct 元素到列表中
    void add_to_list(bool blocking, int delay_ms) {
        _timeline.push_back({ blocking, delay_ms });
    }
    void AddNode(TimelineNode node) {
        _timeline.push_back(node);
    };
    // 执行协程函数
    std::future<void> do_coroutine(TimelineNode ms) {
        return std::async(std::launch::async, [ms]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms.delay_ms));  // 延迟
            std::cout << "Completed: delay " << ms.delay_ms << " ms, blocking: " << ms.is_blocking << "\n";
            });
    }

    // 启动 play 函数，依次执行协程
    void play() {
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
};

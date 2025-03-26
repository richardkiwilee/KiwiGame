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
    void add_to_list(bool blocking, int delay_ms);
    void AddNode(TimelineNode node);
    // 执行协程函数
    std::future<void> do_coroutine(TimelineNode ms);

    // 启动 play 函数，依次执行协程
    void play();
};


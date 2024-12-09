#include <list>
#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <future>
struct TimelineNode
{
	bool is_blocking;    // �Ƿ�����
	int delay_ms;        // �ӳٺ�����
};
class Timeline {
public:
    // �����洢 mystruct ���б�
    std::list<TimelineNode> _timeline;

    // ��� mystruct Ԫ�ص��б���
    void add_to_list(bool blocking, int delay_ms) {
        _timeline.push_back({ blocking, delay_ms });
    }
    void AddNode(TimelineNode node) {
        _timeline.push_back(node);
    };
    // ִ��Э�̺���
    std::future<void> do_coroutine(TimelineNode ms) {
        return std::async(std::launch::async, [ms]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms.delay_ms));  // �ӳ�
            std::cout << "Completed: delay " << ms.delay_ms << " ms, blocking: " << ms.is_blocking << "\n";
            });
    }

    // ���� play ����������ִ��Э��
    void play() {
        for (auto& ms : _timeline) {
            // �����Ҫ�������ȴ���ǰЭ��ִ�����
            if (ms.is_blocking) {
                auto future = do_coroutine(ms);
                future.get(); // ����ֱ����ǰЭ�����
            }
            else {
                // ����������Э��
                do_coroutine(ms);
            }
        }
    }
};

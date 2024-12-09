#include <vector>

struct TimelineNode
{

};

class Timeline
{
public:
	Timeline() {};
	~Timeline() {};
	void AddNode(TimelineNode node) {
		_timeline.push_back(node);
	};
	void Play() {
		for (auto& node : _timeline) {
			// play node
		}
	};
private:
	std::vector<TimelineNode> _timeline;	
};

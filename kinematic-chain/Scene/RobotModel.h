#pragma once
#include <memory>
#include "RobotConfiguration.h"

class RobotModel
{
	RobotConfiguration start;
	RobotConfiguration end;

public:
	RobotModel() : start(RobotConfiguration()), end(RobotConfiguration()) { }
	RobotModel(const RobotConfiguration& _s, const RobotConfiguration& _e) : start(_s), end(_e) { }
	RobotModel(std::shared_ptr<RobotModel> m) : start(m->start), end(m->end) { }
	RobotModel(const RobotModel& m) : start(m.start), end(m.end) { }
	RobotModel& operator=(const RobotModel& m);

	RobotConfiguration& GetStartRef() { return start; }
	RobotConfiguration& GetEndRef() { return end; }

	void SetStartConfiguration(const RobotConfiguration& _s) { start = _s; }
	void SetEndConfiguration(const RobotConfiguration& _e) { end = _e; }
};

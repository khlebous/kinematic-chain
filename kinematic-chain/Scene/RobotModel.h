#pragma once
#include <memory>
#include "RobotConfiguration.h"

class RobotModel
{
	RobotConfiguration start;
	RobotConfiguration end;
	RobotConfiguration current;

public:
	RobotModel() : start(RobotConfiguration()), end(RobotConfiguration()), current(RobotConfiguration()) { }
	RobotModel(const RobotConfiguration& _s, const RobotConfiguration& _e) : start(_s), end(_e), current(_s) { }
	RobotModel(std::shared_ptr<RobotModel> m) : start(m->start), end(m->end), current(m->current) { }
	RobotModel(const RobotModel& m) : start(m.start), end(m.end), current(m.current) { }
	RobotModel& operator=(const RobotModel& m);

	RobotConfiguration& GetStartRef() { return start; }
	RobotConfiguration& GetEndRef() { return end; }
	RobotConfiguration& GetCurrentRef() { return current; }
};

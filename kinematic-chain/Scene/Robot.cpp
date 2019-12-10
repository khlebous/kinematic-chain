#include "Robot.h"

Robot& Robot::operator=(const Robot& o)
{
	model = std::make_shared<RobotModel>(o.model);
	view = std::make_shared<RobotView>(model, o.GetView()->GetShader());

	return *this;
}

void Robot::Render(bool isRunning)
{
	view->Render(isRunning);
	configuration_space->Render(isRunning);
}

void Robot::DoFloodFill()
{
	size_t start_arm1 = (size_t)EulerUtils::GetCorrectedAngle(glm::degrees(model->GetStartRef().GetArm1Angle()));
	size_t start_arm2 = (size_t)EulerUtils::GetCorrectedAngle(glm::degrees(model->GetStartRef().GetArm2Angle()));

	size_t end_arm1 = (size_t)EulerUtils::GetCorrectedAngle(glm::degrees(model->GetEndRef().GetArm1Angle()));
	size_t end_arm2 = (size_t)EulerUtils::GetCorrectedAngle(glm::degrees(model->GetEndRef().GetArm2Angle()));

	configuration_space->DoFloodFill(start_arm1, start_arm2, end_arm1, end_arm2);
}

void Robot::UpdateCurrentConfiguration(float simulation_percentage)
{
	size_t path_size = configuration_space->GetPathSize();
	size_t path_idx = (size_t)glm::min(simulation_percentage * (path_size - 1), (float)(path_size - 2));

	float path_idx_pers = (float)path_idx / (path_size - 1);
	float path_idx_plus_one_pers = (float)(path_idx + 1) / (path_size - 1);

	float new_persentage = (simulation_percentage - path_idx_pers) / (path_idx_plus_one_pers - path_idx_pers);

	float a1 = configuration_space->GetPathElementX(path_idx);
	float a2 = configuration_space->GetPathElementX(path_idx + 1);
	float a3 = configuration_space->GetPathElementY(path_idx);
	float a4 = configuration_space->GetPathElementY(path_idx + 1);

	model->GetCurrentRef().GetArm1Ref().SetAngle(glm::radians(EulerUtils::GetEulerRotation(a1, a2, new_persentage)));
	model->GetCurrentRef().GetArm2Ref().SetAngle(glm::radians(EulerUtils::GetEulerRotation(a3, a4, new_persentage)));
}

glm::vec4 Robot::GetNewParametrizations(float x, float y)
{
	float l1 = model->GetStartRef().GetArm1Ref().GetLength();
	float l2 = model->GetStartRef().GetArm2Ref().GetLength();
	float l_square = x * x + y * y;

	float theta2 = 2.f * glm::pi<float>() - glm::acos((l_square - l1 * l1 - l2 * l2) / (2.f * l1 * l2));

	float beta = glm::atan(y, x);
	float phi = glm::acos((l_square + l1 * l1 - l2 * l2) / (2.f * l1 * glm::sqrt(l_square)));
	float theta1 = beta - phi;

	glm::vec4 out;

	out.x = beta + phi;
	out.y = theta2;

	out.z = beta - phi;
	out.w = -theta2;

	return out;
}

void Robot::ProcessConfiguration(RobotConfiguration& configuration, float xpos, float ypos)
{
	glm::vec2 pos = WindowSizeUtils::ParsePos(xpos, ypos);
	if (glm::length(pos) > configuration.GetArm1Ref().GetLength() + configuration.GetArm2Ref().GetLength() ||
		glm::length(pos) < configuration.GetArm1Ref().GetLength() - configuration.GetArm2Ref().GetLength())
	{
		configuration.SetIsCorrect(false);
		return;
	}

	configuration.SetIsCorrect(true);
	glm::vec4 param = GetNewParametrizations(pos.x, pos.y);

	configuration.GetArm1Ref().SetAngle(param.x);
	configuration.GetArm2Ref().SetAngle(param.y);

	configuration.GetArm1Ref().SetAlthernativeAngle(param.z);
	configuration.GetArm2Ref().SetAlthernativeAngle(param.w);
}

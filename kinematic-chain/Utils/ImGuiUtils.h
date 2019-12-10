#pragma once
#include "..//ImGui/imgui.h"
#include "..//ImGui/imgui_internal.h"

class ImGuiUtils
{
public:
	static void PushDisabledWithAlpha(float alpha = 0.5f)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * alpha);
	}

	static void PopDisabled()
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}
};
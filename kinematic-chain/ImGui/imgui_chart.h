#pragma once

#pragma once
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

using namespace std;

struct ChartData
{
public:
	ChartData() { }
	ChartData(vector<ImVec2>* _data, ImU32 _color) :data(_data), color(_color) {}
	vector<ImVec2>* data;
	ImU32 color;
};

class MyImGui 
{
public:
	static void DrawChart(std::vector<ChartData> data, ImVec2 min_range, ImVec2 max_range);
};

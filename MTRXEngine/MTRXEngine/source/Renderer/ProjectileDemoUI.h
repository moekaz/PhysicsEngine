#pragma once

#include <UIPanel.h>
#include <imgui/imgui.h>

class ProjectileDemoUI : public UIPanel
{
public:
	ProjectileDemoUI(const char* panelName, const glm::vec2& dimensions, int* projectile);
	~ProjectileDemoUI();

	void SetupPanelContent() override;
	int* projectile;
};


#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

class IntroSplashScreenComponent : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(IntroSplashScreenComponent, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	void init();
	void update();

private:
	enum class State
	{
		TitleFadeIn,
		TitleDisplay,
		TitleFadeOut,
		TextFadeIn,
		TextDisplay,
		TextFadeOut,
		Done
	};

	void showNextPair();

	State state = State::TitleFadeIn;
	bool end_of_splash_screen;
	float timer = 0.0f;
	int current_pair = 0;

	Unigine::WidgetSpritePtr background;
	Unigine::WidgetLabelPtr title_label;
	Unigine::WidgetLabelPtr text_label;
	Unigine::NodePtr freeze_state;
	Unigine::WidgetSpritePtr logo;

	Unigine::Vector<Unigine::String> line_pairs;

	const float fade_duration = 3.5f;
	const float display_duration = 2.5f;
};

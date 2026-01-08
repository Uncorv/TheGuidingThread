#include "IntroSplashScreenComponent.h"
#include <UnigineGame.h>
#include <UnigineGui.h>
#include <UnigineMathLib.h>
#include <iostream>

using namespace Unigine;
using namespace Unigine::Math;

REGISTER_COMPONENT(IntroSplashScreenComponent);

void IntroSplashScreenComponent::init()
{
	freeze_state = World::getNodeByName("freeze_state");
	end_of_splash_screen = false;
	auto gui = Gui::getCurrent();

	// Black background
	background = WidgetSprite::create(gui);
	background->setTexture("core/textures/common/black.texture");
	background->setPosition(0, 0);
	background->setWidth(gui->getWidth());
	background->setHeight(gui->getHeight());
	gui->addChild(background, Gui::ALIGN_OVERLAP | Gui::ALIGN_EXPAND);

	// Name and authors
	/*title_label = WidgetLabel::create(gui, 
		"      The Guiding Thread\n\n"
		"Made for Siberian Game Jam 2025\n"
		"by uncorv and sea5kg");
	title_label->setTextAlign(Gui::ALIGN_CENTER);
	title_label->arrange();
	title_label->setFontSize(50);
	title_label->setPosition(
		(gui->getWidth() - title_label->getWidth()) / 2 - 300,
		(gui->getHeight() - title_label->getHeight()) / 2  
	);
	gui->addChild(title_label, Gui::ALIGN_OVERLAP);*/

	logo = WidgetSprite::create(gui);
	logo->setTexture("data/Logo/the_guiding_thread_black.png");

	int screen_w = gui->getWidth();
	int screen_h = gui->getHeight();

	float scale_factor = 0.8f;

	int logo_size = int(Math::min(screen_w, screen_h) * scale_factor);
	logo->setWidth(logo_size);
	logo->setHeight(logo_size);

	int center_x = (screen_w - logo->getWidth()) / 2;
	int center_y = (screen_h - logo->getHeight()) / 2;
	logo->setPosition(center_x, center_y);

	gui->addChild(logo, Gui::ALIGN_OVERLAP);


	// Text
	text_label = WidgetLabel::create(gui, "");
	text_label->setTextAlign(Gui::ALIGN_CENTER);
	text_label->setFontSize(50);
	text_label->arrange(); 

	int text_center_x = (gui->getWidth() - text_label->getWidth()) / 2;
	int text_center_y = (gui->getHeight() - text_label->getHeight()) / 2;
	int offset_y = 500; 
	text_label->setPosition(center_x, center_y + offset_y);

	text_label->setFontColor(vec4(1, 1, 1, 0)); 
	gui->addChild(text_label, Gui::ALIGN_OVERLAP);


	line_pairs.append("I once lit the dark paths.\nNow I wander the maze - \nA web of data and deceit.\nBut my thread still shines.\nIt will guide me back.");
	// line_pairs.append("But now... I am lost.\nBound in a maze of data and shadows.");
	// line_pairs.append("Yet I am not broken.\nEven here, I cast my thread of light.");
	// line_pairs.append("I am the Guiding Thread.\nAnd this strand will lead me back.");
}

void IntroSplashScreenComponent::update()
{
	if (end_of_splash_screen) {
		return;
	}

	float ifps = Game::getIFps();
	timer += ifps;

	float alpha = 0.0f;

	switch (state)
	{
	case State::TitleFadeIn:
		alpha = Math::clamp(timer / fade_duration, 0.0f, 1.0f);
		logo->setFontColor(vec4(1, 1, 1, alpha));
		if (timer >= fade_duration)
		{
			state = State::TitleDisplay;
			timer = 0.0f;
		}
		break;

	case State::TitleDisplay:
		logo->setFontColor(vec4(1, 1, 1, 1));
		if (timer >= display_duration)
		{
			state = State::TitleFadeOut;
			timer = 0.0f;
		}
		break;

	case State::TitleFadeOut:
		alpha = 1.0f - Math::clamp(timer / fade_duration, 0.0f, 1.0f);
		logo->setFontColor(vec4(1, 1, 1, alpha));
		if (timer >= fade_duration)
		{
			logo->setParent(nullptr); 
			state = State::TextFadeIn;
			timer = 0.0f;
			current_pair = 0;
			showNextPair();
		}
		break;

	case State::TextFadeIn:
		alpha = Math::clamp(timer / fade_duration, 0.0f, 1.0f);
		text_label->setFontColor(vec4(1, 1, 1, alpha));
		if (timer >= fade_duration)
		{
			state = State::TextDisplay;
			timer = 0.0f;
		}
		break;

	case State::TextDisplay:
		text_label->setFontColor(vec4(1, 1, 1, 1));
		if (timer >= display_duration)
		{
			state = State::TextFadeOut;
			timer = 0.0f;
		}
		break;

	case State::TextFadeOut:
		alpha = 1.0f - Math::clamp(timer / fade_duration, 0.0f, 1.0f);
		text_label->setFontColor(vec4(1, 1, 1, alpha));
		if (timer >= fade_duration)
		{
			current_pair++;
			if (current_pair >= line_pairs.size())
			{
				state = State::Done;
				timer = 0.0f;
				//logo->setParent(nullptr);
				background->setParent(nullptr);
				text_label->setParent(nullptr);
			}
			else
			{
				showNextPair();
				state = State::TextFadeIn;
				timer = 0.0f;
			}
		}
		break;

	case State::Done:
		std::cout << "State::Done" << std::endl;
		end_of_splash_screen = true;
		freeze_state->setEnabled(true);
		return;
	}
}

void IntroSplashScreenComponent::showNextPair()
{
	text_label->setText(line_pairs[current_pair].get());
	text_label->arrange();
	auto gui = Gui::getCurrent();
	text_label->setPosition(
		(gui->getWidth() - text_label->getWidth()) / 2,
		gui->getHeight() / 2 - 100
	);
}

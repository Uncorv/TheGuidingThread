#include "MenuComponent.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"
#include "UnigineInput.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(MenuComponent);

void MenuComponent::init() {
    Unigine::Log::warning("MenuComponent::init");

    keyWaiterEsc.setWaitSec(0.7f);
	keyWaiterEsc.setKey(Input::KEY_ESC);

    freeze_state = World::getNodeByName("freeze_state");
    pause_state = World::getNodeByName("pause_state");

    gui = Unigine::Gui::getCurrent();

    // showedIntro = true;

    // double radius = 25.0f;
    // Copernicus_min_x = Room1Copernic.WorldBoundBox.minimum.x;
    // Copernicus_max_x = Room1Copernic.WorldBoundBox.maximum.x;
    // Copernicus_min_y = Room1Copernic.WorldBoundBox.minimum.y;
    // Copernicus_max_y = Room1Copernic.WorldBoundBox.maximum.y;

    // DaVinchi_min_x = Room1Davinci.WorldBoundBox.minimum.x;
    // DaVinchi_max_x = Room1Davinci.WorldBoundBox.maximum.x;
    // DaVinchi_min_y = Room1Davinci.WorldBoundBox.minimum.y;
    // DaVinchi_max_y = Room1Davinci.WorldBoundBox.maximum.y;

    // Aristotel_min_x = Room1Aristotel.WorldBoundBox.minimum.x;
    // Aristotel_max_x = Room1Aristotel.WorldBoundBox.maximum.x;
    // Aristotel_min_y = Room1Aristotel.WorldBoundBox.minimum.y;
    // Aristotel_max_y = Room1Aristotel.WorldBoundBox.maximum.y;

    // // sound_music = World.GetNodeByName("Music_Menu") as SoundSource;

    // InitMusicBackground();

    // main_window = WindowManager.MainWindow;

    // sound_effect = new SoundSource("Gui/Music/Effect_Scroll.ogg", 2);
    // sound_effect.PlayOnEnable = false;
    // sound_effect.Gain = 0.0f;
    // sound_effect.Name = "Effect_Scroll";
    // sound_effect.Occlusion = 0;
    // sound_effect.MinDistance = 0.0f;
    // sound_effect.MaxDistance = 100.0f;
    // sound_effect.Loop = 0;
    // // sound_effect.Enabled = true;
    // sound_effect.Stream = true;
    // sound_effect.SourceMask = 0x1000;
    // node.AddChild(sound_effect);
    // sound_effect.Position = new Vec3(0.0f, 0.0f, 0.0f);

    // showedMenu = false;
    // milliseconds = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
    // started_ms = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();

    // // need event on frist resizing
    // screen_width = gui.Width;
    // screen_height = gui.Height;

    // if (!isOutro) InitIntros();
    // else InitOutro();

    // Black background
    background = WidgetSprite::create(gui, "mane_background");
    // background.Texture = "menu_background0.png";
    background->setColor(vec4(0.0f, 0.0f, 0.0f, 0.8f));
    background->setPosition(0, 0);
    background->setWidth(gui->getWidth());
    background->setHeight(gui->getHeight());
    background->setHidden(!showedMenu);
    background->setOrder(1000);
    // background->arrange();
    gui->addChild(background, Gui::ALIGN_OVERLAP | Gui::ALIGN_EXPAND);
    // background.Lifetime = Widget.LIFETIME.WORLD;

    // // banner
    // LocalSprite sprite_banner = new LocalSprite(
    //     gui, "menu_banner",
    //     550, 50, 663, 329, // field 1600x900
    //     300, // order
    //     screen_width, screen_height
    // );
    // sprite_banner.SetHidden(!showedMenu);
    // widgets_menu.Add(sprite_banner);

    // // play button
    // LocalButton btn_play = new LocalButton(
    //     gui, "menu_start", node,
    //     550, 400, 500, 199, // field 1600x900
    //     300, // order
    //     screen_width, screen_height
    // );
    // btn_play.SetHidden(!showedMenu);
    // btn_play.btn.EventClicked.Connect(OnButtonContinueClicked);
    // buttons_menu.Add(btn_play);
    // widgets_menu.Add(btn_play);

    // // creating a button widget and setting its caption
    // LocalButton btn_exit = new LocalButton(
    //     gui, "menu_exit", node,
    //     550, 600, 500, 199, // field 1600x900
    //     300, // order
    //     screen_width, screen_height
    // );
    // btn_exit.SetHidden(!showedMenu);
    // btn_exit.btn.EventClicked.Connect(OnButtonExitClicked);
    // buttons_menu.Add(btn_exit);
    // widgets_menu.Add(btn_exit);

    // sprite_music_scroll_cursor = InitScrollControl("Музыка", 10, 350, OnButtonMinusMusicClicked, OnButtonPlusMusicClicked);
    // sprite_effects_scroll_cursor = InitScrollControl("Эффекты", 10, 500, OnButtonMinusEffectsClicked, OnButtonPlusEffectsClicked);

    // // nodePressPForCallMenu = World::getNodeByName("PressPForCallMenu");
    // label_hint = new WidgetLabel(gui, HintText);
    // label_hint.FontSize = 30;
    // label_hint.FontColor = new vec4(1.0f, 1.0f, 1.0f, 1.0f);
    // label_hint.SetPosition(20, -20);

    // label_hint.Hidden = showedMenu;
    // label_hint.Order = 150;
    // label_hint.Arrange();
    // label_hint.Hidden = true;
    // if (!isOutro) gui.AddChild(label_hint, Gui.ALIGN_OVERLAP | Gui.ALIGN_LEFT | Gui.ALIGN_BOTTOM);
    // else gui.AddChild(label_hint, Gui.ALIGN_OVERLAP | Gui.ALIGN_CENTER | Gui.ALIGN_EXPAND);
    // label_hint.Lifetime = Widget.LIFETIME.WORLD;
    // UpdateScrollPositions();
}

void MenuComponent::update() {
    UpdateIfWindowsResized();

    if (!freeze_state->isEnabled()) {
        return;
    }

    if (keyWaiterEsc.isPressed()) {
        ToggleMenu();
    }

    Unigine::Input::setMouseGrab(!showedMenu);

    // // kostyl
    // long milliseconds2 = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
    // // Log.Message("MenuMain update " + milliseconds2 + "\n");
    // if (!started && (milliseconds2 - started_ms) > 500) {
    //     started = true;

    //     sound_effect.Gain = 0.5f;
    //     SetEffectGain(sound_effect.Gain);

    //     SetMusicGain(sound_music_level);

    //     UpdateScrollPositions();
    // }

    // CheckAndSwitchMusic();

    if (Unigine::Input::isMouseGrab())
        return;

    // if (showedMenu) {
    //     int mouse_x = gui.MouseX;
    //     int mouse_y = gui.MouseY;

    //     foreach (LocalButton btn0 in buttons_menu)
    //     {
    //         btn0.HandleMouseEvent(mouse_x, mouse_y);
    //     }
    // }

    // if (showedIntro && !showedMenu) {
    //     int mouse_x = gui.MouseX;
    //     int mouse_y = gui.MouseY;

    //     foreach (LocalButton btn0 in buttons_intro)
    //     {
    //         btn0.HandleMouseEvent(mouse_x, mouse_y);
    //     }
    // }
}

void MenuComponent::UpdateIfWindowsResized() {
    if (screen_width != gui->getWidth() || screen_height != gui->getHeight()) {
        Unigine::Log::message("UpdateIfWindowsResized resized\n");
        screen_width = gui->getWidth();
        screen_height = gui->getHeight();

        background->setWidth(screen_width);
        background->setHeight(screen_height);

        // foreach (LocalWidget wgt0 in widgets_menu)
        // {
        //     wgt0.Update(screen_width, screen_height);
        // }

        // foreach (LocalWidget wgt0 in widgets_intro)
        // {
        //     wgt0.Update(screen_width, screen_height);
        // }

        UpdateScrollPositions();
    }
}


void MenuComponent::UpdateScrollPositions() {
    // int new_x_position = Convert.ToInt32((700 - 160 - 100) * sound_music_level);
    // sprite_music_scroll_cursor.SetNewPositionX(10 + Convert.ToInt32((new_x_position + 100 + 80) * scroll_scale));

    // int new_x_position2 = Convert.ToInt32((700 - 160 - 100) * sound_effect.Gain);
    // sprite_effects_scroll_cursor.SetNewPositionX(10 + Convert.ToInt32((new_x_position2 + 100 + 80) * scroll_scale));
}

void MenuComponent::ToggleMenu() {
    Unigine::Log::warning("MenuComponent::ToggleMenu()\n");

	showedMenu = !showedMenu;

    pause_state->setEnabled(showedMenu);

// 		// if (showedMenu) {
// 		// 	PlayMusic("Menu");
// 		// }
    background->setHidden(!showedMenu);

// 		label_hint.Hidden = showedMenu;
// 		// label_hint.Arrange();

// 		foreach (LocalButton btn0 in buttons_menu)
// 		{
// 			btn0.btn.Hidden = !showedMenu;
// 		}

// 		foreach (LocalWidget wgt0 in widgets_menu)
// 		{
// 			wgt0.SetHidden(!showedMenu);
// 		}

// 		if (showedMenu) {
// 			foreach (LocalButton btn0 in buttons_intro)
// 			{
// 				btn0.SetHidden(true);
// 			}
// 		}

// 		if (!showedMenu && showedIntro) {
// 			foreach (LocalButton btn0 in buttons_intro)
// 			{
// 				btn0.SetHidden(false);
// 			}
// 		}

 	Unigine::Input::setMouseGrab(!showedMenu);
}




/*

// added from other

#region Math Variables
#if UNIGINE_DOUBLE
using Scalar = System.Double;
using Vec2 = Unigine.dvec2;
using Vec3 = Unigine.dvec3;
using Vec4 = Unigine.dvec4;
using Mat4 = Unigine.dmat4;
#else
using Scalar = System.Single;
using Vec2 = Unigine.vec2;
using Vec3 = Unigine.vec3;
using Vec4 = Unigine.vec4;
using Mat4 = Unigine.mat4;
using WorldBoundBox = Unigine.BoundBox;
using WorldBoundSphere = Unigine.BoundSphere;
using WorldBoundFrustum = Unigine.BoundFrustum;
#endif
#endregion

using System.Collections;
using System.Collections.Generic;
using System;
using Unigine;

public delegate void MyClick();

[Component(PropertyGuid = "a11da8c3b45a5bb1ac1e5af4c3f850270e7f6210")]
public class MainMenu : Component
{
	private class LocalWidget {
		public Widget widget;
		public int order;
		protected int min_x;
		protected int min_y;
		protected int max_x;
		protected int max_y;
		protected float fx;
		protected float fy;
		protected float fw;
		protected float fh;
		protected float scale_x;
		protected float scale_y;
		protected int screen_w;
		protected int screen_h;

		// Constructor with parameters
		public LocalWidget(Gui gui, Widget widg, int x, int y, int w, int h, int ord, int scr_w, int scr_h)
		{
			order = ord;
			screen_w = scr_w;
			screen_h = scr_h;
			widget = widg;

			scale_x = (float)screen_w / 1600.0f;
			scale_y = (float)screen_h / 900.0f;

			fx = ((float)x * scale_x) / (float)screen_w;
			fy = ((float)y * scale_y) / (float)screen_h;
			fw = ((float)w * scale_x) / (float)screen_w;
			fh = ((float)h * scale_y) / (float)screen_h;
			widget.Order = order;
			widget.Arrange();
			Update(screen_w, screen_h);
			gui.AddChild(widget, Gui.ALIGN_OVERLAP | Gui.ALIGN_LEFT | Gui.ALIGN_EXPAND);
			widget.Lifetime = Widget.LIFETIME.WORLD;
		}

		public void Update(int scr_w, int scr_h) {
			screen_w = scr_w;
			screen_h = scr_h;

			scale_x = (float)screen_w / 1600.0f;
			scale_y = (float)screen_h / 900.0f;

			widget.SetPosition(Convert.ToInt32(fx * screen_w), Convert.ToInt32(fy * screen_h));
			widget.Width = Convert.ToInt32(fw * screen_w);
			widget.Height = Convert.ToInt32(fh * screen_h);

			min_x = widget.PositionX;
			min_y = widget.PositionY;
			max_x = widget.PositionX + widget.Width;
			max_y = widget.PositionY + widget.Height;
			// widget.Order = order;
			// widget.Arrange();
		}

		public void SetNewPositionX(int x) {
			fx = ((float)x * scale_x) / (float)screen_w;
			widget.SetPosition(Convert.ToInt32(fx * screen_w), Convert.ToInt32(fy * screen_h));
		}

		public void SetHidden(bool hidden) {
			widget.Hidden = hidden;
			// widget.Order = order;
			// widget.Arrange();
		}
	}

	private class LocalButton : LocalWidget {
		public WidgetSprite btn;

		private bool mouse_over = false;
		private SoundSource sound_mouse_in;
		private string texture;
		private string texture_selected;

		// Constructor with parameters
		public LocalButton(Gui gui, string texture_prefix, Node node, int x, int y, int w, int h, int ord, int scr_w, int scr_h)
			: base(gui, new WidgetSprite(gui), x, y, w, h, ord, scr_w, scr_h)
		{
			texture = texture_prefix + ".png";
			texture_selected = texture_prefix + "_selected.png";
			btn = widget as WidgetSprite;
			Update(scr_w, scr_h);

			sound_mouse_in = new SoundSource("Gui/Music/Effect_MouseIn.ogg");
			sound_mouse_in.Name = "Effect_MouseIn";
			sound_mouse_in.Occlusion = 0;
			sound_mouse_in.Gain = 0.0f;
			sound_mouse_in.MinDistance = 0.0f;
			sound_mouse_in.MaxDistance = 100.0f;
			sound_mouse_in.Loop = 0;
			sound_mouse_in.Stream = true;
			sound_mouse_in.SourceMask = 0x1000;
			node.AddChild(sound_mouse_in);
			sound_mouse_in.Position = new Vec3(0.0f, 0.0f, 0.0f);
		}

		public void Update(int scr_w, int scr_h) {
			base.Update(scr_w, scr_h);
			btn.Texture = texture;
		}

		public bool hasPoint(int mouse_x, int mouse_y) {
			return mouse_x >= min_x && mouse_x <= max_x
			&& mouse_y >= min_y && mouse_y <= max_y;
		}

		public void MouseIn() {
			// Log.Message("Exit button overing \n");
			if (!mouse_over) {
				mouse_over = true;
				sound_mouse_in.Play();
				btn.Texture = texture_selected;
			}
		}

		public void MouseOut() {
			if (mouse_over) {
				mouse_over = false;
				btn.Texture = texture;
			}
		}

		public void HandleMouseEvent(int mouse_x, int mouse_y) {
			if (hasPoint(mouse_x, mouse_y)) {
				MouseIn();
			} else {
				MouseOut();
			}
		}
	}

	private class LocalSprite : LocalWidget {
		public WidgetSprite sprite;
		// private string texture;

		public LocalSprite(Gui gui, string texture_prefix, int x, int y, int w, int h, int ord, int scr_w, int scr_h)
			: base(gui, new WidgetSprite(gui), x, y, w, h, ord, scr_w, scr_h)
		{
			sprite = widget as WidgetSprite;
			sprite.Texture = texture_prefix + ".png";
			Update(scr_w, scr_h);
		}
	}

	private class LocalLabel : LocalWidget {
		public WidgetLabel label;
		private string texture;

		public LocalLabel(Gui gui, string text, int x, int y, int ord, int scr_w, int scr_h)
			: base(gui, new WidgetLabel(gui), x, y, 100, 100, ord, scr_w, scr_h)
		{
			label = widget as WidgetLabel;
			label.Text = text;
			label.FontSize = 30;
			label.FontColor = new vec4(0.318f, 0.255f, 0.188f, 1.0f);

			// WidgetLabel label_scroll = new WidgetLabel(gui, label);
			// gui.AddChild(label_scroll, Gui.ALIGN_OVERLAP | Gui.ALIGN_LEFT | Gui.ALIGN_EXPAND);
			// labels.Add(label_scroll);

			Update(scr_w, scr_h);
		}
	}

	private class LocalIntroPage {
		private LocalSprite background;
		private LocalSprite background_text;
		private LocalLabel label;

		public LocalIntroPage(bool showedIntro, Gui gui, string back_texture, string text, int screen_width, int screen_height, List<LocalWidget> widgets_intro) {
			background = new LocalSprite(
				gui, back_texture,
				0, 0, 1600, 900, // 1600x900 (recalculated in controll automaticly)
				110, // order
				screen_width, screen_height
			);
			background.SetHidden(!showedIntro);
			widgets_intro.Add(background);

			background_text = new LocalSprite(
				gui, "intro_text_background",
				0, 0, 1600, 900, // 1600x900 (recalculated in controll automaticly)
				120, // order
				screen_width, screen_height
			);
			background_text.SetHidden(!showedIntro);
			widgets_intro.Add(background_text);

			label = new LocalLabel(
				gui, text,
				100, 200,
				130, // order
				screen_width, screen_height
			);
			label.label.FontColor = new vec4(1.0f, 1.0f, 1.0f, 0.9f);;
			label.SetHidden(!showedIntro);
			widgets_intro.Add(label);
		}

		public void Hide() {
			background.SetHidden(true);
			background_text.SetHidden(true);
			label.SetHidden(true);
		}

		public void Show() {
			background.SetHidden(false);
			background_text.SetHidden(false);
			label.SetHidden(false);
		}
	};

	// private Mat4 worldTransform = Mat4.IDENTITY;
	private bool showedMenu;
	private bool showedIntro;
	private long milliseconds;
	private long started_ms;
	private bool started = false;
	private EngineWindow main_window;
	private WidgetLabel label_hint;
	private WidgetSprite background;
	private LocalButton btn_intro_continue;

	private float sound_music_level = 0.08f;
	private SoundSource sound_effect;
	private int screen_width = 0;
	private int screen_height = 0;
	private float scroll_scale = 0.5f;
	private LocalSprite sprite_music_scroll_cursor;
	private LocalSprite sprite_effects_scroll_cursor;

	private double Copernicus_min_x;
	private double Copernicus_max_x;
	private double Copernicus_min_y;
	private double Copernicus_max_y;

	private double DaVinchi_min_x;
	private double DaVinchi_max_x;
	private double DaVinchi_min_y;
	private double DaVinchi_max_y;

	private double Aristotel_min_x;
	private double Aristotel_max_x;
	private double Aristotel_min_y;
	private double Aristotel_max_y;

	private Gui gui;

	// [HideInEditor]
	[ShowInEditor]
	public string HintText { get; set; } = "Нажмите 'Esc' для выхода в меню. 'E' - взять предмет. 'Q' - бросить предмет.";

	private List<LocalButton> buttons_menu = new List<LocalButton>();
	private List<LocalWidget> widgets_menu = new List<LocalWidget>();
	private List<LocalButton> buttons_intro = new List<LocalButton>();
	private List<LocalWidget> widgets_intro = new List<LocalWidget>();
	private List<LocalIntroPage> pages_intro = new List<LocalIntroPage>();
	private int pages_intro_idx = 0;
	private Dictionary<string, SoundSource> sound_musics = new Dictionary<string, SoundSource>();
	public Node Room1Copernic;
	public Node Room1Davinci;
	public Node Room1Aristotel;

	[ShowInEditor]
  	[Parameter]
	public bool isOutro = false;


	void Init() {
		if (isOutro) HintText = "КОНЕЦ. Спасибо что поиграли в нашу игру!";
		gui = Gui.GetCurrent();
		gui.SetFontPath("CormorantUnicase-Medium.ttf");

		showedIntro = true;

		double radius = 25.0f;
		Copernicus_min_x = Room1Copernic.WorldBoundBox.minimum.x;
		Copernicus_max_x = Room1Copernic.WorldBoundBox.maximum.x;
		Copernicus_min_y = Room1Copernic.WorldBoundBox.minimum.y;
		Copernicus_max_y = Room1Copernic.WorldBoundBox.maximum.y;

		DaVinchi_min_x = Room1Davinci.WorldBoundBox.minimum.x;
		DaVinchi_max_x = Room1Davinci.WorldBoundBox.maximum.x;
		DaVinchi_min_y = Room1Davinci.WorldBoundBox.minimum.y;
		DaVinchi_max_y = Room1Davinci.WorldBoundBox.maximum.y;

		Aristotel_min_x = Room1Aristotel.WorldBoundBox.minimum.x;
		Aristotel_max_x = Room1Aristotel.WorldBoundBox.maximum.x;
		Aristotel_min_y = Room1Aristotel.WorldBoundBox.minimum.y;
		Aristotel_max_y = Room1Aristotel.WorldBoundBox.maximum.y;

		// sound_music = World.GetNodeByName("Music_Menu") as SoundSource;

		InitMusicBackground();

		main_window = WindowManager.MainWindow;

		sound_effect = new SoundSource("Gui/Music/Effect_Scroll.ogg", 2);
		sound_effect.PlayOnEnable = false;
		sound_effect.Gain = 0.0f;
		sound_effect.Name = "Effect_Scroll";
		sound_effect.Occlusion = 0;
		sound_effect.MinDistance = 0.0f;
		sound_effect.MaxDistance = 100.0f;
		sound_effect.Loop = 0;
		// sound_effect.Enabled = true;
		sound_effect.Stream = true;
		sound_effect.SourceMask = 0x1000;
		node.AddChild(sound_effect);
		sound_effect.Position = new Vec3(0.0f, 0.0f, 0.0f);

		showedMenu = false;
		milliseconds = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
		started_ms = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();

		// need event on frist resizing
		screen_width = gui.Width;
		screen_height = gui.Height;

		if (!isOutro) InitIntros();
		else InitOutro();

		// Black background
		background = new WidgetSprite(gui);
		background.Texture = "menu_background0.png";
		// background.Texture = "intro1.png";
		background.Color = new vec4(1.0f, 1.0f, 1.0f, 0.9f);
		background.SetPosition(0, 0);
		background.Width = gui.Width;
		background.Height = gui.Height;
		background.Hidden = !showedMenu;
		background.Order = 200;
		background.Arrange();
		gui.AddChild(background, Gui.ALIGN_OVERLAP | Gui.ALIGN_EXPAND);
		background.Lifetime = Widget.LIFETIME.WORLD;

		// banner
		LocalSprite sprite_banner = new LocalSprite(
			gui, "menu_banner",
			550, 50, 663, 329, // field 1600x900
			300, // order
			screen_width, screen_height
		);
		sprite_banner.SetHidden(!showedMenu);
		widgets_menu.Add(sprite_banner);

		// play button
		LocalButton btn_play = new LocalButton(
			gui, "menu_start", node,
			550, 400, 500, 199, // field 1600x900
			300, // order
			screen_width, screen_height
		);
		btn_play.SetHidden(!showedMenu);
		btn_play.btn.EventClicked.Connect(OnButtonContinueClicked);
		buttons_menu.Add(btn_play);
		widgets_menu.Add(btn_play);

		// creating a button widget and setting its caption
		LocalButton btn_exit = new LocalButton(
			gui, "menu_exit", node,
			550, 600, 500, 199, // field 1600x900
			300, // order
			screen_width, screen_height
		);
		btn_exit.SetHidden(!showedMenu);
		btn_exit.btn.EventClicked.Connect(OnButtonExitClicked);
		buttons_menu.Add(btn_exit);
		widgets_menu.Add(btn_exit);

		sprite_music_scroll_cursor = InitScrollControl("Музыка", 10, 350, OnButtonMinusMusicClicked, OnButtonPlusMusicClicked);
		sprite_effects_scroll_cursor = InitScrollControl("Эффекты", 10, 500, OnButtonMinusEffectsClicked, OnButtonPlusEffectsClicked);

		// nodePressPForCallMenu = World::getNodeByName("PressPForCallMenu");
		label_hint = new WidgetLabel(gui, HintText);
		label_hint.FontSize = 30;
		label_hint.FontColor = new vec4(1.0f, 1.0f, 1.0f, 1.0f);
		label_hint.SetPosition(20, -20);
		
		label_hint.Hidden = showedMenu;
		label_hint.Order = 150;
		label_hint.Arrange();
		label_hint.Hidden = true;
		if (!isOutro) gui.AddChild(label_hint, Gui.ALIGN_OVERLAP | Gui.ALIGN_LEFT | Gui.ALIGN_BOTTOM);
		else gui.AddChild(label_hint, Gui.ALIGN_OVERLAP | Gui.ALIGN_CENTER | Gui.ALIGN_EXPAND);
		label_hint.Lifetime = Widget.LIFETIME.WORLD;
		UpdateScrollPositions();


		// label_hint.Order = 150;
		// label_hint.Arrange();

		// if (showedMenu) {
		// 	PlayMusic("Menu");
		// 	// sound_music.Enabled = true;
		// }
	}

	SoundSource CreateSound(string name, string filepath, int stream) {
		SoundSource sound = new SoundSource(filepath);
		sound.Name = name;
		sound.Enabled = false;
		sound.Occlusion = 0;
		sound.Gain = 0.0f;
		sound.MinDistance = 0.0f;
		sound.MaxDistance = 100.0f;
		sound.Loop = 1;
		sound.PlayOnEnable = true;
		sound.RestartOnEnable = false;
		sound.Stream = true;
		sound.SourceMask = 0x8000;
		node.AddChild(sound);
		sound.Position = new Vec3(0.0f, 0.0f, 0.0f);
		return sound;
	}

	void InitMusicBackground() {
		sound_musics.Add("Menu",
			CreateSound("Music_Menu", "Gui/Music/Music_Menu-v2.ogg", 1)
		);
		sound_musics.Add("Novel",
			CreateSound("Music_Novel", "Gui/Music/Music_Novel-v1.ogg", 2)
		);
		sound_musics.Add(
			"Copernicus",
			CreateSound("Music_Copernicus", "Gui/Music/Music_Copernicus-v1.ogg", 3)
		);
		sound_musics.Add(
			"Aristotle",
			CreateSound("Music_Aristotle", "Gui/Music/Music_Aristotle-v1.ogg", 4)
		);
		sound_musics.Add(
			"Da-Vinci",
			CreateSound("Music_Da-Vinci", "Gui/Music/Music_Da-Vinci-v2.ogg", 5)
		);
	}

	void InitIntros() {
		// page1
		string label_intro1_text = "Молодой учёный сидел у окна своей небольшой обсерватории.\n";
		label_intro1_text += "Он тщательно протирал линзу телескопа мягкой тканью — день был ясный,\n";
		label_intro1_text += "а значит, предстояла долгая ночь наблюдений.\n";
		label_intro1_text += "Весь стол был заставлен десятком линз, которые ждали своей очереди\n";
		label_intro1_text += "на полировку, а на шкафу пылилась старая призма — подарок от наставника,\n";
		label_intro1_text += "бесполезная, как он тогда решил.";
		LocalIntroPage page1 = new LocalIntroPage(
			showedIntro,
			gui, "intro1",
			label_intro1_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page1);

		// page2
		string label_intro2_text = "Вдруг на стекле мелькнули тонкие радужные полосы.\n";
		label_intro2_text += "Они не стояли на месте — двигались, переливались.\n";
		label_intro2_text += "Он наклонился ближе, поворачивал линзу к свету, прятал её в тень,\n";
		label_intro2_text += "снова выносил под солнце — а блики то появлялись, то исчезали,\n";
		label_intro2_text += "не подчиняясь никакому порядку.\n";
		LocalIntroPage page2 = new LocalIntroPage(
			false,
			gui, "intro2",
			label_intro2_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page2);

		// page3
		string label_intro3_text = "Он нахмурился. Ни одна известная ему теория не могла объяснить этого.\n";
		label_intro3_text += "Не было ни влаги, ни пыли, ни царапин — но цвета появлялись, как будто из ниоткуда.\n";
		label_intro3_text += "Он записал в тетради: «Блики на линзе ведут себя произвольно.\n";
		label_intro3_text += "Возможно, глаз сам создаёт их? Или это свойство стекла?»\n";
		LocalIntroPage page3 = new LocalIntroPage(
			false,
			gui, "intro3",
			label_intro3_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page3);

		// page4
		string label_intro4_text = "Потом он долго вертел линзу, следил за её сиянием, но чем внимательнее смотрел, тем меньше понимал.\n";
		label_intro4_text += "Свет на стекле жил своей жизнью, не слушаясь логики.\n";
		LocalIntroPage page4 = new LocalIntroPage(
			false,
			gui, "intro4",
			label_intro4_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page4);

		// page5
		string label_intro5_text = "Свеча догорела, воздух стал прохладным.\n";
		label_intro5_text += "Учёный положил линзу рядом с тетрадью, ещё раз взглянул на неё и устало опустил голову на руки.\n";
		label_intro5_text += "Он уснул, еще не зная, что блики, мелькающие в мыслях, станут началом его открытия\n";
		LocalIntroPage page5 = new LocalIntroPage(
			false,
			gui, "intro5",
			label_intro5_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page5);

		btn_intro_continue = new LocalButton(
			gui, "intro_btn_continue", node,
			1100, 550, 300, 100, // field 1600x900
			190, // order
			screen_width, screen_height
		);
		btn_intro_continue.SetHidden(!showedIntro);
		btn_intro_continue.btn.EventClicked.Connect(OnButtonIntroContinueClicked);
		buttons_intro.Add(btn_intro_continue);
		widgets_intro.Add(btn_intro_continue);
	}
	void InitOutro() {
		// page1
		string label_intro1_text = "Я проснулся прямо за столом, среди учебников и собственных записей.\n";
		label_intro1_text += "Солнце уже пробивалось сквозь щель в окне, освещая призму, стоящую на шкафу\n";
		label_intro1_text += "Всю ночь мне снились странные вещи — будто свет распадается на части, как нить,\nкоторую кто-то тянет.\n";
		LocalIntroPage page1 = new LocalIntroPage(
			showedIntro,
			gui, "final1",
			label_intro1_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page1);

		// page2
		string label_intro2_text = "Я взял призму, решив наконец проверить, как поведёт себя свет,\n";
		label_intro2_text += "если пропустить его сквозь стекло, и поднял её к солнечному лучу.\n";
		label_intro2_text += "На стене появилась полоса цветов.\n";
		label_intro2_text += "Я наклонил призму — цвета изменили порядок, но не исчезли.\n";
		LocalIntroPage page2 = new LocalIntroPage(
			false,
			gui, "final2",
			label_intro2_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page2);

		// page3
		string label_intro3_text = "Свет, который я считал единым, оказался множеством.\n";
		label_intro3_text += "И в тот миг я понял: истина не прячется во тьме — она просто разложена на части,\n";
		label_intro3_text += "и увидеть её можно лишь тем, кто ищет внимательнее.\n";
		LocalIntroPage page3 = new LocalIntroPage(
			false,
			gui, "final3",
			label_intro3_text,
			screen_width, screen_height,
			widgets_intro
		);
		pages_intro.Add(page3);

		btn_intro_continue = new LocalButton(
			gui, "intro_btn_continue", node,
			1100, 550, 300, 100, // field 1600x900
			190, // order
			screen_width, screen_height
		);
		btn_intro_continue.SetHidden(!showedIntro);
		btn_intro_continue.btn.EventClicked.Connect(OnButtonIntroContinueClicked);
		buttons_intro.Add(btn_intro_continue);
		widgets_intro.Add(btn_intro_continue);
	}
	LocalSprite InitScrollControl(string label, int x, int y, EventDelegate minus, EventDelegate plus) {

		// nodePressPForCallMenu = World::getNodeByName("PressPForCallMenu");
		LocalLabel label_scroll = new LocalLabel(
			gui, label,
			x + Convert.ToInt32((100 + 250) * scroll_scale), // x
			y,
			300, // order
			screen_width, screen_height
		);
		label_scroll.SetHidden(!showedMenu);
		widgets_menu.Add(label_scroll);

		// music down
		LocalButton btn_music_down = new LocalButton(
			gui, "menu_scroll_down", node,
			x, // x
			y + 30, Convert.ToInt32(100 * scroll_scale), Convert.ToInt32(189 * scroll_scale), // field 1600x900
			300, // order
			screen_width, screen_height
		);
		btn_music_down.SetHidden(!showedMenu);
		btn_music_down.btn.EventClicked.Connect(minus);
		buttons_menu.Add(btn_music_down);
		widgets_menu.Add(btn_music_down);

		// music scroll
		LocalSprite sprite_music_scroll = new LocalSprite(
			gui, "menu_scroll",
			x + Convert.ToInt32(100 * scroll_scale), // x
			y + 30, Convert.ToInt32(700 * scroll_scale), Convert.ToInt32(189 * scroll_scale), // field 1600x900
			300, // order
			screen_width, screen_height
		);
		sprite_music_scroll.SetHidden(!showedMenu);
		widgets_menu.Add(sprite_music_scroll);

		// music cursor
		LocalSprite sprite_scroll_cursor = new LocalSprite(
			gui, "menu_scroll_cursor",
			x + Convert.ToInt32((100 + 80) * scroll_scale), // x
			y + 30, Convert.ToInt32(100 * scroll_scale), Convert.ToInt32(189 * scroll_scale), // field 1600x900
			300, // order
			screen_width, screen_height
		);
		sprite_scroll_cursor.SetHidden(!showedMenu);
		widgets_menu.Add(sprite_scroll_cursor);

		// music up
		LocalButton btn_music_up = new LocalButton(
			gui, "menu_scroll_up", node,
			x + Convert.ToInt32(100 * scroll_scale) + Convert.ToInt32(700 * scroll_scale), // x
			y + 30, Convert.ToInt32(100 * scroll_scale), Convert.ToInt32(189 * scroll_scale), // field 1600x900
			300, // order
			screen_width, screen_height
		);
		btn_music_up.SetHidden(!showedMenu);
		btn_music_up.btn.EventClicked.Connect(plus);
		buttons_menu.Add(btn_music_up);
		widgets_menu.Add(btn_music_up);

		return sprite_scroll_cursor;
	}

	void Update()
	{
		UpdateIfWindowsResized();
		// if (!Input.MouseGrab)
		// 	return;

		if (Input.IsKeyDown(Input.KEY.ESC)) {
			ToggleMenu();
		}

		Input.MouseGrab = !showedMenu && !showedIntro;

		// kostyl
		long milliseconds2 = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
		// Log.Message("MenuMain update " + milliseconds2 + "\n");
		if (!started && (milliseconds2 - started_ms) > 500) {
			started = true;

			sound_effect.Gain = 0.5f;
			SetEffectGain(sound_effect.Gain);

			SetMusicGain(sound_music_level);

			UpdateScrollPositions();
		}

		CheckAndSwitchMusic();

		if (Input.MouseGrab)
			return;

		if (showedMenu) {
			int mouse_x = gui.MouseX;
			int mouse_y = gui.MouseY;

			foreach (LocalButton btn0 in buttons_menu)
			{
				btn0.HandleMouseEvent(mouse_x, mouse_y);
			}
		}

		if (showedIntro && !showedMenu) {
			int mouse_x = gui.MouseX;
			int mouse_y = gui.MouseY;

			foreach (LocalButton btn0 in buttons_intro)
			{
				btn0.HandleMouseEvent(mouse_x, mouse_y);
			}
		}

		// Log.Message("Mouse " + mouse_x + "; " + mouse_y + "\n");
	}

	public void OnButtonExitClicked()
	{
		Engine.Quit();
	}

	public void OnButtonContinueClicked()
	{
		ToggleMenu();
	}

	private void ToggleMenu() {
		showedMenu = !showedMenu;
		// if (showedMenu) {
		// 	PlayMusic("Menu");
		// }

		background.Hidden = !showedMenu;
		// background.Order = 200;
		// background.Arrange();

		label_hint.Hidden = showedMenu;
		// label_hint.Arrange();

		foreach (LocalButton btn0 in buttons_menu)
		{
			btn0.btn.Hidden = !showedMenu;
		}

		foreach (LocalWidget wgt0 in widgets_menu)
		{
			wgt0.SetHidden(!showedMenu);
		}
		// foreach (LocalWidget wgt0 in widgets_intro)
		// {
		// 	wgt0.SetHidden(!showedMenu);
		// }

		if (showedMenu) {
			foreach (LocalButton btn0 in buttons_intro)
			{
				btn0.SetHidden(true);
			}
		}

		if (!showedMenu && showedIntro) {
			foreach (LocalButton btn0 in buttons_intro)
			{
				btn0.SetHidden(false);
			}
		}

		Input.MouseGrab = !showedMenu && !showedIntro;

		// sound_menu_mouse.Play();
	}

	private void UpdateIfWindowsResized() {
		// Log.Message("UpdateIfWindowsResized\n");
		if (screen_width != gui.Width || screen_height != gui.Height) {
			// Log.Message("resized!!!\n");
			screen_width = gui.Width;
			screen_height = gui.Height;

			background.Width = screen_width;
			background.Height = screen_height;

			foreach (LocalWidget wgt0 in widgets_menu)
			{
				wgt0.Update(screen_width, screen_height);
			}

			foreach (LocalWidget wgt0 in widgets_intro)
			{
				wgt0.Update(screen_width, screen_height);
			}

			UpdateScrollPositions();
		}
	}

	private void UpdateScrollPositions() {
		int new_x_position = Convert.ToInt32((700 - 160 - 100) * sound_music_level);
		sprite_music_scroll_cursor.SetNewPositionX(10 + Convert.ToInt32((new_x_position + 100 + 80) * scroll_scale));

		int new_x_position2 = Convert.ToInt32((700 - 160 - 100) * sound_effect.Gain);
		sprite_effects_scroll_cursor.SetNewPositionX(10 + Convert.ToInt32((new_x_position2 + 100 + 80) * scroll_scale));
	}

	private void OnButtonPlusMusicClicked() {
		sound_music_level += 0.05f;
		if (sound_music_level > 1.0f) {
			sound_music_level = 1.0f;
		}
		SetMusicGain(sound_music_level);
		UpdateScrollPositions();
	}

	private void OnButtonMinusMusicClicked() {
		sound_music_level -= 0.05f;
		if (sound_music_level < 0.0f) {
			sound_music_level = 0.0f;
		}
		SetMusicGain(sound_music_level);
		UpdateScrollPositions();
	}

	private void OnButtonPlusEffectsClicked() {
		sound_effect.Gain += 0.1f;
		sound_effect.Play();
		SetEffectGain(sound_effect.Gain);
		UpdateScrollPositions();
	}

	private void OnButtonMinusEffectsClicked() {
		sound_effect.Gain -= 0.1f;
		sound_effect.Play();
		SetEffectGain(sound_effect.Gain);
		UpdateScrollPositions();
	}

	private void SetEffectGain(float val) {
		List<Node> nodes = new List<Node>();
		World.GetNodesByType((int)Node.TYPE.SOUND_SOURCE, nodes);
		foreach (var n in nodes) {
			SoundSource s = n as SoundSource;
			if (s.Name.StartsWith("Effect_")) {
				s.Gain = val;
			}
		}
	}

	private void SetMusicGain(float val) {
		List<Node> nodes = new List<Node>();
		World.GetNodesByType((int)Node.TYPE.SOUND_SOURCE, nodes);
		foreach (var n in nodes) {
			SoundSource s = n as SoundSource;
			if (s.Name.StartsWith("Music_")) {
				s.Gain = val;
			}
		}
	}

	private void PlayMusic(string name) {

		foreach (KeyValuePair<string, SoundSource> pair in sound_musics)
		{
			if (pair.Key == name) {
				if (!pair.Value.Enabled) {
					Log.Message("Enabled: " + pair.Key);
					pair.Value.Enabled = true;
				}
			} else {
				if (pair.Value.Enabled) {
					Log.Message("Disabled: " + pair.Key);
					pair.Value.Enabled = false;
				}
			}
		}

		// if (sound_musics.TryGetValue(name, out SoundSource sound))
        // {
		// 	Log.Message("Try play: " + name + "\n");
		// 	if (!sound.IsPlaying) {
		// 		Log.Message("Play\n");
		// 		sound.Enabled = true;
		// 		sound.Play();
		// 	}
        // } else {
		// 	Log.Message("Not found: " + name);
		// }
	}

	private void CheckAndSwitchMusic() {
		if (showedIntro) {
			PlayMusic("Novel");
		}
		else if (showedMenu) {
			PlayMusic("Menu"); // TODO novel or menu
		} else {
			double x = node.WorldPosition.x;
			double y = node.WorldPosition.y;

			if (x >= Copernicus_min_x && x <= Copernicus_max_x ) {
				PlayMusic("Copernicus");
			} else if (x >= Aristotel_min_x && x <= Aristotel_max_x ) {
				PlayMusic("Aristotle");
			} else if (x >= DaVinchi_min_x && x <= DaVinchi_max_x) {
				PlayMusic("Da-Vinci");
			} else {
				PlayMusic("None");
			}

		}
	}

	private void OnButtonIntroContinueClicked() {
		if (pages_intro_idx < pages_intro.Count) {
			pages_intro[pages_intro_idx].Hide();
		}
		pages_intro_idx += 1;
		if (pages_intro_idx < pages_intro.Count) {
			pages_intro[pages_intro_idx].Show();
		} else {
			btn_intro_continue.SetHidden(true);
			label_hint.Hidden = false;
			showedIntro = false;
		}
	}
}

*/

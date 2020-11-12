#include"GameProces.h"
#include"Settings.h"
#include"MyHeader.h"


int main()
{
	setlocale(LC_ALL, "rus");
	
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	ContextSettings settings;
	settings.antialiasingLevel = 20;//сглаживание

	workWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
	Image icon;
	if (!icon.loadFromFile("Images/icon.png"))
		exit(1);
	workWindow.setIcon(32, 32, icon.getPixelsPtr());

	Game game;
	bool start = 0;
	int NumberImage = 1;
	Button PvP("", { 288, 80 }, 40, Color::Cyan, Color::Black, 3, Color::Black);
	Button Settings("", { 288, 80 }, 40, Color::Cyan, Color::Black, 3, Color::Black);

	PvP.setPosition({ 106,107.5 });
	Settings.setPosition({ 106,322.5 });

	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");

	PvP.setFont(font);
	Settings.setFont(font);

	Text textPvP, textSettings;
	textPvP = Text(L"Играть", font, 40);
	textPvP.setPosition(180, 117.5);
	textPvP.setStyle(Text::Bold);
	textPvP.setFillColor(Color::Black);

	textSettings = Text(L"Настройки", font, 40);
	textSettings.setPosition(146, 332.5);
	textSettings.setStyle(Text::Bold);
	textSettings.setFillColor(Color::Black);

	while (workWindow.isOpen()) {
		Event event;
		while (workWindow.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				workWindow.close();
			case Event::MouseMoved:
				if (PvP.isMouseOver(workWindow))
					PvP.setBackColor(Color(247, 255, 0));
				else
					PvP.setBackColor(Color::Cyan);

				if (Settings.isMouseOver(workWindow))
					Settings.setBackColor(Color(247, 255, 0));
				else
					Settings.setBackColor(Color::Cyan);
				break;
			case Event::MouseButtonPressed:
				if (PvP.isMouseOver(workWindow))
				{
					PvPGame(settings);
				}

				if (Settings.isMouseOver(workWindow))//открытие окна настроек
				{
					checker_settings(settings);
				}
				break;

			default:
				break;
			}
		}

		workWindow.clear(Color(245, 210, 175));
		PvP.DrawTo(workWindow);
		Settings.DrawTo(workWindow);
		workWindow.draw(textPvP);
		workWindow.draw(textSettings);
		workWindow.display();
	}
	return 0;
}
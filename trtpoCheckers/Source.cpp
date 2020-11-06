#include"GameProces.h"
#include"Settings.h"
#include"MyHeader.h"


int main()
{
	setlocale(LC_ALL, "rus");

	ContextSettings settings;
	settings.antialiasingLevel = 20;//сглаживание

	WorkWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
	Image icon;
	if (!icon.loadFromFile("Images/icon.png"))
		exit(1);
	WorkWindow.setIcon(32, 32, icon.getPixelsPtr());

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
	textPvP = Text(L"Игра с другом", font, 40);
	textPvP.setPosition(116, 117.5);
	textPvP.setStyle(Text::Bold);
	textPvP.setFillColor(Color::Black);

	textSettings = Text(L"Настройки", font, 40);
	textSettings.setPosition(146, 332.5);
	textSettings.setStyle(Text::Bold);
	textSettings.setFillColor(Color::Black);

	while (WorkWindow.isOpen()) {
		Event event;
		while (WorkWindow.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				WorkWindow.close();
			case Event::MouseMoved:
				if (PvP.isMouseOver(WorkWindow))
					PvP.setBackColor(Color(247, 255, 0));
				else
					PvP.setBackColor(Color::Cyan);

				if (Settings.isMouseOver(WorkWindow))
					Settings.setBackColor(Color(247, 255, 0));
				else
					Settings.setBackColor(Color::Cyan);
				break;
			case Event::MouseButtonPressed:
				if (PvP.isMouseOver(WorkWindow))
				{
					PvPGame(settings);
				}

				if (Settings.isMouseOver(WorkWindow))//открытие окна настроек
				{
					CheckerSettings(settings);
				}
				break;

			default:
				break;
			}
		}

		WorkWindow.clear(Color(245, 210, 175));
		PvP.DrawTo(WorkWindow);
		Settings.DrawTo(WorkWindow);
		WorkWindow.draw(textPvP);
		WorkWindow.draw(textSettings);
		WorkWindow.display();
	}
	return 0;
}
#pragma once
#include"MyHeader.h"

class Button {
public:
	Button() {}
	Button(string BattonText, Vector2f size, int charSize, Color ButtonColor, Color TextColor, int border, Color OutLineColor) {
		text.setString(BattonText);
		text.setFillColor(TextColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setFillColor(ButtonColor);
		button.setOutlineThickness(border);
		button.setOutlineColor(OutLineColor);
	}
	void setFont(Font& font) {
		text.setFont(font);
	}

	void setBackColor(Color color)
	{
		button.setFillColor(color);
	}

	void setTextColor(Color color)
	{
		text.setFillColor(color);
	}
	void setPosition(Vector2f pos)
	{
		button.setPosition(pos);

		float xPos = (pos.x + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 2);
		float yPos = (pos.y + button.getGlobalBounds().height / 40) - (text.getGlobalBounds().height / 1);
		text.setPosition({ xPos,yPos });
	}
	void setPositionText(Vector2f pos)// special settings
	{
		float xPos = (pos.x + button.getGlobalBounds().width / 8) - (text.getGlobalBounds().width / 5);
		float yPos = (pos.y + button.getGlobalBounds().height / 40) - (text.getGlobalBounds().height / 1);
		text.setPosition({ xPos,yPos });
	}
	void DrawTo(RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}
	bool isMouseOver(RenderWindow& window) {
		float MouseX = Mouse::getPosition(window).x;
		float MouseY = Mouse::getPosition(window).y;

		float ButtonPosX = button.getPosition().x;
		float ButtonPosY = button.getPosition().y;

		float ButtonPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float ButtonPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (MouseX < ButtonPosWidth && MouseX> ButtonPosX && MouseY<ButtonPosHeight && MouseY> ButtonPosY)
			return true;
		return false;
	}
private:
	RectangleShape button;
	Text text;
};


void regulations_windows(ContextSettings& settings)
{
	setlocale(LC_ALL, "rus");

	RenderWindow RegulationsWindow(VideoMode(600, 550), L"Правила игры Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
	Image icon;
	icon.loadFromFile("Images/icon.png");
	RegulationsWindow.setIcon(32, 32, icon.getPixelsPtr());

	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	Text text[13];
	text[0] = Text(L"Правила:", font, 30);
	text[0].setPosition(25, 25);

	text[1] = Text(L"1-Существует только два вида шашек:", font, 25);
	text[1].setPosition(25, 75);

	text[2] = Text(L"простые и дамки.", font, 25);
	text[2].setPosition(25, 110);

	text[3] = Text(L"2-В начале партии все шашки простые.", font, 25);
	text[3].setPosition(25, 145);

	text[4] = Text(L"3-Простая шашка может превратиться в ", font, 25);
	text[4].setPosition(25, 180);

	text[5] = Text(L"дамку, если она достигнет последнего", font, 25);
	text[5].setPosition(25, 215);

	text[6] = Text(L"противоположного горизонтального ряда", font, 25);
	text[6].setPosition(25, 250);

	text[7] = Text(L"доски.", font, 25);
	text[7].setPosition(25, 285);

	text[8] = Text(L"4-Простые шашки ходят вперёд на следующее ", font, 25);
	text[8].setPosition(25, 320);

	text[9] = Text(L"поле, назад, только если надо взять шашку.", font, 25);
	text[9].setPosition(25, 355);

	text[10] = Text(L"Дамки могут ходить и вперёд и назад.", font, 25);
	text[10].setPosition(25, 390);

	text[11] = Text(L"5-Брать шашку, находящуюся под боем", font, 25);
	text[11].setPosition(25, 425);

	text[12] = Text(L"обязательно.", font, 25);
	text[12].setPosition(25, 460);


	for (int i = 0; i < 13; i++)
	{
		text[i].setFillColor(Color::Black);
	}

	while (RegulationsWindow.isOpen()) {
		Event event;
		while (RegulationsWindow.pollEvent(event))
			if (event.type == Event::Closed)
			{
				RegulationsWindow.close();
			}


		RegulationsWindow.clear(Color(245, 210, 175));


		for (int i = 0; i < 13; i++)
		{
			RegulationsWindow.draw(text[i]);
		}
		RegulationsWindow.display();
	}
}
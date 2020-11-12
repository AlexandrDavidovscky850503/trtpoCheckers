#pragma once
#include"MyHeader.h"
#include"GameProces.h"
#include"Checker.h"
#include"Tool.h"


void QueenImage(int NumberQueen)
{
	Texture TextureWhite, TextureBlack;
	if (NumberQueen == 1) {
		texture_white.loadFromFile("Images//01.png");
		texture_black.loadFromFile("Images//011.png");

	}
	if (NumberQueen == 2) {
		texture_white.loadFromFile("Images//02.png");
		texture_black.loadFromFile("Images//022.png");

	}
	if (NumberQueen == 3) {
		texture_white.loadFromFile("Images//03.png");
		texture_black.loadFromFile("Images//03.png");

	}
	if (NumberQueen == 4) {
		texture_white.loadFromFile("Images//04.png");
		texture_black.loadFromFile("Images//044.png");
	}
	if (NumberQueen == 5) {
		texture_white.loadFromFile("Images//0999.png");
		texture_black.loadFromFile("Images//0999.png");

	}
}
void CheckerImages(RenderWindow& window, CircleShape& CheckerWhite, CircleShape& CheckerBlack, int NumberQueen)
{
	Texture TextureWhite, TextureBlack;
	Sprite SpriteWhite, SpriteBlack;
	if (NumberQueen == 1) {
		TextureWhite.loadFromFile("Images//1.png");
		TextureBlack.loadFromFile("Images//11.png");
		SpriteWhite.setTexture(TextureWhite);
		SpriteBlack.setTexture(TextureBlack);
		SpriteWhite.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteBlack.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteWhite.setPosition({ 134,180 });
		SpriteBlack.setPosition({ 262,180 });
	}
	if (NumberQueen == 2) {
		TextureWhite.loadFromFile("Images//2.png");
		TextureBlack.loadFromFile("Images//22.png");
		SpriteWhite.setTexture(TextureWhite);
		SpriteBlack.setTexture(TextureBlack);
		SpriteWhite.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteBlack.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteWhite.setPosition({ 134,177 });
		SpriteBlack.setPosition({ 262,177 });
	}
	if (NumberQueen == 3) {
		TextureWhite.loadFromFile("Images//3.png");
		TextureBlack.loadFromFile("Images//3.png");
		SpriteWhite.setTexture(TextureWhite);
		SpriteBlack.setTexture(TextureBlack);
		SpriteWhite.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteBlack.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteWhite.setPosition({ 134,180 });
		SpriteBlack.setPosition({ 262,180 });
	}
	if (NumberQueen == 4) {
		TextureWhite.loadFromFile("Images//4.png");
		TextureBlack.loadFromFile("Images//44.png");
		SpriteWhite.setTexture(TextureWhite);
		SpriteBlack.setTexture(TextureBlack);
		SpriteWhite.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteBlack.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteWhite.setPosition({ 134,170 });
		SpriteBlack.setPosition({ 262,170 });
	}
	if (NumberQueen == 5) {
		TextureWhite.loadFromFile("Images//999.png");
		TextureBlack.loadFromFile("Images//999.png");
		SpriteWhite.setTexture(TextureWhite);
		SpriteBlack.setTexture(TextureBlack);
		SpriteWhite.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteBlack.setTextureRect(IntRect(0, 0, 100, 100));
		SpriteWhite.setPosition({ 134,170 });
		SpriteBlack.setPosition({ 262,170 });
	}
	window.draw(SpriteWhite);
	window.draw(SpriteBlack);
}

void CheckerSettings(ContextSettings& settings)
{
	ifImage = true;

	WorkWindow.create(VideoMode(500, 500), "Checker", sf::Style::Close | sf::Style::Titlebar, settings);
	CircleShape CheckerBlack = CircleShape(54);
	CircleShape CheckerWhite = CircleShape(54);
	CheckerBlack.setPosition({ 258,173 });
	CheckerWhite.setPosition({ 130,173 });

	CheckerBlack.setOutlineThickness(5);
	CheckerBlack.setOutlineColor(Color::Black);

	CheckerWhite.setOutlineThickness(5);
	CheckerWhite.setOutlineColor(Color::Black);
	CheckerBlack.setFillColor(Color::Black);

	sf::Texture textureR, textureL, textureMusik;
	textureR.loadFromFile("Images/lol1.png");
	textureL.loadFromFile("Images/lol2.png");


	Sprite SpLeft, SpRight, SpriteMusik;

	SpLeft.setTexture(textureL);
	SpLeft.setTextureRect(IntRect(0, 0, 50, 50));
	SpLeft.setPosition({ 50,200 });



	SpRight.setTexture(textureR);
	SpRight.setTextureRect(IntRect(0, 0, 50, 50));
	SpRight.setPosition({ 400,200 });

	Button ButtonCheckerRight("", { 50,50 }, 40, Color::Cyan, Color::Black, 3, Color::Black);
	Button ButtonCheckerLeft("", { 50,50 }, 40, Color::Cyan, Color::Black, 3, Color::Black);
	Button Save("", { 240,50 }, 40, Color::Cyan, Color::Black, 3, Color::Black);

	ButtonCheckerRight.setPosition({ 400,200 });
	ButtonCheckerLeft.setPosition({ 50,200 });
	Save.setPosition({ 130,380 });

	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	ButtonCheckerRight.setFont(font);
	ButtonCheckerLeft.setFont(font);
	Save.setFont(font);

	Text TextLine1, TextLine2, SaveText;
	TextLine1 = Text("", font, 40);
	TextLine1.setPosition(70, 30);
	TextLine1.setStyle(Text::Bold);
	TextLine1.setString(L"Выберите корону");
	TextLine1.setFillColor(Color::Black);

	TextLine2 = Text("", font, 40);
	TextLine2.setPosition(180, 80);
	TextLine2.setStyle(Text::Bold);
	TextLine2.setString(L"дамки");
	TextLine2.setFillColor(Color::Black);

	SaveText = Text("", font, 40);
	SaveText.setPosition(145, 380);
	SaveText.setStyle(Text::Bold);
	SaveText.setString(L"Сохранить");
	SaveText.setFillColor(Color::Black);

	Image icon;
	icon.loadFromFile("Images/icon.png");

	WorkWindow.setIcon(32, 32, icon.getPixelsPtr());

	while (WorkWindow.isOpen()) {
		Event event;
		while (WorkWindow.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				WorkWindow.close();

			case Event::MouseMoved:
				if (ButtonCheckerRight.isMouseOver(WorkWindow))
					ButtonCheckerRight.setBackColor(Color(247, 255, 0));
				else
					ButtonCheckerRight.setBackColor(Color::Cyan);
				if (ButtonCheckerLeft.isMouseOver(WorkWindow))
					ButtonCheckerLeft.setBackColor(Color(247, 255, 0));
				else
					ButtonCheckerLeft.setBackColor(Color::Cyan);
				if (Save.isMouseOver(WorkWindow))
					Save.setBackColor(Color(247, 255, 0));
				else
					Save.setBackColor(Color::Cyan);

				break;
			case Event::MouseButtonPressed:
				if (ButtonCheckerRight.isMouseOver(WorkWindow))
				{
					NumberImage++;
					if (NumberImage > 5)
						NumberImage = 1;
				}
				if (ButtonCheckerLeft.isMouseOver(WorkWindow))
				{
					NumberImage--;
					if (NumberImage < 1)
						NumberImage = 5;
				}
				if (Save.isMouseOver(WorkWindow))
				{
					QueenImage(NumberImage);
					WorkWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
					WorkWindow.setIcon(32, 32, icon.getPixelsPtr());
					return;
				}

				break;
			default:
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			Sleep(150);
			NumberImage++;
			if (NumberImage > 5)
				NumberImage = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			Sleep(150);
			NumberImage--;
			if (NumberImage < 1)
				NumberImage = 5;
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			Sleep(150);
			QueenImage(NumberImage);
			WorkWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
			WorkWindow.setIcon(32, 32, icon.getPixelsPtr());
			return;
		}

		WorkWindow.clear(Color(245, 210, 175));


		ButtonCheckerRight.DrawTo(WorkWindow);
		ButtonCheckerLeft.DrawTo(WorkWindow);
		Save.DrawTo(WorkWindow);
		WorkWindow.draw(TextLine1);
		WorkWindow.draw(TextLine2);
		WorkWindow.draw(SaveText);

		WorkWindow.draw(SpLeft);
		WorkWindow.draw(SpRight);
		WorkWindow.draw(CheckerBlack);
		WorkWindow.draw(CheckerWhite);

		CheckerImages(WorkWindow, CheckerWhite, CheckerBlack, NumberImage);
		WorkWindow.display();
	}
}
#pragma once
#include"MyHeader.h"
#include"GameProces.h"
#include"Checker.h"
#include"Tool.h"


void queen_image(int NumberQueen)
{
	Texture TextureWhite, TextureBlack;
	if (NumberQueen == 1) {
		textureWhite.loadFromFile("Images//01.png");
		textureBlack.loadFromFile("Images//011.png");

	}
	if (NumberQueen == 2) {
		textureWhite.loadFromFile("Images//02.png");
		textureBlack.loadFromFile("Images//022.png");

	}
	if (NumberQueen == 3) {
		textureWhite.loadFromFile("Images//03.png");
		textureBlack.loadFromFile("Images//03.png");

	}
	if (NumberQueen == 4) {
		textureWhite.loadFromFile("Images//04.png");
		textureBlack.loadFromFile("Images//044.png");
	}
	if (NumberQueen == 5) {
		textureWhite.loadFromFile("Images//0999.png");
		textureBlack.loadFromFile("Images//0999.png");

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

void checker_settings(ContextSettings& settings)
{
	ifImage = true;

	workWindow.create(VideoMode(500, 500), "Checker", sf::Style::Close | sf::Style::Titlebar, settings);
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

	workWindow.setIcon(32, 32, icon.getPixelsPtr());

	while (workWindow.isOpen()) {
		Event event;
		while (workWindow.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				workWindow.close();

			case Event::MouseMoved:
				if (ButtonCheckerRight.isMouseOver(workWindow))
					ButtonCheckerRight.setBackColor(Color(247, 255, 0));
				else
					ButtonCheckerRight.setBackColor(Color::Cyan);
				if (ButtonCheckerLeft.isMouseOver(workWindow))
					ButtonCheckerLeft.setBackColor(Color(247, 255, 0));
				else
					ButtonCheckerLeft.setBackColor(Color::Cyan);
				if (Save.isMouseOver(workWindow))
					Save.setBackColor(Color(247, 255, 0));
				else
					Save.setBackColor(Color::Cyan);

				break;
			case Event::MouseButtonPressed:
				if (ButtonCheckerRight.isMouseOver(workWindow))
				{
					numberImage++;
					if (numberImage > 5)
						numberImage = 1;
				}
				if (ButtonCheckerLeft.isMouseOver(workWindow))
				{
					numberImage--;
					if (numberImage < 1)
						numberImage = 5;
				}
				if (Save.isMouseOver(workWindow))
				{
					queen_image(numberImage);
					workWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
					workWindow.setIcon(32, 32, icon.getPixelsPtr());
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
			numberImage++;
			if (numberImage > 5)
				numberImage = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			Sleep(150);
			numberImage--;
			if (numberImage < 1)
				numberImage = 5;
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			Sleep(150);
			queen_image(numberImage);
			workWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
			workWindow.setIcon(32, 32, icon.getPixelsPtr());
			return;
		}

		workWindow.clear(Color(245, 210, 175));


		ButtonCheckerRight.DrawTo(workWindow);
		ButtonCheckerLeft.DrawTo(workWindow);
		Save.DrawTo(workWindow);
		workWindow.draw(TextLine1);
		workWindow.draw(TextLine2);
		workWindow.draw(SaveText);

		workWindow.draw(SpLeft);
		workWindow.draw(SpRight);
		workWindow.draw(CheckerBlack);
		workWindow.draw(CheckerWhite);

		CheckerImages(workWindow, CheckerWhite, CheckerBlack, numberImage);
		workWindow.display();
	}
}
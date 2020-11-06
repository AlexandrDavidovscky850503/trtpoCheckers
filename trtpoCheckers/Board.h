#pragma once
#include "Square.h"
#include"MyHeader.h"


class Board {
private:
	Square all_squares[8][8];
	RectangleShape rectangle;

public:
	Board() {}
	Square& get_all_squares(int _i, int _j) {
		if (_i >= 0 && _j >= 0 && _i < 8 && _j < 8)
			return this->all_squares[_i][_j];
		throw 1;
	}

	void draw_board(RenderWindow& _window) {	//отрисовка доски

		// определяем прямоугольник размером 
		rectangle.setSize(Vector2f{ 400,400 });
		rectangle.setFillColor(sf::Color(0, 50, 250));
		// задаём контур толщиной 5 пикселей 
		rectangle.setOutlineThickness(5);
		rectangle.setOutlineColor(sf::Color(0, 0, 0));
		rectangle.setPosition(50, 50);
		_window.draw(rectangle);

		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(50 * i, 50 * j);//сохранить координаты клетки  
				if ((i + j) % 2 == 1)
					all_squares[i - 1][j - 1].set_color(Color(255, 255, 255));//белая клетка
				else
					all_squares[i - 1][j - 1].set_color(Color(174, 87, 0));// коричневая клетка
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}


		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_backlight() == 1) {
					RectangleShape square_light(Vector2f(50, 50));
					square_light.setPosition(50 * i, 50 * j);
					all_squares[i - 1][j - 1].set_color(Color(26, 255, 0));//подсветка зелёным цветом
				}
				_window.draw(all_squares[i - 1][j - 1].get_square());
			}

		Font font;//шрифт
		font.loadFromFile("Font//bahnschrift.ttf");//подгрузка шрифта
		Text* t[16];
		for (int i = 0; i < 16; i++)
			t[i] = new Text("", font, 35);

		t[0]->setString(L"1");	//L-расширенные строковые литералы
		t[1]->setString(L"2");
		t[2]->setString(L"3");
		t[3]->setString(L"4");
		t[4]->setString(L"5");
		t[5]->setString(L"6");
		t[6]->setString(L"7");
		t[7]->setString(L"8");
		t[8]->setString(L"А");
		t[9]->setString(L"B");
		t[10]->setString(L"C");
		t[11]->setString(L"D");
		t[12]->setString(L"E");
		t[13]->setString(L"F");
		t[14]->setString(L"G");
		t[15]->setString(L"H");
		for (int i = 0; i < 8; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition(15, i * 50 + 50);
			_window.draw(*t[i]);
			t[i]->setPosition(465, i * 50 + 50);
			_window.draw(*t[i]);
		}
		for (int i = 8; i < 16; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition((i - 8) * 50 + 60, 5);
			_window.draw(*t[i]);
			t[i]->setPosition((i - 8) * 50 + 60, 455);
			_window.draw(*t[i]);
		}
		for (int i = 0; i < 16; i++)
			delete t[i];
	}
};
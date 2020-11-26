#pragma once
#include"MyHeader.h"

class Square {
private:
	bool backlight = 0;	// подсветка 0 если нет, 1 если есть.
	bool employment = 0;// 0 для свободных, 1 для занятых.//0-cleaar,1-white,2-black
	bool checkerColor = 0;	// 0 для белых, 1 для черных.
	RectangleShape square = RectangleShape(Vector2f(50, 50));//создание об. квадрат
public:
	Square() {}

	RectangleShape& get_square() {
		return this->square;
	}
	bool get_backlight() {					//получить подсветку
		return this->backlight;
	}
	bool get_employment() {					//получить занятость клетки
		return this->employment;
	}
	bool get_checker_color() {				//получить цвет шашки
		return this->checkerColor;
	}

	void on_backlight() {					//включить подсветку
		this->backlight = 1;
	}
	void off_backlight() {					//выключить подсветку
		this->backlight = 0;
	}

	void square_employment(bool _color) {	//клетка занята
		this->employment = 1;
		this->checkerColor = _color;
	}

	void square_free() {					//клетка свободна
		this->employment = 0;
	}


	void set_color(Color _color) {			//сохранить цвет клетки
		this->square.setFillColor(_color);
	}

	void set_position(float _x, float _y) {	//сохранить координаты
		this->square.setPosition(_x, _y);
	}

	bool get_square_employment()
	{
		return this->checkerColor;
	}
};
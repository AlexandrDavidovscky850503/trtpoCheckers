#pragma once
#include"Tool.h"
#include"MyHeader.h"

class Checker {
private:
	CircleShape checker = CircleShape(18);// определяем круг с радиусом 18
	bool checker_color;// 0 для белых, 1 для черных
	bool select = 0;//1 если выбрана, 0 если нет
	bool queen = 0;//1 если шашка дамка, 0 если нет
	Texture texture;//текстура значка дамки
	Sprite sprite;


public:
	CircleShape& get_checker() {//получить шашку
		return this->checker;
	}
	Vector2f get_position() {// получить координаты
		return this->checker.getPosition();
	}
	float get_x() {//получить координату X
		return (this->get_position().x - 57) / 50;
	}
	float get_y() {//получить координату Y
		return (this->get_position().y - 57) / 50;
	}
	bool get_color() {// получить цвет шашки
		return this->checker_color;
	}
	bool get_select() {//получить состояние шашки
		return this->select;
	}
	bool get_queen() {//получить ранг шашки
		return this->queen;
	}


	void make_queen() {//изменение ранга
		this->queen = 1;
	}
	void set_position(float x_positinon, float y_position) {//сохранить координаты шашки
		this->checker.setPosition(x_positinon, y_position);
	}
	void set_color(Color color) {//сохранить цвет шашки
		this->checker.setFillColor(color);
	}
	void select_checker() {//выбор фигуры
		this->select = 1;
	}
	void leave_checker() {//отмена выбора фигуры
		this->select = 0;
	}

	Checker() { }

	Checker(float x_position, float y_position, bool color) {
		this->checker.setOutlineThickness(3);// задаём контур толщиной 3 пикселей чёрного цвета
		this->checker.setOutlineColor(sf::Color(0, 0, 0));
		this->checker_color = color;

		if (color == 0)
			this->set_color(Color(255, 255, 255));//белая шашка
		else if (color == 1)
			//this->set_color(Color(61, 25, 7));//чёреая шашка
			this->set_color(Color::Black);

		this->set_position(x_position, y_position);
		this->select = 0;
	}

	void draw_checker(RenderWindow& _window) {// отрисовка шашки
		_window.draw(this->checker);
		if (queen == 1)
			if (ifImage == false)
			{
				texture_white.loadFromFile("Images//01.png");
				texture_black.loadFromFile("Images//011.png");
				if (checker_color == 0)
					this->sprite.setTexture(texture_white);
				else
					this->sprite.setTexture(texture_black);
			}
			else
			{
				if (checker_color == 0)
					this->sprite.setTexture(texture_white);
				else
					this->sprite.setTexture(texture_black);
			}
		this->sprite.setTextureRect(IntRect(0, 0, 25, 25));
		sprite.setPosition(this->get_position().x + 6, this->get_position().y + 6);
		_window.draw(this->sprite);
	}

	Checker operator = (Checker _checker) {
		this->texture = _checker.texture;
		this->sprite = _checker.sprite;
		this->select = _checker.select;
		this->queen = _checker.queen;
		this->checker_color = _checker.checker_color;

		if (_checker.checker_color == 0)
			this->set_color(Color(255, 255, 255));
		else if (_checker.checker_color == 1)
			this->set_color(Color::Black);

		this->set_position(_checker.get_position().x, _checker.get_position().y);
		return (*this);
	}
};
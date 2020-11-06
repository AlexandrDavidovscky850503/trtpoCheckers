#pragma once
#include"MyHeader.h"

class Square {
private:
	bool backlight = 0;	// ��������� 0 ���� ���, 1 ���� ����.
	bool employment = 0;// 0 ��� ���������, 1 ��� �������.//0-cleaar,1-white,2-black
	//int game_chackers = 0;
	bool checker_color = 0;	// 0 ��� �����, 1 ��� ������.
	RectangleShape square = RectangleShape(Vector2f(50, 50));//�������� ��. �������
public:
	Square() {}

	RectangleShape& get_square() {
		return this->square;
	}
	bool get_backlight() {					//�������� ���������
		return this->backlight;
	}
	bool get_employment() {					//�������� ��������� ������
		return this->employment;
	}
	bool get_checker_color() {				//�������� ���� �����
		return this->checker_color;
	}

	void on_backlight() {					//�������� ���������
		this->backlight = 1;
	}
	void off_backlight() {					//��������� ���������
		this->backlight = 0;
	}

	void square_employment(bool _color) {	//������ ������
		this->employment = 1;
		this->checker_color = _color;
	}

	void square_free() {					//������ ��������
		this->employment = 0;
	}


	void set_color(Color _color) {			//��������� ���� ������
		this->square.setFillColor(_color);
	}

	void set_position(float _x, float _y) {	//��������� ����������
		this->square.setPosition(_x, _y);
	}



	bool get_square_employment()
	{
		return this->checker_color;
	}
};
#pragma once
#include"MyHeader.h"
#include"CheckerOnBoard.h"
#include"Tool.h"


class Game {
private:
	bool who_can_move = 0;//цвет хода, 0 если ход белых, 1 если ход черных
	bool select_is_made = 0;//0 если фигуры не выбрана, 1 если выбрана
	int choise_chacker;//номер выбранной для хода шашки
	float x;//номер клетки в которой шашка по оси х
	float y;//номер клетки в которой шашка по оси у
	Vector2i mause_position;//позиция мыши
	Checkers_on_board checkers_on_board;
	vector <int> who_must_eat;//храню шашки, которые могут съесть
public:
	Checkers_on_board& get_checkers_on_board() {
		return this->checkers_on_board;
	}
	void set_mause_position(RenderWindow& _window) {
		this->mause_position = Mouse::getPosition(_window);
	}
	Vector2i centre_on_square() {//
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (mause_position.x < i * 50 + 100 && mause_position.x < (i + 1) * 50 + 100 && mause_position.y < j * 50 + 100 && mause_position.y < (j + 1) * 50 + 100)
					return Vector2i(i * 50 + 57, j * 50 + 57);
	}

	bool get_who_can_move()
	{
		return this->who_can_move;
	}

	void choise_of_chacker(RenderWindow& _window, Event _event) {//выбор шашки
		if (_event.type == sf::Event::MouseButtonPressed)
			if (_event.key.code == Mouse::Left) {
				set_mause_position(_window);
				if (_event.type == sf::Event::MouseButtonPressed)//для отмены взятия фигуры
				{
					set_mause_position(_window);
					if (_event.key.code == Mouse::Left && !checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight())
						if (checkers_on_board.get_checker(choise_chacker).get_select() == 1 && select_is_made == 1) {
							checkers_on_board.get_checker(choise_chacker).leave_checker();
							select_is_made = 0;
							std::cout << "Drop" << endl;
							checkers_on_board.delete_backlight();
							return;
						}
				}

				for (int i = 0; i < checkers_on_board.get_size(); i++)
					if (this->mause_position.x >= checkers_on_board.get_checker(i).get_position().x - 7 &&
						this->mause_position.x <= checkers_on_board.get_checker(i).get_position().x + 43 &&
						this->mause_position.y >= checkers_on_board.get_checker(i).get_position().y - 7 &&
						this->mause_position.y <= checkers_on_board.get_checker(i).get_position().y + 43)
						if (checkers_on_board.get_checker(i).get_select() == 0 && select_is_made == 0)
							if (checkers_on_board.get_checker(i).get_color() == who_can_move) {
								if (if_you_can_eat_you_must_eat(checkers_on_board.get_checker(i).get_color())) {//проверка на обязательный ход какой то конкретной шашки
									int s = 0;
									for (int f : who_must_eat)
										if (f == i)
											s++;

									if (s == 0) {
										error_choise_checker(_window, _event);
										checkers_on_board.delete_backlight();
										return;
									}
								}
								choise_chacker = i;
								select_is_made = 1;
								checkers_on_board.get_checker(choise_chacker).select_checker();
								std::cout << "Take" << endl;
								x = checkers_on_board.get_checker(choise_chacker).get_x();
								y = checkers_on_board.get_checker(choise_chacker).get_y();
								if (checkers_on_board.get_checker(choise_chacker).get_queen())
									queen_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color(), 1, 1, 1, 1);
								else
									square_for_move();
								return;
							}
			}

	}


	void change_position(RenderWindow& _window, Event _event) {//ход шашки

		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left)  //// _event.key.code == Mouse::Right
				if (checkers_on_board.get_checker(choise_chacker).get_select() == 1 && select_is_made == 1) {
					set_mause_position(_window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) {
						checkers_on_board.get_board().get_all_squares(x, y).square_free();
						if (checkers_on_board.get_checker(choise_chacker).get_queen() == 1) {
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkers_on_board.delete_backlight();
								if (queen_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color(), 1, 1, 1, 1)) {
									cout << "loop" << endl;

									return;
								}
							}
						}
						else {
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();

							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (checkers_on_board.get_checker(choise_chacker).get_queen() == 1) {
									checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkers_on_board.get_checker(choise_chacker).get_color());
									who_can_move = !who_can_move;
									checkers_on_board.get_checker(choise_chacker).leave_checker();
									select_is_made = 0;
									std::cout << "Drop" << endl;

									checkers_on_board.delete_backlight();
									return;
								}

								if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						checkers_on_board.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkers_on_board.get_checker(choise_chacker).get_color());
						who_can_move = !who_can_move;
						checkers_on_board.get_checker(choise_chacker).leave_checker();
						select_is_made = 0;
						std::cout << "Drop" << endl;

						checkers_on_board.delete_backlight();
						return;
					}
				}
		}
	}


	void make_move(RenderWindow& _window, Event _event) {
		choise_of_chacker(_window, _event);//проверка выбора шашки
		change_position(_window, _event);//ход шашки
	}

	void square_for_move() {//варианты хода
		if (checkers_on_board.get_checker(choise_chacker).get_color()) {
			if (x + 1 >= 0 && y + 1 < 8 && x + 1 < 8 && y + 1 >= 0 && checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0)
				if (end_board(x + 1, y + 1))
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_backlight();


			if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0)
				if (end_board(x - 1, y + 1))
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).on_backlight();
		}
		else {
			if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0)
				if (end_board(x + 1, y - 1))
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_backlight();


			if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0)
				if (end_board(x - 1, y - 1))
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_backlight();


		}
		if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {//варианты съесть шашку
			checkers_on_board.delete_backlight();
			chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color());
		}
	}
	bool chance_eat_checker(bool _color) {//варианты съесть шашку
		bool more = 1;
		if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_employment()) // проверяем правый нижний ход шашки
			if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x + 2 >= 0 && x + 2 < 8 && y + 2 >= 0 && y + 2 < 8 && checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x + 2, y + 2)) {// если не конец доски
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}


		if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_employment()) // проверяем левый нижний ход шашки
			if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x - 2 >= 0 && y + 2 < 8 && x - 2 < 8 && y + 2 >= 0 && checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}


		if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_employment()) // проверяем правый верхний ход шашки
			if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x + 2 >= 0 && y - 2 < 8 && x + 2 < 8 && y - 2 >= 0 && checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}


		if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_employment()) // проверяем левый верхний ход шашки
			if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x - 2 >= 0 && y - 2 < 8 && x - 2 < 8 && y - 2 >= 0 && checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
		return more;
	}

	bool eat_checker() {//ем шашку
		if ((centre_on_square().x - 57) / 50 - x == 2 || (centre_on_square().x - 57) / 50 - x == -2 &&
			(centre_on_square().y - 57) / 50 - y == 2 || (centre_on_square().y - 57) / 50 - y == -2)
			for (int i = 0; i < checkers_on_board.get_size(); i++)
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(choise_chacker).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(choise_chacker).get_y() - y) / 2) {
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++)
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);

					checkers_on_board.delete_checker();
					if (i < choise_chacker)
						choise_chacker = choise_chacker - 1;

					return 1;
				}
		return 0;
	}

	void make_queen() {
		if (checkers_on_board.get_checker(choise_chacker).get_color() == 0)
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 0) {
				checkers_on_board.get_checker(choise_chacker).make_queen();
			//	who_can_move = !who_can_move;
			}


		if (checkers_on_board.get_checker(choise_chacker).get_color() == 1)
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 7) {
				checkers_on_board.get_checker(choise_chacker).make_queen();
			//	who_can_move = !who_can_move;
			}


	}
	bool queen_square_for_move(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
		int must_eat = 0;
		int i_line_number_eat[4] = { 0,0,0,0 };

		bool can_eat[4] = { _i1, _i2, _i3, _i4 };
		checkers_on_board.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) { // низ право
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == _color)
							break;

						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_employment() == 0) {
									if (i_line_number_eat[0] > 0)
									{
										break;
									}
									i_line_number_eat[0] += 1;
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen + 1)) { // низ лево
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_employment() == 0) {
									if (i_line_number_eat[1] > 0)
									{
										break;
									}
									i_line_number_eat[1] += 1;
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[1] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen + 1, y_queen - 1)) {//верх право
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_employment() == 0) {
									if (i_line_number_eat[2] > 0)
									{
										break;
									}
									i_line_number_eat[2] += 1;
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_backlight();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_backlight();
						x_queen = x_queen + 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_employment() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_employment() == 0) {
									if (i_line_number_eat[3] > 0)
									{
										break;
									}
									i_line_number_eat[3] += 1;
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_backlight();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_backlight();
						x_queen = x_queen - 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0) {
			return 0;
		}
		else {
			if (_i1 == 1 && _i2 == 1 && _i3 == 1 && _i4 == 1) {
				queen_square_for_move(_color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);
			}
			else return 1;
		}
	}
	bool queen_eat_checker() {//ем шашку
		int x_eat = 0;
		int y_eat = 0;
		if ((centre_on_square().x - 57) / 50 - x >= 2 && (centre_on_square().y - 57) / 50 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j + 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		if ((centre_on_square().x - 57) / 50 - x >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 57) / 50 - 1 && j >(centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j - 1).get_employment() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && (centre_on_square().y - 57) - y / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j < (centre_on_square().y - 57) / 50 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j + 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 57) / 50 >= 2 && y - (centre_on_square().y - 57) / 50 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 57) / 50 + 1 && j > (centre_on_square().y - 57) / 50 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j - 1).get_employment() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}

		for (int f = 0; f < checkers_on_board.get_size(); f++) {
			if (checkers_on_board.get_checker(f).get_x() == x_eat && checkers_on_board.get_checker(f).get_y() == y_eat) {
				checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(f).get_x(), checkers_on_board.get_checker(f).get_y()).square_free();

				for (int c = f; c < checkers_on_board.get_size() - 1; c++) {
					checkers_on_board.get_checker(c) = checkers_on_board.get_checker(c + 1);
				}
				checkers_on_board.delete_checker();
				if (f < choise_chacker) {
					choise_chacker = choise_chacker - 1;
				}
				return 1;
			}
		}
		return 0;
	}

	bool end_board(float _x, float _y) {//проверка выходы за пределы поля
		if (_x >= 0 && _x < 8 && _y >= 0 && _y < 8) {
			return 1;
		}
		return 0;
	}

	bool if_you_can_eat_you_must_eat(bool _color) {
		while (who_must_eat.size() != 0)//освобождаем место под новые шашки которые могут съесть
			who_must_eat.pop_back();

		for (int i = 0; i < checkers_on_board.get_size(); i++)
			if (checkers_on_board.get_checker(i).get_color() == _color) {
				if (checkers_on_board.get_checker(i).get_queen() == 0) {// обычная шашка
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (!chance_eat_checker(_color))
						who_must_eat.push_back(i);

				}
				if (checkers_on_board.get_checker(i).get_queen() == 1) {//дамка
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (queen_square_for_move(_color, 1, 1, 1, 1))
						who_must_eat.push_back(i);

				}
			}

		checkers_on_board.delete_backlight();
		if (who_must_eat.size() != 0) return 1;
		else return 0;
	}
	void error_choise_checker(RenderWindow& _window, Event _event) {
		while (1) {
			RectangleShape back = RectangleShape(Vector2f(270, 50));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(165, 225);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 25);
			t.setString(L"Нужно скушать шашку");
			t.setFillColor(Color::Black);
			t.setPosition(172, 235);
			Text out = Text("", font, 11);
			out.setString(L"нажмите что-то для продолжения");
			out.setFillColor(Color::Black);
			out.setPosition(173, 260);
			_window.draw(back);
			_window.draw(t);
			_window.draw(out);
			_window.display();
			while (_window.pollEvent(_event)) {
				if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
					return;
				}
			}
		}
	}

	void gameInformation(RenderWindow& _window) {

		Font font;
		font.loadFromFile("Font//bahnschrift.ttf");

		Text textControlChecker[4];
		textControlChecker[0] = Text(L"Управление игрой:", font, 30);
		textControlChecker[0].setPosition(625, 350);
		textControlChecker[1] = Text(L"левый щелчёк по шашке - выбор шашки", font, 25);
		textControlChecker[1].setPosition(532, 395);
		textControlChecker[2] = Text(L"левый щелчёк по клетке - сделать ход", font, 25);
		textControlChecker[2].setPosition(540, 420);

		if (who_can_move == 0)
		{
			textControlChecker[3] = Text(L"Сейчас ходят белые", font, 35);
		}
		else
			textControlChecker[3] = Text(L"Сейчас ходят черные", font, 35);
		textControlChecker[3].setStyle(Text::Bold);
		textControlChecker[3].setPosition(582, 35);

		for (int i = 0; i < 4; i++)
		{
			textControlChecker[i].setFillColor(Color::Black);
			_window.draw(textControlChecker[i]);
		}
	}

	bool end_game() {
		int black = 0;
		int white = 0;
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == 0) {
				white++;
			}
			if (checkers_on_board.get_checker(i).get_color() == 1) {
				black++;
			}
		}
		if (white == 0) {
			return 1;
		}
		if (black == 0) {
			return 1;
		}
		return 0;
	}

	void LoserGame()
	{
		Image icon;
		icon.loadFromFile("Images/icon.png");

		ContextSettings settings;
		settings.antialiasingLevel = 20;//сглаживание
		RenderWindow LoserWindow(VideoMode(400, 150), "Loser", sf::Style::Close | sf::Style::Titlebar, settings);
		LoserWindow.setIcon(32, 32, icon.getPixelsPtr());

		Font font;
		font.loadFromFile("Font//bahnschrift.ttf");

		Text t = Text("", font, 81);
		if (!who_can_move)
			t.setString(L"Black win");
		else
			t.setString(L"White win");

		t.setFillColor(Color::Black);
		t.setPosition(28, 15);

		Event event;
		while (LoserWindow.isOpen()) {
			while (LoserWindow.pollEvent(event)) {
				if (event.type == Event::Closed || event.type == Event::MouseButtonPressed)
				{
					WorkWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
					WorkWindow.setIcon(32, 32, icon.getPixelsPtr());
					LoserWindow.close();

					return;
				}
			}
			LoserWindow.clear(Color(245, 210, 175));
			LoserWindow.draw(t);
			LoserWindow.display();
		}
	}

};

void PvPGame(ContextSettings& settings)
{
	WorkWindow.create(VideoMode(1050, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
	Image icon;
	icon.loadFromFile("Images/icon.png");
	WorkWindow.setIcon(32, 32, icon.getPixelsPtr());

	Button Regulations("", { 180,60 }, 40, Color::Cyan, Color::Black, 3, Color::Black);
	Button Loser("", { 180,60 }, 40, Color::Cyan, Color::Black, 3, Color::Black);
	Button TesT("", { 400,400 }, 40, Color::Cyan, Color::Black, 3, Color::Black);

	TesT.setPosition({ 50,50 });
	Regulations.setPosition({ 672,220 });
	Loser.setPosition({ 672,120 });

	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");

	Text  textRegulations, textLoser;
	textRegulations = Text(L"Правила", font, 40);
	textRegulations.setPosition(682, 220);
	textRegulations.setStyle(Text::Bold);
	textRegulations.setFillColor(Color::Black);

	textLoser = Text(L"Сдаться", font, 40);
	textLoser.setPosition(682, 120);
	textLoser.setStyle(Text::Bold);
	textLoser.setFillColor(Color::Black);

	sf::Texture textureMusik;
	textureMusik.loadFromFile("Images/Yes.png");

	Sprite SpriteMusik;
	SpriteMusik.setTexture(textureMusik);
	SpriteMusik.setTextureRect(IntRect(0, 0, 50, 50));
	SpriteMusik.setPosition({ 582,270 });

	Game game;
	bool start = 1, endOfGame = 0;
	Event event;
	while (WorkWindow.isOpen()) {
		while (WorkWindow.pollEvent(event)) {
			if (event.type == Event::Closed)
			{
				WorkWindow.close();
				return;
			}


			if (TesT.isMouseOver(WorkWindow))
				game.make_move(WorkWindow, event);

			switch (event.type)
			{
			case Event::MouseMoved:

				if (Regulations.isMouseOver(WorkWindow))
					Regulations.setBackColor(Color(247, 255, 0));
				else
					Regulations.setBackColor(Color::Cyan);

				if (Loser.isMouseOver(WorkWindow))
					Loser.setBackColor(Color(247, 255, 0));
				else
					Loser.setBackColor(Color::Cyan);

				break;
			case Event::MouseButtonPressed:

				if (Regulations.isMouseOver(WorkWindow))
					Regulations_windows(settings);

				if (Loser.isMouseOver(WorkWindow))
				{
					endOfGame = 1;
				}

				break;
			default:
				break;
			}
		}
		WorkWindow.clear(Color(245, 210, 175));

		TesT.DrawTo(WorkWindow);
		Regulations.DrawTo(WorkWindow);
		Loser.DrawTo(WorkWindow);
		WorkWindow.draw(textRegulations);
		WorkWindow.draw(textLoser);
		game.gameInformation(WorkWindow);
		game.get_checkers_on_board().draw_checkers(WorkWindow);//рисую поле и шашки

		if (endOfGame == 1) {
			game.LoserGame();
			return;
		}

		WorkWindow.display();
		if (game.end_game())     //рисую если конец игры	
		{
			game.LoserGame();
			return;
		}
	}
}
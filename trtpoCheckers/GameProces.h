#pragma once
#include"MyHeader.h"
#include"CheckerOnBoard.h"
#include"Tool.h"


class Game {
private:
	bool whoCanMove = 0;//цвет хода, 0 если ход белых, 1 если ход черных
	bool selectIsMade = 0;//0 если фигуры не выбрана, 1 если выбрана
	int choiseChacker;//номер выбранной для хода шашки
	float x;//номер клетки в которой шашка по оси х
	float y;//номер клетки в которой шашка по оси у
	Vector2i mausePosition;//позиция мыши
	CheckersOnBoard checkersOnBoard;
	vector <int> whoMustEat;//храню шашки, которые могут съесть
public:
	CheckersOnBoard& get_checkers_on_board() {
		return this->checkersOnBoard;
	}
	void set_mause_position(RenderWindow& _window) {
		this->mausePosition = Mouse::getPosition(_window);
	}
	Vector2i centre_on_square() {//
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (mausePosition.x < i * 50 + 100 && mausePosition.x < (i + 1) * 50 + 100 && mausePosition.y < j * 50 + 100 && mausePosition.y < (j + 1) * 50 + 100)
					return Vector2i(i * 50 + 57, j * 50 + 57);
	}

	bool get_who_can_move()
	{
		return this->whoCanMove;
	}

	void choise_of_chacker(RenderWindow& _window, Event _event) {//выбор шашки
		if (_event.type == sf::Event::MouseButtonPressed)
			if (_event.key.code == Mouse::Left) {
				set_mause_position(_window);
				if (_event.type == sf::Event::MouseButtonPressed)//для отмены взятия фигуры
				{
					set_mause_position(_window);
					if (_event.key.code == Mouse::Left && !checkersOnBoard.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight())
						if (checkersOnBoard.get_checker(choiseChacker).get_select() == 1 && selectIsMade == 1) {
							checkersOnBoard.get_checker(choiseChacker).leave_checker();
							selectIsMade = 0;
							std::cout << "Drop" << endl;
							checkersOnBoard.delete_backlight();
							return;
						}
				}

				for (int i = 0; i < checkersOnBoard.get_size(); i++)
					if (this->mausePosition.x >= checkersOnBoard.get_checker(i).get_position().x - 7 &&
						this->mausePosition.x <= checkersOnBoard.get_checker(i).get_position().x + 43 &&
						this->mausePosition.y >= checkersOnBoard.get_checker(i).get_position().y - 7 &&
						this->mausePosition.y <= checkersOnBoard.get_checker(i).get_position().y + 43)
						if (checkersOnBoard.get_checker(i).get_select() == 0 && selectIsMade == 0)
							if (checkersOnBoard.get_checker(i).get_color() == whoCanMove) {
								if (if_you_can_eat_you_must_eat(checkersOnBoard.get_checker(i).get_color())) {//проверка на обязательный ход какой то конкретной шашки
									int s = 0;
									for (int f : whoMustEat)
										if (f == i)
											s++;

									if (s == 0) {
										error_choise_checker(_window, _event);
										checkersOnBoard.delete_backlight();
										return;
									}
								}
								choiseChacker = i;
								selectIsMade = 1;
								checkersOnBoard.get_checker(choiseChacker).select_checker();
								std::cout << "Take" << endl;
								x = checkersOnBoard.get_checker(choiseChacker).get_x();
								y = checkersOnBoard.get_checker(choiseChacker).get_y();
								if (checkersOnBoard.get_checker(choiseChacker).get_queen())
									queen_square_for_move(checkersOnBoard.get_checker(choiseChacker).get_color(), 1, 1, 1, 1);
								else
									square_for_move();
								return;
							}
			}

	}


	void change_position(RenderWindow& _window, Event _event) {//ход шашки

		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.key.code == Mouse::Left) 
				if (checkersOnBoard.get_checker(choiseChacker).get_select() == 1 && selectIsMade == 1) {
					set_mause_position(_window);
					if (checkersOnBoard.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).get_backlight()) {
						checkersOnBoard.get_board().get_all_squares(x, y).square_free();
						if (checkersOnBoard.get_checker(choiseChacker).get_queen() == 1) {
							checkersOnBoard.get_checker(choiseChacker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								checkersOnBoard.delete_backlight();
								if (queen_square_for_move(checkersOnBoard.get_checker(choiseChacker).get_color(), 1, 1, 1, 1)) {
									cout << "loop" << endl;

									return;
								}
							}
						}
						else {
							checkersOnBoard.get_checker(choiseChacker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();

							if (eat_checker()) {
								checkersOnBoard.delete_backlight();
								x = (centre_on_square().x - 57) / 50;
								y = (centre_on_square().y - 57) / 50;
								if (checkersOnBoard.get_checker(choiseChacker).get_queen() == 1) {
									checkersOnBoard.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkersOnBoard.get_checker(choiseChacker).get_color());
									whoCanMove = !whoCanMove;
									checkersOnBoard.get_checker(choiseChacker).leave_checker();
									selectIsMade = 0;
									std::cout << "Drop" << endl;

									checkersOnBoard.delete_backlight();
									return;
								}

								if (!chance_eat_checker(checkersOnBoard.get_checker(choiseChacker).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						checkersOnBoard.get_board().get_all_squares((centre_on_square().x - 57) / 50, (centre_on_square().y - 57) / 50).square_employment(checkersOnBoard.get_checker(choiseChacker).get_color());
						whoCanMove = !whoCanMove;
						checkersOnBoard.get_checker(choiseChacker).leave_checker();
						selectIsMade = 0;
						std::cout << "Drop" << endl;

						checkersOnBoard.delete_backlight();
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
		if (checkersOnBoard.get_checker(choiseChacker).get_color()) {
			if (x + 1 >= 0 && y + 1 < 8 && x + 1 < 8 && y + 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x + 1, y + 1).get_employment() == 0)
				if (end_board(x + 1, y + 1))
					checkersOnBoard.get_board().get_all_squares(x + 1, y + 1).on_backlight();


			if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y + 1).get_employment() == 0)
				if (end_board(x - 1, y + 1))
					checkersOnBoard.get_board().get_all_squares(x - 1, y + 1).on_backlight();
		}
		else {
			if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x + 1, y - 1).get_employment() == 0)
				if (end_board(x + 1, y - 1))
					checkersOnBoard.get_board().get_all_squares(x + 1, y - 1).on_backlight();


			if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y - 1).get_employment() == 0)
				if (end_board(x - 1, y - 1))
					checkersOnBoard.get_board().get_all_squares(x - 1, y - 1).on_backlight();


		}
		if (!chance_eat_checker(checkersOnBoard.get_checker(choiseChacker).get_color())) {//варианты съесть шашку
			checkersOnBoard.delete_backlight();
			chance_eat_checker(checkersOnBoard.get_checker(choiseChacker).get_color());
		}
	}
	bool chance_eat_checker(bool _color) {//варианты съесть шашку
		bool more = 1;
		if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && checkersOnBoard.get_board().get_all_squares(x + 1, y + 1).get_employment()) // проверяем правый нижний ход шашки
			if (x + 1 >= 0 && x + 1 < 8 && y + 1 >= 0 && y + 1 < 8 && checkersOnBoard.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x + 2 >= 0 && x + 2 < 8 && y + 2 >= 0 && y + 2 < 8 && checkersOnBoard.get_board().get_all_squares(x + 2, y + 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x + 2, y + 2)) {// если не конец доски
						checkersOnBoard.get_board().get_all_squares(x + 2, y + 2).on_backlight();
						more = 0;
					}


		if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y + 1).get_employment()) // проверяем левый нижний ход шашки
			if (x - 1 >= 0 && y + 1 < 8 && x - 1 < 8 && y + 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x - 2 >= 0 && y + 2 < 8 && x - 2 < 8 && y + 2 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 2, y + 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x - 2, y + 2)) {
						checkersOnBoard.get_board().get_all_squares(x - 2, y + 2).on_backlight();
						more = 0;
					}


		if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x + 1, y - 1).get_employment()) // проверяем правый верхний ход шашки
			if (x + 1 >= 0 && y - 1 < 8 && x + 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x + 2 >= 0 && y - 2 < 8 && x + 2 < 8 && y - 2 >= 0 && checkersOnBoard.get_board().get_all_squares(x + 2, y - 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x + 2, y - 2)) {
						checkersOnBoard.get_board().get_all_squares(x + 2, y - 2).on_backlight();
						more = 0;
					}


		if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y - 1).get_employment()) // проверяем левый верхний ход шашки
			if (x - 1 >= 0 && y - 1 < 8 && x - 1 < 8 && y - 1 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != _color) // стоит ли там вражеская шашка
				if (x - 2 >= 0 && y - 2 < 8 && x - 2 < 8 && y - 2 >= 0 && checkersOnBoard.get_board().get_all_squares(x - 2, y - 2).get_employment() == 0) // свободно ли пространство за шашкой противника
					if (end_board(x - 2, y - 2)) {
						checkersOnBoard.get_board().get_all_squares(x - 2, y - 2).on_backlight();
						more = 0;
					}
		return more;
	}

	bool eat_checker() {//ем шашку
		if ((centre_on_square().x - 57) / 50 - x == 2 || (centre_on_square().x - 57) / 50 - x == -2 &&
			(centre_on_square().y - 57) / 50 - y == 2 || (centre_on_square().y - 57) / 50 - y == -2)
			for (int i = 0; i < checkersOnBoard.get_size(); i++)
				if (checkersOnBoard.get_checker(i).get_x() == x + (checkersOnBoard.get_checker(choiseChacker).get_x() - x) / 2 &&
					checkersOnBoard.get_checker(i).get_y() == y + (checkersOnBoard.get_checker(choiseChacker).get_y() - y) / 2) {
					checkersOnBoard.get_board().get_all_squares(checkersOnBoard.get_checker(i).get_x(), checkersOnBoard.get_checker(i).get_y()).square_free();
					for (int j = i; j < checkersOnBoard.get_size() - 1; j++)
						checkersOnBoard.get_checker(j) = checkersOnBoard.get_checker(j + 1);

					checkersOnBoard.delete_checker();
					if (i < choiseChacker)
						choiseChacker = choiseChacker - 1;

					return 1;
				}
		return 0;
	}

	void make_queen() {
		if (checkersOnBoard.get_checker(choiseChacker).get_color() == 0)
			if (checkersOnBoard.get_checker(choiseChacker).get_y() == 0) {
				checkersOnBoard.get_checker(choiseChacker).make_queen();

			}


		if (checkersOnBoard.get_checker(choiseChacker).get_color() == 1)
			if (checkersOnBoard.get_checker(choiseChacker).get_y() == 7) {
				checkersOnBoard.get_checker(choiseChacker).make_queen();

			}


	}
	bool queen_square_for_move(bool _color, int _i1, int _i2, int _i3, int _i4) {//варианты хода дамки
		int must_eat = 0;
		int i_line_number_eat[4] = { 0,0,0,0 };

		bool can_eat[4] = { _i1, _i2, _i3, _i4 };
		checkersOnBoard.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) { // низ право
					if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_employment() == 1) {
						if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == _color)
							break;

						else if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkersOnBoard.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_employment() == 0) {
									if (i_line_number_eat[0] > 0)
									{
										break;
									}
									i_line_number_eat[0] += 1;
									checkersOnBoard.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_backlight();
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
						checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_backlight();
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
					if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_employment() == 1) {
						if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == _color) {
							break;
						}
						else if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkersOnBoard.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_employment() == 0) {
									if (i_line_number_eat[1] > 0)
									{
										break;
									}
									i_line_number_eat[1] += 1;
									checkersOnBoard.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_backlight();
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
						checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_backlight();
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
					if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_employment() == 1) {
						if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkersOnBoard.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_employment() == 0) {
									if (i_line_number_eat[2] > 0)
									{
										break;
									}
									i_line_number_eat[2] += 1;
									checkersOnBoard.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_backlight();
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
						checkersOnBoard.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_backlight();
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
					if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_employment() == 1) {
						if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == _color) {
							break;
						}
						else if (checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != _color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkersOnBoard.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_employment() == 0) {
									if (i_line_number_eat[3] > 0)
									{
										break;
									}
									i_line_number_eat[3] += 1;
									checkersOnBoard.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_backlight();
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
						checkersOnBoard.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_backlight();
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
					if (checkersOnBoard.get_board().get_all_squares(i + 1, j + 1).get_employment() == 1) {
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
					if (checkersOnBoard.get_board().get_all_squares(i + 1, j - 1).get_employment() == 1) {
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
					if (checkersOnBoard.get_board().get_all_squares(i - 1, j + 1).get_employment() == 1) {
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
					if (checkersOnBoard.get_board().get_all_squares(i - 1, j - 1).get_employment() == 1) {
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

		for (int f = 0; f < checkersOnBoard.get_size(); f++) {
			if (checkersOnBoard.get_checker(f).get_x() == x_eat && checkersOnBoard.get_checker(f).get_y() == y_eat) {
				checkersOnBoard.get_board().get_all_squares(checkersOnBoard.get_checker(f).get_x(), checkersOnBoard.get_checker(f).get_y()).square_free();

				for (int c = f; c < checkersOnBoard.get_size() - 1; c++) {
					checkersOnBoard.get_checker(c) = checkersOnBoard.get_checker(c + 1);
				}
				checkersOnBoard.delete_checker();
				if (f < choiseChacker) {
					choiseChacker = choiseChacker - 1;
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
		while (whoMustEat.size() != 0)//освобождаем место под новые шашки которые могут съесть
			whoMustEat.pop_back();

		for (int i = 0; i < checkersOnBoard.get_size(); i++)
			if (checkersOnBoard.get_checker(i).get_color() == _color) {
				if (checkersOnBoard.get_checker(i).get_queen() == 0) {// обычная шашка
					x = checkersOnBoard.get_checker(i).get_x();
					y = checkersOnBoard.get_checker(i).get_y();
					if (!chance_eat_checker(_color))
						whoMustEat.push_back(i);

				}
				if (checkersOnBoard.get_checker(i).get_queen() == 1) {//дамка
					x = checkersOnBoard.get_checker(i).get_x();
					y = checkersOnBoard.get_checker(i).get_y();
					if (queen_square_for_move(_color, 1, 1, 1, 1))
						whoMustEat.push_back(i);

				}
			}

		checkersOnBoard.delete_backlight();
		if (whoMustEat.size() != 0) return 1;
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

	void game_information(RenderWindow& _window) {

		Font font;
		font.loadFromFile("Font//bahnschrift.ttf");

		Text textControlChecker[4];
		textControlChecker[0] = Text(L"Управление игрой:", font, 30);
		textControlChecker[0].setPosition(625, 350);
		textControlChecker[1] = Text(L"левый щелчёк по шашке - выбор шашки", font, 25);
		textControlChecker[1].setPosition(532, 395);
		textControlChecker[2] = Text(L"левый щелчёк по клетке - сделать ход", font, 25);
		textControlChecker[2].setPosition(540, 420);

		if (whoCanMove == 0)
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
		for (int i = 0; i < checkersOnBoard.get_size(); i++) {
			if (checkersOnBoard.get_checker(i).get_color() == 0) {
				white++;
			}
			if (checkersOnBoard.get_checker(i).get_color() == 1) {
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

	void loser_game()
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
		if (!whoCanMove)
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
					workWindow.create(VideoMode(500, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
					workWindow.setIcon(32, 32, icon.getPixelsPtr());
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
	workWindow.create(VideoMode(1050, 500), "Checkers", sf::Style::Close | sf::Style::Titlebar, settings);
	Image icon;
	icon.loadFromFile("Images/icon.png");
	workWindow.setIcon(32, 32, icon.getPixelsPtr());

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
	while (workWindow.isOpen()) {
		while (workWindow.pollEvent(event)) {
			if (event.type == Event::Closed)
			{
				workWindow.close();
				return;
			}


			if (TesT.isMouseOver(workWindow))
				game.make_move(workWindow, event);

			switch (event.type)
			{
			case Event::MouseMoved:

				if (Regulations.isMouseOver(workWindow))
					Regulations.setBackColor(Color(247, 255, 0));
				else
					Regulations.setBackColor(Color::Cyan);

				if (Loser.isMouseOver(workWindow))
					Loser.setBackColor(Color(247, 255, 0));
				else
					Loser.setBackColor(Color::Cyan);

				break;
			case Event::MouseButtonPressed:

				if (Regulations.isMouseOver(workWindow))
					regulations_windows(settings);

				if (Loser.isMouseOver(workWindow))
				{
					endOfGame = 1;
				}

				break;
			default:
				break;
			}
		}
		workWindow.clear(Color(245, 210, 175));

		TesT.DrawTo(workWindow);
		Regulations.DrawTo(workWindow);
		Loser.DrawTo(workWindow);
		workWindow.draw(textRegulations);
		workWindow.draw(textLoser);
		game.game_information(workWindow);
		game.get_checkers_on_board().draw_checkers(workWindow);//рисую поле и шашки

		if (endOfGame == 1) {
			game.loser_game();
			return;
		}

		workWindow.display();
		if (game.end_game())     //рисую если конец игры	
		{
			game.loser_game();
			return;
		}
	}
}
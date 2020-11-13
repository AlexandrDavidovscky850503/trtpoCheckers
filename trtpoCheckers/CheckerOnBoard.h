#pragma once
#include"MyHeader.h"
#include"Checker.h"
#include"Board.h"


class CheckersOnBoard {
private:
	vector <Checker> checkers;// шашки
	Board board;
	int matrixBoard[8][8];

public:
	Board& get_board() {
		return this->board;
	}

	Checker& get_checker(int _i) {
		return this->checkers[_i];
	}

	int get_size() {
		return this->checkers.size();
	}

	void start_game() {
		for (int i = 0; i < 24; i++) {// расстановка черных шашек
			if (i < 4) {

				checkers.push_back(Checker((float)i * 100 + 107, (float)57, 1));//добавления нового элемента в конец вектора 
				board.get_all_squares(i * 2 + 1, 0).square_employment(1);
			}
			else if (i >= 4 && i < 8) {
				checkers.push_back(Checker((float)(i - 4) * 100 + 57, (float)107, 1));
				board.get_all_squares((i - 4) * 2, 1).square_employment(1);
			}
			else if (i >= 8 && i < 12) {
				checkers.push_back(Checker((float)(i - 8) * 100 + 107, (float)157, 1));
				board.get_all_squares((i - 8) * 2 + 1, 2).square_employment(1);
			}

			else if (i >= 12 && i < 16) {//расстановка белых шашек
				checkers.push_back(Checker((float)(i - 12) * 100 + 57, (float)307, 0));
				board.get_all_squares((i - 12) * 2, 5).square_employment(0);
			}
			else if (i >= 16 && i < 20) {
				checkers.push_back(Checker((float)(i - 16) * 100 + 107, (float)357, 0));
				board.get_all_squares((i - 16) * 2 + 1, 6).square_employment(0);
			}
			else if (i >= 20 && i < 24) {
				checkers.push_back(Checker((float)(i - 20) * 100 + 57, (float)407, 0));
				board.get_all_squares((i - 20) * 2, 7).square_employment(0);
			}
		}
	}

	void delete_checker() {
		checkers.pop_back();
	}

	CheckersOnBoard() {
		start_game();//расставляю шашки
	}

	void draw_checkers(RenderWindow& _window) {//функция рисования поля с фигурами
		board.draw_board(_window);//рисую доску

		int xPos = 0, yPos = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {
				matrixBoard[i][j] = 0;
			}
		}


		for (int i = 0; i < checkers.size(); i++) {
			checkers[i].draw_checker(_window);//рисую каждую шашку
			yPos = (int)checkers[i].get_x();
			xPos = (int)checkers[i].get_y();
			if (checkers[i].get_color())
			{
				if (checkers[i].get_queen())
					matrixBoard[xPos][yPos] = 3;
				else
					matrixBoard[xPos][yPos] = 2;
			}
			else
				matrixBoard[xPos][yPos] = 1;
		}
	}

	void delete_backlight() {//удаляю все подсвеченные клетки
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				this->board.get_all_squares(i, j).off_backlight();
	}
};
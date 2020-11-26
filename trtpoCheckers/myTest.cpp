//#define BOOST_TEST_MODULE mytests
//#include <boost/test/included/unit_test.hpp>
////#include"Checker.h"
//#include"GameProces.h"
//
//BOOST_AUTO_TEST_CASE(myTestCase)
//{
//	////////////////////////////////////////Checker class test START///////////////////////////////////////////////////////
//	Checker checkerTest(107, 107, 1);
//
//	BOOST_CHECK(checkerTest.get_x() == 1);//из-за формулы
//	BOOST_CHECK(checkerTest.get_y() == 1);
//
//	checkerTest.set_position(207,207);
//
//	BOOST_CHECK(checkerTest.get_queen() == 0);
//	BOOST_CHECK(checkerTest.get_select() == 0);
//
//	BOOST_CHECK(checkerTest.get_x() == 3);
//	BOOST_CHECK(checkerTest.get_y() == 3);
//
//	checkerTest.select_checker();
//	BOOST_CHECK(checkerTest.get_select() == 1);
//
//	cout << "Checker class test is Good" << endl;
//	////////////////////////////////////////Checker class test END///////////////////////////////////////////////////////
//
//
//
//	////////////////////////////////////////CheckerOnBoard class test START//////////////////////////////////////////////
//	CheckersOnBoard checkerOnBoardTest;
//
//	BOOST_CHECK(checkerOnBoardTest.get_size() == 24);
//	checkerOnBoardTest.delete_checker();
//	BOOST_CHECK(checkerOnBoardTest.get_size() == 23);
//
//	cout << "CheckersOnBoard class test is Good" << endl;
//	////////////////////////////////////////CheckerOnBoard class test END///////////////////////////////////////////////
//
//
//
//	////////////////////////////////////////Square class test START/////////////////////////////////////////////////////
//	
//	Square squareTest;
//
//	squareTest.square_employment(1);
//	BOOST_CHECK(squareTest.get_employment() == 1);
//	BOOST_CHECK(squareTest.get_checker_color() == 1);
//	BOOST_CHECK(squareTest.get_square_employment() == 1);
//	squareTest.on_backlight();
//	BOOST_CHECK(squareTest.get_backlight() == 1);
//	cout << "Square class test is Good" << endl;
//	////////////////////////////////////////Square class test END///////////////////////////////////////////////////////
//
//
//
//	////////////////////////////////////////Game class test START//////////////////////////////////////////////////////
//	Game gameTest;
//	BOOST_CHECK(gameTest.end_board(9,9) == 0);
//	BOOST_CHECK(gameTest.end_board(0, 0) == 1);
//	BOOST_CHECK(gameTest.end_game() == 0);
//	BOOST_CHECK(gameTest.if_you_can_eat_you_must_eat(1) == 0);
//	BOOST_CHECK(gameTest.if_you_can_eat_you_must_eat(0) == 0);
//	cout << "Game class test is Good";
//	////////////////////////////////////////Game class test END////////////////////////////////////////////////////////
//	
//}
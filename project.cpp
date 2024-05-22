#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include "rang.hpp"

using namespace rang;
using namespace std;

// доска для игры
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

char currentPlayer = 'X';

// вывод доски для игры
void printBoard() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << board[i][j] << " ";
    }
    cout << "\n";
  }
}

// проверка победителя 
bool checkWin() {
  for (int i = 0; i < 3; ++i) {
    if (board[i][0] == currentPlayer && board[i][1] == currentPlayer &&
        board[i][2] == currentPlayer)
      return true;
    if (board[0][i] == currentPlayer && board[1][i] == currentPlayer &&
        board[2][i] == currentPlayer)
      return true;
  }
  if (board[0][0] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][2] == currentPlayer)
    return true;
  if (board[0][2] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][0] == currentPlayer)
    return true;
  return false;
}

// проверка, полная ли доска (ничья)
bool isBoardFull() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == ' ')
        return false;
    }
  }
  return true;
}

int main() {
  srand(time(0));
  
  int a, b, c, count = 0, player; //коэффициенты и счетчик неправильных ответов 
  double x1, x2, x11, x22; // корни уравнения
  
  cout << fg::black << "И" << fg::red <<"г" << fg::green << "р" << fg::yellow << "а " << fg::blue <<"к" << fg::magenta << "р" << fg::cyan << "е" << fg::gray << "с" << fg::black << "т" << fg::red << "и" << fg::green <<"к"<< fg::yellow << "и"<< fg::blue <<"-" << fg::magenta << "н"<< fg::cyan <<"о"<< fg::gray <<"л"<< fg::black <<"и"<< fg::red <<"к"<< fg::green <<"и\n";

  cout<< fg::reset << "вы умеете играть или нет?  \n1 - умею\n2 - не умею\n";

  cin >> player;
  
  if(player == 2) cout << "Правила игры просты, Первый, кто поставит три символа в ряд в любом из направлений, будь то вертикальный, горизонтальный или диагональный ряд, станет победителем, ";
  cout << fg::green << "Удачной игры :)\n\n";

  while (true) {
    
    cout << fg::reset << style::italic << "Ход игрока " << currentPlayer << ", Решите квадратное уравнение(округлите до целого числа, по правилам математики) \n";
    printBoard(); // доска для игры

    a = rand() % 9 + 1; // генерация случайного значения от 1 до 9 для коэффициента a
    b = rand() % 19 - 9; // генерация случайного значения от -9 до 9 для коэффициента b 
    c = rand() % 19 - 9; // генерация случайного значения от -9 до 9 коэффициента c

    // проверка, что у уравнения есть корни
    while (b * b - 4 * a * c <= 0) {
      b = rand() % 19 - 9;
      c = rand() % 19 - 9;
    }

    // вычислеие корней уравения
    x1 = (-b + sqrt(b * b - (4 * a * c))) / (2 * a);
    x2 = (-b - sqrt(b * b - (4 * a * c))) / (2 * a);

    // вывод уравнения
    if (a > 0 && b > 0 && c > 0) cout << a << "x^2 + " << b << "x + " << c << " = 0\n";
    else if(a > 0 && b > 0 && c < 0) cout << a << "x^2 + " << b << "x " << c << " = 0\n";
    else if(a > 0 && b < 0 && c < 0) cout << a << "x^2 " << b << "x " << c << " = 0\n";
    else if(a > 0 && b < 0 && c > 0) cout << a << "x^2 " << b << "x + " << c << " = 0\n";
    else if (a > 0 && b > 0 && c == 0) cout << a << "x^2 + " << b << "x" << " = 0\n";
    else if (a > 0 && b == 0 && c > 0) cout << a << "x^2 + "<< c << " = 0\n";
    else if (a > 0 && b == 0 && c < 0) cout << a << "x^2 " << c << " = 0\n";
    else if (a > 0 && b < 0 && c == 0) cout << a << "x^2 " << b << "x" << " = 0\n";

    // округление корней по правилам математики
    x1 = round(x1);
    x2 = round(x2);

    if(x1 == -0) x1 = 0;
    if(x2 == -0) x2 = 0;

    // проверка на наличие одного или двух корней
    if (x1 != x2) cin >> x11 >> x22;
    else cin >> x11;

    int row, col;

    if (((x11 == x1 || x11 == x2) && (x22 == x2 || x22 == x1)) || (x11 == x1 && x11 == x2)) {
      cout << fg::green << "Введите номер строки (1-3) и номер столбца (1-3): " << fg::reset;
      cin >> row >> col;
      
      count = 0;
      
      if (row < 1 || row > 3 || col < 1 || col > 3) {
        cout << fg::yellow << "Неверные координаты! Повторите ввод.\n";
        continue;
      }

      if (board[row - 1][col - 1] != ' ') {
        cout << fg::yellow << "Ячейка уже занята! Повторите ввод.\n";
        continue;
      }
    }

    else {
      if(x1 != x2) cout << fg::red << "Неверно, вы пропускаете ход. Корни были: \nx1 = " << x1 << " x2 = " << x2 << "\n";
      else cout << fg::red << "Неверно, вы пропускаете ход. Корни были: \nx = " << x1 << "\n";
      count++;
      cout << "Количество неверных ответов подряд = " << count << "\n";
    }

    board[row - 1][col - 1] = currentPlayer;

    // конец игры 
    if (checkWin()) {
      cout <<  fg::green << "Игрок " << currentPlayer << " победил!\n";
      break;
    } 
    else if (isBoardFull() || count == 4) {
      cout <<  fg::yellow << "Ничья!\n" << fg::reset;
      break;
    }

    // переход хода с игрока Х на игрока О и наоборот
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
  }

  printBoard();

  return 0;
}

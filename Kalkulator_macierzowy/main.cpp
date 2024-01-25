#include "Matrix.h"
#include "Operation.h"
#include <iostream>
#include <locale.h>

using namespace std;

int expression();
int determinant();

int main()
{
	setlocale(LC_ALL, "pl-PL");
	cout << "KALKULATOR MACIERZOWY" << endl;
	bool main_continue = true;
	int choice = 3;
	while (main_continue)
	{
		cout << "Obliczanie wyznacznika macierzy: wybierz \"1\"" << endl;
		cout << "Obliczanie wyra�enia macierzowego: wybierz \"2\"" << endl;
		cout << "Zako�cz: wybierz \"3\"" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			determinant();
			break;
		case 2:
			cout.flush();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.clear();
			expression();
			break;
		case 3:
			return 0;
		default:
			cout << "Nieprawid�owa warto��!" << endl;
		}
	}
}

int expression()
{
	cout << endl;
	cout << "Spos�b wprowadzania wyra�e� do kalkulatora: " << endl;
	cout << "V\"liczba\" - macierz o numerze \"liczba\" np. V1, V2, V3 " << endl;
	cout << "Dost�pne operacje:" << endl;
	cout << "\"*\" - mno�enie;		\"/\" - dzielenie;	\"-\" - odejmowanie;	\"+\" - dodawanie" << endl;
	cout << "\"%\" - transpozycja;	\"$\" - macierz odwrotna;		\"^\" - pot�gowanie" << endl;
	cout << "Przyk�adowe wyra�enie: (V1 + V2$) * (V3^3 / V4%)" << endl;
	bool calc_continue = true;
	string answer;
	Operation function;
	int amountMatrix;
	while (calc_continue)
	{
		Matrix::amountMatrix = 1;
		function.load();
		amountMatrix = function.amountMatrix();
		Matrix* table = new Matrix[amountMatrix];

		int rows, columns;
		for (int i = 0; i < amountMatrix; i++)
		{
			cout << "Podaj liczb� wierszy macierzy V" << i + 1 << ": ";
			cin >> rows;
			cout << "Podaj liczb� kolumn macierzy V" << i + 1 << ": ";
			cin >> columns;
			Matrix m(rows, columns);
			cout << endl;
			m.enter();
			table[i] = move(m);
			//table[i] = m;
		}

		function.transpone(table);
		function.inverse(table);
		function.exponentation(table);
		function.infixToPostfix();
		cout << function.calculate(table);

		cout << endl;
		cout << "Czy chcesz obliczy� kolejne wyra�enie? (tak/nie): ";
		cin >> answer;
		if (answer == "tak")
		{
			calc_continue = true;
		}
		else calc_continue = false;
		cout << endl;
		delete[] table;
		cout.flush();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.clear();
		function.clear();
	}
	return 0;
}

int determinant()
{
	Matrix::amountMatrix = 1;
	bool calc_continue = true;
	int rows, columns;
	string answer;
	while (calc_continue)
	{
		cout << "Podaj liczb� wierszy macierzy: ";
		cin >> rows;
		cout << "Podaj liczb� kolumn macierzy:";
		cin >> columns;
		Matrix m(rows, columns);
		cout << endl;
		m.enter();
		cout << endl;
		cout << "Wyznacznik macierzy = " << m.determinant() << endl;
		cout << "Czy chcesz obliczy� kolejny wyznacznik? (tak/nie): ";
		cin >> answer;
		if (answer == "tak")
		{
			calc_continue = true;
		}
		else calc_continue = false;
		cout << endl;
		cout.flush();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin.clear();
	}
	return 0;
}
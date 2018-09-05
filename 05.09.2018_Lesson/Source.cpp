#include <iostream>
#include <iomanip>
#include<math.h>
#include<ctime>

using namespace std;

int* form_array(int**a, int n, int m, int &new_size) { // returns a pointer!!! (*)
	new_size = n * m;
	int index = 0;
	int *tmp = new int[new_size];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp[index++] = a[i][j];

	return tmp;
}
void add_row(int **&a, int &n, int m) {
	int **tmp = new int*[n+1]; // доп строка будет во временной матрице
	
	for (int i = 0; i < n; i++)
		tmp[i] = a[i];	// Важно: переназначается указатель, никакие числа не копируются!

	delete[] a; // нельзя удалять сами подмассивы с целыми хранящимися числами!
	// Необходимо только переназначить новый указатель на старую область памяти
	// поэтому удаляется старый массив, где хранятся адреса подмассивов, а сами подмассивы нетронуты, просто для них теперь есть новый указатель

	a = tmp;
	a[n] = new int[m];
	n++;
}
void add_firstRow(int **&a, int &n, int m) {
	int **tmp = new int*[n + 1];

	for (int i = 0; i < n; i++)
		tmp[i+1] = a[i];	

	delete[] a;

	a = tmp;
	a[0] = new int[m];
	n++;
}
void add_anyRow(int **&a, int &n, int m) {
	int **tmp = new int*[n + 1];
	int k;
	cin >> k;
	for (int i = 0; i < n; i++)
	{
		if (i < k)
			tmp[i] = a[i];
		else if (i >= k) tmp[i + 1] = a[i];
	}
		
	delete[] a;

	a = tmp;
	a[k] = new int[m];
	n++;
}
void erase_anyRow(int **&a, int &n, int m) {
	int **tmp = new int*[n - 1];
	int k;
	cin >> k;
	for (int i = 0; i < n; i++)
	{
		if (i < k)
			tmp[i] = a[i];
		else if (i == k)
			continue;
		else if (i > k)
			tmp[i - 1] = a[i];
	}

	delete[] a;

	a = tmp;
	n--;
}
void delete_last_row(int**&a, int&n, int m) { // просто стирание последней строки
	delete[] a[n - 1];
	n--;
}
void delete_any_row(int**&a, int&n, int m) { // просто стирание последней строки
	int k;
	cin >> k;
	
	delete[] a[k];
	n--;
}

// 1.	Напишите функцию для обращения одномерного массива в N - мерный.Должны выполняться соответствующие проверки.
void reform(int *a, int n, int **&pp, int column) {
	if (n%column == 0)
	{
		int **tmp = new int*[column];
		int row = n / column;

		for (int i = 0; i < column; i++)
			tmp[i] = new int[row];

		int k = 0;

		for (int i = 0; i < column; i++)
		{
			for (int j = 0; j < row; j++)
			{
				tmp[i][j] = a[k++];
				cout << tmp[i][j] << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < column; i++)
			delete[] pp[i];
		delete[] pp;
		pp = tmp;
	}
	
}

// 2.	Транспонирование матрицы – это операция, после которой столбцы прежней матрицы становятся строками, а строки столбцами.
// Напишите функцию транспонирования матрицы.
void transp(int**&a, int &n, int &m) {
	int **tmp = new int*[m];
	for (int i = 0; i < m; i++)
		tmp[i] = new int[n];

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			tmp[i][j] = a[j][i];

	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;

	a = tmp;
	int k = n;
	n = m;
	m = k;
}


int main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Rus");

	int tn = 0;

	while (true)
	{
		cout << "Задача № ";
		cin >> tn;

		switch (tn)
		{
		case 1:
		{
			int **a;
			int *p;
			int n, m, arr_size;
			cin >> n >> m;
			a = new int*[n];
			p = new int[n];

			for (int i = 0; i < n; i++)
				a[i] = new int[m];

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					a[i][j] = rand() % 20 + 1;
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;

			p = form_array(a, n, m, arr_size);

			for (int i = 0; i < arr_size; i++)
				cout << p[i] << " ";
			cout << endl;

			int**pp;
			n = 5, m = 6;
			arr_size = n * m;
			pp = new int*[n];
			for (int i = 0; i < n; i++)
				pp[i] = new int[m];


			delete[] p;

			for (int i = 0; i < n; i++)
				delete[] a[i];
			delete[] a;

			for (int i = 0; i < n; i++)
				delete[] pp[i];
			delete[] pp;
		}
		break;
		case 2:
		{
			int**a;
			int n = 4, m = 5, arr_size;
			a = new int*[n];

			for (int i = 0; i < n; i++)
				a[i] = new int[m];

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					a[i][j] = rand() % 20 + 1;
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;


			a[0][0] = 100;
			add_row(a, n, m);
			a[4][0] = 200;

			add_firstRow(a, n, m);
			a[0][0] = 500;

			add_anyRow(a, n, m);

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}

			erase_anyRow(a, n, m);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}

			for (int i = 0; i < n; i++)
				delete[] a[i];
			delete[] a;
		}
		break;
		case 3:
		{
			int **a;
			int n, m;
			cin >> n >> m;
			a = new int*[n];

			for (int i = 0; i < n; i++)
				a[i] = new int[m];

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					a[i][j] = rand() % 20 + 1;
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;

			transp(a, n, m);

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					cout << setw(3) << a[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			for (int i = 0; i < n; i++)
				delete[] a[i];
			delete[] a;
		}
		break;
		case 4:
		{
			int *p;
			int **pp;
			int n, m;
			cin >> n >> m;

			p = new int[n];

			pp = new int*[m];
			for (int i = 0; i < m; i++)
				pp[i] = new int[n/m];

			for (int i = 0; i < n; i++)
			{
				p[i] = rand() % 10;
				cout << p[i] << " ";
			}
			cout << endl << endl;

			reform(p, n, pp, m);

			delete[] p;

			for (int i = 0; i < m; i++)
				delete[] pp[i];
			delete[] pp;
		}
		break;
		case 5:
		{

		}
		break;
		case 6:
		{

		}
		break;
		case 7:
		{

		}
		break;
		case 8:
		{

		}
		break;
		case 9:
		{

		}
		break;
		case 10:
		{

		}
		break;
		default:
			cout << "нет такой задачи" << endl << endl;
		}
	}
	system("pause");
	return 0;
}
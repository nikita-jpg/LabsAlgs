#include <iostream>
#include <random>
#include <iomanip>
#include <ctime>
#include <cmath>
#pragma comment(linker, "/STACK:2000000")
using namespace std;




//Начало турнирной сортировки
//М-часть кода,которую вы можете удалить. Используется конкретно в моей реализации.
struct Cell //ячейка дерева
{
	Cell* right;// правый потомок
	Cell* left;//левый потомок
	Cell* next;//элемент, находящийся справа на том же уровне
	int key; //значение ячейки
};
Cell* BuildTree(int* arr, int n, long long int& c, long long int& m) {
	Cell* level = NULL; //указатель на первый элемент уровня дерева
	Cell* pred = NULL; //указатель на предыдуший элемент
	Cell* tek = NULL; //указатель на текущий элемент
	Cell* leftEl = NULL;// указатель на левого потомка
	Cell* rightEl = NULL;// указатель на правого потомка
	//Заполнение первого уровня дерева
	for (int i = 0; i < n; i++) {

		tek = new Cell;
		tek->left = NULL;
		tek->right = NULL;
		tek->next = NULL;
		tek->key = arr[i];
		if (level == NULL) level = tek;
		else pred->next = tek;
		pred = tek;
	}
	tek->next = NULL;
	pred = NULL;
	// заполнение остальных уровней 
	while (level->next != NULL) {
		leftEl = level;
		level = NULL;
		while (leftEl != NULL) {
			rightEl = leftEl->next;
			tek = new Cell;
			tek->right = rightEl;
			tek->left = leftEl;
			tek->next = NULL;


			if (level == NULL)level = tek;
			else pred->next = tek;
			pred = tek;

			if ((rightEl == NULL) or (rightEl->key > leftEl->key)) {
				tek->key = leftEl->key;
			}
			else tek->key = rightEl->key;
			if (rightEl != NULL) leftEl = rightEl->next;
			else
			{
				leftEl = NULL;
			}

		}
	}
	return level;
}
Cell* Competit(Cell* root, long long int& c, long long int& m, int n) {
	if (n != 0) {//Если мы дошли до первого уровня,то потомков точно нет
		c++;
		if ((root->left != NULL) && (root->key == root->left->key)) root->left = Competit(root->left, c, m, n - 1);
		else if (root->right != NULL) root->right = Competit(root->right, c, m, n - 1);
	}
	if ((root->left == NULL) && (root->right == NULL)) {
		root = NULL;
	}
	else {
		if ((root->left == NULL) || ((root->right != NULL) && (root->left->key > root->right->key))) {
			root->key = root->right->key;
		}
		else root->key = root->left->key;

	}
	return root;
}
long long int* TournamentSort(int arr[], int n) //Турнирная сортировка
{

	long long int arrRetur[2];
	long long int c = 0;
	long long int m = 0;
	int otv[70000];//М, Массив ответов
	Cell* ph = BuildTree(arr, n, c, m);

	for (int i = 0; i < n; i++) {

		otv[i] = ph->key;
		ph = Competit(ph, c, m, ceil(log(n) / log(2)));//Округляем логарифм в большую сторону, т.к. количество уровней дерева - целое число.
	}
	//М-начало
	arrRetur[0] = 1;
	for (int i = 0; i < n - 1; i++) {
		if (otv[i] > otv[i + 1]) arrRetur[0] = 0;
	}
	arrRetur[1] = c + m;
	return arrRetur;
	//М-конец
}
//Конец турнирной сортировки

long long int* ShakerSort(int arr[], int n) {
	long long int arrRetur[2];
	bool son = true;
	int right = n;
	int left = 1;
	int i = 0;
	int c = 0;
	int m = 0;
	do {
		son = true;
		for (i = left; i < right; i++) {
			c++;
			if (arr[i - 1] > arr[i]) {
				swap(arr[i], arr[i - 1]);
				m++;
				son = false;
			}
		}
		right--;
		for (i = right; i = left; i--) {
			c++;
			if (arr[i] < arr[i - 1]) {
				m++;
				swap(arr[i], arr[i]);
				son = false;
			}
		}
	} while (son == false);

	arrRetur[0] = 1;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) arrRetur[0] = 0;
	}
	arrRetur[1] = c + m;
	return arrRetur;
}






long long int* InserationSort(int arr[], int n) //сортировка вставками
{
	int key;
	int i;
	long long int c = 0;
	long long int m = 0;
	long long int arrRetur[2];
	int otv[100000];
	for (int j = 1; j < n; j++)
	{
		key = arr[j];
		i = j - 1;
		c++;
		while (i >= 0 && arr[i] > key)
		{
			arr[i + 1] = arr[i];
			i--;
			m++;
			c++;
		}
		arr[i + 1] = key;
	}
	arrRetur[0] = 1;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) arrRetur[0] = 0;
		otv[i] = arr[i];
	}
	arrRetur[1] = c + m;
	return arrRetur;
}
long long int* SelectionSort(int arr[], int n) //сортировка выбором
{
	int key;
	int i;
	long long int arrRetur[2];
	long long int c = 0;
	long long int m = 0;
	int temp;
	for (int j = 0; j < n - 1; j++)
	{
		temp = j;
		for (int i = j + 1; i < n; i++) {
			c++;
			if (arr[temp] > arr[i]) {
				temp = i;
			}
		}
		if (temp != j) {
			swap(arr[temp], arr[j]);
			m++;
		}
	}

	arrRetur[0] = 1;
	//Проверка массива на отсортированность
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) arrRetur[0] = 0;
	}
	arrRetur[1] = c + m;
	return arrRetur;
}
void Reverse(int arry[], int n)
{
	int key;
	int i;
	long long int arrRetur[2];
	long long int c = 0;
	long long int m = 0;
	int temp;
	for (int j = 0; j < n; j++)
	{
		temp = 0;
		int k = 0;
		for (int i = 1; i < n - j; i++) {
			m++;
			if (arry[temp] > arry[i]) {
				temp = i;
				c++;
				k = 1;
			}
		}
		swap(arry[temp], arry[n - j - 1]);
		c++;
	}
}
bool Test() {
	int test1[10];
	int a;
	//Заполнение тестового массива
	for (int i = 0; i < 10; i++) {
		cin >> a;
		test1[i] = a;
	}
	bool bol = true;
	if (TournamentSort(test1, 10)[0] == 1) cout << "Турнирная сортировка работает правильно" << endl;
	else
	{
		cout << "Турнирная сортировка работает не правильно" << endl;
		bol = false;
	}
	if (InserationSort(test1, 10)[0] == 1) cout << "Вставки работают правильно" << endl;
	else
	{
		cout << "Вставки работают не правильно" << endl;
		bol = false;
	}
	if (SelectionSort(test1, 10)[0] == 1) cout << "Обратная работает правильно" << endl;
	else
	{
		cout << "Обратная работает не правильно" << endl;
		bol = false;
	}
	return bol;
}
void Vivod(long long int arr[], string str, int n, clock_t times[]) {
	cout << "Сортировка " << str << "    Средний случай" << endl;
	cout << "Количество элементов     " << "Tэ(n)=C+M" << "  T(n) " << endl;
	for (int i = 0; i < 5; i++) cout << (i + 3) * 10000 << +"                    " << arr[i] << "    " << setprecision(3) <<(double)(times[i]) / CLOCKS_PER_SEC << endl;
	cout << endl;


	cout << "Сортировка " << str << "    Лучший случай" << endl;
	cout << "Количество элементов     " << "Tэ(n)=C+M" << "  T(n) " << endl;
	for (int i = 5; i < 10; i++) cout << (i - 2) * 10000 << "                    " << arr[i] << "    " << setprecision(3) << (double)(times[i]) / CLOCKS_PER_SEC << endl;
	cout << endl;

	cout << "Сортировка " << str << "    Худший случай" << endl;
	cout << "Количество элементов     " << "Tэ(n)=C+M" << "  T(n) " << endl;
	for (int i = 10; i < 15; i++) cout << (i - 7) * 10000 << "                    " << arr[i] << "    " << setprecision(3) << (double)(times[i]) / CLOCKS_PER_SEC << endl;
	cout << endl << endl << endl << endl;
}

int* random(int arr[], int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		arr[i] = rand();
	}
	return arr;
}
int* reverse(int arr[], int n) {
	for (int i = 0; i < n / 2; i++) {
		swap(arr[i], arr[n - i - 1]);
	}
	return arr;
}
int main()
{
	setlocale(LC_ALL, "");
	int array7[70000];
	int* arr7 = random(array7, 70000);

	int test1[10];

	//Тестовый прогон-начало
	int n;
	cout << "Тестовый прогон-1" << endl << "Основной прогон-2" << endl;
	cin >> n;
	if (n == 1) {
		cout << "Введите целочисленные значения массива (через пробел)";
		for (int i = 0; i < 10; i++)cin >> test1[i];
		if (TournamentSort(test1, 10)[0] == 1) cout << "Турнирная сортировка работает правильно" << endl;
		else cout << "Турнирная сортировка работает не правильно" << endl;

		if (InserationSort(test1, 10)[0] == 1) cout << "Сортировка вставками работает правильно" << endl;
		else cout << "Сортировка вставками работает не правильно" << endl;

		if (SelectionSort(test1, 10)[0] == 1) cout << "Сортировка выбором работает правильно" << endl;
		else cout << "Сортировка выбором работает не правильно" << endl;
	}
	else {
		cout << "Введите номер желаемой сортировки" << endl;
		cout << "Турнирная сортировка - 1" << endl;
		cout << "Шейкерная сортировка - 2" << endl;
		cout << "Сортировка выбором - 3" << endl;
		cin >> n;

		switch (n)
		{
			clock_t  times[15];
			clock_t  startTime;
			long long int arrChange[15];//Массив результатов
		case 1://Турнирная сортировка
			//Средний случай
			for (int i = 0; i < 5; i++) {
				arr7 = random(array7, (i + 3) * 10000);
				startTime = clock();
				arrChange[i] = TournamentSort(arr7, (i + 3) * 10000)[1];
				times[i] = clock() - startTime;

			}

			//Лучший случай
			for (int i = 5; i < 10; i++) {
				startTime = clock();
				arrChange[i] = TournamentSort(arr7, (i - 2) * 10000)[1];
				times[i] = clock() - startTime;
			}

			//Худший случай
			for (int i = 10; i < 15; i++) {
				Reverse(arr7, (i - 7) * 10000);
				startTime = clock();
				arrChange[i] = TournamentSort(arr7, (i - 7) * 10000)[1];
				times[i] = clock() - startTime;
			}
			Vivod(arrChange, "турнирная", 1, times);
			break;

		case 2://Сортировка шейкерная
			//Средний случай
			for (int i = 0; i < 5; i++) {
				arr7 = random(array7, (i + 3) * 10000);
				startTime = clock();
				arrChange[i] = ShakerSort(arr7, (i + 3) * 10000)[1];
				times[i] = clock() - startTime;
			}

			//Лучший случай
			for (int i = 5; i < 10; i++) {
				startTime = clock();
				arrChange[i] = ShakerSort(arr7, (i - 2) * 10000)[1];
				times[i] = clock() - startTime;
			}

			//Худший случай
			for (int i = 10; i < 15; i++) {
				Reverse(arr7, (i - 7) * 10000);
				startTime = clock();
				arrChange[i] = ShakerSort(arr7, (i - 7) * 10000)[1];
				times[i] = clock() - startTime;
			}

			Vivod(arrChange, "шейкерная", 1, times);
			break;

		case 3://Сортировка выбором
			//Средний случай
			for (int i = 0; i < 5; i++) {
				arr7 = random(array7, (i + 3) * 10000);
				startTime = clock();
				arrChange[i] = SelectionSort(arr7, (i + 3) * 10000)[1];
				times[i] = clock() - startTime;
			}

			//Лучший случай
			for (int i = 5; i < 10; i++) {
				startTime = clock();
				arrChange[i] = SelectionSort(arr7, (i - 2) * 10000)[1];
				times[i] = clock() - startTime;
			}

			//Худший случай
			for (int i = 10; i < 15; i++) {
				Reverse(arr7, (i - 7) * 10000);
				startTime = clock();
				arrChange[i] = SelectionSort(arr7, (i - 7) * 10000)[1];
				times[i] = clock() - startTime;
			}
			Vivod(arrChange, "выбором", 2, times);
			break;

		default:
			break;
		}
	}

	return(0);
}

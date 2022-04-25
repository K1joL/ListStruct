#include <iostream>

using namespace std;

struct list
{
	list();
	~list();

	void push_back(int data);					//Добавить элемент в конец списка
	void pop_front();						//Удаление первого элемента в списке
	void clear();							//Удаление всех элементов списка
	int& operator[](const int index);				//Индексирование списка
	void removebynum(int index);					//Удаление элемента по номеру
	void removebydata(int data);					//Удаление элементов по значению
	void change_data(int data,int index);				//Изменить данные в элементе под номером index
	void SortList();						//Сортировка списка
	int GetSize() { return Size; };					//Получение размера списка

	struct node
	{
		node *pNext;
		int data;
		node(int data = 0, node *pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	node *First;
};

list::list()
{
	Size = 0;
	First = nullptr;
}

list::~list()
{
}

void list::push_back(int data)
{
	if (First == nullptr)
	{
		First = new node(data);
	}
	else
	{
		node* current = this->First;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new node(data);
	}
	Size++;
}

void list::pop_front()
{
	node *temp = First;
	First = First->pNext;
	delete temp;
	Size--;
}

void list::clear()
{
	while (Size)
	{
		pop_front();
	}
}

int& list::operator[](const int index)
{
	int counter = 0;
	node* current = this->First;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

void list::removebynum(int index)
{
	node *previous = this->First;
	node *temp = nullptr;
	if (!(index))
	{
		pop_front();
	}
	else
	{
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		temp = previous->pNext;
		previous->pNext = temp->pNext;
		delete temp;
		Size--;
	}
}

void list::removebydata(int data)
{
	node *current = this->First;
	for (int i = 0; i < GetSize(); i++)
	{
		if (current->data == data)
		{
			removebynum(i);
			break;
		}
		else
		{
			current = current->pNext;
		}
	}
}

void list::change_data(int data,int index)
{
	node *current = this->First;
	for (int i = 0; i < index; i++)
	{
		current = current->pNext;
	}
	current->data = data;
}
//"Пузырёк"
void list::SortList()
{
	for (int i = 1; i <= GetSize(); i++)
	{
		node *current = this->First;
		int f = 0;
		for (int k = 0; k <= GetSize() - 1 - i; k++)
		{
			if (current->data > current->pNext->data)
			{
				int tmp = current->data;
				current->data = current->pNext->data;
				current->pNext->data = tmp;
				f++;
			}
			if (current->pNext) {
				current = current->pNext;
			}
			else break;
		}
		if (f == 0) break;
	}
}

void list_out(list lst)
{
	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << i + 1 << ". " << lst[i] << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	char button = 0;
	list(lst);

	cout << "--------------Меню--------------" << endl <<
		"1. Добавить новый элемент в список;" << endl <<
		"2. Добавить новый элемент со случайными данными;" << endl <<
		"3. Удалить элемент по номеру;" << endl <<
		"4. Удалить элемент по значению;" << endl <<
		"5. Изменить данные в элементе;" << endl <<
		"6. Сортировка списка;" << endl <<
		"7. Вывести список;" << endl << 
		"8. Выход" << endl;

	while (button != '8')
	{
		cout << endl << "Выберите функцию:" << endl;
		cin >> button;
		int data = 0, index = 0;
		switch (button)
		{

		//Добавление элемента с заданным значением
		case '1':
			cout << "Введите данные: " << endl;
			cin >> data;
			lst.push_back(data);
			cout << "Добавлен элемент: " << lst.GetSize() << ". " << lst[lst.GetSize() - 1] << endl;
			break;

		//Добавление элемента со случайным значением
		case '2':
			lst.push_back(rand());
			cout << "Добавлено элемент: " << lst.GetSize() <<". " << lst[lst.GetSize() - 1] << endl;
			break;

		//Удаление элемента по номеру
		case '3':
			if (lst.GetSize())
			{
				while (true)
				{
					cout << "Введите номер элемента (для отмены введите \"0\"): ";
					cin >> index;
					if (index - 1 <= lst.GetSize() and index - 1 >= 0)
					{
						lst.removebynum(index - 1);
						break;
					}
					else
					{
						if (index == 0)
						{
							cout << "Выход." << endl;
							break;
						}
						cout << "Кажется введён неправильный номер. Попробуйте ещё раз." << endl;
					}
				}
				break;
			}
			else
			{
				cout << "Список пуст." << endl;
				break;
			}

		//Удалить элемент по значению
		case '4':
			if (lst.GetSize())
			{
				int counter = 0;
				cout << "Введите данные, которые хотите удалить: ";
				cin >> data;
				//Поиск элементов по данным
				for (int i = 0; i < lst.GetSize(); i++)
				{
					if (lst[i] == data)
					{
						counter++;
					}
				}

				if (!counter)
				{
					cout << "Элементов не найдено.";
					break;
				}

				cout << "Элементов будет удалено: " << counter << endl;
				for (int i = 0; i < counter; i++)
				{
					lst.removebydata(data);
				}

				break;
			}
			else
			{
				cout << "Список пуст." << endl;
				break;
			}
		//Изменить элемент по номеру
		case '5':
			if (lst.GetSize())
			{
				int data = 0, index = 0;

				cout << "Введите номер элемента, который хотите изменить: ";
				cin >> index; cout << endl;
				if (index - 1 <= lst.GetSize() and index - 1 >= 0)
				{
					cout << "Введите данные: ";
					cin >> data; cout << endl;
					lst.change_data(data, index - 1);
					break;
				}
				else
				{
					cout << "Кажется введён неправильный номер. Попробуйте ещё раз." << endl;
					break;
				}
			}
			else
			{
				cout << "Список пуст. Нечего менять." << endl;
				break;
			}

		//Сортировка списка
		case '6':
			if (lst.GetSize()) 
			{
				lst.SortList();
				break;
			}
			else
			{
				cout << "Список пуст." << endl;
				break;
			}
		//Вывод списка
		case '7':
			if (lst.GetSize())
			{
				cout << "Список:" << endl;
				list_out(lst);
				break;
			}
			else {
				cout << "Список пуст." << endl;
				break;
			}

		//Выход из программы и очистка списка
		case '8':
			lst.clear();
			break;

		default:
			cout << "Этой функции нет!" << endl;
		}
	}

	return 32;
}

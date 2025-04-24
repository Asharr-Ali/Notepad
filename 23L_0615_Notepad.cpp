#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<fstream>

using namespace std;

class notepad
{
	struct node
	{
		char data;
		node* prev;
		node* next;

		node()
		{
			data = '\0';
			prev = next = nullptr;
		}
		node(char a, node* prev, node* next)
		{
			this->data = a;
			this->prev = prev;
			this->next = next;
		}
	};
	node* head, * cursor;
	int size = 0;

public:
	notepad();
	void moveCursorLeft();
	void moveCursorRight();
	void _delete();
	void _insert(char);
	void saveData();
	void loadData();
	void display();
	void run();
	~notepad();
};
notepad::notepad()
{
	head = new node();//dummy node
	cursor = new node('|', head, nullptr);//cursor node
	head->next = cursor;
}
void notepad::moveCursorLeft()
{
	if (cursor->prev->prev)
	{
		char temp = cursor->prev->data;
		cursor->prev->data = cursor->data;
		cursor->data = temp;
		cursor = cursor->prev;
	}
}
void notepad::moveCursorRight()
{
	if (cursor->next)
	{
		char temp = cursor->next->data;
		cursor->next->data = cursor->data;
		cursor->data = temp;
		cursor = cursor->next;
	}
}
void notepad::_delete()
{
	if (cursor->prev->prev)
	{
		node* temp = cursor->prev;
		temp->prev->next = cursor;
		cursor->prev = temp->prev;
		delete temp;
		size--;
	}
}
void notepad::_insert(char data)
{
	cursor->prev->next = new node(data, cursor->prev, cursor);
	cursor->prev = cursor->prev->next;
	size++;
}
void notepad::saveData()
{
	ofstream file("C:\\Users\\Administrator\\source\\repos\\Notepad\\notes.txt");

	if (!file)
		cout << "\nFile Failed to open!\n";

	node* temp = head->next;
	while (temp)
	{
		if(temp->data!='|')
			file << temp->data;
		temp = temp->next;
	}
	file.close();
}
void notepad::loadData()
{
	ifstream file("C:\\Users\\Administrator\\source\\repos\\Notepad\\notes.txt");

	if (!file)
		cout << "\nFile Failed to open!\n";

	char temp;
	while (file.get(temp))
	{
		_insert(temp);
	}
	file.close();
}
void notepad::display()
{
	system("cls");

	cout << "\t\tWelcome to Notepad!!!\n\n";

	node* temp = head->next;
	while (temp)
	{
		cout << temp->data;
		temp = temp->next;
	}

	int footer = 0;
	temp = head->next;
	while (temp != cursor && temp != nullptr)
	{
		footer++;
		temp = temp->next;
	}
	cout << "\n\nCurrent Cursor Position:" << footer;
}
void notepad::run()
{
	loadData();
	while (1)
	{
		display();

		int input = _getch();
		if (input == '\r')
			input = '\n';

		if (input == 0 || input==224)
		{
			input = _getch();
			if (input == 75)
				moveCursorLeft();
			else if (input == 77)
				moveCursorRight();
		}
		else if (input == 8)
			_delete();
		else if (input == 27)
			break;
		else if (input == 19)
			saveData();
		else
			_insert(input);
	}
}
notepad::~notepad()
{
	node* temp = head;
	while (temp)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}
int main()
{
	notepad note1;
	note1.run();
}
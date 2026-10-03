#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <new>

#include <Windows.h>

#include "time.h"

#define DEBUG

// Include <new> header for implementing this
template <typename Data>
class linkedList
{
private:
	
	struct node
	{
		Data Data{};
		node* next{ nullptr };
	};

	node* head{};
	node* tail{};

	int indexes{ 0 };

	// creates new node, handles nullptr
	node* newNode(Data data, node* next)
	{
		node* temp = new (std::nothrow) node{ data,next };

		// handling allocation failure
		if (temp)
		{
			indexes += 1;
			return temp;
		}
		else
		{
			std::cerr << "linked list: memory allocation failed\n";
		}
		return nullptr;
	}

	// O(n) linear search
	node* traverse(int index)
	{
		node* selected{ head };

#ifdef DEBUG
		int complexity{};

		// traversing linked list
		for (int i{}; i < index; ++i)
		{
			if (selected)
			{
				selected = selected->next;
				complexity = i;
			}
			else
			{
				std::cerr << "NULLPTR NODE \n";
				break;
			}

		}
		std::cout << "O(" << complexity << ") ";
#else
		for (int i{}; i < index; ++i)
		{
			if (selected)
			{
				selected = selected->next;
			}
		}
#endif


		if (selected)
		{
			return selected;
		}
		return 0;
	}

public:

	linkedList()
	{
		head = new node( 0, nullptr);
	}
	linkedList( Data data_at_head)
	{
		head = new node(data_at_head, nullptr);
	}

	// leaks memory.
	~linkedList()
	{
		node* next_{ nullptr };
		node* thisNode{ head };
		
		for (int i{ 0 }; i < indexes+1; ++i)
		{
			if (thisNode->next) 
			{
				next_ = thisNode->next;
				delete thisNode;
				thisNode = next_;
			}
			else
			{
				delete thisNode;
			}
		}

	}

	Data at(int index)
	{
		return traverse(index)->Data;
	}

	// probably breaks chain and leaks memory.s
	void append( Data data )
	{
		if (!tail && !head->next)
		{
			tail = newNode(0, nullptr);
			head->next = tail;
		}
		if (!tail->next)
		{
			auto newTail = newNode(0, nullptr);
			tail->next = newTail;
			tail = newTail;
		}
		

	}

	void append_after_head(Data data)
	{
		node* newsecond = traverse(1);
		node* newfirst = newNode(data, newsecond);

		head->next = newfirst;
		
	}

	void push_head(Data data)
	{
		node* newfirst = new node{ head->Data,head->next };
		head->Data = data;
		head->next = newfirst;

		if (!newfirst->next)
		{
			tail = newfirst;
		}
		indexes += 1;
	}

	int size()
	{
		return indexes + 1;
	}

};



int main()
{

	char* start = new char{0};
	char* trackerStart{ start };

	for (int i{ 0 }; i<50000; ++i)
	{
		linkedList<int> somedata{ 0 };
		for (INT64 ii{ 0 }; ii < 20; ++ii)
		{
			somedata.append(ii);
		}
	}


	char* end = new char{ 0 };;
	char* trackerEnd{ end };
	auto delta = std::abs(trackerEnd - trackerStart);

	return 0;
}

/*int WinMain
	(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
) {*/


//int main()
//{
//	bool endProgram{ false };
//	Interval clock{};
//	std::wstring output { L"elapsed" };
//
//	clock.setStart();
//	// std::this_thread::sleep_for(milliseconds(1000));
//	clock.setEnd();
//
//	// MessageBoxW(0, L"working", output.c_str(), MB_OK);
//
//	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	// second argument wAttributes is specified by two hex digits, first - background color, second - text color. 
//	SetConsoleTextAttribute(stdHandle, 0x0F);
//	
//	std::cout << "first message, fucks";
//
//	while (!endProgram)
//	{
//		for (int vkey{ 0 }; vkey < 255; ++vkey)
//		{
//			// if we match one of vkeys and first bit is set true.
//			if (GetAsyncKeyState(vkey) & 0b1)
//			{
//				switch (vkey)
//				{
//				case VK_ESCAPE: { endProgram = true; }
//				}
//			}
//		}
//	}
//
//
//	return 0;
//}

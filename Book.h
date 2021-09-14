#ifndef Book_h
#define Book_h

#include <iostream>

using namespace std;

class Book {
	public:
		string author;
		string title;
		string year;
		string isbn;
		string publisher;
		string llc;
		int stock;

		Book() {
			author = title = isbn = publisher = llc = "";
			stock = 0;
		}

};

#endif // Book_h

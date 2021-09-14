#ifndef Library_h
#define Library_h

using namespace std;

class Library {
private:
	vector <Book> books;
	ifstream dbIn;
	ofstream dbOut;
	int curOrder = 1;

	int toInt(string s) {
		int i = 0;
		int res = 0;
		while (i < s.size())
			res = res * 10 + s[i] - '0', i++;
		return res;
	}
public:
	Library() {
		readFromFile();
	}
	void readFromFile() {																				//Loading database from file
		dbIn.open("lmsdb.csv");
		string unformatted;
		getline(dbIn, unformatted);
		while (getline(dbIn, unformatted)) {
			int i = 0;
			while (i < unformatted.size() && unformatted[i] != ';') i++;								// skipping '#' column
			i++;

			Book b;
			while (i < unformatted.size() && unformatted[i] != ';') b.author += unformatted[i], i++;
			i++;

			while (i < unformatted.size() && unformatted[i] != ';') b.title += unformatted[i], i++;
			i++;

			while (i < unformatted.size() && unformatted[i] != ';') b.year += unformatted[i], i++;
			i++;

			while (i < unformatted.size() && unformatted[i] != ';') b.isbn += unformatted[i], i++;
			i++;

			while (i < unformatted.size() && unformatted[i] != ';') b.publisher += unformatted[i], i++;
			i++;

			while (i < unformatted.size() && unformatted[i] != ';') b.llc += unformatted[i], i++;
			i++;

			while (i < unformatted.size()) b.stock = b.stock * 10 + unformatted[i] - '0', i++;
			i++;

			books.push_back(b);
		}
		dbIn.close();
	}
	void updateFile() {													//Function for updating the output file
		dbOut.open("lmsdb.csv");
		dbOut << "#;Author;Title;Year;ISBN;Publisher;LLC;Stock" << endl;
		int i = 0;
		for (Book& b : books) {
			i++;
			dbOut << i << ";";
			dbOut << b.author << ";";
			dbOut << b.title << ";";
			dbOut << b.year << ";";
			dbOut << b.isbn << ";";
			dbOut << b.publisher << ";";
			dbOut << b.llc << ";";
			dbOut << b.stock;
			dbOut << endl;
		}
		dbOut.close();
	}

	bool exists_book(int ind) {											//Check for existence of the book with given number in the list
		return ind >= 1 && ind <= books.size();
	}

	string out_book(int ind) {
		char buffer[501];
		ind--;
		sprintf(buffer, "%2d | %20s | %60s | %5s | %15s | %15s | %15s | %2d", ind + 1, books[ind].author.c_str(), books[ind].title.c_str(), books[ind].year.c_str(), books[ind].isbn.c_str(), books[ind].publisher.c_str(), books[ind].llc.c_str(), books[ind].stock);
		string str = buffer;
		return str;
	}
	string out_book(Book b) {
		char buffer[501];
		sprintf(buffer, "%20s | %60s | %5s | %15s | %15s | %15s", b.author.c_str(), b.title.c_str(), b.year.c_str(), b.isbn.c_str(), b.publisher.c_str(), b.llc.c_str());
		string str = buffer;
		return str;
	}

	vector <int> find_book(Book fB) {									//Finding index of the book fB in database
		vector <int> res;
		for (int i = 0; i < books.size(); i++) {
			Book b = books[i];
			if (fB.author != "" && fB.author != b.author)
				continue;
			if (fB.title != "" && fB.title != b.title)
				continue;
			if (fB.year != "" && fB.year != b.year)
				continue;
			if (fB.isbn != "" && fB.isbn != b.isbn)
				continue;
			if (fB.publisher != "" && fB.publisher != b.publisher)
				continue;
			if (fB.llc != "" && fB.llc != b.llc)
				continue;
			res.push_back(i);
		}
		return res;
	}

	void add_book(Book b) {
		books.push_back(b);
		updateFile();
	}

	bool delete_book(int ind, int stock) {
		if (!exists_book(ind) || books[ind - 1].stock == 0) {
			return false;
		}
		else {
			books[ind - 1].stock -= min(books[ind - 1].stock, stock);
		}
		updateFile();
		return true;
	}

	bool delete_book(int ind) {
		if (!exists_book(ind)) {
			return false;
		}
		else {
			books.erase(books.begin() + (ind - 1));
		}
		updateFile();
		return true;
	}

	void update_book(int ind, int x, string val) {
		ind--;
		update_book(books[ind], x, val);
	}

	void update_book(Book& b, int x, string val) {
		switch (x) {
			case 1: b.author = val; break;
			case 2: b.title = val; break;
			case 3: b.year = val; break;
			case 4: b.isbn = val; break;
			case 5: b.publisher = val; break;
			case 6: b.llc = val; break;
			case 7: b.stock = toInt(val); break;
			default: break;
		}
	}

	string delimiter(int x) {
		string res = "";
		while (x)
			res += "-", x--;
		return res;
	}

	void display_books(ostream& c) {
		c << " # |          Author      |                              Title                           |  Year |       ISBN      |     Publisher   |        LLC      | Stock" << endl;
		for (int i = 1; i <= books.size(); i++)
			c << delimiter(200) << endl << out_book(i) << endl;
	}
	void display_books(ostream& c, vector<int> ind) {
		c << " # |          Author      |                              Title                           |  Year |       ISBN      |     Publisher   |        LLC      | Stock" << endl;
		for (int i = 0; i < ind.size(); i++)
			c << delimiter(200) << endl << out_book(ind[i] + 1) << endl;
	}

	void sort_books(int curOrder) {
		for (int i = 0; i < books.size(); i++)
			for (int j = i + 1; j < books.size(); j++) {
				bool notToSwap = true;
				Book& x = books[i];
				Book& y = books[j];
				switch (curOrder) {
					case 1: notToSwap = (x.author < y.author); break;
					case 2: notToSwap = (x.title < y.title); break;
					case 3: notToSwap = (x.year < y.year); break;
					case 4: notToSwap = (x.isbn < y.isbn); break;
					case 5: notToSwap = (x.publisher < y.publisher); break;
					case 6: notToSwap = (x.llc < y.llc); break;
					default: break;
				}

				if (!notToSwap)
					swap(books[i], books[j]);

			}
		updateFile();
	}
};

#endif // Library_h

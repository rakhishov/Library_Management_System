#ifndef Display_h
#define Display_h

#include "Library.h"
#include "Book.h"
#include <iomanip>

const int N = 1000;
Library lib;

class Display
{
public:
    void add_book() {
        lib.updateFile();
        string s;
        char xx;
        Book b;
        while (true) {
            system("CLS");																		//Clean the console

            cout<<("\nThe book info:\n");
            cout << lib.out_book(b) << " | " << b.stock;
            cout<<("\n\n");

            cout<<("Book addition menu:\n");
            cout<<("1. Set the author name\n");
            cout<<("2. Set the title of the book\n");
            cout<<("3. Set the year of publication\n");
            cout<<("4. Set ISBN number\n");
            cout<<("5. Set publisher of the book\n");
            cout<<("6. Set LLC number\n");
            cout<<("7. Set number of copies in stock\n");
            cout<<("8. Add book\n");
            cout<<("9. Go back\n");
            cout<<("Please select an option.\n");

            xx = _getch();																	//Get user's choice
            int x = xx - '0';
            if (x == 9)
                return;
            if (x > 9 || x < 1)
                continue;
            if (x == 8) {
                lib.add_book(b);
                cout<<("The book was successfully added! Press any key to continue...\n");
                _getch();
                return;
            }
            cout<<("Enter the value:\n");
            getline(cin, s);
            lib.update_book(b, x, s);														//Update book info
        }
    }

    void delete_book() {
        lib.updateFile();
        Book b;
        char xx;
        string s;
        while (true) {
            system("CLS");

            cout<<("\nCurrent setting for the book is:\n");
            cout << lib.out_book(b);
            cout<<("\n\n");

            cout<<("Book deletion menu:\n");
            cout<<("1. Set the author name\n");
            cout<<("2. Set the title of the book\n");
            cout<<("3. Set the year of publication\n");
            cout<<("4. Set ISBN number\n");
            cout<<("5. Set publisher of the book\n");
            cout<<("6. Set LLC number\n");
            cout<<("7. Find and delete\n");
            cout<<("8. Go back\n");
            cout<<("Select an option, please.\n");

            xx = _getch();
            int x = xx - '0';

            if (x == 8)
                return;
            if (x > 8 || x < 1)
                continue;
            if (x == 7) {
                vector<int> ind = lib.find_book(b);
                if (ind.size() == 0) {										//If such book is not in database
                    cout<<("There are no such books in the library!\n");
                    cout<<("Press any key to continue...\n");
                    _getch();
                    continue;
                }
                else {
                    if (ind.size() == 1) {
                        lib.delete_book(ind[0]);
                    }
                    else {
                        lib.display_books(cout, ind);

                        cout<<("\nEnter the number of the book in the list: ");
                        int ind2 = 0;
                        while (!lib.exists_book(ind2)) {
                            cin >> ind2;
                            if (!lib.exists_book(ind2))
                                cout<<("There is no such book in the list. Try again: ");
                        }
                        string s;
                        getline(cin, s);
                        lib.delete_book(ind2);
                    }

                    cout<<("The book was successfully deleted.\n");
                    cout<<("Press any key to continue...\n");
                    _getch();											//Wait until user presses a key
                    return;
                }
            }

            cout<<("Enter the value:\n");
            getline(cin, s);
            lib.update_book(b, x, s);
        }
    }

    void modify_book() {
        lib.updateFile();
        cout<<("\nEnter the number of the book in the list: ");
        int ind = 0;
        while (!lib.exists_book(ind)) {
            cin >> ind;
            if (!lib.exists_book(ind))
                cout<<("There is no such book in the list. Try again: ");
        }
        string s;
        getline(cin, s);														//To account for newline produced by cin >> ind
        char x;
        while (true) {
            system("CLS");

            cout<<("\nThe book is:\n");
            cout << lib.out_book(ind);
            cout<<("\n\n");

            cout<<("Book modification menu:\n");
            cout<<("1. Set the author name\n");
            cout<<("2. Set the title of the book\n");
            cout<<("3. Set the year of publication\n");
            cout<<("4. Set ISBN number\n");
            cout<<("5. Set publisher of the book\n");
            cout<<("6. Set LLC number\n");
            cout<<("7. Go back\n");
            cout<<("Your choice: ");

            x = _getch();
            if (x == '7')
                return;
            if (x > '7' || x < '1')
                continue;
            cout<<("\nEnter the new value:\n");

            getline(cin, s);

            lib.update_book(ind, x - '0', s);
        }

    }

    void search_book() {
        lib.updateFile();
        char xx;
        string s;
        Book b;
        while (true) {
            system("CLS");

            cout<<("\nCurrent setting for the book is:\n");
            cout << lib.out_book(b);
            cout<<("\n\n");

            cout<<("Book search menu:\n");
            cout<<("1. Set the author name\n");
            cout<<("2. Set the title of the book\n");
            cout<<("3. Set the year of publication\n");
            cout<<("4. Set ISBN number\n");
            cout<<("5. Set publisher of the book\n");
            cout<<("6. Set LLC number\n");
            cout<<("7. Search\n");
            cout<<("8. Go back\n");
            cout<<("Select an option, please.\n");

            xx = _getch();
            int x = xx - '0';

            if (x == 8)
                return;
            if (x > 8 || x < 1)
                continue;
            if (x == 7) {
                vector<int> ind = lib.find_book(b);
                if (ind.size() == 0)										//If such book is not in database
                    cout<<("There is no such book in the library!");
                else {
                    lib.display_books(cout, ind);
                }
                cout<<("\n\nPress any key to continue...\n");
                _getch();											//Wait until user presses a key
                return;
            }

            cout<<("Enter the value:\n");
            getline(cin, s);
            lib.update_book(b, x, s);
        }
    }

    void display_books() {
        lib.updateFile();
        char xx;
        string s;
        system("CLS");
        while (true) {

            cout<<("Sorting menu:\n");
            cout<<("1. Sort by author name\n");
            cout<<("2. Sort by title of the book\n");
            cout<<("3. Sort by year of publication\n");
            cout<<("4. Sort by ISBN number\n");
            cout<<("5. Sort by publisher of the book\n");
            cout<<("6. Sort by LLC number\n");
            cout<<("7. Display the list\n");
            cout<<("8. Go back\n");
            cout<<("Select an option, please.\n");

            xx = _getch();
            int x = xx - '0';
            if (x == 8)
                return;
            if (x > 8 || x < 1)
                continue;
            if (x != 7) {
                lib.sort_books(x);
                cout<<("The list was successfully sorted!\n\n");
                continue;
            }
            lib.display_books(cout);
            cout<<("\nPress any key to continue...\n");
            _getch();
            return;
        }
    }

    void issue_book() {
        lib.updateFile();
        cout<<("Enter ISBN number of the book to issue:\n");
        string s;
        getline(cin, s);
        Book b;
        b.isbn = s;
        vector <int> ind = lib.find_book(b);
        if (ind.size() == 0) {
            cout<<("Books not available\n");
            cout<<("Press any key to continue...\n");
            _getch();
            return;
        }
        if (lib.delete_book(ind[0] + 1, 1))
            cout<<("Book Issued\n");
        else
            cout<<("Books not available\n");
        cout<<("Press any key to continue...\n");
        _getch();
    }

    void return_book() {
        lib.updateFile();
        cout<<("Enter ISBN number of the book to return:\n");
        string s;
        getline(cin, s);
        Book b;
        b.isbn = s;
        vector <int> ind = lib.find_book(b);
        if (ind.size() == 0) {
            cout<<("Incorrect ISBN\n");
            cout<<("Press any key to continue...\n");
            _getch();
            return;
        }
        lib.update_book(ind[0] + 1, 7, "1");
        cout<<("Book successfully returned.\nPress any key to continue...\n");
        _getch();
    }

    void showMenu()
    {
        system("CLS");
        cout<<setw(80)<<("Welcome to the Library Management System!\n");
        cout<<("1. Add a book\n");
        cout<<("2. Delete a book\n");
        cout<<("3. Modify a book\n");
        cout<<("4. Search a book\n");
        cout<<("5. Display the list of books\n");
        cout<<("6. Issue a book by taking the ISBN as input\n");
        cout<<("7. Return a book by using the book ISBN as input\n");
        cout<<("8. Exit\n\n");
        cout<<("Please select an option.\n");
        char x = _getch();
        switch (x) {
            case '1': add_book(); break;
            case '2': delete_book(); break;
            case '3': modify_book(); break;
            case '4': search_book(); break;
            case '5': display_books(); break;
            case '6': issue_book(); break;
            case '7': return_book(); break;
            case '8': return;
            default:
                break;
        }
        showMenu();
    }

};

#endif // Display_h

export module library;

import <iostream>;
import <concepts>;
import <vector>;
import <string>;

class Book {
private:
	std::string author;
	std::string title;
	int ISBN;
	bool is_borrowed;

public:
	Book(std::string author, std::string title, int ISBN) : author(author), title(title), ISBN(ISBN) {}

	bool borrow_book() {
		if (is_borrowed)
			return false;

		is_borrowed = true;
		return is_borrowed;
	}

	bool return_book() {
		if (!is_borrowed)
			return true;

		is_borrowed = false;
		return is_borrowed;
	}

	std::string get_author() {
		return author;
	}

	std::string get_title() {
		return title;
	}

	int get_ISBN() {
		return ISBN;
	}
	
	std::string set_author(std::string new_author) {
		author = new_author;
	}

	std::string set_title(std::string new_title) {
		title = new_title;
	}
};

template<typename B>
concept book = std::same_as<B, Book>;

std::vector<Book> Bookshelf;

void print_menu() {
	std::cout << "Bibliotheca Alexandria" << std::endl
		<< "1) Add a book" << std::endl
		<< "2) Borrow a book" << std::endl
		<< "3) Return a book" << std::endl
		<< "4) List books" << std::endl
		<< "5) Quit" << std::endl;
	
}

void add_book() {
	std::string title, author;
	int ISBN;

	std::cout << "Provide author: ";
	std::cin >> author;

	std::cout << "Provide title: ";
	std::cin >> title;

	std::cout << "Provide ISBN: ";
	std::cin >> ISBN;

	Book new_book(author, title, ISBN);
	Bookshelf.push_back(new_book);
}

Book* find_book(int ISBN) {
	for (auto b : Bookshelf) {
		if (b.get_ISBN() == ISBN) {
			return &b;
		}
	}
}

void borrow_book() {
	int ISBN;

	std::cout << "Provide ISBN: " << std::endl;
	std::cin >> ISBN;

	Book* found_book = find_book(ISBN);

	if (found_book == nullptr) {
		std::cout << "Book not found" << std::endl;
		return;
	}

	bool check = found_book->borrow_book();

	if (check) {
		std::cout << "Book is already borrowed!" << std::endl;
		return;
	}

	std::cout << "Book borrowed!" << std::endl;
}

void return_book() {
	int ISBN;

	std::cout << "Provide ISBN: " << std::endl;
	std::cin >> ISBN;

	Book* found_book = find_book(ISBN);

	if (found_book == nullptr) {
		std::cout << "Book not found" << std::endl;
		return;
	}

	bool check = found_book->return_book();

	if (!check) {
		std::cout << "Book is not borrowed!" << std::endl;
		return;
	}

	std::cout << "Book returned!" << std::endl;
}

void list_books() {
	for (auto b : Bookshelf) {
		std::cout << b.get_ISBN() << ": " << b.get_author() << " - " << b.get_title() << std::endl;
	}
}

export void start_library() {
	int choice;
	bool quit = true;

	while (quit)
	{
		print_menu();
		std::cout << "Choose option: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			add_book();
			break;
		case 2: 
			borrow_book();
			break;
		case 3:
			return_book();
			break;
		case 4:
			list_books();
			break;
		case 5:
		default:
			quit = false;
			break;
		}
	}
}
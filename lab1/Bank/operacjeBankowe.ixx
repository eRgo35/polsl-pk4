export module operacjeBankowe;
export import kontoBankowe;
export import <iostream>;

export void stanKonta(Konto& account)
{
	double balans = account.getStanKonta();
	std::cout << account.getImie()
		<< " " << account.getNazwisko()
		<< std::endl << "Balans: "
		<< balans << "PLN" << std::endl;
}

export void wplataPieniedzy(Konto& account, double amount) {
	account.setStanKonta(account.getStanKonta() + amount);
	std::cout << account.getImie()
		<< " " << account.getNazwisko()
		<< std::endl << "Wpłacono: "
		<< account.getStanKonta() << "PLN" << std::endl;
}

export void wyplataPieniedzy(Konto& account, double amount) {
	account.setStanKonta(account.getStanKonta() - amount);
	std::cout << account.getImie()
		<< " " << account.getNazwisko()
		<< std::endl << "Wpłacono: "
		<< account.getStanKonta() << "PLN" << std::endl;
}

export void przelewSrodkow(Konto& from_account, Konto& to_account, double amount) {
	from_account.setStanKonta(from_account.getStanKonta() - amount);
	to_account.setStanKonta(to_account.getStanKonta() + amount);

	std::cout << "Przelew z konta: " << from_account.getImie()
		<< " " << from_account.getNazwisko() <<
		std::endl << "Na konto: " << to_account.getImie() <<
		" " << to_account.getNazwisko() << std::endl <<
		"Kwota: " << amount << "PLN" << std::endl;
}
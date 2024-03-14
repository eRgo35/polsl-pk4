export module menuBankowe;
import <vector>;
import operacjeBankowe;

export void menuGlowne() {
	char option;
	std::vector<Konto> konta;

	do {
		std::cout << "Menu Główne:" << std::endl
			<< "1) Tworzenie konta bankowego" << std::endl
			<< "2) Aktualny stan konta" << std::endl
			<< "3) Wpłata środków na konto" << std::endl
			<< "4) Wypłata środków z konta" << std::endl
			<< "5) Przelew środków między kontami" << std::endl
			<< "q) Wyjście z programu" << std::endl
			<< std::endl;
		std::cout << "Wybierz operację: ";

		std::cin >> option;

		switch (option) {
		case '1':
		{
			std::string imie;
			std::string nazwisko;

			std::cout << "Imię: ";
			std::cin >> imie;

			std::cout << "Nazwisko: ";
			std::cin >> nazwisko;

			double kwota_startowa = 0.00;
			Konto konto(imie, nazwisko, kwota_startowa);

			int numer_konta = konto.getNumerKonta();

			std::cout << "Dziękujemy za utworzenie konta!" << std::endl <<
				"Twój numer konta: " << numer_konta << std::endl;

			konta.push_back(konto);
		}
		break;
		case '2':
		{
			int numer_konta;

			std::cout << "Numer Konta: ";
			std::cin >> numer_konta;

			for (int i = 0; i < konta.size(); i++)
			{
				if (numer_konta == konta.at(i).getNumerKonta())
				{
					stanKonta(konta.at(i));
				}
			}
		}
		break;
		case '3':
		{
			int numer_konta;
			double kwota;

			std::cout << "Numer Konta: ";
			std::cin >> numer_konta;

			std::cout << "Kwota do wpłaty: ";
			std::cin >> kwota;

			for (int i = 0; i < konta.size(); i++)
			{
				if (numer_konta == konta.at(i).getNumerKonta())
				{
					wplataPieniedzy(konta.at(i), kwota);
				}
			}
		}
		break;
		case '4':
		{
			int numer_konta;
			double kwota;

			std::cout << "Numer Konta: ";
			std::cin >> numer_konta;

			std::cout << "Kwota do wypłaty: ";
			std::cin >> kwota;

			for (int i = 0; i < konta.size(); i++)
			{
				if (numer_konta == konta.at(i).getNumerKonta())
				{
					wyplataPieniedzy(konta.at(i), kwota);
				}
			}
		}
		break;
		case '5':
		{
			int from_numer_konta;
			int to_numer_konta;
			double kwota;

			std::cout << "Numer Konta Nadawcy: ";
			std::cin >> from_numer_konta;

			std::cout << "Numer Konta Odbiorcy: ";
			std::cin >> to_numer_konta;

			std::cout << "Kwota do przelewu: ";
			std::cin >> kwota;

			for (int i = 0; i < konta.size(); i++)
			{
				if (from_numer_konta == konta.at(i).getNumerKonta()) {
					for (int j = 0; j < konta.size(); j++)
					{
						if (to_numer_konta == konta.at(j).getNumerKonta()) {
							przelewSrodkow(konta.at(i), konta.at(j), kwota);
						}
					}
				}
			}
		}
		break;
		case 'q':
		case 'Q':
			std::cout << "Zamykanie aplikacji" << std::endl;
		default:
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Niepoprawna operacja!" << std::endl;
		}
		std::cout << std::endl;
	} while (option != 'q');
}
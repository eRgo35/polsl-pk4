export module kontoBankowe;
import <chrono>;

export class Konto {
private:
	int numerKonta;
	std::string imie;
	std::string nazwisko;
	double stanKonta;

public:
	Konto(std::string imie, std::string nazwisko, double stanKonta) : imie(imie), nazwisko(nazwisko), stanKonta(stanKonta) {
		auto id = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		numerKonta = id;
	}

	int getNumerKonta() {
		return numerKonta;
	}

	std::string getImie() {
		return imie;
	}

	std::string getNazwisko() {
		return nazwisko;
	}

	double getStanKonta() {
		return stanKonta;
	}

	void setNumerKonta(int newNumerKonta) {
		numerKonta = newNumerKonta;
	}

	void setImie(std::string newImie) {
		imie = newImie;
	}

	void setNazwisko(std::string newNazwisko) {
		nazwisko = newNazwisko;
	}

	void setStanKonta(double newStanKonta) {
		stanKonta = newStanKonta;
	}
};
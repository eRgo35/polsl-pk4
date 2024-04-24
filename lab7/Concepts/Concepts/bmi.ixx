export module bmi;

import <iostream>;
import <random>;
import <vector>;
import <thread>;
import <mutex>;

class Student {
private:
	int id;
	double weight;
	double height;
	double BMI;

public:
	Student(int id, double weight, double height) : id(id), weight(weight), height(height) { 
		
	}

	int get_id() {
		return id;
	}

	double get_weight() {
		return weight;
	}

	double get_height() {
		return height;
	}

	double get_BMI() {
		return BMI;
	}

	void set_BMI(double new_BMI) {
		BMI = new_BMI;
	}
};

export template<typename N>
concept Double = std::same_as<N, int> || std::floating_point<N>;

std::mutex mux;
std::vector<Student> students;


export template<typename G>
requires Double<G>
double generate_number(G min, G max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(min, max);

	return distrib(gen);
}

void calcualte_bmi(Student& student) {
	double BMI = student.get_weight() / (student.get_height() * student.get_height()) * 10'000;
	student.set_BMI(BMI);
}

void wrong_BMI(Student& student) {
	if (student.get_BMI() > 27 || student.get_BMI() < 17)
		std::cout << student.get_id() << " | w: " << student.get_weight() << " | h: " << student.get_height() << " | BMI: " << student.get_BMI() << std::endl;
}

void generate_student(int i, std::vector<Student> &students_vector) {
	Student student(i, generate_number(40.0, 110.0), generate_number(140.0, 210.0));
	
	calcualte_bmi(student);
	wrong_BMI(student);
	
	std::lock_guard<std::mutex> guard(mux);
	students_vector.push_back(student);
}

void generate_students(int how_many) {
	for (int i = 0; i < how_many; ++i) {
		std::jthread thread1(generate_student, std::ref(i), std::ref(students));
		std::jthread thread2(generate_student, std::ref(++i), std::ref(students));
	}

}

export void bmi() {
	std::cout << "Generating students..." << std::endl;
	
	generate_students(100);
}
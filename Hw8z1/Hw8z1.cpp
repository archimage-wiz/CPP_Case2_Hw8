
#include <iostream>
#include <exception>


namespace std {
	class bed_length : exception {
		public:const char* what() const override {
			return "Вы ввели слово запретной длины! До свидания";
		}
	};
}


int function(std::string in_str, int forbidden_length) {

	if (in_str.length() == forbidden_length) {
		throw std::bed_length();
	}
	return in_str.length();
}


int main() { setlocale(LC_ALL, "Ru");

	int forbidden_length = 5;

	while (true)
	{
		std::string new_str;
		std::cout << "ВВедите строку запретной длинны" << std::endl;
		std::cin >> new_str;
		try {
			std::cout << "Длинна слова " << new_str << char(32) << function(new_str, forbidden_length) << std::endl;
		} catch (const std::bed_length err) {
			std::cout << err.what() << std::endl;
			break;
		}
	}

	return 0;
}

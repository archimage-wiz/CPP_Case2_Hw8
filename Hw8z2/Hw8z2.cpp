#include <iostream>


class fig_creation_error : std::domain_error {
    public:
        fig_creation_error(std::string err_msg) : std::domain_error(err_msg) {
            
        }
        public:const char* what() const override {
            return this->std::domain_error::what(); // че это я тут понаписал сам не понял =)
        }
};


class Figure {

private:
    int x_sides_count = 0;

protected:
    std::string x_name;
    Figure(int sides_count) {
        x_sides_count = sides_count > 0 ? sides_count : 0;
    }

public:
    virtual bool check() {
        return x_sides_count == 0 ? true : false;
    }
    virtual void print_info(Figure* p_base) {
        std::cout << x_name + ":" << std::endl;
        std::cout << (p_base->check() == true ? "Правильная" : "Неправильная") << std::endl;
        std::cout << "Количество сторон: " << get_sides_count() << std::endl;
    }

    Figure() : Figure(0) {
        x_name = "Фигура";
    }
    virtual int get_sides_count() {
        return x_sides_count;
    }
    virtual std::string get_name() {
        return x_name;
    }

};

class Triangle : public Figure {

protected:
    int _a, _b, _c, _A, _B, _C;

public:
    Triangle(int a, int b, int c, int A, int B, int C) : _a(a), _b(b), _c(c), _A(A), _B(B), _C(C), Figure(3) {
        x_name = "Треугольник";
        if(!this->check()) throw fig_creation_error("Error (_A + _B + _C) != 180");
    }
    virtual bool check() {
        return (get_sides_count() == 3 && (_A + _B + _C) == 180) ? true : false;
    }
    virtual void print_info(Figure* p_base) override {
        Figure::print_info(p_base);
        std::cout << "Стороны:";
        std::cout << " a=" << _a << " b=" << _b << " c=" << _c << std::endl;
        std::cout << "Углы:";
        std::cout << " A=" << _A << " B=" << _B << " C=" << _C << std::endl;
    }

};

class RightTriangle : public Triangle {
public:
    virtual bool check() {
        if (Triangle::check())
            return (_C == 90) ? true : false;
        else
            return false;
    }

    RightTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
        x_name = "Прямоугольный треугольник";
        if (!this->check()) throw fig_creation_error("Error _C != 90");
    }
};



int main() {
    setlocale(LC_ALL, "Ru");

    Figure fig;
    Triangle fig1(10, 20, 30, 50, 60, 70);
    RightTriangle fig_rt(10, 20, 30, 50, 40, 90);
    RightTriangle * fig_rt2 = nullptr;

    try {
        fig_rt2 = new RightTriangle (10, 20, 30, 100, 70, 10);
    } catch (const fig_creation_error err) {
        std::cout << "Прямоугольный треугольник не был создан. Причина: " << err.what() << std::endl;
    }
    try {
        fig_rt2 = new RightTriangle(10, 20, 30, 50, 50, 90);
    } catch (const fig_creation_error err) {
        std::cout << "Прямоугольный треугольник не был создан. Причина: " << err.what() << std::endl;
    }
    std::cout << std::endl;

    Figure* p_base;
    p_base = &fig;
    p_base->print_info(p_base);
    std::cout << std::endl;

    p_base = &fig1;
    p_base->print_info(p_base);
    std::cout << std::endl;

    p_base = &fig_rt;
    p_base->print_info(p_base);
    std::cout << std::endl;

    if (fig_rt2 != nullptr) {
        p_base = fig_rt2;
        p_base->print_info(p_base);
        std::cout << std::endl;
    }


    return 0;
}


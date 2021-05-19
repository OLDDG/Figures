#include <string> 
#include <sstream> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Figure {
public:
    virtual double get_square() const = 0;
    virtual ~Figure() {}
    virtual std::string to_string() = 0;
    virtual bool equals (const Figure *fig) = 0;
};

class Rectangle: public Figure {
    double a_, b_;
public: 
    Rectangle (double a = 0.0, double b = 0.0): a_(a),b_(b) {}
    virtual double get_square () const {
        return a_ * b_;
    }
    virtual std::string to_string() {
        std::string s; 
        std::ostringstream out;
        out << 'R' << " " << a_ << " " << b_;
        return out.str();
    }
    static Rectangle* make (const std::string &s) {
        std::stringstream str (s);
        double a, b;
        str >> a >> b;
        Rectangle *rect = new Rectangle(a, b);
        return rect;
    }
    bool equals (const Figure *fig) {
        const Rectangle *rec = dynamic_cast<const Rectangle*> (fig);
        return rec->a_ == a_ && rec->b_ == b_;
    }
};

class Square: public Figure {
    double a_;
public:
    Square (double a = 0.0): a_(a){}
    virtual double get_square () const{
        return a_ * a_;
    }
    virtual std::string to_string() {
        std::string s;
        std::ostringstream out;
        out << "S " << a_;
        return out.str();
    }
    static Square* make (const std::string &s) {
        std::stringstream str(s);
        double a;
        str >> a;
        Square *sqr = new Square(a);
        return sqr;
    }
    bool equals (const Figure *fig) {
        const Square *sqr = dynamic_cast<const Square*> (fig);
        return sqr->a_ == a_;
    }
};

class Circle: public Figure {
    double r_;
public:
    Circle (double r): r_(r) {}
    virtual double get_square () const{
        return M_PI * r_ * r_;
    }
    virtual std::string to_string() {
        std::string s, s_cat;
        std::stringstream out;
        out << "C " << r_;
        return out.str();
    }
    static Circle* make (const std::string &s) {
        std::stringstream str(s);
        double r;
        str >> r;
        Circle *circ = new Circle(r);
        return circ;
    }
    bool equals (const Figure *fig) {
        const Circle *circ = dynamic_cast<const Circle*> (fig);
        return circ->r_ == r_;
    }
};

class Factory {
    Factory() {};
public: 
    static Factory *factory_instance (){
        static Factory *fact;
        return fact;
    }
    Figure* make (const std::string &s)const {
        std::stringstream str(s);
        char c;
        str >> c;
        std::string params;
        std::getline (str, params);
        if (c == 'R') {
            return Rectangle::make(params);
        }
        else if (c == 'S') {
            return Square::make(params);
        }
        else if (c == 'C') {
            return Circle::make(params);
        }
        else return nullptr;
    }
};

int main() {
    std::string s;
    Factory *f {Factory::factory_instance()};
    std::vector <Figure*> v;
    while (std::getline(std::cin, s)) {
        v.push_back(f->make(s));
    }
    stable_sort(v.begin(), v.end(), 
                [](Figure *a, Figure *b) -> bool {return a->get_square() < b->get_square();});
    for (auto x: v) {
        std::cout << x->to_string() << std::endl;
    }
    for (auto x: v) delete x;
    delete f;
}

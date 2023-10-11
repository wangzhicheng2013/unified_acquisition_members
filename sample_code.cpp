#include <iostream>
#include <string>
#include <cassert>
class person_privacy {
private:
    int a_;
    int b_;
    std::string c_;
public:
    person_privacy(int a, int b, const std::string& c) : a_(a),
                                                   b_(b),
                                                   c_(c) {}
    person_privacy(int a, int b, std::string&& c) : a_(a),
                                                   b_(b),
                                                   c_(c) {}
    person_privacy(const person_privacy& p) {
        a_ = p.get_a();
        b_ = p.get_b();
        c_ = p.get_c();
    }
    person_privacy(person_privacy&& p) {
        a_ = p.get_a();
        b_ = p.get_b();
        c_ = p.get_c();
    }
    int get_a() const {
        return a_;
    }
    int get_b() const {
        return b_;
    }
    std::string get_c() const {
        return c_;
    }
};
static const int FILEDS = 5;
class person {
private:
    std::string name_;
    int age_;
    person_privacy privacy_;
public:
    person(const std::string& name, int age, const person_privacy& privacy) : name_(name),
                                                                        age_(age),
                                                                        privacy_(privacy) {}
    person(std::string&& name, int age, const person_privacy& privacy) : name_(name),
                                                                        age_(age),
                                                                        privacy_(privacy) {}
    person(std::string&& name, int age, person_privacy&& privacy) : name_(name),
                                                                        age_(age),
                                                                        privacy_(privacy) {}
    std::string get_name() const {
        return name_;
    }
    int get_age() const {
        return age_;
    }
    template<size_t index>
    decltype(auto) get_info() const {
        static_assert(index < FILEDS);
        if constexpr (0 == index) {
            return get_name();
        }
        else if constexpr (1 == index) {
            return get_age();
        }
        else if constexpr (2 == index) {
            return privacy_.get_a();
        }
        else if constexpr (3 == index) {
            return privacy_.get_b();
        }
        else if constexpr (4 == index) {
            return privacy_.get_c();
        }
    }
};
int main() {
    person zhang_san("zhangsan", 18, person_privacy(1, 2, "3"));
    std::cout << zhang_san.get_info<0>() << std::endl;
    std::cout << zhang_san.get_info<1>() << std::endl;
    std::cout << zhang_san.get_info<2>() << std::endl;
    std::cout << zhang_san.get_info<3>() << std::endl;
    std::cout << zhang_san.get_info<4>() << std::endl;

    return 0;
}
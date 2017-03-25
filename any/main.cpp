#include <bits/stdc++.h>
#include "any.h"


const int ITER_NUM = (int) 5e6;
void divider() {
    std::cout << "\n*************************************\n";
}

struct alignas(128) big {
    int field;

    big(int field) : field(field) {}

    big(const big& other) {
        field = other.field;
    }

    big(big&& other) {
        field = other.field;
    }
};



void test_4() {
    for (int i = 0; i < 100000; i++) {
        big cc(i);
        any temp1(cc);
        any temp2(temp1);
        std::cout << any_cast<big>(temp2).field << '\n';
    }
}

void test_5() {
    for (int i = 0; i < 100000; i++) {
        any temp1(i);
        any temp2(temp1);
        std::cout << any_cast<big>(temp2).field << '\n';
    }
}

void test_6() {
    any a(true);
    any b(1ll);
    std::cout << any_cast<char>(a) << '\n';
    std::cout << any_cast<double>(b) << '\n';
    a.swap(b);
    std::cout << any_cast<char>(b) << '\n';
    std::cout << any_cast<double>(a) << '\n';
}

void test_big_big() {
    std::vector<int> _a;
    std::string _b = "123";
    _a.push_back(128);

    any a(_a), b(_b);
    a.swap(b);
    std::cout << any_cast<std::vector<int>>(b)[0] << '\n';
    std::cout << any_cast<std::string>(a) << '\n';
    divider();
}

void test_big_small() {
    std::vector<int> _a;
    int _b = 123;
    _a.push_back(128);
    
    any a(_a), b(_b);
    a.swap(b);
    std::cout << any_cast<std::vector<int>>(b)[0] << '\n';
    std::cout << any_cast<int>(a) << '\n';
    divider();
}

void test_small_big() {
    std::vector<int> _a;
    int _b = 123;
    _a.push_back(128);
    
    any a(_a), b(_b);
    b.swap(a);
    std::cout << any_cast<std::vector<int>>(b)[0] << '\n';
    std::cout << any_cast<int>(a) << '\n';
    divider();
}

void test_small_small() {
    double _a = 128.0;
    int _b(123);
    
    any a(_a), b(_b);
    b.swap(a);
    std::cout << any_cast<double>(b) << '\n';
    std::cout << any_cast<int>(a) << '\n';
    divider();
}

void test_small() {
    for (int i = 0; i < ITER_NUM; i++) {
        int a = rand();
        any x(a);
        assert(any_cast<int>(x) == a);
    } 

    for (int i = 0; i < ITER_NUM; i++) {
        double a = 1.0 * rand() + 0.42;
        any x(a);
        assert(any_cast<double>(x) == a);
    }

    for (int i = 0; i < ITER_NUM; i++) {
        int a = rand();
        double b = 0.42 + rand();
        any x(a), y(b);
        x.swap(y);
        assert(any_cast<int>(y) == a && any_cast<double>(x) == b);
    }
}

void test_big() {
    std::vector <std::string> vec;
    vec.push_back("hello[0]");
    vec.push_back("1111111[1]");
    vec.push_back("itmonet.com[2]");
    vec.push_back("variable[3]");
    int n = (int) vec.size();
    any a(vec);
    int num = 101;
    any b(num);

    a.swap(b);
    
    assert(any_cast<int>(a) == num); // small 

    for (int i = 0; i < n; i++) {
        std::cout << any_cast<std::vector<std::string> >(b)[i] << "\n"; 
    }
}

int main() {
    // test_1();
    // test_2();
    // test_3();
     test_4();
     test_5();
     test_6();
     test_big_big();
     test_small_big();
     test_big_small();
     test_small_small();
    test_big();
	 test_small();
    return 0;
}

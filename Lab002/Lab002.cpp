// Lab002.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <stack>

struct Point
{
    unsigned long long const x, y;

    Point(unsigned long long x, unsigned long long y) : x(x), y(y) { }

    Point minx(Point const& rha) const
    {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const& rha) const
    {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const& rha) const
    {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const& rha) const
    {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const
    {
        std::cout << '(' << x << ',' << y << ')';
    }
};

class Rectangle
{
private:
    Point const urp;

public:
    Rectangle() : urp(0, 0) { }

    Rectangle(Point const& urp) : urp(urp) { }

    Rectangle operator+(Rectangle const& rha) const
    {
        return Rectangle(urp.maxx(rha.urp).maxy(rha.urp));
    }

    Rectangle operator*(Rectangle const& rha) const
    {
        return Rectangle(urp.minx(rha.urp).miny(rha.urp));
    }

    void print() const
    {
        urp.print();
    }
};

std::string infix2rpn(std::string expr)
{
    std::string res = "";
    std::stack<char> oper;

    for (auto i : expr)
        switch (i) {
            case '+' : {
                while (!oper.empty()) {
                    res.push_back(oper.top());
                    oper.pop();
                }
                oper.push(i);
            }
            break;

            case '*' : {
                while (!oper.empty() && oper.top() != '+') {
                    res.push_back(oper.top());
                    oper.pop();
                }
                oper.push(i);
            }
            break;

            case '(' : case ',' : case ')' :
            case '1' : case '2' : case '3' : case '4' : case '5' : 
            case '6' : case '7' : case '8' : case '9' : case '0' : {
                res.push_back(i);
            }
            break;
        }

    while (!oper.empty()) {
        res.push_back(oper.top());
        oper.pop();
    }

    return res;
}

Rectangle str2rect(std::string str)
{
    unsigned long long x, y;
    sscanf_s(str.c_str(), "(%llu,%llu)", &x, &y);
    return Rectangle(Point(x, y));
}

Rectangle compex(std::string expr)
{
    std::string rect = "";
    std::stack<Rectangle> res;

    for (auto i : expr)
        switch (i) {
            case '+' : {
                auto op1 = res.top();
                res.pop();
                auto op2 = res.top();
                res.pop();
                res.push(op1 + op2);
            }
            break;

            case '*' : {
                auto op1 = res.top();
                res.pop();
                auto op2 = res.top();
                res.pop();
                res.push(op1 * op2);
            }
            break;

            case ')' : {
                rect.push_back(i);
                res.push(str2rect(rect));
                rect.clear();
            }
            break;

            default : {
                rect.push_back(i);
            }
        }

    return res.top();
}

int main()
{
    std::string in;
    std::getline(std::cin, in);

    compex(infix2rpn(in)).print();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

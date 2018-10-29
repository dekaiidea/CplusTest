#include <iostream>
using namespace std;

// Point类
class Point
{
    // 构造函数与析构函数
    public:
        Point(int _x = 0, int _y = 0) : x(_x), y(_y){}
        ~Point(){}
    // 普通成员函数
    public:
        // 输出点的坐标
        void showPosition(){cout << "(" << x << ", " << y << ")" << endl;}
    // 运算符函数重载
    public:
        // 前置， ++i\--i
        Point operator ++();
        Point operator --();
        // 后置,i++\i--
        Point operator ++(int);
        Point operator --(int);
        //加法
        Point operator +(Point b);
    private:
        int x;
        int y;
};

Point Point::operator ++()
{
    Point po;
    po.x = x + 1;
    po.y = y + 1;

    x += 1;
    y += 1;

    return po;
}

Point Point::operator --()
{
    Point po;
    po.x = x - 1;
    po.y = y - 1;

    x -= 1;
    y -= 1;

    return po;
}

Point Point::operator ++(int)
{
    Point po;
    po.x = x;
    po.y = y;

    x += 1;
    y += 1;

    return po;
}

Point Point::operator --(int)
{
    Point po;
    po.x = x;
    po.y = y;

    x -= 1;
    y -= 1;

    return po;
}

Point Point::operator +(Point b)
{
    Point po;
    po.x = this->x+b.x;
    po.y = this->y+b.y;

    return po;
}


int main()
{
    Point po(0, 0);
    Point po1(2, 3);
    Point po2(1, 4);

    // 三点初始坐标
    cout << "Position po: "; po.showPosition();
    cout << "Position po1: "; po1.showPosition();
    cout << "Position po2: "; po2.showPosition();
    cout << "_______________" << endl;

    // 后置运算后的坐标
    po = po1++;
    cout << "Pos ++: po = "; po.showPosition();
    cout << "Pos ++: po1 = "; po1.showPosition();
    po = po2--;
    cout << "Pos --: po = "; po.showPosition();
    cout << "Pos --: po2 = "; po2.showPosition();
    cout << "_______________" << endl;

    // 前置运算后的坐标
    po = ++po1;
    cout << "Pre ++: po = "; po.showPosition();
    cout << "Pre ++: po1 = "; po1.showPosition();
    po = --po2;
    cout << "Pre --: po = "; po.showPosition();
    cout << "Pre --: po2 = "; po2.showPosition();

    //加法重载
    Point result = po1+po2;

    return 0;
}
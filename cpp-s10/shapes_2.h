#pragma once
// ������ _USE_MATH_DEFINES ���������, ����� ��� ����������� <cmath> ���� ��������� ��������� M_PI
#define _USE_MATH_DEFINES
// ������ _USE_MATH_DEFINES ������� �������� �� ����������� ������ ������������ ������,
// ������� ����� ���������� <cmath> ������
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

enum class Color { RED, GREEN, BLUE };

ostream& operator<<(ostream& out, Color color) {
    switch (color) {
    case Color::RED:
        out << "red"s;
        break;
    case Color::GREEN:
        out << "green"s;
        break;
    case Color::BLUE:
        out << "blue"s;
        break;
    }
    return out;
}

class Shape {
public:
    explicit Shape(const Color color)
        : color_(color) {
    }

    virtual string GetType() const {
        return "Shape"s;
    }

    virtual Color GetColor() const {
        return color_;
    }

    virtual double GetArea() const {
        return 0.0;
    }

    virtual void SetColor(Color color) {
        color_ = color;
    }

private:
    Color color_;
};

class Rectangle : public Shape {
public:
    explicit Rectangle(const double width, const double height, Color color)
        : Shape(color)
        , width_(width)
        , height_(height) {
    }

    virtual double GetArea() const override {
        return width_ * height_;
    }

    virtual std::string GetType() const override {
        return "Rectangle";
    }

    virtual Color GetColor() const override {
        return Shape::GetColor();
    }

    int GetWidth() const {
        return width_;
    }

    int GetHeight() const {
        return height_;
    }

    virtual void SetColor(Color color) override {
        Shape::SetColor(color);
    }

    void SetSize(int width, int height) {
        width_ = width;
        height_ = height;
    }

private:
    double width_;
    double height_;
};

class Circle : public Shape {
public:
    explicit Circle(const double radius, const Color color)
        : Shape(color)
        , radius_(radius) {
    }

    virtual double GetArea() const override {
        return radius_ * radius_ * M_PI;
    }

    virtual std::string GetType() const override {
        return "Circle";
    }

    virtual Color GetColor() const override {
        return Shape::GetColor();
    }

    virtual void SetColor(Color color) override {
        Shape::SetColor(color);
    }

    inline void SetRadius(double radius) {
        radius_ = radius;
    }

    double GetRadius() const {
        return radius_;
    }

private:
    double radius_;
};

// ���������� ��������� ������� �����, ��������� �� ������� ��������� � ���������� ��������� collection
template <typename ShapeCollection>
double CalcSumArea(const ShapeCollection& collection) {
    double sum = 0.0;
    for (const Shape* shape : collection) {
        sum += shape->GetArea();
    }
    return sum;
}

void PrintShapeInfo(const Shape& shape) {
    cout << shape.GetType() << ": color: "s << shape.GetColor() << ", area:"s << shape.GetArea() << endl;
}

void TestShapes() {
    Circle c{ 10.0, Color::RED };
    Rectangle r{ 10, 20, Color::BLUE };
    Shape sh{ Color::GREEN };

    const Shape* shapes[] = { &c, &r, &sh };

    assert(sh.GetType() == "Shape"s);
    assert(c.GetType() == "Circle"s);
    assert(r.GetType() == "Rectangle"s);

    assert(sh.GetColor() == Color::GREEN);
    assert(c.GetColor() == Color::RED);
    assert(r.GetColor() == Color::BLUE);
    sh.SetColor(Color::BLUE);
    c.SetColor(Color::GREEN);
    r.SetColor(Color::RED);
    assert(sh.GetColor() == Color::BLUE);
    assert(c.GetColor() == Color::GREEN);
    assert(r.GetColor() == Color::RED);

    assert(std::abs(r.GetArea() - 200.0) < 1e-5);
    assert(std::abs(c.GetArea() - 314.15) < 1e-2);
    c.SetRadius(1.0);
    assert(std::abs(c.GetArea() - 3.1415) < 1e-4);
    r.SetSize(5, 7);
    assert(r.GetWidth() == 5);
    assert(r.GetHeight() == 7);
    assert(std::abs(r.GetArea() - 35.0) < 1e-5);

    assert(abs(CalcSumArea(shapes) - 38.1416) < 1e-4);

    for (const Shape* shape : shapes) {
        PrintShapeInfo(*shape);
    }
    cout << "Total area: " << CalcSumArea(shapes) << endl;
}
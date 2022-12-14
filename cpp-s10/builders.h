#pragma once
#include <cassert>
#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>

using namespace std;

class House {
public:
    explicit House(int length, int width, int height)
        : length_(length)
        , width_(width)
        , height_(height) {
    }

    int GetLength() const {
        return length_;
    }

    int GetWidth() const {
        return width_;
    }

    int GetHeight() const {
        return height_;
    }

private:
    int length_;
    int width_;
    int height_;
};

class Resources {
public:
    Resources() = delete;
    explicit Resources(const int brick_count)
        : brick_count_(brick_count) {
    }

    void TakeBricks(const int count) {
        if (count < 0 || brick_count_ - count < 0) {
            throw std::out_of_range("");
        }
        brick_count_ -= count;
    }

    int GetBrickCount() const {
        return brick_count_;
    }

private:
    int brick_count_;
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
public:
    Builder() = delete;
    explicit Builder(Resources& resources) : resources_(resources) {}

    const House& BuildHouse(const HouseSpecification& spec) try {
        int s = spec.length * spec.height * 64 + spec.width * spec.height * 64;
        resources_.TakeBricks(s);
        return *(new House(spec.length, spec.width, spec.height));
    }
    catch (std::out_of_range const&) {
        throw std::runtime_error("runtime error");
    }

private:
    Resources& resources_;
};

void TestBuilders() {
    Resources resources{ 10000 };
    Builder builder1{ resources };
    Builder builder2{ resources };

    House house1 = builder1.BuildHouse(HouseSpecification{ 12, 9, 3 });
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{ 8, 6, 3 });
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{ 4, 3, 2 });
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}
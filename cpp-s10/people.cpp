#include "people.h"

#include <stdexcept>

using namespace std;

const string& Person::GetName() const {
    return name_;
}

int Person::GetAge() const {
    return age_;
}

Gender Person::GetGender() const {
    return gender_;
}

const string& Programmer::GetName() const {
    return Person::GetName();
}

int Programmer::GetAge() const {
    return Person::GetAge();
}

Gender Programmer::GetGender() const {
    return Person::GetGender();
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    language_.insert(language);
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    int count = language_.count(language);
    return (count > 0) ? true : false;
}

const string& Worker::GetName() const {
    return Person::GetName();
}

int Worker::GetAge() const {
    return Person::GetAge();
}

Gender Worker::GetGender() const {
    return Person::GetGender();
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    specs_.insert(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    int count = specs_.count(speciality);
    return (count > 0) ? true : false;
}
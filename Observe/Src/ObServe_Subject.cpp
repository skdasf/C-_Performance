#include "Observe_Subject.hpp"


void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(const int index) {
    observers.erase(observers.begin() + index);
}

void Subject::notify() {
    for (unsigned int i = 0; i < observers.size(); i++) {
        observers.at(i)->update(this);
    }
}


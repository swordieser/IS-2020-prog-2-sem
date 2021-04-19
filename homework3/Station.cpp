#include "Station.h"


Station::Station() = default;

void Station::set_number(unsigned int number) {
    this->number = number;
}

unsigned int Station::get_number() const {
    return number;
}

void Station::set_type(const std::string &type) {
    this->type = type;
}

const std::string &Station::get_type() const {
    return type;
}

void Station::set_streets(std::string s) {
    std::vector<std::string> temp;
    temp.push_back(s.substr(0, s.find(',')));
    s.erase(0, s.find(',')+1);
    if (!s.empty())
        temp.push_back(s.substr(1, s.find('\0')));
    this->streets = temp;
}

const std::vector<std::string> &Station::get_streets() const {
    return streets;
}

void Station::set_routes(std::string s) {
    std::vector<std::string> temp;
    while(!s.empty()) {
        unsigned i;
        for (i = 0; i < s.length(); i++) {
            if (s.at(i) == ',' || s.at(i) == '.') {
                this->routes.push_back(s.substr(0, i));
                s.erase(0, i+1);
                break;
            }
        }
        if (i == s.length()){
            this->routes.push_back(s);
            s.clear();
        }
    }
}

const std::vector<std::string> &Station::get_routes() const {
    return routes;
}

void Station::set_coordinates(std::string s) {
    float a, b;
    a = std::stof(s.substr(0, s.find(',')));
    s.erase(0, s.find(',')+1);
    b = std::stof(s);
    this->coordinates = std::make_pair(a, b);
}

const std::pair<float, float> &Station::get_coordinates() const {
    return coordinates;
}








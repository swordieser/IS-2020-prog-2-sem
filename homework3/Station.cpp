#include "Station.h"
#include "cmath"
#include "cfloat"

const float ONE_DEGREE_MERIDIAN = 111.0;
const float ONE_DEGREE_LATITUDE = 58.0;



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
    s.erase(0, s.find(','));
    if (!s.empty())
        temp.push_back(s.substr(1, s.find('\0')));
    this->streets = temp;
}

const std::vector<std::string> &Station::get_streets() const {
    return streets;
}

void Station::set_routes(std::string s) {
    std::vector<std::string> temp;
    while (!s.empty()) {
        unsigned i;
        for (i = 0; i < s.length(); i++) {
            if (s.at(i) == ',' || s.at(i) == '.') {
                this->routes.push_back(s.substr(0, i));
                s.erase(0, i + 1);
                break;
            }
        }
        if (i == s.length()) {
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
    s.erase(0, s.find(',') + 1);
    b = std::stof(s);
    this->coordinates = std::make_pair(a, b);
}

const std::pair<float, float> &Station::get_coordinates() const {
    return coordinates;
}

float get_distance_between_station(std::pair<float, float> s1, std::pair<float, float> s2) {
    auto [first_longitude, first_latitude] = s1;
    auto [second_longitude, second_latitude] = s2;
    return (float) sqrt(pow((first_longitude - second_longitude) * ONE_DEGREE_MERIDIAN, 2) +
                        pow((first_latitude - second_latitude) * ONE_DEGREE_LATITUDE, 2));
}

float Station::calculate_length_of_route(const std::vector<std::pair<float, float>> &stations_coordinates) {
    float length = 0.0;
    unsigned next_station = 0;
    std::vector<bool> visited(stations_coordinates.size(), false);
    while (next_station < stations_coordinates.size()) {
        unsigned current = next_station;
        visited.at(current) = true;
        float minimal_distance = FLT_MAX;
        next_station = stations_coordinates.size();
        for (unsigned i = 0; i < stations_coordinates.size(); i++) {
            if (visited.at(i)) {
                continue;
            } else {
                float temp_distance = get_distance_between_station(stations_coordinates.at(current), stations_coordinates.at(i));
                if (temp_distance < minimal_distance) {
                    minimal_distance = temp_distance;
                    next_station = i;
                }
            }
        }
        if (next_station < stations_coordinates.size()){
            length+=minimal_distance;
        }
    }
    return length;
}








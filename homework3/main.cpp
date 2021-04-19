#include "../pugixml-1.11/src/pugixml.hpp"
#include "iostream"
#include "Station.h"
#include <clocale>
#include <fstream>
#include "unordered_map"
#include "unordered_set"

int main() {
    setlocale(LC_CTYPE, "rus");
    pugi::xml_document doc;
    doc.load_file("../homework3/transport.xml");
    std::vector<Station> stations;

    std::ofstream fout("../homework3/output.txt");
    for (auto s : doc.child("dataset").children("transport_station")) {
        Station station;

        station.set_number(std::stoi(s.child_value("number")));
        station.set_type(s.child_value("type_of_vehicle"));
        station.set_streets(s.child_value("location"));
        station.set_routes(s.child_value("routes"));
        station.set_coordinates(s.child_value("coordinates"));

        stations.push_back(station);
    }

    ///Task 1
    std::unordered_set<std::string> types_of_transport;
    for (const Station &s : stations) {
        types_of_transport.insert(s.get_type());
    }
    std::unordered_map<std::string, std::pair<std::string, unsigned>> max_station_at_route_by_type;
    for (auto &type : types_of_transport) {
        std::unordered_map<std::string, unsigned> stations_at_route;
        max_station_at_route_by_type.at(type) = std::make_pair("", 0);
        for (auto &station : stations) {
            if (station.get_type() != type) {
                continue;
            } else {
                for (auto &route : station.get_routes()) {
                    if (stations_at_route.find(route) != stations_at_route.end()) {
                        stations_at_route.at(route) += 1;
                    } else {
                        stations_at_route.at(route) = 1;
                    }
                }
            }
        }

        for (auto[route, number_of_station] : stations_at_route) {
            if (number_of_station > max_station_at_route_by_type.at(type).second) {
                max_station_at_route_by_type.at(type).first = route;
                max_station_at_route_by_type.at(type).second = number_of_station;
            }
        }
    }

    ///Task 2




    ///Task 3
    std::unordered_map<std::string, unsigned> stations_at_street;
    for (auto &station : stations) {
        for (auto &street : station.get_streets()) {
            if (stations_at_street.find(street) != stations_at_street.end()) {
                stations_at_street.at(street) += 1;
            } else {
                stations_at_street.at(street) = 1;
            }
        }
    }
    std::pair<std::string, unsigned> maximal;
    for (auto &[street, number_of_station] : stations_at_street){
        if (number_of_station > maximal.second){
            maximal.first = street;
            maximal.second = number_of_station;
        }
    }
}
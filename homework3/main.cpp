#include "../pugixml-1.11/src/pugixml.hpp"
#include "iostream"
#include "Station.h"
#include <clocale>
#include <fstream>
#include "unordered_map"
#include "unordered_set"
#include "windows.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pugi::xml_document doc;
    doc.load_file("../homework3/transport.xml");
    std::vector<Station> stations;


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
        max_station_at_route_by_type[type] = std::make_pair("", 0);
        for (auto &station : stations) {
            if (station.get_type() != type) {
                continue;
            } else {
                for (auto &route : station.get_routes()) {
                    if (stations_at_route.find(route) != stations_at_route.end()) {
                        stations_at_route[route] += 1;
                    } else {
                        stations_at_route[route] = 1;
                    }
                }
            }
        }
        //todo first decond
        for (auto[route, number_of_station] : stations_at_route) {
            if (number_of_station > max_station_at_route_by_type.at(type).second) {
                max_station_at_route_by_type.at(type).first = route;
                max_station_at_route_by_type.at(type).second = number_of_station;
            }
        }
    }

    ///Task 2

    std::unordered_map<std::string, std::pair<std::string, float>> max_length_of_route_by_type;
    for (auto &type : types_of_transport) {
        max_length_of_route_by_type[type] = std::make_pair("", 0.0);
        std::unordered_map<std::string, std::vector<std::pair<float, float>>> station_coordinates_at_route;
        for (auto &station : stations) {
            if (station.get_type() != type) {
                continue;
            } else {
                for (auto &route : station.get_routes()) {
                    if (station_coordinates_at_route.find(route) != station_coordinates_at_route.end()) {
                        station_coordinates_at_route.at(route).push_back(station.get_coordinates());
                    } else {
                        station_coordinates_at_route[route] = std::vector<std::pair<float, float>>(
                                {station.get_coordinates()});
                    }
                }
            }
        }
        for (auto[route, station_coordinates] : station_coordinates_at_route) {
            float length = Station::calculate_length_of_route(station_coordinates);

            if (length > max_length_of_route_by_type.at(type).second) {
                max_length_of_route_by_type.at(type).first = route;
                max_length_of_route_by_type.at(type).second = length;
            }
        }
    }

    ///Task 3
    std::unordered_map<std::string, unsigned> stations_at_street;
    for (auto &station : stations) {
        for (auto &street : station.get_streets()) {
            if (!street.empty()) {
                if (stations_at_street.find(street) != stations_at_street.end()) {
                    stations_at_street[street] += 1;
                } else {
                    stations_at_street[street] = 1;
                }
            }
        }
    }
    std::pair<std::string, unsigned> maximal;
    for (auto &[street, number_of_station] : stations_at_street) {
        if (number_of_station > maximal.second) {
            maximal.first = street;
            maximal.second = number_of_station;
        }
    }

    ///Output
    std::ofstream fout("../homework3/output.txt");
    fout << "Задание #1" << std::endl;
    for (auto &type : types_of_transport) {
        fout << type << " : " << max_station_at_route_by_type.at(type).first << " — "
             << max_station_at_route_by_type.at(type).second << " остановок" << std::endl;
    }
    fout << std::endl;

    fout << "Задание #2" << std::endl;
    for (auto &type : types_of_transport){
        fout << type << " : " << max_length_of_route_by_type.at(type).first << " — "
             << max_length_of_route_by_type.at(type).second  << std::endl;
    }
    fout << std::endl;

    fout << "Задание #3" << std::endl;
    fout << maximal.first << " — " << maximal.second;
}


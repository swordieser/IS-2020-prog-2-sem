#ifndef IS_2020_PROG_2_SEM_STATION_H
#define IS_2020_PROG_2_SEM_STATION_H

#include "string"
#include "vector"


class Station {
private:
    unsigned number;
    std::string type;
    std::vector<std::string> streets;
    std::vector<std::string> routes;
    std::pair<float, float> coordinates;

public:
    Station();

    void set_number(unsigned int number);

    unsigned int get_number() const;

    void set_type(const std::string &type);

    const std::string &get_type() const;

    void set_streets(std::string s);

    const std::vector<std::string> &get_streets() const;

    void set_routes(std::string s);

    const std::vector<std::string> &get_routes() const;

    void set_coordinates(std::string s);

    const std::pair<float, float> &get_coordinates() const;

    static float calculate_length_of_route(const std::vector<std::pair<float, float>>& stations_coordinates);
};


#endif //IS_2020_PROG_2_SEM_STATION_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <filesystem>
#include "cpp_or_cs.cpp"

int main(int argc, char** argv) {
    // Entry point for set_of_points
    // TODO: implement functionality
    std::cout << "set_of_points: main() started\n";
    
    string filename = std::filesystem::current_path().string() + "/test_data/test3.txt";
    Point_Line pl(0, filename);
    pl.print_points();
    pl.save_points_to_file("output_points.txt");
    PointSet f_pl = pl.filter_by_min_distance(25);
    for(auto &p : f_pl.points) {
        std::cout << "Filtered Point x: " << p.x << std::endl;
    }
    std::cout << pl.has_regular_spacing(25, 1e-6, 3);

    return 0;
}
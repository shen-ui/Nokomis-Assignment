#pragma once
#include <string>
#include <vector>

struct Point {
    double x;
};

struct PointSet {
    int id;
    int point_size;
    std::vector<Point> points; 
};

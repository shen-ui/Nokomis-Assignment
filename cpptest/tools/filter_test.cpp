#include <iostream>
#include "../src/cpp_or_cs.cpp"

int main() {
    const std::string filename = "test_data/test1.txt";
    Point_Line pl(filename);

    std::cout << "Original points (count=" << pl.point_set.points.size() << "):\n";
    for (const auto &p : pl.point_set.points) {
        std::cout << "seq=" << p.seq_id << " x=" << p.x << " marked=" << p.marked << "\n";
    }

    double min_dist = 2.0;
    auto filtered = pl.filter_by_min_distance(min_dist);
    std::cout << "\nFiltered points with min_dist=" << min_dist << " (count=" << filtered.points.size() << "):\n";
    for (const auto &p : filtered.points) {
        std::cout << "seq=" << p.seq_id << " x=" << p.x << " marked=" << p.marked << "\n";
    }
    std::cout << "\nChecking regular spacing...\n";
    double spacing = 2.0;
    bool has = pl.has_regular_spacing(spacing, 1e-6, 3);
    std::cout << "Spacing " << spacing << (has ? " exists" : " does not exist") << " among 3+ points\n";

    return 0;
}

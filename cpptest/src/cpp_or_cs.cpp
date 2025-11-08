#include <utility>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "../resources/points.h"

using namespace std;

/** Assumtions:
* lines are not uniformally spaced.
* e.g., [1.0, 1.1, 2.1, 3.0, 4.1, 8.1)
*
 *  i.g.
 * 
 * 1.  0_._|_._1_._|_._2_._|_._3_._|_._4_._|_._5_._|_._6_._|_._7_._|_._8_._|_._9_._|
 *     x   x  xx    x       x xx         x         x       x       x       x
 * 2.  0_._|_._1_._|_._2_._|_._3_._|_._4_._|_._5_._|_._6_._|_._7_._|_._8_._|_._9_._|
 *        x xx       x   xx    x   x   x   x       x
 * 3.  0_._|_._1_._|_._2_._|_._3_._|_._4_._|_._5_._|_._6_._|_._7_._|_._8_._|_._9_._|
 *                                x    x xxxx x                       x
 * 
 *  Solution: use inplace sliding frame algorithm to identify points and reference point position with ruler line.
 */

#include <cctype>
#include <cmath>

class Point_Line {
    private:
        // ruler min and max NOT point x min and max
        // max and min marks are easily extracted from point_set first and last elements
        int line_max = 0;
        int line_min = 0;
        std::string label;

    public:
        PointSet point_set;

        // Default constructor
        Point_Line() {
            point_set.id = 0;
        }
        // Construct and immediately load a file
        Point_Line(int id, const std::string& filename) : Point_Line() {
            load_file(filename);

        }
        // Construct and immediately load a file
        Point_Line(const std::string& filename) : Point_Line() {
            load_file(filename);
        }
        // Getters and setters for private members
        int get_line_max() const {
            return line_max;
        }
        void set_line_max(int v) {
            line_max = v;
        }

        int get_line_min() const {
            return line_min;
        }
        void set_line_min(int v) {
            line_min = v;
        }

        const std::string& get_label() const {
            return label;
        }
        void set_label(const std::string& v) {
            label = v;
        }
        void print_points() const {
            cout << "label: " << get_label() << endl;
            for (const auto &p : point_set.points) {
                cout << "Point x: " << p.x << endl;
            }
            cout << "min x: " << get_line_min() << endl;
            cout << "max x: " << get_line_max() << endl;
        }
        // Add a single point ( x coordinate, sequence id)
        void add_point(double p) {
            Point point {p};
            point_set.points.push_back(point);
        }
        // Calculate the point position in point_line.
        void calc_points(int start_idx, int end_idx, int start_val, int end_val, const string& point_line) {
            double dist_step = (static_cast<double>(end_idx) - static_cast<double>(start_idx)) / (end_val - start_val);
            int start_pos = start_idx;
            int multiplier = 0;
            
            for (int i = start_val; i <= end_val; ++i) {
                if (point_line[i] == 'x') {
                    
                    double pos = start_pos + (i - start_val) * dist_step;
                    cout << pos << endl;

                    add_point(pos);
                    multiplier++;
                }
            }
        }
        void process_file(string num_line, string point_line) {
            // Find first and last numeric character positions on the ruler and their values.
            int idx = -1;
            int min = -1;
            int max = -1;
            int prev_i = 0;
            string num_str;

            for (size_t i = 0; i < num_line.size(); ++i) {
                if (std::isdigit(static_cast<unsigned char>(num_line[i]))) {
                    // Parse a (possibly multi-digit) number starting at i.
                    size_t j = i;
                    
                    // Collect digits for ruler line reference.
                    while (j < num_line.size() && std::isdigit(static_cast<unsigned char>(num_line[j]))) {
                        num_str.push_back(num_line[j]);
                        ++j;
                    }
                    double val = std::stod(num_str);
                    cout << "Parsed number: " << val << " at position " << i << endl;
                    // If first idx does not exist yet, set it.
                    if (idx == -1 ) {
                        idx = val;
                        min = idx;
                    } else {
                        cout << "Calculating points between " << idx << " and " << val << endl;
                        calc_points(idx, val, prev_i, static_cast<int>(i), point_line);
                        idx = val;
                        prev_i = j - 1;
                        max = idx; // Update max to latest found because we are unsure of last digit.
                    }
                    // Advance i to j so we don't re-read same digits.
                    i = j - 1;
                }
                num_str.clear();
                // Performing interval calculation on last points are meaningless without a reference of ruler end
                // especially if ruler line is non-uniformly spaced.
                // i.g. _._244431_._|_.
                //                    x
                // No changes are needed to implement if capability is added to hardware.
            }
            set_line_min(min);
            set_line_max(max);
            
            // handle if no reference numeric markers found
            if (idx = -1) {
                cout << "Could not find numeric markers on ruler line" << endl;
                return;
            }
        }
        void save_points_to_file(const std::string& filename) const {
            ofstream file(filename);
            if (!file) {
                cout << "Failed to open file for writing!" << endl;
                return;
            }
            for (const auto &p : point_set.points) {
                file << p.x << endl;
            }
            file.close();
        }
        /**Load a two-line file where the first line is a ruler (numbers at certain
         * character columns) and the second line contains 'x' characters marking
         * point positions. Each 'x' character becomes a Point. The x-coordinate is
         * interpolated between the first and last numeric markers on the ruler.
         */
        void load_file(const std::string& filename) {
            cout << "Loading file: " << filename << endl;
            ifstream file(filename);
            if (!file) {
                cout << "Failed to open file!" << endl;
                return;
            }

            string num_line, point_line;
            if (!std::getline(file, num_line)) {
                cout << "DATA MALFORMED: File empty or missing ruler line" << endl;
                return;
            }
            if (!std::getline(file, point_line)) {
                cout << "DATA MALFORMED: File missing point line" << endl;
                return;
            }
            process_file(num_line, point_line);
            // Remember filename as label.
            set_label(filename);

            file.close();

        }

        // Return a new PointSet containing only points separated by at least
        // min_dist. Points are compared on their x coordinate. The first
        // (smallest-x) point is always kept; subsequent points are kept only
        // if they are at least min_dist away from the last kept point.
        // The returned PointSet does not replace the class level point_set.
        PointSet filter_by_min_distance(double min_dist) const {
            PointSet out = point_set;
            out.points.clear();

            // Create a local copy and sort by x
            std::vector<Point> pts = point_set.points;
            std::sort(pts.begin(), pts.end(), [](const Point &a, const Point &b){
                return a.x < b.x;
            });

            for (const auto &p : pts) {
                if (out.points.empty()) {
                    Point np = p; 
                    out.points.push_back(np);
                    continue;
                }

                double last_x = out.points.back().x;
                if (std::fabs(p.x - last_x) >= min_dist) {
                    Point np = p;
                    out.points.push_back(np);
                }
            }
            return out;
        }

        // In-place filter that replaces the current point_set with the
        // filtered set (keeps label and id metadata from the original).
        void filter_inplace(double min_dist) {
            PointSet filtered = filter_by_min_distance(min_dist);
            point_set.points.swap(filtered.points);
        }

        /**
         * Detect whether there exists 3 or more points in the set that form
         * an arithmetic progression with the given spacing (within tol).
         * Returns true if such a sequence is found.
         */
        bool has_regular_spacing(double spacing, double tol, int required_count = 3) const {
            if (spacing <= 0.0) return false;
            const auto &pts = point_set.points;
            if (static_cast<int>(pts.size()) < required_count) return false;

            // extract x values and sort
            std::vector<double> xs;
            xs.reserve(pts.size());
            for (const auto &p : pts) xs.push_back(p.x);
            std::sort(xs.begin(), xs.end());

            const int n = static_cast<int>(xs.size());

            for (int i = 0; i < n; ++i) {
                int count = 1;
                double next_expected = xs[i] + spacing;
                // attempt to find successive points matching the spacing
                while (true) {
                    // lower_bound for next_expected - tol
                    auto it = std::lower_bound(xs.begin() + i + 1, xs.end(), next_expected - tol);
                    if (it == xs.end()) break;
                    double found = *it;
                    if (std::fabs(found - next_expected) <= tol) {
                        ++count;
                        if (count >= required_count) return true;
                        next_expected += spacing;
                    } else {
                        // not found; break the sequence starting at i
                        break;
                    }
                }
            }

            return false;
        }
};

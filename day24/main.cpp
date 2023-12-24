#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct Hailstone {
    long long x, y, z;
    long long vx, vy, vz;
};

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<Hailstone> hailstones;

    std::string line;
    while(std::getline(in, line)) {
        for(size_t i = 0; i < line.length(); i++) {
            if(line[i] == ',' || line[i] == '@') line[i] = ' ';
        }

        std::stringstream ss(line);
        long long x, y, z, vx, vy, vz;
        ss >> x >> y >> z >> vx >> vy >> vz;
        hailstones.push_back(Hailstone{x, y, z, vx, vy, vz});
    }

    long long min = 200000000000000;
    long long max = 400000000000000;
    long long count = 0;

    for(size_t i = 0; i < hailstones.size(); i++) {
        for(size_t j = i + 1; j < hailstones.size(); j++) {
            auto h1 = hailstones[i];
            auto h2 = hailstones[j];

            double m1 = (double)h1.vy / (double)h1.vx;
            double m2 = (double)h2.vy / (double)h2.vx;

            if(m1 == m2) continue;

            double b1 = (double)h1.y - m1 * (double)h1.x;
            double b2 = (double)h2.y - m2 * (double)h2.x;

            double int_x = (b2 - b1) / (m1 - m2);
            double int_y = int_x * m1 + b1;

            if(h1.vx * (int_x - h1.x) <= 0 && h1.vy * (int_y - h1.y) <= 0) {
                continue;
            }

            if(h2.vx * (int_x - h2.x) <= 0 && h2.vy * (int_y - h2.y) <= 0) {
                continue;
            }

            if(int_x >= min && int_x <= max && int_y >= min && int_y <= max) {
                count++;
            }
        }
    }

    out << count;

    out.close();
    in.close();
}

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::vector<Hailstone> hailstones;

    std::string line;
    while(std::getline(in, line)) {
        for(size_t i = 0; i < line.length(); i++) {
            if(line[i] == ',' || line[i] == '@') line[i] = ' ';
        }

        std::stringstream ss(line);
        long long x, y, z, vx, vy, vz;
        ss >> x >> y >> z >> vx >> vy >> vz;
        hailstones.push_back(Hailstone{x, y, z, vx, vy, vz});
    }

    out << "r = Solve[{\n";
    size_t limit = 4;
    size_t i = 0;

    for(const auto& h: hailstones) {
        out << "rx - (" << h.x << ") + t" << i << " * (rvx - (" << h.vx << ")) == 0" << ",\n";
        out << "ry - (" << h.y << ") + t" << i << " * (rvy - (" << h.vy << ")) == 0" << ",\n";
        out << "rz - (" << h.z << ") + t" << i << " * (rvz - (" << h.vz << ")) == 0";
        if (i < limit - 1) {
            out << ",\n";
        } else {
            out << '\n';
            break;
        }
        i++;
    }
    out << "}, {rx, ry, rz, rvx, rvy, rvz, ";

    for(size_t t = 0; t < limit; t++){
        out << "t" << t;
        if(t == limit - 1){
            out << "}];\n";
        } else {
            out << ", ";
        }
    }
    out << "(rx + ry + rz) //. r[[1]]\n";

    // https://www.wolframcloud.com/obj/19e34f06-7f4b-46d7-94e4-c22296d820aa

    out.close();
    in.close();
}

int main() {
    solve_p1();
    solve_p2();
    return 0;
}

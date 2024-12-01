#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

int horizontal(std::vector<std::string>& pattern, int smudges) {
	for (size_t i = 0; i < pattern.size() - 1; i++) {
	    int dist = 0;
	    int j = i;
		size_t k = i + 1;
	    while (dist <= smudges && j >= 0 && k < pattern.size()) {
	    	for (size_t l = 0; l < pattern[0].size(); l++) {
	    		dist += (pattern[j][l] != pattern[k][l]);
	    	}
	    	j--;
	    	k++;
	    }
	    if (dist == smudges) {
	    	return i + 1;
	    }
	}
  
	return 0;
}
 
int vertical(std::vector<std::string>& pattern, int smudges) {
	std::vector<std::string> new_pattern;
	for (size_t j = 0; j < pattern[0].length(); j++) {
		std::string temp;
		for (size_t i = 0; i < pattern.size(); i++) {
		  temp += pattern[i][j];
		}
		new_pattern.push_back(temp);
	}

	return horizontal(new_pattern, smudges);
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    int sum = 0;

    std::vector<std::string> pattern;
	std::vector<std::vector<std::string>> patterns;

	while (std::getline(in, line)) {
		if (line.compare("")) {
			pattern.push_back(line);
		}
		else {
			patterns.push_back(pattern);
			pattern.clear();
		}
	}
	patterns.push_back(pattern);

    for (size_t i = 0; i < patterns.size(); i++) {
		int hor = horizontal(patterns[i], 0);
		int vert = vertical(patterns[i], 0);
		sum += (hor * 100) + vert;
	}

    out << sum;

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

    std::string line;
    int sum = 0;

    std::vector<std::string> pattern;
	std::vector<std::vector<std::string>> patterns;

	while (std::getline(in, line)) {
		if (line.compare("")) {
			pattern.push_back(line);
		}
		else {
			patterns.push_back(pattern);
			pattern.clear();
		}
	}
	patterns.push_back(pattern);

    for (size_t i = 0; i < patterns.size(); i++) {
		int hor = horizontal(patterns[i], 1);
		int vert = vertical(patterns[i], 1);
		sum += (hor * 100) + vert;
	}

    out << sum;

    out.close();
    in.close();
}

int main() {
    solve_p2();
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>

enum hand {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

std::unordered_map<char, int> alphabet_p1 = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, 
    {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}
};

bool find(const std::vector<int>& v, int x) {
    for(int y: v) {
        if(y == x) return true;
    }
    return false;
}

hand get_hand_type_p1(std::string cards) {
    std::unordered_map<char, int> counts;
    std::vector<int> occurrence;
    for(char c: cards) {
        if(!counts[c]) {
            counts[c] = 0;
        }
        counts[c]++;
    }

    for(const auto& p: counts)
        occurrence.push_back(p.second);

    if (find(occurrence, 5)) {
        return FIVE_OF_A_KIND;
    } else if (find(occurrence, 4)) {
        return FOUR_OF_A_KIND;
    } else if (find(occurrence, 3) && find(occurrence, 2)) {
        return FULL_HOUSE;
    } else if (find(occurrence, 3)) {
        return THREE_OF_A_KIND;
    } else if(std::count(occurrence.begin(), occurrence.end(), 2) == 2) {
        return TWO_PAIR;
    } else if(find(occurrence, 2)) {
        return ONE_PAIR;
    } else {
        return HIGH_CARD;
    }
}

bool compare_hands_p1(std::string lhs, std::string rhs) {
    hand lhand = get_hand_type_p1(lhs);
    hand rhand = get_hand_type_p1(rhs);
    if(lhand != rhand) return lhand < rhand;
    else {
        for(size_t i = 0; i < lhs.length(); i++) {
            if(lhs[i] != rhs[i])
                return alphabet_p1[lhs[i]] < alphabet_p1[rhs[i]];
        }
        return false;
    }
}

void solve_p1() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p1.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::pair<std::string, int>> hands;
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string hand;
        int bid;
        ss >> hand >> bid;
        hands.push_back({hand, bid});
    }

    std::sort(std::begin(hands), std::end(hands),
        [] (const auto& lhs, const auto& rhs) {
            return compare_hands_p1(lhs.first, rhs.first);
        }
    );

    int sum = 0;
    size_t index = 1;
    for(const auto& h: hands) {
        sum += index * h.second;
        index++;
    }

    out << sum;

    out.close();
    in.close();
}

std::unordered_map<char, int> alphabet_p2 = {
    {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5},
    {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12}
};

std::string faces = "23456789TQKA";

hand get_hand_type_p2(std::string cards) {
    hand max_hand = HIGH_CARD;

    for(char c: faces) {
        hand candidate_hand; 
        std::string candidate = cards;
        std::replace(candidate.begin(), candidate.end(), 'J', c);

        std::unordered_map<char, int> counts;
        std::vector<int> occurrence;
        for(char c: candidate) {
            if(!counts[c]) {
                counts[c] = 0;
            }
            counts[c]++;
        }

        for(const auto& p: counts)
            occurrence.push_back(p.second);

        if (find(occurrence, 5)) {
            candidate_hand = FIVE_OF_A_KIND;
        } else if (find(occurrence, 4)) {
            candidate_hand = FOUR_OF_A_KIND;
        } else if (find(occurrence, 3) && find(occurrence, 2)) {
            candidate_hand = FULL_HOUSE;
        } else if (find(occurrence, 3)) {
            candidate_hand = THREE_OF_A_KIND;
        } else if(std::count(occurrence.begin(), occurrence.end(), 2) == 2) {
            candidate_hand = TWO_PAIR;
        } else if(find(occurrence, 2)) {
            candidate_hand = ONE_PAIR;
        } else {
            candidate_hand = HIGH_CARD;
        }

        if(candidate_hand > max_hand)
            max_hand = candidate_hand;
    }

    return max_hand;
}

bool compare_hands_p2(std::string lhs, std::string rhs) {
    hand lhand = get_hand_type_p2(lhs);
    hand rhand = get_hand_type_p2(rhs);
    if(lhand != rhand) return lhand < rhand;
    else {
        for(size_t i = 0; i < lhs.length(); i++) {
            if(lhs[i] != rhs[i])
                return alphabet_p2[lhs[i]] < alphabet_p2[rhs[i]];
        }
        return false;
    }
}

void solve_p2() {
    std::ifstream in("input.txt");
    std::ofstream out("output_p2.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::vector<std::pair<std::string, int>> hands;
    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string hand;
        int bid;
        ss >> hand >> bid;
        hands.push_back({hand, bid});
    }

    std::sort(std::begin(hands), std::end(hands),
        [] (const auto& lhs, const auto& rhs) {
            return compare_hands_p2(lhs.first, rhs.first);
        }
    );

    int sum = 0;
    size_t index = 1;
    for(const auto& h: hands) {
        sum += index * h.second;
        index++;
    }

    out << sum;

    out.close();
    in.close();
}


int main() {
    solve_p2();
    return 0;
}

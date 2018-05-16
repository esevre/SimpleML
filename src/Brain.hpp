//
// Created by Erik Sevre on 5/15/18.
//

#ifndef MLDOTS_BRAIN_HPP
#define MLDOTS_BRAIN_HPP

#include <cinder/gl/gl.h>
#include <vector>
#include <algorithm>
#include <random>

class Brain {
public:
    explicit Brain(size_t size) : directions(size) {
        randomize();
    }

    // copy and move constructor
    Brain(const Brain &brain) : directions(brain.directions) {}
    Brain(Brain &&brain) : directions(std::move(brain.directions)) {}

    // copy and move assignment
    Brain &operator=(const Brain &brain);
    Brain &operator=(Brain &&brain) {
        directions = std::move(brain.directions);
        return *this;
    }

    auto begin() { return directions.begin(); }
    auto end() { return directions.end(); }
    auto cbegin() const { return directions.cbegin(); }
    auto cend() const { return directions.cend(); }

    auto &operator[](size_t i) { return directions[i]; }
    auto operator[](size_t i) const { return directions[i]; }

    size_t size() const { return directions.size(); }

    ci::vec2 getNextDirection() {
        ci::vec2 val = directions[step];
        ++step;
        return val;
    }

    bool is_finished() const { return step > directions.size(); }

    ci::vec2 getGoal() const { return goal; }
protected:
    void randomize() {
        for (auto &direction : directions) {
            double random_angle = gen_random_double(0.0, 2*pi);   // Random number in 2*pi
            direction = directionFromAngle(random_angle);
        }
    }
    double gen_random_double(double min, double max) {
        std::random_device rd;
        std::seed_seq seed {rd(), rd()};
        std::mt19937 mt(seed);
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(mt);
    }
    ci::vec2 directionFromAngle(double angle) const {
        double x = std::sin(angle);
        double y = std::cos(angle);
        return ci::vec2(x, y);
    }


private:
    std::vector<ci::vec2> directions;
    size_t step = 0; // keep track of the current step number
    double pi = std::acos(-1);
    ci::vec2 goal = ci::vec2(50, 10);
};


#endif //MLDOTS_BRAIN_HPP
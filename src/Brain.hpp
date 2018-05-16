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
    Brain &operator=(Brain &&brain) noexcept {
        directions = std::move(brain.directions);
        step = 0;
        return *this;
    }

//    auto begin() { return directions.begin(); }
//    auto end()   { return directions.end(); }
//    auto cbegin() const { return directions.cbegin(); }
//    auto cend()   const { return directions.cend(); }
//
//    auto &operator[](size_t i)      { return directions[i]; }
//    auto operator[](size_t i) const { return directions[i]; }

    size_t size() const { return directions.size(); }

    ci::vec2 getNextDirection() {
        ci::vec2 val = directions[step];
        ++step;
        return val;
    }

    bool at_end() const {
        return step > directions.size();
    }

    ci::vec2 getGoal() const { return goal; }

    size_t numSteps() const { return step; }

    void mutate() {
        float mutationRate = 0.3f; // chance that any vector in directions gets changed
        for (int i = 0; i < directions.size(); ++i) {
            float rand_num = gen_random_float(0.0, 1.0);
            if (rand_num < mutationRate) {
                float theta = gen_random_float(0.0, 2*pi);
                directions[i] = directionFromAngle(theta);
            }

        }
    }

    float gen_random_float(float min, float max) const {
        // note: static makes this method MUCH faster
        static std::random_device rd;
        static std::seed_seq seed {rd(), rd()};
        static std::mt19937 mt(seed);
        static std::uniform_real_distribution<float> distribution(min, max);
        return distribution(mt);
    }

    void reset() {
        step = 0;
    }

protected:
    void randomize() {
        for (auto &direction : directions) {
            float random_angle = gen_random_float(0.0, 2 * pi);   // Random number in 2*pi
            direction = directionFromAngle(random_angle);
        }
    }


    ci::vec2 directionFromAngle(float angle) const {
        float x = std::sin(angle);
        float y = std::cos(angle);
        return ci::vec2(x, y);
    }


private:
    std::vector<ci::vec2> directions;
    size_t step = 0;  // keep track of the current step number
    float pi = std::acos(-1);
    ci::vec2 goal = ci::vec2(50, 10);
};


#endif //MLDOTS_BRAIN_HPP

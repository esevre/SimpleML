//
// Created by Erik Sevre on 5/15/18.
//

#ifndef MLDOTS_BRAIN_HPP
#define MLDOTS_BRAIN_HPP

#include <vector>
#include <algorithm>
#include <random>

#include "esml.hpp"

namespace ESML {


    class Brain {
    public:
        explicit Brain(size_t size) : directions(size) {
            randomize();
        }

        // copy and move constructor
        Brain(const Brain &brain)
                : directions(brain.directions),
                  step(brain.step),
                  goal(brain.goal)
        {}
        Brain(Brain &&brain) noexcept
                : directions(std::move(brain.directions)),
                  step(brain.step),
                  goal(brain.goal)
        {}

        // copy and move assignment
        Brain &operator=(const Brain &brain);
        Brain &operator=(Brain &&brain) noexcept {
            directions = std::move(brain.directions);
            step = 0;
            return *this;
        }

        ItType begin() { return directions.begin(); }
        ItType end()   { return directions.end(); }
        ConstItType cbegin() const { return directions.cbegin(); }
        ConstItType cend()   const { return directions.cend(); }

        PointType &operator[](size_t i)      { return directions[i]; }
        PointType operator[](size_t i) const { return directions[i]; }

        SizeType size() const { return directions.size(); }

        PointType getNextDirection() {
            PointType val = directions[step];
            ++step;
            return val;
        }

        bool at_end() const {
            return step >= directions.size();
        }

        PointType getGoal() const { return goal; }

        SizeType numSteps() const { return step; }

        void mutate(NumberType mutationRate = 0.01) {
            for (auto &direction : directions) {
                NumberType rand_num = gen_random_number(0.0, 1.0);
                if (rand_num < mutationRate) {
                    NumberType theta = gen_random_number(0.0, 2 * pi);
                    direction = directionFromAngle(theta);
                }
            }
        }

        NumberType gen_random_number(NumberType min, NumberType max)
        {
            // note: static makes this method MUCH faster
            static std::random_device rd;
            static std::seed_seq seed { rd(), rd() };
            static std::mt19937 mt(seed);
            static std::uniform_real_distribution<NumberType> distribution(min, max);
            return distribution(mt);
        }

        void reset() {
            step = 0;
        }

    protected:
        void randomize() {
            for (auto &direction : directions) {
                NumberType random_angle = gen_random_number(0.0, 2 * pi);   // Random number in 2*pi
                direction = directionFromAngle(random_angle);
            }
        }


        PointType directionFromAngle(NumberType angle) const {
            NumberType x = static_cast<NumberType>(std::sin(angle));
            NumberType y = static_cast<NumberType>(std::cos(angle));
            return PointType(x, y);
        }


    private:
        VectorType directions;
        SizeType step = 0;    // keep track of the current step number
        NumberType pi = static_cast<NumberType >(std::acos(-1));
        PointType goal = PointType(50, 10);
    };


}






#endif //MLDOTS_BRAIN_HPP

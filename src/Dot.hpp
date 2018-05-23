//
// Created by Erik Sevre on 5/15/18.
//

#ifndef MLDOTS_DOT_HPP
#define MLDOTS_DOT_HPP

#include <cmath>

#include "esml.hpp"
#include "Brain.hpp"


namespace ESML {

    class Dot {
    public:
        Dot() : brain( 1000 ) {}
        explicit Dot(AppPointer app) : brain(1000) { }
        Dot(NumberType x, NumberType y) : brain(1000), pos(start_pos) { }
        Dot(const Dot &dot) : brain(dot.brain), pos(start_pos) { }
        Dot(Dot &&dot) noexcept
                : brain(std::move(dot.brain)), pos(start_pos) { }

        Dot &operator=(const Dot &dot) {
            brain = dot.brain;
            pos = start_pos;
            vel = PointType(0, 0);
            acc = PointType(0, 0);

            return *this;
        }

        void draw(NumberType scale) const;
        void draw(NumberType scale, ColorType color) const;

        void move();
        void update();

        void calculateFitness(const PointType &goal){
            if (reachedGoal) {
                // if the dot reached the goal then the fitness is based on the amount of steps it took to get there
                fitness = 1.0f/16.0f + 10000.0f / (NumberType)(brain.numSteps()*brain.numSteps());
            } else {
                // if the dot didn't reach the goal, then the fitness is basedo n how close it is to the goal
                NumberType distanceToGoal = distance(pos, goal);
                fitness = 1.0f / (distanceToGoal*distanceToGoal);
                //fitness = 1.0 / ((pos.x - goal.x)*(pos.x - goal.x)+std::pow(pos.y - goal.y, 3));
            }
        }

        static NumberType distance(const PointType &a, const PointType &b) {
            NumberType dx = a.x - b.x;
            NumberType dy = a.y - b.y;
            return std::sqrt(dx*dx + dy*dy);
        }

        void reset() {
            brain.reset();
            pos = start_pos;
            vel = PointType(0,0);
            acc = PointType(0,0);
            dead = false;
            reachedGoal = false;
        }

    private:

        static constexpr NumberType length(const PointType &vec) {
            return sqrt(vec.x*vec.x + vec.y*vec.y);
        }

        void limit_length(PointType &pt, NumberType max_length) {
            NumberType l = length(pt);
            if (l > max_length){
                auto x = pt.x / l;
                auto y = pt.y / l;
                pt.x = x * max_length;
                pt.y = y * max_length;
            }
        }



    public:
        const PointType start_pos = PointType(50, 90);
        PointType pos;
        PointType vel = PointType(0, 0);
        PointType acc = PointType(0, 0);
        Brain brain;
        NumberType radius = 4;

        bool dead = false;
        bool reachedGoal = false;
        bool isBest = false;

        NumberType fitness = 0.0;

        NumberType width = 100.0f;
        NumberType height = 100.0f;
    };


}

#endif //MLDOTS_DOT_HPP
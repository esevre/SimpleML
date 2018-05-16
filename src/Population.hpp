//
// Created by Erik Sevre on 5/16/18.
//

#ifndef MLDOTS_POPULATION_HPP
#define MLDOTS_POPULATION_HPP

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "Dot.hpp"

class Population {

public:
    explicit Population(size_t size) : dots(size) {}

    void draw() const {
        for (auto &dot : dots) {
            dot.draw(scale_factor);
        }
    }
    void update(const float &scale = 1.0) {
        scale_factor = scale;
        for (auto &dot : dots) {
            if (dot.brain.numSteps() > minStep) {
                // if the dot has already taken more steps than the best dot to reach the goal
                dot.dead = true;
            } else {
                dot.update();
            }
        }
    }

    void calculateFitness(const ci::vec2 &goal) {
        for(auto &dot : dots) {
            dot.calculateFitness(goal);
        }
    }

    bool allDotsDead() const {
        for(auto &dot : dots) {
            if(!dot.dead and !dot.reachedGoal) {
                return false;
            }
        }
        return true;
    }

    void calculateFitnessSum() {
        fitnessSum = 0.0f;
        for (auto &dot : dots) {
            fitnessSum += dot.fitness;
        }
    }

    void setBestDot() {
        float max = 0;
        int maxIndex = 0;
        int i = 0;
        for (auto &dot : dots) {
            if (dot.fitness > max) {
                max = dot.fitness;
                maxIndex = i;
            }
            ++i;
        }
        bestDot = maxIndex;
        if (dots[bestDot].reachedGoal) {
            minStep = dots[bestDot].brain.numSteps();
            std::cout << "min steps: " << minStep << "\n";
        }
    }

    void naturalSelection() {
        std::vector<Dot> newDots(dots.size());
        setBestDot();
        calculateFitnessSum();


        for (auto &newDot : newDots) {
            // select parent based on fitness
            newDot = selectParent();
        }
        // the champion lives on
        newDots[0] = dots[bestDot];
        newDots[0].isBest = true;

        dots = newDots;
        //std::copy(newDots.begin(), newDots.end(), dots.begin());

        for (auto &dot : dots) {
            dot.reset();
        }

        std::cout << "generation number: " << gen << "\n";
        ++gen;
    }

    Dot selectParent(){
        float rand_num = gen_random_float(0.0f, fitnessSum);
        float running_sum = 0.0;

        for (const auto &dot : dots) {
            running_sum += dot.fitness;
            if (running_sum >= rand_num) {
                return dot;
            }
        }

        return dots[dots.size()-1];
    }

    void mutateDemBabies() {
        for (auto &dot : dots) {
            dot.brain.mutate();
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

public:
    std::vector<Dot> dots;
    float fitnessSum = 0.0f;
    int gen = 1;

    int bestDot = 0;
    int minStep = 1000;

    float scale_factor = 1.0;

};


#endif //MLDOTS_POPULATION_HPP
//
// Created by Erik Sevre on 5/16/18.
//

#ifndef MLDOTS_POPULATION_HPP
#define MLDOTS_POPULATION_HPP

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "esml.hpp"
#include "Dot.hpp"

namespace ESML {
    class Population {

    public:
        explicit Population(size_t size) : dots(size) {}

        void draw() const {
            for (auto &dot : dots) {
                dot.draw(scale_factor);
            }
        }
        void update(const NumberType &scale = 1.0) {
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

        void calculateFitness(const PointType &goal) {
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

        bool didReachGoal() const {
            for (auto &dot : dots) {
                if (dot.reachedGoal) {
                    return true;
                }
            }
            return false;
        }

        void calculateFitnessSum() {
            fitnessSum = 0.0f;
            for (auto &dot : dots) {
                fitnessSum += dot.fitness;
            }
        }

        void setBestDot() {
            NumberType max = 0;
            int maxIndex = 0;
            int i = 0;
            for (auto &dot : dots) {
                dot.isBest = false;
                if (dot.fitness > max) {
                    max = dot.fitness;
                    maxIndex = i;
                }
                ++i;
            }
            bestDot = maxIndex;
            dots[bestDot].isBest = true;
            if (dots[bestDot].reachedGoal) {
                minStep = static_cast<int>(dots[bestDot].brain.numSteps());
                std::cout << "min steps: " << minStep << "\n";
            }
        }

        void sort_by_fitness() {
            std::sort(dots.begin(), dots.end(),
                      [](const Dot &a, const Dot &b)
                      {
                          return a.fitness < b.fitness;
                      });
        }

        void naturalSelection() {
            std::vector<Dot> newDots(dots.size());
            setBestDot();
            calculateFitnessSum();


            for (auto &newDot : newDots) {
                // select random parent based on fitness
                newDot = selectParent();
            }
            // the champion lives on
            newDots[0] = dots[bestDot];
            newDots[0].isBest = true;


            //dots = newDots;
            std::copy(newDots.begin(), newDots.end(), dots.begin());


            for (auto &dot : dots) {
                dot.reset();
            }

            if (dots[0].isBest) {
                std::cout << "correct best dot marked\n";
            }

            std::cout << "generation number: " << gen << "\n";
            ++gen;
        }

        Dot selectParent(){
            NumberType rand_num = gen_random_number(0.0f, fitnessSum);
            NumberType running_sum = 0.0;

            for (const auto &dot : dots) {
                running_sum += dot.fitness;
                if (running_sum >= rand_num) {
                    return dot;
                }
            }

            return dots[dots.size()-1];
        }

        void mutateDemBabies(const NumberType mutationRate = 0.01) {
            for (int i = 1; i < dots.size(); ++i) {
                dots[i].brain.mutate(mutationRate);
            }
        }

        NumberType gen_random_number(NumberType min, NumberType max) {
            // note: static makes this method MUCH faster
            static std::random_device rd;
            static std::seed_seq seed {rd(), rd()};
            static std::mt19937 mt(seed);
            static std::uniform_real_distribution<NumberType> distribution(min, max);
            return distribution(mt);
        }

    public:
        std::vector<Dot> dots;
        NumberType fitnessSum = 0.0f;
        int gen = 1;

        int bestDot = 0;
        int minStep = 1000;

        NumberType scale_factor = 1.0;

    };

}


#endif //MLDOTS_POPULATION_HPP
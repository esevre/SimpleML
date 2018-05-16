//
// Created by Erik Sevre on 5/15/18.
//

#ifndef MLDOTS_DOT_HPP
#define MLDOTS_DOT_HPP

#include <cmath>

#include <cinder/gl/gl.h>

#include "cinder/app/App.h"


#include "Brain.hpp"

class Dot {
public:
    Dot() : brain( 1000 ) {}
    Dot(ci::app::App *app) : parent_app(app), brain(1000) { setup(); }
    Dot(float x, float y) : brain(1000), pos(start_pos) {}
    Dot(const Dot &dot) : brain(dot.brain), pos(start_pos) {}
    Dot(Dot &&dot) : brain(std::move(dot.brain)), pos(start_pos) {}

    Dot &operator=(const Dot &dot) {
        brain = dot.brain;
        pos = start_pos;
        vel = ci::vec2(0, 0);
        acc = ci::vec2(0, 0);

        return *this;
    }
    //Dot &operator=(Dot &&dot) = default;

    void set_parent(ci::app::App *parent) {
        parent_app=parent;
        setup();
    }

    void draw(float scale) const;
    void draw(float scale, ci::Color color) const;

    void move();
    void update();

    void calculateFitness(const ci::vec2 &goal){
        if (reachedGoal) {
            // if the dot reached the goal then the fitness is based on the amount of steps it took to get there
            fitness = 1.0/16.0 + 10000.0 / (double)(brain.numSteps()*brain.numSteps());
        } else {
            // if the dot didn't reach the goal, then the fitness is basedo n how close it is to the goal
            float distanceToGoal = distance(pos, goal);
            fitness = 1.0 / (distanceToGoal*distanceToGoal);
            //fitness = 1.0 / ((pos.x - goal.x)*(pos.x - goal.x)+std::pow(pos.y - goal.y, 3));
        }
    }

    static float distance(const ci::vec2 &a, const ci::vec2 &b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    Dot gimmeBaby() const {
        Dot baby = *this;
        return baby;
    }

    void reset() {
        brain.reset();
        pos = start_pos;
        vel = ci::vec2(0,0);
        acc = ci::vec2(0,0);
        dead = false;
        reachedGoal = false;
    }

private:
    float length(const ci::vec2 &vec) const {
        return std::sqrt(vec.x*vec.x + vec.y*vec.y);
    }
    void limit_length(ci::vec2 &pt, float max_length) {
        float l = length(pt);
        if (l > 5.0){
            auto x = pt.x / l;
            auto y = pt.y / l;
            pt.x = x * max_length;
            pt.y = y * max_length;
        }
    }

    void setup() {
    }

public:
    ci::app::App *parent_app = nullptr;

    const ci::vec2 start_pos = ci::vec2(50, 90);
    ci::vec2 pos;
    ci::vec2 vel = ci::vec2(0, 0);
    ci::vec2 acc = ci::vec2(0, 0);
    Brain brain;
    float radius = 4;

    bool dead = false;
    bool reachedGoal = false;
    bool isBest = false;

    double fitness = 0.0;

    float width = 100.0f;
    float height = 100.0f;


};


#endif //MLDOTS_DOT_HPP
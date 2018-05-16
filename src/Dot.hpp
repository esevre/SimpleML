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
    Dot(float x, float y) : brain(1000), pos(x,y) {}
    Dot(const Dot &dot) = default;
    Dot(Dot &&dot) = default;

    Dot &operator=(const Dot &dot) = default;
    Dot &operator=(Dot &&dot) = default;

    void set_parent(ci::app::App *parent) {
        parent_app=parent;
        setup();
    }

    void draw(float scale);

    void move();

    void update();
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



    ci::vec2 pos = ci::vec2(50, 90);
    ci::vec2 vel = ci::vec2(0, 0);
    ci::vec2 acc = ci::vec2(0, 0);
    Brain brain;
    float radius = 4;

    bool dead = false;
    bool reachedGoal = false;
    bool isBest = false;

    float fitness = 0.0;

    float width = 100.0f;
    float height = 100.0f;


};


#endif //MLDOTS_DOT_HPP
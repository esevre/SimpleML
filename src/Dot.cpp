//
// Created by Erik Sevre on 5/15/18.
//

#include "Dot.hpp"

void Dot::draw(float scale) {
    ci::vec2 draw_pos = pos;
    draw_pos.x = pos.x * scale;
    draw_pos.y = pos.y * scale;
    if (isBest) {
        ci::gl::color(ci::Color(0, 1, 0));
        ci::gl::drawSolidEllipse(draw_pos, radius, radius);
    } else if (dead){
        ci::gl::color(ci::Color(1, 0, 0));
        ci::gl::drawSolidEllipse(draw_pos, 2*radius, 2*radius);
    } else {
        ci::gl::color(ci::Color(0, 0, 0));
        ci::gl::drawSolidEllipse(draw_pos, 2*radius, 2*radius);
    }
}

void Dot::move() {
    if (!dead) {
        acc = brain.getNextDirection();
        vel += acc;
        limit_length(vel, 5.0);
        pos += vel;
        if (brain.is_finished()) {
            dead = true;
        }
    }
}

void Dot::update() {
    if (!dead && !reachedGoal) {
        move();
        if (pos.x< 2|| pos.y<2 || pos.x>width-2 || pos.y>height -2) {//if near the edges of the window then kill it
            dead = true;
            //dist(pos.x, pos.y, goal.x, goal.y)
        } else if ( length(pos - brain.getGoal()) < 5.0f) { //if reached goal
            reachedGoal = true;
        }
//        else if (pos.x< 600 && pos.y < 310 && pos.x > 0 && pos.y > 300) {//if hit obstacle
//            dead = true;
//        }
    }
}







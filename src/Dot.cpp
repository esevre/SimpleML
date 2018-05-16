//
// Created by Erik Sevre on 5/15/18.
//

#include "Dot.hpp"

///
/// \param scale adjust points position on screen
/// \param color of dot to draw
void Dot::draw(float scale, ci::Color color) const {
    ci::vec2 draw_pos = pos;
    draw_pos.x = pos.x * scale;
    draw_pos.y = pos.y * scale;
    ci::gl::color(color);
    ci::gl::drawSolidEllipse(draw_pos, radius, radius);
}

void Dot::draw(float scale) const {
    if (isBest) {
        ci::vec2 draw_pos = pos;
        draw_pos.x = pos.x * scale;
        draw_pos.y = pos.y * scale;
        ci::gl::color(ci::Color(0, 1, 0));
        ci::gl::drawSolidEllipse(draw_pos, 2*radius, 2*radius);
    } else if (dead){
        draw(scale, ci::Color(1, 0, 0));
    } else if (reachedGoal){
        draw(scale, ci::Color(0, 0, 1));
    } else {
        draw(scale, ci::Color(0, 0, 0));
    }
}

void Dot::move() {
    if (!dead) {
        acc = brain.getNextDirection();
        vel += acc;
        limit_length(vel, 5.0);
        pos += vel;
        if (brain.at_end()) {
            dead = true;
        }
    }
}

void Dot::update() {
    if (!dead && !reachedGoal) {
        move();
        // if near the edges of the window then kill it
        if (pos.x < 2) {
            pos.x = 0;
            dead = true;
            //dist(pos.x, pos.y, goal.x, goal.y)
        } else if (pos.y<2) {
            pos.y = 0;
            dead = true;
        } else if(pos.x > width - 2) {
            pos.x = width;
            dead = true;
        } else if (pos.y > height - 2) {
            pos.y = height;
            dead = true;
        }else if ( length(pos - brain.getGoal()) < 1.1f) {
                //if reached goal, then mark that
            reachedGoal = true;
        } else if ( pos.x < 70 and std::fabs(pos.y - 35) < 3.0) {
            pos.y = 35; // fix pos to line
            dead = true;
        } else if ( pos.x > 30 and std::fabs(pos.y - 70) < 3.0) {
            pos.y = 70; // fix pos to line
            dead = true;
        }
    }
}







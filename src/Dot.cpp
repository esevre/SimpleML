//
// Created by Erik Sevre on 5/15/18.
//

#include "Dot.hpp"


namespace ESML {
///
/// \param scale adjust points position on screen
/// \param color of dot to draw
        void Dot::draw(const NumberType scale, const ColorType color) const {
            PointType draw_pos = pos;
            draw_pos.x = pos.x * scale;
            draw_pos.y = pos.y * scale;

            SetGlColor(color);
            DrawSolidCircle(draw_pos, radius);
        }

        void Dot::draw(NumberType scale) const {
            if (isBest) {
                PointType draw_pos = pos;
                draw_pos.x = pos.x * scale;
                draw_pos.y = pos.y * scale;

                SetGlColorRGB( 0, 1, 0 );
                DrawSolidCircle(draw_pos, 2*radius);
            } else if (dead){
                draw(scale, ColorType(1, 0, 0));
            } else if (reachedGoal){
                draw(scale, ColorType(0, 0, 1));
            } else {
                draw(scale, ColorType(0, 0, 0));
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
                } else if ( pos.x < 70.0f and std::fabs(pos.y - 35.0f) < 3.0f) {
                    pos.y = 35; // fix pos to line
                    dead = true;
                } else if ( pos.x > 30.0f and std::fabs(pos.y - 70.0f) < 3.0f) {
                    pos.y = 70; // fix pos to line
                    dead = true;
                }
            }
        }

}








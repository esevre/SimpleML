#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


#include "Dot.hpp"
#include "Population.hpp"

#include <vector>

using namespace ESML;

class MLDotsApp : public ci::app::App {
public:
	void setup() override;
	//void mouseDown( ci::app::MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
    Dot goal_dot;
    Population test = Population(2000);
    float scale_factor = 1.0;

    ci::vec2 line_1_a = ci::vec2(  0, 35);
    ci::vec2 line_1_b = ci::vec2( 70, 35);
    ci::vec2 line_2_a = ci::vec2( 30, 70);
    ci::vec2 line_2_b = ci::vec2(100, 70);
    ci::vec2 line_1_a_scaled;
    ci::vec2 line_1_b_scaled;
    ci::vec2 line_2_a_scaled;
    ci::vec2 line_2_b_scaled;
};

void MLDotsApp::setup()
{
    goal_dot.pos = ci::vec2(50, 10);
}

//void MLDotsApp::mouseDown( ci::app::MouseEvent event ) {}

void MLDotsApp::update()
{
    //test.dots[0].isBest = true;
    if (test.allDotsDead()) {
        // genetic algorithm
        test.calculateFitness(goal_dot.pos);
        test.naturalSelection();
        test.mutateDemBabies();
    } else {
        test.update();
    }

    scale_factor = std::min(this->getWindowWidth(), this->getWindowHeight()) / 100.0f;
    test.update(scale_factor);

    line_1_a_scaled = line_1_a * scale_factor;
    line_1_b_scaled = line_1_b * scale_factor;
    line_2_a_scaled = line_2_a * scale_factor;
    line_2_b_scaled = line_2_b * scale_factor;

}

void MLDotsApp::draw()
{
	ci::gl::clear( ci::Color( 1.0f, 1.0f, 1.0f ) );

	ci::Rectf bounding_box(0.0f, 0.0f, 100.0f * scale_factor, 100.0f * scale_factor);
	ci::gl::drawStrokedRect(bounding_box, 1.0);

    ci::gl::drawLine(line_1_a_scaled, line_1_b_scaled);
    ci::gl::drawLine(line_2_a_scaled, line_2_b_scaled);

    test.draw();
    goal_dot.draw(scale_factor, ci::Color(0,0,1));


}

CINDER_APP( MLDotsApp, ci::app::RendererGl )

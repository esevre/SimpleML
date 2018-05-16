#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


#include "Dot.hpp"

#include <vector>


class MLDotsApp : public ci::app::App {
public:
	void setup() override;
	void mouseDown( ci::app::MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
    Dot dot;
    std::vector<Dot> dots;
    float scale_factor = 1.0;
};

void MLDotsApp::setup()
{
    dot = Dot(50, 90);
    dots.resize(50);
    //dot.set_parent(this);
}

void MLDotsApp::mouseDown( ci::app::MouseEvent event )
{
}

void MLDotsApp::update()
{
    for (auto &d : dots) {
        d.update();
    }
    dot.update();
    scale_factor = std::min(this->getWindowWidth(), this->getWindowHeight()) / 100.0f;
}

void MLDotsApp::draw()
{
	ci::gl::clear( ci::Color( 1.0f, 1.0f, 1.0f ) );
	ci::Rectf bounding_box(0.0f, 0.0f, 100.0f * scale_factor, 100.0f * scale_factor);
	ci::gl::drawStrokedRect(bounding_box, 1.0);
	dot.draw(scale_factor);
	for (auto &d : dots) {
	    d.draw(scale_factor);
	}
}

CINDER_APP( MLDotsApp, ci::app::RendererGl )

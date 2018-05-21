//
// Created by Erik Sevre on 5/21/18.
//

#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

namespace ESML {
    using SizeType = size_t;
    using PointType = ci::vec2;
    using NumberType = float;
    using VectorType = std::vector<PointType>;
    using ColorType = ci::Color;
    using AppPointer = ci::app::App*;

    using ItType = VectorType::iterator;
    using ConstItType = VectorType::const_iterator;

    #define SetGlColor( Color ) ci::gl::color(Color)
    #define SetGlColorRGB( r, g, b ) SetGlColor( ColorType(r,g,b) )

    #define DrawSolidEllipse( Position, RadiusX, RadiusY ) ci::gl::drawSolidEllipse(Position, RadiusX, RadiusY)
    #define DrawSolidCircle( Position, Radius ) ci::gl::drawSolidEllipse(Position, Radius, Radius)


}





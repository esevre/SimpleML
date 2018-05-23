//
// Created by Erik Sevre on 5/21/18.
//

#pragma once

#include <limits>

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



    /*
     * Constexpr version of the square root
     * Return value:
     *	- For a finite and non-negative value of "x", returns an approximation for the square root of "x"
     *   - Otherwise, returns NaN
     */
    namespace Detail
    {
        NumberType constexpr sqrtNewtonRaphson(NumberType x, NumberType curr, NumberType prev)
        {
            return curr == prev
                   ? curr
                   : sqrtNewtonRaphson(x, 0.5f * (curr + x / curr), curr);
        }
    }
    NumberType constexpr sqrt(NumberType x)
    {
        return x >= 0 && x < std::numeric_limits<NumberType>::infinity()
               ? Detail::sqrtNewtonRaphson(x, x, 0)
               : std::numeric_limits<NumberType>::quiet_NaN();
    }


}





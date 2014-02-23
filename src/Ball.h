//! This code sets up the parameters for ball detection.

#ifndef HAVE_Ball_H
#define HAVE_Ball_H

#include <vector>
#include "Vision/ColorImage.h"

class Ball
{
public:
    double m_majorRadius;
    double m_minorRadius;
    double m_rawScore;
    double m_xPos;
    double m_yPos;
    double m_score;
    double m_rotation;
    double m_xMax;
    bool m_bothFound;

    static vector<Ball> FindCircularTargets(ColorImage *image);
    double GetHorizontalAngle();
    void Print();
};

#endif

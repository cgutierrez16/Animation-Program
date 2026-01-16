/**
 * @file PolyDrawable.cpp
 * @author Carlos Gutierrez
 */

#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name Name of PolyDrawable
 */
PolyDrawable::PolyDrawable(const std::wstring& name): Drawable(name)
{
}

/**
 * Draws PolyDrawable
 * @param graphics Graphics context to draw PolyDrawable
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }
}

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
bool PolyDrawable::HitTest(wxPoint pos)
{
    return mPath.Contains(pos.x, pos.y);
}

/**
 * Places points to draw polygon
 * @param point Point to draw to
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}

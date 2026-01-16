/**
 * @file HeadTop.cpp
 * @author Carlos Gutierrez
 */

#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name The head top name
 * @param filename Image file for the head top
 */
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename) : ImageDrawable (name, filename)
{
}

/**
 * Draw head top
 * @param graphics Graphics context
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);
    DrawEyebrows(graphics);
    DrawEyes(graphics);
}

/**
 * Drawe eyebrows on head top
 * @param graphics Graphics context of head top
 */
void HeadTop::DrawEyebrows(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen eyebrowPen(*wxBLACK, 6);
    wxPoint p = TransformPoint(wxPoint(75, 60));
    wxPoint p2 = TransformPoint(wxPoint(30, 60));

    graphics->SetPen(eyebrowPen);

    graphics->PushState();
    graphics->Translate(p.x, p.y);
    graphics->Rotate(-mPlacedR);
    graphics->StrokeLine(-12, 0, 12, 0);
    graphics->PopState();

    graphics->PushState();
    graphics->Translate(p2.x, p2.y);
    graphics->Rotate(-mPlacedR);
    graphics->StrokeLine(-12, 0, 12, 0);
    graphics->PopState();
}

/**
 * Draw eyes on head top
 * @param graphics Graphics context for head top
 */
void HeadTop::DrawEyes(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen eyePen(*wxBLACK, 2);
    wxPoint e1 = TransformPoint(wxPoint(75, 80));
    wxPoint e2 = TransformPoint(wxPoint(30, 80));


    float wid = 15.0f;
    float hit = 20.0f;

    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

    graphics->PushState();
    graphics->Translate(e2.x, e2.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Add the channels for this drawable to a timeline
 * @param timeline The timeline class.
 */
void HeadTop::SetTimeline(Timeline *timeline)
{
    Drawable::SetTimeline(timeline);
    timeline->AddChannel(&mChannelPosition);
}

/**
 * Set a keyframe based on the current position.
 */
void HeadTop::SetKeyframe()
{
    Drawable::SetKeyframe();
    mChannelPosition.SetKeyframe(GetPosition());
}

/**
 * Get a keyframe update from the animation system.
 */
void HeadTop::GetKeyframe()
{
    Drawable::GetKeyframe();
    if (mChannelPosition.IsValid())
        SetPosition(mChannelPosition.GetPosition());
}
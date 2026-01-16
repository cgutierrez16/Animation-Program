/**
 * @file PolyDrawable.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef POLYDRAWABLE_H
#define POLYDRAWABLE_H

#include <vector>
#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable{
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// Collection of wxPoints
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;
public:
    /// Destructor
    virtual ~PolyDrawable() {}

    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable &) = delete;

    /// Assignment operator
    void operator=(const PolyDrawable &) = delete;

    PolyDrawable(const std::wstring & name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint position) override;

    void AddPoint(wxPoint point);

    /**
     * Get color of poly drawable
     * @return Color of PolyDrawable
     */
    wxColour GetColor() const { return mColor; }

    /**
     * Set color of poly drawable
     * @param color Color of poly drawable
     */
    void SetColor(wxColour color) { mColor = color; };
};



#endif //POLYDRAWABLE_H

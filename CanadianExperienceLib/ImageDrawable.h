/**
 * @file ImageDrawable.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef IMAGEDRAWABLE_H
#define IMAGEDRAWABLE_H
#include "Drawable.h"

/**
 * Drawable class that can use images
 */
class ImageDrawable : public Drawable {
private:
    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// Center of image drawable
    wxPoint mCenter = wxPoint(0, 0);

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

public:
    ImageDrawable(const std::wstring& name, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    bool HitTest(wxPoint pos);

    /**
     * Set the center of ImageDrawable
     * @param point Center of ImageDrawable
     */
    void SetCenter(wxPoint point) { mCenter = point; }

    /**
     * Get center of ImageDrawable
     * @return Center of ImageDrawable object
     */
    wxPoint GetCenter() { return mCenter; }
};



#endif //IMAGEDRAWABLE_H

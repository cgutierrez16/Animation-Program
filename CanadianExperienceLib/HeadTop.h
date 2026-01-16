/**
 * @file HeadTop.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef HEADTOP_H
#define HEADTOP_H

#include "ImageDrawable.h"

class AnimChannelPosition;
class Timeline;

/**
 * Class representing top of character head
 */
class HeadTop : public ImageDrawable {
private:
    /// AnimChannelPosition class this HeadTop is a part of
    AnimChannelPosition mChannelPosition;
public:
    HeadTop(const std::wstring& name, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawEyebrows(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawEyes(std::shared_ptr<wxGraphicsContext> graphics);
    wxPoint TransformPoint(wxPoint p);

    void SetTimeline(Timeline* timeline) override;
    void SetKeyframe() override;
    void GetKeyframe() override;

    /**
     * Makes HeadTop move independently
     * @return True
     */
    bool IsMovable() override { return true; }
};



#endif //HEADTOP_H

/**
 * @file TimelineDlg.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef TIMELINEDLG_H
#define TIMELINEDLG_H

class Timeline;


/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// Timeline
    Timeline* mTimeline;
    /// Number of frames in the animation
    int mNumberOfFrames;
    /// Frame rate of the animation
    int mFrameRate;
public:
    TimelineDlg(wxWindow* parent, Timeline* timeline);
    void OnOK(wxCommandEvent& event);
};



#endif //TIMELINEDLG_H

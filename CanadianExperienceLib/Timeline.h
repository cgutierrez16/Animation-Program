/**
 * @file Timeline.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef TIMELINE_H
#define TIMELINE_H

#include <cmath>

class AnimChannel;

/**
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline {
private:
    /// Number of total frames in our animation
    int mNumFrames = 300;

    /// Frame rate for our animation
    int mFrameRate = 30;

    /// Current time in our animation
    double mCurrentTime = 0.0;

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;
public:
    /// Copy constructor (disabled)
    Timeline(const Timeline &) = delete;

    /// Assignment operator
    void operator=(const Timeline &) = delete;
    Timeline();
    void AddChannel(AnimChannel* animChannel);

    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    void SetCurrentTime(double currentTime);

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return static_cast<double>(mNumFrames) / mFrameRate; }

    /**
     * Get the current frame.
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return floor(mCurrentTime * mFrameRate); }
};



#endif //TIMELINE_H

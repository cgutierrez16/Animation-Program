/**
 * @file AnimChannel.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef ANIMCHANNEL_H
#define ANIMCHANNEL_H

class Timeline;

/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:
    /// Name of anim channel
    std::wstring mName;
    /// Keyframe 1 for anim channel
    int mKeyframe1 = -1;
    /// Keyframe 2 for anim channel
    int mKeyframe2 = -1;
    /// The timeline object
    Timeline *mTimeline = nullptr;
protected:
    /// Default constructor
    AnimChannel() { }

    /**
     * Class descibing a keyframe for AnimChannel
     */
    class Keyframe
    {
    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    private:
        /// Frame animation is on
        int mFrame;
        /// The channel this keyframe is associated with
        AnimChannel *mChannel;
    public:
        /// Default constructor (disabled)
        Keyframe() = delete;
        /// Copy constructor (disabled)
        Keyframe(const Keyframe &) = delete;
        /// Assignment operator
        void operator=(const Keyframe &) = delete;

        /// Use this keyframe as keyframe 1
        virtual void UseAs1() = 0;
        /// Use this keyframe as keyframe 2
        virtual void UseAs2() = 0;
        /// Use this keyframe as the position
        virtual void UseOnly() = 0;

        /**
         * Set the frame in animation
         * @param frame Frame in animation to set
         */
        void SetFrame(int frame) { mFrame = frame; }

        /**
         * Get a frame from the animation
         * @return mFrame Current frame
         */
        int GetFrame() const { return mFrame; }
    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Compute a position that is an interpolation
     * between two keyframes
     *
     * This function is called after Use1 and Use2,
     * so we have pointers to valid keyframes of the
     * type KeyframePosition. This function computes the
     * tweening.
     *
     * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
     * Other values interpolate between.
     */
    virtual void Tween(double t) = 0;

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:
    /// Destructor
    virtual ~AnimChannel() {}
    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;
    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    bool IsValid();
    void DeleteKeyframe(int frame);
    void SetFrame(int currFrame);

    /**
     * Set the mName variable of an anim channel
     * @param name wstring representing name of anim channel
     */
    void SetName(const std::wstring& name) { mName = name; }

    /**
     * Return the name of this anim channel
     * @return wstring Name of anim channel
     */
    std::wstring GetName() { return mName; }

    /**
     * Get timeline this anim channel is a part of
     * @return timeline class this anim channel is a part of
     */
    Timeline *GetTimeline() { return mTimeline; }

    /**
     * Sets the timeline this anim channel will be a part of
     * @param timeline Timeline to set this anim channel to
     */
    void SetTimeline(Timeline *timeline) { mTimeline = timeline; }
};



#endif //ANIMCHANNEL_H

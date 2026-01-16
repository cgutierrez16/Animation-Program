/**
 * @file AnimChannelAngle.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef ANIMCHANNELANGLE_H
#define ANIMCHANNELANGLE_H
#include "AnimChannel.h"

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:
    /// Angle of our animation
    double mAngle = 0;
protected:
    void Tween(double t) override;

    /**
     * Keyframe class for angles of characters
     */
    class KeyframeAngle : public Keyframe
    {
    private:
        /// Angle of keyframe
        double mAngle;
        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;
    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /// Default constructor (disabled)
        KeyframeAngle() = delete;
        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;
        /// Assignment operator
        void operator=(const KeyframeAngle &) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

        /**
         * Get the angle of a keyframe
         * @return double Angle of the keyframe
         */
        double GetAngle() { return mAngle; }
    };
private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;
    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;
public:
    /// Constructor
    AnimChannelAngle() { }
    /// Destructor
    virtual ~AnimChannelAngle() {}
    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;
    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;

    /**
     * Get the angle of the anim channel
     * @return double Angle of anim channel
     */
    double GetAngle() { return mAngle; }


    void SetKeyframe(double angle);
    void DeleteKeyframe(int frame);

};



#endif //ANIMCHANNELANGLE_H

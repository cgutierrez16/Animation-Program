/**
 * @file AnimChannelPosition.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef ANIMCHANNELPOSITION_H
#define ANIMCHANNELPOSITION_H
#include "AnimChannel.h"

/**
 * Animation channel for position
 */
class AnimChannelPosition : public AnimChannel{
private:
    /// The position of our animation
    wxPoint mPosition;
protected:
    void Tween(double t) override;

    /**
     * Keyframe for the position of characters
     */
    class KeyframePosition : public Keyframe
    {
    private:
        /// Position of keyframe
        wxPoint mPosition = wxPoint(0, 0);
        /// The channel this keyframe is associated with
        AnimChannelPosition *mChannel;
    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param position The position for the keyframe
         */
        KeyframePosition(AnimChannelPosition *channel, wxPoint position) :
                Keyframe(channel), mChannel(channel), mPosition(position) {}

        /// Default constructor (disabled)
        KeyframePosition() = delete;
        /// Copy constructor (disabled)
        KeyframePosition(const KeyframePosition &) = delete;
        /// Assignment operator
        void operator=(const KeyframePosition &) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the position
        void UseOnly() override { mChannel->mPosition = mPosition; }

        /**
         * Get the position of the keyframe
         * @return wxPoint Position of keyframe
         */
        wxPoint GetPosition() { return mPosition; }
    };
private:
    /// The first angle keyframe
    KeyframePosition *mKeyframe1 = nullptr;
    /// The second angle keyframe
    KeyframePosition *mKeyframe2 = nullptr;
public:
    AnimChannelPosition() { }
    /// Destructor
    virtual ~AnimChannelPosition() {}
    /// Copy constructor (disabled)
    AnimChannelPosition(const AnimChannelPosition &) = delete;
    /// Assignment operator
    void operator=(const AnimChannelPosition &) = delete;

    wxPoint GetPosition();
    void SetKeyframe(wxPoint position);
};



#endif //ANIMCHANNELPOSITION_H

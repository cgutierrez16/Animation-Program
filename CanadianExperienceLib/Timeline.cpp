/**
 * @file Timeline.cpp
 * @author Carlos Gutierrez
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
 * Constructor
 */
Timeline::Timeline()
{
}

/**
 * Add a channel to the Timeline
 * @param animChannel AnimChannel to add to the timeline
 */
void Timeline::AddChannel(AnimChannel* animChannel)
{
    mChannels.push_back(animChannel);
    animChannel->SetTimeline(this);
}

/**
 * Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * @param t The new time to set
 */
void Timeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}
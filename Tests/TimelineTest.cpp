/**
 * @file TimelineTest.cpp
 * @author Carlos Gutierrez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>
#include <AnimChannelAngle.h>

TEST(TimelineTest, MemberVariables)
{
    Timeline timeline;
    ASSERT_EQ(timeline.GetNumFrames(), 300);
    ASSERT_EQ(timeline.GetFrameRate(), 30);
    ASSERT_NEAR(0, timeline.GetCurrentTime(), 0.00001);

    timeline.SetFrameRate(60);
    timeline.SetNumFrames(600);
    timeline.SetCurrentTime(5.5);

    ASSERT_EQ(timeline.GetFrameRate(), 60);
    ASSERT_EQ(timeline.GetNumFrames(), 600);
    ASSERT_NEAR(5.5, timeline.GetCurrentTime(), 0.00001);
}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}
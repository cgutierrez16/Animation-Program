/**
 * @file AnimChannelAngleTest.cpp
 * @author Carlos Gutierrez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>
#include <AnimChannel.h>

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle channelAngle;
    channelAngle.SetName(L"Test Name");

    ASSERT_EQ(std::wstring(L"Test Name"), channelAngle.GetName());
}
/**
 * @file DrawableTest.cpp
 * @author Carlos Gutierrez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

using namespace std;

class DrawableMock : public Drawable
{
public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Constructor)
{
    DrawableMock drawable(L"Bob");
    ASSERT_EQ(std::wstring(L"Bob"), drawable.GetName());
}

TEST(DrawableTest, Position)
{
    DrawableMock drawable(L"Bob");
    ASSERT_EQ(drawable.GetPosition(), wxPoint(0, 0));

    drawable.SetPosition(wxPoint(5, 10));

    ASSERT_EQ(drawable.GetPosition(), wxPoint(5, 10));
}

TEST(Drawable, Rotation)
{
    DrawableMock drawable(L"Bob");

    ASSERT_NEAR(0, drawable.GetRotation(), 0.00001);

    drawable.SetRotation(5.6);

    ASSERT_NEAR(5.6, drawable.GetRotation(), 0.00001);
}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}
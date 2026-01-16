/**
 * @file PictureObserverTest.cpp
 * @author Carlos Gutierrez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <PictureObserver.h>
#include <Picture.h>

class PictureObserverMock : public PictureObserver
{
public:
    PictureObserverMock() : PictureObserver() {}
    void UpdateObserver() override { mUpdated = true; }
    bool mUpdated = false;

};

TEST(PictureObserverTest, Construct) {
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, GetPicture)
{
    auto picture = std::make_shared<Picture>();

    PictureObserverMock observer;

    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_EQ(picture, observer.GetPicture());
}

TEST(PictureObserverTest, TwoObservers)
{
    auto picture = std::make_shared<Picture>();

    PictureObserverMock observer1;
    PictureObserverMock observer2;

    observer1.SetPicture(picture);
    observer2.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer1.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, DestroyObserver)
{
    auto picture = std::make_shared<Picture>();

    PictureObserverMock observer1;
    observer1.SetPicture(picture);

    {
        PictureObserverMock observer2;

        // And set it for the observer:
        observer2.SetPicture(picture);
    }

    picture->UpdateObservers();

    ASSERT_TRUE(observer1.mUpdated);
}
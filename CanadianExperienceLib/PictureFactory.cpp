/**
 * @file PictureFactory.cpp
 * @author Carlos Gutierrez
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "BobFactory.h"
#include "Picture.h"
#include "Actor.h"
#include "ImageDrawable.h"



/**
 * Factory method to create a new picture.
 * @param imagesDir Directory that contains the images for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring imagesDir)
{
    std::shared_ptr<Picture> picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 500));
    picture->AddActor(harold);

    // Create and add Bob
    BobFactory bobFactory;
    auto bob = bobFactory.Create(imagesDir);

    // This is where Bob will start out.
    bob->SetPosition(wxPoint(500, 500));
    picture->AddActor(bob);

    return picture;
}
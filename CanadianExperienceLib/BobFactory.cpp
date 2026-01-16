/**
 * @file BobFactory.cpp
 * @author Carlos Gutierrez
 */

#include "pch.h"
#include "BobFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

/**
* This is a factory method that creates our Harold actor.
* @param imagesDir Directory that contains the images for this application
* @return Pointer to an actor object.
*/
std::shared_ptr<Actor> BobFactory::Create(std::wstring imagesDir)
{
    std::shared_ptr<Actor> actor = std::make_shared<Actor>(L"Bob");

    auto shirt = make_shared<ImageDrawable>(L"Shirt", imagesDir + L"/black_coat.png");
    shirt->SetCenter(wxPoint(44, 138));
    shirt->SetPosition(wxPoint(0, -114));
    actor->SetRoot(shirt);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/jeans_lleg.png");
    lleg->SetCenter(wxPoint(11, 9));
    lleg->SetPosition(wxPoint(20, 0));
    shirt->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/jeans_rleg.png");
    rleg->SetCenter(wxPoint(39, 9));
    rleg->SetPosition(wxPoint(-27, 0));
    shirt->AddChild(rleg);

    auto headb = make_shared<ImageDrawable>(L"Head Bottom", imagesDir + L"/bob_headb.png");
    headb->SetCenter(wxPoint(44, 31));
    headb->SetPosition(wxPoint(0, -130));
    shirt->AddChild(headb);

    auto headt = make_shared<HeadTop>(L"Head Top", imagesDir + L"/bob_headt.png");
    headt->SetCenter(wxPoint(55, 109));
    headt->SetPosition(wxPoint(5, -16));
    headb->AddChild(headt);

    auto larm = std::make_shared<PolyDrawable>(L"Left Arm");
    larm->SetColor(wxColour(0, 0, 0));
    larm->SetPosition(wxPoint(50, -130));
    larm->AddPoint(wxPoint(-13, -7));
    larm->AddPoint(wxPoint(-13, 96));
    larm->AddPoint(wxPoint(8, 96));
    larm->AddPoint(wxPoint(8, -7));
    shirt->AddChild(larm);

    auto rarm = std::make_shared<PolyDrawable>(L"Right Arm");
    rarm->SetColor(wxColour(0, 0, 0));
    rarm->SetPosition(wxPoint(-45, -130));
    rarm->AddPoint(wxPoint(-13, -7));
    rarm->AddPoint(wxPoint(-13, 96));
    rarm->AddPoint(wxPoint(8, 96));
    rarm->AddPoint(wxPoint(8, -7));
    shirt->AddChild(rarm);

    auto lhand = std::make_shared<PolyDrawable>(L"Left Hand");
    lhand->SetColor(wxColour(213, 168, 130));
    lhand->SetPosition(wxPoint(0, 96));
    lhand->AddPoint(wxPoint(-12, -2));
    lhand->AddPoint(wxPoint(-12, 17));
    lhand->AddPoint(wxPoint(11, 17));
    lhand->AddPoint(wxPoint(11, -2));
    larm->AddChild(lhand);

    auto rhand = std::make_shared<PolyDrawable>(L"Right Hand");
    rhand->SetColor(wxColour(213, 168, 130));
    rhand->SetPosition(wxPoint(0, 96));
    rhand->AddPoint(wxPoint(-12, -2));
    rhand->AddPoint(wxPoint(-12, 17));
    rhand->AddPoint(wxPoint(11, 17));
    rhand->AddPoint(wxPoint(11, -2));
    rarm->AddChild(rhand);


    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(shirt);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}
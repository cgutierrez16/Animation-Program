/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>

#include "ViewTimeline.h"
#include "Actor.h"
#include "Picture.h"
#include "TimelineDlg.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";


/**
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir Image directory to pull images from
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir) :
    wxScrolled(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mPointerImage = std::make_unique<wxImage>(imagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
                 &ViewTimeline::OnEditTimelineProperties, this,
                 XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    auto size = GetPicture()->GetSize();
    SetVirtualSize((GetPicture()->GetTimeline()->GetNumFrames() * 4) + 25, size.GetHeight());
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    graphics->SetPen(*wxBLACK);

    auto timeline = GetPicture()->GetTimeline();
    int numFrames = timeline->GetNumFrames();
    int frameRate = timeline->GetFrameRate();
    double currentTime = timeline->GetCurrentTime();

    for (int tickNum = 0; tickNum <= numFrames; tickNum++) {
        int x = BorderLeft + (TickSpacing * tickNum);
        bool onSecond = (tickNum % frameRate) == 0;

        int tickHeight;
        if (onSecond)
        {
            tickHeight = TickLong;
        } else
        {
            tickHeight = TickShort;
        }

        // Draw the tick mark
        graphics->StrokeLine(x, TickTop, x, TickTop + tickHeight);

        wxFont font(TickFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        graphics->SetFont(font, *wxBLACK);

        // Draw the second markers
        if (onSecond) {
            std::wstringstream str;
            str << (tickNum / frameRate);
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);
            graphics->DrawText(wstr, x - w / 2, TickTop + TickLong + 2);
        }
    }

    mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);

    graphics->DrawBitmap(mPointerBitmap,
    (BorderLeft / 2) + (currentTime * frameRate * 4), TickTop,
    mPointerImage->GetWidth(),
    mPointerImage->GetHeight());
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;

    if(mMovingPointer)
    {
        int xx = 0;
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    if (mMovingPointer && event.Dragging())
    {
        Timeline *timeline = GetPicture()->GetTimeline();

        double newTime = (click.x - BorderLeft) / (double)(timeline->GetFrameRate() * TickSpacing);

        newTime = std::max(0.0, std::min(newTime, timeline->GetDuration()));

        GetPicture()->SetAnimationTime(newTime);
        GetPicture()->UpdateObservers();
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Handle SetKeyframe when button is pressed
 * @param event Command event
 */
void ViewTimeline::OnSetKeyframe(wxCommandEvent& event) {
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * handle DeleteKeyframe when button is pressed
 * @param event Command event
 */
void ViewTimeline::OnDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    auto frame = GetPicture()->GetTimeline()->GetCurrentFrame();
    for (auto actor : *picture)
    {
        actor->DeleteKeyframe(frame);
    }

    GetPicture()->SetAnimationTime(0);
}
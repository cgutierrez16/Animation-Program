/**
 * @file PictureObserver.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef PICTUREOBSERVER_H
#define PICTUREOBSERVER_H

#include <memory>

class Picture;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class PictureObserver {
protected:
    /// Constructor
    PictureObserver() {}
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;
public:
    virtual ~PictureObserver();
    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver &) = delete;
    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    /**
     * Get picture to observe
     * @return Picture being observed
     */
    std::shared_ptr<Picture> GetPicture() const {return mPicture;}

    void SetPicture(std::shared_ptr<Picture> picture);

};



#endif //PICTUREOBSERVER_H

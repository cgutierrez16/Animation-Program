/**
 * @file BobFactory.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef BOBFACTORY_H
#define BOBFACTORY_H

class Actor;

/**
 * Factory class that builds the Bob character
 */
class BobFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //BOBFACTORY_H

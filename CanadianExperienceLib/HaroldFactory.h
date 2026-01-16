/**
 * @file HaroldFactory.h
 * @author Carlos Gutierrez
 *
 *
 */
 
#ifndef HAROLDFACTORY_H
#define HAROLDFACTORY_H

class Actor;

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //HAROLDFACTORY_H

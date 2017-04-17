/////////////////////////////////////////////////////////
// servicelocator.cpp
//
// Ben Storey
//
// The only reason I didn't throw all this in the header file is because
// then it's forced to include lots of other header files that I don't
// necessarily want to force the user to include
//
/////////////////////////////////////////////////////////

#include "servicelocator.hpp"

#include "audio/soundmanager.hpp"
#include "input/inputmanager.hpp"
#include "event/eventmanager.hpp"
#include "scene/scenemanager.hpp"
#include "resource/resourcemanager.hpp"
#include "graphics/renderer.hpp"

void jimbo::ServiceLocator::setService(SoundManager * sm)
{
    sm_.reset(sm);
}

void jimbo::ServiceLocator::setService(InputManager * im)
{
    im_.reset(im);
}

void jimbo::ServiceLocator::setService(EventManager * em)
{
    em_.reset(em);
}

void jimbo::ServiceLocator::setService(SceneManager * scm)
{
    scm_.reset(scm);
}

void jimbo::ServiceLocator::setService(ResourceManager * rm)
{
    rm_.reset(rm);
}

void jimbo::ServiceLocator::setService(Renderer * r)
{
    r_.reset(r);
}

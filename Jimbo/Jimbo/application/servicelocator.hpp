#ifndef JIMBO_SERVICELOCATOR_HPP
#define JIMBO_SERVICELOCATOR_HPP

/////////////////////////////////////////////////////////
// servicelocator.hpp
//
// Ben Storey
//
// Already an issue I'm having is finding the injected services in a clean way, without passing around
// many many pointers. This lends itself nicely to the service locator pattern, where before startup (or even during runtime)
// we can inject new services. These can then be passed around to other classes that need them easily.
//
// I've been in very mixed minds about whether to take ownership in this class or merely be a collection
// of raw pointers. In the end I decided to do a shared pointer, because then we can still add
// decorators relatively easily and keeping references to a service should always be safe
//
// The locator is also made noncopyable, because I don't want people to accidentally pass the locator by value and have
// it's pointers changed, without it reflecting in the rest of the application
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <memory>

namespace jimbo
{
    class Config;
    class SoundManager;
    class InputManager;
    class EventManager;
    class SceneManager;
    class ResourceManager;
    class Renderer;
    
    class ServiceLocator : boost::noncopyable
    {
    public:

        void setService(SoundManager* sm);
        void setService(InputManager* im);
        void setService(EventManager* em);
        void setService(SceneManager* scm);
        void setService(ResourceManager* rm);
        void setService(Renderer* r);
        void setService(Config* c);

        std::shared_ptr<SoundManager>    soundManager()       const { return sm_; }
        std::shared_ptr<InputManager>    inputManager()       const { return im_; }
        std::shared_ptr<EventManager>    eventManager()       const { return em_; }
        std::shared_ptr<SceneManager>    sceneManager()       const { return scm_; }
        std::shared_ptr<ResourceManager> resourceManager() const { return rm_; }
        std::shared_ptr<Renderer>        renderer()           const { return r_; }
        std::shared_ptr<Config>          config()          const { return c_; }

    private:
        std::shared_ptr<SoundManager>    sm_;
        std::shared_ptr<InputManager>    im_;
        std::shared_ptr<EventManager>    em_;
        std::shared_ptr<SceneManager>    scm_;
        std::shared_ptr<ResourceManager> rm_;
        std::shared_ptr<Renderer>        r_;
        std::shared_ptr<Config>          c_;
    };
    
}


#endif // JIMBO_SERVICELOCATOR_HPP
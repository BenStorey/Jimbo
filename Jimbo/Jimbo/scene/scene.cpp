/////////////////////////////////////////////////////////
// Scene.cpp
//
// Ben Storey
//
// Some functions I couldn't put in the header file as SceneManager.hpp already includes Scene.hpp
//
/////////////////////////////////////////////////////////

#include "scene/scene.hpp"
#include "scene/scenemanager.hpp"

#include "resource/resourceid.hpp"
#include "resource/resourcemanager.hpp"

#include "event/eventmanager.hpp"

void jimbo::Scene::endScene()
{
    serviceLocator_->sceneManager()->popScene();
}

void jimbo::Scene::pushScene(Scene * scene)
{
    serviceLocator_->sceneManager()->pushScene(scene);
}

void jimbo::Scene::pushScene(std::unique_ptr<Scene> scene)
{
    serviceLocator_->sceneManager()->pushScene(std::move(scene));
}

void jimbo::Scene::quitApplication()
{
    serviceLocator_->sceneManager()->quit();
}

void jimbo::Scene::loadResource(ResourceID id)
{
    serviceLocator_->resourceManager()->loadResource(id);
}

void jimbo::Scene::raiseEvent(EventBase * ev)
{
    serviceLocator_->eventManager()->raiseEvent(ev);
}

void jimbo::Scene::raiseEvent(std::unique_ptr<EventBase> ev)
{
    serviceLocator_->eventManager()->raiseEvent(std::move(ev));
}

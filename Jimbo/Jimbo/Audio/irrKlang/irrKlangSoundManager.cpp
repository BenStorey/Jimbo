/////////////////////////////////////////////////////////
// irrKlangSoundManager.cpp
//
// Ben Storey
//
// Implement the interface using irrKlang (which is not free for commercial use!)
//
/////////////////////////////////////////////////////////

#include "audio/irrklang/irrklangsoundmanager.h"
#include "audio/irrklang/irrklangsound.h"

bool jimbo::irrKlangSoundManager::initialise()
{
    engine_ = irrklang::createIrrKlangDevice();
    return engine_ != nullptr;
}

void jimbo::irrKlangSoundManager::shutdown()
{
    if (engine_)
        engine_->drop();
}

void jimbo::irrKlangSoundManager::stopAllSounds()
{
    if (engine_)
        engine_->stopAllSounds();
}

std::unique_ptr<jimbo::Sound> jimbo::irrKlangSoundManager::createSound()
{
    return std::unique_ptr<Sound>(new irrKlangSound(engine_));
}

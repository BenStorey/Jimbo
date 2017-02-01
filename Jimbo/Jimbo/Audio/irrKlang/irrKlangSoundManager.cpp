/////////////////////////////////////////////////////////
// irrKlangSoundManager.cpp
//
// Ben Storey
//
// Implement the interface using irrKlang (which is not free for commercial use!)
//
/////////////////////////////////////////////////////////

#include "audio/irrklang/irrklangsoundmanager.h"

#include "util/logging.h"
#include "audio/irrklang/irrklangsound.h"

bool Jimbo::irrKlangSoundManager::initialise()
{
    engine_ = irrklang::createIrrKlangDevice();
    return engine_ != nullptr;
}

void Jimbo::irrKlangSoundManager::shutdown()
{
    if (engine_)
        engine_->drop();
}

void Jimbo::irrKlangSoundManager::stopAllSounds()
{
    if (engine_)
        engine_->stopAllSounds();
}

std::unique_ptr<Jimbo::Sound> Jimbo::irrKlangSoundManager::createSound()
{
    return std::unique_ptr<Sound>(new irrKlangSound(engine_));
}

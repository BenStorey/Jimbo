
#ifndef JIMBO_TEST_TESTSCENE_HPP
#define JIMBO_TEST_TESTSCENE_HPP

///////////////////////////////////////////////////////////////////////////////////////
// TestScene.h
//
// Ben Storey
//
// A simpler Test class that runs a scene and ends
//
///////////////////////////////////////////////////////////////////////////////////////

#include "scene/scene.hpp"
#include "util/logging.hpp"
#include "audio/soundmanager.hpp"
#include "audio/sound.hpp"
#include "input/inputsettings.hpp"
#include "input/keymapping.hpp"

namespace jimbo
{
    class TestScene : public Scene
    {
    public:

        enum InputActions { QUIT = 1, SOUND = 2 };

        // Initialise and Shutdown allow the scene to load/unload files as necessary
        bool onInitialise(std::chrono::milliseconds) override 
        {
            // Play some music
            music_ = soundManager()->createSound();
            music_->loadFromFile("../Assets/SomeMusic.ogg");

            // And to play a sound later
            sound_ = soundManager()->createSound();
            sound_->loadFromFile("../Assets/Success.wav");

            return true;
        }

        void onShutdown() override 
        {
            music_->release();
            sound_->release();
        }

        void onUpdate(std::chrono::milliseconds) override 
        {
            if (!music_->isPlaying())
                music_->playLoop();
        }

        void onRender() override;

        void onSetupInputMaps(InputSettings& map) override
        {
            map.addKeyMapping(KeyMapping::KEY_ESCAPE, InputActions::QUIT);
            map.addKeyMapping(KeyMapping::KEY_Z, KeyModifier::ControlDown, InputActions::QUIT);
            map.addKeyMapping(KeyMapping::KEY_S, InputActions::SOUND);

            map.setRepeatInterval(InputActions::SOUND, std::chrono::milliseconds(1000));
        }

        void onKeyJustPressed(int action) override
        {
            if (action == InputActions::QUIT)
                quitApplication();

            if (action == InputActions::SOUND)
                sound_->play();
        }

        void onKeyJustReleased(int state) override {}
        void onKeyRepeat(int state) override {}

        void onWindowCloseEvent() override
        {
            quitApplication();
        }

        void onLoseFocus() override {}

    private:
        std::unique_ptr<Sound> music_;
        std::unique_ptr<Sound> sound_;
    };
}

#endif // JIMBO_TEST_TESTSCENE_HPP

#ifndef JIMBO_TEST_TESTSCENE_HXX
#define JIMBO_TEST_TESTSCENE_HXX

///////////////////////////////////////////////////////////////////////////////////////
// testscene.hxx
//
// Ben Storey
//
// A simpler Test class that runs a scene and ends. Included as part of testengine.hpp
//
///////////////////////////////////////////////////////////////////////////////////////


#include "jimbo.hpp"

namespace jimbo
{

    namespace test
    {

        class TestScene : public Scene
        {
        public:


            enum InputActions { QUIT = 1, SOUND = 2 };

            // Initialise and Shutdown allow the scene to load/unload files as necessary
            bool onInitialise(std::chrono::milliseconds) override
            {
                // Normally this will be done on startup and not defined in a scenes initialise function
                // but since this is a test scene and I want it self contained, we can do that anyway
                //registerResource(RID("music"), new ResourceFileLoader("../Assets/SomeMusic.ogg"));
                //registerResource(RID("sound"), new ResourceFileLoader("../Assets/Success.wav"));
                //registerResourceGroup(RID("testGroup"), { RID("music"), RID("sound") });

                // We would however normally request our resources to be loaded here (if not earlier!)

                loadResource(RID("testSound"));

                //loadResource(RID("sound"));
                //loadResources({ RID("music"), RID("sound") });
                //loadResourceGroup(RID("testGroup"));

                // For our music API we can setup our jukebox
                //jukebox()->setPlaylist({ RID("music") });
                //jukebox()->play();


                //loadResource(RID("music"));
                //loadResource(RID("sound"));

                // Play some music
                //music_ = soundManager()->createSound();
                //music_->loadFromFile("../Assets/SomeMusic.ogg");

                // And to play a sound later
                //sound_ = soundManager()->createSound();
                //sound_->loadFromFile("../Assets/Success.wav");

                return true;
            }

            void onShutdown() override
            {
                // These probably aren't required anymore, so can forget about them
                // We only hint because we don't really care if they are removed or not
                //hintReleaseResource(RID("testSound"));
                //hintReleaseResource(RID("sound"));
            }

            void onUpdate(std::chrono::milliseconds) override
            {
                //if (!jukebox()->isPlaying())
                //    jukebox()->play();
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
                {
                    // Will play if the resource is loaded, throw away otherwise
                    // we could keep the result if we wanted to change the volume etc

                    // createSound(RID("testSound"))->play();
                    // auto sound = createSound(RID("testSound"));
                }
            }

            void onKeyJustReleased(int state) override {}
            void onKeyRepeat(int state) override {}

            void onWindowCloseEvent() override
            {
                quitApplication();
            }

        };

    }
}

#endif // JIMBO_TEST_TESTSCENE_HXX

/////////////////////////////////////////////////////////
// config.cpp
//
// Ben Storey
//
// Code to parse our TOML file
//
/////////////////////////////////////////////////////////

#include <cpptoml/cpptoml.h>
#include <boost/algorithm/string.hpp>
#include "application/config.hpp"


void jimbo::Config::reload()
{
    if (path_.length() == 0) throw std::invalid_argument("Config has no filename defined to reload");

    auto config = cpptoml::parse_file(path_);

    //////////////////////////////////////////////////////////////////////
    // Values to determine properties about how the window is displayed //
    //////////////////////////////////////////////////////////////////////

    auto display = config->get_table("display");

    if (display)
    {
        // Use value_or as it saves checking for null
        setWindowName(display->get_as<std::string>("title").value_or(windowName_));
        setFullScreen(display->get_as<bool>("fullscreen").value_or(fullScreen_));

        auto frameRate = display->get_as<int>("capframerate");
        if (frameRate) setFrameRateCap(*frameRate);
        
        // Frustratingly, this fails with int but it's happy with int64_t. 
        // So for now I just take int64_t and cast it down to a regular int (which is plenty big enough..)
        auto windowSize = display->get_array_of<int64_t>("windowsize");
        if (windowSize)
        {
            if (windowSize->size() != 2)
                throw std::invalid_argument("Incorrect number of parameters for windowsize. Expected [ x, y ] ");

            setWindowSize(static_cast<int>(windowSize->at(0)), static_cast<int>(windowSize->at(1)));
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Values to determine which implementations we use internally for audio or graphics etc //
    ///////////////////////////////////////////////////////////////////////////////////////////

    auto implementation = config->get_table("implementation");

    if (implementation)
    {
        auto audio = implementation->get_as<std::string>("audio");
        if (audio)
        {
            if (boost::iequals(*audio, "irrklang")) audioEngine_ = AudioEngine::IRRKLANG;
            if (boost::iequals(*audio, "silent")) audioEngine_ = AudioEngine::SILENT;
        }
    }

    ///////////////////////////////////////////////////
    // Values to determine how we handle game assets //
    ///////////////////////////////////////////////////

    auto resource = config->get_table("resource");

    if (resource)
    {
        setResourceThreadPoolSize(display->get_as<int>("threadpoolsize").value_or(resourceThreadPoolSize_));
    }

    // Decide later how to handle our resource loads here //
}
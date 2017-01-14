/////////////////////////////////////////////////////////
// SoundManager.cpp
//
// Ben Storey
//
/////////////////////////////////////////////////////////

#include "OpenALSoundManager.h"
#include "../../Core/Logging.h"

// This is a handy macro for checking alError on every AL call. Borrowed from the helpful people
// at gamedev.net - https://www.gamedev.net/resources/_/technical/game-programming/basic-openal-sound-manager-for-your-project-r3791

#ifndef AL_CHECK
#ifdef _DEBUG
#define AL_CHECK(stmt) do { \
            stmt; \
            checkOpenALError(#stmt, __FILE__, __LINE__); \
        } while (0);
#else
#define AL_CHECK(stmt) stmt
#endif
#endif

/* Define the number of buffers and buffer size (in milliseconds) to use. 4
* buffers with 200ms each gives a nice per-chunk size, and lets the queue last
* for almost one second. */
#define NUM_BUFFERS 4
#define BUFFER_TIME_MS 200

typedef struct StreamPlayer {
	/* These are the buffers and source to play out through OpenAL with */
	ALuint buffers[NUM_BUFFERS];
	ALuint source;

	/* Handle for the audio file */
	//FilePtr file;

	/* The format of the output stream */
	ALenum format;
	ALenum channels;
	ALenum type;
	ALuint rate;
} StreamPlayer;

bool Jimbo::OpenALSoundManager::initialise()
{
	ALCdevice* device = alcOpenDevice(nullptr);
	
	if (!device)
	{
		LOG("Failed to initialize OpenAL sound manager!\n");
		return false;
	}

	// Check if we can enumerate the available devices. If we can then also print the device details to our log
	ALboolean enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_TRUE)
	{
		debugPrintAudioDevices(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));
	}

	ALCcontext *context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context))
	{
		LOG("Failed to set AL device context");
		return false;
	}

	// Generate sources. For now this is just for sounds, and we don't care about positions yet. Once we move
	// into 3D we'll want sounds to properly take into account the position of the listener as well
	// as the location of sounds. For now, we don't need to worry about that. 
	AL_CHECK(alGenSources((ALuint)1, &source_));
	AL_CHECK(alSourcef(source_, AL_PITCH, 1));
	AL_CHECK(alSourcef(source_, AL_GAIN, 1));
	AL_CHECK(alSource3f(source_, AL_POSITION, 0, 0, 0));
	AL_CHECK(alSource3f(source_, AL_VELOCITY, 0, 0, 0));
	AL_CHECK(alSourcei(source_, AL_LOOPING, AL_FALSE));

	AL_CHECK(alGenBuffers((ALuint)1, &buffer_));

	StreamPlayer *player = new StreamPlayer();
	
	/* Generate the buffers and source */
	alGenBuffers(NUM_BUFFERS, player->buffers);

	// Return success, we are all good!
	return true;
}


void Jimbo::OpenALSoundManager::debugPrintAudioDevices(const ALCchar* devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	std::string deviceList = "Audio Devices Enumerated:\n-------------------------\n";

	while (device && *device != '\0' && next && *next != '\0') 
	{
		deviceList.append(std::string(device));
		deviceList.append("\n");
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}

	deviceList.append("------------------------- ");
	LOG(deviceList);
}

const std::string Jimbo::OpenALSoundManager::getOpenALErrorString(int errID)
{
	if (errID == AL_NO_ERROR) return "";
	if (errID == AL_INVALID_NAME) return "Invalid name";
	if (errID == AL_INVALID_ENUM) return "Invalid enum";
	if (errID == AL_INVALID_VALUE) return "Invalid value";
	if (errID == AL_INVALID_OPERATION) return "Invalid operation";
	if (errID == AL_OUT_OF_MEMORY) return "Out of memory";

	return "Unknown Error";
}

inline void Jimbo::OpenALSoundManager::checkOpenALError(const char * statement, const char * filename, int line)
{
	auto err = alGetError();
	if (err != AL_NO_ERROR)
	{
		Log::d(std::string(statement), filename, line);
	}
}

void Jimbo::OpenALSoundManager::playSound(Sound&)
{

}

void Jimbo::OpenALSoundManager::playMusic(Music&)
{

}
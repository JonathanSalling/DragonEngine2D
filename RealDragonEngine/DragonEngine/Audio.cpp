#include "Audio.h"
#include <SDL3_mixer/SDL_mixer.h>
#include "Engine.h"
#include "TemplateUtilities.h"

DragonEngine::Audio::Audio(const std::string& aPath)
{
	myAudio = MIX_LoadAudio(Engine::GetInstance().GetMixer(), aPath.c_str(), false);
	if (!myAudio)
	{
		SDL_Log("Couldn't load %s: %s", aPath.c_str(), SDL_GetError());
		assert(false && "Audio failed to load");
		return;
	}

	myTrack = MIX_CreateTrack(Engine::GetInstance().GetMixer());
	if (!myTrack)
	{
		SDL_Log("Couldn't create track for: %s %s", aPath.c_str(), SDL_GetError());
		return;
	}
}

DragonEngine::Audio::~Audio()
{
	if (myAudio)
	{
		MIX_DestroyAudio(myAudio);
		myAudio = nullptr;
	}
	if (myTrack)
	{
		MIX_DestroyTrack(myTrack);
		myTrack = nullptr;
	}
}

void DragonEngine::Audio::Play(const bool aShouldReset)
{
	if (!HasTrack())
	{
		return;
	}

	if (aShouldReset)
	{
		Stop(0); // prevent overlapping duplicates
	}

	MIX_SetTrackAudio(myTrack, myAudio);
	MIX_PlayTrack(myTrack, 0);
}

void DragonEngine::Audio::PlayOneshot()
{
	if (!HasAudio())
	{
		return;
	}
	MIX_PlayAudio(Engine::GetInstance().GetMixer(), myAudio);
}

void DragonEngine::Audio::Stop(int aFadeOutSeconds)
{
	if (!HasTrack())
	{
		return;
	}
	MIX_StopTrack(myTrack, MIX_TrackMSToFrames(myTrack, aFadeOutSeconds * 1000));
}

void DragonEngine::Audio::Pause()
{
	if (!HasTrack())
	{
		return;
	}
	MIX_PauseTrack(myTrack);
}

void DragonEngine::Audio::Resume()
{
	if (!HasTrack())
	{
		return;
	}
	MIX_ResumeTrack(myTrack);
}

void DragonEngine::Audio::SetVolume(const float aVolume)
{
	if (!HasTrack())
	{
		return;
	}
	MIX_SetTrackGain(myTrack, DragonEngine::Clamp(0.f, FLT_MAX, aVolume));
}

void DragonEngine::Audio::SetLoops(int aNumLoops) const
{
	if (!HasTrack())
	{
		return;
	}
	MIX_SetTrackLoops(myTrack, aNumLoops);
}

bool DragonEngine::Audio::IsPlaying() const
{
	if (!HasTrack())
	{
		return false;
	}
	return MIX_GetTrackRemaining(myTrack);
}

bool DragonEngine::Audio::IsPaused() const
{
	if (!HasTrack())
	{
		return false;
	}
	return MIX_TrackPaused(myTrack);
}

bool DragonEngine::Audio::HasAudio() const
{
	return myAudio != nullptr;
}

bool DragonEngine::Audio::HasTrack() const
{
	return myTrack != nullptr;
}

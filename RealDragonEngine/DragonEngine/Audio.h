#pragma once
#include <string>

struct MIX_Audio;
struct MIX_Track;

namespace DragonEngine
{
	class Audio
	{
	public:
		Audio(const std::string& aPath);
		~Audio();

		void Play(const bool aShouldReset = true);
		void PlayOneshot();
		void Stop(int aFadeOutSeconds);
		void Pause();
		void Resume();
		void SetVolume(const float aVolume);
		void SetLoops(int aNumLoops) const;

		bool IsPlaying() const;
		bool IsPaused() const;
		bool HasAudio() const;
		bool HasTrack() const;

	private:
		MIX_Audio* myAudio = nullptr;
		MIX_Track* myTrack = nullptr;
	};
}

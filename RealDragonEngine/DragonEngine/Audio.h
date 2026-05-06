#pragma once
#include <string>

struct MIX_Audio;
struct MIX_Track;

namespace DragonEngine
{
	// The Audio class represents a sound or music track that can be played, paused, stopped, and have its volume and looping behavior controlled.
	class Audio
	{
	public:
		// Create and load audio from the specified path
		// Can be used for both music and sound effects, but is primarily intended for music. 
		// For sound effects, consider using PlayOneshot instead of Play.
		Audio(const std::string& aPath);
		~Audio();

		// Deleted copy and move constructors and assignment operators to prevent copying or moving the sprite,
		// which would cause issues with the owned MIX_Audio and MIX_Track
		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;
		Audio(Audio&&) = delete;
		Audio& operator=(Audio&&) = delete;

		// Play the audio. If aShouldReset is true, the audio will be stopped and restarted if it's already playing.
		void Play(const bool aShouldReset = true);

		// Play the audio once without affecting the track. This is useful for sound effects.
		void PlayOneshot();

		// Stop the audio with an optional fade-out duration in seconds. If aFadeOutSeconds is 0, the audio will stop immediately.
		void Stop(int aFadeOutSeconds = 0);
		// Pause the audio if it's currently playing.
		void Pause();
		// Resume the audio if it's currently paused.
		void Resume();
		// Set the volume of the audio. The volume should be a value between 0.0 (silent) and 1.0 (full volume)
		// Can go beyond 1.0 for amplification.
		void SetVolume(const float aVolume);

		// Set the number of times the audio should loop. A value of -1 will loop indefinitely, 0 will play once, and positive values will loop that many times.
		void SetLoops(int aNumLoops) const;

		// Check if the audio is currently playing.
		bool IsPlaying() const;
		// Check if the audio is currently paused.
		bool IsPaused() const;
		// Check if the audio has been loaded successfully.
		bool HasAudio() const;
		// Check if the track has been created successfully.
		bool HasTrack() const;

	private:
		MIX_Audio* myAudio = nullptr;
		MIX_Track* myTrack = nullptr;
	};
}

//
// Created by amin on 1/3/19.
//

#include "effects.h"
#include "structs.h"


void audioCallback(void* userData, Uint8* stream, int streamLength) {
    AudioData* audio = (AudioData*)userData;

    if (audio->length == 0)
    {
        return;
    }

    Uint32 length = (Uint32)streamLength;

    length = (length > audio->length ? audio->length : length);

    SDL_memcpy(stream, audio->position, length);

    audio->position += length;
    audio->length -= length;
}

void play_sound_effect() {
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    char* filePath = "/home/amin/Desktop/project/sound effects/Explosion+1.wav";

    if(SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        printf("Error: file could not be loaded as an audio file.\n") ;
    }

    AudioData audio;
    audio.position = wavStart;
    audio.length = wavLength;

    wavSpec.callback = audioCallback;
    wavSpec.userdata = &audio;

    SDL_AudioDeviceID audioDevice;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (audioDevice == 0)
    {
        printf("Error: %d\n" , SDL_GetError() );
        return;
    }

    SDL_PauseAudioDevice(audioDevice, 0);

    while (audio.length > 0)
    {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavStart);

}
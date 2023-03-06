#include "AudioVisualizer.h"


// constructor populates the fftSmooth vector with 0s
AudioVisualizer::AudioVisualizer() {
    bands = 64;
    for (int i = 0; i < 8192; i++){
        fftSmooth.push_back(0);
    }
}

// Setters
void AudioVisualizer::setBands(int bandsUpdate) {
    bands = bandsUpdate;
}

// Getters
int AudioVisualizer::getBands() {
    return bands;
}

// Returns a vector of amplitudes based on the sound being played
vector<float> AudioVisualizer::getAmplitudes() {
    vector<float> amplitudes;

    for(int i = 0; i < bands; i++) {
        amplitudes.push_back(fftSmooth[i] * -300);
    }

    return amplitudes;
}

// Updates the amplitudes vector
void AudioVisualizer::updateAmplitudes() {
    ofSoundUpdate();
    float * value = ofSoundGetSpectrum(bands);
    for (int i = 0; i < bands; i++){
        fftSmooth[i] *= 0.9f;
        if (fftSmooth[i] < value[i]){
            fftSmooth[i] = value[i];
        }
    }
}

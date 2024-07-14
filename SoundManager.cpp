#include "SoundManager.h"

SoundManager* SoundManager::_currentInstance = nullptr;

SoundManager::SoundManager() : _currentMusic(), _musicOn(true)
{
    // Constructor implementation
}

SoundManager& SoundManager::getInstance()
{
    if (SoundManager::_currentInstance == nullptr) {
        SoundManager::_currentInstance = new SoundManager();
    }
    return *SoundManager::_currentInstance;
}

void SoundManager::loadMusic(const std::string& route)
{
    if (_currentMusic.getStatus() != sf::Music::Stopped)
    {
        return;
    }
    if (!_currentMusic.openFromFile(route))
    {
        throw std::runtime_error("Error loading music: " + route);
    }
    _currentMusic.setVolume(50.0f); // Default volume
    _currentMusic.setLoop(true); // Set loop if required
}

void SoundManager::playMusic()
{
    if (_currentMusic.getStatus() != sf::Music::Playing)
    {
        _currentMusic.play();
    }
}

void SoundManager::stopMusic()
{
    _currentMusic.stop();
}

void SoundManager::pauseMusic()
{
    _currentMusic.pause();
}

void SoundManager::setVolume(float volume)
{
    _currentMusic.setVolume(volume);
}

void SoundManager::setMusicOn(bool state)
{
    _musicOn = state;
}

bool SoundManager::getMusicOn()
{
    return _musicOn;
}



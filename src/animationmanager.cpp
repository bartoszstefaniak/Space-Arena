// Bartosz Stefaniak

#include "animationmanager.hpp"
#include "camera.hpp"

void AnimationManager::update()
{   
    animations.erase(
        std::remove_if(
            std::begin(animations),
            std::end(animations),
            [](const std::unique_ptr<Animation>& ptr){
                return ptr->done();
            }
        ),
        std::end(animations));

    for(const auto& ptr : animations)
    {
        ptr->update();
    }
}

void AnimationManager::add_animation(std::string path, sf::Vector2f center, int frames)
{
    animations.push_back(std::make_unique<Animation>(path, center, frames));
}

void AnimationManager::draw()
{
    for(const auto& ptr : animations)
    {
        Camera::get_window().draw(*ptr);
    }
}

void AnimationManager::clear()
{
    animations.clear();
}
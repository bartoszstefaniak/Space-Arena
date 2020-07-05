// Bartosz Stefaniak

#include "animation.hpp"
#include "resourcemanager.hpp"
#include "defines.hpp"

Animation::Animation(std::string path, sf::Vector2f center, int frames)
    : base_anim_path{path}, frames{frames}
{
    setTexture(ResourceManager::get_texture(base_anim_path + "0.png", true));
    setScale(X_SCALE, Y_SCALE);
    setOrigin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
    setPosition(center);
}

void Animation::update()
{
    if(skipped_frames >= ANIMATION_FRAME_SKIP)
    {
        skipped_frames = 0;
        current_frame++;

        if(current_frame >= frames)
        {
            done_ = true;
            return ;    
        }

        auto center = getPosition();

        setTexture(ResourceManager::get_texture(base_anim_path + std::to_string(current_frame) + ".png", true));
        setScale(X_SCALE, Y_SCALE);
        setOrigin(getGlobalBounds().width / 2.0f, getGlobalBounds().height / 2.0f);
        setPosition(center);
    }
    else
    {
        ++skipped_frames;
    }
}
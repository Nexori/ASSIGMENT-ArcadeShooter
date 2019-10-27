#include "Animation.h"
Animation::Animation() {
	textureAtlas.loadFromFile("textures.png"); 
};
void Animation::update(double time, Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets)
{
}

void Animation::addFrame(Frame& frame)
{
}

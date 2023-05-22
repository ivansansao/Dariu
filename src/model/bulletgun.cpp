#include "bulletgun.hpp"

BulletGun::BulletGun() {
    bulletGun.init(2, 0.5f, "./src/asset/image/bulletgun.png", sf::IntRect(0, 0, 10, 5), true);
}
void BulletGun::draw(sf::RenderWindow *w) {
    bulletGun.draw(pos.left, pos.top, w);
    // bulletGun.anime(sf::IntRect(bulletGun.getFrame() * 10, 0, 10, 5), bulletGun.direction_x);
    bulletGun.anime(sf::IntRect(Tools::getStartSprite(bulletGun.getFrame(), bulletGun.direction_x) * 10, 0, bulletGun.direction_x * 10, 5), bulletGun.direction_x);

    // sf::RectangleShape rectangle;
    // rectangle.setSize(sf::Vector2f(1, 1));
    // rectangle.setOutlineColor(sf::Color::Red);
    // rectangle.setPosition(this->pos.left, this->pos.top);
    // w->draw(rectangle);
}
void BulletGun::update(Tilemap *tilemap, Sounds *sounds) {
    if (!this->collided) {
        // const int offset = 16 * direction_x;
        const float sprite_w = this->bulletGun.sprite.getGlobalBounds().width;
        const float sprite_h = this->bulletGun.sprite.getGlobalBounds().height;
        const int i = (this->pos.top) / 32;
        const int j = (this->pos.left) / 32;
        const int i2 = (this->pos.top + sprite_h - 1) / 32;
        const int j2 = (this->pos.left + sprite_w - 1) / 32;

        // std::cout << j << " bl: " << this->pos.left << " tile1: " << tilemap->map[i][j] << " tile2: " << tilemap->map[i][j2] << " tile3: " << tilemap->map[i2][j] << " sprite_w: " << sprite_w << "\n";
        if (tilemap->free_path_bullet(i, j) && tilemap->free_path_bullet(i, j2) && tilemap->free_path_bullet(i2, j) && tilemap->free_path_bullet(i2, j2)) {
            this->pos.left += 10 * this->bulletGun.direction_x;
        } else {
            this->collided = true;
        }
    }
}
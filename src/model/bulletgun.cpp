#include "bulletgun.hpp"

BulletGun::BulletGun() {
    bulletGun.init(2, 0.5f, "./src/asset/image/bulletgun.png", sf::IntRect(0, 0, 10, 5), true, 0, 0, false);
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
        const float sprite_w = this->bulletGun.sprite.getGlobalBounds().width;
        const float sprite_h = this->bulletGun.sprite.getGlobalBounds().height;

        const int topm = this->pos.top + (sprite_h * 0.5);
        const int leftm = this->pos.left + (sprite_w * 0.5);

        const int i = (this->pos.top) / 32;
        const int j = (this->pos.left) / 32;
        const int i2 = (this->pos.top + sprite_h - 1) / 32;
        const int j2 = (this->pos.left + sprite_w - 1) / 32;
        const int im = topm / 32;
        const int jm = leftm / 32;

        if (onPortal) {
            if (!tilemap->isPortal(im, jm)) {
                onPortal = false;
            }
        } else {
            if (tilemap->isPortal(im, jm)) {
                onPortal = true;
                const auto point = tilemap->getMapOppositPortal(im, jm);

                if (point.found) {
                    this->bulletGun.direction_x = -this->bulletGun.direction_x;
                    this->pos.top = (point.i * 32) + (topm % 32);
                    this->pos.left = (point.j * 32) + (leftm % 32 * this->bulletGun.direction_x);
                }
            }
        }

        if (tilemap->free_path_bullet(i, j) && tilemap->free_path_bullet(i, j2) && tilemap->free_path_bullet(i2, j) && tilemap->free_path_bullet(i2, j2)) {
            this->pos.left += 10 * this->bulletGun.direction_x;
        } else {
            this->collided = true;
        }
    }
}
#ifndef COOKIE_H
#define COOKIE_H

#include "component.h"
#include <vector>
#include <string>

class Cookie : public Component {
    int points;
    bool powerUp;
public:
    Cookie(int xPos, int yPos, int pts = 10, bool isPowerUp = false);

    std::string getType() const override;
    int getPoints() const;
    bool isPowerUpCookie() const;

    static std::vector<Cookie> generateRandomCookies(
        int level, int width, int height,
        int baseCookies = 20, int cookiesPerLevel = 10,
        int basePowerUps = 2);
};


#endif


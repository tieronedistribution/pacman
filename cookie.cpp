#include "cookie.h"
#include <random>

Cookie::Cookie(int xPos, int yPos, int pts, bool isPowerUp)
    : Component(xPos, yPos, false), points(pts), powerUp(isPowerUp) {}

std::string Cookie::getType() const {
    return powerUp ? "PowerUpCookie" : "Cookie";
}

int Cookie::getPoints() const { return points; }

bool Cookie::isPowerUpCookie() const { return Cookie::powerUp; }

std::vector<Cookie> Cookie::generateRandomCookies(
    int level, int width, int height,
    int baseCookies, int cookiesPerLevel,
    int basePowerUps)
{
    std::vector<Cookie> cookies;

    int cookieCount = baseCookies + level * cookiesPerLevel;
    int powerUpCount = basePowerUps + level;

    std::mt19937 rng(level * 54321);
    std::uniform_int_distribution<int> distX(1, width - 2);
    std::uniform_int_distribution<int> distY(1, height - 2);

    for (int i = 0; i < cookieCount; i++)
    {
        int x = distX(rng);
        int y = distY(rng);
        cookies.emplace_back(x, y, 10, false);
    }
    
    for (int i = 0; i < powerUpCount; i++)
    {
        int x = distX(rng);
        int y = distY(rng);
        cookies.emplace_back(x,y, 50, true);
    }
    return cookies; 
}


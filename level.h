#ifndef LEVEL_H
#define LEVEL_H

#include<string>

enum level{
    // three level in total
    EASY = 1,
    MODERATE = 2,
    HARD = 3,
};

class LevelSelector{
    private:

    public:
        static std::string level_to_string(level level_value);
        static level select_level();
};
#endif

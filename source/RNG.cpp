#include "rng.h"
#include "vec.h"

float aether::math::lerp(float a, float b, float t)
{
    return (1 - t) * a + t * b;
}


int aether::math::randi(int min, int max)
{
    return min + randi(max - min);
}

int aether::math::randi(int max)
{
    return std::rand() % max;
}

size_t aether::math::split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

#ifndef ENGINE_LIVERENDER_H
#define ENGINE_LIVERENDER_H

#include "string"
#include "../Include/easy_image.h"

class LiveRender {
public:
    static void renderIni(const std::string &inifile);
    static void render(const img::EasyImage& image);
};


#endif //ENGINE_LIVERENDER_H

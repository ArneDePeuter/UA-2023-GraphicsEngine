#include "Include/easy_image.h"
#include "Include/ini_configuration.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <climits>
#include <cmath>
#include "Objects/LSystem2D.h"
#include "Objects/Wireframe.h"
#include "Objects/Line2D.h"

#define max(x,y) (x>y ? x : y)
#define min(x,y) (x<y ? x : y)

img::EasyImage draw2DLines(const img::Color &backgroundcolor, std::list<Line2D> lines, int size) {
    //1. Determine xmin, xmax, ymin, ymax
    double xMin = INT_MAX, xMax = INT_MIN, yMin = INT_MAX, yMax = INT_MIN;
    for (const Line2D& l : lines) {
        double lMinX = min(l.p1.x, l.p2.x), lMaxX = max(l.p1.x, l.p2.x);
        double lMinY = min(l.p1.y, l.p2.y), lMaxY = max(l.p1.y, l.p2.y);
        xMin = min(xMin, lMinX);
        xMax = max(xMax, lMaxX);
        yMin = min(yMin, lMinY);
        yMax = max(yMax, lMaxY);
    }
    double xRange = xMax - xMin, yRange = yMax - yMin;

    //2. Calculate size of image
    double imageX = size * (xRange / max(xRange, yRange));
    double imageY = size * (yRange / max(xRange, yRange));
    img::EasyImage image(lround(imageX), lround(imageY), backgroundcolor);

    //3. Scale
    double d = 0.95 * (imageX / xRange);
    for (Line2D &l : lines) {
        l.p1.x *= d;
        l.p1.y *= d;
        l.p2.x *= d;
        l.p2.y *= d;
    }

    //4 and 5. Move
    Point2D DC(d * ((xMin+xMax)/2), d * ((yMin+yMax)/2));
    double dx = imageX / 2 - DC.x, dy = imageY / 2 - DC.y;
    for (Line2D &l : lines) {
        l.p1.x = lround(l.p1.x + dx);
        l.p1.y = lround(l.p1.y + dy);
        l.p2.x = lround(l.p2.x + dx);
        l.p2.y = lround(l.p2.y + dy);
    }

    //6. draw
    for (const Line2D& l : lines) {
        l.draw(&image);
    }
    return image;
}

// const removed for pass reference
img::EasyImage generate_image(ini::Configuration &configuration)
{
    Lines2D lines;
    img::Color backgroundcolor;
    int size;

    std::string type = configuration["General"]["type"].as_string_or_die();
    if (type == "2DLSystem") {
        LSystem2D lSys(configuration);
        lines = lSys.lines;
        backgroundcolor = lSys.backgroundcolor;
        size = lSys.size;
    } else if (type == "Wireframe") {
        Wireframe wf(configuration);
        lines = wf.project(1);
        backgroundcolor = wf.backgroundColor;
        size = wf.size;
    } else {
        return img::EasyImage(0,0, img::Color(0,0,0));
    }
    return draw2DLines(backgroundcolor, lines, size);
}

int main(int argc, char const* argv[])
{
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                if (fin.peek() == std::istream::traits_type::eof()) {
                                    std::cout << "Ini file appears empty. Does '" <<
                                    fileName << "' exist?" << std::endl;
                                    continue;
                                }
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
    		//When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
    		//Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
    		//(Unless of course you are already consuming the maximum allowed amount of memory)
    		//If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
		    //mark the test as failed while in reality it just needed a bit more memory
                std::cerr << "Error: insufficient memory" << std::endl;
                retVal = 100;
        }
        return retVal;
}

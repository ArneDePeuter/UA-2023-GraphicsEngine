#include "LiveRender.h"
#include "../Objects/IniLoader.h"
#include "fstream"
#include <opencv2/opencv.hpp>

void LiveRender::renderIni(const std::string &inifile) {
    std::ifstream fin(inifile);
    if (fin.peek() == std::istream::traits_type::eof()) {
        std::cout << "Ini file appears empty. Does '" << inifile << "' exist?" << std::endl;
        exit(3);
    }
    ini::Configuration conf;
    fin >> conf;
    fin.close();
    render(IniLoader::createImage(conf));
}

void LiveRender::render(const img::EasyImage &image) {
    cv::Mat mat(image.get_height(), image.get_width(), CV_8UC3);

    for (unsigned int y = 0; y < image.get_height(); ++y) {
        for (unsigned int x = 0; x < image.get_width(); ++x) {
            const img::Color& color = image(x, y);
            cv::Vec3b& pixel = mat.at<cv::Vec3b>(y, x);
            pixel[2] = color.red;
            pixel[1] = color.green;
            pixel[0] = color.blue;
        }
    }

    cv::imshow("Image", mat);
    cv::waitKey(0);
}

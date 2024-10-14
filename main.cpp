#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h" 

void average_colors(std::vector<Pixel> &pixel_list) {
    float total_r = 0.0f;
    float total_g = 0.0f;
    float total_b = 0.0f;

    for (const Pixel& pixel : pixel_list) {
        total_r += pixel.r;
        total_g += pixel.g;
        total_b += pixel.b;
    }

    int num_pixels = pixel_list.size();
    float avg_r = total_r / num_pixels;
    float avg_g = total_g / num_pixels;
    float avg_b = total_b / num_pixels;

    std::cout << "Average R: " << avg_r << std::endl;
    std::cout << "Average G: " << avg_g << std::endl;
    std::cout << "Average B: " << avg_b << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list) {
    int num_pixels = pixel_list.size();
    int y_length = 256; // y-dimension is 256

    for (int i = 0; i < num_pixels / 2; i++) {
        // Swap the y coordinates of pixels at symmetrical positions
        int y1 = pixel_list[i].y;
        int y2 = y_length - y1 - 1;

        std::swap(pixel_list[i].y, pixel_list[num_pixels - i - 1].y);
    }
}

int main(int argc, char* argv[]) {
    std::vector<Pixel> pixel_list;

  
    std::string filename = "pixels.dat"; // Default filename

    if (argc > 1) { 
        filename = argv[1]; // Use filename from command line argument
    }

    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1; 
    }

    std::string line;
    while (std::getline(input_file, line)) {
        std::size_t pos = 0;
        int x, y;
        float r, g, b;

        // Extract x, y, r, g, b values from the line
        pos = line.find(',');
        x = std::stoi(line.substr(0, pos)); 
        line = line.substr(pos + 1);

        pos = line.find(',');
        y = std::stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        pos = line.find(',');
        r = std::stof(line.substr(0, pos));
        line = line.substr(pos + 1);

        pos = line.find(',');
        g = std::stof(line.substr(0, pos));
        line = line.substr(pos + 1);

        b = std::stof(line);

        // Create a Pixel object and store it in the vector
        Pixel pixel = {r, g, b, x, y};
        pixel_list.push_back(pixel); 
    }

    input_file.close();
    average_colors(pixel_list);
    flip_vertically(pixel_list);

    std::ofstream output_file("flipped.dat");
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open output file flipped.dat" << std::endl;
        return 1;
    }

    for (const Pixel& pixel : pixel_list) {
        output_file << pixel.x << "," << pixel.y << "," 
                   << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
    }

    output_file.close();

    return 0; 
}

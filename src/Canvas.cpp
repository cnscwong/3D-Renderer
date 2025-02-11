#include "Canvas.h"

// Canvas constructors
Canvas::Canvas(){
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    pixels = std::vector<std::vector<Colour>>(height, std::vector<Colour> (width, Colour()));
}

Canvas::Canvas(int w, int h){
    if(w < 1){
        width = DEFAULT_WIDTH;
    }else{
        width = w;
    }

    if(h < 1){
        height = DEFAULT_HEIGHT;
    }else{
        height = h;
    }

    pixels = std::vector<std::vector<Colour>>(height, std::vector<Colour> (width, Colour()));
}

// Getters for width and height
int Canvas::getWidth(){
    return width;
}

int Canvas::getHeight(){
    return height;
}

// Returns the colour of pixel at position [x][y]
Colour Canvas::pixelColour(int x, int y){
    return pixels.at(y).at(x);
}

// Updates the pixel colour at position [x][y]
void Canvas::write_pixel(int x, int y, Colour c){
    if(x >= 0 && x < width && y >= 0 && y < height){
        pixels[y][x] = c;
    }
}

// Sets all pixels to specified colour c
void Canvas::setAllPixels(Colour c){
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            pixels[y][x] = c;
        }
    }
}

// Converts canvas to ppm file
std::string Canvas::toPPM(){
    std::string file = "";

    // PPM identifier
    file += "P3\n";

    // width height
    file += std::to_string(width) + " " + std::to_string(height) + "\n";

    // maximum colour value
    file += "255\n";

    // Variables to help with limiting line length to 70 or less
    Colour currPixel;
    int currInt;
    int currChars;

    for(int y = 0; y < height; y++){
        currChars = 0;
        for(int x = 0; x < width; x++){
            // Getting the current pixel
            currPixel = this->pixelColour(x, y);

            // Getting the r value for the pixel
            currInt = ceil(std::min(currPixel.r, 1.0f)*255);
            if(currInt < 0){
                currInt = 0;
            }

            // Checks if adding the current int to the string will character limit for current line
            if(currChars + 1 + countDigits(currInt) > 70){
                file += "\n" + std::to_string(currInt);
                currChars = countDigits(currInt);
            }else if(currChars == 0){
                file += std::to_string(currInt);
                currChars += countDigits(currInt);
            }else{
                file += " " + std::to_string(currInt);
                currChars += 1 + countDigits(currInt);
            }

            // Getting the g value for the pixel
            currInt = ceil(std::min(currPixel.g, 1.0f)*255);
            if(currInt < 0){
                currInt = 0;
            }

            // Checks if adding the current int to the string will character limit for current line
            if(currChars + 1 + countDigits(currInt) > 70){
                file += "\n" + std::to_string(currInt);
                currChars = countDigits(currInt);
            }else{
                file += " " + std::to_string(currInt);
                currChars += 1 + countDigits(currInt);
            }

            // Getting the b value for the pixel
            currInt = ceil(std::min(currPixel.b, 1.0f)*255);
            if(currInt < 0){
                currInt = 0;
            }

            // Checks if adding the current int to the string will character limit for current line
            if(currChars + 1 + countDigits(currInt) > 70){
                file += "\n" + std::to_string(currInt);
                currChars = countDigits(currInt);
            }else{
                file += " " + std::to_string(currInt);
                currChars += 1 + countDigits(currInt);
            }
        }
        file += "\n";
    }

    return file;
}

void Canvas::writeToFile(std::string file_name){
    std::ofstream f(file_name);
    std::string ppm_string = this->toPPM();
    // Write to the file
    f << ppm_string;
    f.close();
}
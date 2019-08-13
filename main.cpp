#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

inline float gaussian_bell_curve(float t)
{
    float lowerCasePhi = 1 / std::sqrt(2 * M_PI) * std::exp(-0.5 * t * t);

    return lowerCasePhi;
}

inline float normal_distribution(float z)
{
    float upperCasePhi = 0.0f;
    
    for (float t = -50.0f; t < z; t += 0.001f)
    {
        upperCasePhi += gaussian_bell_curve(t) * 0.001f;

        if (std::abs(upperCasePhi - 1.0f) < 0.0001f)
        {
            upperCasePhi = 1.0f;
            break;
        }
    }

    return upperCasePhi;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "No upper bound given. Usage: nd <z>, z: Upper bound of the integral." << std::endl;
        return EXIT_FAILURE;
    }

    float z = 0.0f;
    try {
        z = std::stof(argv[1]);
    } catch(std::invalid_argument &e) {
        std::cout << "Invalid upper bound. Usage: nd <z>, z: Upper bound of the integral." << std::endl;
        return EXIT_FAILURE;
    } catch(std::out_of_range &e) {
        std::cout << "Upper bound too high. Usage: nd <z>, z: Upper bound of the integral." << std::endl;
        return EXIT_FAILURE;
    }
    
    float result = normal_distribution(z);
    std::cout << "Phi(" << std::fixed 
        << std::setprecision(2) << z << ")~" 
        << std::setprecision(4) << result << std::endl;

    /*
    // Computes the table from the book Mathematik Oberstufe MA-4 (Cornelsen, ISBN: 978-3-06-040014-0, page 165).
    for (float z = 0.0f; z <= 3.49f; z += 0.01f)
    {
        float result = normal_distribution(z);
        std::cout << "Phi(" << std::fixed 
            << std::setprecision(2) << z << ")~" 
            << std::setprecision(4) << result << std::endl;
    }
    */

    return EXIT_SUCCESS;
}

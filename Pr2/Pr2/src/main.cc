#include <iostream>
#include <fstream>
#include <string>
#include "../lib/bigRational.h"

void processFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream file(inputFilename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << inputFilename << "\n";
        return;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << outputFilename << "\n";
        return;
    }

    std::string line;
    unsigned char base = 10;
    std::string N1_str, N2_str;

    while (std::getline(file, line)) {
        if (line.find("Base = ") == 0) {
            base = std::stoi(line.substr(7));
        } else if (line.find("N1 = ") == 0) {
            N1_str = line.substr(5);
        } else if (line.find("N2 = ") == 0) {
            N2_str = line.substr(5);
        }
    }

    file.close();

    outputFile << std::boolalpha;

    switch (base) {
        case 2: {
            BigRational<2> N1(N1_str), N2(N2_str);
            outputFile << "N1: " << N1 << "\n";
            outputFile << "N2: " << N2 << "\n";
            outputFile << "N1 == N2: " << (N1 == N2) << "\n";
            outputFile << "N1 < N2: " << (N1 < N2) << "\n";
            outputFile << "N1 + N2: " << (N1 + N2) << "\n";
            outputFile << "N1 - N2: " << (N1 - N2) << "\n";
            outputFile << "N1 * N2: " << (N1 * N2) << "\n";
            outputFile << "N1 / N2: " << (N1 / N2) << "\n";
            break;
        }
        case 8: {
            BigRational<8> N1(N1_str), N2(N2_str);
            outputFile << "N1: " << N1 << "\n";
            outputFile << "N2: " << N2 << "\n";
            outputFile << "N1 == N2: " << (N1 == N2) << "\n";
            outputFile << "N1 < N2: " << (N1 < N2) << "\n";
            outputFile << "N1 + N2: " << (N1 + N2) << "\n";
            outputFile << "N1 - N2: " << (N1 - N2) << "\n";
            outputFile << "N1 * N2: " << (N1 * N2) << "\n";
            outputFile << "N1 / N2: " << (N1 / N2) << "\n";
            break;
        }
        case 10: {
            BigRational<10> N1(N1_str), N2(N2_str);
            outputFile << "N1: " << N1 << "\n";
            outputFile << "N2: " << N2 << "\n";
            outputFile << "N1 == N2: " << (N1 == N2) << "\n";
            outputFile << "N1 < N2: " << (N1 < N2) << "\n";
            outputFile << "N1 + N2: " << (N1 + N2) << "\n";
            outputFile << "N1 - N2: " << (N1 - N2) << "\n";
            outputFile << "N1 * N2: " << (N1 * N2) << "\n";
            outputFile << "N1 / N2: " << (N1 / N2) << "\n";
            break;
        }
        case 16: {
            BigRational<16> N1(N1_str), N2(N2_str);
            outputFile << "N1: " << N1 << "\n";
            outputFile << "N2: " << N2 << "\n";
            outputFile << "N1 == N2: " << (N1 == N2) << "\n";
            outputFile << "N1 < N2: " << (N1 < N2) << "\n";
            outputFile << "N1 + N2: " << (N1 + N2) << "\n";
            outputFile << "N1 - N2: " << (N1 - N2) << "\n";
            outputFile << "N1 * N2: " << (N1 * N2) << "\n";
            outputFile << "N1 / N2: " << (N1 / N2) << "\n";
            break;
        }
        default:
            std::cerr << "Error: Base no soportada\n";
            break;
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    BigInteger<10> a("123");
    BigUnsigned<10> b("987");
    BigInteger<10> c("456");
    BigUnsigned<10> d("543");

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;

    std::cout << a + c << std::endl;
    std::cout << a - c << std::endl;
    std::cout << a * c << std::endl;
    std::cout << a / c << std::endl;
    std::cout << (a == c) << std::endl;
    std::cout << (a < c) << std::endl;

    std::cout << b + d << std::endl;
    std::cout << b - d << std::endl;
    std::cout << b * d << std::endl;
    std::cout << b / d << std::endl;
    std::cout << (b == d) << std::endl;
    std::cout << (b < d) << std::endl;

    BigRational<10> e(a, b);
    BigRational<10> f(c, d);

    std::cout << e << std::endl;
    std::cout << f << std::endl;
    std::cout << e + f << std::endl;
    std::cout << e - f << std::endl;
    std::cout << e * f << std::endl;
    std::cout << e / f << std::endl;
    std::cout << (e == f) << std::endl;
    std::cout << (e < f) << std::endl;

    return 0;
}
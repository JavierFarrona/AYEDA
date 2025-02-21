#include <iostream>
#include <fstream>
#include <string>
#include "../lib/bigRational.h"

/*
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
*/

#include <iostream>
#include "../lib/bigUnsigned.h"

int main() {
	/*
    // Base 8
    BigRational<8> rat8_1("17/4"); // 15/4 en decimal
    BigRational<8> rat8_2("7/3");  // 7/3 en decimal
    std::cout << "Base 8:\n";
    std::cout << "rat8_1: " << rat8_1 << "\n";
    std::cout << "rat8_2: " << rat8_2 << "\n";
    std::cout << "rat8_1 + rat8_2: " << (rat8_1 + rat8_2) << "\n";
    std::cout << "rat8_1 - rat8_2: " << (rat8_1 - rat8_2) << "\n";
    std::cout << "rat8_1 * rat8_2: " << (rat8_1 * rat8_2) << "\n";
    std::cout << "rat8_1 / rat8_2: " << (rat8_1 / rat8_2) << "\n";
    std::cout << std::boolalpha;
    std::cout << "rat8_1 == rat8_2: " << (rat8_1 == rat8_2) << "\n";
    std::cout << "rat8_1 < rat8_2: " << (rat8_1 < rat8_2) << "\n";
    std::cout << "rat8_1 <= rat8_2: " << (rat8_1 <= rat8_2) << "\n";
    std::cout << "rat8_1 > rat8_2: " << (rat8_1 > rat8_2) << "\n";
    std::cout << "rat8_1 >= rat8_2: " << (rat8_1 >= rat8_2) << "\n\n";

    // Base 10
    BigRational<10> rat10_1("15/4");
    BigRational<10> rat10_2("7/3");
    std::cout << "Base 10:\n";
    std::cout << "rat10_1: " << rat10_1 << "\n";
    std::cout << "rat10_2: " << rat10_2 << "\n";
    std::cout << "rat10_1 + rat10_2: " << (rat10_1 + rat10_2) << "\n";
    std::cout << "rat10_1 - rat10_2: " << (rat10_1 - rat10_2) << "\n";
    std::cout << "rat10_1 * rat10_2: " << (rat10_1 * rat10_2) << "\n";
    std::cout << "rat10_1 / rat10_2: " << (rat10_1 / rat10_2) << "\n";
    std::cout << std::boolalpha;
    std::cout << "rat10_1 == rat10_2: " << (rat10_1 == rat10_2) << "\n";
    std::cout << "rat10_1 < rat10_2: " << (rat10_1 < rat10_2) << "\n";
    std::cout << "rat10_1 <= rat10_2: " << (rat10_1 <= rat10_2) << "\n";
    std::cout << "rat10_1 > rat10_2: " << (rat10_1 > rat10_2) << "\n";
    std::cout << "rat10_1 >= rat10_2: " << (rat10_1 >= rat10_2) << "\n\n";

    // Base 16
    BigRational<16> rat16_1("F/4"); // 15/4 en decimal
    BigRational<16> rat16_2("7/3"); // 7/3 en decimal
    std::cout << "Base 16:\n";
    std::cout << "rat16_1: " << rat16_1 << "\n";
    std::cout << "rat16_2: " << rat16_2 << "\n";
    std::cout << "rat16_1 + rat16_2: " << (rat16_1 + rat16_2) << "\n";
    std::cout << "rat16_1 - rat16_2: " << (rat16_1 - rat16_2) << "\n";
    std::cout << "rat16_1 * rat16_2: " << (rat16_1 * rat16_2) << "\n";
    std::cout << "rat16_1 / rat16_2: " << (rat16_1 / rat16_2) << "\n";
    std::cout << std::boolalpha;
    std::cout << "rat16_1 == rat16_2: " << (rat16_1 == rat16_2) << "\n";
    std::cout << "rat16_1 < rat16_2: " << (rat16_1 < rat16_2) << "\n";
    std::cout << "rat16_1 <= rat16_2: " << (rat16_1 <= rat16_2) << "\n";
    std::cout << "rat16_1 > rat16_2: " << (rat16_1 > rat16_2) << "\n";
    std::cout << "rat16_1 >= rat16_2: " << (rat16_1 >= rat16_2) << "\n\n";

    // Base 2
    std::cout << "Base 2:\n";
    BigRational<2> rat2_1("-1111/101"); // 11/4 en decimal
    BigRational<2> rat2_2("011/1");   // 7/3 en decimal

    std::cout << "rat2_1: " << rat2_1 << "\n";
    std::cout << "rat2_2: " << rat2_2 << "\n";

    std::cout << "rat2_1 + rat2_2: " << (rat2_1 + rat2_2) << "\n";
    std::cout << "rat2_1 - rat2_2: " << (rat2_1 - rat2_2) << "\n";
    std::cout << "rat2_1 * rat2_2: " << (rat2_1 * rat2_2) << "\n";
    std::cout << "rat2_1 / rat2_2: " << (rat2_1 / rat2_2) << "\n";
    std::cout << std::boolalpha;
    std::cout << "rat2_1 == rat2_2: " << (rat2_1 == rat2_2) << "\n";
    std::cout << "rat2_1 < rat2_2: " << (rat2_1 < rat2_2) << "\n";
    std::cout << "rat2_1 <= rat2_2: " << (rat2_1 <= rat2_2) << "\n";
    std::cout << "rat2_1 > rat2_2: " << (rat2_1 > rat2_2) << "\n";
    std::cout << "rat2_1 >= rat2_2: " << (rat2_1 >= rat2_2) << "\n\n";
	*/

  	BigRational<2> num1("-1100101/100");
    BigRational<2> num2("10100/101");
    std::cout << "num1: " << num1 << "\n";
    std::cout << "num2: " << num2 << "\n";
    std::cout << num1 << " + " << num2 << " = " << (num1 + num2) << "\n";
    std::cout << num1 << " - " << num2 << " = " << (num1 - num2) << "\n";
    std::cout << num1 << " * " << num2 << " = " << (num1 * num2) << "\n";
    std::cout << num1 << " / " << num2 << " = " << (num1 / num2) << "\n";
    //std::cout << num1 << " % " << num2 << " = " << (num1 % num2) << "\n";


    return 0;
}
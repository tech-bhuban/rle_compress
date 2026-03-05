

#include <iostream>
#include <fstream>
#include <string>

class RLECompressor {
public:
    std::string compress(const std::string& input) {
        std::string output;
        int count = 1;
        
        for(size_t i = 1; i <= input.length(); i++) {
            if(i < input.length() && input[i] == input[i-1]) {
                count++;
            } else {
                if(count > 1) {
                    output += std::to_string(count) + input[i-1];
                } else {
                    output += input[i-1];
                }
                count = 1;
            }
        }
        return output;
    }
    
    std::string decompress(const std::string& input) {
        std::string output;
        for(size_t i = 0; i < input.length(); i++) {
            if(isdigit(input[i])) {
                int count = 0;
                while(i < input.length() && isdigit(input[i])) {
                    count = count * 10 + (input[i] - '0');
                    i++;
                }
                output += std::string(count, input[i]);
            } else {
                output += input[i];
            }
        }
        return output;
    }
    
    void compressFile(const std::string& inFile, const std::string& outFile) {
        std::ifstream in(inFile);
        std::string content((std::istreambuf_iterator<char>(in)), 
                            std::istreambuf_iterator<char>());
        std::string compressed = compress(content);
        
        std::ofstream out(outFile);
        out << compressed;
        
        std::cout << "Original size: " << content.length() << " bytes\n";
        std::cout << "Compressed size: " << compressed.length() << " bytes\n";
        std::cout << "Ratio: " << (compressed.length() * 100.0 / content.length()) << "%\n";
    }
};

int main() {
    RLECompressor rle;
    
    // Test with repeated characters
    std::string text = "AAAABBBCCDAA";
    std::string comp = rle.compress(text);
    std::string decomp = rle.decompress(comp);
    
    std::cout << "Original: " << text << "\n";
    std::cout << "Compressed: " << comp << "\n";
    std::cout << "Decompressed: " << decomp << "\n";
    
    return 0;
}

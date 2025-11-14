#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::string transformChar( const char in_char){
        /*Transliterates input alphanumeric char into an uppercase string.

        char in_char: char to transliterate.

        return: std:string of the transliterated char. 
        */ 
        std::string inputText;
    // Uppercase alphabetic characters
        if (std::isalpha(in_char)) {
            inputText += std::toupper(in_char);
        
        }
            // Transliterate digits to English words
        switch (in_char) {
            case '0':
                inputText += "ZERO";
                break;
            case '1':
                inputText += "ONE";
                break;
            case '2':
                inputText += "TWO";
                break;
            case '3':
                inputText += "THREE";
                break;
            case '4':
                inputText += "FOUR";
                break;
            case '5':
                inputText += "FIVE";
                break;
            case '6':
                inputText += "SIX";
                break;
            case '7':
                inputText += "SEVEN";
                break;
            case '8':
                inputText += "EIGHT";
                break;
            case '9':
                inputText += "NINE";
                break;

        }
    
            // If the character isn't alphabetic or numeric, DONT add it
        return inputText;
}


bool processCommandLine(const std::vector<std::string>& args,
    bool& helpRequested,
    bool& versionRequested, 
    std::string& inputFileName,
    std::string& outputFileName)
    {

        /*Processes argmuents and flags given to mpags-cipher

        const std::vector<std::string>& args: vector of arguments taken from the command line
        bool& helpRequested: flag to trigger help message to appear
        bool& versionRequested: flag to trigger version message
        std::string& inputFileName: name of file to take cipher input from (NOT IMPLEMENTED)
        std::string& outputFileName: name of file to place cipher output (NOT IMPLEMENTED)

        return: 0 with success 1 with failiure
        */
    const std::size_t nCmdLineArgs{args.size()};    
    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            return 1;
        }
    }
    return 0;
    }

int main(int argc, char* argv[])
{
    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFileName{""};
    std::string outputFileName{""};

    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName);

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFileName.empty()) {
        std::cerr << "[warning] input from file ('" << inputFileName
                  << "') not implemented yet, using stdin\n";
    }

    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText += transformChar(inputChar);

    }

   

    // Warn that output file option not yet implemented
    if (!outputFileName.empty()) {
        std::cerr << "[warning] output to file ('" << outputFileName
                  << "') not implemented yet, using stdout\n";
    }

     // Print out the transliterated text
    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

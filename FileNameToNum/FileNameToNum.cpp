#include <iostream>
#include <string.h>
#include <filesystem>
#include <cstdio>

using namespace std;


unsigned int NumberIns = 0;
std::string InsToFive;

string CalCIns(unsigned int NI) {
    if (NI < 10) {
        InsToFive = "0000" + to_string(NI);
    }
    else {
        InsToFive = "000" + to_string(NI);
    }

    return InsToFive;
}

int main()
{
    string path;

    std::cout << " [>] Enter the folder contains your images: ";
    std::cin >> path;

    unsigned int SumOfPNG = 0;
    unsigned int SumOfJPG = 0;
    unsigned int ErrTp = 0;
    unsigned int SumCImg = 0;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::cout << " [•] A folder is found. You probably want to remove it: " << entry.path() << std::endl;
        }
        else if (std::filesystem::path(entry.path()).extension() == ".png") {
            std::cout << " [•] A PNG is found: " << std::filesystem::path(entry.path()).filename() << endl;
            SumOfPNG += 1;
        }
        else if (std::filesystem::path(entry.path()).extension() == ".jpg") {
            std::cout << " [•] A JPG is found: " << std::filesystem::path(entry.path()).filename() << endl;
            SumOfJPG += 1;
        }
    }

    std::cout << "\n" << std::endl;
    std::cout << " [¤] Images Total: " << to_string(SumOfPNG) << std::endl;
    std::cout << " [¤] Other Ext of Images Total: " << to_string(SumOfJPG) << std::endl;

    char contnue;
    char convjpg;
    char rovcjpg;

    std::cout << " [>] Do you wish to continue renaming PNG files? (y/n): ";
    std::cin >> contnue;

    std::cout << " [>] Do you wish to convert JPG files to PNG files? (y/n): ";
    std::cin >> convjpg;

    std::cout << " [>] Do you wish to delete original JPG files after converting them? (y/n): ";
    std::cin >> rovcjpg;

    std::string WhiteSpace = " ";
    std::string SysCmd;

    std::cout << "\n" << std::endl;

    if (contnue == 'y') {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::path(entry.path()).extension() == ".png") {
                NumberIns += 1;
                CalCIns(NumberIns);

                std::string CurFN = std::filesystem::path(entry.path()).filename().string();

                if (std::rename(entry.path().string().c_str(), (path + "/" + InsToFive + ".png").c_str()) == 0) {
                    std::cout << " [•] Successfully renamed " << CurFN << " to " << InsToFive << ".png" << endl;
                }
                else {
                    perror((" [•] Could not rename " + CurFN + " to " + InsToFive + ".png because").c_str());
                    ErrTp += 1;
                    SumOfPNG -= 1;
                }
            }
            else if (std::filesystem::path(entry.path()).extension() == ".jpg") {
                if (convjpg == 'y') {
                    NumberIns += 1;
                    SumCImg += 1;
                    CalCIns(NumberIns);

                    SysCmd = "python " + std::filesystem::current_path().string() + "/src/jpg2png.py " + entry.path().string() + WhiteSpace + path + "/" + InsToFive + ".png " + std::filesystem::path(entry.path()).filename().string() + WhiteSpace + InsToFive + ".png";

                    system(SysCmd.c_str());
                }
                if (rovcjpg == 'y') {
                    if (std::remove(entry.path().string().c_str()) != 0) {
                        std::cout << " [E] Couldn't remove the original file: " << std::filesystem::path(entry.path()).filename().string() << endl;
                    }
                }
            }
            else {
                ErrTp += 1;
            }
        }
    }
    else {
        std::cout << " [^] Dev: Vestir.";

        exit(0);
    }

    std::cout << "\n" << std::endl;
    std::cout << "- Summary -" << std::endl;
    std::cout << " [¤] Successfully Renamed Images Total: " << to_string(SumOfPNG) << std::endl;
    std::cout << " [¤] Successfully Converted Images Total: " << to_string(SumCImg) << std::endl;
    std::cout << " [¤] Error Types Images Total: " << to_string(ErrTp) << std::endl;
    std::cout << "\n" << std::endl;

    system("pause");

    return 0;
}
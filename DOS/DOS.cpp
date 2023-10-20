#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

std::vector<std::string> emulatorFiles;

std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void clearScreen() {
    system("cls");
}

void displayHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "CLS - Clear the screen" << std::endl;
    std::cout << "HELP - Display available commands" << std::endl;
    std::cout << "DIR - List directory contents" << std::endl;
    std::cout << "MKDIR - Create a Directory" << std::endl;
    std::cout << "FORMAT - Format a drive" << std::endl;
    std::cout << "CHKDSK - Check a drive for errors" << std::endl;
    std::cout << "VOL - Display disk volume" << std::endl;
    std::cout << "MEM - Display memory usage" << std::endl;
    std::cout << "VER - Display version information" << std::endl;
    std::cout << "EXIT - Exit MS-DOS" << std::endl;
}

void formatDrive() {
    std::cout << "Formatting a drive..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Drive formatted." << std::endl;
}

void checkDriveForErrors() {
    std::cout << "Checking drive for errors..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "No errors found." << std::endl;
}


void displayDiskVolume() {
    std::cout << "Volume in drive C is MS-DOS_Emulator" << std::endl;
}

void displayMemoryUsage() {
    std::cout << "Total memory: 640K" << std::endl;
    std::cout << "Available memory: 620K" << std::endl;
}

void displayVersionInfo() {
    std::cout << "Microsoft(R) MS-DOS Version 7.10" << std::endl;
    std::cout << "(C) Copyright Microsoft Corp 1981-2001" << std::endl;
}

void exitEmulator() {
    std::cout << "Exiting MS-DOS..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    exit(0);
}

std::map<std::string, std::vector<std::string>> directories;

void createDirectory(const std::string& dirname) {
    directories[dirname];
    std::cout << "Directory '" << dirname << "' created." << std::endl;
}

void dir() {
    std::cout << "Volume in drive C has no label." << std::endl;
    std::cout << "Directory of C:\\" << std::endl;

    for (const std::string& file : emulatorFiles) {
        std::cout << file << std::endl;
    }

    for (const auto& directory : directories) {
        std::cout << directory.first << "                     <DIR>" << std::endl;
        std::cout << "" << std::endl;
    }
}

void startupAnimation() {
    std::cout << "Microsoft(R) MS-DOS Version 7.10" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "(C) Copyright Microsoft Corp 1981-2001" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "HIMEM is testing extended memory...";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << " HMA is available." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Devicehigh=EMM386.EXE" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Lastdrive=Z" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "FCBS=4,0" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "DOSKEY installed" << std::endl;
    std::cout << "" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "C:\\>" << std::endl;
}


int main() {
    std::map<std::string, void(*)()> commands;

    commands["cls"] = clearScreen;
    commands["help"] = displayHelp;
    commands["dir"] = dir;
    commands["format"] = formatDrive;
    commands["chkdsk"] = checkDriveForErrors;
    commands["vol"] = displayDiskVolume;
    commands["mem"] = displayMemoryUsage;
    commands["ver"] = displayVersionInfo;
    commands["exit"] = exitEmulator;

    startupAnimation();

    while (true) {
        std::string input;
        std::cout << "C:\\>";
        std::getline(std::cin, input);

        input = toLowerCase(input);

        if (commands.find(input) != commands.end()) {
            commands[input]();
        }
        else if (input.find("mkdir ") == 0) {
            std::string dirname = input.substr(6);
            createDirectory(dirname);
        }
        else {
            std::cout << "Bad command or file name." << std::endl;
        }
    }

    return 0;
}

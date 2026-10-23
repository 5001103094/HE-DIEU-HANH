
#include "../include/input.hpp"

#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>

namespace {

// Nhap so nguyen va kiem tra du lieu
bool readInteger(
    const std::string& prompt,
    int minimum,
    int& result)
{
    std::string line;

    while (true)
    {
        std::cout << prompt;

        if (!std::getline(std::cin, line))
            return false;

        std::istringstream stream(line);
        long long number = 0;
        std::string extra;

        if (!(stream >> number) ||
            (stream >> extra) ||
            number < minimum ||
            number > std::numeric_limits<int>::max())
        {
            std::cout << "Du lieu khong hop le. "
                      << "Vui long nhap so nguyen "
                      << (minimum == 0 ? "khong am" : "duong")
                      << ".\n";
            continue;
        }

        result = static_cast<int>(number);
        return true;
    }
}

// Nhap ma tien trinh va kiem tra trung lap

bool readPid(
    const std::set<std::string>& usedPid,
    std::string& result)
{
    static const std::regex pattern(R"(^P[1-9][0-9]*$)");

    std::string line;

    while (true)
    {
        std::cout << "Ma tien trinh (vi du P1): ";

        if (!std::getline(std::cin, line))
            return false;

        // Kiem tra dinh dang P1, P2, P3,...
        if (!std::regex_match(line, pattern))
        {
            std::cout
                << "Ma tien trinh khong hop le. "
                << "Vui long nhap dung dinh dang P1, P2, P3,...\n";
        }
        // Kiem tra trung ma tien trinh
        else if (usedPid.count(line) != 0)
        {
            std::cout
                << "Ma tien trinh da ton tai. "
                << "Hay nhap ma khac.\n";
        }
        else
        {
            result = line;
            return true;
        }
    }
}


// Kiem tra cac vung RAM co chong lan khong
bool overlapsExisting(
    const MemoryState& memory,
    int start,
    int size)
{
    const long long end =
        static_cast<long long>(start) + size;

    for (const Hole& hole : memory)
    {
        const long long existingEnd =
            static_cast<long long>(hole.startKB)
            + hole.freeKB;

        if (start < existingEnd &&
            hole.startKB < end)
        {
            return true;
        }
    }

    return false;
}

} // namespace

// CV02 - Nhap du lieu RAM va tien trinh
bool inputData(
    MemoryState& initialMemory,
    std::vector<Request>& requests)
{
    MemoryState newMemory;
    std::vector<Request> newRequests;

    int holeCount = 0;

    if (!readInteger(
        "So vung RAM trong: ", 1, holeCount))
    {
        return false;
    }

    // Nhap danh sach vung RAM
    for (int i = 1; i <= holeCount; ++i)
    {
        std::cout << "\nNhap vung H" << i << ":\n";

        while (true)
        {
            int startKB = 0;
            int freeKB = 0;

            if (!readInteger(
                "Dia chi bat dau (KB): ", 0, startKB))
            {
                return false;
            }

            if (!readInteger(
                "Dung luong trong (KB): ", 1, freeKB))
            {
                return false;
            }

            if (freeKB >
                std::numeric_limits<int>::max() - startKB)
            {
                std::cout << "Dia chi ket thuc "
                          << "vuot gioi han. Nhap lai.\n";
                continue;
            }

            if (overlapsExisting(
                newMemory, startKB, freeKB))
            {
                std::cout << "Vung RAM bi chong lan. "
                          << "Nhap lai.\n";
                continue;
            }

            newMemory.push_back(
                Hole{i, startKB, freeKB});

            break;
        }
    }

    // Nhap so tien trinh
    int requestCount = 0;

    if (!readInteger(
        "\nSo tien trinh: ", 1, requestCount))
    {
        return false;
    }

    std::set<std::string> usedPid;

    // Nhap danh sach tien trinh
    for (int i = 1; i <= requestCount; ++i)
    {
        std::cout << "\nNhap tien trinh thu "
                  << i << ":\n";

        std::string pid;
        int requiredKB = 0;

        if (!readPid(usedPid, pid))
            return false;

        if (!readInteger(
            "Dung luong yeu cau (KB): ",
            1, requiredKB))
        {
            return false;
        }

        usedPid.insert(pid);

        newRequests.push_back(
            Request{pid, requiredKB});
    }

    
    // Sap xep RAM theo dia chi bat dau tang dan
    // Giu nguyen ID cua tung vung RAM
    std::sort(
        newMemory.begin(),
        newMemory.end(),
        [](const Hole& a, const Hole& b)
        {
            return a.startKB < b.startKB;
        }
    );

    // Chi cap nhat du lieu khi nhap thanh cong
    initialMemory = newMemory;
    requests = newRequests;

    return true;

}

// CV02 - Hien thi du lieu da nhap
void displayInputData(
    const MemoryState& initialMemory,
    const std::vector<Request>& requests)
{
    std::cout << "\n=== CAC VUNG RAM TRONG ===\n";

    for (const Hole& hole : initialMemory)
    {
        std::cout << "H" << hole.id
                  << ": bat dau " << hole.startKB
                  << " KB, trong " << hole.freeKB
                  << " KB\n";
    }

    std::cout << "\n=== CAC TIEN TRINH ===\n";

    for (const Request& request : requests)
    {
        std::cout << request.pid
                  << ": can " << request.requiredKB
                  << " KB\n";
    }
}

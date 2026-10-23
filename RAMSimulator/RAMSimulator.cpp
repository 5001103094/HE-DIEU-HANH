
#include <iostream>
#include <string>

#include "include/models.hpp"
#include "include/allocators.hpp"
#include "include/input.hpp"
#include <vector>
#include "include/memory.hpp"
#include <iomanip>
// CV01 - TV5: Hien thi menu chinh
void showMenu()
{
    std::cout << "\n========================================\n";
    std::cout << "       MO PHONG CAP PHAT RAM\n";
    std::cout << "========================================\n";
    std::cout << "1. Nhap du lieu RAM va tien trinh\n";
    std::cout << "2. Chay thuat toan First Fit\n";
    std::cout << "3. Chay thuat toan Best Fit\n";
    std::cout << "4. Chay thuat toan Worst Fit\n";
    std::cout << "5. Chay ca ba thuat toan\n";
    std::cout << "6. So sanh ket qua cap phat\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "========================================\n";
    std::cout << "Nhap lua chon: ";
}

using AllocatorFunction =
    AllocationResult (*)(MemoryState&, const Request&);

// CV03 - Chay mot thuat toan tren ban sao RAM
void runAlgorithm(
    const std::string& algorithmName,
    const MemoryState& initialMemory,
    const std::vector<Request>& requests,
    AllocatorFunction allocator)
{
    if (initialMemory.empty() || requests.empty())
    {
        std::cout << "\nChua co du lieu RAM hoac tien trinh.\n";
        std::cout << "Vui long chon 1 de nhap du lieu.\n";
        return;
    }

    // Moi thuat toan su dung RAM ban dau doc lap
    MemoryState memory = copyMemory(initialMemory);

    int successCount = 0;
    int failureCount = 0;

    std::cout << "\n=== " << algorithmName << " ===\n";

    for (const Request& request : requests)
    {
        AllocationResult result = allocator(memory, request);

        std::cout << "\nTien trinh: " << result.pid
                  << " - Yeu cau: " << request.requiredKB
                  << " KB\n";

        if (result.success)
        {
            ++successCount;

            std::cout << "Cap phat thanh cong tai H"
                      << result.holeId << "\n";
            std::cout << "Dung luong con lai tai vung: "
                      << result.remainingKB << " KB\n";
        }
        else
        {
            ++failureCount;

            std::cout << "Cap phat that bai.\n";
            std::cout << "Nguyen nhan: "
                      << result.reason << "\n";
        }
    }

    std::cout << "\n=== THONG KE " << algorithmName
              << " ===\n";

    std::cout << "Thanh cong: " << successCount << "\n";
    std::cout << "That bai: " << failureCount << "\n";
    std::cout << "Tong RAM trong: "
              << totalFreeKB(memory) << " KB\n";
    std::cout << "Vung trong lon nhat: "
              << largestHoleKB(memory) << " KB\n";
}

struct AlgorithmSummary
{
    int successCount = 0;
    int failureCount = 0;
    long long totalFree = 0;
    int largestHole = 0;
};

// Thong ke ket qua mot thuat toan
AlgorithmSummary calculateSummary(
    const MemoryState& initialMemory,
    const std::vector<Request>& requests,
    AllocatorFunction allocator)
{
    MemoryState memory = copyMemory(initialMemory);
    AlgorithmSummary summary;

    for (const Request& request : requests)
    {
        AllocationResult result = allocator(memory, request);

        if (result.success)
            ++summary.successCount;
        else
            ++summary.failureCount;
    }

    summary.totalFree = totalFreeKB(memory);
    summary.largestHole = largestHoleKB(memory);

    return summary;
}

// CV03 - So sanh ba thuat toan
void compareAlgorithms(
    const MemoryState& initialMemory,
    const std::vector<Request>& requests)
{
    if (initialMemory.empty() || requests.empty())
    {
        std::cout << "\nChua co du lieu.\n";
        std::cout << "Vui long chon 1 de nhap du lieu.\n";
        return;
    }

    AlgorithmSummary ff =
        calculateSummary(initialMemory, requests, firstFit);

    AlgorithmSummary bf =
        calculateSummary(initialMemory, requests, bestFit);

    AlgorithmSummary wf =
        calculateSummary(initialMemory, requests, worstFit);

    std::cout << "\n=== BANG SO SANH THUAT TOAN ===\n";

    std::cout << std::left
              << std::setw(15) << "Thuat toan"
              << std::setw(12) << "Thanh cong"
              << std::setw(12) << "That bai"
              << std::setw(16) << "Tong RAM trong"
              << "Vung lon nhat\n";

    auto printRow = [](const std::string& name,
                       const AlgorithmSummary& result)
    {
        std::cout << std::left
                  << std::setw(15) << name
                  << std::setw(12) << result.successCount
                  << std::setw(12) << result.failureCount
                  << std::setw(16) << result.totalFree
                  << result.largestHole << "\n";
    };

    printRow("First Fit", ff);
    printRow("Best Fit", bf);
    printRow("Worst Fit", wf);

    std::cout << "\nDon vi dung luong: KB\n";
}

// CV01 - TV5: Xu ly lua chon tren menu
void handleChoice(
    const std::string& choice,
    MemoryState& initialMemory,
    std::vector<Request>& requests)
{
    if (choice == "1")
    {
        std::cout << "\n[Nhap du lieu RAM va tien trinh]\n";

        if (inputData(initialMemory, requests))
        {
            std::cout << "\nNhap du lieu thanh cong!\n";
            displayInputData(initialMemory, requests);
        }
        else
        {
            std::cout << "\nQua trinh nhap bi ket thuc.\n";
        }
    }
    else if (choice == "2")
    {
        runAlgorithm(
            "FIRST FIT",
            initialMemory,
            requests,
            firstFit
        );
    }
    else if (choice == "3")
    {
        runAlgorithm(
            "BEST FIT",
            initialMemory,
            requests,
            bestFit
        );
    }
    else if (choice == "4")
    {
        runAlgorithm(
            "WORST FIT",
            initialMemory,
            requests,
            worstFit
        );
    }
    else if (choice == "5")
    {
        if (initialMemory.empty() || requests.empty())
        {
            std::cout << "\nChua co du lieu. "
                    << "Vui long chon 1 de nhap du lieu.\n";
        }
        else
        {
            runAlgorithm(
                "FIRST FIT",
                initialMemory,
                requests,
                firstFit
            );

            runAlgorithm(
                "BEST FIT",
                initialMemory,
                requests,
                bestFit
            );

            runAlgorithm(
                "WORST FIT",
                initialMemory,
                requests,
                worstFit
            );
        }
    }
    else if (choice == "6")
    {
        compareAlgorithms(initialMemory, requests);
    }
    else
    {
        std::cout << "\nLua chon khong hop le!\n";
        std::cout << "Vui long nhap so tu 0 den 6.\n";
    }
}

// CV01 - TV5: Dieu khien chuong trinh
int main()
{
    std::string choice;

    MemoryState initialMemory;
    std::vector<Request> requests;

    while (true)
    {
        showMenu();

        if (!std::getline(std::cin, choice))
        {
            break;
        }

        if (choice == "0")
        {
            std::cout << "\nKet thuc chuong trinh.\n";
            break;
        }

        handleChoice(choice, initialMemory, requests);

        std::cout << "\nNhan Enter de quay lai menu...";

        if (!std::getline(std::cin, choice))
        {
            break;
        }
    }

    return 0;
}

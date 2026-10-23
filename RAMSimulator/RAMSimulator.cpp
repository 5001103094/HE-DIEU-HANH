
#include <iostream>
#include <string>

#include "include/models.hpp"
#include "include/allocators.hpp"
#include "include/input.hpp"
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
        std::cout << "\n[First Fit]\n";
        std::cout << "Chua tich hop thuat toan.\n";
    }
    else if (choice == "3")
    {
        std::cout << "\n[Best Fit]\n";
        std::cout << "Chua tich hop thuat toan.\n";
    }
    else if (choice == "4")
    {
        std::cout << "\n[Worst Fit]\n";
        std::cout << "Chua tich hop thuat toan.\n";
    }
    else if (choice == "5")
    {
        std::cout << "\n[Chay ca ba thuat toan]\n";
        std::cout << "Chua tich hop cac thuat toan.\n";
    }
    else if (choice == "6")
    {
        std::cout << "\n[So sanh ket qua]\n";
        std::cout << "Chuc nang se duoc tich hop sau.\n";
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

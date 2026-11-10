
#include "include/allocators.hpp"
#include <ostream>

// CV03 - Hien thi qua trinh cap phat Best Fit - TV3
// Ham nay chi hien thi, khong thay doi RAM.
void printBestFitTrace(
    const MemoryState& before,
    const Request& request,
    const AllocationResult& result,
    const MemoryState& after,
    std::ostream& out
) {
    out << "\n========== BEST FIT TRACE ==========\n";
    out << "Tien trinh: " << request.pid << '\n';
    out << "Yeu cau: " << request.requiredKB << " KB\n";

    // Buoc 1: Hien thi RAM truoc cap phat
    out << "\nBuoc 1. Cac vung RAM truoc cap phat:\n";

    long long totalFree = 0;
    int largestHole = 0;

    if (before.empty()) {
        out << "(Khong co vung RAM trong)\n";
    }

    for (const Hole& h : before) {
        out << "H" << h.id
            << ": start=" << h.startKB
            << " KB, free=" << h.freeKB << " KB";

        if (request.requiredKB <= 0) {
            out << " -> YEU CAU KHONG HOP LE";
        }
        else if (h.freeKB >= request.requiredKB) {
            out << " -> DU";
        }
        else {
            out << " -> KHONG DU";
        }

        out << '\n';

        totalFree += h.freeKB;

        if (h.freeKB > largestHole) {
            largestHole = h.freeKB;
        }
    }

    // Buoc 2: Hien thi ket qua Best Fit
    out << "\nBuoc 2. Ket qua lua chon:\n";

    if (result.success) {
        out << "THANH CONG: Chon H"
            << result.holeId << '\n';

        for (const Hole& h : before) {
            if (h.id == result.holeId) {
                out << "Vung truoc: start="
                    << h.startKB
                    << " KB, free="
                    << h.freeKB << " KB\n";

                out << "Dia chi da cap: ["
                    << h.startKB << ", "
                    << (static_cast<long long>(h.startKB)
                        + request.requiredKB)
                    << ") KB\n";
                break;
            }
        }

        out << "Dung luong con lai tai vung da chon: "
            << result.remainingKB << " KB\n";
    }
    else {
        out << "THAT BAI";

        if (!result.reason.empty()) {
            out << ": " << result.reason;
        }

        out << '\n';

        if (request.requiredKB > 0) {
            if (totalFree < request.requiredKB) {
                out << "Tong RAM trong khong du.\n";
            }
            else if (largestHole < request.requiredKB) {
                out << "RAM trong du tong dung luong "
                    << "nhung bi phan manh ngoai.\n";
            }
        }
    }

    // Buoc 3: Hien thi RAM sau cap phat
    out << "\nBuoc 3. RAM sau thao tac:\n";

    if (after.empty()) {
        out << "(Khong con vung RAM trong)\n";
    }

    for (const Hole& h : after) {
        out << "H" << h.id
            << ": start=" << h.startKB
            << " KB, free=" << h.freeKB << " KB\n";
    }

    out << "====================================\n";
}

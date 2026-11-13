cmake_minimum_required(VERSION 3.16)

# Mot cau hinh bien dich chung cho macOS, Windows va Linux.
project(MoPhongBoNho LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Cac tep nay dung chung cho ung dung va cac bo kiem thu.
add_library(thu_vien_bo_nho STATIC
    cap_phat_dau_tien.cpp
    cap_phat_vua_nhat.cpp
    dien_bien_cap_phat.cpp
    src/bo_nho.cpp
    src/nhap_du_lieu.cpp
    src/cap_phat_lon_nhat.cpp
    src/so_sanh.cpp
)
target_include_directories(thu_vien_bo_nho PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Mot tep main() duy nhat cho ung dung chinh.
add_executable(mo_phong_bo_nho mo_phong_bo_nho.cpp)
target_link_libraries(mo_phong_bo_nho PRIVATE thu_vien_bo_nho)

# Tim Qt6 Widgets de xay dung giao dien do hoa.
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Chuong trinh giao dien co ham main() rieng.
add_executable(mo_phong_bo_nho_giao_dien
    giao_dien/cua_so_chinh.cpp
)

# Dung chung cac thuat toan va thu vien Qt.
target_link_libraries(mo_phong_bo_nho_giao_dien PRIVATE
    thu_vien_bo_nho
    Qt6::Widgets
)

include(CTest)
if(BUILD_TESTING)
    # Moi bo kiem thu co main() rieng, khong gop vao mot chuong trinh.
    set(danh_sach_kiem_thu
        kiem_thu_bo_nho
        kiem_thu_cap_phat_dau_tien
        kiem_thu_cap_phat_vua_nhat
        kiem_thu_cap_phat_lon_nhat
        kiem_thu_dien_bien
        kiem_thu_so_sanh
        kiem_thu_nhap_du_lieu
        kiem_thu_so_sanh_lich_su
    )

    foreach(ten_kiem_thu IN LISTS danh_sach_kiem_thu)
        add_executable(${ten_kiem_thu} "tests/${ten_kiem_thu}.cpp")
        target_link_libraries(${ten_kiem_thu} PRIVATE thu_vien_bo_nho)

        # Van bat assert trong cac bo kiem thu ke ca khi chon Release.
        if(MSVC)
            target_compile_options(${ten_kiem_thu} PRIVATE /UNDEBUG)
        else()
            target_compile_options(${ten_kiem_thu} PRIVATE -UNDEBUG)
        endif()

        add_test(NAME ${ten_kiem_thu} COMMAND ${ten_kiem_thu})
    endforeach()
endif()

cmake_minimum_required(VERSION 3.28)

project(super VERSION 0.0.1 DESCRIPTION "We OS")

enable_language(ASM_NASM)

set(CMAKE_CXX_STANDARD 20)

add_executable(kernel)

target_sources(kernel PUBLIC
        src/init.cxx
        src/glue/stubs.cxx
        src/glue/mem.cxx
)

target_sources(kernel
        PUBLIC
          FILE_SET CXX_MODULES FILES
        src/au/util.cxx
        src/au/types.cxx
        src/au/array.cxx
        src/au/verify.cxx
        src/framebuffer.cxx
        src/font.cxx
        src/limine.cxx
        src/kernel.cxx
)

target_compile_features(kernel PRIVATE cxx_std_20)

target_compile_options(kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX>:
        -fno-stack-check
        -fno-stack-protector
        -fno-pic
        -fno-pie
        -fno-rtti
        -fno-exceptions
        -ffreestanding
        -mabi=sysv
        -mno-80387
        -mno-mmx
        -mno-3dnow
        -mno-sse
        -mno-sse2
        -mno-ssse3
        -mno-sse4
        -mno-sse4a
        -mno-sse4.1
        -mno-sse4.2
        -mno-avx
        -mno-avx2
        -mno-avx512f
        -mno-red-zone
        -msoft-float
        -mcmodel=kernel
        -std=c++20
        >)

target_link_options(kernel PUBLIC
        -T${CMAKE_CURRENT_SOURCE_DIR}/link.ld
        -nostdlib
        -static
)

set(ISO_IMAGE ${PROJECT_NAME}.iso)

add_custom_command(OUTPUT ${ISO_IMAGE} DEPENDS kernel
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot/limine
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/iso_root/EFI/BOOT
        COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/kernel ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/limine.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot/limine
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/limine-bios.sys ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot/limine
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/limine-bios-cd.bin ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot/limine
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/limine-uefi-cd.bin ${CMAKE_CURRENT_BINARY_DIR}/iso_root/boot/limine
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/BOOTX64.EFI ${CMAKE_CURRENT_BINARY_DIR}/iso_root/EFI/BOOT
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/BOOTIA32.EFI ${CMAKE_CURRENT_BINARY_DIR}/iso_root/EFI/BOOT
        COMMAND xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label ${CMAKE_CURRENT_BINARY_DIR}/iso_root -o ${CMAKE_CURRENT_BINARY_DIR}/${ISO_IMAGE}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/subprojects/limine/limine bios-install ${CMAKE_CURRENT_BINARY_DIR}/${ISO_IMAGE}
)

add_custom_target(iso ALL DEPENDS ${ISO_IMAGE})
add_custom_target(run DEPENDS ${ISO_IMAGE} COMMAND qemu-system-x86_64 -no-reboot -no-shutdown -M q35 -m 2G -cdrom ${ISO_IMAGE})

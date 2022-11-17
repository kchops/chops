{ pkgs }: {
	deps = [
		pkgs.file
  pkgs.less
        pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
        pkgs.gcc-arm-embedded
        pkgs.cmake
        pkgs.qemu
		pkgs.gnumake
        pkgs.xorg_sys_opengl
	];
}
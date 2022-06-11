# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.195.0/containers/cpp/.devcontainer/base.Dockerfile
# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-ubuntu-21.04
USER root
RUN apt-get update \
    && apt-get -y install --no-install-recommends bzip2 cmake ninja-build doxygen clangd-12 clangd \
    && wget https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v11.2.1-1.2/xpack-arm-none-eabi-gcc-11.2.1-1.2-linux-x64.tar.gz \
    && echo "unzipping files" \
    && tar -xf xpack-arm-none-eabi-gcc-11.2.1-1.2-linux-x64.tar.gz \
    && echo "copying" \
    && ls -l \
    && cp -rf xpack-arm-none-eabi-gcc-11.2.1-1.2/* /usr/local/ \
    && echo "removing unnecessary files" \
    && rm xpack-arm-none-eabi-gcc-11.2.1-1.2-linux-x64.tar.gz \
    && rm -rf xpack-arm-none-eabi-gcc-11.2.1-1.2 \
    && ls \
    && echo "more setup" \
    && apt-get -y install --no-install-recommends openocd stlink-tools libusb-1.0-0 usbutils libusb-0.1-4 libhidapi-libusb0 libtool gdb-multiarch\
    && apt-get clean -y 
USER vscode
EXPOSE 50000
# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

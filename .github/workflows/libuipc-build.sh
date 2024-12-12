# File: libuipc-build.sh
# License: Apache v2.0

ARG=$1
if [ "$ARG" = "setup" ]; then
	ln -sf /usr/share/zoneinfo/HongKong /etc/localtime
	export DEBIAN_FRONTEND=noninteractive

	apt update
	apt-get install -y git curl zip unzip tar wget pkg-config make

	mkdir -p ~/miniconda3
	wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
	bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
	rm ~/miniconda3/miniconda.sh
	source ~/miniconda3/bin/activate
	conda install -y gcc_linux-64=11.2.0 gxx_linux-64=11.2.0 cmake=3.26 pybind11 mypy numpy nvidia/label/cuda-12.4.0::cuda-toolkit

	git clone https://github.com/microsoft/vcpkg.git $HOME/vcpkg
	cd ~/vcpkg
	./bootstrap-vcpkg.sh

elif [ "$ARG" = "compile" ]; then
	source ~/miniconda3/bin/activate ""
    export CMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
    git config --global --add safe.directory $HOME/libuipc
	mkdir ~/build
	cd ~/build
	cmake -S ../libuipc-github-actions -DUIPC_BUILD_GUI=0 -DCMAKE_BUILD_TYPE=Release
	cmake --build . -j$(nproc)
elif [ "$ARG" = "run" ]; then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/build/Release/bin
	$HOME/build/Release/bin/uipc_test_sim_case
fi

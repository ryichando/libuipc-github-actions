## ⚙️ GitHub Actions for libuipc

[![Docker](https://github.com/ryichando/libuipc-github-actions/actions/workflows/docker.yml/badge.svg)](https://github.com/ryichando/libuipc-github-actions/actions/workflows/docker.yml) [![vast-ai](https://github.com/ryichando/libuipc-github-actions/actions/workflows/vast-ai.yml/badge.svg)](https://github.com/ryichando/libuipc-github-actions/actions/workflows/vast-ai.yml)

This fork provides fully automated GitHub Action functionality for libuipc (https://github.com/spiriMirror/libuipc), delivering following benefits listed below.

### 🔧 Reliability in Build

Despite most packages being automatically installed via `vcpkg`, some libraries still need to be manually installed.
Some variables such as `CMAKE_TOOLCHAIN_FILE` also needs to be manually set.
In contrast, GitHub Actions offer high reliability and transparency during the compilation process without any user intervention.

### 🐳 Docker Sealed

The original libuipc recommends installing specific versions of GCC compilers and the NVIDIA CUDA toolkit using `conda`.
However, using `conda` can interfere with the more widely used `pip` if not managed carefully.
See [this article for example](https://www.anaconda.com/blog/using-pip-in-a-conda-environment).
Once both `conda` and `pip` are installed together, an accidental package installation can break your environment.
Encapsulating everything within a Docker container ensures greater security and better maintainability in this regard.
Here's how to run in a Docker container.
You need to install both Docker and the Docker Container Toolkit.

```bash
cd $HOME

# clone repository
git clone https://github.com/ryichando/libuipc-github-actions.git

# set variables
DOCKER_IMAGE=nvidia/cuda:12.4.0-base-ubuntu22.04
TMP_CONTAINER_NAME=libuipc
TMP_SCRIPT_PATH=/root/libuipc-github-actions/.github/workflows/libuipc-build.sh

# create a container
docker run -d -t --gpus all \
    --name $TMP_CONTAINER_NAME \
    -e NVIDIA_DRIVER_CAPABILITIES=compute,utility \
    $DOCKER_IMAGE

# copy files
docker cp $HOME/libuipc-github-actions $TMP_CONTAINER_NAME:/root/libuipc-github-actions

# setup, compile and run
docker exec $TMP_CONTAINER_NAME bash $TMP_SCRIPT_PATH /root setup
docker exec $TMP_CONTAINER_NAME bash $TMP_SCRIPT_PATH /root compile
docker exec $TMP_CONTAINER_NAME bash $TMP_SCRIPT_PATH /root run

# cleanup
docker stop $TMP_CONTAINER_NAME
docker rm $TMP_CONTAINER_NAME
```

### ☁️ [vast.ai](https://vast.ai) Support

Our GitHub Actions also support [vast.ai](https://vast.ai) instances.

> [!NOTE]
> The [libuipc documentation](https://spirimirror.github.io/libuipc-doc/build/) states that the minimum required CUDA version is 12.0, but it also specifies that conda installs version 12.4. Therefore, you need to select an instance that supports at least CUDA 12.4 or later.
> Our experience shows that selecting instances with older versions results in runtime errors.

All you need to do is create a template with `nvidia/cuda:12.4.0-base-ubuntu22.04`, provision an instance, and run

```bash
cd $HOME

# clone repository
git clone https://github.com/ryichando/libuipc-github-actions.git

# set variable
SCRIPT_PATH=$HOME/libuipc-github-actions/.github/workflows/libuipc-build.sh

bash $SCRIPT_PATH $HOME setup   # Install dependencies
bash $SCRIPT_PATH $HOME compile # Compile the library
bash $SCRIPT_PATH $HOME run     # Run a test example
```

### 🧹 Simplified Cleanup
Since everything is contained within the Docker environment, any traces left over from the installation process can be easily cleaned up.
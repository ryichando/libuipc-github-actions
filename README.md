## ⚙️ GitHub Actions for libuipc

[![Docker](https://github.com/ryichando/libuipc-github-actions/actions/workflows/docker.yml/badge.svg)](https://github.com/ryichando/libuipc-github-actions/actions/workflows/docker.yml) [![vast-ai](https://github.com/ryichando/libuipc-github-actions/actions/workflows/vast-ai.yml/badge.svg)](https://github.com/ryichando/libuipc-github-actions/actions/workflows/vast-ai.yml)

This fork provides fully automated GitHub Action functionality for libuipc (https://github.com/spiriMirror/libuipc), delivering the following benefits:

### 🔧 Reliability in Build

GitHub Actions offer high reliability and transparency during the compilation process. You do not need to carefully read through documentation to figure out which specific libraries need to be installed during the installation process.

### 🐳 Docker Sealed

The original libuipc recommends installing specific versions of GCC compilers and the NVIDIA CUDA toolkit using `conda`.
However, using `conda` can conflict with `pip` if not managed carefully. Encapsulating everything within a Docker container ensures excellent maintainability in this regard.

### ☁️ [vast.ai](https://vast.ai) Support

Our GitHub Actions also support vast.ai instances. All you need to do is create a template with `nvidia/cuda:12.4.0-base-ubuntu22.04`, provision an instance, and run

```bash
cd $HOME
git clone https://github.com/ryichando/libuipc-github-actions.git
SCRIPT_PATH=$HOME/libuipc-github-actions/.github/workflows/libuipc-build.sh
bash $SCRIPT_PATH $HOME setup   # Install dependencies
bash $SCRIPT_PATH $HOME compile # Compile the library
bash $SCRIPT_PATH $HOME run     # Run a test example
```

### 🧹 Simplified Cleanup
Since everything is contained within the Docker environment, any traces left over from the installation process can be easily cleaned up.
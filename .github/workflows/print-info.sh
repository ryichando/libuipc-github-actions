# File: print-info.sh
# License: Apache v2.0

echo '## NVIDIA Driver Info' >>$GITHUB_STEP_SUMMARY
echo '```bash' >>$GITHUB_STEP_SUMMARY
nvidia-smi >>$GITHUB_STEP_SUMMARY
echo '```' >>$GITHUB_STEP_SUMMARY

echo '## OS Info' >>$GITHUB_STEP_SUMMARY
echo '```bash' >>$GITHUB_STEP_SUMMARY
lsb_release -a >>$GITHUB_STEP_SUMMARY
echo '```' >>$GITHUB_STEP_SUMMARY

echo '## Kernel Info' >>$GITHUB_STEP_SUMMARY
echo '```bash' >>$GITHUB_STEP_SUMMARY
uname -a >>$GITHUB_STEP_SUMMARY
echo '```' >>$GITHUB_STEP_SUMMARY

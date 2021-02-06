#!/bin/bash
# Create fifo files using mknod and mkfifo commands
# save the strace info in the strace_mknod and strace_mkfifo files
strace mknod MKNOD_FIFO p 2> strace_mknod
echo "====================================================="
echo "strace of mknod command"
echo "====================================================="
tail -5 strace_mknod
strace mkfifo MKFIFO_FIFO 2> strace_mkfifo
echo "====================================================="
echo "strace of mkfifo command"
echo "====================================================="
tail -5 strace_mkfifo
# both the commands uses same call mknod to create the fifo file
gcc 19.c
strace ./a.out mkfifo MKFIFO_F 2> strace_mkfifo_a
echo "====================================================="
echo "strace mkfifo library call"
echo "====================================================="
tail -3 strace_mkfifo_a
strace ./a.out mknod MKNOD_F 2> strace_mknod_a
echo "====================================================="
echo "strace mknod system call"
echo "====================================================="
tail -3 strace_mknod_a
# here also library function mkfifo uses mknod as internal call
# so both are same
rm a.out strace_mkfifo strace_mknod strace_mkfifo_a strace_mknod_a MKFIFO_F  MKFIFO_FIFO  MKNOD_F  MKNOD_FIFO

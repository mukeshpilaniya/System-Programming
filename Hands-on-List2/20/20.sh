#!/bin/bash
mknod myfifo p
gcc reader.c -o reader
gcc writer.c -o writer
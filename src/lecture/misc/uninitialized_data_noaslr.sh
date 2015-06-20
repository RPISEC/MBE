#/bin/sh
# Note: This will drop privileges, and so can't be used for exploiting setuid binaries.
setarch $(uname -m) -R /levels/lecture/misc/uninitialized_data

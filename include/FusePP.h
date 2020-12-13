// MIT License
//
// Copyright (c) 2020 Anh-Duy Vu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
//     of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//     copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//     copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LIBFUSE_FUSEPP_H_
#define LIBFUSE_FUSEPP_H_

#define FUSE_USE_VERSION 31

#include <string>

#include <fuse.h>

using namespace std;

namespace io::github::vuanhduy::libfusepp {
class FusePP {
public:
    FusePP();
    FusePP(const FusePP&) = delete;
    FusePP(const FusePP&&) = delete;

    FusePP& operator=(const FusePP&) = delete;
    FusePP& operator=(const FusePP&&) = delete;

    int launch(int argc, char *argv[]);

    virtual int getattr(const string &, struct stat *, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int readdir(const string &, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *,
                        enum fuse_readdir_flags) {
        return -ENOSYS;
    };

    virtual int create(const string &, mode_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int open(const string &, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int read(const string &, char *, size_t, off_t, fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int write(const string &, const char *, size_t,off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

private:
    static void load_operation();
    static struct fuse_operations s_operations;

    /*
     * fuse_operations callbacks.
     */
    static int getattr_cb(const char *path, struct stat *buf, struct fuse_file_info *fi);
    static int readdir_cb(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi,
                          enum fuse_readdir_flags flags);
    static int create_cb(const char *path, mode_t mode, struct fuse_file_info *fi);
    static int open_cb(const char *path, struct fuse_file_info *fi);
    static int read_cb(const char *path, char *buf, size_t size, off_t off, fuse_file_info *fi);
    static int write_cb(const char *path, const char *buf, size_t size, off_t off, struct fuse_file_info *fi);
}; //class FusePP
}; // namespace io::github::vuanhduy::libfusepp

#endif //LIBFUSE_FUSEPP_H_

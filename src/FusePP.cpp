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

#include "FusePP.h"

using namespace std;

namespace io::github::vuanhduy::libfusepp {

struct fuse_operations FusePP::s_operations;

FusePP::FusePP() {
    load_operation();
};

void FusePP::load_operation() {
    s_operations.getattr = getattr_cb;
    s_operations.readdir = readdir_cb;
    s_operations.create = create_cb;
    s_operations.open = open_cb;
    s_operations.read = read_cb;
    s_operations.write = write_cb;
}

int FusePP::launch(int argc, char *argv[]) {
    return fuse_main(argc, argv, &s_operations, this);
}

#define GET_INSTANCE(var)      auto var = static_cast<FusePP *>(fuse_get_context()->private_data)

int FusePP::getattr_cb(const char *path, struct stat *buf, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->getattr(path, buf, fi);
}

int FusePP::readdir_cb(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi,
                       enum fuse_readdir_flags flags) {
    GET_INSTANCE(fuse);
    return fuse->readdir(path, buf, filler, off, fi, flags);
}

int FusePP::create_cb(const char *path, mode_t mode, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->create(path, mode, fi);
}

int FusePP::open_cb(const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->open(path, fi);
}

int FusePP::read_cb(const char *path, char *buf, size_t size, off_t off, fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->read(path, buf, size, off, fi);
}

int FusePP::write_cb(const char *path, const char *buf, size_t size, off_t off, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->write(path, buf, size, off, fi);
}

#undef GET_INSTANCE

}; // namespace io::github::vuanhduy::libfusepp

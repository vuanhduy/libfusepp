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

#define LOG_TAG "MyFuse"

#ifndef GLOG_logtostderr
#define GLOG_logtostderr 1
#endif

#include <cstring>
#include <algorithm>

#include <unistd.h>
#include <sys/types.h>
#include <glog/logging.h>

#include "MyFuse.h"

namespace io::github::vuanhduy::libfusepp::example {

int MyFuse::getattr(const string &path, struct stat *buf, struct fuse_file_info *) {
    memset(buf, 0, sizeof(struct stat));
    if (path == "/") {
        buf->st_mode = S_IFDIR | 0755;
        buf->st_nlink = 2;
        buf->st_gid = getgid();
        buf->st_uid = getuid();
        return EXIT_SUCCESS;
    }

    for (auto &file: m_files) {
        // ignore the beginning "/"
        if (path.substr(1) == file.name) {
            buf->st_mode = S_IFREG | 0666;
            buf->st_nlink = 1;
            buf->st_size = file.content.size();
            buf->st_gid = getgid();
            buf->st_uid = getuid();
            return EXIT_SUCCESS;
        }
    }

    return -ENOENT;
}

int MyFuse::readdir(const string &path, void *buf, fuse_fill_dir_t filler, off_t, struct fuse_file_info *,
                            enum fuse_readdir_flags) {
    // do not support subdir
    if (path != "/")
        return -ENOENT;;

    // reading the whole directory in a single call
    filler(buf, ".", nullptr, 0, (enum fuse_fill_dir_flags) 0);
    filler(buf, "..", nullptr, 0, (enum fuse_fill_dir_flags) 0);
    for (auto &file: m_files) {
        filler(buf, file.name.c_str(), nullptr, 0, (enum fuse_fill_dir_flags) 0);
    }

    return EXIT_SUCCESS;
}

int MyFuse::create(const string &path, mode_t, struct fuse_file_info *fi) {
    LOG(INFO) << "created a new file (" << path << ")";
    struct MyFuseFile new_file;
    new_file.name = path.substr(1);    // remove the beginning "/" in the path
    m_files.push_back(new_file);
    fi->fh = m_files.size() - 1;
    return EXIT_SUCCESS;
}

int MyFuse::open(const string &path, struct fuse_file_info *fi) {
    if ((fi->flags & O_ACCMODE) == O_RDONLY) {
        for (size_t i = 0; i < m_files.size(); i++) {
            if (path == m_files[i].name) {
                // Assign file handle id to accelerate read() callback
                fi->fh = i;
                return EXIT_SUCCESS;
            }
        }
    }

    LOG(ERROR) << "File system does not support write operation";
    return -EACCES;
}

int MyFuse::read(const string &, char *buf, size_t size, off_t, struct fuse_file_info *fi) {
    // Note that, we always read from the beginning of the file.
    // File handle id was assigned in open(), so we can get the file by index instead of searching
    auto file = m_files[fi->fh];
    auto len = min(file.content.size(), size);
    memcpy(buf, file.content.c_str(), len);
    return len;
}

int MyFuse::write(const string &, const char *buf, size_t size, off_t, struct fuse_file_info *fi) {
    // We allow to write to only empty files (i.e., newly created file)
    // and the write must be done in 1 transaction.
    // File handle id was assigned in create(), so we can get the file by index instead of searching
    m_files[fi->fh].content = string(buf, buf + size);
    return size;
}

} //namespace io::github::vuanhduy::libfusepp::example

using namespace io::github::vuanhduy::libfusepp::example;

// Executing command: GLOG_logtostderr=1 ./MyFuse -d -s -f <mount point>
int main(int argc, char *argv[]) {
    // Initialize Google’s logging library.
    google::InitGoogleLogging(LOG_TAG);

    MyFuse fuse;
    return fuse.launch(argc, argv);
}

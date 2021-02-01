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

#include <iostream>
using namespace std;

#include "FusePP.h"

using namespace std;

namespace me::vuanhduy::libfusepp {

struct fuse_operations FusePP::s_operations;

FusePP::FusePP() {
    load_operation();
};

void FusePP::load_operation() {
    s_operations.getattr = getattr_cb;
    s_operations.readlink = readlink_cb;
    s_operations.mknod = mknod_cb;
    s_operations.mkdir = mkdir_cb;
    s_operations.unlink = unlink_cb;
    s_operations.rmdir = rmdir_cb;
    s_operations.symlink = symlink_cb;
    s_operations.rename = rename_cb;
    s_operations.link = link_cb;
    s_operations.chmod = chmod_cb;
    s_operations.chown = chown_cb;
    s_operations.truncate = truncate_cb;
    s_operations.open = open_cb;
    s_operations.read = read_cb;
    s_operations.write = write_cb;
    s_operations.statfs = statfs_cb;
    s_operations.flush = flush_cb;
    s_operations.release = release_cb;
    s_operations.fsync = fsync_cb;
    s_operations.setxattr = setxattr_cb;
    s_operations.getxattr = getxattr_cb;
    s_operations.listxattr = listxattr_cb;
    s_operations.removexattr = removexattr_cb;
    s_operations.opendir = opendir_cb;
    s_operations.readdir = readdir_cb;
    s_operations.releasedir = releasedir_cb;
    s_operations.fsyncdir = fsyncdir_cb;
    s_operations.init = init_cb;
    s_operations.destroy = destroy_cb;
    s_operations.access = access_cb;
    s_operations.create = create_cb;
    s_operations.lock = lock_cb;
    s_operations.utimens = utimens_cb;
    s_operations.bmap = bmap_cb;
    s_operations.ioctl = ioctl_cb;
    s_operations.poll = poll_cb;
    s_operations.flock = flock_cb;
    s_operations.fallocate = fallocate_cb;
    s_operations.copy_file_range = copy_file_range_cb;
    s_operations.lseek = lseek_cb;
}

int FusePP::launch(int argc, char *argv[]) {
    return fuse_main(argc, argv, &s_operations, this);
}

#define INSTANCE_CALL(func, ...)    auto fuse = static_cast<FusePP *>(fuse_get_context()->private_data); \
                                    return fuse->func(__VA_ARGS__)

int FusePP::getattr_cb(const char *path, struct stat *buf, struct fuse_file_info *fi) {
    INSTANCE_CALL(getattr, path, buf, fi);
}

int FusePP::readlink_cb (const char *path, char *buf, size_t size) {
    INSTANCE_CALL(readlink, path, buf, size);
}

int FusePP::mknod_cb (const char *path, mode_t mode, dev_t dev) {
    INSTANCE_CALL(mknod, path, mode, dev);
}

int FusePP::mkdir_cb (const char *path, mode_t mode) {
    INSTANCE_CALL(mkdir, path, mode);
}

int FusePP::unlink_cb (const char *path) {
    INSTANCE_CALL(unlink, path);
}

int FusePP::rmdir_cb (const char *path) {
    INSTANCE_CALL(rmdir, path);
}

int FusePP::symlink_cb (const char *target, const char *link) {
    INSTANCE_CALL(symlink, target, link);
}

int FusePP::rename_cb (const char *old_path, const char *new_path, unsigned int flags) {
    INSTANCE_CALL(rename, old_path, new_path, flags);
}

int FusePP::link_cb (const char *old_path, const char *new_path) {
    INSTANCE_CALL(link, old_path, new_path);
}

int FusePP::chmod_cb (const char *path, mode_t mode, struct fuse_file_info *fi) {
    INSTANCE_CALL(chmod, path, mode, fi);
}

int FusePP::chown_cb (const char *path, uid_t uid, gid_t gid, struct fuse_file_info *fi) {
    INSTANCE_CALL(chown, path, uid, gid, fi);
}

int FusePP::truncate_cb (const char *path, off_t off, struct fuse_file_info *fi) {
    INSTANCE_CALL(truncate, path, off, fi);
}

int FusePP::open_cb (const char *path, struct fuse_file_info *fi) {
    INSTANCE_CALL(open, path, fi);
}

int FusePP::read_cb (const char *path, char *buf, size_t size, off_t off, struct fuse_file_info *fi) {
    INSTANCE_CALL(read, path, buf, size, off, fi);
}

int FusePP::write_cb (const char *path, const char *buf, size_t size, off_t off, struct fuse_file_info *fi) {
    cout << "Test";
    INSTANCE_CALL(write, path, buf, size, off, fi);
}

int FusePP::statfs_cb (const char *path, struct statvfs *buf) {
    INSTANCE_CALL(statfs, path, buf);
}

int FusePP::flush_cb (const char *path, struct fuse_file_info *fi) {
    INSTANCE_CALL(flush, path, fi);
}

int FusePP::release_cb (const char *path, struct fuse_file_info *fi) {
    INSTANCE_CALL(release, path, fi);
}

int FusePP::fsync_cb (const char *path, int datasync, struct fuse_file_info *fi) {
    INSTANCE_CALL(fsync, path, datasync, fi);
}

int FusePP::setxattr_cb (const char *path, const char *name, const char *value, size_t size, int flags) {
    INSTANCE_CALL(setxattr, path, name, value, size, flags);
}

int FusePP::getxattr_cb (const char *path, const char *name, char *value, size_t size) {
    INSTANCE_CALL(getxattr, path, name, value, size);
}

int FusePP::listxattr_cb (const char *path, char *list, size_t size) {
    INSTANCE_CALL(listxattr, path, list, size);
}

int FusePP::removexattr_cb (const char *path, const char *name) {
    INSTANCE_CALL(removexattr, path, name);
}

int FusePP::opendir_cb (const char *path, struct fuse_file_info *fi) {
    INSTANCE_CALL(opendir, path, fi);
}

int FusePP::readdir_cb(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi,
                       enum fuse_readdir_flags flags) {
    INSTANCE_CALL(readdir, path, buf, filler, off, fi, flags);
}

int FusePP::releasedir_cb (const char *path, struct fuse_file_info *fi) {
    INSTANCE_CALL(releasedir, path, fi);
}
int FusePP::fsyncdir_cb (const char *path, int datasync, struct fuse_file_info *fi) {
    INSTANCE_CALL(fsyncdir, path, datasync, fi);
}

void *FusePP::init_cb (struct fuse_conn_info *fi, struct fuse_config *cf) {
    INSTANCE_CALL(init, fi, cf);
}

void FusePP::destroy_cb (void *private_data) {
    INSTANCE_CALL(destroy, private_data);
}

int FusePP::access_cb (const char *path, int mask) {
    INSTANCE_CALL(access, path, mask);
}

int FusePP::create_cb (const char *path, mode_t mode, struct fuse_file_info *fi) {
    INSTANCE_CALL(create, path, mode, fi);
}

int FusePP::lock_cb (const char *path, struct fuse_file_info *fi, int cmd, struct flock *lock) {
    INSTANCE_CALL(lock, path, fi, cmd, lock);
}

int FusePP::utimens_cb (const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    INSTANCE_CALL(utimens, path, tv, fi);
}

int FusePP::bmap_cb (const char *path, size_t blocksize, uint64_t *idx) {
    INSTANCE_CALL(bmap, path, blocksize, idx);
}

#if defined ANDROID || FUSE_USE_VERSION > 35
int FusePP::ioctl_cb (const char *path, unsigned int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) {
#else
int FusePP::ioctl_cb (const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) {
#endif
    INSTANCE_CALL(ioctl, path, cmd, arg, fi, flags, data);
}

int FusePP::poll_cb (const char *path, struct fuse_file_info *fi, struct fuse_pollhandle *ph, unsigned *reventsp) {
    INSTANCE_CALL(poll, path, fi, ph, reventsp);
}

int FusePP::flock_cb (const char *path, struct fuse_file_info *fi, int op) {
    INSTANCE_CALL(flock, path, fi, op);
}

int FusePP::fallocate_cb (const char *path, int mode, off_t off, off_t length, struct fuse_file_info *fi) {
    INSTANCE_CALL(fallocate, path, mode, off, length, fi);
}

ssize_t FusePP::copy_file_range_cb (const char *path_in, struct fuse_file_info *fi_in, off_t off_in, const char *path_out,
                                    struct fuse_file_info *fi_out, off_t off_out, size_t size, int flags) {
    INSTANCE_CALL(copy_file_range, path_in, fi_in, off_in, path_out, fi_out, off_out, size, flags);
}

off_t FusePP::lseek_cb (const char *path, off_t off, int whence, struct fuse_file_info *fi) {
    INSTANCE_CALL(lseek, path, off, whence, fi);
}

#undef INSTANCE_CALL

}; // namespace me::vuanhduy::libfusepp

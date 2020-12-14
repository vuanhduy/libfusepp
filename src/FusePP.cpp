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
    s_operations.write_buf = write_buf_cb;
    s_operations.read_buf = read_buf_cb;
    s_operations.flock = flock_cb;
    s_operations.fallocate = fallocate_cb;
    s_operations.copy_file_range = copy_file_range_cb;
    s_operations.lseek = lseek_cb;
}

int FusePP::launch(int argc, char *argv[]) {
    return fuse_main(argc, argv, &s_operations, this);
}

#define GET_INSTANCE(var)      auto var = static_cast<FusePP *>(fuse_get_context()->private_data)

int FusePP::getattr_cb(const char *path, struct stat *buf, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->getattr(path, buf, fi);
}

int FusePP::readlink_cb (const char *path, char *buf, size_t size) {
    GET_INSTANCE(fuse);
    return fuse->readlink(path, buf, size);
}

int FusePP::mknod_cb (const char *path, mode_t mode, dev_t dev) {
    GET_INSTANCE(fuse);
    return fuse->mknod(path, mode, dev);
}

int FusePP::mkdir_cb (const char *path, mode_t mode) {
    GET_INSTANCE(fuse);
    return fuse->mkdir(path, mode);
}

int FusePP::unlink_cb (const char *path) {
    GET_INSTANCE(fuse);
    return fuse->unlink(path);
}

int FusePP::rmdir_cb (const char *path) {
    GET_INSTANCE(fuse);
    return fuse->rmdir(path);
}

int FusePP::symlink_cb (const char *target, const char *link) {
    GET_INSTANCE(fuse);
    return fuse->symlink(target, link);
}

int FusePP::rename_cb (const char *old_path, const char *new_path, unsigned int flags) {
    GET_INSTANCE(fuse);
    return fuse->rename(old_path, new_path, flags);
}

int FusePP::link_cb (const char *old_path, const char *new_path) {
    GET_INSTANCE(fuse);
    return fuse->link(old_path, new_path);
}

int FusePP::chmod_cb (const char *path, mode_t mode, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->chmod(path, mode, fi);
}

int FusePP::chown_cb (const char *path, uid_t uid, gid_t gid, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->chown(path, uid, gid, fi);
}

int FusePP::truncate_cb (const char *path, off_t off, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->truncate(path, off, fi);
}

int FusePP::open_cb (const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->open(path, fi);
}

int FusePP::read_cb (const char *path, char *buf, size_t size, off_t off, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->read(path, buf, size, off, fi);
}

int FusePP::write_cb (const char *path, const char *buf, size_t size, off_t off, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->write(path, buf, size, off, fi);
}

int FusePP::statfs_cb (const char *path, struct statvfs *buf) {
    GET_INSTANCE(fuse);
    return fuse->statfs(path, buf);
}

int FusePP::flush_cb (const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->flush(path, fi);
}

int FusePP::release_cb (const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->release(path, fi);
}

int FusePP::fsync_cb (const char *path, int datasync, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->fsync(path, datasync, fi);
}

int FusePP::setxattr_cb (const char *path, const char *name, const char *value, size_t size, int flags) {
    GET_INSTANCE(fuse);
    return fuse->setxattr(path, name, value, size, flags);
}

int FusePP::getxattr_cb (const char *path, const char *name, char *value, size_t size) {
    GET_INSTANCE(fuse);
    return fuse->getxattr(path, name, value, size);
}

int FusePP::listxattr_cb (const char *path, char *list, size_t size) {
    GET_INSTANCE(fuse);
    return fuse->listxattr(path, list, size);
}

int FusePP::removexattr_cb (const char *path, const char *name) {
    GET_INSTANCE(fuse);
    return fuse->removexattr(path, name);
}

int FusePP::opendir_cb (const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->opendir(path, fi);
}

int FusePP::readdir_cb(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi,
                       enum fuse_readdir_flags flags) {
    GET_INSTANCE(fuse);
    return fuse->readdir(path, buf, filler, off, fi, flags);
}

int FusePP::releasedir_cb (const char *path, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse-> releasedir(path, fi);
}
int FusePP::fsyncdir_cb (const char *path, int datasync, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->fsyncdir(path, datasync, fi);
}

void *FusePP::init_cb (struct fuse_conn_info *fi, struct fuse_config *cf) {
    GET_INSTANCE(fuse);
    return fuse->init(fi, cf);
}

void FusePP::destroy_cb (void *private_data) {
    GET_INSTANCE(fuse);
    return fuse->destroy(private_data);
}

int FusePP::access_cb (const char *path, int mask) {
    GET_INSTANCE(fuse);
    return fuse->access(path, mask);
}

int FusePP::create_cb (const char *path, mode_t mode, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->create(path, mode, fi);
}

int FusePP::lock_cb (const char *path, struct fuse_file_info *fi, int cmd, struct flock *lock) {
    GET_INSTANCE(fuse);
    return fuse->lock(path, fi, cmd, lock);
}

int FusePP::utimens_cb (const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->utimens(path, tv, fi);
}

int FusePP::bmap_cb (const char *path, size_t blocksize, uint64_t *idx) {
    GET_INSTANCE(fuse);
    return fuse->bmap(path, blocksize, idx);
}

#if FUSE_USE_VERSION < 35
int FusePP::ioctl_cb (const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) {
#else
int FusePP::ioctl_cb (const char *path, unsigned int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) {
#endif
    GET_INSTANCE(fuse);
    return fuse->ioctl(path, cmd, arg, fi, flags, data);
}

int FusePP::poll_cb (const char *path, struct fuse_file_info *fi, struct fuse_pollhandle *ph, unsigned *reventsp) {
    GET_INSTANCE(fuse);
    return fuse->poll(path, fi, ph, reventsp);
}

int FusePP::write_buf_cb (const char *path, struct fuse_bufvec *buf, off_t off, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->write_buf(path, buf, off, fi);
}

int FusePP::read_buf_cb (const char *path, struct fuse_bufvec **buf, size_t size, off_t off,
                         struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->read_buf(path, buf, size, off, fi);
}

int FusePP::flock_cb (const char *path, struct fuse_file_info *fi, int op) {
    GET_INSTANCE(fuse);
    return fuse->flock(path, fi, op);
}

int FusePP::fallocate_cb (const char *path, int mode, off_t off, off_t length, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->fallocate(path, mode, off, length, fi);
}

ssize_t FusePP::copy_file_range_cb (const char *path_in, struct fuse_file_info *fi_in, off_t off_in, const char *path_out,
                                    struct fuse_file_info *fi_out, off_t off_out, size_t size, int flags) {
    GET_INSTANCE(fuse);
    return fuse->copy_file_range(path_in, fi_in, off_in, path_out, fi_out, off_out, size, flags);
}

off_t FusePP::lseek_cb (const char *path, off_t off, int whence, struct fuse_file_info *fi) {
    GET_INSTANCE(fuse);
    return fuse->lseek_cb(path, off, whence, fi);
}

#undef GET_INSTANCE

}; // namespace io::github::vuanhduy::libfusepp

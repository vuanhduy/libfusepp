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
    FusePP (const FusePP&) = delete;
    FusePP (const FusePP&&) = delete;

    FusePP& operator= (const FusePP&) = delete;
    FusePP& operator= (const FusePP&&) = delete;

    int launch(int argc, char *argv[]);

    virtual int getattr(const string &, struct stat *, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int readlink (const string &, char *, size_t) {
        return -ENOSYS;
    };

    virtual int mknod (const string &,  mode_t, dev_t) {
        return -ENOSYS;
    };

    virtual int mkdir (const string &,  mode_t) {
        return -ENOSYS;
    };

    virtual int unlink (const char *) {
        return -ENOSYS;
    };

    virtual int rmdir (const char *) {
        return -ENOSYS;
    };

    virtual int symlink (const string &,  const char *) {
        return -ENOSYS;
    };

    virtual int rename (const string &,  const char *, unsigned int) {
        return -ENOSYS;
    };

    virtual int link (const string &,  const char *) {
        return -ENOSYS;
    };

    virtual int chmod (const string &,  mode_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int chown (const string &,  uid_t, gid_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int truncate (const string &,  off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int open (const string &, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int read (const string &, char *, size_t, off_t, fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int write (const string &, const char *, size_t,off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int statfs (const string &, struct statvfs *) {
        return -ENOSYS;
    };

    virtual int flush (const string &, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int release (const string &,  struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int fsync (const string &,  int, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int setxattr (const string &,  const char *, const char *, size_t, int) {
        return -ENOSYS;
    };

    virtual int getxattr (const string &,  const char *, char *, size_t) {
        return -ENOSYS;
    };

    virtual int listxattr (const string &,  char *, size_t) {
        return -ENOSYS;
    };

    virtual int removexattr (const string &,  const char *) {
        return -ENOSYS;
    };

    virtual int opendir (const string &,  struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int readdir(const string &,  void *, fuse_fill_dir_t, off_t, struct fuse_file_info *, enum fuse_readdir_flags) {
        return -ENOSYS;
    };

    virtual int releasedir (const string &,  struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int fsyncdir (const string &,  int, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual void *init (struct fuse_conn_info *, struct fuse_config *) {
        return nullptr;
    };

    virtual void destroy (void *) {};

    virtual int access (const string &, int) {
        return -ENOSYS;
    };

    virtual int create (const string &, mode_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int lock (const string &, struct fuse_file_info *, int, struct flock *) {
        return -ENOSYS;
    };

    virtual int utimens (const string &, const struct timespec [2], struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int bmap (const string &,  size_t, uint64_t *) {
        return -ENOSYS;
    };

#if FUSE_USE_VERSION < 35
    virtual int ioctl (const string &,  int, void *, struct fuse_file_info *, unsigned int, void *) {
#else
    virtual int ioctl (const string &,  unsigned int, void *, struct fuse_file_info *, unsigned int, void *) {
#endif
        return -ENOSYS;
    };

    virtual int poll (const string &,  struct fuse_file_info *, struct fuse_pollhandle *, unsigned *) {
        return -ENOSYS;
    };

    virtual int write_buf (const string &,  struct fuse_bufvec *, off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int read_buf (const string &,  struct fuse_bufvec **, size_t, off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual int flock (const string &,  struct fuse_file_info *, int) {
        return -ENOSYS;
    };

    virtual int fallocate (const string &,  int, off_t, off_t, struct fuse_file_info *) {
        return -ENOSYS;
    };

    virtual ssize_t copy_file_range (const string &,  struct fuse_file_info *, off_t, const char *,
                                     struct fuse_file_info *, off_t, size_t, int) {
        return -ENOSYS;
    };

    virtual off_t lseek_cb (const string &,  off_t, int, struct fuse_file_info *) {
      return -ENOSYS;
    };

private:
    static void load_operation();
    static struct fuse_operations s_operations;

    /*
     * fuse_operations callbacks.
     */
    static int getattr_cb (const char *, struct stat *, struct fuse_file_info *);
    static int readlink_cb (const char *, char *, size_t);
    static int mknod_cb (const char *, mode_t, dev_t);
    static int mkdir_cb (const char *, mode_t);
    static int unlink_cb (const char *);
    static int rmdir_cb (const char *);
    static int symlink_cb (const char *, const char *);
    static int rename_cb (const char *, const char *, unsigned int);
    static int link_cb (const char *, const char *);
    static int chmod_cb (const char *, mode_t, struct fuse_file_info *);
    static int chown_cb (const char *, uid_t, gid_t, struct fuse_file_info *);
    static int truncate_cb (const char *, off_t, struct fuse_file_info *);
    static int open_cb (const char *, struct fuse_file_info *);
    static int read_cb (const char *, char *, size_t, off_t, struct fuse_file_info *);
    static int write_cb (const char *, const char *, size_t, off_t, struct fuse_file_info *);
    static int statfs_cb (const char *, struct statvfs *);
    static int flush_cb (const char *, struct fuse_file_info *);
    static int release_cb (const char *, struct fuse_file_info *);
    static int fsync_cb (const char *, int, struct fuse_file_info *);
    static int setxattr_cb (const char *, const char *, const char *, size_t, int);
    static int getxattr_cb (const char *, const char *, char *, size_t);
    static int listxattr_cb (const char *, char *, size_t);
    static int removexattr_cb (const char *, const char *);
    static int opendir_cb (const char *, struct fuse_file_info *);
    static int readdir_cb(const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *, enum fuse_readdir_flags);
    static int releasedir_cb (const char *, struct fuse_file_info *);
    static int fsyncdir_cb (const char *, int, struct fuse_file_info *);
    static void *init_cb (struct fuse_conn_info *, struct fuse_config *);
    static void destroy_cb (void *);
    static int access_cb (const char *, int);
    static int create_cb (const char *, mode_t, struct fuse_file_info *);
    static int lock_cb (const char *, struct fuse_file_info *, int, struct flock *);
    static int utimens_cb (const char *, const struct timespec tv[2], struct fuse_file_info *);
    static int bmap_cb (const char *, size_t, uint64_t *);
#if FUSE_USE_VERSION < 35
    static int ioctl_cb (const char *, int, void *, struct fuse_file_info *, unsigned int, void *);
#else
    static int ioctl_cb (const char *, unsigned int, void *, struct fuse_file_info *, unsigned int, void *);
#endif
    static int poll_cb (const char *, struct fuse_file_info *, struct fuse_pollhandle *, unsigned *);
    static int write_buf_cb (const char *, struct fuse_bufvec *, off_t, struct fuse_file_info *);
    static int read_buf_cb (const char *, struct fuse_bufvec **, size_t, off_t, struct fuse_file_info *);
    static int flock_cb (const char *, struct fuse_file_info *, int);
    static int fallocate_cb (const char *, int, off_t, off_t, struct fuse_file_info *);
    static ssize_t copy_file_range_cb (const char *, struct fuse_file_info *, off_t, const char *,
                                       struct fuse_file_info *, off_t, size_t, int);
    static off_t lseek_cb (const char *, off_t, int, struct fuse_file_info *);
}; //class FusePP
}; // namespace io::github::vuanhduy::libfusepp

#endif //LIBFUSE_FUSEPP_H_

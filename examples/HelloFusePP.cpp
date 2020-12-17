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
#include <cstring>
#include <string>
#include <algorithm>

#include <unistd.h>
#include <sys/types.h>
#include <glog/logging.h>

#include "HelloFusePP.h"

using namespace std;
namespace io::github::vuanhduy::libfusepp::example {

/*
 * Command line options
 *
 * We can't set default values for the char* fields here because
 * fuse_opt_parse would attempt to free() them when the user specifies
 * different values on the command line.
 */
static struct options {
  const char *filename;
  const char *contents;
  int show_help;
} options;

#define OPTION(t, p)                           \
    { t, offsetof(struct options, p), 1 }
static const struct fuse_opt option_spec[] = {
    OPTION("--name=%s", filename),
    OPTION("--contents=%s", contents),
    OPTION("-h", show_help),
    OPTION("--help", show_help),
    FUSE_OPT_END
};

void *HelloFusePP::init(struct fuse_conn_info *, struct fuse_config *cfg) {
    cfg->kernel_cache = 1;
    return this;
}

int HelloFusePP::getattr(const string &path, struct stat *buf, struct fuse_file_info *) {
    int res = 0;

    memset(buf, 0, sizeof(struct stat));
    if (path == "/") {
        buf->st_mode = S_IFDIR | 0755;
        buf->st_nlink = 2;
    } else if ( path.substr(1) == options.filename) {
        buf->st_mode = S_IFREG | 0444;
        buf->st_nlink = 1;
        buf->st_size = strlen(options.contents);
    } else
        res = -ENOENT;

    return res;
}

int HelloFusePP::readdir(const string &path, void *buf, fuse_fill_dir_t filler,
                  off_t, struct fuse_file_info *, enum fuse_readdir_flags) {
    if (path != "/")
        return -ENOENT;

    filler(buf, ".", NULL, 0, (enum fuse_fill_dir_flags)0);
    filler(buf, "..", NULL, 0, (enum fuse_fill_dir_flags)0);
    filler(buf, options.filename, NULL, 0, (enum fuse_fill_dir_flags)0);

    return 0;
}

int HelloFusePP::open(const string &path, struct fuse_file_info *fi) {
    if (path.substr(1) != options.filename)
        return -ENOENT;

    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;

    return 0;
}

int HelloFusePP::read(const string &path, char *buf, size_t size, off_t offset, struct fuse_file_info *) {
    size_t len;
    if (path.substr(1) != options.filename)
        return -ENOENT;

    len = strlen(options.contents);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, options.contents + offset, size);
    } else
        size = 0;

    return size;
}

} // namespace io::github::vuanhduy::libfusepp::example

using namespace io::github::vuanhduy::libfusepp::example;

static void show_help(const char *progname)
{
    cout << "usage: " << progname << " [options] <mountpoint>\n\n";
    cout << "File-system specific options:\n"
           "    --name=<s>          Name of the \"hello\" file\n"
           "                        (default: \"hello\")\n"
           "    --contents=<s>      Contents \"hello\" file\n"
           "                        (default \"Hello, World!\\n\")\n"
           "\n";
}

// Executing command: GLOG_logtostderr=1 ./MyFuse -d -s -f <mount point>
int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    /* Set defaults -- we have to use strdup so that
	   fuse_opt_parse can free the defaults if other
	   values are specified */
    options.filename = strdup("hello");
    options.contents = strdup("Hello World!\n");

    /* Parse options */
    if (fuse_opt_parse(&args, &options, option_spec, nullptr) == -1)
        return 1;

    /* When --help is specified, first print our own file-system
	   specific help text, then signal fuse_main to show
	   additional help (by adding `--help` to the options again)
	   without usage: line (by setting argv[0] to the empty
	   string) */
    if (options.show_help) {
        show_help(argv[0]);
        CHECK(fuse_opt_add_arg(&args, "--help") == 0);
        args.argv[0][0] = '\0';
    }

    HelloFusePP fuse;
    int ret = fuse.launch(args.argc, args.argv);
    fuse_opt_free_args(&args);
    return ret;
}

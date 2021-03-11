// MIT License
//
// Copyright (c) 2020 Anh-Duy Vu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LIBFUSEPP_EXAMPLES_HELLOFUSEPP_H_
#define LIBFUSEPP_EXAMPLES_HELLOFUSEPP_H_

#include <string>
#include "FusePP.h"

namespace me::vuanhduy::libfusepp::example {
class HelloFusePP: public FusePP {
public:
    HelloFusePP() : FusePP() {}

private:
    void *init(struct fuse_conn_info *, struct fuse_config *) override;
    int getattr(const std::string &, struct stat *,
                struct fuse_file_info *) override;
    int readdir(const std::string &, void *, fuse_fill_dir_t, off_t,
                struct fuse_file_info *, enum fuse_readdir_flags) override;
    int open(const std::string &, struct fuse_file_info *) override;
    int read(const std::string &, char *, size_t, off_t,
             struct fuse_file_info *) override;
};  // class HelloFusePP
}   // namespace me::vuanhduy::libfusepp::example
#endif  // LIBFUSEPP_EXAMPLES_HELLOFUSEPP_H_

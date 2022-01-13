#ifndef __INCLUDE_MEMOIZE_H__
#define __INCLUDE_MEMOIZE_H__

// MIT License

// Copyright (c) 2021 Debashish Ghosh

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <functional>
#include <map>

template <typename R, typename... Args>
class memoize_f : public std::function<R(Args...)>
{
public:
  using Callable = std::function<R(Args...)>;

  memoize_f(Callable func, std::size_t maxSize = 0)
      : target(func), max_size(maxSize)
  {
  }

  R operator()(Args &&...args)
  {
    auto iter = cache.find(std::tie(args...));
    if (iter == cache.end())
    {
      std::tie(iter, std::ignore) = cache.emplace(std::make_tuple(std::forward<Args>(args)...), target(args...));
    }
    return iter->second;
  }

private:
  std::size_t max_size;
  std::map<std::tuple<Args...>, R> cache;
  Callable target;
};

#endif /* __INCLUDE_MEMOIZE_H__ */

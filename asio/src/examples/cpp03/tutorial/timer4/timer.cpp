//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class printer
{
public:
  printer(asio::io_context& io)
    : timer_(io, boost::posix_time::seconds(1)),
      count_(0)
  {
    timer_.async_wait(boost::bind(&printer::print, this));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print()
  {
    if (count_ < 5)
    {
      std::cout << count_ << std::endl;
      ++count_;

      timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
      timer_.async_wait(boost::bind(&printer::print, this));
    }
  }

private:
  asio::deadline_timer timer_;
  int count_;
};

int main()
{
  asio::io_context io;
  printer p(io);
  io.run();

  return 0;
}

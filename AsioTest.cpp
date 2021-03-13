//
// Created by skamath on 13/03/21.
//

#include <iostream>
#include "gtest/gtest.h"
#include "boost/asio.hpp"

using namespace std;
namespace asio = boost::asio;

TEST(Asio, syncTimer) {
    cout << "Asio sync start" << endl;

    asio::io_context ioc;
    asio::steady_timer t(ioc, asio::chrono::seconds(2));
    t.wait();

    cout << "Asio sync end" << endl;
}

TEST(Asio, asyncTimer) {
    cout << "Asio async start" << endl;

    asio::io_context ioc;
    asio::steady_timer t(ioc, asio::chrono::seconds(2));

    t.async_wait([](const boost::system::error_code &ec) {
        cout << "done" << endl;
    });

    ioc.run();

    cout << "Asio async end" << endl;
}

TEST(Asio, asyncTimerTick) {
    int tick = 0;
    cout << "Asio async start" << endl;

    asio::io_context ioc;
    asio::steady_timer t(ioc, asio::chrono::seconds(1));

    std::function<void(const boost::system::error_code)> handler =
            [&t, &tick, &handler](const boost::system::error_code &ec) {
                tick++;
                cout << "tick: " << tick << endl;
                if (tick < 5) {
                    t.expires_at(t.expiry() + boost::asio::chrono::seconds(1));
                    t.async_wait(handler);
                }
            };

    t.async_wait(handler);

    ioc.run();

    cout << "Asio async end" << endl;
}

typedef std::function<void(const boost::system::error_code)> handler_t;

class Ticker {
public:
    explicit Ticker(asio::io_context &ioc) :
            _timer(ioc, asio::chrono::seconds(1)),
            _count(0) {

        _handler = [this](const boost::system::error_code &ec) {
            if (tick()) {
                _timer.expires_at(_timer.expiry() + boost::asio::chrono::seconds(1));
                _timer.async_wait(_handler);
            }
        };

        _timer.async_wait(_handler);
    }

    bool tick() {
        _count++;
        cout << "tick: " << _count << endl;
        return _count < 5;
    }

private:
    asio::steady_timer _timer;
    int _count;
    // without handler being member variable I see an crash
    // it is because lambda has to be captured by reference
    // I am not sure if there is a better workaround
    handler_t _handler;
};

TEST(Asio, Ticker) {
    asio::io_context ioc;
    Ticker t(ioc);
    ioc.run();
}

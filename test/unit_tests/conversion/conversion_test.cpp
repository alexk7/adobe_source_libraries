/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/*************************************************************************************************/

#include <adobe/config.hpp>

#include <functional>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <adobe/conversion.hpp>

/*************************************************************************************************/

namespace {

struct base {
    virtual ~base() {}
};
struct derived : base {};
struct not_derived {};
struct other_derived : base {};

} // namespace


void conversion_test() {
    using adobe::runtime_cast;

    {
        base* x = new derived;
        BOOST_CHECK(runtime_cast<derived*>(x));
        BOOST_CHECK(runtime_cast<const derived*>(x));
        // BOOST_CHECK(runtime_cast<not_derived*>(x));

        BOOST_CHECK(runtime_cast<other_derived*>(x) == 0);

        runtime_cast<derived&>(*x) = derived();
    }

    {
        const base* x = new derived;
        // BOOST_CHECK(runtime_cast<derived*>(x));
        BOOST_CHECK(runtime_cast<const derived*>(x));
        derived y = runtime_cast<const derived&>(*x);
    }
}

using namespace boost::unit_test;

test_suite* init_unit_test_suite(int, char * []) {
    framework::master_test_suite().add(BOOST_TEST_CASE(&conversion_test));

    return 0;
}

#define BOOST_TEST_MODULE bitvec

#include <bitvec/bitvec.hpp>
#include <vector>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(initilize1)
{
    bitvec::bitvec<std::vector> bv;
    BOOST_CHECK(bv.empty());
}

BOOST_AUTO_TEST_CASE(initilize2)
{
    bitvec::bitvec<std::vector> bv(65);
    BOOST_CHECK_EQUAL(bv.size(), 65);
}

BOOST_AUTO_TEST_CASE(random_access)
{
    bitvec::bitvec<std::vector> bv;
    bv.push_back(0);
    bv.push_back(1);
    bv.push_back(1);
    BOOST_CHECK_EQUAL(*bv[0], 0);
    BOOST_CHECK_EQUAL(*bv[1], 1);
    BOOST_CHECK_EQUAL(*bv[2], 1);
    BOOST_CHECK(!bv[100]);
}

BOOST_AUTO_TEST_CASE(push_back)
{
    bitvec::bitvec<std::vector> bv;
    bv.push_back(0);
    bv.push_back(1);
    bv.push_back(1);
    BOOST_CHECK_EQUAL(bv.size(), 3);
    BOOST_CHECK_EQUAL(*bv.get_nth_block(0), 0x6ULL);
    BOOST_CHECK(!bv.get_nth_block(100));
}

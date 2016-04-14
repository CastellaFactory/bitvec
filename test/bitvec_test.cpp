#define BOOST_TEST_MODULE bitvec

#include <bitvec/bitvec.hpp>
#include <boost/container/vector.hpp>
#include <boost/mpl/list.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <vector>

using bitvec_types = boost::mpl::list<bitvec::bitvec<std::vector>,
                                      bitvec::bitvec<boost::container::vector>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(initilize1, T, bitvec_types)
{
    T bv;
    BOOST_CHECK(bv.empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(initilize2, T, bitvec_types)
{
    T bv(65);
    BOOST_CHECK_EQUAL(bv.size(), 65);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(random_access, T, bitvec_types)
{
    T bv;
    bv.push_back(0);
    bv.push_back(1);
    bv.push_back(1);
    BOOST_CHECK_EQUAL(*bv[0], 0);
    BOOST_CHECK_EQUAL(*bv[1], 1);
    BOOST_CHECK_EQUAL(*bv[2], 1);
    BOOST_CHECK(!bv[100]);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(push_back, T, bitvec_types)
{
    T bv;
    bv.push_back(0);
    bv.push_back(1);
    bv.push_back(1);
    BOOST_CHECK_EQUAL(bv.size(), 3);
    BOOST_CHECK_EQUAL(*bv.get_nth_block(0), 0x6ULL);
    BOOST_CHECK(!bv.get_nth_block(100));
}

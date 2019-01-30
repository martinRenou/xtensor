/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xoptional_assembly_operation.hpp"

#include "test_common.hpp"

namespace xt
{
    using array_type = xarray<int>;
    using flag_array_type = xarray<bool>;
    using opt_ass_type = xoptional_assembly<array_type, flag_array_type>;
    using cm_opt_ass_type = xoptional_assembly<xarray<int, layout_type::column_major>, xarray<bool, layout_type::column_major>>;
    using dyn_opt_ass_type = xoptional_assembly<xarray<int, layout_type::dynamic>, xarray<bool, layout_type::dynamic>>;

    TEST(xoptional_assembly_operation, fillna)
    {
        auto missing = xtl::missing<int>();
        opt_ass_type a = {{0, missing, 2}, {missing, 32, 1}};
        auto b = fillna(a, 2);
        // std::cout << "Access " << b(1, 0) << std::endl;
        std::cout << b << std::endl;
    }
}

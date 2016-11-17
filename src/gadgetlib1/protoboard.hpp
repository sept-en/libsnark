/** @file
 *****************************************************************************
 * @author     This file is part of libsnark, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef PROTOBOARD_HPP_
#define PROTOBOARD_HPP_

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include "gadgetlib1/pb_variable.hpp"
#include "relations/constraint_satisfaction_problems/r1cs/r1cs.hpp"
#include "common/utils.hpp"

namespace libsnark {

template<typename FieldT>
class r1cs_constraint;

template<typename FieldT>
class r1cs_constraint_system;

template<typename FieldT>
class protoboard {
private:
    FieldT constant_term; /* only here, because pb.val() needs to be able to return reference to the constant 1 term */
    r1cs_variable_assignment<FieldT> values; /* values[0] will hold the value of the first allocated variable of the protoboard, *NOT* constant 1 */

    size_t next_free_variable_index;
    size_t next_free_linear_combination_index;

    std::vector<FieldT> linear_combination_values;
    r1cs_constraint_system<FieldT> constraint_system;

public:
    protoboard();

    void clear_values();

    FieldT& val(const pb_variable<FieldT> &var);
    FieldT val(const pb_variable<FieldT> &var) const;

    FieldT& lc_val(const pb_linear_combination<FieldT> &lc);
    FieldT lc_val(const pb_linear_combination<FieldT> &lc) const;

    void add_r1cs_constraint(const r1cs_constraint<FieldT> &constr, const std::string &annotation="");
    void augment_variable_annotation(const pb_variable<FieldT> &v, const std::string &postfix);
    bool is_satisfied() const;
    void dump_variables() const;

    size_t num_constraints() const;
    size_t num_inputs() const;
    size_t num_variables() const;

    void set_input_sizes(const size_t primary_input_size);

    r1cs_variable_assignment<FieldT> full_variable_assignment() const;
    r1cs_primary_input<FieldT> primary_input() const;
    r1cs_auxiliary_input<FieldT> auxiliary_input() const;
    r1cs_constraint_system<FieldT> get_constraint_system() const;

    friend class pb_variable<FieldT>;
    friend class pb_linear_combination<FieldT>;

private:
    size_t allocate_variable_index(const std::string &annotation="");
    size_t allocate_linear_combination_index();
};

} // libsnark
#include "gadgetlib1/protoboard.tcc"
#endif // PROTOBOARD_HPP_

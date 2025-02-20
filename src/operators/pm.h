/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 - 2021 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#ifndef SRC_OPERATORS_PM_H_
#define SRC_OPERATORS_PM_H_

#include <string>
#include <memory>
#include <utility>
#include <mutex>

#include "src/operators/operator.h"
#include "src/utils/acmp.h"


namespace modsecurity {
namespace operators {


class Pm : public Operator {
 public:
    /** @ingroup ModSecurity_Operator */
    explicit Pm(std::unique_ptr<RunTimeString> param)
        : Operator("Pm", std::move(param)) {
        m_p = acmp_create(0);
    }
    explicit Pm(const std::string &n, std::unique_ptr<RunTimeString> param)
        : Operator(n, std::move(param)) {
        m_p = acmp_create(0);
    }
    ~Pm() override;
    bool evaluate(Transaction *transaction, RuleWithActions *rule,
        const std::string &str,
        RuleMessage &ruleMessage) override;


    bool init(const std::string &file, std::string *error) override;
    void postOrderTraversal(acmp_btree_node_t *node);
    void cleanup(acmp_node_t *n);

 protected:
    ACMP *m_p;
};


}  // namespace operators
}  // namespace modsecurity


#endif  // SRC_OPERATORS_PM_H_

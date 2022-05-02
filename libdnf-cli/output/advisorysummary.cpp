/*
Copyright Contributors to the libdnf project.

This file is part of libdnf: https://github.com/rpm-software-management/libdnf/

Libdnf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

Libdnf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libdnf.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "libdnf-cli/output/advisorysummary.hpp"

#include "libdnf-cli/output/key_value_table.hpp"

#include <iostream>

namespace libdnf::cli::output {


void print_advisorysummary_table(const libdnf::advisory::AdvisoryQuery & advisories, const std::string & mode) {
    KeyValueTable output_table;
    std::cout << mode << " advisory information summary:" << std::endl;

    libdnf::advisory::AdvisoryQuery bugfixes{advisories};
    bugfixes.filter_type("bugfix");

    libdnf::advisory::AdvisoryQuery enhancements{advisories};
    enhancements.filter_type("enhancement");

    libdnf::advisory::AdvisoryQuery securities{advisories};
    securities.filter_type("security");

    libdnf::advisory::AdvisoryQuery security_critical{securities};
    security_critical.filter_severity("Critical");
    libdnf::advisory::AdvisoryQuery security_important{securities};
    security_important.filter_severity("Important");
    libdnf::advisory::AdvisoryQuery security_moderate{securities};
    security_moderate.filter_severity("Moderate");
    libdnf::advisory::AdvisoryQuery security_low{securities};
    security_low.filter_severity("Low");
    libdnf::advisory::AdvisoryQuery security_none{securities};
    security_none.filter_severity("None");

    libdnf::advisory::AdvisoryQuery others{advisories};
    others -= bugfixes;
    others -= enhancements;
    others -= securities;

    auto security_row = output_table.add_line("Security", securities.size(), nullptr);
    output_table.add_line("Critical", security_critical.size(), nullptr, security_row);
    output_table.add_line("Important", security_important.size(), nullptr, security_row);
    output_table.add_line("Moderate", security_moderate.size(), nullptr, security_row);
    output_table.add_line("Low", security_low.size(), nullptr, security_row);
    output_table.add_line("None", security_none.size(), nullptr, security_row);

    output_table.add_line("Bugfix", bugfixes.size(), nullptr);
    output_table.add_line("Enhancement", enhancements.size(), nullptr);

    output_table.add_line("Others", others.size(), nullptr);

    output_table.print();
}


}  // namespace libdnf::cli::output

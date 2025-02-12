/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <dsn/cpp/rpc_holder.h>
#include <dsn/utility/errors.h>
#include <dsn/dist/replication/replication_types.h>

namespace dsn {
namespace replication {

typedef rpc_holder<duplication_modify_request, duplication_modify_response> duplication_modify_rpc;
typedef rpc_holder<duplication_add_request, duplication_add_response> duplication_add_rpc;
typedef rpc_holder<duplication_query_request, duplication_query_response> duplication_query_rpc;
typedef rpc_holder<duplication_sync_request, duplication_sync_response> duplication_sync_rpc;

typedef int32_t dupid_t;

extern const char *duplication_status_to_string(duplication_status::type status);

extern const char *duplication_fail_mode_to_string(duplication_fail_mode::type);

inline bool is_duplication_status_valid(duplication_status::type status)
{
    return status == duplication_status::DS_PAUSE || status == duplication_status::DS_START;
}

/// Returns the cluster id of url specified in the duplication-group section
/// of your configuration, for example:
///
/// ```
///   [duplication-group]
///       wuhan-mi-srv-ad = 3
///       tianjin-mi-srv-ad = 4
/// ```
///
/// The returned cluster id of get_duplication_cluster_id("wuhan-mi-srv-ad") is 3.
extern error_with<uint8_t> get_duplication_cluster_id(const std::string &cluster_name);

/// Returns a json string.
extern std::string duplication_entry_to_string(const duplication_entry &dup);

/// Returns a json string.
extern std::string duplication_query_response_to_string(const duplication_query_response &);

/// Returns a mapping from cluster_name to cluster_id.
extern const std::map<std::string, uint8_t> &get_duplication_group();

extern const std::set<uint8_t> &get_distinct_cluster_id_set();

inline bool is_cluster_id_configured(uint8_t cid)
{
    return get_distinct_cluster_id_set().find(cid) != get_distinct_cluster_id_set().end();
}

} // namespace replication
} // namespace dsn
